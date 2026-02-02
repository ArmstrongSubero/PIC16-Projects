/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 47_NRF24L01
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 * Program Version: 1.3
 *                  * Updated to PIC16F1718
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows us to use the nRF24L01+ module 
 *                      in a combined TX/RX configuration we send a fixed 
 *                      5 byte payload on channel 83 at 1 Mbps with a 2 byte 
 *                      CRC. We have a push-button that when we press rotates 
 *                      between commands send. 
 * 
 * Hardware Description: The HC-05 is connected to the PIC16F1718 as follows:
 *                      CE  -> RC0
 *                      CSN -> RC1
 *                      SCK -> RC3
 *                      SDI -> RC4   (nRF MISO -> PIC SDI)
 *                      SDO -> RC5   (PIC SDO  -> nRF MOSI)
 *
 *                      UART: EUSART (TX on RB2, RX on RB3)
 *                      Button: RB0 (to GND)
 *                       
 * Created on Thursday 29th January, 2026, 4:53 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "SPI.h"

/* ===================== SELECT ROLE HERE ===================== */
#define BUILD_AS_TX   1    /* 1 = transmitter (RB0 button sends commands) */
                           /* 0 = receiver (prints ASCII commands)       */
/* ============================================================ */

/* ===== nRF24L01+ registers & instructions ===== */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define RX_ADDR_P0  0x0A
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define FIFO_STATUS 0x17

/* Bit mnemonics */
#define MASK_RX_DR  0x40
#define MASK_TX_DS  0x20
#define MASK_MAX_RT 0x10
#define EN_CRC      0x08
#define CRCO        0x04
#define PWR_UP      0x02
#define PRIM_RX     0x01
#define AW5         0x03

/* Instructions */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define NOP           0xFF

/* ===== App config (MUST MATCH on TX + RX) ===== */
#define Channel       83
#define PAYLOAD_LEN   5   /* fixed 5 bytes */

/* ===== Pin map ===== */
#define NRF_CE_LAT    LATCbits.LATC0
#define NRF_CE_TRIS   TRISCbits.TRISC0
#define NRF_CSN_LAT   LATCbits.LATC1
#define NRF_CSN_TRIS  TRISCbits.TRISC1

static inline void CE_H(void){ NRF_CE_LAT = 1; }
static inline void CE_L(void){ NRF_CE_LAT = 0; }
static inline void CSN_H(void){ NRF_CSN_LAT = 1; }
static inline void CSN_L(void){ NRF_CSN_LAT = 0; }

/* Button RB0 (press to GND) */
#define BTN_TRIS      TRISBbits.TRISB0
#define BTN_PORT      PORTBbits.RB0
#define BTN_ANSEL     ANSELBbits.ANSB0
#define BTN_WPU       WPUBbits.WPUB0

/* Address MUST MATCH TX/RX */
static const uint8_t adr0[5] = {0x78,0x78,0x78,0x78,0x78};

/* ===== UART helpers ===== */
static void uart_crlf(void){ EUSART_Write('\r'); EUSART_Write('\n'); }
static void uart_print(const char *s){ EUSART_Write_Text((char*)s); }

static void uart_write_n(const char *buf, uint8_t n)
{
    for(uint8_t i=0;i<n;i++) EUSART_Write((uint8_t)buf[i]);
}

static void uart_hex8(uint8_t v)
{
    const char h[]="0123456789ABCDEF";
    EUSART_Write(h[(v>>4)&0x0F]);
    EUSART_Write(h[v&0x0F]);
}

/* ===== SPI xfer ===== */
static inline uint8_t spi_xfer(uint8_t b){ return SPI_Exchange8bit(b); }

/* ===== nRF low-level ===== */
static inline void toggleCSN(void)
{
    CSN_H(); __delay_us(20);
    CSN_L(); __delay_us(10);
}

static void nrf_write_reg(uint8_t reg, uint8_t val)
{
    CSN_L();
    spi_xfer(W_REGISTER | (reg & REGISTER_MASK));
    spi_xfer(val);
    CSN_H();
}

static uint8_t nrf_read_reg(uint8_t reg)
{
    uint8_t v;
    CSN_L();
    spi_xfer(R_REGISTER | (reg & REGISTER_MASK));
    v = spi_xfer(NOP);
    CSN_H();
    return v;
}

static void nrf_write_buf(uint8_t reg, const uint8_t *buf, uint8_t len)
{
    CSN_L();
    spi_xfer(W_REGISTER | (reg & REGISTER_MASK));
    for(uint8_t i=0;i<len;i++) spi_xfer(buf[i]);
    CSN_H();
}

static void nrf_cmd(uint8_t cmd)
{
    CSN_L();
    spi_xfer(cmd);
    CSN_H();
}

static void nrf_clear_irqs(void)
{
    nrf_write_reg(STATUS, MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT);
}

static void nrf_flush_all(void)
{
    nrf_cmd(FLUSH_TX);
    nrf_cmd(FLUSH_RX);
}

/* Read payload into buffer (fixed length) */
static void nrf_read_payload(uint8_t *buf, uint8_t len)
{
    CSN_L();
    spi_xfer(R_RX_PAYLOAD);
    for(uint8_t i=0;i<len;i++) buf[i] = spi_xfer(NOP);
    CSN_H();
}

/* Write payload from buffer (fixed length) */
static void nrf_write_payload(const uint8_t *buf, uint8_t len)
{
    CSN_L();
    spi_xfer(W_TX_PAYLOAD);
    for(uint8_t i=0;i<len;i++) spi_xfer(buf[i]);
    CSN_H();
}

/* ===== Common radio setup (no-ack, 1Mbps, CRC 2B) ===== */
static void radio_common_setup(void)
{
    CE_L();
    __delay_ms(5);

    nrf_flush_all();
    nrf_clear_irqs();

    /* Auto-ACK OFF */
    nrf_write_reg(EN_AA, 0x00);

    /* Enable pipe0 */
    nrf_write_reg(EN_RXADDR, 0x01);

    /* 5-byte address */
    nrf_write_reg(SETUP_AW, AW5);

    /* Retries OFF */
    nrf_write_reg(SETUP_RETR, 0x00);

    /* Channel + 1Mbps */
    nrf_write_reg(RF_CH, Channel);
    nrf_write_reg(RF_SETUP, 0x06);

    /* Addresses */
    nrf_write_buf(RX_ADDR_P0, adr0, 5);
    nrf_write_buf(TX_ADDR,    adr0, 5);

    /* Fixed payload size */
    nrf_write_reg(RX_PW_P0, (uint8_t)PAYLOAD_LEN);
}

/* ===== TX init ===== */
static void radio_init_tx(void)
{
    radio_common_setup();

    /* CONFIG: PWR_UP + CRC(2B), PRIM_RX=0 */
    nrf_write_reg(CONFIG, (PWR_UP | EN_CRC | CRCO)); /* 0x0E */
    __delay_ms(3);

    CE_L(); /* standby */
}

/* ===== RX init ===== */
static void radio_init_rx(void)
{
    radio_common_setup();

    /* CONFIG: PWR_UP + CRC(2B) + PRIM_RX */
    nrf_write_reg(CONFIG, (PWR_UP | EN_CRC | CRCO | PRIM_RX)); /* 0x0F */
    __delay_ms(3);

    CE_H(); /* listen */
}

/* ===== TX send: returns 1 if TX_DS, else 0 ===== */
static uint8_t tx_send_packet(const uint8_t *payload5)
{
    nrf_clear_irqs();
    nrf_cmd(FLUSH_TX);

    nrf_write_payload(payload5, PAYLOAD_LEN);

    /* CE pulse */
    CE_H();
    __delay_us(20);
    CE_L();

    /* wait for TX_DS */
    for(uint32_t t=0;t<60000;t++)
    {
        uint8_t st = nrf_read_reg(STATUS);
        if(st & MASK_TX_DS)
        {
            nrf_write_reg(STATUS, MASK_TX_DS);
            return 1;
        }
        if(st & MASK_MAX_RT)
        {
            nrf_write_reg(STATUS, MASK_MAX_RT);
            nrf_cmd(FLUSH_TX);
            return 0;
        }
    }
    nrf_cmd(FLUSH_TX);
    return 0;
}

/* ===== PPS + pins ===== */
static void initMain(void)
{
    internal_32();
    __delay_ms(100);

    /* UART pins */
    TRISBbits.TRISB2 = 0; ANSELBbits.ANSB2 = 0;
    TRISBbits.TRISB3 = 1; ANSELBbits.ANSB3 = 0;

    /* SPI pins */
    ANSELCbits.ANSC3 = 0; TRISCbits.TRISC3 = 0; /* SCK */
    ANSELCbits.ANSC4 = 0; TRISCbits.TRISC4 = 1; /* SDI */
    ANSELCbits.ANSC5 = 0; TRISCbits.TRISC5 = 0; /* SDO */

    /* CE/CSN pins */
    NRF_CE_TRIS  = 0;
    NRF_CSN_TRIS = 0;
    CE_L(); CSN_H();

    /* Button RB0 */
    BTN_TRIS  = 1;
    BTN_ANSEL = 0;
    /* enable weak pullups (or use external pullup) */
    OPTION_REGbits.nWPUEN = 0; /* global enable */
    BTN_WPU = 1;

    /* PPS */
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;      /* TX1 */
    RXPPSbits.RXPPS   = 0x0B;      /* RB3 -> RX1 */

    SSPDATPPSbits.SSPDATPPS = 0x14;/* RC4 -> SDI */
    RC3PPSbits.RC3PPS       = 0x10;/* RC3 -> SCK */
    RC5PPSbits.RC5PPS       = 0x11;/* RC5 -> SDO */

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;
}

/* ===== Simple debounce: returns 1 on NEW press =====
   Button wired to GND => pressed = 0
*/
static uint8_t button_pressed_event(void)
{
    static uint8_t last = 1;
    uint8_t now = BTN_PORT;

    if(now != last)
    {
        __delay_ms(20);          /* debounce */
        now = BTN_PORT;
        if(now != last)
        {
            last = now;
            if(now == 0) return 1; /* new press */
        }
    }
    return 0;
}

/* ===== Make 5-byte padded command ===== */
static void make_cmd5(uint8_t out[5], const char *s)
{
    /* pad with spaces */
    out[0]=' '; out[1]=' '; out[2]=' '; out[3]=' '; out[4]=' ';
    for(uint8_t i=0;i<5 && s[i]; i++) out[i] = (uint8_t)s[i];
}

void main(void)
{
    initMain();

    EUSART_Initialize(19200);
    SPI_Initialize();
    __delay_ms(50);

#if BUILD_AS_TX
    uart_crlf();
    uart_print("nRF24 TX NO-ACK ASCII  CH=");
    EUSART_Write_Integer(Channel);
    uart_print("  PL=");
    EUSART_Write_Integer(PAYLOAD_LEN);
    uart_crlf();

    radio_init_tx();

    /* Command list */
    const char *cmds[] = {"ON","OFF","UP","DOWN","LEFT","RIGHT"};
    const uint8_t N = (uint8_t)(sizeof(cmds)/sizeof(cmds[0]));
    uint8_t idx = 0;

    uint8_t pkt[5];

    uart_print("Press RB0 to send next command"); uart_crlf();

    while(1)
    {
        if(button_pressed_event())
        {
            make_cmd5(pkt, cmds[idx]);

            uint8_t ok = tx_send_packet(pkt);

            uart_print(ok ? "TX_DS OK  \"" : "TX FAIL   \"");
            uart_write_n((char*)pkt, 5);
            uart_print("\"");
            uart_crlf();

            idx++;
            if(idx >= N) idx = 0;
        }
    }

#else
    uart_crlf();
    uart_print("nRF24 RX NO-ACK ASCII  CH=");
    EUSART_Write_Integer(Channel);
    uart_print("  PL=");
    EUSART_Write_Integer(PAYLOAD_LEN);
    uart_crlf();

    radio_init_rx();

    uint8_t pkt[5];

    while(1)
    {
        uint8_t st = nrf_read_reg(STATUS);

        if(st & MASK_RX_DR)
        {
            nrf_read_payload(pkt, 5);

            /* clear RX_DR */
            nrf_write_reg(STATUS, MASK_RX_DR);

            uart_print("RX \"");
            uart_write_n((char*)pkt, 5);
            uart_print("\"  hex=");
            for(uint8_t i=0;i<5;i++){ uart_hex8(pkt[i]); EUSART_Write(' '); }
            uart_crlf();
        }

        __delay_ms(2);
    }
#endif
}

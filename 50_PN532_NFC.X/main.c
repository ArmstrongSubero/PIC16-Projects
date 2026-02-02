/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/Int OSC @ 32MHz, 5v
 * Program: 50_PN532_NFC
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC16F1718 to communicate with a 
 *                      PN532 NFC reader module, and perform NTAG text 
 *                      extraction, works with NTAG and Ultralight NFC cards
 *           
 * Hardware Description: A PN532 NFC module is connected to the PIC16F1718 as
 *                       follows:
 *                                      
 *                       RXD -> TX
 *                       TXD -> RX
 *                       GND -> GND
 *                       VCC -> VCC
 *                      
 *                       Pull-up resistors are needed with module. 
 * 
 *                                 
 * Created April 18th, 2017, 12:51 PM
 * Updated January 30th, 2026,  12:50 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "I2C.h"
#include <stdint.h>
#include <stdbool.h>
#include "pn532.h"

/* Scan range: skip reserved addresses */
#define I2C_SCAN_START_ADDR   0x08
#define I2C_SCAN_END_ADDR     0x77

/* ----------------------------- Helpers ----------------------------- */

static void print_hex8(uint8_t v)
{
    const char hex[] = "0123456789ABCDEF";
    char s[3];
    s[0] = hex[(v >> 4) & 0x0F];
    s[1] = hex[v & 0x0F];
    s[2] = '\0';
    EUSART_Write_Text(s);
}

static void print_hex_array(uint8_t *d, uint8_t n)
{
    for (uint8_t i = 0; i < n; i++) {
        print_hex8(d[i]);
        if (i + 1 < n) EUSART_Write_Text(" ");
    }
}

/*
 * Bus recovery for RC4(SDA) / RC5(SCL):
 */
static void I2C_BusRecover_RC4_RC5(void)
{
    SSPCONbits.SSPEN = 0;

    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;

    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;

    LATCbits.LATC5 = 1;
    __delay_us(10);

    for (uint8_t i = 0; i < 9; i++)
    {
        LATCbits.LATC5 = 0; __delay_us(10);
        LATCbits.LATC5 = 1; __delay_us(10);
    }

    TRISCbits.TRISC4 = 0;
    LATCbits.LATC4 = 0;     __delay_us(10);
    LATCbits.LATC5 = 1;     __delay_us(10);
    LATCbits.LATC4 = 1;     __delay_us(10);

    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    SSPCONbits.SSPEN = 1;

    SSPCON1bits.SSPOV = 0;
    SSPCON1bits.WCOL  = 0;
    PIR1bits.SSP1IF   = 0;
    PIR2bits.BCL1IF   = 0;
}

/* ----------------------------- Scanner ----------------------------- */

static void I2C_ScanBus_Robust(void)
{
    uint8_t  found = 0;
    uint16_t timeouts = 0;
    uint16_t collisions = 0;

    I2C_BusRecover_RC4_RC5();

    EUSART_Write_Text("\n=== I2C BUS SCAN (7-bit 0x08..0x77) ===\n");

    for (uint8_t addr = I2C_SCAN_START_ADDR; addr <= I2C_SCAN_END_ADDR; addr++)
    {
        I2C_ClearErrors();

        I2C_Status_t st = I2C_Start();
        if (st != I2C_OK)
        {
            if (st == I2C_TIMEOUT) timeouts++;
            I2C_BusRecover_RC4_RC5();
            continue;
        }

        st = I2C_WriteByte((uint8_t)((addr << 1) | 0u));
        (void)I2C_Stop();

        if (st == I2C_TIMEOUT)
        {
            timeouts++;
            I2C_BusRecover_RC4_RC5();
            continue;
        }
        if (st == I2C_BUS_COLLISION)
        {
            collisions++;
            I2C_BusRecover_RC4_RC5();
            continue;
        }

        if (st == I2C_OK)
        {
            found++;
            EUSART_Write_Text("FOUND: 0x");
            print_hex8(addr);

            if (addr == 0x24) EUSART_Write_Text("  <PN532 common>");
            if (addr == 0x68) EUSART_Write_Text("  <MPU6050 common>");
            if (addr == 0x3C || addr == 0x3D) EUSART_Write_Text("  <SSD1306 common>");

            EUSART_Write_Text("\n");
        }

        __delay_ms(2);
    }

    EUSART_Write_Text("Total found: ");
    EUSART_Write_Integer(found);
    EUSART_Write_Text("  timeouts=");
    EUSART_Write_Integer(timeouts);
    EUSART_Write_Text("  collisions=");
    EUSART_Write_Integer(collisions);
    EUSART_Write_Text("\n");
}

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/
static void initMain(void)
{
    internal_32();
    __delay_ms(10);

    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;

    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS   = 0x0B;

    RC4PPSbits.RC4PPS         = 0x11;
    SSPDATPPSbits.SSPDATPPS   = 0x14;

    SSPCLKPPSbits.SSPCLKPPS   = 0x15;
    RC5PPSbits.RC5PPS         = 0x10;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/
void main(void)
{
    initMain();

    EUSART_Initialize(19200);
    I2C_Init();

    __delay_ms(2000);
    
    EUSART_Write_Text("\n=== I2C Scan Bus ===\n");
    I2C_ScanBus_Robust();
     
    EUSART_Write_Text("\nPN532 PIC16F1719 I2C TEST\n");

    PN532_Init_PIC();

    uint8_t ver[4] = {0};
    if (PN532_GetFirmwareVersion(ver) != PN532_STATUS_OK) {
        EUSART_Write_Text("PN532 firmware read FAILED\n");
        while (1);
    }

    EUSART_Write_Text("PN532 FW: ");
    print_hex_array(ver, 4);
    EUSART_Write_Text("\n");

    if (PN532_SamConfiguration() != PN532_STATUS_OK) {
        EUSART_Write_Text("SAM config FAILED\n");
        while (1);
    }
    EUSART_Write_Text("SAM OK. Tap card...\n");

    uint8_t uid[10];
    uint8_t last_uid[10] = {0};
    int last_uid_len = 0;
    char card_text[64];  // Buffer for extracted NDEF text

    while (1)
    {
        int uid_len = PN532_ReadPassiveTarget(uid, 0x00, 500);
        
        if (uid_len > 0) {
            // Check if this is a new card (different UID)
            bool new_card = (uid_len != last_uid_len);
            if (!new_card) {
                for (int i = 0; i < uid_len; i++) {
                    if (uid[i] != last_uid[i]) {
                        new_card = true;
                        break;
                    }
                }
            }

            if (new_card) {
                // New card detected - read it
                EUSART_Write_Text("\n=============================\n");
                EUSART_Write_Text("Card UID: ");
                print_hex_array(uid, (uint8_t)uid_len);
                EUSART_Write_Text(" (");
                EUSART_Write_Integer(uid_len);
                EUSART_Write_Text(" bytes)\n");

                // Detect card type by UID length:
                // - 4 bytes = MIFARE Classic or NTAG (single size UID)
                // - 7 bytes = NTAG21x, MIFARE Ultralight (double size UID)
                
                if (uid_len == 4) {
                    // Could be MIFARE Classic - try to read as Classic first
                    EUSART_Write_Text("Trying MIFARE Classic...\n");
                    PN532_DumpMifareClassic(uid, (uint8_t)uid_len);
                    // Text is printed inside dump function if found
                } else {
                    // 7-byte UID = NTAG/Ultralight
                    EUSART_Write_Text("NTAG/Ultralight detected\n");
                    PN532_DumpNtagCard();

                    // Extract NDEF text into variable
                    if (PN532_GetNdefText(card_text, sizeof(card_text)) == PN532_STATUS_OK) {
                        EUSART_Write_Text("\n>>> NDEF Text: \"");
                        EUSART_Write_Text(card_text);
                        EUSART_Write_Text("\"\n");
                    }
                }

                EUSART_Write_Text("=============================\n");
                EUSART_Write_Text("Remove card...\n");

                // Save UID to detect when card is removed/changed
                for (int i = 0; i < uid_len; i++) {
                    last_uid[i] = uid[i];
                }
                last_uid_len = uid_len;
            }
            
            __delay_ms(500);
            
        } else {
            // No card detected
            if (last_uid_len > 0) {
                // Card was just removed - recover I2C bus
                EUSART_Write_Text("Card removed. Tap another...\n");
                last_uid_len = 0;
                PN532_ClearDump();  // Clear stored data
                I2C_BusRecover_RC4_RC5();  // Recover I2C bus
                __delay_ms(100);
                PN532_SamConfiguration();  // Reinit SAM
            }
            EUSART_Write_Text(".");
            __delay_ms(300);
        }
    }
}
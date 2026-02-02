#include <xc.h>
#include <stdint.h>

#include "sdcard.h"
#include "SPI.h"
#include "EUSART.h"

// 512 byte read buffer
unsigned char SDRdata[512];
// 512 byte write buffer
unsigned char SDWdata[512];

// SD command buffer
static unsigned char SDcommand[6];

// ---------- SD CS pin (matches your current SPI wiring: SS on RC2) ----------
#define SD_CS_TRIS   TRISCbits.TRISC2
#define SD_CS_LAT    LATCbits.LATC2

static inline void SD_Select(void)   { SD_CS_LAT = 0; }
static inline void SD_Deselect(void) { SD_CS_LAT = 1; }

// ---------- UART debug helpers (minimal) ----------
static inline void dbg(const char *s)
{
    EUSART_Write_Text((char*)s); // cast because your API isn't const-correct
}

// ---------- SPI helpers built on your MSSP driver ----------
static inline uint8_t sd_xfer(uint8_t b)
{
    return SPI_Exchange8bit(b);
}

static void sd_send(const uint8_t *buf, uint16_t len)
{
    while (len--)
    {
        (void)sd_xfer(*buf++);
    }
}

static void sd_recv(uint8_t *buf, uint16_t len)
{
    while (len--)
    {
        *buf++ = sd_xfer(0xFF); // SD read clocks must be 0xFF
    }
}

// ---------- Wait for a specific response byte, with timeout ----------
static unsigned char SDcard_get_response(unsigned char response)
{
    unsigned int t = SD_TIMEOUT;          // IMPORTANT: reset timeout each call
    unsigned char b;

    do
    {
        b = sd_xfer(0xFF);                // clock while waiting
        if (b == response) return 0;      // success
    }
    while (--t);

    return 1; // timeout
}

void SDcard_init(void)
{
    dbg("Starting SD card initialization...\n");

    // Ensure CS pin configured as output, deasserted
    SD_CS_TRIS = 0;
    SD_Deselect();

    // Send 80 clocks with CS high (10 bytes of 0xFF)
    for (unsigned char i = 0; i < 10; i++) SDWdata[i] = 0xFF;
    sd_send(SDWdata, 10);

    // Select card
    SD_Select();

    dbg("Sending CMD0, awaiting response...");
    SDcommand[0] = 0x40; // CMD0
    SDcommand[1] = 0x00;
    SDcommand[2] = 0x00;
    SDcommand[3] = 0x00;
    SDcommand[4] = 0x00;
    SDcommand[5] = 0x95; // valid CRC for CMD0 in SPI mode
    sd_send(SDcommand, 6);

    if (SDcard_get_response(0x01))
    {
        dbg("timeout/fail\n");
        SD_Deselect();
        return;
    }
    dbg("success!\n");

    dbg("Sending CMD1, awaiting response...");
    SDcommand[0] = 0x41; // CMD1
    SDcommand[1] = 0x00;
    SDcommand[2] = 0x00;
    SDcommand[3] = 0x00;
    SDcommand[4] = 0x00;
    SDcommand[5] = 0xFF; // dummy CRC

    // Wait until card leaves idle (R1 becomes 0x00)
    while (1)
    {
        sd_send(SDcommand, 6);

        // R1 response can come after a few 0xFF bytes
        unsigned int t = SD_TIMEOUT;
        unsigned char r1 = 0xFF;
        while (t--)
        {
            r1 = sd_xfer(0xFF);
            if (r1 != 0xFF) break;
        }
        if (r1 == 0x00) break;
    }
    dbg("success!\n");

    SD_Deselect();
    sd_xfer(0xFF); // trailing clocks (good practice)
    dbg("SD card initialized successfully!\n");
}

void SDcard_read_block(unsigned long address)
{
    dbg("Sending CMD17...");
    SD_Select();

    SDcommand[0] = 0x51; // CMD17
    SDcommand[1] = (address >> 24) & 0xFF;
    SDcommand[2] = (address >> 16) & 0xFF;
    SDcommand[3] = (address >> 8) & 0xFF;
    SDcommand[4] = (address >> 0) & 0xFF;
    SDcommand[5] = 0xFF;

    sd_send(SDcommand, 6);

    if (SDcard_get_response(0x00))
    {
        dbg("timeout/fail\n");
        SD_Deselect();
        sd_xfer(0xFF);
        return;
    }
    dbg("success!\n");

    // Wait for data token 0xFE
    if (SDcard_get_response(0xFE))
    {
        dbg("token timeout\n");
        SD_Deselect();
        sd_xfer(0xFF);
        return;
    }

    sd_recv(SDRdata, 512);

    // discard CRC
    (void)sd_xfer(0xFF);
    (void)sd_xfer(0xFF);

    SD_Deselect();
    sd_xfer(0xFF);
}

void SDcard_write_block(unsigned long address)
{
    dbg("Sending CMD24...");
    SD_Select();

    SDcommand[0] = 0x58; // CMD24
    SDcommand[1] = (address >> 24) & 0xFF;
    SDcommand[2] = (address >> 16) & 0xFF;
    SDcommand[3] = (address >> 8) & 0xFF;
    SDcommand[4] = (address >> 0) & 0xFF;
    SDcommand[5] = 0xFF;

    sd_send(SDcommand, 6);

    if (SDcard_get_response(0x00))
    {
        dbg("timeout/fail\n");
        SD_Deselect();
        sd_xfer(0xFF);
        return;
    }
    dbg("success!\n");

    // gap byte
    sd_xfer(0xFF);

    dbg("Sending data block...");
    sd_xfer(0xFE);              // data token
    sd_send(SDWdata, 512);      // payload
    sd_xfer(0xFF);              // CRC dummy
    sd_xfer(0xFF);

    // data response token
    unsigned char resp = sd_xfer(0xFF);

    if ((resp & 0x0F) == 0x0D) dbg("write error occured!\n");
    if ((resp & 0x0F) == 0x0B) dbg("CRC error occured!\n");
    if ((resp & 0x0F) == 0x05)
    {
        dbg("success!\n");
        dbg("Waiting for card to finish write process...");

        // busy wait: card holds MISO low (0x00) while busy; ready is 0xFF
        unsigned int t = SD_TIMEOUT;
        while (t--)
        {
            if (sd_xfer(0xFF) == 0xFF) break;
        }
        if (t == 0) dbg("timeout!");
        dbg("done!\n");
    }

    SD_Deselect();
    sd_xfer(0xFF);
}

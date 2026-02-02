// SD Card.c 
// we use CMD8 + ACMD41 + CMD58 so we get SD v2 /SDHC capable init 
// keeps compatability with SDSC cards as well. 
// we switch byte vs block addressing using a flag

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

// SDHC flag: 0 = SDSC (byte addressing), 1 = SDHC/SDXC (block addressing)
static uint8_t sd_is_sdhc = 0;

// ---------- SD CS pin; SS on RC2 ----------
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
        (void)sd_xfer(*buf++);
}

static void sd_recv(uint8_t *buf, uint16_t len)
{
    while (len--)
        *buf++ = sd_xfer(0xFF); // SD read clocks must be 0xFF
}

// ---------- Wait for a specific response byte, with timeout ----------
static unsigned char SDcard_get_response(unsigned char response)
{
    unsigned int t = SD_TIMEOUT;
    unsigned char b;

    do
    {
        b = sd_xfer(0xFF);
        if (b == response) return 0;
    }
    while (--t);

    return 1;
}

// ---------- Read an R1 response (first non-0xFF), with timeout ----------
static unsigned char sd_get_r1(void)
{
    unsigned int t = SD_TIMEOUT;
    unsigned char r1 = 0xFF;

    while (t--)
    {
        r1 = sd_xfer(0xFF);
        if (r1 != 0xFF) break;
    }
    return r1; // may still be 0xFF if timed out
}

// ---------- Send a command packet and return R1 ----------
static unsigned char sd_send_cmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    SDcommand[0] = 0x40 | (cmd & 0x3F);
    SDcommand[1] = (uint8_t)(arg >> 24);
    SDcommand[2] = (uint8_t)(arg >> 16);
    SDcommand[3] = (uint8_t)(arg >> 8);
    SDcommand[4] = (uint8_t)(arg >> 0);
    SDcommand[5] = crc;

    sd_send(SDcommand, 6);
    return sd_get_r1();
}

// ---------- ACMD helper: CMD55 then CMD41 ----------
static unsigned char sd_send_acmd41(uint32_t arg)
{
    unsigned char r1;

    r1 = sd_send_cmd(55, 0, 0xFF); // CMD55
    if (r1 > 0x01) return r1;

    r1 = sd_send_cmd(41, arg, 0xFF); // ACMD41
    return r1;
}

void SDcard_init(void)
{
    dbg("Starting SD card initialization...\n");

    sd_is_sdhc = 0;

    // Ensure CS pin configured as output, deasserted
    SD_CS_TRIS = 0;
    SD_Deselect();

    // 80 clocks with CS high
    for (unsigned char i = 0; i < 10; i++) SDWdata[i] = 0xFF;
    sd_send(SDWdata, 10);

    // Select card
    SD_Select();

    dbg("Sending CMD0, awaiting response...");
    // CMD0: go to idle, CRC required = 0x95
    if (sd_send_cmd(0, 0, 0x95) != 0x01)
    {
        dbg("fail\n");
        SD_Deselect();
        sd_xfer(0xFF);
        return;
    }
    dbg("success!\n");

    // CMD8: voltage check (SD v2+)
    dbg("Sending CMD8...");
    unsigned char r1 = sd_send_cmd(8, 0x000001AAUL, 0x87); // CRC required for CMD8
    if (r1 == 0x01)
    {
        // Read R7 (4 bytes)
        uint8_t r7[4];
        sd_recv(r7, 4);

        // Check pattern 0x1AA (only need last byte == 0xAA; r7[2] typically 0x01)
        if (r7[3] == 0xAA)
        {
            dbg("SD v2 detected.\n");

            // ACMD41 with HCS bit (bit30) to request SDHC
            dbg("Initializing with ACMD41...");
            unsigned int t = SD_TIMEOUT;
            do
            {
                r1 = sd_send_acmd41(0x40000000UL);
                if (r1 == 0x00) break;
            }
            while (--t);

            if (t == 0)
            {
                dbg("ACMD41 timeout\n");
                SD_Deselect();
                sd_xfer(0xFF);
                return;
            }
            dbg("done!\n");

            // CMD58 read OCR to detect SDHC
            dbg("Reading OCR (CMD58)...");
            r1 = sd_send_cmd(58, 0, 0xFF);
            if (r1 != 0x00)
            {
                dbg("fail\n");
                SD_Deselect();
                sd_xfer(0xFF);
                return;
            }

            uint8_t ocr[4];
            sd_recv(ocr, 4);

            // CCS bit = OCR[0] bit6 (bit30 overall)
            if (ocr[0] & 0x40)
            {
                sd_is_sdhc = 1;
                dbg("SDHC/SDXC detected.\n");
            }
            else
            {
                sd_is_sdhc = 0;
                dbg("SDSC v2 detected.\n");
            }
        }
        else
        {
            dbg("CMD8 pattern mismatch.\n");
        }
    }
    else
    {
        // Older SDSC v1 card: CMD8 illegal, use ACMD41 without HCS, or CMD1 fallback
        // Many SDSC v1 cards support ACMD41 too; try it first.
        dbg("CMD8 not supported (likely SDSC v1). Init...\n");

        unsigned int t = SD_TIMEOUT;
        do
        {
            r1 = sd_send_acmd41(0x00000000UL);
            if (r1 == 0x00) break;
        }
        while (--t);

        if (t == 0)
        {
            // Fallback to CMD1 (old method))
            dbg("ACMD41 timeout, trying CMD1...\n");
            while (1)
            {
                r1 = sd_send_cmd(1, 0, 0xFF);
                if (r1 == 0x00) break;
            }
        }

        sd_is_sdhc = 0; // SDSC uses byte addressing
    }

    SD_Deselect();
    sd_xfer(0xFF);
    dbg("SD card initialized successfully!\n");
}

void SDcard_read_block(unsigned long address)
{
    dbg("Sending CMD17...");
    SD_Select();

    // Convert byte address -> block address if SDHC
    uint32_t arg = (uint32_t)address;
    if (sd_is_sdhc)
        arg >>= 9; // divide by 512

    // CMD17
    SDcommand[0] = 0x51;
    SDcommand[1] = (arg >> 24) & 0xFF;
    SDcommand[2] = (arg >> 16) & 0xFF;
    SDcommand[3] = (arg >> 8) & 0xFF;
    SDcommand[4] = (arg >> 0) & 0xFF;
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

    // Convert byte address -> block address if SDHC
    uint32_t arg = (uint32_t)address;
    if (sd_is_sdhc)
        arg >>= 9;

    // CMD24
    SDcommand[0] = 0x58;
    SDcommand[1] = (arg >> 24) & 0xFF;
    SDcommand[2] = (arg >> 16) & 0xFF;
    SDcommand[3] = (arg >> 8) & 0xFF;
    SDcommand[4] = (arg >> 0) & 0xFF;
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
    sd_xfer(0xFE);
    sd_send(SDWdata, 512);
    sd_xfer(0xFF);
    sd_xfer(0xFF);

    unsigned char resp = sd_xfer(0xFF);

    if ((resp & 0x0F) == 0x0D) dbg("write error occured!\n");
    if ((resp & 0x0F) == 0x0B) dbg("CRC error occured!\n");
    if ((resp & 0x0F) == 0x05)
    {
        dbg("success!\n");
        dbg("Waiting for card to finish write process...");

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

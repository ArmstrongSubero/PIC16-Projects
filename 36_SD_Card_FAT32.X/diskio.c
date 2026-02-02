#include <xc.h>
#include <stdint.h>
#include "diskio.h"
#include "SPI.h"
#include "EUSART.h"

// ---- SD CS on RC2 (matches your wiring) ----
#define CS_TRIS   TRISCbits.TRISC2
#define CS_LAT    LATCbits.LATC2
#define CS_LOW()  (CS_LAT = 0)
#define CS_HIGH() (CS_LAT = 1)

static inline uint8_t xfer_spi(uint8_t d)
{
    return SPI_Exchange8bit(d);
}

static void xmit_spi(uint8_t d)
{
    (void)xfer_spi(d);
}

static uint8_t rcv_spi(void)
{
    return xfer_spi(0xFF);
}

// crude delay ~100us scale (tune if you want)
static void dly_100us(void)
{
    __delay_us(100);
}

// ---- SD Commands ----
#define CMD0    (0x40+0)
#define CMD1    (0x40+1)
#define ACMD41  (0xC0+41)
#define CMD8    (0x40+8)
#define CMD16   (0x40+16)
#define CMD17   (0x40+17)
#define CMD24   (0x40+24)
#define CMD55   (0x40+55)
#define CMD58   (0x40+58)

// Card type flags
static uint8_t CardType;
#define CT_MMC    0x01
#define CT_SD1    0x02
#define CT_SD2    0x04
#define CT_BLOCK  0x08

// ---- Send command (PIC24-style, but on PIC16) ----
static uint8_t send_cmd_raw(uint8_t cmd, uint32_t arg)
{
    uint8_t n, res;

    // Select card with a dummy clock
    CS_HIGH(); rcv_spi();
    CS_LOW();  rcv_spi();

    xmit_spi(cmd);
    xmit_spi((uint8_t)(arg >> 24));
    xmit_spi((uint8_t)(arg >> 16));
    xmit_spi((uint8_t)(arg >> 8));
    xmit_spi((uint8_t)arg);

    // CRC (only required for CMD0 and CMD8 in SPI mode)
    n = 0x01;
    if (cmd == CMD0) n = 0x95;
    if (cmd == CMD8) n = 0x87;
    xmit_spi(n);

    n = 10;
    do { res = rcv_spi(); } while ((res & 0x80) && --n);

    return res;
}

static uint8_t send_cmd(uint8_t cmd, uint32_t arg)
{
    uint8_t res;

    if (cmd & 0x80) {                  // ACMD: CMD55 then CMDxx
        cmd &= 0x7F;
        res = send_cmd_raw(CMD55, 0);
        if (res > 1) return res;
    }
    return send_cmd_raw(cmd, arg);
}


// ---- Public diskio API ----
DSTATUS disk_initialize(void)
{
    uint8_t n, ty, ocr[4];
    uint16_t tmr;

    // Make sure CS is output + high
    CS_TRIS = 0;
    CS_HIGH();

    // 80 clocks with CS high
    for (n = 10; n; n--) rcv_spi();

    ty = 0;

    if (send_cmd(CMD0, 0) == 1) {
        // Idle

        if (send_cmd(CMD8, 0x1AA) == 1) {
            // SDv2
            for (n = 0; n < 4; n++) ocr[n] = rcv_spi();

            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {
                // Wait for ACMD41(HCS)
                for (tmr = 10000; tmr && send_cmd(ACMD41, 1UL << 30); tmr--) dly_100us();

                if (tmr && send_cmd(CMD58, 0) == 0) {
                    for (n = 0; n < 4; n++) ocr[n] = rcv_spi();
                    ty = (ocr[0] & 0x40) ? (CT_SD2 | CT_BLOCK) : CT_SD2;
                }
            }

        } else {
            // SDv1 or MMC
            uint8_t cmd;
            if (send_cmd(ACMD41, 0) <= 1) { ty = CT_SD1; cmd = ACMD41; }
            else { ty = CT_MMC; cmd = CMD1; }

            for (tmr = 10000; tmr && send_cmd(cmd, 0); tmr--) dly_100us();

            if (!tmr || send_cmd(CMD16, 512) != 0) {
                ty = 0;
            }
        }
    }

    CardType = ty;
    CS_HIGH();
    rcv_spi();

    return ty ? 0 : STA_NOINIT;
}

DRESULT disk_readp(BYTE* buff, DWORD sector, UINT offset, UINT count)
{
    uint16_t i;
    uint8_t token;
    UINT offset0 = offset;
    UINT count0  = count;

    if (!(CardType & CT_BLOCK)) sector *= 512;

    if (send_cmd(CMD17, sector) != 0) {
        CS_HIGH(); rcv_spi();
        return RES_ERROR;
    }

    i = 40000;
    do {
        token = rcv_spi();
    } while (token == 0xFF && --i);

    if (token != 0xFE) {
        CS_HIGH(); rcv_spi();
        return RES_ERROR;
    }

    while (offset--) rcv_spi();
    while (count--) *buff++ = rcv_spi();

    // Drain remaining bytes in the 512-byte block
    i = (uint16_t)(512 - (offset0 + count0));
    while (i--) rcv_spi();

    // Discard CRC
    rcv_spi();
    rcv_spi();

    CS_HIGH();
    rcv_spi();

    return RES_OK;
}

DRESULT disk_writep (const BYTE* buff, DWORD sc)
{
    static uint16_t wc;      // bytes remaining in current 512B sector
    uint8_t token;

    if (!buff) {
        if (sc) {
            // ---- START WRITE: sc = sector number ----
            if (!(CardType & CT_BLOCK)) sc *= 512;

            if (send_cmd(CMD24, sc) != 0) {
                CS_HIGH(); rcv_spi();
                return RES_ERROR;
            }

            token = 0xFE;
            xmit_spi(token);
            wc = 512;
            return RES_OK;
        } else {
            // ---- FINALIZE WRITE ----
            // pad remaining bytes with 0xFF
            while (wc) { xmit_spi(0xFF); wc--; }

            // dummy CRC
            xmit_spi(0xFF);
            xmit_spi(0xFF);

            // data response
            uint8_t resp = rcv_spi();
            if ((resp & 0x1F) != 0x05) {   // 0x05 = accepted
                CS_HIGH(); rcv_spi();
                return RES_ERROR;
            }

            // wait until not busy
            while (rcv_spi() == 0x00) {;}

            CS_HIGH(); rcv_spi();
            return RES_OK;
        }
    }

    // ---- STREAM BYTES ----
    while (sc && wc) {
        xmit_spi(*buff++);
        wc--;
        sc--;
    }

    return RES_OK;
}

#include <xc.h>
#include <stdint.h>
#include "diskio.h"
#include "SPI.h"

// ---- SD CS on RC2 ----
#define CS_TRIS   TRISCbits.TRISC2
#define CS_LAT    LATCbits.LATC2
#define CS_LOW()  (CS_LAT = 0)
#define CS_HIGH() (CS_LAT = 1)

static inline uint8_t xfer_spi(uint8_t d) { return SPI_Exchange8bit(d); }
static void xmit_spi(uint8_t d) { (void)xfer_spi(d); }
static uint8_t rcv_spi(void) { return xfer_spi(0xFF); }

static void dly_100us(void) { __delay_us(100); }

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

static uint8_t CardType;
#define CT_MMC    0x01
#define CT_SD1    0x02
#define CT_SD2    0x04
#define CT_BLOCK  0x08

static DSTATUS Stat = STA_NOINIT;

// ---- Helpers ----
static void deselect(void)
{
    CS_HIGH();
    rcv_spi(); // extra clock
}

static uint8_t select_card(void)
{
    CS_LOW();
    rcv_spi(); // dummy
    // wait ready (optional)
    uint16_t tmr = 5000;
    while (tmr-- && rcv_spi() != 0xFF) dly_100us();
    return (tmr != 0);
}

static uint8_t send_cmd_raw(uint8_t cmd, uint32_t arg)
{
    uint8_t n, res;

    deselect();
    if (!select_card()) return 0xFF;

    xmit_spi(cmd);
    xmit_spi((uint8_t)(arg >> 24));
    xmit_spi((uint8_t)(arg >> 16));
    xmit_spi((uint8_t)(arg >> 8));
    xmit_spi((uint8_t)arg);

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

    if (cmd & 0x80) { // ACMD
        cmd &= 0x7F;
        res = send_cmd_raw(CMD55, 0);
        if (res > 1) return res;
    }
    return send_cmd_raw(cmd, arg);
}

static uint8_t rcvr_datablock(uint8_t* buff, uint16_t btr)
{
    uint8_t token;
    uint16_t tmr = 40000;

    do { token = rcv_spi(); } while (token == 0xFF && --tmr);
    if (token != 0xFE) return 0;

    do { *buff++ = rcv_spi(); } while (--btr);

    rcv_spi(); // CRC
    rcv_spi();
    return 1;
}

static uint8_t xmit_datablock(const uint8_t* buff)
{
    uint8_t resp;

    xmit_spi(0xFE); // data token
    for (uint16_t i = 0; i < 512; i++) xmit_spi(buff[i]);

    xmit_spi(0xFF); // CRC dummy
    xmit_spi(0xFF);

    resp = rcv_spi();
    if ((resp & 0x1F) != 0x05) return 0; // accepted?

    while (rcv_spi() == 0x00) {;} // busy wait
    return 1;
}

// ---- FatFs required API ----
DSTATUS disk_status(BYTE pdrv)
{
    (void)pdrv;
    return Stat;
}

DSTATUS disk_initialize(BYTE pdrv)
{
    (void)pdrv;

    uint8_t n, ty, ocr[4];
    uint16_t tmr;

    CS_TRIS = 0;
    CS_HIGH();

    // 80 clocks with CS high
    for (n = 10; n; n--) rcv_spi();

    ty = 0;

    if (send_cmd(CMD0, 0) == 1) {

        if (send_cmd(CMD8, 0x1AA) == 1) {
            for (n = 0; n < 4; n++) ocr[n] = rcv_spi();

            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {
                for (tmr = 10000; tmr && send_cmd(ACMD41, 1UL << 30); tmr--) dly_100us();

                if (tmr && send_cmd(CMD58, 0) == 0) {
                    for (n = 0; n < 4; n++) ocr[n] = rcv_spi();
                    ty = (ocr[0] & 0x40) ? (CT_SD2 | CT_BLOCK) : CT_SD2;
                }
            }

        } else {
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
    deselect();

    if (ty) {
        Stat &= (DSTATUS)~STA_NOINIT;
    } else {
        Stat = STA_NOINIT;
    }

    return Stat;
}

DRESULT disk_read(BYTE pdrv, BYTE* buff, LBA_t sector, UINT count)
{
    (void)pdrv;

    if (!count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    if (!(CardType & CT_BLOCK)) sector *= 512;

    while (count--) {
        if (send_cmd(CMD17, (uint32_t)sector) != 0) { deselect(); return RES_ERROR; }
        if (!rcvr_datablock(buff, 512)) { deselect(); return RES_ERROR; }
        deselect();

        sector++;
        buff += 512;
    }

    return RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count)
{
    (void)pdrv;

    if (!count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    if (!(CardType & CT_BLOCK)) sector *= 512;

    while (count--) {
        if (send_cmd(CMD24, (uint32_t)sector) != 0) { deselect(); return RES_ERROR; }
        if (!xmit_datablock(buff)) { deselect(); return RES_ERROR; }
        deselect();

        sector++;
        buff += 512;
    }

    return RES_OK;
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff)
{
    (void)pdrv;

    if (Stat & STA_NOINIT) return RES_NOTRDY;

    switch (cmd) {
        case CTRL_SYNC:
            // We wait for ready in select_card(); so just OK here
            return RES_OK;

        case GET_SECTOR_SIZE:
            *(WORD*)buff = 512;
            return RES_OK;

        case GET_BLOCK_SIZE:
            // erase block size in sectors (rough default)
            *(DWORD*)buff = 1;
            return RES_OK;

        case GET_SECTOR_COUNT:
            // Optional but nice. You can implement by reading CSD.
            // For now, return PARERR to indicate ?not supported?.
            return RES_PARERR;

        default:
            return RES_PARERR;
    }
}

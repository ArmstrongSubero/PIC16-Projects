/*-----------------------------------------------------------------------/
/  Low level disk interface modlue include file   (C)ChaN, 2014          /
/-----------------------------------------------------------------------*/

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif
    
// get/set SD_CS aliases
#define SD_CS_TRIS               TRISC0
#define SD_CS_LAT                LATC0
#define SD_CS_PORT               PORTCbits.RC0
#define SD_CS_SetHigh()    do { LATC0 = 1; } while(0)
#define SD_CS_SetLow()   do { LATC0 = 0; } while(0)
#define SD_CS_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define SD_CS_GetValue()         PORTCbits.RC0
#define SD_CS_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define SD_CS_SetDigitalOutput()   do { TRISC0 = 0; } while(0)    
    

#define _USE_WRITE	1	/* 1: Enable disk_write function */
#define _USE_IOCTL	1	/* 1: Enable disk_ioctl fucntion */

#define _SD_SPI 1
/* This option defines the SPI port to be used.
/
/   0: Default port (for devices with a single MSSP)
/   1: SPI 1
/   2: SPI 2 */

#include "integer.h"
#include "SPI.h"

/* Status of Disk Functions */
typedef BYTE	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */


/* Command code for disk_ioctrl fucntion */

/* Generic command (Used by FatFs) */
#define CTRL_SYNC			0	/* Complete pending write process (needed at _FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size (needed at _USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size (needed at _MAX_SS != _MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at _USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at _USE_TRIM == 1) */

/* Generic command (Not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status */
#define CTRL_LOCK			6	/* Lock/Unlock media removal */
#define CTRL_EJECT			7	/* Eject media */
#define CTRL_FORMAT			8	/* Create physical format on the media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision */
#define ATA_GET_MODEL		21	/* Get model name */
#define ATA_GET_SN			22	/* Get serial number */


/*-------------------------------------*/
/* PIC18 SPI definitions and functions */

/* Note: sd_init() must open SPI at a speed between 100-400 KHz */

#if _SD_SPI == 1

#define sd_init()	SPI_Initialize()
#define sd_open()	
#define sd_tx(d)	SPI_Exchange8bit(d)
#define sd_rx()		SPI_Exchange8bit(0xFF)

#elif _SD_SPI == 2

#define sd_init()	SPI2_Initialize()
#define sd_open()	SPI2_Open()
#define sd_tx(d)	SPI2_Exchange8bit(d)
#define sd_rx()		SPI2_Exchange8bit(0xFF)

#else

#define sd_init()	SPI_Initialize()
#define sd_open()	SPI_Open()
#define sd_tx(d)	SPI_Exchange8bit(d)
#define sd_rx()		SPI_Exchange8bit(0xFF)

#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 37_SD_Card_FATFS
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This program allows us to use the PIC16 to use FAT32 
 *                      cards with full FATFS. This is intended for data 
 *                      logger applications and it uses about 42% of RAM and 
 *                      80% of flash. However you get access to a full file 
 *                      system as well as the ability to handle large 8GB, 16GB
 *                      or higher cards with no issues. Should be able to handle
 *                      up to 32GB cards with no issue. I recommend 4GB and 8GB 
 *                      cards as these are more than enough for data logging 
 *                      and storage for an 8-bit MCU!
 * 
 * Hardware Description: An SD card is connected to the PIC16 as follows: 
 * 
 *                       CS  -> RC2 (GPIO)
 *                       SCK -> RC3 (MSSP)
 *                       SDI -> RC4 (MSSP input)
 *                       SDO -> RC5 (MSSP output)
 *                       
 *                       We also have a CP2104 USB-UART connected to RB2 and 
 *                       RB3.
 *                       
 * Created December 26th 2025, 6:28 PM
 */

#include "PIC16F1718_Internal.h"
#include "SPI.h"
#include "EUSART.h"

#include "ff.h"        // Full FatFs
#include "diskio.h"    // FatFs disk I/O API

#include <string.h>

// FatFs objects
static FATFS fs;
static FIL fil;

// Helper to print FatFs errors
static void print_fr(FRESULT fr)
{
    // Minimal: just print numeric code
    char buf[32];
    // If you don't have sprintf, comment this and just print fixed text.
    // sprintf(buf, "FR=%u\r\n", (unsigned)fr);
    // EUSART_Write_Text(buf);

    // Simple fallback without sprintf:
    EUSART_Write_Text("FatFs error\r\n");
}

// Initmain
static void initMain(void)
{
    internal_32();
    __delay_ms(100);

    // EUSART pins (TX=RB2, RX=RB3)
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    TRISBbits.TRISB2 = 0; // TX output
    TRISBbits.TRISB3 = 1; // RX input

    // SPI pins for SD
    ANSELCbits.ANSC2 = 0;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;

    TRISCbits.TRISC2 = 0; // CS output
    TRISCbits.TRISC3 = 0; // SCK output
    TRISCbits.TRISC4 = 1; // SDI input
    TRISCbits.TRISC5 = 0; // SDO output

    LATCbits.LATC2 = 1;   // CS deasserted

    // PPS mapping (unlock -> map -> lock)
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;

    // EUSART
    RB2PPSbits.RB2PPS = 0x14; // RB2 -> EUSART:TX
    RXPPSbits.RXPPS   = 0x0B; // RB3 -> EUSART:RX

    // MSSP (SPI)
    SSPDATPPSbits.SSPDATPPS = 0x14; // RC4 -> MSSP:SDI
    RC3PPSbits.RC3PPS       = 0x10; // RC3 -> MSSP:SCK
    RC5PPSbits.RC5PPS       = 0x11; // RC5 -> MSSP:SDO

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;

    SPI_Initialize();
    EUSART_Initialize(19200);
}

// Initialize and write to a file
static void fatfs_write_create_overwrite(void)
{
    FRESULT fr;
    UINT bw;

    const char msg[] = "Hello from PIC16F1718 (Full FatFs)!\r\n";

    EUSART_Write_Text("f_open HELLO.TXT (CREATE_ALWAYS)...\r\n");

    // Creates a new file or overwrites existing file
    fr = f_open(&fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        EUSART_Write_Text("f_open FAIL\r\n");
        print_fr(fr);
        while (1);
    }

    EUSART_Write_Text("f_write...\r\n");
    fr = f_write(&fil, msg, (UINT)strlen(msg), &bw);
    if (fr != FR_OK || bw != (UINT)strlen(msg)) {
        EUSART_Write_Text("f_write FAIL\r\n");
        print_fr(fr);
        (void)f_close(&fil);
        while (1);
    }

    // Flush cached data + directory entry updates
    EUSART_Write_Text("f_sync...\r\n");
    fr = f_sync(&fil);
    if (fr != FR_OK) {
        EUSART_Write_Text("f_sync FAIL\r\n");
        print_fr(fr);
        (void)f_close(&fil);
        while (1);
    }

    EUSART_Write_Text("f_close...\r\n");
    fr = f_close(&fil);
    if (fr != FR_OK) {
        EUSART_Write_Text("f_close FAIL\r\n");
        print_fr(fr);
        while (1);
    }

    EUSART_Write_Text("Write OK\r\n");
}

// Main 
void main(void)
{
    FRESULT fr;

    initMain();
    __delay_ms(5000);

    EUSART_Write_Text("disk_initialize...\r\n");
    if (disk_initialize(0) & STA_NOINIT) {
        EUSART_Write_Text("disk init FAIL\r\n");
        while (1);
    }

    EUSART_Write_Text("f_mount...\r\n");
    fr = f_mount(&fs, "", 1);
    if (fr != FR_OK) {
        EUSART_Write_Text("mount FAIL\r\n");
        print_fr(fr);
        while (1);
    }

    EUSART_Write_Text("Mounted OK\r\n");

    fatfs_write_create_overwrite();

    while (1) {
        // idle
    }
}

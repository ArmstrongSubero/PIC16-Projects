/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 36_SD_Card_FAT32
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This program allows us to use the PIC16 to use 
 *                      SDHC cards FAT32 so larger cards like 8GB and 16GB 
 *                      should work. It is meant for minimal memory usage and 
 *                      FAT32 support. It is extremely limited as it uses 
 *                      petitfatfs under the hood and is better for reading. 
 *                      for writing create a file "LOG.TXT" fill it up with 
 *                      some bytes to make sure its not empty and the example 
 *                      here will work. The amount of bytes you fill with must 
 *                      be equal to the message you write. 
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
 * Created December 26th 2025, 5:35 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "SPI.h"
#include "EUSART.h"
#include "pff.h"
#include "diskio.h"
#include "pffconf.h"
#include <string.h>

FATFS fs;

/*******************************************************************************
 * Function: initMain
 * Description: Clock + PPS + GPIO setup for EUSART and SPI
 ******************************************************************************/
static void initMain(void)
{
    // Run at 32 MHz internal oscillator (matches your UART project style)
    internal_32();

    // Allow PLL/startup time
    __delay_ms(100);

    // -----------------------------
    // EUSART pins (TX=RB2, RX=RB3)
    // -----------------------------
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    TRISBbits.TRISB2 = 0; // TX output
    TRISBbits.TRISB3 = 1; // RX input

    // -----------------------------
    // SPI pins for SD
    // CS  = RC2 (GPIO)
    // SCK = RC3 (MSSP)
    // SDI = RC4 (MSSP input)
    // SDO = RC5 (MSSP output)
    // -----------------------------
    ANSELCbits.ANSC2 = 0;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;

    TRISCbits.TRISC2 = 0; // CS output
    TRISCbits.TRISC3 = 0; // SCK output (PPS)
    TRISCbits.TRISC4 = 1; // SDI input (PPS)
    TRISCbits.TRISC5 = 0; // SDO output (PPS)

    LATCbits.LATC2 = 1;   // CS deasserted (high)

    // -----------------------------
    // PPS mapping (unlock -> map -> lock)
    // -----------------------------
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

    // Initialize peripherals
    SPI_Initialize();
    EUSART_Initialize(19200);
}


static void write_test(void)
{
    UINT bw;
    FRESULT fr;

    const char msg[] = "Hello from PIC16F1718!\r\n";
    UINT total = 0;

    EUSART_Write_Text("pf_open LOG.TXT...\n");
    fr = pf_open("LOG.TXT");
    if (fr != FR_OK) { EUSART_Write_Text("pf_open FAIL\n"); while(1); }

    // Start at beginning
    fr = pf_lseek(0);
    if (fr != FR_OK) { EUSART_Write_Text("lseek FAIL\n"); while(1); }

    // Write message
    EUSART_Write_Text("pf_write msg...\n");
    fr = pf_write(msg, (UINT)strlen(msg), &bw);
    if (fr != FR_OK) { EUSART_Write_Text("pf_write FAIL\n"); while(1); }
    total += bw;

    // ---- overwrite the rest of the file with spaces ----
    // NOTE: fs is your global FATFS fs; and pff uses it internally.
    // Many pff ports keep size in fs.fsize after pf_open().
    // If your FATFS struct has fsize, this works.
    while (total < fs.fsize) {
        char pad[32];
        UINT chunk = (fs.fsize - total > sizeof(pad)) ? sizeof(pad) : (UINT)(fs.fsize - total);
        memset(pad, ' ', chunk);

        fr = pf_write(pad, chunk, &bw);
        if (fr != FR_OK) { EUSART_Write_Text("pad write FAIL\n"); while(1); }
        total += bw;

        if (bw == 0) break;
    }

    // Finalize write (REQUIRED)
    fr = pf_write(0, 0, &bw);
    if (fr != FR_OK) { EUSART_Write_Text("finalize FAIL\n"); while(1); }

    EUSART_Write_Text("Write OK\n");
}

/*******************************************************************************
 * Function: main
 ******************************************************************************/

void main(void)
{
    initMain();
    
    __delay_ms(5000);

    EUSART_Write_Text("disk_initialize...\n");
    if (disk_initialize() & STA_NOINIT) {
        EUSART_Write_Text("disk init FAIL\n");
        while(1);
    }

    EUSART_Write_Text("pf_mount...\n");
    if (pf_mount(&fs) != FR_OK) {
        EUSART_Write_Text("mount FAIL\n");
        while(1);
    }

    EUSART_Write_Text("Mounted OK\n");

    write_test();

    while(1);
}

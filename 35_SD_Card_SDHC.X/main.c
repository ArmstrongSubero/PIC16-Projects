/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 34_SD_Card
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This program allows us to use the PIC16 to write to 
 *                      SDHC cards. This library has a size limitation of 4GB 
 *                      giving double the capacity limit without compromising on
 *                      resources used. It is compatible with FAT16 so if on 
 *                      Windows format your card as FAT. If you're using a tool
 *                      like RUFUS or otherwise, be sure to use large clusters 
 *                      16 or 32 KB. 
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
 * Created December 26th 2025, 4:19 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "SPI.h"
#include "EUSART.h"
#include "sdcard.h"
#include "fatfs.h"

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

/*******************************************************************************
 * Function: main
 ******************************************************************************/
void main(void)
{
    initMain();
    
    __delay_ms(5000);

    EUSART_Write_Text("Booting SD+FAT demo...\n");

    // SD init 
    SDcard_init();

    // Mount and write a simple file
    mount_disk();
    file_create((const unsigned char*)"DATALOGS.TXT");

    sector_open();
    file_append((const unsigned char*)"Hello from PIC16F1718! HC Card!\n");
    file_append((const unsigned char*)"This is a test log line.\n");
    sector_close();

    file_update_size();

    EUSART_Write_Text("Done. Halting.\n");

    while (1)
    {
        // idle
    }
}

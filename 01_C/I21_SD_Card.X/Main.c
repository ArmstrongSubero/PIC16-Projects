/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: I21_SD_Card
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.1
 *                
 * Program Description: This Program Allows PIC16F1719 to interface with SD cards
 *                      and opens a file and writes some text
 * 
 * Hardware Description: An SD card module with SD card is connected as follows:
 *                       5v  ->  5v
 *                       GND ->  GND
 *                       CS  ->  RC0
 *                       MOSI -> RC5 (SDO)
 *                       SCK  -> RC3 (SCK)
 *                       MISO -> RC4 (SCI)
 *                       
 * Created April 24th, 2019, 1:39 AM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "ff.h"
#include "SPI.h"


// work area
FATFS FatFs;

// file object
FIL Fil;

// variable for pointer to number of bytes
UINT bw;

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/

void initMain(){
    // Run at 16 MHz
    internal_16();
    
    // Setup PORTC for SPI
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
    
    TRISDbits.TRISD0 = 0;
     
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    SSPDATPPSbits.SSPDATPPS = 0x14;   //RC4->MSSP:SDI;
    RC3PPSbits.RC3PPS = 0x10;         //RC3->MSSP:SCK;
    RC5PPSbits.RC5PPS = 0x11;         //RC5->MSSP:SDO;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    
    // Initialize SPI
    SPI_Initialize();
    
    
    // toggle LED on startup
    RD0 = 1;
    __delay_ms(100);
    RD0 = 0;
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();
    

    // mount SD
    if (f_mount(&FatFs, "", 1) == FR_OK) {
        
        // open or create file
		if (f_open(&Fil, "texty.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {	

            // go to the end of the file
			if ((Fil.fsize != 0) && (f_lseek(&Fil, Fil.fsize) != FR_OK))
            {
                goto endSD;	
            }

            // write data to file
			f_write(&Fil, "This is my message\r\n", 19, &bw);	
           
            // close the file
			endSD: f_close(&Fil);							
            
            // turn LED on on done writing
            RD0 = 1;
            __delay_ms(3000);
            RD0 = 0;
		}
	}
    
    
    else
    {
        int y;
        
        for (y = 0; y<= 3; y++)
        {
            RD0 = 1;
            __delay_ms(1000);
            RD0 = 0;
            __delay_ms(1000);
        }
    }
    
    
    while(1){
 
    }
    
    return;
    
}

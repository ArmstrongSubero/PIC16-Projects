/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 12_SPI
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.3
 *                  * Focused on PIC16F1718
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1718 to demonstrate use 
 *                      of the SPI bus 
 * 
 * Hardware Description: A MCP41010 Digipot is connected to the SPI bus as 
 *                       follows:-
 *                       Vss --> Vss
 *                       Vdd --> Vdd
 *                       SS  --> RC2
 *                       SCK --> RC3
 *                       SDI --> RC5
 *                       POB --> GND
 *                       POW --> LED via 1k resistor
 *                       POA --> Vdd
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Thursday 25th, December, 2025, 4:12 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "SPI.h"

void digiPot_write(uint8_t v);

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
    // Run at 32 MHz
    internal_16();
   
    // Allow PLL startup time ~2 ms
    __delay_ms(10);
    
    ////////////////////////
    // Setup SPI
    ///////////////////////
    
    ANSELCbits.ANSC2 = 0;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
    
    LATCbits.LATC2 = 1;
     
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    SSPDATPPSbits.SSPDATPPS = 0x14;   //RC4->MSSP:SDI;
    RC3PPSbits.RC3PPS = 0x10;   //RC3->MSSP:SCK;
    RC5PPSbits.RC5PPS = 0x11;   //RC5->MSSP:SDO;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    // Initialize SPI
    SPI_Initialize();
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
    
    // Digipot variable
    int i;
    
    
    while(1){
       
      for (uint16_t i = 0; i < 255; i++) {
    digiPot_write((uint8_t)i);
    __delay_ms(10);
      }
    }
    
    return;
    
}



/*******************************************************************************
 * Function: digipot_write
 *
 * Returns: Nothing
 *
 * Description: Writes a particular value to a MCP4131 digital potentiometer 
 * 
 * Usage: digiPot_write(x);
 ******************************************************************************/
void digiPot_write(uint8_t v)
{
    LATCbits.LATC2 = 0;
    SPI_Exchange8bit(0x11);
    SPI_Exchange8bit(v);
    LATCbits.LATC2 = 1;
}
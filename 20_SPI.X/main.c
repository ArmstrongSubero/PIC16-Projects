/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 20_SPI
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1719 to demonstrate use 
 *                      of the SPI bus 
 * 
 * Hardware Description: A MCP4131 Digipot is connected to the SPI bus as 
 *                       follows:-
 *                       Vss --> Vss
 *                       Vdd --> Vdd
 *                       SS  --> RD1
 *                       SCK --> RC3
 *                       SDI --> RC5
 *                       POB --> GND
 *                       POW --> LED via 1k resistor
 *                       POA --> Vdd
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: November 24th, 2023, 3:36 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"
#include "SPI.h"

void digiPot_write(int i);

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
    internal_32();
   
    // Allow PLL startup time ~2 ms
    __delay_ms(10);
    
    ////////////////////////
    // Setup SPI
    ///////////////////////
    
    // Set PIN D1 as SS
    TRISDbits.TRISD1 = 0;
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
     
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
       
      // Seven bit resolution
      for (i = 0; i <= 128; i++){  
          // Write Value
          digiPot_write(i);
          __delay_ms(100);
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

void digiPot_write(int i){
    // Set SS Low
    LATDbits.LATD1 = 0;
    
    // Slave address
    SPI_Exchange8bit(0x00);
    
    // Data
    SPI_Exchange8bit(i);
    
    // Set SS High
    LATDbits.LATD1 = 1;
}
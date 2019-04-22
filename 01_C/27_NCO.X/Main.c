/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 27_NCO
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.1
 *                
 *                
 * Program Description: This Program Allows PIC16F1719 to use the NCO to generate
 *                      a 500 Hz square wave
 *  
 * Hardware Description: An oscilloscope probe is connected to PIN A4
 *                      
 * Created November 4th, 2016, 1:00 PM
 * Updated April 22nd, 2019, 2:50 PM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.1         -Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
         
              -Program incorrectly had C0 as NCO output when it was supposed
               to be PINA4
              
*******************************************************************************/
/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"


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
    
    /////////////////
    // Set UP NCO
    ////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00; // unlock PPS
    
    RA4PPSbits.RA4PPS = 0x03; // NCO1 OUTPUT to PORTA4
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01;
    
    TRISAbits.TRISA4 = 0;
    ANSELAbits.ANSA4 = 0;
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
    
    // run NCO at 500 Hz
    NCO1INCH = 0;
    NCO1INCL = 65;
  
    // Enable NCO
    NCO1CONbits.N1EN = 1;
    
    // Operate in Fixed Duty cycle mode
    NCO1CONbits.N1PFM = 0;
    
    // Output signal active high
    NCO1CONbits.N1POL = 0;
    
    // Clock is 16 MHz System Oscillator
    NCO1CLKbits.N1CKS = 0b01;
    

    while(1){
       
    }
    
    return;
    
}

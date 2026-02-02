/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 23_NCO
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This generates a 1kHz NCO Signal on PA4
 * 
 * Hardware Description: An Oscilloscope probe is connected to pin PA4
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: December 25th, 2025, 9:53 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

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
    
    // PLL stabilization 
    __delay_ms(100);
    
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
    
    // run NCO at 1000 Hz
    NCO1INCH = 0;
    NCO1INCL = 65;
  
    // Enable NCO
    NCO1CONbits.N1EN = 1;
    
    // Operate in Fixed Duty cycle mode
    NCO1CONbits.N1PFM = 0;
    
    // Output signal active high
    NCO1CONbits.N1POL = 0;
    
    // Clock is 32 MHz System Oscillator (FOSC))
    NCO1CLKbits.N1CKS = 0b01;
    

    while(1){
       
    }
    
    return;
    
}

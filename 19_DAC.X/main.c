/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 19_DAC
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to demonstrate use of 
 *                      the 8-bit DAC module. 
 * 
 * Hardware Description: An Oscilloscope probe is connected to pin RA2
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 7:48 PM
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
    
    // PLL Stabilization 
    __delay_ms(100);
    
    //////////////////////
    // Configure DAC
    /////////////////////
    
    // DAC enabled
    DAC1CON0bits.DAC1EN = 1;
    
    // DACOUT pin enabled
    DAC1CON0bits.DAC1OE1 = 1;
    
    // +ve source is Vdd
    DAC1CON0bits.DAC1PSS = 0;
    
    // -ve source is Vss
    DAC1CON0bits.DAC1NSS = 0;
    
    // Initial output is 0v
    DAC1CON1bits.DAC1R = 0;
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
    
    while(1){
        DAC1CON1++;
    }
    
    return;
    
}

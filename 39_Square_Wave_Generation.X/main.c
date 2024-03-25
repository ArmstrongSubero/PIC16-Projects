/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 39_Square_Wave_Generation
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1719 DAC1 to generate a 
 *                      square waveform on PIN RA2
 * 
 * Hardware Description: An Oscilloscope probe is connected to pin RA2
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: March 25th, 2024, 3:03 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"

#define MAX_DAC_VALUE  255 // Max DAC value for PIC16F1719
#define MIN_DAC_VALUE  0   // Min DAC value


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
    __delay_ms(2);
    
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    LATDbits.LATD1 = 0;
    
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
 
    while(1)
    {
       DAC1CON1 = MAX_DAC_VALUE;
       __delay_ms(1); // High duration
       DAC1CON1 = MIN_DAC_VALUE;
       __delay_ms(1); // Low duration   
    }
    
    return; 
}

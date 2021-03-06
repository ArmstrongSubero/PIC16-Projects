/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 10_Periodic_Sleep
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to toggle an LED every
 *                      16 seconds and then go to sleep. The CPU is then awoken
 *                      by a WDT timeout.
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN D1
 *                      
 * Created November 4th, 2016, 9:13 PM
 */


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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    ////////////////////////////
    // Configure Watchdog timer
    ////////////////////////////
    // Set WDT period to 16s
    WDTCONbits.WDTPS = 0b01110;
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
        // flash LED
        LATDbits.LATD1 = 1;
        __delay_ms(1000);
        LATDbits.LATD1 = 0;
        
        // Sleep
        SLEEP();
    }
    
    return;
}

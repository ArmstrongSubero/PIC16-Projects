/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 09_Watchdog_Timer
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1719 to demonstrate use 
 *                      of the watchdog timer. The watchdog timer toggles the
 *                      LED every 16 seconds and then goes to sleep. The CPU
 *                      is then awoken by a WDT timeout
 *                      CLRWDT() macro can clear the watchdog timer. WDTE macro
 *                      is also set in PIC16F1718_Internal.h
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and 
 *                       a switch is connected to PIN C3
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 2:05 AM
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
    
    // Set PIN D1 as output
    TRISCbits.TRISC3 = 0;
    
    // Turn off LED
    LATCbits.LATC3 = 0;
    
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
        LATCbits.LATC3 = 1;
        __delay_ms(3000);
        LATCbits.LATC3 = 0;
        
        // Sleep
        SLEEP();
    }
    
    return;
}

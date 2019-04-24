/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: 00_Output
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.1
 *                
 * Program Description: This Program Allows PIC16F1719 to Turn on an LED
 * 
 * Hardware Description: An LED is connected via a 150R resistor to PIN D1
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: April 20th, 2019, 9:29 PM
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
        // Set PIND1 High
        LATDbits.LATD1 = 1;
    }
    
    return;
    
}

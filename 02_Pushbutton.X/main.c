/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 02_Pushbutton
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1719 to Turn on an LED
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN D1 and 
 *                       a switch connected to PIN D2
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 17th, 2023, 10:05 PM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"


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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    LATDbits.LATD1 = 0;
    
    // Set PIN D2 as input
    TRISDbits.TRISD2 = 1;  
    ANSELDbits.ANSD2 = 0;
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
        // Toggle LED on PUSH Button 
        LATDbits.LATD1 = ~PORTDbits.RD2;
    }
    
    return;
}
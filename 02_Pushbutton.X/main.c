/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 02_Pushbutton
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.3
 *                
 * Program Description: This Program Allows PIC16F1718 to Turn on an LED
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and 
 *                       a switch connected to PIN C4
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Wednesday 24th, December, 2025, 11:56 PM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.3         Updated for MPLAX v6.20 using XC8 v2.46 focus on PIC16F1718
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

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
    
    // Stabilize PLL 
    __delay_ms(100);
    
    // Set PIN C3 as output
    TRISCbits.TRISC3 = 0;
    LATCbits.LATC3 = 0;
    
    // Set PIN C4 as input
    // Disable Analog 
    TRISCbits.TRISC4 = 1;  
    ANSELCbits.ANSC4 = 0;
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
        LATCbits.LATC3 = ~PORTCbits.RC4;
    }
    
    return;
}

/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 03_Timer0
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to flash an LED at 1 Hz
 *                      on Timer0 overflow 
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 12:25 AM
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

//counter variable 
int count = 0;


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
    TRISCbits.TRISC3 = 0;
    LATCbits.LATC3 = 0;
 
    
    ///////////////////////
    /// Configure Timer0
    //////////////////////
    
    // Select timer mode
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 0;
    
    // Set Prescaler to 256
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    // Zero Timer
    TMR0 = 0;
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
        // When timer overflows TMR0 interrupt flag will be equal to 1
        while (INTCONbits.TMR0IF != 1);

        // Reset flag after overflow
        INTCONbits.TMR0IF = 0;

        // Increment count
        count++;

        // Value = fclk / (4 * 256 * 256 * fout)
        //                                   |-- Frequency out (in Hz)
        //                      |-- Prescaler value
        // Value =  32 000 000 / (262 144)
        // Value =  122.07 for 1 s


        // Turn on LED for 1 second on timer overflow
        if (count == 122){
            LATCbits.LATC3 = 1;
            count = 0;
        }

        // Else turn LED off
        else {
            LATCbits.LATC3 = 0;
        }     
    }
    
    return;
}

/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 04_Counter
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1719 to turn on an LED 
 *                      using Timer0 internal interrupt
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN D1 and 
 *                       a switch is connected to PIN B0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 18th, 2023, 1:06 AM
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
    //////////////////////
    // Configure Ports
    /////////////////////
    
    // Run at 16 MHz
    internal_32();
    
    // Set PIN D1, D2 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    ///////////////////////
    // Configure Timer0
    //////////////////////
    
    // Select timer mode
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 0;
    
    // Set Prescaler to 256
    OPTION_REGbits.PS = 0b111;
    
    // enable Timer0 interrupt
    INTCONbits.TMR0IE = 1;

    // enable global interrupts
    ei();  
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
        LATDbits.LATD1 = ~PORTBbits.RB0;
    }
    
    return;
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer0 interrupt at a rate of 1 second
 ******************************************************************************/
void __interrupt() isr(void)
{                               
    static int count = 0;
           
    // Reset flag after overflow
    INTCONbits.TMR0IF = 0;
    
    TMR0 = 0;
        
    // Increment count
    count++;
    
     // Value = fclk / (4 * 256 * 256 * fout)
     //                                   |-- Frequency out (in Hz)
     //                      |-- Prescaler value
     // Value =  32 000 000 / (262 144)
     // Value =  122.07 for 1 s
               
    // Turn on LED for 1 second on timer overflow
    if (count == 122){
        LATDbits.LATD1 = 1;
        count = 0;
    }
    
    // Else keep LED off
    else {
        LATDbits.LATD1 = 0;
    }
   
}
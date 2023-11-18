/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 04_Timer0
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to flash an LED at 1 Hz
 *                      on Timer0 overflow
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN D1
 *                      
 * Created November 4th, 2016, 4:14 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"

// Counter variable
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
    // Run at 16 MHz
    internal_16();
    
    ///////////////////////
    /// Configure Ports
    //////////////////////
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    
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
            // Value =  16 000 000 / (262 144)
            // Value =  61.04 for 1 s
           
            
            // Turn on LED for 1 second on timer overflow
            if (count == 61){
                LATDbits.LATD1 = 1;
                count = 0;
            }
            
            // Else turn LED off
            else {
                LATDbits.LATD1 = 0;
            }     
           
    }
    
    return;
}

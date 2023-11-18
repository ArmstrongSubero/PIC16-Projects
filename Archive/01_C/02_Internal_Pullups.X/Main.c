/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 02_Internal_Pullups
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to turn on an LED based
 *                      on a Pushbutton
 *                      
 * Hardware Description: An LED is connected via a 1k resistor to PIN D1 and a
 *                       switch is connected to PIN B0
 *                      
 * Created November 4th, 2016, 1:08 PM
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
    
    // Enable weak-pullups global
    OPTION_REGbits.nWPUEN = 0;
    
    // Enable weak-pullup on PINB0
    WPUBbits.WPUB0 = 1;
    
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
        //LATDbits.LATD1 = ~PORTBbits.RB0;
        
        // Check if switch pressed
        if (RB0 == 0)
        {
            // short delay
            __delay_ms(100);
            
            // if switch still pressed 
            if (RB0 == 0)
            {
                // turn led on
                LATDbits.LATD1 = 1;
            }
        }
        
        else{
            // keep LED off
            LATDbits.LATD1 = 0;
        }
    }
    
    return;
    
}

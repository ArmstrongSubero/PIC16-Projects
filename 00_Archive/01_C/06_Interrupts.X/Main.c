/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 06_Interrupts
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 flash an LED at a rate
 *                      of 1 Hz while responding to a pushbutton input using 
 *                      a timer0 interrupt
 *                      
 *                      
 * Hardware Description: An LED is connected via a 1k resistor to PIN D1 and 
 *                       another LED connected to PIN D2 switch is connected 
 *                       to PIN B0
 *                      
 * Created November 4th, 2016, 7:15 PM
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
    //////////////////////
    // Configure Ports
    /////////////////////
    
    // Run at 16 MHz
    internal_16();
    
    // Set PIN D1, D2 as output
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    
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

void interrupt isr(void)
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
     // Value =  16 000 000 / (262 144)
     // Value =  61.04 for 1 s
               
    // Turn on LED for 1 second on timer overflow
    if (count == 61){
        LATDbits.LATD2 = 1;
        count = 0;
    }
    
    // Else keep LED off
    else {
        LATDbits.LATD2 = 0;
    }
   
}

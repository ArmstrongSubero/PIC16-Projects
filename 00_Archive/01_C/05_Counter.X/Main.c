/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 05_Counter
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                r
 * Program Description: This Program Allows PIC16F1717 to turn on an LED after
 *                      the counter module on Time0 reaches a specified value
 *                      which is detected from external pulses given via a 
 *                      switch on RB0.
 *                      
 * Hardware Description: An LED is connected via a 1k resistor to pin RD1 and
 *                       a switch is connected to pin RB0
 *                      
 * Created February 23rd, 2017, 5:22 PM
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
    
    // Select counter mode
    OPTION_REGbits.TMR0CS = 1;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 1;

    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    T0CKIPPSbits.T0CKIPPS = 0x08;   //RB0->TMR0:T0CKI;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
    
    // Zero Timer
    TMR0 = 0;
    
    // Enable timer0 interrupts and clear interrupt flag
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0; 
}

/*******************************************************************************
 * Function: int ReadTimer(void)
 *
 * Returns: int readVal;
 *
 * Description: Returns the value of Timer0
 * 
 * Usage: int x;
 *        x = ReadTimer();
 ******************************************************************************/

uint8_t ReadTimer0(void)
{
    // Read value variable
    uint8_t readVal;

    // Set variable to timer0 value
    readVal = TMR0;

    // return value
    return readVal;
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
    
    // count variable
    uint8_t count;
   
    while(1){
        
        // read timer with count
        count = ReadTimer0();
        
        // if counter has value of 5
        if (count == 5){
            // turn LED on
            LATDbits.LATD1 = 1;
            
            // short delay to see LED on
            __delay_ms(2000);
            
            // zero timer
            TMR0 = 0;
        }
        
        else
        {
            // keep LED off
            LATDbits.LATD1 = 0;
        }
    }
    
    return;
}



/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 04_Timer0_Counter
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to turn on an LED 
 *                      using Timer0 counter
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and 
 *                       a pushbutton is connected to PIN B0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 12:32 AM
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
    
    // PLL Stabilization 
    __delay_ms(100);
    
    ///////////////////////
    /// Configure Ports
    //////////////////////
    
    // Set PIN C3 as output
    TRISCbits.TRISC3 = 0;
    
    // Turn off LED
    LATCbits.LATC3 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    //////////////////////
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
            LATCbits.LATC3 = 1;
            
            // short delay to see LED on
            __delay_ms(2000);
            
            // zero timer
            TMR0 = 0;
        }
        
        else
        {
            // keep LED off
            LATCbits.LATC3 = 0;
        }
    }
    
    return;
}
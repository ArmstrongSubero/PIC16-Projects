/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 09_Watchdog_Timer
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates using the watchdog timer on a 
 *                      PIC16F1717 to break out of an infinite loop
 *                     
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN D1 and 
 *                       another LED is connected to PIN D2 and a switch is 
 *                       connected to PIN B0
 *                      
 * Created November 4th, 2016, 9:04 PM
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
    
    ////////////////////////
    /// Configure Ports
    ////////////////////////
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    // unlock PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00;
    
    // Enable weak-pullups global
    OPTION_REGbits.nWPUEN = 0;
    
    // Enable weak-pullup on PINB0
    WPUBbits.WPUB0 = 1;
    
    /////////////////////////
    /// Configure Interrupts
    ////////////////////////
    
    // Set Interrupt pin to pin B0
    INTPPSbits.INTPPS = 0b01000;
    
    // lock   PPS 
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01; 
    
    // Trigger on falling edge
    OPTION_REGbits.INTEDG = 0;
    
    // Clear external interrupt flag
    INTCONbits.INTF = 0;
    
    //  Enable external interrupt
    INTCONbits.INTE = 1;
    
    // Enable global interrupt
    ei(); 
    
    //////////////////////////////////
    // Configure watchdog timer
    //////////////////////////////////
    
    // Set watchdog timeout for 2 seconds (prescale = 65536)
    WDTCONbits.WDTPS = 0b01011;
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
    
    int x;
    while(1){
       
       // If WDT timeout occurred turn on error LED
        if (!STATUSbits.nTO){
            LATDbits.LATD1 = 1;
        }
        
        // flash heartbeat LED
        LATDbits.LATD2 = 1;
        __delay_ms(1000);
        LATDbits.LATD2 = 0;

            
        for(;;){
            // infinite loop
        }
        
    }
    
    return;
    
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Interrupt triggered on pushbutton press
 ******************************************************************************/

void interrupt isr(void){
    // Clear interrupt flag
    INTCONbits.INTF = 0;
    
    // Toggle led
    LATDbits.LATD2 = ~LATDbits.LATD2;
}

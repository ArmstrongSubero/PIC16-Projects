/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 11_IOC
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to toggle an LED based
 *                      on the state of a IOC
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN D1 and 
 *                       a switch is connected to PIN B0
 *                      
 * Created November 6th, 2016, 9:35 PM
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
    
    /////////////////////////
    /// Configure Interrupts
    ////////////////////////
    
    // enable detection of falling edges on RB0
    IOCBNbits.IOCBN0 = 1;
    
    // enable IOC interrupt
    INTCONbits.IOCIE = 1;
    
    // Enable global interrupt
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
       ; // do nothing
    }
    
    return;
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Service port change interrupt which is triggered on any valid
 *              transition on IOC-enables input pin caused by external button 
 *              press. Toggles LED on every enabled transition (high -> low)
 ******************************************************************************/

void interrupt isr(void){
    
    // clear IOC flags on PORTB
    IOCBF = 0;
    
    // toggle LED
    LATDbits.LATD1 = ~LATDbits.LATD1;
}

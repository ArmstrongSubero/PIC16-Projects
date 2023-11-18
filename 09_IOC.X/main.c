/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 09_IOC
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1719 to toggle the LED based
 *                      on the state of the IOC
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN D1 and 
 *                       a switch is connected to PIN B0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 18th, 2023, 2:05 AM
 */


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
    // Run at 32 MHz
    internal_32();
    
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

void __interrupt() isr(void){
    
    // clear IOC flags on PORTB
    IOCBF = 0;
    
    // toggle LED
    LATDbits.LATD1 = ~LATDbits.LATD1;
}

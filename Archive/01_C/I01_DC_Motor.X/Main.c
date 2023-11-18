/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I01_DC_Motor
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates interfacing a DC motor to a PIC
 *                      microcontroller.
 *                      
 * Hardware Description: An NPN transistor is connected to PIN D0 which is then
 *                       connected to a OMR-C-105H motor.
 *                      
 * Created November 4th, 2016, 8:43 PM
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
    
    
    ////////////////////
    // Configure Ports
    ///////////////////
    
    // Make D0 Output
    TRISDbits.TRISD0 = 0;
    
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
    
   // Turn motor on for 5 seconds
    while(1){
        LATD0 = !LATD0;
        __delay_ms(5000);
    }
    
    return;
    
}


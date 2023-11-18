/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I06_Stepper_Motor
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates using a unipolar stepper motor with a 
 *                      pic microcontroller.
 *                      
 * Hardware Description: A Sinotech 25BY4801 4 phase unipolar stepper motor
 *                       is connected to PORT D of the microcontroller with a
 *                       ULN2003A darlington transistor array used as a driver
 *                       for the stepper motor.
 * 
 *                       Connections are as follows:
 * 
 *                       The ULN2003A is connected to the microcontroller as 
 *                       shown below:
 *                          
 *                       IN1 --> RD0
 *                       IN2 --> RD1
 *                       IN3 --> RD2
 *                       IN4 --> RD3
 * 
 *                       The Stepper motor is connected to the ULN2003A as
 *                       follows:
 * 
 *                       White = OUT1
 *                       Black = OUT2
 *                       Red = OUT3
 *                       Yellow = OUT4
 *                      
 * Created January 15th, 2017, 12:05 AM
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
    TRISD = 0;
    
    // Turn off analog
    ANSELD = 0;
    
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
        LATD = 0b00001001; // Step 1
        __delay_ms(500);
        LATD = 0b00000101; // Step 2
        __delay_ms(500);
        LATD = 0b00000110; // Step 3
        __delay_ms(500);
        LATD = 0b00001010; // Step 4
        __delay_ms(500);
    }
     return;    
}


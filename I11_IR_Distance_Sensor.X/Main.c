/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I11_IR_Distance_Sensor
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                           
 * Program Description: This demonstrates using a Infrared distance sensor with
 *                      a PIC microcontroller.
 *                      
 * Hardware Description: A IR distance sensor is connected to a PORT RD0 and
 *                       and LED to RD1. The LED lights up when the infrared
 *                       distance sensor detects object at desired distance.
 *                       
 *                      
 * Created January 15th, 2017, 12:15 PM
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
    
    // Set PIN D0 as input
    TRISDbits.TRISD0 = 1;
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
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
        if (PORTDbits.RD0 == 1){
            RD1 = 0;
        }
        
        else{
            RD1 = 1;
        }

    }
     return;    
}


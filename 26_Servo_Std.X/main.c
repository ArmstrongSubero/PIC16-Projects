/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: 26_Servo_Std
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This controls a servo to rotate to 0, 90 and 180 
 *                      degree positions
 * 
 * Hardware Description: An standard servo is connected to PIND0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 26th, 2023, 4:48 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "Servo.h"


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
    
   // Rotate servo 0 - 90 - 180
    while(1){
       
        servoRotate0();
        servoRotate90();
        servoRotate180();
    
    return;
    }  
}


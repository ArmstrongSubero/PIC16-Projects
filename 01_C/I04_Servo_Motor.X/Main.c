/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I04_Servo_Motor
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates using a servo on a pic microcontroller
 *                      
 * Hardware Description: A MG90s microservo is connected to PIN RD0 
 
 *                      
 * Created January 14th, 2017, 10:30 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
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


/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 31_Motor_On_Off
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This program allows for control of a DC motor. The 
 *                      motor is turned on for 1 second and then off for 
 *                      one second. 
 * 
 * Hardware Description: The 2N2222A transistor is used to drive an IRF540 
 *                       MOSFET that is then used to control a 131:1 gear 
 *                       motor rated for a 5A stall current. The base of the 
 *                       2N2222A is connected to pin RD1
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: January 01st, 2024, 6:57 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"


// Function to control the motor
/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Function to control the motor
 * 
 * Usage: controlMotor(1)
 ******************************************************************************/
void controlMotor(uint8_t state) 
{
    // Assuming RD1 is connected to the base of the transistor
    LATD1 = state;
}

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/

void initMain()
{
    // Run at 16 MHz
    internal_16();
    
    ////////////////////
    // Configure Ports
    ///////////////////
    TRISDbits.TRISD1 = 0;
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) 
{
    initMain();

    while(1)
    {
        // Turn the motor on
        controlMotor(1);
        
        // Delay for 1 second
        __delay_ms(1000);  

        // Turn the motor off
        controlMotor(0);
        
        // Delay for 1 second
        __delay_ms(1000);  
    }
     return;    
}
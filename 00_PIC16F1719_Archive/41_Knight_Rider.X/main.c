/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 30_Countdown_Timer
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Cleaned up code
 *                  * Added additional comments
 *                  * Upgraded from PIC16F1717 to PIC16F1719
 *                
 * Program Description: This Program allows the PIC16F1719 to use multiplexed
 *                      seven segment displays to make a countdown timer
 *                      when RC1 is pressed the count increments, when RC2 is
 *                      pressed the count decrements, pressing C0 starts the 
 *                      decrement. When the decrement is finished, pressing 
 *                      C0 again will reset the flag allowing the process to
 *                      be repeated.
 * 
 * Hardware Description: Two seven segment displays are connected to PORTD and
 *                       three pushbuttons are connected to C0, C1 and C2
 *
 *                      
 * Created April 1st, 2017, 12:26 PM
 * Updated December 5th, 2023, 8:44 AM
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
    // Run at 16 MHz
    internal_16();
    
    TRISD = 0;
    PORTD = 0;
}


/*******************************************************************************
 * Function: Main
 *nsigned char direction = 0; // 0 for moving right, 1 for moving left
    
    while (1) {
        PORTD = J;

        if (direction == 0) {
            J = J << 1;
            if (J == 0b10000000) { // If the LED reaches the end on the right
                direction = 1; // Change direction to left
                J = J >> 1;    // Move back one step to the left
            }
        } else {
            J = J >> 1;
            if (J == 0b00000001) { // If the LED reaches the end on the left
                direction = 0; // Change direction to right
                J = J << 1;    // Move back one step to the right
            }
        }

        __delay_ms(200);
    }

    return;
}
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();

    unsigned char J = 1;
    unsigned char direction = 0; // 0 for moving right, 1 for moving left
    
    while (1) {
        PORTD = J;

        if (direction == 0) {
            J = J << 1;
            if (J == 0) { // If the LED reaches the end on the right
                direction = 1; // Change direction to left
                J = 1 << (7 - 1); // Move back to the second last LED
            }
        } else {
            J = J >> 1;
            if (J == 0) { // If the LED reaches the end on the left
                direction = 0; // Change direction to right
                J = 1; // Move back to the first LED
            }
        }

        __delay_ms(100);
    }

    return;
}

/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I02_Seven_Segment
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC16F1717 to drive a single 
 *                      seven segment display, it displays the hexadecimal 
 *                      digits 0-F on the seven segment display. 
 * 
 * Hardware Description: An seven segment display of the cathode variety is 
 *                       connected to port D of the microcontroller.
 *                      
 * Created February 16th, 2017, 6:31 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"

unsigned char Display(unsigned char digit);


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
    
    // Set PIN D1 as output
    TRISD = 0;
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
    
    // loop variable
    int i;
    
    initMain();
    
    // Keep displaying digits 0-F 
    // and update it ever second
    while(1){
        for (i = 0; i <= 15; i++){
            LATD = Display(i);
             __delay_ms(1000);
        }
       
    }
    
    return;
    
}

/*******************************************************************************
 * Function: unsigned char Display(unsigned char digit)
 *
 * Returns: unsigned char numbers
 *
 * Description: Function that takes a number and returns its index in an array
 *              corresponding to the hexadecimal digit
 ******************************************************************************/

unsigned char Display(unsigned char digit)
{
    // variable representing numbers
    unsigned char numbers;
    
    // an array of the digits 0-F 
    unsigned char DIGITS[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                              0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    
    // assign index given by user to variable
    numbers = DIGITS[digit];
    
    // return it
    return numbers;
}


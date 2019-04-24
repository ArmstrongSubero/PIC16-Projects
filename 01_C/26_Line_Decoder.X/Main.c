/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: 26_Line_Decoder
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC16F179 to used a 3-8 line decoder
 *                      IC being the 74HC138
 * 
 * Hardware Description: A 74HC138 3-8 line decoder demultiplexer is connected 
 *                       as follows:
 *                       
 *                       Vcc     -> Vcc
 *                       Gnd     -> Gnd
 *                       Y0 - Y7 -> LEDs with 1k resistor
 *                       A0      -> RD0
 *                       A1      -> RD1
 *                       A2      -> RD2
 *                       !E1     -> GND
 *                       !E2     -> GND
 *                       E3      -> Vcc
 *                      
 * Created April 23rd, 2019, 11:08 PM
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
    
    // Set PORTD as output
    TRISD = 0;
    PORTD = 0;
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
    
    // set initial count to 0
    int count = 0x00;
    
    while(1){
        
        // set port D to count
        PORTD = count;
        
        // increment count
        count++;
        
        // delay a little
        __delay_ms(250);
        
        // if reached > 7 begin again
        if (count > 0x07)
        {
            count = 0x00;
        }
    }
    
    return;
    
}

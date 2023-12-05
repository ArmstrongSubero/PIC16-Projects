/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 28_Seven_Segment
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Cleaned up code
 *                  * Added additional comments
 *                  * Upgraded from PIC16F1717 to PIC16F1719
 *                
 * Program Description: This Program allows the PIC16F1719 to use a seven
 *                      segment display
 * 
 * Hardware Description: A seven segment display is connected to PORTD
 *
 *                      
 * Created April 1st, 2017, 12:26 PM
 * Updated December 5th, 2023, 6:45 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"

// main loop variables 
uint16_t digit, digitCount;
uint16_t i = 0;

/*******************************************************************************
 * Function: uint16_t seg(unsigned int num)
 *
 * Returns: Activation of Segments as Hex
 *
 * Description: Returns seven segment activations for each digit
 * 
 * Usage: x = seg(digit)
 ******************************************************************************/
uint16_t seg(unsigned int num)
{
   switch(num)
   {
    case 0 : return 0x3F;
    case 1 : return 0x06;
    case 2 : return 0x5B;
    case 3 : return 0x4F;
    case 4 : return 0x66;
    case 5 : return 0x6D;
    case 6 : return 0x7D;
    case 7 : return 0x07;
    case 8 : return 0x7F;
    case 9 : return 0x6F;
   }
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

void initMain(){
    // Run at 16 MHz
    internal_16();
    
    // Set PORTD to output
    TRISD = 0;
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
      
    while(1)
    {   
      i++;
      
      if (i > 9999)
      {
         i = 0;
      }
      
      // extract and display thousands digit from i
      digit = (i / 1000) % 10;
      digitCount = seg(digit);
      PORTD = digitCount;
    
      __delay_ms(2);
    
    }
    
    return;   
}




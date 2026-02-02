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


#define SEG0 LATBbits.LATB0
#define SEG1 LATBbits.LATB1

// main loop variables 
uint16_t digit, digitCount0, digitCount1;
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
    LATD = 0;
    
    // Configure multiplexing on PORTB
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    PORTB = 0;
    
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC2 = 1;
    
    ANSELCbits.ANSC2 = 0;
    
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
    
    
    uint8_t c0_pressed = 0; // Flag to track if C0 button is pressed
    
 
    while(1)
    { 
        // Check if C0 button is pressed to toggle the flag for decrement
        if (PORTCbits.RC0 == 0) {
            // Toggle the flag to indicate C0 is pressed
            c0_pressed = !c0_pressed;
            
            // Add a small delay or debounce logic if needed to avoid multiple detections
            __delay_ms(50); // Adjust delay as required for debounce
        }
        
        // If C0 is pressed, decrement the value
        if (c0_pressed == 1) {
            if (i > 0) {
                i--;
            }
        }
       
        
        // Check if C1 button is pressed to increment the value
        if (PORTCbits.RC1 == 0) {
            i++;
        }
        
        // Check if C2 button is pressed to decrement the value
        if (PORTCbits.RC2 == 0) {
            if (i > 0) {
                i--;
            }
        }
        
      if (i > 9999)
      {
         i = 0;
      }
      
      // Take hundreds digit      
      digit = (i / 100) % 10;
      digitCount0 = seg(digit);
      SEG0 = 0;
      SEG1 = 1;
      LATD = digitCount0;
      __delay_ms(5);
      
      
      // Ensure both displays are off before switching
      LATD = 0x00; // Turn off both displays
      __delay_ms(1); // Short delay between switching
      
      // Take Thousands digit
      SEG0 = 1;
      SEG1 = 0;
      digit = (i / 1000) % 10;
      digitCount1 = seg(digit);
      LATD = digitCount1;
    
      __delay_ms(5);
      
      // Ensure both displays are off before switching
      LATD = 0x00; // Turn off both displays
      __delay_ms(1); // Short delay between switching
        
    }
        
    return;   
}




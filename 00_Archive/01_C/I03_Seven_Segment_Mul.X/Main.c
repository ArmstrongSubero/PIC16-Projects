/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I03_Seven_Segment_Mul
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC16F1717 to countdown from a 
 *                      time of up to 99 seconds which is determined by the
 *                      user.
 * 
 * Hardware Description: Dual seven segment displays of the cathode variety is 
 *                       connected to port D of the microcontroller via 1k
 *                       resistors. There are two transistors connected in 
 *                       common emitter configuration on pins RB0 and RB1 
 *                       respectively. There are also two pushbuttons connected
 *                       to pins RC4 and RC5 used for decrementing and 
 *                       incrementing. There is also a button connected to 
 *                       RC6 used to begin the countdown.
 *                      
 * Created February 16th, 2017, 11:16 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"

unsigned char display(unsigned char digit);
void countDown(unsigned char number);
void showNumber(unsigned char number);

// display port
#define DISPLAYPORT LATD

// digit one enable
#define DIGITONE LATB0

// digit two enable
#define DIGITTWO LATB1


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
    // Analog disabled
    TRISD = 0;
    ANSELD = 0;
    
    // Set PORTB as output
    // Analog disabled
    TRISB = 0;
    ANSELB = 0;
    
    // Set RC4, RC5 and RC6 as input
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    TRISCbits.TRISC6 = 1;
    
    // Turn of analog on C
    ANSELC = 0;
    
    // Enable weak-pullups global
    OPTION_REGbits.nWPUEN = 0;
    
    // Enable weak-pullup on RC4, RC5 and RC6
    WPUCbits.WPUC4 = 1;
    WPUCbits.WPUC5 = 1;
    WPUCbits.WPUC6 = 1;
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    
    // count variable
    unsigned char count = 0;
    
    initMain();
    
  
    while(1){
        
        // If RC4 pressed increment count
        if(RC4 == 0){
            __delay_ms(100);
            
            if (RC4 == 0){
              count++;
            }
        }
        
        // If RC5 pressed decrement count
        if (RC5 == 0)
        {
            __delay_ms(100);
            
            if(RC5 == 0){
                count--;
            }
        }
        
        
        // If RC6 pressed begin countdown
        if (RC6 == 0)
        {
            __delay_ms(100);
            
            if (RC6 == 0){
                countDown(count);
            }
        }
        
        
        // If value invalid set to 0
        if (count > 99 || count < 0){
            count = 0;
        } 
       
        // show number on display
        showNumber(count);
       
        __delay_ms(1);
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

unsigned char display(unsigned char digit)
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


/*******************************************************************************
 * Function: void countdown(unsigned char number)
 *
 * Returns: nothing
 *
 * Description: Begins a countdown based on number passed to function
 ******************************************************************************/

void countDown(unsigned char number)
{
    // loop counter
    int i;
    
    // begin countdown
    for (i = number; i >= 0; i--)
    {
        showNumber(i);
        __delay_ms(1000);
    }
    
    return;
  
}


/*******************************************************************************
 * Function: void shownumber(unsigned char number)
 *
 * Returns: nothing
 *
 * Description: Displays a number on the port specified
 ******************************************************************************/

void showNumber(unsigned char number)
{
    // most significant digit
    unsigned char MSD;
    
    // least significant digit
    unsigned char LSD;
    
    // Get MSD and LSD
    MSD = number/10;
    LSD = number%10;
            
    // Display MSD
    DISPLAYPORT = display(MSD);
    DIGITTWO = 1;
    __delay_ms(20);
    DIGITTWO = 0;
            
    // Display LSD
    DISPLAYPORT = display(LSD);
    DIGITONE = 1;
    __delay_ms(20);
    DIGITONE = 0; 
     
}


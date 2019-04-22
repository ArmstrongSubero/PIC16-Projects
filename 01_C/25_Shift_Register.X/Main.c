/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: 25_Shift_Register
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.1
 *                
 * Program Description: This Program Allows PIC16F1719 to use a shift register
 *                      for LED chasing
 * 
 * Hardware Description: A SN74HC595N shift register is connected as follows:
 *                       Vcc     -> Vcc
 *                       Gnd     -> Gnd
 *                       QA - QH -> 1k Resistors with LEDs
 *                       SER     -> SER_595   (D0)
 *                       !OE     -> Gnd
 *                       RCLK    -> RCLK_595  (D1)
 *                       SRCLK   -> SRCLK_595 (D2)
 *                       SRCLR   -> Vcc
 *                      
 * Created April 22nd, 2019, 1:36 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "HC595.h"


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
    
    // Configure outputs
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 0;
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
  
    // initial value
    int count = 0b00000001;
    
    while(1){
        
        // submit value
        write_595(count);
        
        // shift by one bit
        count = count << 1;
        
        // repeat cycle through
        if (count > 0b10000000)
        {
            count = 0b00000001;
        }
        
        __delay_ms(200);
    }
    
    return;
}

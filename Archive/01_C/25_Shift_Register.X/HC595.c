/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: Library file for SN74HC595N
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
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
 * Includes and defines
 ******************************************************************************/
#include "HC595.h"


/*******************************************************************************
* Function: void clockPulse(void)
*
* Returns: Nothing
*
* Description: Provides a pulse on clock pin
*
*******************************************************************************/
void clockPulse(void){
    SRCLK_595 = 1;
    __delay_us(500);
    SRCLK_595 = 0;
    __delay_us(500);
}


/*******************************************************************************
* Function: void latchPulse(void)
*
* Returns: Nothing
*
* Description: Provides a pulse on latch pin
*
*******************************************************************************/
void latchPulse(void){
    RCLK_595 = 1;
    __delay_us(500);
    RCLK_595 = 0;
} 


/*******************************************************************************
* Function: void write_595(void)
*
* Returns: Nothing
*
* Description: Writes data to the SN74HC595N
*
*******************************************************************************/
void write_595(unsigned int data){
    for (int i=0 ; i<8 ; i++){
        SER_595 = (data >> i) & 0x01;
        clockPulse();
    }
    latchPulse(); // Latch data
}

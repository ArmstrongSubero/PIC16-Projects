/*
 * File: HC595.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file for 74HC595
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version 1.0
 *                  
 * Program Description: This program header will provides function prototypes
 *                      and includes for the 74HC595N shift register with the
 *                      PIC microcontroller.
 *
 * Created on April 22nd, 2019, 1:36 PM
 */

#include "16F1717_Internal.h"


#define SER_595 PORTDbits.RD0
#define RCLK_595 PORTDbits.RD1
#define SRCLK_595 PORTDbits.RD2

void clockPulse(void);
void latchPulse(void);
void write_595(unsigned int data);
/*
 * File: sound.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 alarm
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version 1.0
 *           
 * Program Description: This program header allows PIC to sound a simple alarm
 *
 * Created on April 15th, 2017, 12:20 PM
 */


#include "16F1717_Internal.h"


/*******************************************************************************
 * Function: void play_alarm()
 *
 * Returns: Nothing
 *
 * Description: Plays alarm on PIN B2
 * 
 ******************************************************************************/

void play_alarm()
{
    int i;
    
    for (i=0; i<10; i++) {     //play x notes inside song array
    
        PORTBbits.RB2 = 0;
        __delay_us(1200);
        PORTBbits.RB2 = 1;
        __delay_us(1200);
    }
}
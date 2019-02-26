/*
 * File: 16F1717_STD.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.35, MPLAX X v3.10)
 * Program Version: 1.2
 *                *Added additional comments
 *                
 * Program Description: This Library allows you to setup a PIC16F1717
 *                      
 * Created on January 9th, 2016, 6:45 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "16F1717_Internal.h"


/*******************************************************************************
 * Function: internal_32()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 32MHz
 * 
 * Usage: internal_32()
 ******************************************************************************/
//Set to 32MHz
void internal_32(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 0;
    IRCF1 = 1;
    IRCF2 = 1;
    IRCF3 = 1;

    //SET PLLx4 ON
    SPLLEN = 1;
}

/*******************************************************************************
 * Function: internal_16()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 16MHz
 * 
 * Usage: internal_16()
 ******************************************************************************/
//Set to 16MHz
void internal_16(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 1;
    IRCF1 = 1;
    IRCF2 = 1;
    IRCF3 = 1;

    //SET PLLx4 OFF
    SPLLEN = 0;
}

/*******************************************************************************
 * Function: internal_8()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 8MHz
 * 
 * Usage: internal_8()
 ******************************************************************************/
//Set to 8MHz
void internal_8(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 0;
    IRCF1 = 1;
    IRCF2 = 1;
    IRCF3 = 1;

    //SET PLLx4 OFF
    SPLLEN = 0;
}

/*******************************************************************************
 * Function: internal_4()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 4MHz
 * 
 * Usage: internal_4()
 ******************************************************************************/
//Set to 4MHz
void internal_4(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 1;
    IRCF1 = 0;
    IRCF2 = 1;
    IRCF3 = 1;

    //SET PLLx4 OFF
    SPLLEN = 0;
}

/*******************************************************************************
 * Function: internal_2()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 2MHz
 * 
 * Usage: internal_2()
 ******************************************************************************/
//Set to 2MHz
void internal_2(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 0;
    IRCF1 = 0;
    IRCF2 = 1;
    IRCF3 = 1;

    //SET PLLx4 OFF
    SPLLEN = 0;
}

/*******************************************************************************
 * Function: internal_1()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 1MHz
 * 
 * Usage: internal_1()
 ******************************************************************************/
//Set to 1MHz
void internal_1(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 1;
    IRCF1 = 1;
    IRCF2 = 0;
    IRCF3 = 1;

    //SET PLLx4 OFF
    SPLLEN = 0;
}

/*******************************************************************************
 * Function: internal_31()
 *
 * Returns: Nothing
 *
 * Description: Sets internal oscillator to 31kHz
 * 
 * Usage: internal_31()
 ******************************************************************************/
//Set to 31kHz(LFINTOSC)
void internal_31(){
    //Clock determined by FOSC in configuration bits
    SCS0 = 0;
    SCS1 = 0;

    //Frequency select bits
    IRCF0 = 0;
    IRCF1 = 0;
    IRCF2 = 0;
    IRCF3 = 0;

    //SET PLLx4 OFF
    SPLLEN = 0;
}




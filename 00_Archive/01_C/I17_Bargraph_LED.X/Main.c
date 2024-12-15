/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I17_Bargraph_LED
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to use a bargraph LED
 * 
 * Hardware Description: A bargraph LED is connected to PORTD and PORTC bits 
 *                       C2 and C3. 
 *                      
 * Created April 18th, 2017, 5:20 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"

void bargraph_percent(int percent);


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
    
    // Set PORTD as Output
    TRISD = 0;
    
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
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
    
    while(1){
        
        // Convert percentage on value to be displayed on bargraph
        for (int x = 0; x <= 100; x+=10){
            bargraph_percent(x);
            __delay_ms(500);
        }
    }
    
    return;
    
}


/*******************************************************************************
 * Function: void bargraph_percent(int percent)
 *
 * Returns: Nothing
 *
 * Description: Converts a percentage to a particular value on the bargraph
 * 
 * Usage: bargraph_percent(int percent)
 ******************************************************************************/

void bargraph_percent(int percent)
{
    switch (percent){
        case 10:
            LATD = 0x01;
            break;
        case 20:
            LATD = 0x03;
            break;
        case 30:
            LATD = 0x07;
            break;
        case 40:
            LATD = 0x0F;
            break;
        case 50:
            LATD = 0x1F;
            break;
        case 60:
            LATD = 0x3F;
            break;
        case 70:
            LATD = 0x7F;
            break;
        case 80:
            LATD = 0xFF;
            break;
        case 90:
            LATD = 0xFF;
            LATCbits.LATC2 = 1;
            break;
        case 100:
            LATD = 0xFF;
            LATCbits.LATC3 = 1;
            break;
        default:
            LATD = 0x00;
            LATCbits.LATC2 = 0;
            LATCbits.LATC3 = 0;
    }
    
}
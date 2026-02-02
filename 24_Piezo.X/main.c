/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 24_Piezo
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This program demonstrates use of the Piezo Buzzer 
 *                      sound library
 * 
 * Hardware Description: A piezo buzzer is connected to PIN B0
 *                       
 * Created December 26th, 2025, 10:10 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "buzzer.h"

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
    
   // Run at 32 MHz
   internal_32();  
   
   // PLL Stabilization 
   __delay_ms(100);
   
   // Call buzzer library 
   Buzzer_Init();
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/
void main(void) 
{
    // Demo
    Buzzer_Success();
    __delay_ms(400);
    
    Buzzer_SweepUp(1000, 6000, 1200);
    __delay_ms(200);
    
    Buzzer_Siren(1500, 3000, 3000);
    
    while(1) {
        Buzzer_Countdown(8000);
        Buzzer_Warning();
        __delay_ms(800);
    }
}
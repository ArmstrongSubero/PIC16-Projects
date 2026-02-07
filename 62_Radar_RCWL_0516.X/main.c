/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 62_Radar_RCWL_0516
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to interface to an 
 *                      RCWL-0516 microwave Doppler radar motion sensor. The 
 *                      sensor is a binary motion detection device sensing 
 *                      motion or no motion. 
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and the
 *                       RCWL-0516 is connected to pin A0. 
 *                       
 * Created February 7th, 2026, 4:09 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"


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
    internal_32();
    __delay_ms(100);
    
    // Set PIN C3 as output (LED)
    TRISCbits.TRISC3 = 0;
    
    // Set PIN A0 as digital input (RCWL-0516 OUT)
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 0;  // Digital, not analog
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
        if (PORTAbits.RA0) {
            LATCbits.LATC3 = 1;  // Motion detected then LED on
        } else {
            LATCbits.LATC3 = 0;  // No motion then LED off
        }
        __delay_ms(100);
    }
    
    return;
}

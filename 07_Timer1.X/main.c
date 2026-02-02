/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 07_Timer1
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program toggles an LED using Timer1
 * 
 * Hardware Description: An LED is connected via a 1k resistor to RC3
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 1:50 AM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.3         Updated for MPLABX v6.20 and XC8 v2.46 target PIC16F1718
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

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
    // Run at 32 MHz
    internal_32();
    
    // Set PIN D1 as output
    TRISCbits.TRISC3 = 0;
  
    // Turn off LED
    LATCbits.LATC3 = 0;
    
    // prescale = 1
    T1CONbits.T1CKPS = 0b00;
    
    // Set TMR1 to 0
    TMR1 = 0;
    
    // enable timer1
    T1CONbits.TMR1ON = 1;
    
    // enable timer1 interrupt
    PIE1bits.TMR1IE = 1;
    
    // enable peripheral interrupt
    INTCONbits.PEIE = 1;
    
    // enable global interrupts
    ei();
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
        
    }
    
    return;   
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer1 interrupt
 ******************************************************************************/

void __interrupt() isr(void){
    static uint8_t count = 0;
    
    PIR1bits.TMR1IF = 0;
    
    count++;
    
    // Blink every second
    if (count == 122){
        count = 0;
        LATCbits.LATC3 = 1;
    }
    
    else {
        LATCbits.LATC3 = 0;
    }
}

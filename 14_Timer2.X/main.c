/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 14_Timer2
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program toggles an LED using Timer2
 * 
 * Hardware Description: An LED is connected via a 1k resistor to RD1
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 18th, 2023, 3:12 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"

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
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    /////////////////////
    // Configure Timer2
    /////////////////////
    
    /*                                     fclk
     *  count =       -------------------------------------------------
     *                4 * prescaler * (PR2-TMR2) * postscaler * freqout
     * 
     * 
     * count = 32 000 000 / 4 * 16  * (256) * 15 * 1
     * 
     * count = ~122
     *
     */
    
    
    // prescale = 16 
    T2CONbits.T2CKPS = 0b10;
    
    // Set period to 255
    PR2 = 255;
    
    // Set TMR2 to 0
    TMR2 = 0;
    
    // postscale = 15 
    T2CONbits.T2OUTPS = 0b1110;
    
    // enable timer2
    T2CONbits.TMR2ON = 1;
    
    // enable timer2 interrupt
    PIE1bits.TMR2IE = 1;
    
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
 * Description: Timer2 interrupt at a rate of 1 second
 ******************************************************************************/

void __interrupt() isr(void){
    static uint8_t count = 0;
    
    PIR1bits.TMR2IF = 0;
    
    count++;
    
    // Blink every second
    if (count == 122){
        count = 0;
        LATDbits.LATD1 = 1;
    }
    
    else {
        LATDbits.LATD1 = 0;
    }
}

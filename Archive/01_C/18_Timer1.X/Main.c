/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 18_Timer1
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program uses Timer1 to blink an LED
 *                     
 * A LED is connected to PIND1                  
 *                      
 * Created April 21st, 2019, 9:53 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"



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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
   
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

void interrupt isr(void){
    static uint8_t count = 0;
    
    PIR1bits.TMR1IF = 0;
    
    count++;
    
    // Blink every second
    if (count == 65){
        count = 0;
        LATDbits.LATD1 = 1;
    }
    
    else {
        LATDbits.LATD1 = 0;
    }
}

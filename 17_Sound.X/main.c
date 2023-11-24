/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 12_DAC
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1717 DAC1 to generate a 
 *                      waveform on PIN RA2
 * 
 * Hardware Description: An Oscilloscope probe is connected to pin RA2
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 18th, 2023, 2:51 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"


unsigned char sineData[] = {
  127, 129, 131, 133, 135, 137, 139, 142, 144, 146, 148, 151, 153, 155, 157, 159, 
  160, 162, 163, 165, 166, 168, 169, 171, 172, 174, 175, 176, 177, 178, 179, 180, 
  181, 182, 183, 184, 185, 186, 187, 188, 189, 189, 190, 190, 189, 189, 188, 187, 
  186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 172, 171, 169, 
  168, 166, 165, 163, 162, 160, 159, 157, 155, 153, 151, 148, 146, 144, 142, 139,
  137, 135, 133, 131, 129, 127, 125, 123, 121, 119, 117, 115, 113, 111, 110, 108, 
  106, 104, 102, 100, 99, 97, 95, 93, 91, 90, 88, 86, 84, 82, 80, 78, 77, 
  75, 73, 71, 69, 67, 65, 63, 61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41
};


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
    TRISDbits.TRISD2 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    LATDbits.LATD1 = 0;
    
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
    PR2 = 2;
    
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
    
    //////////////////////
    // Configure DAC
    /////////////////////
    
    // DAC enabled
    DAC1CON0bits.DAC1EN = 1;
    
    // DACOUT pin enabled
    DAC1CON0bits.DAC1OE1 = 1;
    
    // +ve source is Vdd
    DAC1CON0bits.DAC1PSS = 0;
    
    // -ve source is Vss
    DAC1CON0bits.DAC1NSS = 0;
    
    // Initial output is 0v
    DAC1CON1bits.DAC1R = 0;
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
    static uint8_t index = 0;
    
    PIR1bits.TMR2IF = 0;
    
    DAC1CON1  = sineData[index];
    
    // Increment index and wrap around if necessary
    index = (index + 1) & 0xFF;
}

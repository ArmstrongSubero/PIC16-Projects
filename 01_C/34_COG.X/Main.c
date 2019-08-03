/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 20_PWM
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program uses the PWM module of the PIC16F1717
 *                                          
 *           
 * Hardware Description: An HD44780 compatible LCD is connected to PORTD of the
 *                       microcontroller as follows:
 * 
 *                       RS ---> RD2
 *                       R/W ---> GND
 *                       EN ---> RD3
 *                       D4 ---> RD4
 *                       D5 ---> RD5
 *                       D6 ---> RD6
 *                       D7 ---> RD7
 *                     
 * An LED is connected to PINB0
 *               
 * Created November 7th, 2016, 5:20 PM
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
    internal_32();
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    // Setup PINB0 as output
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    /////////////////////
    // Configure PWM
    /////////////////////
    
    // Select PWM timer as Timer6
    CCPTMRSbits.C1TSEL = 0b10;
    
    // Prescale = 1
    T6CONbits.T6CKPS = 0b00;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;
    
    // Set timer period
    PR6 = 200;
    
    // Configure CCP1
    
    // LSB's of PWM duty cycle = 00
    CCP1CONbits.DC1B = 00;
    
    // Select PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // run at 50% duty
    CCPR1L = 127;
    
    /////////////////////
    // Configure COG
    /////////////////////
    
    // enable the COG
    COG1CON0bits.G1EN = 0;
    
    // clock select
    COG1CON0bits.G1CS0 = 1;
    COG1CON0bits.G1CS1 = 0;
    
    // select mode
    COG1CON0bits.G1MD0 = 0;
    COG1CON0bits.G1MD1 = 0;
    COG1CON0bits.G1MD2 = 0;
    
    // select rising clock input
    COG1RISbits.G1RIS4 = 1;
    
    // select clock falling input
    COG1FISbits.G1FIS4 = 1;
    
    COG1STRbits.G1STRA = 1;
    COG1STRbits.G1STRB = 1;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to PWM1
    //RB0PPSbits.RB0PPS = 0b01100;
    
    RB1PPS = 0x09;   //RB1->COG1:COG1B;    
    RB0PPS = 0x08;   //RB0->COG1:COG1A;  
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

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
    int x;
    
    while(1){
        
   
       
    }
    
    return;   
}

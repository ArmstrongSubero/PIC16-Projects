/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I05_H_Bridge
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates using a SN754410 H-Bridge with a
 *                      DC motor with a PIC microcontroller.
 *                      
 * Hardware Description: A generic brushed hobby DC motor is connected to the 
 *                       SN754410 as per standard connections. The PWM signals
 *                       are emanating from RB0 and RB1 for forward and reverse
 *                       signals respectively.
 *                       
 *                      
 * Created January 15th, 2017, 11:36 AM
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
    
    
    ////////////////////
    // Configure Ports
    ///////////////////
    
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
    
    // Set PIN B1 as output
    TRISBbits.TRISB1 = 0;
    
    // Turn off analog
    ANSELB = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select PWM timer as Timer6 for CCP1 and CCP2
    CCPTMRSbits.C1TSEL = 0b10;
    CCPTMRSbits.C2TSEL = 0b10;
    
 
    // Enable timer Increments every 250 ns (16MHz clock) 1000/(16/4)
    // Period = 256 x 0.25 us = 64 us
    
    //                          Crystal Frequency 
    //    PWM Freq  = ----------------------------------------- 
    //                  (PRX + 1) * (TimerX Prescaler) * 4
    
    //    PWM Frequency = 16 000 000 / 256 * 1 * 4
    //    PWM Frequency = 15.625 kHz
    
    // Prescale = 1
    T6CONbits.T6CKPS = 0b00;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;
    
    // Set timer period
    PR6 = 255;
    
    
    //////////////////////////
    // Configure PWM
    /////////////////////////
    
    // Configure CCP1
     
    // LSB's of PWM duty cycle = 00
    CCP1CONbits.DC1B = 00;
    
    // Select PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // Configure CCP2
    
    // LSB's of PWM duty cycle = 00
    CCP2CONbits.DC2B = 00;
    
    // Select PWM mode
    CCP2CONbits.CCP2M = 0b1100;
    
    
    //////////////////////////////
    // Configure PPS
    /////////////////////////////
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to PWM1
    RB0PPSbits.RB0PPS = 0b01100;
    
    // Set RB1 to PWM2
    RB1PPSbits.RB1PPS = 0b01101;
    
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

    while(1){
        // Run at 75% duty cycle @ 15.625 kHz for 5 sec
        
        // Forward
        CCPR1L = 192;
        CCPR2L = 0;
        
        __delay_ms(5000);
        
        CCPR1L = 0;
        CCPR2L = 0;
        
        __delay_ms(2000);
        
        // Reverse
        CCPR1L = 0;
        CCPR2L = 192;
        
        __delay_ms(5000);

    }
     return;    
}


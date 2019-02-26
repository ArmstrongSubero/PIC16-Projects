/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I10_RGB_LED
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This demonstrates using a RGB LED with PIC16F1717
 *                      
 * Hardware Description:  A RGB LED is connected as follows:
 *                        Red   - RB0
 *                        Green - RB3
 *                        Blue  - RB2
 *                       
 *                      
 * Created Tuesday 18th, April, 2017, 11:53 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"


/*
 Value for PWM1
 */
void PWM1_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC) >> 2);

    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}

/*
  Value for PWM2 
 */
void PWM2_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR2L = ((dutyValue & 0x03FC) >> 2);

    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP2CON = (CCP2CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}

/*
 Value for PWM3
 */
void PWM3_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
    PWM3DCH = (dutyValue & 0x03FC) >> 2;

    // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
    PWM3DCL = (dutyValue & 0x0003) << 6;
}


/*
 Value for RGB LED
 */
void RGB_LoadValue(uint16_t red, uint16_t green, uint16_t blue)
{

    PWM1_LoadDutyValue(red);
    PWM2_LoadDutyValue(green);
    PWM3_LoadDutyValue(blue); 
}


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
    
    // Set PIN B2 as output
    TRISBbits.TRISB2 = 0;
    
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
    
    // Configure PWM 3
    
    // PWM3EN enabled, PWM3POL active high
    PWM3CON = 0x80;

    // PWM3DCH 127 
    PWM3DCH = 0x7F;

    // PWM3DCL 192 
    PWM3DCL = 0xC0;

    // Select timer6
    CCPTMRSbits.P3TSEL = 0b10;
    
    
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
    
    // Set RB2 to PWM3
    RB2PPSbits.RB2PPS = 0x0E;
    
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
    
    
    // All channels initially 0
    PWM1_LoadDutyValue(0);
    PWM2_LoadDutyValue(0);
    PWM3_LoadDutyValue(0);

    while(1){
        
        // Red
        RGB_LoadValue(512,   0,  0);
        __delay_ms(1000);
        
        
        // Green
        RGB_LoadValue(0,   512,  0);
        __delay_ms(1000);
        
        // Blue
        RGB_LoadValue(0,   0,   512);
        __delay_ms(1000);
        
        // Yellow
        RGB_LoadValue(192,   192,   0);
        __delay_ms(1000);
        
        // Purple
        RGB_LoadValue(192,   0,   192);
        __delay_ms(1000);
        
        // Aquamarine
        RGB_LoadValue(0,   512,   512);
        __delay_ms(1000);
        
    }
     return;    
}


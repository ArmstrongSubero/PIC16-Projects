/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 33_Motor_BTS7960
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.0
 *                
 * Program Description: This program allows a PIC microcontroller to be 
 *                      interfaced to a BTS7960 motor driver module
 * 
 * Hardware Description: A BTS7960 motor driver is connected to a PIC MCU as 
 *                       follows:
 * 
 *                       RPWM - RB0
 *                       LPWM - RB1 
 *                       R_EN - RD0 
 *                       L_EN - RD1
 *                       R_IS - N/C
 *                       L_IS - N/C
 *                       VCC  - 5V
 *                       GND  - GND
 *                         
 *                       The motor used to test is a 131:1 Pololu gear motor. 
 *                       Recommended 4 1000 uF caps on power rails otherwise 
 *                       MCU may fail to program 
 * 
 *                       
 * Created February 26th, 2024, 11:34 PM
 * Last Updated: February 26th, 2024, 11:34 PM
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
    
    ////////////////////
    // Configure Ports
    ///////////////////
    TRISDbits.TRISD1 = 0;
    
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
    
    // Set PIN B1 as output
    TRISBbits.TRISB1 = 0;
    
    // Turn off analog
    ANSELB = 0;
    
    // Control pins for BTS7960
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;  
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select PWM timer as Timer6 for CCP1 and CCP2
    CCPTMRSbits.C1TSEL = 0b10;
    CCPTMRSbits.C2TSEL = 0b10;
    
 
    // Enable timer Increments every 125 ns (32 MHz clock) 1000/(32/4)
    // Period = 256 x 0.125 us = 31.25 us
    
    //                          Crystal Frequency 
    //    PWM Freq  = ----------------------------------------- 
    //                  (PRX + 1) * (TimerX Prescaler) * 4
    
    //    PWM Frequency = 32 000 000 / 256 * 1 * 4
    //    PWM Frequency = 31.250 kHz
    
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

// enable reverse drive enable input
void leftEnable(void)
{
   LATDbits.LATD0 = 1; 
}

// disable reverse drive enable input
void leftDisable(void)
{
    LATDbits.LATD0 = 0;
}

// enable forward drive enable input
void rightEnable(void)
{
    LATDbits.LATD1 = 1;
}

// disable forward drive enable input
void rightDisable(void)
{
    LATDbits.LATD1 = 0;
}

// set rightPWM duty cycle
void rightPWMDuty(uint16_t duty)
{
    CCPR1L = duty;
}

// set left PWM duty cycle
void leftPWMDuty(uint16_t duty)
{
    CCPR2L = duty;
}

/*******************************************************************************
 * Function: void motorTurnLeft(uint16_t motorSpeed)
 *
 * Returns: Nothing
 *
 * Description: Turns the motor in the left direction
 ******************************************************************************/
void motorTurnLeft(uint16_t motorSpeed)
{
   // enable both channels
   leftEnable();
   rightEnable();
   
   // turn off left PWM 
   leftPWMDuty(0);
   
   // turn on right PWM
   rightPWMDuty(motorSpeed);
}


/*******************************************************************************
 * Function: void motorTurnRight(uint16_t motorSpeed)
 *
 * Returns: Nothing
 *
 * Description: Turns the motor in the right direction
 ******************************************************************************/
void motorTurnRight(uint16_t motorSpeed)
{
   // enable both channels
   leftEnable();
   rightEnable();
   
   // turn off left PWM 
   leftPWMDuty(motorSpeed);
   
   // turn on right PWM
   rightPWMDuty(0);
    
}

/*******************************************************************************
 * Function: void motorStop(void)
 *
 * Returns: Nothing
 *
 * Description: Stops the motor rotation
 ******************************************************************************/
void motorStop(void)
{
   // disable both channels
   leftDisable();
   rightDisable();
   
   // turn off left PWM 
   leftPWMDuty(0);
   
   // turn off right PWM
   rightPWMDuty(0); 
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

    while(1)
    {
        // turn the motor left
        motorTurnLeft(192);
        __delay_ms(3000);
        
        motorStop();
        __delay_ms(3000);
        
        // turn the motor right
        motorTurnRight(192);
        __delay_ms(3000);
        
        motorStop();
        __delay_ms(3000);
    }
     return;    
}
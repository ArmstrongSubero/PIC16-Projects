/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 32_Motor_PWM
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.3
 *                
 * Program Description: This program allows for control of a DC motor using 
 *                      the PWM module. The motor speed is ramped up then it 
 *                      it ramped down.
 * 
 * Hardware Description: The 2N2222A transistor is used to drive an IRF540 
 *                       MOSFET that is then used to control a 131:1 gear 
 *                       motor rated for a 5A stall current. 
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: January 11th, 2024, 7:31 PM
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
    __delay_ms(100);
    
    ////////////////////
    // Configure Ports
    ///////////////////
   
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
      
    // Turn off analog
    ANSELB = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select PWM timer as Timer6 for CCP1
    CCPTMRSbits.C1TSEL = 0b10;

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
    
    //////////////////////////////
    // Configure PPS
    /////////////////////////////
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to PWM1
    RB0PPSbits.RB0PPS = 0b01100;
   
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
}


/*******************************************************************************
 * Function: void setPWMDutyCycle(uint8_t dutyCycle) 
 *
 * Returns: Nothing
 *
 * Description: Sets the PWM duty Cycle
 * 
 * Usage: setPWMDutyCycle(255)
 ******************************************************************************/

void setPWMDutyCycle(uint8_t dutyCycle) 
{
    CCPR1L = dutyCycle;     // Load the duty cycle value to CCP1
}


/*******************************************************************************
 * Function: void controlMotorPWM(uint8_t dutyCycle) 
 *
 * Returns: Nothing
 *
 * Description: Controls the motor 
 * 
 * Usage: controlMotorPWM(dutyCycle)
 ******************************************************************************/
void controlMotorPWM(uint8_t dutyCycle) 
{
    // Set the PWM duty cycle
    setPWMDutyCycle(dutyCycle);
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
    initMain();

    while(1)
    {
        // Increase duty cycle to ramp up motor speed
        for (uint8_t dutyCycle = 0; dutyCycle < 255; dutyCycle++) 
        {
            controlMotorPWM(dutyCycle);
            // Adjust delay as needed for smooth speed changes
            __delay_ms(50);  
        }

        // Decrease duty cycle to ramp down motor speed
        for (uint8_t dutyCycle = 255; dutyCycle > 0; dutyCycle--) 
        {
            controlMotorPWM(dutyCycle);
            // Adjust delay as needed for smooth speed changes
            __delay_ms(50); 
        }
    }
     return;    
}
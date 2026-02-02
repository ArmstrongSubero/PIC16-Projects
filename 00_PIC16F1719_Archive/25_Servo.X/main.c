/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 8MHz, 5v
 * Program: 25_Servo
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This controls a servo to turn one direction and then 
 *                      to turn the other direction using PWM
 * 
 * Hardware Description: An continuous rotation servo is connected to PINB0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 26th, 2023, 4:30 AM
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
    // Run at 8 MHz
    internal_8();
       
    ////////////////////
    // Configure Ports
    ///////////////////
    
    // Set PIN B0 as servo output
    TRISBbits.TRISB0 = 0;
    
    // Turn off analog
    ANSELB = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////

    // PR6 249; 
    PR6 = 249;

    // TMR6 0; 
    TMR6 = 0x00;

    // Clearing IF flag.
    PIR2bits.TMR6IF = 0;

    // T6CKPS 1:64; T6OUTPS 1:1; TMR6ON on; 
    T6CON = 0x07;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;

    //////////////////////////
    // Configure PWM
    /////////////////////////
        
    // Set the PWM1 to the options selected in the User Interface
	
	// CCP1M PWM; DC1B 3; 
	CCP1CON = 0x3C;    
	
	// CCPR1L 124; 
	CCPR1L = 0x7C;    
	
	// CCPR1H 0; 
	CCPR1H = 0x00;    

	// Selecting Timer 6
	CCPTMRSbits.C1TSEL = 0x2;
    
      
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
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void PWM1_LoadDutyValue(uint16_t dutyValue)
{
   // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003)<<4);
}

void main(void) {
    initMain();
    
    uint16_t duty;
    
    while(1){
        PWM1_LoadDutyValue(375);
       
        __delay_ms(2000);
       
        PWM1_LoadDutyValue(5);
        
        __delay_ms(2000);
    }
     return;    
}
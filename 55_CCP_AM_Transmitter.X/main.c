/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 55_CCP_AM_Transmitter
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: Transmits Twilight Zone theme via AM at ~1MHz
 *                      using PWM for RF carrier with OOK modulation
 * 
 * Hardware Description: RF output on RB0 (CCP1/PWM), LED on RC3
 *                       Make a 12 inch loop antenna and you'll get reception 
 *                       up to about a foot. 
 *                       
 * Created January 30th, 2026, 1:52 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
volatile unsigned long millis_count = 0;

/*******************************************************************************
 * Function: unsigned long millis(void)
 ******************************************************************************/
unsigned long millis(void) {
    unsigned long m;
    di();
    m = millis_count;
    ei();
    return m;
}

/*******************************************************************************
 * Function: void delay_us_var(unsigned int us)
 ******************************************************************************/
void delay_us_var(unsigned int us) {
    while (us--) {
        __delay_us(1);
    }
}

/*******************************************************************************
 * Function: void initMain()
 ******************************************************************************/
void initMain(){
    // Run at 32 MHz
    internal_32();
    __delay_ms(100);
    
    ////////////////////
    // Configure LED
    ///////////////////
    TRISCbits.TRISC3 = 0;
    ANSELCbits.ANSC3 = 0;
    LATCbits.LATC3 = 0;
    
    ////////////////////
    // Configure PWM Output Pin
    ///////////////////
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSB0 = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select Timer6 for CCP1
    CCPTMRSbits.C1TSEL = 0b10;
    
    // Prescale = 1
    T6CONbits.T6CKPS = 0b00;
    
    // Set timer period for 1MHz PWM
    // PWM Freq = 32MHz / ((PR6 + 1) * 1 * 4)
    // 1MHz = 32MHz / ((7 + 1) * 4)
    PR6 = 7;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;
    
    //////////////////////////
    // Configure PWM (CCP1)
    /////////////////////////
    
    // LSB's of PWM duty cycle = 00
    CCP1CONbits.DC1B = 0b00;
    
    // Select PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // 50% duty cycle for square wave
    // With PR6 = 7, full period = 8 counts
    // 50% = 4
    CCPR1L = 4;
    
    //////////////////////////////
    // Configure PPS
    /////////////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to CCP1/PWM1
    RB0PPSbits.RB0PPS = 0b01100;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    //////////////////////
    // Configure Timer0 for millis()
    //////////////////////
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b100;  // 1:32 prescaler
    TMR0 = 6;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    ei();
}

/*******************************************************************************
 * Function: void __interrupt() isr(void)
 ******************************************************************************/
void __interrupt() isr(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 6;
        millis_count++;
    }
}

/*******************************************************************************
 * Function: void carrier_on(void)
 ******************************************************************************/
void carrier_on(void) {
    CCP1CONbits.CCP1M = 0b1100;  // PWM mode on
}

/*******************************************************************************
 * Function: void carrier_off(void)
 ******************************************************************************/
void carrier_off(void) {
    CCP1CONbits.CCP1M = 0b0000;  // CCP off
    LATBbits.LATB0 = 0;          // Pin low
}

/*******************************************************************************
 * Function: void play_note(unsigned int half_period_us, unsigned int duration_ms)
 ******************************************************************************/
void play_note(unsigned int half_period_us, unsigned int duration_ms) {
    unsigned long start = millis();
    
    while ((millis() - start) < duration_ms) {
        carrier_off();
        delay_us_var(half_period_us);
        carrier_on();
        delay_us_var(half_period_us);
    }
    
    carrier_off();
}

/*******************************************************************************
 * Function: Main
 ******************************************************************************/
void main(void) {
    initMain();
    
    // Twilight Zone theme: G#, A, G#, E
    // Half-periods in microseconds
    const unsigned int half_period[] = {1204, 1136, 1204, 1516};
    const unsigned int beat = 250;  // ms per note
    
    while(1) {
        // Play four notes
        for (uint8_t i = 0; i < 4; i++) {
            play_note(half_period[i], beat);
        }
        
        // LED blink
        LATCbits.LATC3 = 1;
        __delay_ms(1);
        LATCbits.LATC3 = 0;
    }
    
    return;    
}
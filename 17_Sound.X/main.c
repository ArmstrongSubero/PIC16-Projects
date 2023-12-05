/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 17_Sound
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This generates a PWM signal in the audible range using 
 *                      16 bit Timer1
 * 
 * Hardware Description: An Piezo buzzer is connect to PIN RB0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Last Updated: November 18th, 2023, 4:36 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"

#define BUZZER LATBbits.LATB0
#define Max_Notes 25

unsigned char TIMER_H, TIMER_L;


void Delay_Ms(unsigned int s)
{
    unsigned int j;
    for(j = 0; j < s; j++)
    {
        __delay_ms(1);
    }
}

unsigned int Notes[Max_Notes] =
{
    659, 659, 0, 659, 0, 523, 659, 0, 784, 0, 392, 523, 0, 311,
    466, 0, 466, 0, 370, 466, 0, 554, 0, 523, 0, 0,
};

unsigned char Durations[Max_Notes] =
{
    125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
    125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125
};



/*
unsigned int Notes[Max_Notes] =
{
    262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392,
    349, 262, 262, 524, 440, 349, 330, 294, 466, 466, 440,
    349, 392, 349
};

unsigned char Durations[Max_Notes] =
{
    1, 1, 2, 2, 2, 3, 1, 1, 2, 2, 2, 3, 1, 1, 2, 2, 2, 2, 2,
    1, 1, 2, 2, 2, 3
};
 */

void Sound_Play(unsigned int freq, unsigned int duration)
{
    float period;
    period = 500000.0/freq;
    period = 65536-period;
    
    TIMER_H = (char)(period/256);
    TIMER_L = (char) (period-256*TIMER_H);
    TMR1H = TIMER_H;
    TMR1L = TIMER_L;
    
    T1CONbits.TMR1ON = 1;
    
    Delay_Ms(duration);
    T1CONbits.TMR1ON = 0;
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
    // Run at 32 MHz
    internal_32();
    
    ////////////////////
    // Configure Ports
    ///////////////////  
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
    
    
    // Turn off analog
    ANSELB = 0;
    
        // prescale = 2
    T1CONbits.T1CKPS = 0b01;
    
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
    unsigned char i;

    while(1){
       for (i = 0; i < Max_Notes; i++)
       {
           Sound_Play(Notes[i], 400*Durations[i]);
           __delay_ms(100);
       }
       
       __delay_ms(2000);
    
    }
     return;    
}

void __interrupt() isr(void)
{
    PIR1bits.TMR1IF = 0;
    TMR1H = TIMER_H;
    TMR1L = TIMER_L;
    BUZZER = !BUZZER;
}
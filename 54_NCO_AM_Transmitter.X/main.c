/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 54_NCO_AM_Transmitter
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: Transmits Twilight Zone theme via AM at ~1MHz
 *                      using NCO for RF carrier and OOK modulation
 * 
 * Hardware Description: RF output on RA4 (NCO), LED on RC3
 *                       Attach short wire antenna to RA4, the output power is 
 *                       very low and you'll need to put the antenna right up 
 *                       to the device. 
 *                       
 * Created January 30th, 2026, 1:05 PM
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
 *
 * Returns: Milliseconds since startup
 *
 * Description: Returns current millisecond count (interrupt-safe)
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
 *
 * Returns: Nothing
 *
 * Description: Variable microsecond delay (for use with non-constant values)
 ******************************************************************************/
void delay_us_var(unsigned int us) {
    while (us--) {
        __delay_us(1);
    }
}

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 ******************************************************************************/
void initMain(){
    
    // Run at 32 MHz
    internal_32();
    
    // PLL stabilization 
    __delay_ms(100);
    
    //////////////////////
    // Configure LED
    //////////////////////
    TRISCbits.TRISC3 = 0;
    ANSELCbits.ANSC3 = 0;
    LATCbits.LATC3 = 0;
    
    //////////////////////
    // Configure NCO
    //////////////////////
    
    // Unlock PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00;
    
    // NCO output to RA4
    RA4PPSbits.RA4PPS = 0x03;
    
    // Lock PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01;
    
    // Configure RA4 as digital output
    TRISAbits.TRISA4 = 0;
    ANSELAbits.ANSA4 = 0;
    
    // NCO increment for ~1MHz output
    // Fout = (INC * Fosc) / 2^20
    // 1MHz = (INC * 32MHz) / 1048576
    // INC = 32768 = 0x8000
    NCO1INCH = 0x80;
    NCO1INCL = 0x00;
    
    // Fixed Duty Cycle mode (50% square wave)
    NCO1CONbits.N1PFM = 0;
    
    // Output active high
    NCO1CONbits.N1POL = 0;
    
    // Clock source: Fosc (32MHz)
    NCO1CLKbits.N1CKS = 0b01;
    
    // NCO starts disabled (will enable during tone playback)
    NCO1CONbits.N1EN = 0;
    
    //////////////////////
    // Configure Timer0
    //////////////////////
    
    // Timer mode (internal Fosc/4 = 8MHz)
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign prescaler to Timer0
    OPTION_REGbits.PSA = 0;
    
    // Prescaler 1:32 -> 8MHz/32 = 250kHz timer clock
    OPTION_REGbits.PS = 0b100;
    
    // Preload for 1ms overflow: 256 - 250 = 6
    TMR0 = 6;
    
    // Clear interrupt flag
    INTCONbits.TMR0IF = 0;
    
    // Enable Timer0 interrupt
    INTCONbits.TMR0IE = 1;
    
    // Enable global interrupts
    ei();
}

/*******************************************************************************
 * Function: void __interrupt() isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer0 interrupt - 1ms tick for millis() counter
 ******************************************************************************/
void __interrupt() isr(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 6;  // Reload for next 1ms
        millis_count++;
    }
}

/*******************************************************************************
 * Function: void play_note(unsigned int half_period_us, unsigned int duration_ms)
 *
 * Returns: Nothing
 *
 * Description: Plays a single note by OOK modulating the NCO carrier
 *              half_period_us: half the period of the audio tone in microseconds
 *              duration_ms: how long to play the note in milliseconds
 ******************************************************************************/
void play_note(unsigned int half_period_us, unsigned int duration_ms) {
    unsigned long start = millis();
    
    while ((millis() - start) < duration_ms) {
        NCO1CONbits.N1EN = 0;           // Carrier OFF
        delay_us_var(half_period_us);
        NCO1CONbits.N1EN = 1;           // Carrier ON
        delay_us_var(half_period_us);
    }
    
    // Ensure carrier is off between notes
    NCO1CONbits.N1EN = 0;
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point - plays Twilight Zone theme on loop
 ******************************************************************************/
void main(void) {
    initMain();
    
    // Twilight Zone theme: G#, A, G#, E
    // Half-periods calculated as: 500000 / frequency
    // G# (415.3 Hz) -> 1204 us
    // A  (440.0 Hz) -> 1136 us
    // E  (329.6 Hz) -> 1516 us
    
    const unsigned int half_period[] = {1204, 1136, 1204, 1516};
    const unsigned int beat = 250;  // Note duration in ms
    
    while(1) {
        
        // Play the four notes
        for (uint8_t i = 0; i < 4; i++) {
            play_note(half_period[i], beat);
        }
        
        // LED blink to indicate cycle complete
        LATCbits.LATC3 = 1;
        __delay_ms(1);
        LATCbits.LATC3 = 0;
        
        // Small gap before repeat (tune plays once per second)
        // 4 notes * 250ms = 1000ms, so no additional delay needed
        // Adjust this if timing drifts
    }
    
    return;
}
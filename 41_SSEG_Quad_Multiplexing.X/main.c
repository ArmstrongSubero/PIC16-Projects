/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 40_SSEG_Quad_Multiplexing
 * Compiler: XC8 (v2.46, MPLAB X v6.20)
 * Program Version: 2.0
 *
 * Program Description:
 *   Quad (4) digit multiplexed seven segment display using Timer2 interrupt.
 *
 * Hardware Description:
 *   - Segments (a,b,c,d,e,f,g,dp) connected to PORTC (LATC)
 *   - Digit enables connected to:
 *       RB0 = DIG0 (ones)
 *       RB1 = DIG1 (tens)
 *       RB2 = DIG2 (hundreds)
 *       RB3 = DIG3 (thousands)
 *
 * Notes:
 *   - This code assumes "active-high" digit enables.
 *   - For common-anode (active-low enables), invert DIGx logic.
 *   - Segment patterns below assume common-cathode segment logic.
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

/*******************************************************************************
 * Digit enable macros (RB0..RB3)
 ******************************************************************************/
#define DIG0 LATBbits.LATB0
#define DIG1 LATBbits.LATB1
#define DIG2 LATBbits.LATB2
#define DIG3 LATBbits.LATB3

/*******************************************************************************
 * Globals used by ISR
 ******************************************************************************/
volatile uint16_t displayValue = 0;
volatile uint8_t  digits[4]     = {0, 0, 0, 0};
volatile uint8_t  currentDigit  = 0;

/*******************************************************************************
 * Function: uint8_t seg(uint8_t num)
 *
 * Returns:
 *   Segment activation mask for digits 0..9
 ******************************************************************************/
uint8_t seg(uint8_t num)
{
    switch(num)
    {
        case 0: return 0x3F;
        case 1: return 0x06;
        case 2: return 0x5B;
        case 3: return 0x4F;
        case 4: return 0x66;
        case 5: return 0x6D;
        case 6: return 0x7D;
        case 7: return 0x07;
        case 8: return 0x7F;
        case 9: return 0x6F;
        default: return 0x00;
    }
}

/*******************************************************************************
 * Function: void updateDigits(uint16_t value)
 *
 * Description:
 *   Splits value (0..9999) into four decimal digits.
 *   digits[0] = ones, digits[1] = tens, digits[2] = hundreds, digits[3] = thousands
 ******************************************************************************/
void updateDigits(uint16_t value)
{
    digits[0] = (uint8_t)(value % 10);
    digits[1] = (uint8_t)((value / 10) % 10);
    digits[2] = (uint8_t)((value / 100) % 10);
    digits[3] = (uint8_t)((value / 1000) % 10);
}

/*******************************************************************************
 * Function: void initMain(void)
 ******************************************************************************/
void initMain(void)
{
    // Run at 32 MHz
    internal_32();

    // Stabilize PLL
    __delay_ms(100);

    // Segments on PORTC
    TRISC = 0x00;
    LATC  = 0x00;

    // Digit enables on RB0..RB3
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    // Start with all digits OFF
    DIG0 = 0; DIG1 = 0; DIG2 = 0; DIG3 = 0;

    /////////////////////
    // Configure Timer2
    /////////////////////
    T2CONbits.T2CKPS = 0b10;

    // period
    PR2 = 62;

    // reset timer
    TMR2 = 0;

    T2CONbits.T2OUTPS = 0b0000;

    // clear interrupt flag
    PIR1bits.TMR2IF = 0;

    // enable Timer2 interrupt
    PIE1bits.TMR2IE = 1;

    // enable peripheral interrupt
    INTCONbits.PEIE = 1;

    // enable Timer2
    T2CONbits.TMR2ON = 1;

    // enable global interrupts
    ei();
}

/*******************************************************************************
 * Function: void __interrupt() isr(void)
 *
 * Description:
 *   Timer2 interrupt scans one digit per interrupt.
 ******************************************************************************/
void __interrupt() isr(void)
{
    if(PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;

        // Turn OFF all digits first (avoid ghosting)
        DIG0 = 0; DIG1 = 0; DIG2 = 0; DIG3 = 0;

        // Output segment data for the current digit
        LATC = seg(digits[currentDigit]);

        // Enable the correct digit
        switch(currentDigit)
        {
            case 0: DIG0 = 1; break; // ones
            case 1: DIG1 = 1; break; // tens
            case 2: DIG2 = 1; break; // hundreds
            case 3: DIG3 = 1; break; // thousands
            default: break;
        }

        // Next digit
        currentDigit++;
        if(currentDigit >= 4)
            currentDigit = 0;
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();

    // Start at 0
    displayValue = 0;
    updateDigits(displayValue);

    while(1)
    {
        // Count 0..9999
        displayValue++;
        if(displayValue > 9999)
            displayValue = 0;

        // Update digit buffer (ISR will display it)
        updateDigits(displayValue);

        // Slow the visible count rate (display refresh is handled by ISR)
        __delay_ms(100);
    }
}

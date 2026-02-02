/*
 * File: driver.c
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: TinyJoypad Driver Layer Implementation
 * Compiler: XC8
 *
 * Description:
 * Implementation of the JOY_* interface for TinyJoypad games on PIC16F.
 */

#include "driver.h"

/*******************************************************************************
 * Function: void JOY_init(void)
 *
 * Description:
 * Initialize all hardware: oscillator, I2C, OLED, buttons, Timer0, buzzer.
 ******************************************************************************/
void JOY_init(void)
{
    /* Initialize oscillator to 32MHz (call your existing internal_32) */
    internal_32();
    __delay_ms(100);
    
    /***************************************************************************
     * Configure I2C pins (same as your existing setup)
     **************************************************************************/
    ANSELCbits.ANSC4 = 0;   /* Digital */
    ANSELCbits.ANSC5 = 0;   /* Digital */
    TRISCbits.TRISC4 = 1;   /* Input (I2C peripheral controls direction) */
    TRISCbits.TRISC5 = 1;   /* Input (I2C peripheral controls direction) */
    
    /***************************************************************************
     * Configure button pins (RA0, RA1, RA2) as digital inputs with pull-ups
     **************************************************************************/
    ANSELAbits.ANSA0 = 0;   /* Digital */
    ANSELAbits.ANSA1 = 0;   /* Digital */
    ANSELAbits.ANSA2 = 0;   /* Digital */
    
    TRISAbits.TRISA0 = 1;   /* Input - Left button */
    TRISAbits.TRISA1 = 1;   /* Input - Right button */
    TRISAbits.TRISA2 = 1;   /* Input - Fire button */
    
    /* Enable weak pull-ups on PORTA */
    OPTION_REGbits.nWPUEN = 0;  /* Enable individual weak pull-ups */
    WPUAbits.WPUA0 = 1;         /* Pull-up on RA0 */
    WPUAbits.WPUA1 = 1;         /* Pull-up on RA1 */
    WPUAbits.WPUA2 = 1;         /* Pull-up on RA2 */
    
    /***************************************************************************
     * Configure buzzer pin (RB0) as output
     **************************************************************************/
    ANSELBbits.ANSB0 = 0;   /* Digital */
    BUZZER_TRIS = 0;        /* Output */
    BUZZER_LAT = 0;         /* Start low */
    
    /***************************************************************************
     * Configure Timer0 for random number generation
     * Free-running 8-bit timer, no prescaler, Fosc/4 clock
     **************************************************************************/
    OPTION_REGbits.TMR0CS = 0;  /* Internal clock (Fosc/4) */
    OPTION_REGbits.PSA = 1;     /* Prescaler not assigned to TMR0 */
    /* Timer0 now free-runs and wraps, giving pseudo-random values */
    
    /***************************************************************************
     * PPS Mapping for I2C (same as your existing setup)
     **************************************************************************/
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;  /* Unlock PPS */
    
    /* I2C Data on RC4 */
    RC4PPSbits.RC4PPS = 0x11;       /* RC4 -> SDA output */
    SSPDATPPSbits.SSPDATPPS = 0x14; /* RC4 -> SDA input */
    
    /* I2C Clock on RC5 */
    SSPCLKPPSbits.SSPCLKPPS = 0x15; /* RC5 -> SCL input */
    RC5PPSbits.RC5PPS = 0x10;       /* RC5 -> SCL output */
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;  /* Lock PPS */
    
    /***************************************************************************
     * Initialize I2C and OLED
     **************************************************************************/
    I2C_Init();
    __delay_ms(50);
    
    OLED_init();
    OLED_fill(0x00);    /* Clear screen */
}

/*******************************************************************************
 * Function: uint8_t JOY_random(void)
 *
 * Description:
 * Returns a pseudo-random 8-bit value from Timer0.
 ******************************************************************************/
uint8_t JOY_random(void)
{
    return TMR0;
}

/*******************************************************************************
 * Function: void JOY_sound(uint8_t freq, uint8_t duration)
 *
 * Description:
 * Generate a simple tone on the buzzer.
 * freq: delay value (higher = lower frequency)
 * duration: number of cycles
 *
 * Note: This is a blocking function. For a real game you might want
 * to use a timer interrupt for non-blocking sound.
 ******************************************************************************/
void JOY_sound(uint8_t freq, uint8_t duration)
{
    uint8_t i;
    
    /* If freq is 0 or very low, skip (avoid divide by zero or stuck loop) */
    if (freq < 2) return;
    
    for (i = 0; i < duration; i++) {
        BUZZER_LAT = 1;
        
        /* Simple delay based on freq value */
        for (uint8_t d = 0; d < freq; d++) {
            __delay_us(10);
        }
        
        BUZZER_LAT = 0;
        
        for (uint8_t d = 0; d < freq; d++) {
            __delay_us(10);
        }
    }
}

/*
 * File: driver.c
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: TinyJoypad Driver for Tiny Pacman
 * Compiler: XC8
 */

#include "driver.h"
#include "I2C.h"

#define SOUND_ENABLED  1

static uint16_t rnval = 0xACE1;

void JOY_init(void)
{
    internal_32();
    __delay_ms(100);
    
    /* I2C pins */
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    
    /* Button pins - RA0, RA1, RA2, RA4, RA5 as digital inputs */
    ANSELAbits.ANSA0 = 0;
    ANSELAbits.ANSA1 = 0;
    ANSELAbits.ANSA2 = 0;
    ANSELAbits.ANSA4 = 0;
    ANSELAbits.ANSA5 = 0;
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    
    /* Enable weak pull-ups */
    OPTION_REGbits.nWPUEN = 0;
    WPUAbits.WPUA0 = 1;
    WPUAbits.WPUA1 = 1;
    WPUAbits.WPUA2 = 1;
    WPUAbits.WPUA4 = 1;
    WPUAbits.WPUA5 = 1;
    
    /* Buzzer pin */
    ANSELBbits.ANSB0 = 0;
    BUZZER_TRIS = 0;
    BUZZER_LAT = 0;
    
    /* PPS for I2C */
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;
    
    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;
    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
    
    /* Initialize I2C and OLED */
    I2C_Init();
    __delay_ms(50);
    
    OLED_init();
    OLED_fill(0x00);
}

void JOY_delay_ms(uint16_t ms)
{
    while(ms--) {
        __delay_ms(1);
    }
}

uint8_t JOY_random(void)
{
    rnval = (rnval >> 1) ^ (-(rnval & 1) & 0xB400);
    return (uint8_t)(rnval & 0xFF);
}

void JOY_sound(uint8_t freq, uint8_t duration)
{
#if SOUND_ENABLED
    if (freq < 5) return;
    
    while (duration--) {
        BUZZER_LAT = 1;
        for (uint8_t d = 0; d < freq; d++) NOP();
        BUZZER_LAT = 0;
        for (uint8_t d = 0; d < freq; d++) NOP();
    }
#endif
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
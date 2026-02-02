/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 15_OLED_SSD1306
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program uses the SSD1306 OLED on the I2C bus, 
 *                      this program is optimized for space savings and 
 *                      supports %d, %u, %lu, %ld, %x, %s, %c and literal %%
 *                      does not support %f, %e or %g. Uses ~56% memory vs 
 *                      using vsnprintf routines. Also includes an optimized 
 *                      battery icon for displaying battery life. 
 * 
 * Hardware Description: A 128x32 OLED is connected to the I2C bus:
 *                       SDA ->  RC4 
 *                       SCK ->  RC5
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 6:44 PM
 */

/*******************************************************************************
 * Includes and Defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"

/*******************************************************************************
 * Function: void initMain(void)
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);

    /* I2C pins */
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    /* PPS mapping */
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS   = 0x0B;

    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;

    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();
    I2C_Init();
    
    OLED_Init();
    OLED_SetOrientation(OLED_ORIENT_0);
    OLED_Clear();
    
    uint32_t counter = 0;
    uint8_t battery  = 100;
    
    // Draw static text once
    OLED_Printf_Line(2, "Hello, world!");
    
    while (1)
    {
        // Update line 0 with text and battery together
        OLED_Printf_Line(0, "PIC16F1718");
        OLED_DrawBattery(battery, 120, 0);
        OLED_UpdateLine(0);
        
        // Update counter line
        OLED_Printf_Line(1, "Count: %lu", (unsigned long)counter);
        
        counter++;
        if (battery > 0) battery--; else battery = 100;
        
        if (counter > 100) {
            counter = 0;
        }
        
        __delay_ms(100);
    }
}
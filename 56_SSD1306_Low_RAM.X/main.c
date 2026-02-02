/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 56_SSD1306_Low_RAM 
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: This program allows the PIC16 to work with the SSD1306
 *                      OLED display using very little ram, compared to the 
 *                      buffer driver, and includes the bare minimum oled 
 *                      functionality. 
 * 
 * Hardware Description: A 128x64 SSD1306 OLED is connected to the I2C bus. 
 *                       
 *                       Vcc -> Vcc 
 *                       Gnd -> GND
 *                       SDA -> RC4 
 *                       SCL -> RC5
 *                       
 * Created January 30th, 2026, 4:38 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "oled_min.h"

/* Simple test patterns */
const uint8_t testPattern1 = 0xAA;  /* Vertical stripes */
const uint8_t testPattern2 = 0x55;  /* Inverse vertical stripes */
const uint8_t testPattern3 = 0xFF;  /* Solid */
const uint8_t testPattern4 = 0x0F;  /* Bottom half */
const uint8_t testPattern5 = 0xF0;  /* Top half */

/* Simple 8x8 smiley face */
const uint8_t smiley[8] = {
    0x3C,  /* 00111100 */
    0x42,  /* 01000010 */
    0xA5,  /* 10100101 */
    0x81,  /* 10000001 */
    0xA5,  /* 10100101 */
    0x99,  /* 10011001 */
    0x42,  /* 01000010 */
    0x3C   /* 00111100 */
};

/* Simple 8-pixel high letters for "HELLO" */
const uint8_t letterH[6] = {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00};
const uint8_t letterE[6] = {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00};
const uint8_t letterL[6] = {0x7F, 0x40, 0x40, 0x40, 0x40, 0x00};
const uint8_t letterO[6] = {0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00};

/*******************************************************************************
 * Test 1: Fill screen with pattern
 ******************************************************************************/
void test_fill_pattern(uint8_t pattern)
{
    OLED_fill(pattern);
}

/*******************************************************************************
 * Test 2: Draw horizontal bars (one per page)
 ******************************************************************************/
void test_horizontal_bars(void)
{
    uint8_t page, col;
    uint8_t patterns[] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00};
    
    for(page = 0; page < 8; page++) {
        OLED_data_start(page);
        for(col = 0; col < 128; col++) {
            OLED_send(patterns[page]);
        }
        OLED_end();
    }
}

/*******************************************************************************
 * Test 3: Draw vertical bars
 ******************************************************************************/
void test_vertical_bars(void)
{
    uint8_t page, col;
    
    for(page = 0; page < 8; page++) {
        OLED_data_start(page);
        for(col = 0; col < 128; col++) {
            if(col & 0x04) OLED_send(0xFF);  /* 4-pixel wide bars */
            else OLED_send(0x00);
        }
        OLED_end();
    }
}

/*******************************************************************************
 * Test 4: Draw checkerboard
 ******************************************************************************/
void test_checkerboard(void)
{
    uint8_t page, col;
    
    for(page = 0; page < 8; page++) {
        OLED_data_start(page);
        for(col = 0; col < 128; col++) {
            if((col + page) & 1) OLED_send(0xAA);
            else OLED_send(0x55);
        }
        OLED_end();
    }
}

/*******************************************************************************
 * Test 5: Draw border
 ******************************************************************************/
void test_border(void)
{
    uint8_t page, col;
    
    OLED_fill(0x00);  /* Clear first */
    
    for(page = 0; page < 8; page++) {
        OLED_data_start(page);
        for(col = 0; col < 128; col++) {
            if(page == 0) {
                OLED_send(0x01);  /* Top border */
            }
            else if(page == 7) {
                OLED_send(0x80);  /* Bottom border */
            }
            else if(col == 0 || col == 127) {
                OLED_send(0xFF);  /* Side borders */
            }
            else {
                OLED_send(0x00);
            }
        }
        OLED_end();
    }
}

/*******************************************************************************
 * Test 6: Draw smiley faces across screen
 ******************************************************************************/
void test_smiley(void)
{
    uint8_t page, col, i;
    
    OLED_fill(0x00);
    
    /* Draw smileys on page 3 and 4 (middle of screen) */
    for(page = 3; page <= 4; page++) {
        OLED_data_start(page);
        for(col = 0; col < 128; col++) {
            i = col % 16;  /* Repeat every 16 pixels */
            if(i < 8) {
                OLED_send(smiley[i]);
            } else {
                OLED_send(0x00);  /* Gap between smileys */
            }
        }
        OLED_end();
    }
}

/*******************************************************************************
 * Test 7: Write "HELLO" text
 ******************************************************************************/
void test_hello(void)
{
    uint8_t col, i;
    
    OLED_fill(0x00);
    
    /* Draw on page 3 (middle-ish) */
    OLED_data_start(3);
    
    /* Center "HELLO" - 5 letters * 6 pixels = 30 pixels, start at (128-30)/2 = 49 */
    /* Lead with blank space */
    for(col = 0; col < 49; col++) OLED_send(0x00);
    
    /* H */
    for(i = 0; i < 6; i++) OLED_send(letterH[i]);
    /* E */
    for(i = 0; i < 6; i++) OLED_send(letterE[i]);
    /* L */
    for(i = 0; i < 6; i++) OLED_send(letterL[i]);
    /* L */
    for(i = 0; i < 6; i++) OLED_send(letterL[i]);
    /* O */
    for(i = 0; i < 6; i++) OLED_send(letterO[i]);
    
    /* Fill rest with blank */
    for(col = 49 + 30; col < 128; col++) OLED_send(0x00);
    
    OLED_end();
}

/*******************************************************************************
 * Test 8: Scrolling animation
 ******************************************************************************/
void test_scroll(void)
{
    uint8_t page, col, offset;
    
    for(offset = 0; offset < 128; offset += 2) {
        for(page = 0; page < 8; page++) {
            OLED_data_start(page);
            for(col = 0; col < 128; col++) {
                /* Moving vertical bar */
                if(((col + offset) % 32) < 8) {
                    OLED_send(0xFF);
                } else {
                    OLED_send(0x00);
                }
            }
            OLED_end();
        }
        __delay_ms(30);
    }
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
void initMain(void)
{
    /* Initialize oscillator to 32MHz */
    internal_32();
    __delay_ms(100);

    /* Configure I2C pins */
    ANSELCbits.ANSC4 = 0;   /* Digital */
    ANSELCbits.ANSC5 = 0;   /* Digital */
    TRISCbits.TRISC4 = 1;   /* Input (I2C controls) */
    TRISCbits.TRISC5 = 1;   /* Input (I2C controls) */

    /* PPS Mapping for I2C */
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0;

    /* I2C Data on RC4 */
    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;

    /* I2C Clock on RC5 */
    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;
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
    I2C_Init();
    __delay_ms(50);
    
    /* Initialize OLED */
    OLED_init();
    __delay_ms(100);
    
    /* Clear screen */
    OLED_fill(0x00);
    __delay_ms(500);
    
    while(1)
    {
        /* Test 1: Solid white */
        test_fill_pattern(0xFF);
        __delay_ms(1000);
        
        /* Test 2: Solid black */
        test_fill_pattern(0x00);
        __delay_ms(500);
        
        /* Test 3: Vertical stripes pattern */
        test_fill_pattern(0xAA);
        __delay_ms(1000);
        
        /* Test 4: Horizontal bars */
        test_horizontal_bars();
        __delay_ms(1000);
        
        /* Test 5: Vertical bars */
        test_vertical_bars();
        __delay_ms(1000);
        
        /* Test 6: Checkerboard */
        test_checkerboard();
        __delay_ms(1000);
        
        /* Test 7: Border */
        test_border();
        __delay_ms(1000);
        
        /* Test 8: Smiley faces */
        test_smiley();
        __delay_ms(1500);
        
        /* Test 9: Hello text */
        test_hello();
        __delay_ms(1500);
        
        /* Test 10: Scrolling animation */
        test_scroll();
        __delay_ms(500);
    }
}
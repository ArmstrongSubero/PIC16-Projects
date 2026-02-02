/*
 * File: oled_min.c
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: Minimal SSD1306 OLED Driver for TinyJoypad Games
 * Compiler: XC8
 *
 * Description:
 * FAST minimal OLED functions - NO FRAMEBUFFER.
 * Uses direct register access for maximum speed during game rendering.
 * 
 * IMPORTANT: Set SSPADD = 7 in I2C_Init() for 1 MHz operation!
 */

#include "oled_min.h"
#include "PIC16F1718_Internal.h"
#include <xc.h>

/* I2C address with write bit */
#define OLED_ADDR_W     0x78    /* 0x3C << 1 */

/*******************************************************************************
 * FAST I2C Primitives - No timeout checks, minimal overhead
 * These are safe for OLED since we only write and the display always ACKs
 ******************************************************************************/

/* Wait for I2C operation to complete - tight polling */
#define I2C_WAIT()      while(!PIR1bits.SSP1IF); PIR1bits.SSP1IF = 0

/* Fast I2C Start */
static void I2C_Fast_Start(void)
{
    PIR1bits.SSP1IF = 0;
    SSPCON2bits.SEN = 1;
    I2C_WAIT();
}

/* Fast I2C Stop */
static void I2C_Fast_Stop(void)
{
    PIR1bits.SSP1IF = 0;
    SSPCON2bits.PEN = 1;
    I2C_WAIT();
}

/* Fast I2C Write - no ACK check, just blast data */
static void I2C_Fast_Write(uint8_t data)
{
    PIR1bits.SSP1IF = 0;
    SSPBUF = data;
    I2C_WAIT();
}

/*******************************************************************************
 * OLED Initialization Sequence for 128x64
 ******************************************************************************/
static const uint8_t OLED_INIT_CMD[] = {
    OLED_DISPLAY_OFF,
    OLED_MEMORYMODE, 0x00,          /* Horizontal addressing mode */
    OLED_COLUMNS, 0x00, 0x7F,
    OLED_PAGES, 0x00, 0x07,
    OLED_STARTLINE | 0x00,
    OLED_CONTRAST, 0xCF,            /* Higher contrast */
    OLED_XFLIP,
    OLED_INVERT_OFF,
    OLED_MULTIPLEX, 0x3F,
    OLED_YFLIP,
    OLED_OFFSET, 0x00,
    OLED_COMPINS, 0x12,
    OLED_CHARGEPUMP, 0x14,
    0xD5, 0x80,                     /* Set clock divide ratio */
    OLED_DISPLAY_ON
};

/*******************************************************************************
 * Function: void OLED_init(void)
 ******************************************************************************/
void OLED_init(void)
{
    uint8_t i;
    
    I2C_Fast_Start();
    I2C_Fast_Write(OLED_ADDR_W);
    I2C_Fast_Write(OLED_CMD_MODE);
    
    for(i = 0; i < sizeof(OLED_INIT_CMD); i++) {
        I2C_Fast_Write(OLED_INIT_CMD[i]);
    }
    
    I2C_Fast_Stop();
}

/*******************************************************************************
 * Function: void OLED_setpos(uint8_t x, uint8_t y)
 ******************************************************************************/
void OLED_setpos(uint8_t x, uint8_t y)
{
    I2C_Fast_Start();
    I2C_Fast_Write(OLED_ADDR_W);
    I2C_Fast_Write(OLED_CMD_MODE);
    I2C_Fast_Write(OLED_PAGE | (y & 0x07));
    I2C_Fast_Write(x & 0x0F);
    I2C_Fast_Write(OLED_COLUMN_HIGH | (x >> 4));
    I2C_Fast_Stop();
}

/*******************************************************************************
 * Function: void OLED_fill(uint8_t pattern)
 ******************************************************************************/
void OLED_fill(uint8_t pattern)
{
    uint16_t i;
    
    OLED_setpos(0, 0);
    
    I2C_Fast_Start();
    I2C_Fast_Write(OLED_ADDR_W);
    I2C_Fast_Write(OLED_DAT_MODE);
    
    for(i = 0; i < 1024; i++) {
        I2C_Fast_Write(pattern);
    }
    
    I2C_Fast_Stop();
}

/*******************************************************************************
 * Function: void OLED_data_start(uint8_t page)
 ******************************************************************************/
void OLED_data_start(uint8_t page)
{
    OLED_setpos(0, page);
    
    I2C_Fast_Start();
    I2C_Fast_Write(OLED_ADDR_W);
    I2C_Fast_Write(OLED_DAT_MODE);
}

/*******************************************************************************
 * Function: void OLED_send(uint8_t data)
 * 
 * INLINE for maximum speed during rendering loop
 ******************************************************************************/
void OLED_send(uint8_t data)
{
    PIR1bits.SSP1IF = 0;
    SSPBUF = data;
    while(!PIR1bits.SSP1IF);  /* Tight wait */
    PIR1bits.SSP1IF = 0;
}

/*******************************************************************************
 * Function: void OLED_end(void)
 ******************************************************************************/
void OLED_end(void)
{
    I2C_Fast_Stop();
}
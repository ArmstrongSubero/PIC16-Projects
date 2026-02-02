/*
 * File: oled_min.c
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: Minimal SSD1306 OLED Driver
 * Compiler: XC8
 *
 * Description:
 * Minimal OLED functions - NO FRAMEBUFFER.
 * Uses the existing I2C driver layer.
 */

#include "oled_min.h"
#include "I2C.h"

/*******************************************************************************
 * OLED Initialization Sequence for 128x64
 ******************************************************************************/
static const uint8_t OLED_INIT_CMD[] = {
    OLED_DISPLAY_OFF,               /* Display off during init */
    OLED_MEMORYMODE, 0x00,          /* Horizontal addressing mode */
    OLED_COLUMNS, 0x00, 0x7F,       /* Column start/end: 0-127 */
    OLED_PAGES, 0x00, 0x07,         /* Page start/end: 0-7 (for 64 pixels) */
    OLED_STARTLINE | 0x00,          /* Start line 0 */
    OLED_CONTRAST, 0x8F,            /* Contrast */
    OLED_XFLIP,                     /* Flip horizontally (segment remap) */
    OLED_INVERT_OFF,                /* Normal display (not inverted) */
    OLED_MULTIPLEX, 0x3F,           /* Multiplex ratio: 64 */
    OLED_YFLIP,                     /* Flip vertically (COM scan direction) */
    OLED_OFFSET, 0x00,              /* Display offset: 0 */
    OLED_COMPINS, 0x12,             /* COM pins config for 128x64 */
    OLED_CHARGEPUMP, 0x14,          /* Enable charge pump */
    OLED_DISPLAY_ON                 /* Display on */
};

/*******************************************************************************
 * Function: void OLED_init(void)
 *
 * Description:
 * Initialize the SSD1306 OLED display for 128x64 mode.
 * Assumes I2C is already initialized.
 ******************************************************************************/
void OLED_init(void)
{
    uint8_t i;
    
    I2C_Start();
    I2C_WriteByte(OLED_ADDR);           /* Address + Write */
    I2C_WriteByte(OLED_CMD_MODE);       /* Command mode */
    
    for (i = 0; i < sizeof(OLED_INIT_CMD); i++) {
        I2C_WriteByte(OLED_INIT_CMD[i]);
    }
    
    I2C_Stop();
}

/*******************************************************************************
 * Function: void OLED_setpos(uint8_t x, uint8_t y)
 *
 * Description:
 * Set cursor position. x = column (0-127), y = page (0-7)
 ******************************************************************************/
void OLED_setpos(uint8_t x, uint8_t y)
{
    I2C_Start();
    I2C_WriteByte(OLED_ADDR);
    I2C_WriteByte(OLED_CMD_MODE);
    I2C_WriteByte(OLED_PAGE | (y & 0x07));       /* Set page */
    I2C_WriteByte(x & 0x0F);                      /* Lower column nibble */
    I2C_WriteByte(OLED_COLUMN_HIGH | (x >> 4));   /* Upper column nibble */
    I2C_Stop();
}

/*******************************************************************************
 * Function: void OLED_fill(uint8_t pattern)
 *
 * Description:
 * Fill entire 128x64 screen with a byte pattern.
 ******************************************************************************/
void OLED_fill(uint8_t pattern)
{
    uint16_t i;
    
    OLED_setpos(0, 0);
    
    I2C_Start();
    I2C_WriteByte(OLED_ADDR);
    I2C_WriteByte(OLED_DAT_MODE);
    
    /* 128 columns x 8 pages = 1024 bytes */
    for (i = 0; i < 1024; i++) {
        I2C_WriteByte(pattern);
    }
    
    I2C_Stop();
}

/*******************************************************************************
 * Function: void OLED_data_start(uint8_t page)
 *
 * Description:
 * Begin sending pixel data for a specific page (row of 8 pixels high).
 * Call this, then send 128 bytes with OLED_send(), then call OLED_end().
 ******************************************************************************/
void OLED_data_start(uint8_t page)
{
    OLED_setpos(0, page);
    
    I2C_Start();
    I2C_WriteByte(OLED_ADDR);
    I2C_WriteByte(OLED_DAT_MODE);
}

/*******************************************************************************
 * Function: void OLED_send(uint8_t data)
 *
 * Description:
 * Send one byte of pixel data. Must be called between data_start and end.
 ******************************************************************************/
void OLED_send(uint8_t data)
{
    I2C_WriteByte(data);
}

/*******************************************************************************
 * Function: void OLED_end(void)
 *
 * Description:
 * End the data transmission. Call after sending all bytes for a page.
 ******************************************************************************/
void OLED_end(void)
{
    I2C_Stop();
}

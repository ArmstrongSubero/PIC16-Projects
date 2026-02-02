/*
 * File: oled_min.h
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: Minimal SSD1306 OLED Driver
 * Compiler: XC8
 *
 * Description:
 * Minimal OLED functions for games - NO FRAMEBUFFER.
 * Renders directly to display, saving ~1KB RAM.
 *
 * Hardware: SSD1306 128x64 OLED on I2C bus
 *           SDA -> RC4
 *           SCL -> RC5
 */

#ifndef OLED_MIN_H
#define OLED_MIN_H

#include <stdint.h>

/* OLED I2C address (7-bit 0x3C << 1 = 0x78) */
#define OLED_ADDR       0x78

/* Control bytes */
#define OLED_CMD_MODE   0x00    /* Command mode */
#define OLED_DAT_MODE   0x40    /* Data mode */

/* OLED commands */
#define OLED_COLUMN_LOW   0x00
#define OLED_COLUMN_HIGH  0x10
#define OLED_MEMORYMODE   0x20
#define OLED_COLUMNS      0x21
#define OLED_PAGES        0x22
#define OLED_STARTLINE    0x40
#define OLED_CONTRAST     0x81
#define OLED_CHARGEPUMP   0x8D
#define OLED_XFLIP_OFF    0xA0
#define OLED_XFLIP        0xA1
#define OLED_INVERT_OFF   0xA6
#define OLED_MULTIPLEX    0xA8
#define OLED_DISPLAY_OFF  0xAE
#define OLED_DISPLAY_ON   0xAF
#define OLED_PAGE         0xB0
#define OLED_YFLIP_OFF    0xC0
#define OLED_YFLIP        0xC8
#define OLED_OFFSET       0xD3
#define OLED_COMPINS      0xDA

/*******************************************************************************
 * Public API - Minimal functions for game rendering
 ******************************************************************************/

/* Initialize OLED for 128x64 display */
void OLED_init(void);

/* Set cursor position (page 0-7, column 0-127) */
void OLED_setpos(uint8_t x, uint8_t y);

/* Fill entire screen with pattern */
void OLED_fill(uint8_t pattern);

/* Start sending data bytes for a specific page (row) */
void OLED_data_start(uint8_t page);

/* Send a single data byte (pixel column) */
void OLED_send(uint8_t data);

/* End data transmission */
void OLED_end(void);

#endif /* OLED_MIN_H */

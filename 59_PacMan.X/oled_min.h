/*
 * File: oled_min.h
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: Minimal SSD1306 OLED Driver for TinyJoypad Games
 * Compiler: XC8
 *
 * Description:
 * FAST minimal OLED functions for games - NO FRAMEBUFFER.
 * Renders directly to display, saving ~1KB RAM.
 *
 * IMPORTANT: For acceptable game speed, set I2C to 400kHz:
 *            In I2C_Init(), change SSPADD = 79 to SSPADD = 19
 *
 * Hardware: SSD1306 128x64 OLED on I2C bus
 *           SDA -> RC4
 *           SCL -> RC5
 */

#ifndef OLED_MIN_H
#define OLED_MIN_H

#include <stdint.h>

/* OLED I2C address (directly used, no I2C layer needed for data writes) */
#define OLED_ADDR       0x78    /* 0x3C << 1 */

/* Control bytes */
#define OLED_CMD_MODE   0x00
#define OLED_DAT_MODE   0x40

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
 * Public API
 ******************************************************************************/

/* Initialize OLED (call I2C_Init() first!) */
void OLED_init(void);

/* Set cursor position */
void OLED_setpos(uint8_t x, uint8_t y);

/* Fill entire screen with pattern */
void OLED_fill(uint8_t pattern);

/* Start sending data for a page (0-7) */
void OLED_data_start(uint8_t page);

/* Send one data byte - FAST, no overhead */
void OLED_send(uint8_t data);

/* End data transmission */
void OLED_end(void);

#endif /* OLED_MIN_H */
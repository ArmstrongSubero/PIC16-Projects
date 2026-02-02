/*
 * File: OLED_SSD1306.h
 * Author: Armstrong Subero
 * MCU: PIC16F1718 / PIC16F1719
 * Display: SSD1306 OLED (I2C)
 * Compiler: XC8
 *
 * Program Description:
 * Driver for SSD1306 OLED displays using the PIC MSSP I2C driver layer.
 *
 * Notes:
 * - Uses PAGE addressing mode
 * - Screen buffer is maintained in RAM and pushed by line / partial updates.
 */

#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#ifndef OLED_WIDTH
#define OLED_WIDTH   128
#endif

#ifndef OLED_HEIGHT
#define OLED_HEIGHT  32    /* set 64 for 128x64 modules */
#endif

#define OLED_PAGES   (OLED_HEIGHT / 8)

/* 7-bit address is usually 0x3C or 0x3D depending on module wiring */
#ifndef SSD1306_ADDR7
#define SSD1306_ADDR7   0x3C
#endif

typedef enum {
    OLED_ORIENT_0 = 0,
    OLED_ORIENT_180,
    OLED_MIRROR_X,
    OLED_MIRROR_Y
} oled_orient_t;

/* Public API */
void OLED_Init(void);
void OLED_Clear(void);

void OLED_YX(uint8_t page, uint8_t col_char);
void OLED_WriteString(const char* s, uint8_t page, uint8_t col_char);

void OLED_UpdateLine(uint8_t page);
void OLED_UpdatePartialLine(uint8_t page, uint8_t start_col, uint8_t num_cols);

void OLED_Printf_Line(uint8_t line, const char* fmt, ...);
void OLED_DrawBattery(uint8_t percentage, uint8_t x, uint8_t page);

void OLED_SetOrientation(oled_orient_t o);

void OLED_ClearFast(void);

#endif

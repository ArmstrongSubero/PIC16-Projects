/*
 * File: OLED_SSD1306.c
 * Author: Armstrong Subero
 * MCU: PIC16F1718 / PIC16F1719
 * Display: SSD1306 OLED (I2C)
 * Compiler: XC8
 *
 * Program Description:
 * SSD1306 OLED driver using the driver-grade I2C layer.
 *
 * I2C Layer dependency:
 *  - I2C_Start(), I2C_RepeatedStart(), I2C_Stop()
 *  - I2C_WriteByte(), I2C_ReadByte()
 *  - I2C_Status_t returns I2C_OK on success
 * 
 * 28/12/25 Added support for %2u 
 */

#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/*******************************************************************************
 * Bitmaps / fonts
 *
 * Notes:
 * - Font must be ASCII 32..127, 8 bytes per character.
 ******************************************************************************/
/* ---- OLED Font ---- */
const uint8_t OledFont[][8] =
{
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
  {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
  {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
  {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
  {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
  {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
  {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
  {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
  {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
  {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
  {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
  {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
  {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
  {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
  {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
  {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
  {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
  {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
  {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
  {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
  {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
  {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
  {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
  {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
  {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
  {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
  {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
  {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
  {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
  {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
  {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
  {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
  {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
  {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
  {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
  {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
  {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
  {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
  {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
  {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
  {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
  {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
  {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
  {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
  {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
  {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
  {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
  {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
  {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
  {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
  {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
  {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
  {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
  {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
  {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
  {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
  {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
  {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
  {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
  {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
  {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
  {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
  {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
  {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
  {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
  {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
  {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00},
};

/* ---- A battery Icon bitmap array ---- */
const uint8_t BatteryIcon[10] = 
{
    0xFF, // 11111111  Top border of the larger battery
    0x81, // 10000001  Left and right borders
    0xBD, // 10111101  Fill partway for half-filled battery
    0xBD, // 10111101  Continue half-filled representation
    0xBD, // 10111101  Continue half-filled representation
    0x81, // 10000001  Left and right borders
    0xFF, // 11111111  Bottom border of the battery
    0x18, // 00011000  Small rectangle (knob) on the right side
    0x00, // 00000000  Empty space for padding
    0x00  // 00000000  Empty space for padding
};

/*******************************************************************************
 * Local screen buffer
 ******************************************************************************/
static uint8_t screen_buffer[OLED_PAGES][OLED_WIDTH];

/*******************************************************************************
 * SSD1306 Commands
 ******************************************************************************/
#define OLED_SETCONTRAST              0x81
#define OLED_DISPLAYALLON_RESUME      0xA4
#define OLED_NORMALDISPLAY            0xA6
#define OLED_DISPLAYOFF               0xAE
#define OLED_DISPLAYON                0xAF
#define OLED_SETDISPLAYOFFSET         0xD3
#define OLED_SETCOMPINS               0xDA
#define OLED_SETVCOMDETECT            0xDB
#define OLED_SETDISPLAYCLOCKDIV       0xD5
#define OLED_SETPRECHARGE             0xD9
#define OLED_SETMULTIPLEX             0xA8
#define OLED_SETSTARTLINE             0x40
#define OLED_MEMORYMODE               0x20
#define OLED_SEGREMAP                 0xA0
#define OLED_COMSCANINC               0xC0
#define OLED_COMSCANDEC               0xC8
#define OLED_CHARGEPUMP               0x8D
#define OLED_DEACTIVATE_SCROLL        0x2E

/*******************************************************************************
 * Local helpers: control bytes and address
 *
 * SSD1306 I2C format:
 * START -> SLA+W -> CONTROL -> DATA...
 * CONTROL = 0x00 for commands
 * CONTROL = 0x40 for data stream
 ******************************************************************************/
static uint8_t SSD1306_CtrlW(void) { return (uint8_t)((SSD1306_ADDR7 << 1) | 0); }

/*******************************************************************************
 * Function: static I2C_Status_t OLED_Command(uint8_t cmd)
 *
 * Description:
 * Send one command byte to the SSD1306.
 ******************************************************************************/
static I2C_Status_t OLED_Command(uint8_t cmd)
{
    I2C_Status_t st;

    st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte(SSD1306_CtrlW());
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte(0x00);          // control byte: command
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte(cmd);
    I2C_Stop();

    return st;
}

/*******************************************************************************
 * Function: static I2C_Status_t OLED_WriteData(const uint8_t* data, uint16_t len)
 *
 * Description:
 * Streams data bytes to the SSD1306.
 ******************************************************************************/
static I2C_Status_t OLED_WriteData(const uint8_t* data, uint16_t len)
{
    I2C_Status_t st;

    if (data == NULL) return I2C_TIMEOUT;

    st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte(SSD1306_CtrlW());
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte(0x40);          // control byte: data stream
    if (st != I2C_OK) { I2C_Stop(); return st; }

    for (uint16_t i = 0; i < len; i++)
    {
        st = I2C_WriteByte(data[i]);
        if (st != I2C_OK) { I2C_Stop(); return st; }
    }

    I2C_Stop();
    return I2C_OK;
}

/*******************************************************************************
 * Function: void OLED_SetOrientation(oled_orient_t o)
 *
 * Description:
 * Sets display orientation using SEGREMAP and COMSCAN.
 ******************************************************************************/
void OLED_SetOrientation(oled_orient_t o)
{
    (void)OLED_Command(OLED_DEACTIVATE_SCROLL);

    switch (o)
    {
        default:
        case OLED_ORIENT_0:
            (void)OLED_Command(OLED_SEGREMAP | 0x01);
            (void)OLED_Command(OLED_COMSCANDEC);
            break;

        case OLED_ORIENT_180:
            (void)OLED_Command(OLED_SEGREMAP | 0x00);
            (void)OLED_Command(OLED_COMSCANINC);
            break;

        case OLED_MIRROR_X:
            (void)OLED_Command(OLED_SEGREMAP | 0x00);
            (void)OLED_Command(OLED_COMSCANDEC);
            break;

        case OLED_MIRROR_Y:
            (void)OLED_Command(OLED_SEGREMAP | 0x01);
            (void)OLED_Command(OLED_COMSCANINC);
            break;
    }
}

/*******************************************************************************
 * Function: void OLED_YX(uint8_t page, uint8_t col_char)
 *
 * Description:
 * Page addressing positioning (B0..B7 + column low/high nibble).
 *
 * col_char is 8-pixel character columns (0..15 on 128px wide displays).
 ******************************************************************************/
void OLED_YX(uint8_t page, uint8_t col_char)
{
    uint8_t col = (uint8_t)(col_char * 8);

    (void)OLED_Command(0xB0 | (page & 0x07));
    (void)OLED_Command(0x00 | (col & 0x0F));
    (void)OLED_Command(0x10 | ((col >> 4) & 0x0F));
}

/*******************************************************************************
 * Function: void OLED_Init(void)
 *
 * Description:
 * Initializes SSD1306 for 128x32 (or 128x64 if OLED_HEIGHT is 64).
 ******************************************************************************/
void OLED_Init(void)
{
    __delay_ms(10);

    (void)OLED_Command(OLED_DISPLAYOFF);
    (void)OLED_Command(OLED_DEACTIVATE_SCROLL);

    (void)OLED_Command(OLED_SETDISPLAYCLOCKDIV);
    (void)OLED_Command(0x80);

    (void)OLED_Command(OLED_SETMULTIPLEX);
#if (OLED_HEIGHT == 64)
    (void)OLED_Command(0x3F);
#else
    (void)OLED_Command(0x1F);
#endif

    (void)OLED_Command(OLED_SETDISPLAYOFFSET);
    (void)OLED_Command(0x00);

    (void)OLED_Command(OLED_SETSTARTLINE | 0x00);

    (void)OLED_Command(OLED_CHARGEPUMP);
    (void)OLED_Command(0x14);                 // internal charge pump

    (void)OLED_Command(OLED_MEMORYMODE);
    (void)OLED_Command(0x02);                 // PAGE addressing

    (void)OLED_Command(OLED_SEGREMAP | 0x01);
    (void)OLED_Command(OLED_COMSCANDEC);

    (void)OLED_Command(OLED_SETCOMPINS);
#if (OLED_HEIGHT == 64)
    (void)OLED_Command(0x12);
#else
    (void)OLED_Command(0x02);
#endif

    (void)OLED_Command(OLED_SETCONTRAST);
    (void)OLED_Command(0x8F);

    (void)OLED_Command(OLED_SETPRECHARGE);
    (void)OLED_Command(0xF1);

    (void)OLED_Command(OLED_SETVCOMDETECT);
    (void)OLED_Command(0x40);

    (void)OLED_Command(OLED_DISPLAYALLON_RESUME);
    (void)OLED_Command(OLED_NORMALDISPLAY);
    (void)OLED_Command(OLED_DISPLAYON);

    /* Clear buffer + clear panel */
    OLED_Clear();
}

/*******************************************************************************
 * Function: void OLED_Clear(void)
 ******************************************************************************/
void OLED_Clear(void)
{
    for (uint8_t p = 0; p < OLED_PAGES; p++)
    {
        memset(screen_buffer[p], 0, OLED_WIDTH);

        OLED_YX(p, 0);
        (void)OLED_WriteData(screen_buffer[p], OLED_WIDTH);
    }
}

/*******************************************************************************
 * Function: void OLED_UpdateLine(uint8_t page)
 ******************************************************************************/
void OLED_UpdateLine(uint8_t page)
{
    if (page >= OLED_PAGES) return;

    OLED_YX(page, 0);
    (void)OLED_WriteData(screen_buffer[page], OLED_WIDTH);
}

/*******************************************************************************
 * Function: void OLED_UpdatePartialLine(uint8_t page, uint8_t start_col, uint8_t num_cols)
 ******************************************************************************/
void OLED_UpdatePartialLine(uint8_t page, uint8_t start_col, uint8_t num_cols)
{
    if (page >= OLED_PAGES || start_col >= OLED_WIDTH) return;
    if ((uint16_t)start_col + num_cols > OLED_WIDTH)
        num_cols = (uint8_t)(OLED_WIDTH - start_col);

    (void)OLED_Command(0xB0 | (page & 0x07));
    (void)OLED_Command(0x00 | (start_col & 0x0F));
    (void)OLED_Command(0x10 | ((start_col >> 4) & 0x0F));

    (void)OLED_WriteData(&screen_buffer[page][start_col], num_cols);
}

/*******************************************************************************
 * Function: void OLED_WriteString(const char* s, uint8_t page, uint8_t col_char)
 ******************************************************************************/
void OLED_WriteString(const char* s, uint8_t page, uint8_t col_char)
{
    if (s == NULL) return;

    OLED_YX(page, col_char);

    while (*s)
    {
        char ch = *s++;
        if (ch < 32 || ch > 127) ch = ' ';

        (void)OLED_WriteData(&OledFont[(uint8_t)(ch - 32)][0], 8);
    }
}

/*******************************************************************************
 * Function: void OLED_Printf_Line(uint8_t line, const char* fmt, ...)
 *
 * Description:
 * Writes formatted text into the screen buffer and updates the line.
 ******************************************************************************/
/*******************************************************************************
 * Function: void OLED_Printf_Line(uint8_t line, const char* fmt, ...)
 *
 * Description:
 * Lightweight printf replacement - supports %d, %u, %x, %s, %c only
 ******************************************************************************/
void OLED_Printf_Line(uint8_t line, const char* fmt, ...)
{
    static char last_text[8][32];
    char buf[32];
    char *dst = buf;
    const char *src = fmt;

    if (line >= OLED_PAGES) return;

    va_list ap;
    va_start(ap, fmt);

    // Simple format parser (+ supports %02u and %02d)
    while (*src && (dst - buf) < 31)
    {
        if (*src == '%')
        {
            src++;

            // --- handle optional "02" (zero pad width 2) ---
            uint8_t width2_zpad = 0;
            if (*src == '0')
            {
                const char *peek = src;
                peek++;
                if (*peek == '2')
                {
                    width2_zpad = 1;  // we saw "%02"
                    src += 2;         // consume '0' and '2'
                }
            }

            switch (*src)
            {
                case 'd':   // Signed decimal (supports %02d)
                {
                    int16_t val = va_arg(ap, int);

                    if (val < 0)
                    {
                        if ((dst - buf) < 31) *dst++ = '-';
                        val = -val;
                    }

                    // If %02d and value is 0..9, emit leading zero
                    if (width2_zpad && val < 10)
                    {
                        if ((dst - buf) < 31) *dst++ = '0';
                    }

                    char temp[6];
                    uint8_t i = 0;
                    do {
                        temp[i++] = '0' + (val % 10);
                        val /= 10;
                    } while (val && i < 6);

                    while (i-- && (dst - buf) < 31) *dst++ = temp[i];
                    break;
                }

                case 'l':   // %lu or %ld (no %02 support here)
                {
                    src++;
                    if (*src == 'u')
                    {
                        uint32_t val = va_arg(ap, uint32_t);
                        char temp[11];
                        uint8_t i = 0;
                        do {
                            temp[i++] = '0' + (val % 10);
                            val /= 10;
                        } while (val && i < 11);

                        while (i-- && (dst - buf) < 31) *dst++ = temp[i];
                    }
                    else if (*src == 'd')
                    {
                        int32_t val = va_arg(ap, int32_t);
                        if (val < 0)
                        {
                            if ((dst - buf) < 31) *dst++ = '-';
                            val = -val;
                        }

                        char temp[11];
                        uint8_t i = 0;
                        do {
                            temp[i++] = '0' + (val % 10);
                            val /= 10;
                        } while (val && i < 11);

                        while (i-- && (dst - buf) < 31) *dst++ = temp[i];
                    }
                    else
                    {
                        // Unknown format after %l
                        if ((dst - buf) < 31) *dst++ = '%';
                        if ((dst - buf) < 31) *dst++ = 'l';
                        if (*src && (dst - buf) < 31) *dst++ = *src;
                    }
                    break;
                }

                case 'u':   // Unsigned decimal (supports %02u)
                {
                    uint16_t val = va_arg(ap, unsigned int);

                    // If %02u and value is 0..9, emit leading zero
                    if (width2_zpad && val < 10)
                    {
                        if ((dst - buf) < 31) *dst++ = '0';
                    }

                    char temp[6];
                    uint8_t i = 0;
                    do {
                        temp[i++] = '0' + (val % 10);
                        val /= 10;
                    } while (val && i < 6);

                    while (i-- && (dst - buf) < 31) *dst++ = temp[i];
                    break;
                }

                case 'x':   // Hex (unchanged)
                {
                    uint16_t val = va_arg(ap, unsigned int);
                    char temp[5];
                    uint8_t i = 0;
                    do {
                        uint8_t nibble = val & 0xF;
                        temp[i++] = (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
                        val >>= 4;
                    } while (val && i < 5);

                    while (i-- && (dst - buf) < 31) *dst++ = temp[i];
                    break;
                }

                case 's':   // String
                {
                    const char *str = va_arg(ap, const char*);
                    while (*str && (dst - buf) < 31) *dst++ = *str++;
                    break;
                }

                case 'c':   // Character
                {
                    if ((dst - buf) < 31) *dst++ = (char)va_arg(ap, int);
                    break;
                }

                case '%':   // Literal %
                {
                    if ((dst - buf) < 31) *dst++ = '%';
                    break;
                }

                default:    // Unknown
                {
                    if ((dst - buf) < 31) *dst++ = '%';

                    // If we consumed "%02" but format was unknown, put it back visibly
                    if (width2_zpad)
                    {
                        if ((dst - buf) < 31) *dst++ = '0';
                        if ((dst - buf) < 31) *dst++ = '2';
                    }

                    if (*src && (dst - buf) < 31) *dst++ = *src;
                    break;
                }
            }

            if (*src) src++; // move past format specifier
        }
        else
        {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    va_end(ap);

    if (strcmp(buf, last_text[line]) == 0) return;
    strcpy(last_text[line], buf);

    /* Clear the buffer line */
    memset(screen_buffer[line], 0, OLED_WIDTH);

    /* Render text */
    uint8_t col = 0;
    for (const char* p = buf; *p && (col + 8) <= OLED_WIDTH; ++p)
    {
        char ch = *p;
        if (ch < 32 || ch > 127) ch = ' ';
        memcpy(&screen_buffer[line][col], &OledFont[(uint8_t)(ch - 32)][0], 8);
        col += 8;
    }

    OLED_UpdateLine(line);
}


/*******************************************************************************
 * Function: void OLED_DrawBattery(uint8_t percentage, uint8_t x, uint8_t page)
 ******************************************************************************/
void OLED_DrawBattery(uint8_t percentage, uint8_t x, uint8_t page)
{
    if (percentage > 100) percentage = 100;
    if (x + 8 > OLED_WIDTH || page >= OLED_PAGES) return;

    /* Draw outline first (this replaces, not ORs) */
    for (uint8_t i = 0; i < 8; i++) {
        screen_buffer[page][x + i] = BatteryIcon[i];  // Use = not |=
    }

    /* Fill level (inside only) - columns 1-6 */
    uint8_t fill_w = (percentage * 6) / 100;
    for (uint8_t i = 1; i <= fill_w && i <= 6; i++) {
        screen_buffer[page][x + i] = BatteryIcon[i] | 0x7E;  // Combine outline with fill
    }
}
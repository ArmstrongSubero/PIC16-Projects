<<<<<<< HEAD
/*******************************************************************************
 * File: Nokia5110.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup Nokia 5110 LCD module
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version 1.0
 *
 * Program Description: This program file is the header for the Nokia5110 LCD 
 *                      module
 *
 * Created on September 11th, 2018, 12:03 PM
 ******************************************************************************/
#include "16F1717_Internal.h"
#include "SPI.h"
 
//Define pins
#define SCE_5110   LATDbits.LATD0
#define RESET_5110 LATDbits.LATD1
#define DC_5110    LATDbits.LATD2

// LCD constants
#define LCD_X     84
#define LCD_Y     48
#define LCDWIDTH  84
#define LCDHEIGHT 48


/*******************************************************************************
 Function Prototypes
*******************************************************************************/
void LCD5110_init(void);
void LCD5110_send(unsigned char data, unsigned char dc);
void LCD5110_cls(unsigned char b_w);
void LCD5110_sendChar(unsigned char character);
void LCD5110_sendString(const unsigned char* str);
void LCD5110_writeInteger(int v);
char LCD5110_drawBitmap(const unsigned char y[]);
void LCD5110_drawBorder();
=======
/*******************************************************************************
 * File: Nokia5110.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup Nokia 5110 LCD module
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version 1.0
 *
 * Program Description: This program file is the header for the Nokia5110 LCD 
 *                      module
 *
 * Created on September 11th, 2018, 12:03 PM
 ******************************************************************************/
#include "16F1717_Internal.h"
#include "SPI.h"
 
//Define pins
#define SCE_5110   LATDbits.LATD0
#define RESET_5110 LATDbits.LATD1
#define DC_5110    LATDbits.LATD2

// LCD constants
#define LCD_X     84
#define LCD_Y     48
#define LCDWIDTH  84
#define LCDHEIGHT 48


/*******************************************************************************
 Function Prototypes
*******************************************************************************/
void LCD5110_init(void);
void LCD5110_send(unsigned char data, unsigned char dc);
void LCD5110_cls(unsigned char b_w);
void LCD5110_sendChar(unsigned char character);
void LCD5110_sendString(const unsigned char* str);
void LCD5110_writeInteger(int v);
char LCD5110_drawBitmap(const unsigned char y[]);
void LCD5110_drawBorder();
>>>>>>> 33af2e5a0186f497e5625d0fe67563444ebda689
void LCD5110_setPixel(int x, int y);
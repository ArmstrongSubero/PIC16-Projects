/*
 * File: LCD.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to 
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 *                *Added additional comments
 *                
 * Program Version 1.1
 *                *Added additional comments
 *                
 * Program Description: This program header provides routines for controlling
 *                      a STD HITACHI HD44780 and compatible LCD's
 * 
 * Hardware Description:
 * 
 * RS ---> RD2
 * R/W ---> GND
 * EN ---> RD3
 * D4 ---> RD4
 * D5 ---> RD5
 * D6 ---> RD6
 * D7 ---> RD7
 *                      
 *
 * Created on November 7th, 2016, 11:56 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
// STD XC8 include
#include <xc.h>

#define RS RD2  //Register Select (Character or Instruction)
#define EN RD3  //LCD Clock Enable PIN, Falling Edge Triggered

// 4 bit operation
#define D4 RD4  //Bit 4
#define D5 RD5  //Bit 5
#define D6 RD6  //Bit 6
#define D7 RD7  //Bit 7

// function prototypes
void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(const char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();
void Lcd_Write_Integer(int v);
void Lcd_Write_Float(float f);
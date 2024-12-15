/*
 * File: SC1601_LCD.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/X OSC @ 32 MHz, 5v
 * Program: Header file to 
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version 1.2
 *                *Added additional comments
 *                *Optimized for 32 MHz
 *                *Improved Readability
 *                
 * Program Description: This program header provides routines for controlling
 *                      a SC1601K LCD
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
 * Last Updated on December 14th, 2024, 11:16 PM
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

/*******************************************************************************
 * Core LCD Functions (Low-Level Hardware Interactions)
 ******************************************************************************/
void Lcd_Port(char a);            // Send data to LCD data pins
void Lcd_Cmd(char a);             // Send command to the LCD
void Lcd_Clear();                 // Clear the LCD screen
void Lcd_Set_Cursor(char a, char b); // Set cursor position
void Lcd_Init();                  // Initialize the LCD
void Lcd_Write_Char(char a);      // Write a single character to the LCD
void Lcd_Write_String(const char *a); // Write a string to the LCD

/*******************************************************************************
 * Cursor and Display Controls
 ******************************************************************************/
void Lcd_Blink_On();              // Enable cursor blink
void Lcd_Blink_Off();             // Disable cursor blink
void Lcd_Display_On();            // Turn LCD display ON
void Lcd_Display_Off();           // Turn LCD display OFF
void Lcd_Move_Cursor_Left();      // Move cursor left
void Lcd_Move_Cursor_Right();     // Move cursor right
void Lcd_Shift_Right();           // Shift all display text to the right
void Lcd_Shift_Left();            // Shift all display text to the left
void Lcd_Clear_Line(char row);    // Clear a specific line on the LCD

/*******************************************************************************
 * Data Display Functions
 ******************************************************************************/
void Lcd_Write_Integer(int v);    // Write an integer to the LCD
void Lcd_Write_Float(float f);    // Write a float to the LCD
void Lcd_Write_Padded_Integer(int num, int width); // Write padded integer

/*******************************************************************************
 * Advanced Text Handling
 ******************************************************************************/
void Lcd_Scroll_Text(const char *str);    // Scroll a long text message
void Lcd_Center_Text(char row, const char *str); // Center text on a specific line

/*******************************************************************************
 * Custom Characters
 ******************************************************************************/
void Lcd_Create_Char(unsigned char location, unsigned char charmap[]); // Create a custom character
void Lcd_Display_Custom_Char(unsigned char location);                  // Display a custom character

/*******************************************************************************
 * Additional Features
 ******************************************************************************/
void Lcd_Backlight_On();          // Turn on backlight
void Lcd_Backlight_Off();         // Turn off backlight
void Lcd_Reset();                 // Reset the LCD

/*******************************************************************************
 * Progress Bar
 ******************************************************************************/
void Lcd_Progress_Bar_Init();     // Initialize custom characters for the progress bar
void Lcd_Progress_Bar(int progress, int max); // Display a progress bar

/*******************************************************************************
 * Battery Indicator
 ******************************************************************************/
void Lcd_Battery_Init();          // Initialize custom characters for the battery indicator
void Lcd_Display_Battery(int percentage); // Display battery level with percentage

/*******************************************************************************
 * Signal Strength Indicator
 ******************************************************************************/
void Lcd_Signal_Init();           // Initialize custom characters for signal strength
void Lcd_Display_Signal(int level); // Display signal strength (e.g., no signal, weak, strong)

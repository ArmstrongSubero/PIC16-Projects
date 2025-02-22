/*
 * File: LCD.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.1
 *                *Added additional comments
 *                
 * Program Description: This Library allows you to interface HD44780 and 
 *                      compatible LCD's
 *                      
 * Created on November 7th, 2016, 11:55 AM
 * Updated on March 3rd, 2024, 10:20 PM
 */


#include "LCD.h"
#include "PIC16F1719_Internal.h"
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Function: void Lcd_Port (char a)
 *
 * Returns: Nothing
 *
 * Description: LCD Setup Routines
 ******************************************************************************/

void Lcd_Port(char a)
{
   if(a & 1)
      D4 = 1;
   else
      D4 = 0;

   if(a & 2)
      D5 = 1;
   else
      D5 = 0;

   if(a & 4)
      D6 = 1;
   else
      D6 = 0;

   if(a & 8)
      D7 = 1;
   else
      D7 = 0;
}

/*******************************************************************************
 * Function: void Lcd_Cmd (char a)
 *
 * Returns: Nothing
 *
 * Description: Sets LCD command
 ******************************************************************************/

void Lcd_Cmd(char a)
{
   RS = 0;             // => RS = 0
   Lcd_Port(a);
   EN  = 1;             // => E = 1
        __delay_ms(1);
        EN  = 0;             // => E = 0
}

/*******************************************************************************
 * Function: void Lcd_Clear()
 *
 * Returns: Nothing
 *
 * Description: Clears the LCD
 ******************************************************************************/

void Lcd_Clear()
{
   Lcd_Cmd(0);
   Lcd_Cmd(1);
}

/*******************************************************************************
 * Function: void Lcd_Set_Cursor(char a, char b)
 *
 * Returns: Nothing
 *
 * Description: Sets the LCD cursor position
 ******************************************************************************/

void Lcd_Set_Cursor(char a, char b)
{
   char temp,z,y;
   if(a == 1)
   {
     temp = 0x80 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
   else if(a == 2)
   {
      temp = 0xC0 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
}

/*******************************************************************************
 * Function: void Lcd_Init()
 *
 * Returns: Nothing
 *
 * Description: Initialises the LCD
 ******************************************************************************/

void Lcd_Init()
{
  Lcd_Port(0x00);
   __delay_ms(10);
  Lcd_Cmd(0x03);
   __delay_ms(3);
  Lcd_Cmd(0x03);
   __delay_ms(10);
  Lcd_Cmd(0x03);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}

/*******************************************************************************
 * Function: void Lcd_Write_Char (char a)
 *
 * Returns: Nothing
 *
 * Description: Writes a character to the LCD
 ******************************************************************************/

void Lcd_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(20);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(20);
   EN = 0;
}

/*******************************************************************************
 * Function: void Lcd_Write_String (const char *a)
 *
 * Returns: Nothing
 *
 * Description: Writes a string to the LCD
 ******************************************************************************/

void Lcd_Write_String(const char *a)
{
   int i;
   for(i=0;a[i]!='\0';i++)
      Lcd_Write_Char(a[i]);
}

/*******************************************************************************
 * Function: void Lcd_Shift_Right()
 *
 * Returns: Nothing
 *
 * Description: Shifts text on the LCD right
 ******************************************************************************/

void Lcd_Shift_Right()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x0C);
}

/*******************************************************************************
 * Function: void Lcd_Shift_Left()
 *
 * Returns: Nothing
 *
 * Description: Shifts text on the LCD left
 ******************************************************************************/

void Lcd_Shift_Left()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x08);
}


/*******************************************************************************
 * Function: void Lcd_Write_Integer(int v)
 *
 * Returns: Nothing
 *
 * Description: Converts a string to an integer
 ******************************************************************************/

// A simple itoa function for base 10 conversion
char* c_itoa(int value, char* result, int base) {
    // Check that the base is valid
    if (base < 2 || base > 36) { 
        *result = '\0'; 
        return result; 
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    // Handle negative values if necessary
    if (value < 0 && base == 10) {
        *ptr++ = '-';
    }

    ptr1 = ptr;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply terminating null character
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}



void Lcd_Write_Integer(int v)
{
    unsigned char buf[8];

    Lcd_Write_String(c_itoa(buf, v, 10));
}


/*******************************************************************************
 * Function: void Lcd_Write_Float(float f)
 *
 * Returns: Nothing
 *
 * Description: Converts a string to a float
 ******************************************************************************/


char * c_ftoa(float f, int * status)
{
    static char buf[17];
    char * cp = buf;
    unsigned long l, rem;
 
    if(f < 0) {
        *cp++ = '-';
        f = -f;
    }
    l = (unsigned long)f;
    f -= (float)l;
    rem = (unsigned long)(f * 1e6);
    sprintf(cp, "%lu.%6.6lu", l, rem);
    return buf;
}


void Lcd_Write_Float(float f)
{
    char* buf11;
    int status;

    buf11 = c_ftoa(f, &status);

    Lcd_Write_String(buf11);
}

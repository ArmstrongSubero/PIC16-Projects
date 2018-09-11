<<<<<<< HEAD
/*
 * File: 16F1717_STD.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to use a Nokia5110 LCD module
 *                      
 * Created on September 11th, 2010, 12:01 PM
 */


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "Nokia5110.h"

/*******************************************************************************
* Name:
* font[]
*
* Description:
* Holds data for font to be displayed on Nokia 5110 LCD
*******************************************************************************/
const char font[] = {0x00, 0x00, 0x00, 0x00, 0x00, // 20 space
    0x00, 0x00, 0x5f, 0x00, 0x00, // 21 !
    0x00, 0x07, 0x00, 0x07, 0x00, // 22 "
    0x14, 0x7f, 0x14, 0x7f, 0x14, // 23 #
    0x24, 0x2a, 0x7f, 0x2a, 0x12, // 24 $
    0x23, 0x13, 0x08, 0x64, 0x62, // 25 %
    0x36, 0x49, 0x55, 0x22, 0x50, // 26 &
    0x00, 0x05, 0x03, 0x00, 0x00, // 27 '
    0x00, 0x1c, 0x22, 0x41, 0x00, // 28 (
    0x00, 0x41, 0x22, 0x1c, 0x00, // 29 )
    0x14, 0x08, 0x3e, 0x08, 0x14, // 2a *
    0x08, 0x08, 0x3e, 0x08, 0x08, // 2b +
    0x00, 0x50, 0x30, 0x00, 0x00, // 2c ,
    0x08, 0x08, 0x08, 0x08, 0x08, // 2d -
    0x00, 0x60, 0x60, 0x00, 0x00, // 2e .
    0x20, 0x10, 0x08, 0x04, 0x02, // 2f /
    0x3e, 0x51, 0x49, 0x45, 0x3e, // 30 0
    0x00, 0x42, 0x7f, 0x40, 0x00, // 31 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 32 2
    0x21, 0x41, 0x45, 0x4b, 0x31, // 33 3
    0x18, 0x14, 0x12, 0x7f, 0x10, // 34 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 35 5
    0x3c, 0x4a, 0x49, 0x49, 0x30, // 36 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 37 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 38 8
    0x06, 0x49, 0x49, 0x29, 0x1e, // 39 9
    0x00, 0x36, 0x36, 0x00, 0x00, // 3a :
    0x00, 0x56, 0x36, 0x00, 0x00, // 3b ;
    0x08, 0x14, 0x22, 0x41, 0x00, // 3c <
    0x14, 0x14, 0x14, 0x14, 0x14, // 3d =
    0x00, 0x41, 0x22, 0x14, 0x08, // 3e >
    0x02, 0x01, 0x51, 0x09, 0x06, // 3f ?
    0x32, 0x49, 0x79, 0x41, 0x3e, // 40 @
    0x7e, 0x11, 0x11, 0x11, 0x7e, // 41 A
    0x7f, 0x49, 0x49, 0x49, 0x36, // 42 B
    0x3e, 0x41, 0x41, 0x41, 0x22, // 43 C
    0x7f, 0x41, 0x41, 0x22, 0x1c, // 44 D
    0x7f, 0x49, 0x49, 0x49, 0x41, // 45 E
    0x7f, 0x09, 0x09, 0x09, 0x01, // 46 F
    0x3e, 0x41, 0x49, 0x49, 0x7a, // 47 G
    0x7f, 0x08, 0x08, 0x08, 0x7f, // 48 H
    0x00, 0x41, 0x7f, 0x41, 0x00, // 49 I
    0x20, 0x40, 0x41, 0x3f, 0x01, // 4a J
    0x7f, 0x08, 0x14, 0x22, 0x41, // 4b K
    0x7f, 0x40, 0x40, 0x40, 0x40, // 4c L
    0x7f, 0x02, 0x0c, 0x02, 0x7f, // 4d M
    0x7f, 0x04, 0x08, 0x10, 0x7f, // 4e N
    0x3e, 0x41, 0x41, 0x41, 0x3e, // 4f O
    0x7f, 0x09, 0x09, 0x09, 0x06, // 50 P
    0x3e, 0x41, 0x51, 0x21, 0x5e, // 51 Q
    0x7f, 0x09, 0x19, 0x29, 0x46, // 52 R
    0x46, 0x49, 0x49, 0x49, 0x31, // 53 S
    0x01, 0x01, 0x7f, 0x01, 0x01, // 54 T
    0x3f, 0x40, 0x40, 0x40, 0x3f, // 55 U
    0x1f, 0x20, 0x40, 0x20, 0x1f, // 56 V
    0x3f, 0x40, 0x38, 0x40, 0x3f, // 57 W
    0x63, 0x14, 0x08, 0x14, 0x63, // 58 X
    0x07, 0x08, 0x70, 0x08, 0x07, // 59 Y
    0x61, 0x51, 0x49, 0x45, 0x43, // 5a Z
    0x00, 0x7f, 0x41, 0x41, 0x00, // 5b [
    0x02, 0x04, 0x08, 0x10, 0x20, // 5c 55
    0x00, 0x41, 0x41, 0x7f, 0x00, // 5d ]
    0x04, 0x02, 0x01, 0x02, 0x04, // 5e ^
    0x40, 0x40, 0x40, 0x40, 0x40, // 5f _
    0x00, 0x01, 0x02, 0x04, 0x00, // 60 `
    0x20, 0x54, 0x54, 0x54, 0x78, // 61 a
    0x7f, 0x48, 0x44, 0x44, 0x38, // 62 b
    0x38, 0x44, 0x44, 0x44, 0x20, // 63 c
    0x38, 0x44, 0x44, 0x48, 0x7f, // 64 d
    0x38, 0x54, 0x54, 0x54, 0x18, // 65 e
    0x08, 0x7e, 0x09, 0x01, 0x02, // 66 f
    0x0c, 0x52, 0x52, 0x52, 0x3e, // 67 g
    0x7f, 0x08, 0x04, 0x04, 0x78, // 68 h
    0x00, 0x44, 0x7d, 0x40, 0x00, // 69 i
    0x20, 0x40, 0x44, 0x3d, 0x00, // 6a j
    0x7f, 0x10, 0x28, 0x44, 0x00, // 6b k
    0x00, 0x41, 0x7f, 0x40, 0x00, // 6c l
    0x7c, 0x04, 0x18, 0x04, 0x78, // 6d m
    0x7c, 0x08, 0x04, 0x04, 0x78, // 6e n
    0x38, 0x44, 0x44, 0x44, 0x38, // 6f o
    0x7c, 0x14, 0x14, 0x14, 0x08, // 70 p
    0x08, 0x14, 0x14, 0x18, 0x7c, // 71 q
    0x7c, 0x08, 0x04, 0x04, 0x08, // 72 r
    0x48, 0x54, 0x54, 0x54, 0x20, // 73 s
    0x04, 0x3f, 0x44, 0x40, 0x20, // 74 t
    0x3c, 0x40, 0x40, 0x20, 0x7c, // 75 u
    0x1c, 0x20, 0x40, 0x20, 0x1c, // 76 v
    0x3c, 0x40, 0x30, 0x40, 0x3c, // 77 w
    0x44, 0x28, 0x10, 0x28, 0x44, // 78 x
    0x0c, 0x50, 0x50, 0x50, 0x3c, // 79 y
    0x44, 0x64, 0x54, 0x4c, 0x44, // 7a z
    0x00, 0x08, 0x36, 0x41, 0x00, // 7b {
    0x00, 0x00, 0x7f, 0x00, 0x00, // 7c |
    0x00, 0x41, 0x36, 0x08, 0x00, // 7d }
    0x10, 0x08, 0x08, 0x10, 0x08, // 7e ~
    0x78, 0x46, 0x41, 0x46, 0x78};

/*******************************************************************************
* Function: SPI1_transfer(char b)
*
* Returns: SP1BUF
*
* Description: Sends data via SPI
*
*******************************************************************************/

char SPI1_transfer(char b)
{
   SPI_Exchange8bit(b);
}


/*******************************************************************************
* Function: void LCD5110_init (void)
*
* Returns: Nothing
*
* Description: Initilize the LCD
*
*******************************************************************************/

void LCD5110_init(void)
{
    __delay_ms(20);
    SCE_5110 = 0; // Enable the 5110 device (Active Low)
    RESET_5110 = 0; // Reset the device
    __delay_ms(20); // Delay 20ms for stabilization
    RESET_5110 = 1;

    LCD5110_send(0x20 + 0x01, 0); // Extended instructions enabled
    LCD5110_send(0x80 + 0x40, 0); // Set contrast 0 - 127
    LCD5110_send(0x04 + 0x02, 0); // Temperature control
    LCD5110_send(0x10 + 0x03, 0); // Set bias system
    LCD5110_send(0x20 + 0x00, 0); // Power on, set horizontal addressing
    LCD5110_send(0x08 + 0x04, 0); // Display control set to normal mode
}

/*******************************************************************************
* Function: void LCD5110_send(unsigned char data, unsigned char dc)
*
* Returns: Nothing
*
* Description: Sends data to the LCD taking data and data/command as args
*
*******************************************************************************/

void LCD5110_send(unsigned char data, unsigned char dc)
{
    DC_5110 = dc; //command=0 or data=1
    SPI1_transfer(data);
}


/*******************************************************************************
* Function: void set_xy(int x, int y)
*
* Returns: Nothing
*
* Description: Sets X and Y coordinates
*
*******************************************************************************/

void set_xy(int x, int y)
{
  LCD5110_send(0x80 | x, 0);  // Column.
  LCD5110_send(0x40 | y, 0);  // Row.
}


/*******************************************************************************
* Function: LCD5110_clearScreen(void)
*
* Returns: Nothing
*
* Description: clears the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_clearScreen(void)
{
  int index;
  for (index = 0; index < LCD_X * LCD_Y / 8; index++) {
    LCD5110_send(0x00, 1);
  }
   set_xy(0,0);
}

/*******************************************************************************
* Function: void LCD5110_sendChar(unsigned char character)
*
* Returns: Nothing
*
* Description: Sends a character to the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_sendChar(unsigned char character)
{
    unsigned char column = 0;
    character = character - 0x20; // 0x20 is the first element of the array

    for (column = 0; column < 5; column++) // Pass through each column
    {
        LCD5110_send(font[(int) character * 5 + column], 1);
    }

    LCD5110_send(0x00, 1); // Send a small space
}


/*******************************************************************************
* Function: void LCD_sendString(const unsigned char *str)
*
* Returns: Nothing
*
* Description: Sends a string to the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_sendString(const unsigned char *str)
{
    while (*str) // pass through each character
    {
        LCD5110_sendChar(*str); // and send it
        str++;
    }
}


/*******************************************************************************
* Function: void LCD5110_writeInteger(int v)
*
* Returns: Nothing
*
* Description: Writes and integer to the Nokai 5110 LCD
*
*******************************************************************************/

void LCD5110_writeInteger(int v)
{
    unsigned char buf[8];

    LCD5110_sendString(itoa(buf, v, 10));
}


/*******************************************************************************
* Function: char LCD5110_drawBitmap(const unsigned char y[])
*
* Returns: Nothing
*
* Description: Draws a Bitmap to the Nokia 5110 LCD
*
*******************************************************************************/

char LCD5110_drawBitmap(const unsigned char y[])
{
   unsigned int i=0;
   while(i<504){
      LCD5110_send(y[i], 1);
      i++;
   }
}

/*******************************************************************************
* Function: void LCD5110_drawBorder()
*
* Returns: Nothing
*
* Description: Draws a border (box) on the LCD
*
*******************************************************************************/

void LCD5110_drawBorder()
{
    unsigned char j;
    for(j=0; j<84; j++) // top
	{
          set_xy (j,0);
	  LCD5110_send (1, 1);
  }
    
   for(j=0; j<84; j++) //Bottom
	{
          set_xy (j,5);
	  LCD5110_send (128, 1);
  }

  for(j=0; j<10; j++) // Right
	{
          set_xy (83,j);
	  LCD5110_send (255, 1);
  }

  for(j=0; j<10; j++) // Left
	{
          set_xy (0,j);
	  LCD5110_send (255, 1);
  }
}



/*******************************************************************************
* Function: LCD5110_setPixel(int x, int y)
*
* Returns: Nothing
*
* Description: Writes an individual pixel to the LCD
*
*******************************************************************************/

void LCD5110_setPixel(int x, int y)
{
  int y_mod = (int)(y >> 3);    // >>3 divides by 8
  int y_pix = (y-(y_mod << 3)); // <<3 multiplies by 8
  int val = 1 << y_pix;         //1<< y_pix

  // Write the pixel out to the LCD
  set_xy(x,y_mod);
  LCD5110_send (val, 1);
}
=======
/*
 * File: 16F1717_STD.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to use a Nokia5110 LCD module
 *                      
 * Created on September 11th, 2010, 12:01 PM
 */


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "Nokia5110.h"

/*******************************************************************************
* Name:
* font[]
*
* Description:
* Holds data for font to be displayed on Nokia 5110 LCD
*******************************************************************************/
const char font[] = {0x00, 0x00, 0x00, 0x00, 0x00, // 20 space
    0x00, 0x00, 0x5f, 0x00, 0x00, // 21 !
    0x00, 0x07, 0x00, 0x07, 0x00, // 22 "
    0x14, 0x7f, 0x14, 0x7f, 0x14, // 23 #
    0x24, 0x2a, 0x7f, 0x2a, 0x12, // 24 $
    0x23, 0x13, 0x08, 0x64, 0x62, // 25 %
    0x36, 0x49, 0x55, 0x22, 0x50, // 26 &
    0x00, 0x05, 0x03, 0x00, 0x00, // 27 '
    0x00, 0x1c, 0x22, 0x41, 0x00, // 28 (
    0x00, 0x41, 0x22, 0x1c, 0x00, // 29 )
    0x14, 0x08, 0x3e, 0x08, 0x14, // 2a *
    0x08, 0x08, 0x3e, 0x08, 0x08, // 2b +
    0x00, 0x50, 0x30, 0x00, 0x00, // 2c ,
    0x08, 0x08, 0x08, 0x08, 0x08, // 2d -
    0x00, 0x60, 0x60, 0x00, 0x00, // 2e .
    0x20, 0x10, 0x08, 0x04, 0x02, // 2f /
    0x3e, 0x51, 0x49, 0x45, 0x3e, // 30 0
    0x00, 0x42, 0x7f, 0x40, 0x00, // 31 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 32 2
    0x21, 0x41, 0x45, 0x4b, 0x31, // 33 3
    0x18, 0x14, 0x12, 0x7f, 0x10, // 34 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 35 5
    0x3c, 0x4a, 0x49, 0x49, 0x30, // 36 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 37 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 38 8
    0x06, 0x49, 0x49, 0x29, 0x1e, // 39 9
    0x00, 0x36, 0x36, 0x00, 0x00, // 3a :
    0x00, 0x56, 0x36, 0x00, 0x00, // 3b ;
    0x08, 0x14, 0x22, 0x41, 0x00, // 3c <
    0x14, 0x14, 0x14, 0x14, 0x14, // 3d =
    0x00, 0x41, 0x22, 0x14, 0x08, // 3e >
    0x02, 0x01, 0x51, 0x09, 0x06, // 3f ?
    0x32, 0x49, 0x79, 0x41, 0x3e, // 40 @
    0x7e, 0x11, 0x11, 0x11, 0x7e, // 41 A
    0x7f, 0x49, 0x49, 0x49, 0x36, // 42 B
    0x3e, 0x41, 0x41, 0x41, 0x22, // 43 C
    0x7f, 0x41, 0x41, 0x22, 0x1c, // 44 D
    0x7f, 0x49, 0x49, 0x49, 0x41, // 45 E
    0x7f, 0x09, 0x09, 0x09, 0x01, // 46 F
    0x3e, 0x41, 0x49, 0x49, 0x7a, // 47 G
    0x7f, 0x08, 0x08, 0x08, 0x7f, // 48 H
    0x00, 0x41, 0x7f, 0x41, 0x00, // 49 I
    0x20, 0x40, 0x41, 0x3f, 0x01, // 4a J
    0x7f, 0x08, 0x14, 0x22, 0x41, // 4b K
    0x7f, 0x40, 0x40, 0x40, 0x40, // 4c L
    0x7f, 0x02, 0x0c, 0x02, 0x7f, // 4d M
    0x7f, 0x04, 0x08, 0x10, 0x7f, // 4e N
    0x3e, 0x41, 0x41, 0x41, 0x3e, // 4f O
    0x7f, 0x09, 0x09, 0x09, 0x06, // 50 P
    0x3e, 0x41, 0x51, 0x21, 0x5e, // 51 Q
    0x7f, 0x09, 0x19, 0x29, 0x46, // 52 R
    0x46, 0x49, 0x49, 0x49, 0x31, // 53 S
    0x01, 0x01, 0x7f, 0x01, 0x01, // 54 T
    0x3f, 0x40, 0x40, 0x40, 0x3f, // 55 U
    0x1f, 0x20, 0x40, 0x20, 0x1f, // 56 V
    0x3f, 0x40, 0x38, 0x40, 0x3f, // 57 W
    0x63, 0x14, 0x08, 0x14, 0x63, // 58 X
    0x07, 0x08, 0x70, 0x08, 0x07, // 59 Y
    0x61, 0x51, 0x49, 0x45, 0x43, // 5a Z
    0x00, 0x7f, 0x41, 0x41, 0x00, // 5b [
    0x02, 0x04, 0x08, 0x10, 0x20, // 5c 55
    0x00, 0x41, 0x41, 0x7f, 0x00, // 5d ]
    0x04, 0x02, 0x01, 0x02, 0x04, // 5e ^
    0x40, 0x40, 0x40, 0x40, 0x40, // 5f _
    0x00, 0x01, 0x02, 0x04, 0x00, // 60 `
    0x20, 0x54, 0x54, 0x54, 0x78, // 61 a
    0x7f, 0x48, 0x44, 0x44, 0x38, // 62 b
    0x38, 0x44, 0x44, 0x44, 0x20, // 63 c
    0x38, 0x44, 0x44, 0x48, 0x7f, // 64 d
    0x38, 0x54, 0x54, 0x54, 0x18, // 65 e
    0x08, 0x7e, 0x09, 0x01, 0x02, // 66 f
    0x0c, 0x52, 0x52, 0x52, 0x3e, // 67 g
    0x7f, 0x08, 0x04, 0x04, 0x78, // 68 h
    0x00, 0x44, 0x7d, 0x40, 0x00, // 69 i
    0x20, 0x40, 0x44, 0x3d, 0x00, // 6a j
    0x7f, 0x10, 0x28, 0x44, 0x00, // 6b k
    0x00, 0x41, 0x7f, 0x40, 0x00, // 6c l
    0x7c, 0x04, 0x18, 0x04, 0x78, // 6d m
    0x7c, 0x08, 0x04, 0x04, 0x78, // 6e n
    0x38, 0x44, 0x44, 0x44, 0x38, // 6f o
    0x7c, 0x14, 0x14, 0x14, 0x08, // 70 p
    0x08, 0x14, 0x14, 0x18, 0x7c, // 71 q
    0x7c, 0x08, 0x04, 0x04, 0x08, // 72 r
    0x48, 0x54, 0x54, 0x54, 0x20, // 73 s
    0x04, 0x3f, 0x44, 0x40, 0x20, // 74 t
    0x3c, 0x40, 0x40, 0x20, 0x7c, // 75 u
    0x1c, 0x20, 0x40, 0x20, 0x1c, // 76 v
    0x3c, 0x40, 0x30, 0x40, 0x3c, // 77 w
    0x44, 0x28, 0x10, 0x28, 0x44, // 78 x
    0x0c, 0x50, 0x50, 0x50, 0x3c, // 79 y
    0x44, 0x64, 0x54, 0x4c, 0x44, // 7a z
    0x00, 0x08, 0x36, 0x41, 0x00, // 7b {
    0x00, 0x00, 0x7f, 0x00, 0x00, // 7c |
    0x00, 0x41, 0x36, 0x08, 0x00, // 7d }
    0x10, 0x08, 0x08, 0x10, 0x08, // 7e ~
    0x78, 0x46, 0x41, 0x46, 0x78};

/*******************************************************************************
* Function: SPI1_transfer(char b)
*
* Returns: SP1BUF
*
* Description: Sends data via SPI
*
*******************************************************************************/

char SPI1_transfer(char b)
{
   SPI_Exchange8bit(b);
}


/*******************************************************************************
* Function: void LCD5110_init (void)
*
* Returns: Nothing
*
* Description: Initilize the LCD
*
*******************************************************************************/

void LCD5110_init(void)
{
    __delay_ms(20);
    SCE_5110 = 0; // Enable the 5110 device (Active Low)
    RESET_5110 = 0; // Reset the device
    __delay_ms(20); // Delay 20ms for stabilization
    RESET_5110 = 1;

    LCD5110_send(0x20 + 0x01, 0); // Extended instructions enabled
    LCD5110_send(0x80 + 0x40, 0); // Set contrast 0 - 127
    LCD5110_send(0x04 + 0x02, 0); // Temperature control
    LCD5110_send(0x10 + 0x03, 0); // Set bias system
    LCD5110_send(0x20 + 0x00, 0); // Power on, set horizontal addressing
    LCD5110_send(0x08 + 0x04, 0); // Display control set to normal mode
}

/*******************************************************************************
* Function: void LCD5110_send(unsigned char data, unsigned char dc)
*
* Returns: Nothing
*
* Description: Sends data to the LCD taking data and data/command as args
*
*******************************************************************************/

void LCD5110_send(unsigned char data, unsigned char dc)
{
    DC_5110 = dc; //command=0 or data=1
    SPI1_transfer(data);
}


/*******************************************************************************
* Function: void set_xy(int x, int y)
*
* Returns: Nothing
*
* Description: Sets X and Y coordinates
*
*******************************************************************************/

void set_xy(int x, int y)
{
  LCD5110_send(0x80 | x, 0);  // Column.
  LCD5110_send(0x40 | y, 0);  // Row.
}


/*******************************************************************************
* Function: LCD5110_clearScreen(void)
*
* Returns: Nothing
*
* Description: clears the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_clearScreen(void)
{
  int index;
  for (index = 0; index < LCD_X * LCD_Y / 8; index++) {
    LCD5110_send(0x00, 1);
  }
   set_xy(0,0);
}

/*******************************************************************************
* Function: void LCD5110_sendChar(unsigned char character)
*
* Returns: Nothing
*
* Description: Sends a character to the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_sendChar(unsigned char character)
{
    unsigned char column = 0;
    character = character - 0x20; // 0x20 is the first element of the array

    for (column = 0; column < 5; column++) // Pass through each column
    {
        LCD5110_send(font[(int) character * 5 + column], 1);
    }

    LCD5110_send(0x00, 1); // Send a small space
}


/*******************************************************************************
* Function: void LCD_sendString(const unsigned char *str)
*
* Returns: Nothing
*
* Description: Sends a string to the Nokia 5110 LCD
*
*******************************************************************************/

void LCD5110_sendString(const unsigned char *str)
{
    while (*str) // pass through each character
    {
        LCD5110_sendChar(*str); // and send it
        str++;
    }
}


/*******************************************************************************
* Function: void LCD5110_writeInteger(int v)
*
* Returns: Nothing
*
* Description: Writes and integer to the Nokai 5110 LCD
*
*******************************************************************************/

void LCD5110_writeInteger(int v)
{
    unsigned char buf[8];

    LCD5110_sendString(itoa(buf, v, 10));
}


/*******************************************************************************
* Function: char LCD5110_drawBitmap(const unsigned char y[])
*
* Returns: Nothing
*
* Description: Draws a Bitmap to the Nokia 5110 LCD
*
*******************************************************************************/

char LCD5110_drawBitmap(const unsigned char y[])
{
   unsigned int i=0;
   while(i<504){
      LCD5110_send(y[i], 1);
      i++;
   }
}

/*******************************************************************************
* Function: void LCD5110_drawBorder()
*
* Returns: Nothing
*
* Description: Draws a border (box) on the LCD
*
*******************************************************************************/

void LCD5110_drawBorder()
{
    unsigned char j;
    for(j=0; j<84; j++) // top
	{
          set_xy (j,0);
	  LCD5110_send (1, 1);
  }
    
   for(j=0; j<84; j++) //Bottom
	{
          set_xy (j,5);
	  LCD5110_send (128, 1);
  }

  for(j=0; j<10; j++) // Right
	{
          set_xy (83,j);
	  LCD5110_send (255, 1);
  }

  for(j=0; j<10; j++) // Left
	{
          set_xy (0,j);
	  LCD5110_send (255, 1);
  }
}



/*******************************************************************************
* Function: LCD5110_setPixel(int x, int y)
*
* Returns: Nothing
*
* Description: Writes an individual pixel to the LCD
*
*******************************************************************************/

void LCD5110_setPixel(int x, int y)
{
  int y_mod = (int)(y >> 3);    // >>3 divides by 8
  int y_pix = (y-(y_mod << 3)); // <<3 multiplies by 8
  int val = 1 << y_pix;         //1<< y_pix

  // Write the pixel out to the LCD
  set_xy(x,y_mod);
  LCD5110_send (val, 1);
}
>>>>>>> 33af2e5a0186f497e5625d0fe67563444ebda689



//define lcd routine commands
#define cursor_off 0b00001101
#define blink_off 0b00001110
#define display_off 0b00001011
#define display_on 0b00001111

//HITECH header
#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
 #define _XTAL_FREQ 16000000
#endif

//set up enable and register select PINS
#define LCD_EN RD2
#define LCD_RS RD3

//define data port
#define LCD_DATA PORTD

//define cursor position
#define        lcd_cursor(x)        lcd_write(((x)&0x7F)|0x80)

//define strobe function
#define LCD_STROBE()   ((LCD_EN = 1),(LCD_EN=0))


//write a command to the LCD
void lcd_write(unsigned char c)
{
   _delay(20);
   LCD_DATA = ( ( c >> 4 ) & 0x0F );
   LCD_STROBE();
   LCD_DATA = ( c & 0x0F );
   LCD_STROBE();
}

//clear the LCD
void lcd_clear(void)
{
   LCD_RS = 0;
   lcd_write(0x1);
   _delay(20);
}

//write a string to the LCD
void lcd_puts(const char * s)
{
   LCD_RS = 1;   // write characters
   while(*s)
      lcd_write(*s++);
}

//write a character to the LCD
void lcd_putch(char c)
{
   LCD_RS = 1;   // write characters
   lcd_write( c );
}

//goto a position on the lcd
void lcd_goto(unsigned char pos)
{
   LCD_RS = 0;
   lcd_write(0x80+pos);
}

//initilise the lcd in 4-bit mode
void lcd_init()
{
   char init_value;

   ADCON1 = 0x06;   // Disable analog pins on PORTA

   init_value = 0x3;
   TRISA=0;
   TRISD=0;
   LCD_RS = 0;
   LCD_EN = 0;

   _delay(500);   // wait 15mSec after power applied,
   LCD_DATA = init_value;
   LCD_STROBE();
   _delay(500);
   LCD_STROBE();
   _delay(200);
   LCD_STROBE();
   _delay(200);
   LCD_DATA = 2;   // Four bit mode
   LCD_STROBE();

   lcd_write(0x28); // Set interface length
   lcd_write (0b00001101);
   _delay (20);
   lcd_write (0b00001110);
   lcd_clear();   // Clear screen
   lcd_write(0x6); // Set entry Mode
}
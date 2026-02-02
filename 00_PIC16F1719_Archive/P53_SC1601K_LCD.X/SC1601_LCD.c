/*
 * File: SC1601_LCD.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 32MHz (Optimized for 32MHz), 5v
 * Program: Library file to configure PIC16F1717/1719
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                *Optimized delays and modularized functions
 *                *Improved readability and maintainability
 * 
 * Program Description: This Library allows you to interface HD44780 and 
 *                      compatible LCDs in this library a SC1601K
 * 
 * Created on November 7th, 2016, 11:55 AM
 * Last Updated: December 14th, 2024
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "SC1601_LCD.h"
#include "PIC16F1719_Internal.h"
#include <string.h>

// Define timing constants
#define LCD_ENABLE_PULSE_DELAY_US 50   // Delay for Enable pulse
#define LCD_CMD_EXEC_DELAY_US 40       // Delay between commands
#define LCD_CLEAR_DELAY_MS 2           // Delay for LCD clear command
#define LCD_INIT_DELAY_MS 20           // Delay during initialization

#define LCD_BACKLIGHT LATDbits.LATD0 // Example pin for backlight control

/*******************************************************************************
 * Function: void Lcd_Port (char a)
 *
 * Returns: Nothing
 *
 * Description: Sends 4-bit nibble to the LCD data pins
 ******************************************************************************/
void Lcd_Port(char a)
{
    D4 = (a & 0x01);      // Set D4 based on bit 0 of 'a'
    D5 = (a & 0x02) >> 1; // Set D5 based on bit 1 of 'a'
    D6 = (a & 0x04) >> 2; // Set D6 based on bit 2 of 'a'
    D7 = (a & 0x08) >> 3; // Set D7 based on bit 3 of 'a'
}

/*******************************************************************************
 * Function: void Lcd_Enable_Pulse()
 *
 * Returns: Nothing
 *
 * Description: Generates Enable pulse for LCD
 ******************************************************************************/
void Lcd_Enable_Pulse()
{
    EN = 1;
    __delay_us(LCD_ENABLE_PULSE_DELAY_US);
    EN = 0;
}

/*******************************************************************************
 * Function: void Lcd_Cmd (char a)
 *
 * Returns: Nothing
 *
 * Description: Sends a command nibble to the LCD
 ******************************************************************************/
void Lcd_Cmd(char a)
{
    RS = 0;             // Command mode
    Lcd_Port(a);        // Send nibble
    Lcd_Enable_Pulse();
}

/*******************************************************************************
 * Function: void Lcd_Send_Command (char cmd)
 *
 * Returns: Nothing
 *
 * Description: Sends a full 8-bit command to the LCD
 ******************************************************************************/
void Lcd_Send_Command(char cmd)
{
    Lcd_Cmd(cmd >> 4); // Send high nibble
    Lcd_Cmd(cmd & 0x0F); // Send low nibble
}

/*******************************************************************************
 * Function: void Lcd_Clear()
 *
 * Returns: Nothing
 *
 * Description: Clears the LCD display
 ******************************************************************************/
void Lcd_Clear()
{
    Lcd_Send_Command(0x01); // Clear display command
    __delay_ms(LCD_CLEAR_DELAY_MS); // Required delay for clear operation
}

/*******************************************************************************
 * Function: void Lcd_Set_Cursor (char row, char col)
 *
 * Returns: Nothing
 *
 * Description: Sets the LCD cursor to a specified row and column
 ******************************************************************************/
void Lcd_Set_Cursor(char row, char col)
{
    char address = (row == 1) ? (0x80 + col - 1) : (0xC0 + col - 1);
    Lcd_Send_Command(address);
}

/*******************************************************************************
 * Function: void Lcd_Init()
 *
 * Returns: Nothing
 *
 * Description: Initializes the LCD in 4-bit mode
 ******************************************************************************/
void Lcd_Init()
{
    Lcd_Port(0x00);       // Reset port
    __delay_ms(LCD_INIT_DELAY_MS);

    // Initialization sequence
    Lcd_Cmd(0x03); __delay_ms(5);
    Lcd_Cmd(0x03); __delay_us(100);
    Lcd_Cmd(0x03); 
    Lcd_Cmd(0x02); // Set to 4-bit mode

    // Configure display
    Lcd_Send_Command(0x28); // Function set: 2-line, 5x8 dots
    Lcd_Send_Command(0x0C); // Display ON, Cursor OFF
    Lcd_Send_Command(0x06); // Entry mode: Increment cursor
    __delay_ms(2); // Allow configuration to settle
}

/*******************************************************************************
 * Function: void Lcd_Write_Char (char a)
 *
 * Returns: Nothing
 *
 * Description: Writes a single character to the LCD
 ******************************************************************************/
void Lcd_Write_Char(char a)
{
    RS = 1;                // Data mode
    Lcd_Port(a >> 4);      // Send high nibble
    Lcd_Enable_Pulse();
    Lcd_Port(a & 0x0F);    // Send low nibble
    Lcd_Enable_Pulse();
}

/*******************************************************************************
 * Function: void Lcd_Write_String (const char *str)
 *
 * Returns: Nothing
 *
 * Description: Writes a string to the LCD
 ******************************************************************************/
void Lcd_Write_String(const char *str)
{
    while (*str) {
        Lcd_Write_Char(*str++);
    }
}

/*******************************************************************************
 * Function: void Lcd_Shift_Right()
 *
 * Returns: Nothing
 *
 * Description: Shifts text on the LCD to the right
 ******************************************************************************/
void Lcd_Shift_Right()
{
    Lcd_Send_Command(0x1C); // Command for shift right
}

/*******************************************************************************
 * Function: void Lcd_Shift_Left()
 *
 * Returns: Nothing
 *
 * Description: Shifts text on the LCD to the left
 ******************************************************************************/
void Lcd_Shift_Left()
{
    Lcd_Send_Command(0x18); // Command for shift left
}

/*******************************************************************************
 * Function: (char* buf, int value, int base)
 *
 * Returns: Buffer
 *
 * Description: Performs Integer to ASCII Conversion
 ******************************************************************************/
char* itoa(char* buf, int value, int base) {
    char* ptr = buf;
    char* ptr1 = buf;
    char tmp_char;
    int tmp_value;

    // Handle negative numbers for base 10
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    // Convert integer to string
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEF"[tmp_value - (value * base)];
    } while (value);

    // Null-terminate string
    *ptr = '\0';

    // Reverse string
    ptr--;
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }

    return buf;
}

/*******************************************************************************
 * Function: (char* buf, int value, int base)
 *
 * Returns: Buffer
 *
 * Description: Performs Float to ASCII Conversion
 ******************************************************************************/
char* ftoa(float f, int* status) {
    static char buf[16]; // Static buffer to hold the converted string
    char* ptr = buf;
    int int_part = (int)f;      // Extract integer part
    float frac_part = f - int_part; // Extract fractional part
    int frac_as_int;
    int frac_digits = 2;       // Number of fractional digits to display

    // Handle special cases
    if (f < 0.0) {
        *ptr++ = '-';
        f = -f;
        int_part = (int)f;
        frac_part = f - int_part;
    }

    // Convert integer part using itoa
    itoa(ptr, int_part, 10);
    while (*ptr != '\0') {
        ptr++;
    }

    // Add decimal point
    *ptr++ = '.';

    // Convert fractional part
    frac_as_int = (int)(frac_part * 10 * frac_digits);
    itoa(ptr, frac_as_int, 10);

    // Null-terminate the string
    *status = 0; // Indicate successful conversion
    return buf;
}


/*******************************************************************************
 * Function: void Lcd_Write_Integer (int v)
 *
 * Returns: Nothing
 *
 * Description: Converts an integer to string and writes it to the LCD
 ******************************************************************************/
void Lcd_Write_Integer(int v)
{
    char buf[8];
    Lcd_Write_String(itoa(buf, v, 10));
}

/*******************************************************************************
 * Function: void Lcd_Write_Float (float f)
 *
 * Returns: Nothing
 *
 * Description: Converts a float to string and writes it to the LCD
 ******************************************************************************/
void Lcd_Write_Float(float f)
{
    char* buf;
    int status;
    buf = ftoa(f, &status);
    Lcd_Write_String(buf);
}

/*******************************************************************************
 * Function: void Lcd_Write_Padded_Integer(int num, int width)
 *
 * Returns: Nothing
 *
 * Description: Writes an integer to the LCD, padded with leading zeros to the
 *              specified width.
 ******************************************************************************/

void Lcd_Write_Padded_Integer(int num, int width)
{
    char buf[16];
    sprintf(buf, "%0*d", width, num); // Format number with leading zeros
    Lcd_Write_String(buf);
}


/*******************************************************************************
 * Function: void Lcd_Center_Text(char row, const char *str)
 *
 * Returns: Nothing
 *
 * Description: Centers the provided text on the specified LCD row.
 ******************************************************************************/
void Lcd_Center_Text(char row, const char *str)
{
    int len = strlen(str);
    int start_col = (16 - len) / 2 + 1; // Center calculation for 16x2 LCD
    Lcd_Set_Cursor(row, start_col);
    Lcd_Write_String(str);
}

/*******************************************************************************
 * Function: void Lcd_Reset()
 *
 * Returns: Nothing
 *
 * Description: Resets the LCD and reinitializes it to 4-bit mode.
 ******************************************************************************/
void Lcd_Reset()
{
    Lcd_Send_Command(0x03); __delay_ms(5);
    Lcd_Send_Command(0x03); __delay_us(100);
    Lcd_Send_Command(0x03);
    Lcd_Send_Command(0x02); // Return to 4-bit mode
    Lcd_Init(); // Reinitialize settings
}

/*******************************************************************************
 * Function: void Lcd_Scroll_Text(const char *str)
 *
 * Returns: Nothing
 *
 * Description: Scrolls the provided text across the LCD screen.
 ******************************************************************************/
void Lcd_Scroll_Text(const char *str)
{
    char buffer[17]; // Assuming 16x2 LCD
    int len = strlen(str);
    for (int i = 0; i <= len - 16; i++) {
        strncpy(buffer, &str[i], 16); // Copy 16 characters at a time
        buffer[16] = '\0'; // Null-terminate
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String(buffer);
        __delay_ms(200);
    }
}

/*******************************************************************************
 * Function: void Lcd_Create_Char(unsigned char location, unsigned char charmap[])
 *
 * Returns: Nothing
 *
 * Description: Defines a custom character in the LCD CGRAM at the specified 
 *              location using the provided character map.
 ******************************************************************************/
void Lcd_Create_Char(unsigned char location, unsigned char charmap[])
{
    location &= 0x07; // Limit to 8 locations (0-7)
    Lcd_Send_Command(0x40 | (location << 3)); // Set CGRAM address
    for (int i = 0; i < 8; i++) {
        Lcd_Write_Char(charmap[i]); // Write custom character data
    }
}

/*******************************************************************************
 * Function: void Lcd_Display_Custom_Char(unsigned char location)
 *
 * Returns: Nothing
 *
 * Description: Displays a custom character stored at the specified CGRAM location.
 ******************************************************************************/
void Lcd_Display_Custom_Char(unsigned char location)
{
    Lcd_Write_Char(location);
}

// Progress Bar
void Lcd_Progress_Bar_Init()
{
    unsigned char block_1[8] = {0x00, 0x10, 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F}; // 1/4 Block
    unsigned char block_2[8] = {0x00, 0x18, 0x18, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F}; // 1/2 Block
    unsigned char block_3[8] = {0x00, 0x1C, 0x1C, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F}; // 3/4 Block
    unsigned char block_full[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}; // Full Block

    Lcd_Create_Char(1, block_1);    // 1/4 block at CGRAM location 1
    Lcd_Create_Char(2, block_2);    // 1/2 block at CGRAM location 2
    Lcd_Create_Char(3, block_3);    // 3/4 block at CGRAM location 3
    Lcd_Create_Char(4, block_full); // Full block at CGRAM location 4
}


void Lcd_Progress_Bar(int progress, int max)
{
    int total_blocks = 16; // Total columns available on the LCD
    int full_blocks = (progress * total_blocks) / max; // Number of full blocks
    int fractional_block = ((progress * total_blocks * 4) / max) % 4; // Fractional block (1/4 steps)

    // Display full blocks
    for (int i = 0; i < full_blocks; i++) {
        Lcd_Write_Char(4); // Full block character
    }

    // Display fractional block if applicable
    if (full_blocks < total_blocks && fractional_block > 0) {
        Lcd_Write_Char(fractional_block); // Use 1/4, 1/2, or 3/4 block
        full_blocks++;
    }

    // Fill the rest with spaces
    for (int i = full_blocks; i < total_blocks; i++) {
        Lcd_Write_Char(' '); // Empty space
    }
}


/// Battery
void Lcd_Battery_Init()
{
    unsigned char level0[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}; // Empty battery
    unsigned char level1[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x0E}; // ~20% battery
    unsigned char level2[8] = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x0E}; // ~30% battery
    unsigned char level3[8] = {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x0E}; // ~50% battery
    unsigned char level4[8] = {0x0E, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E}; // ~70% battery
    unsigned char level5[8] = {0x0E, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E}; // ~90% battery
    unsigned char full[8]  = {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E};  // Full battery (100%)

    // Create custom characters
    Lcd_Create_Char(0, level0);  // CGRAM location 0
    Lcd_Create_Char(1, level1);  // CGRAM location 1
    Lcd_Create_Char(2, level2);  // CGRAM location 2
    Lcd_Create_Char(3, level3);  // CGRAM location 3
    Lcd_Create_Char(4, level4);  // CGRAM location 4
    Lcd_Create_Char(5, level5);  // CGRAM location 5
    Lcd_Create_Char(6, full);    // CGRAM location 6
}


void Lcd_Display_Battery(int percentage)
{
    unsigned char battery_char;
    
    // Determine the custom character based on the percentage
    if (percentage <= 10) {
        battery_char = 0; // Empty battery
    } else if (percentage <= 20) {
        battery_char = 1; // ~20% battery
    } else if (percentage <= 40) {
        battery_char = 2; // ~30% battery
    } else if (percentage <= 50) {
        battery_char = 3; // ~50% battery
    } else if (percentage <= 70) {
        battery_char = 4; // ~70% battery
    } else if (percentage <= 90) {
        battery_char = 5; // ~90% battery
    } else {
        battery_char = 6; // Full battery
    }

    // Display the battery icon
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Battery:");
    Lcd_Set_Cursor(1, 10); // Position for battery icon
    Lcd_Display_Custom_Char(battery_char);

    // Optionally display percentage
    char buf[5];
    sprintf(buf, "%d%%", percentage); // Format percentage as a string
    Lcd_Set_Cursor(1, 12); // Position for percentage
    Lcd_Write_String(buf);
}



/// Signal
void Lcd_Signal_Init()
{
    unsigned char no_signal[8] = {0x00, 0x00, 0x00, 0x04, 0x0E, 0x1F, 0x00, 0x00}; // No signal
    unsigned char weak_signal[8] = {0x00, 0x04, 0x0E, 0x04, 0x0E, 0x1F, 0x00, 0x00}; // Weak
    unsigned char strong_signal[8] = {0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x1F, 0x00, 0x00}; // Strong

    Lcd_Create_Char(0, no_signal);
    Lcd_Create_Char(1, weak_signal);
    Lcd_Create_Char(2, strong_signal);
}

void Lcd_Display_Signal(int level)
{
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Signal:");

    if (level == 0) {
        Lcd_Set_Cursor(1, 10);
        Lcd_Display_Custom_Char(0); // No signal
    } else if (level == 1) {
        Lcd_Set_Cursor(1, 10);
        Lcd_Display_Custom_Char(1); // Weak signal
    } else {
        Lcd_Set_Cursor(1, 10);
        Lcd_Display_Custom_Char(2); // Strong signal
    }
}



/*******************************************************************************
 * Function: void Lcd_Blink_On()
 *
 * Returns: Nothing
 *
 * Description: Enables the LCD cursor blink feature.
 ******************************************************************************/
void Lcd_Blink_On()
{
    Lcd_Send_Command(0x0D); // Display ON, Cursor ON, Blink ON
}

void Lcd_Blink_Off()
{
    Lcd_Send_Command(0x0C); // Display ON, Cursor OFF, Blink OFF
}

/*******************************************************************************
 * Function: void Lcd_Display_On()
 *
 * Returns: Nothing
 *
 * Description: Turns the LCD display ON.
 ******************************************************************************/
void Lcd_Display_On()
{
    Lcd_Send_Command(0x0C); // Display ON, Cursor OFF
}

void Lcd_Display_Off()
{
    Lcd_Send_Command(0x08); // Display OFF, Cursor OFF
}

/*******************************************************************************
 * Function: void Lcd_Move_Cursor_Left()
 *
 * Returns: Nothing
 *
 * Description: Moves the LCD cursor one position to the left.
 ******************************************************************************/
void Lcd_Move_Cursor_Left()
{
    Lcd_Send_Command(0x10); // Move cursor left
}

void Lcd_Move_Cursor_Right()
{
    Lcd_Send_Command(0x14); // Move cursor right
}


/*******************************************************************************
 * Function: void Lcd_Backlight_On()
 *
 * Returns: Nothing
 *
 * Description: Turns the LCD backlight ON (if supported by hardware).
 ******************************************************************************/
void Lcd_Backlight_On()
{
    LCD_BACKLIGHT = 1;
}

void Lcd_Backlight_Off()
{
    LCD_BACKLIGHT = 0;
}


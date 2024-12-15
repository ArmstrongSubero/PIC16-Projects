/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: P53_SC1601K
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 *                  * Optimized Routines
 *                  * Improved library readability
 *                  * Added additional routines
 * 
 * Program Description: This program allows the PIC16F1719 to communicate 
 *                      with a SC1601K (HD44780 compatible) LCD
 * 
 * Hardware Description: An HD44780 compatible LCD is connected to PORTD of the
 *                       microcontroller as follows:
 * 
 *                       RS ---> RD2
 *                       R/W ---> GND
 *                       EN ---> RD3
 *                       D4 ---> RD4
 *                       D5 ---> RD5
 *                       D6 ---> RD6
 *                       D7 ---> RD7
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: November 24th, 2023, 12:54 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "SC1601_LCD.h"


/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/

void initMain(){
    // Run at 32 MHz
    internal_32();
    
    // Allow PLL startup time ~2 ms
    __delay_ms(10);
    
    // Setup LCD Port
    TRISD = 0x00;
    ANSELD = 0x00;
    PORTD = 0x00;
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();
    __delay_ms(100);
    
    // Initialize LCD
    Lcd_Init();
    
    // Allow time to Stabalize
    __delay_ms(100);

    
  while(1)
  {  
    Lcd_Clear();

    Lcd_Backlight_On();         // Turn on backlight 
    __delay_ms(2000);
    Lcd_Backlight_Off();        // Turn off backlight
    
    Lcd_Blink_On();            // Enable cursor blink
    __delay_ms(2000);
    Lcd_Blink_Off();           // Disable cursor blink
    __delay_ms(2000);
   
    Lcd_Display_Off();         // Turn LCD display OFF
    __delay_ms(2000);
    
    Lcd_Display_On();          // Turn LCD display ON
    __delay_ms(1000);
    
     Lcd_Move_Cursor_Left();    // Move cursor left
     __delay_ms(1000);
     Lcd_Move_Cursor_Right();   // Move cursor right
     __delay_ms(1000);
     Lcd_Move_Cursor_Left();    // Move cursor left
    
    // Clear and display a simple message
    Lcd_Clear();
    
    __delay_ms(100);
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("PIC16F1719");
    __delay_ms(1000);
   
   
    // Shift message left
    for (int a = 0; a < 15; a++) {
        __delay_ms(250);
        Lcd_Shift_Left();
    }

    // Shift message right
    for (int a = 0; a < 15; a++) {
        __delay_ms(250);
        Lcd_Shift_Right();
    }
    
    __delay_ms(100);

    
    // Write Incrementing Integer
    for (int c = 0; c <= 10; c++) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Integer(c);
        __delay_ms(250);
    }
    
    // Write Incrementing Float
    for (float b = 0.0; b <= 5.0; b += 0.5) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Float(b);
        __delay_ms(300);
    }  
    
    // Write a padded integer
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Pad:");
    Lcd_Set_Cursor(1, 6);
    
    for (int c = 0; c <= 10; c++) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Padded_Integer(c, 4); // Display "0000"
        __delay_ms(100);
    }

    // Display a custom smiley face character
    unsigned char smiley[8] = {0x00, 0x0A, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00};
    Lcd_Create_Char(0, smiley);         // Define smiley at CGRAM location 0
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("S:");
    Lcd_Set_Cursor(1, 3);
    Lcd_Display_Custom_Char(0);        // Display the smiley character
    __delay_ms(2000);
    
    // Scroll a long text message
    Lcd_Clear();
    Lcd_Scroll_Text("This is a long scrolling text message.");
    __delay_ms(1000);
    
    // Display a centered text
    Lcd_Clear();
    Lcd_Center_Text(1, "Welcome!");
    __delay_ms(2000);
     
    
    Lcd_Progress_Bar_Init(); // Initialize custom characters

    for (int progress = 0; progress <= 100; progress += 5) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Progress:");
        Lcd_Set_Cursor(1, 10); // Start bar at column 10
        Lcd_Progress_Bar(progress, 100); // Update bar
        __delay_ms(300);
    }
    
    // Initialize battery custom characters
    Lcd_Battery_Init(); // Initialize custom characters

    // Demo different battery levels
    int battery_levels[] = {0, 20, 40, 60, 80, 100};
    for (int i = 0; i < 6; i++) {
        Lcd_Display_Battery(battery_levels[i]); // Display battery level
        __delay_ms(2000); // Pause for 2 seconds
    }
    
    Lcd_Signal_Init();    
    Lcd_Display_Signal(1);
    
    __delay_ms(2000);
 
}
    return;
}

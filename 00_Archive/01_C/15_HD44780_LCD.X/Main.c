/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 15_HD44780_LCD
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to interface to HD44780
 *                      and compatible LCD's
 *                      
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
 *                      
 * Created November 7th, 2016, 11:05 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"


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
    // Run at 16 MHz
    internal_16();
    
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
    Lcd_Init();
    __delay_ms(1000);

    int a;
    int c;
    float b;
    
    while(1){  
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        __delay_ms(100);
    
        // Write String
        Lcd_Write_String("PIC16F1717");
        __delay_ms(10);
   
        // Shift it left
        for(a=0;a<15;a++)
        {
            __delay_ms(500);
            Lcd_Shift_Left();
        }

        // Shift it right
        for(a=0;a<15;a++)
        {
            __delay_ms(500);
            Lcd_Shift_Right();
        }

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
    
        // Write Integer
        for (c = 0; c < 100; c++){
            Lcd_Write_Integer(c);
            __delay_ms(300);
            Lcd_Clear();
            __delay_ms(15);
            
        }
    
        // Write Float
        for (b = 0.0; b <= 5; b+= 0.5)
        {
            Lcd_Write_Float(b);
            __delay_ms(300);
            Lcd_Clear();
            __delay_ms(15);
        }
  
        __delay_ms(1000);
}
    
    return;
}

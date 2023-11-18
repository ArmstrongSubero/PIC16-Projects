/*
 * File: touchscreen.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file for Nextion Touchscreen
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to send commands to the Nextion
 *                      touchscreen
 *                      
 * Created on April 21st, 2017, 2:30 PM
 */


#include "touchscreen.h"
#include "EUSART.h"

/*
 Send commands to Touchscreen
 */
void touchscreen_command(char* string)
{
    EUSART_Write_Text(string);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    __delay_ms(1000);
}

void touchscreen_data(char* cmd, char* string2)
{
    EUSART_Write_Text(cmd);
    EUSART_Write_Text(string2);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    
    __delay_ms(100);
}






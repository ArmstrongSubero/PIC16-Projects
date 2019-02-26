/*
 * File: touchscreen.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 I2C
 * Compiler: XC8 (v1.40, MPLAX X v3.55)
 * Program Version 1.0
 *           
 * Program Description: This program header provide function prototypes for 
 *                      sending commands to a Nextion Touch Display
 *
 * Created on April 21st, 2017, 2:25 PM
 */


#include "16F1717_Internal.h"
#include <string.h>

// Function prototypes
void touchscreen_command(char* string);
void touchscreen_data(char* cmd, char* string2);
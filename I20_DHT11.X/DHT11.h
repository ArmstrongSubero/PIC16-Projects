/*******************************************************************************
 * File: DHT11.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup the DHT11 temperature and humidity module
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version 1.0
 *
 * Program Description: This program file is the header for the DHT11 temp/hum
 *                      module
 *
 * Created on September 11th, 2018, 01:37 PM
 ******************************************************************************/

#include "16F1717_Internal.h"

#define Dat_Output    LATDbits.LATD3            
#define Dat_Input     PORTDbits.RD3    
#define Dat_Direction TRISDbits.TRISD3

void DHT11_Init();
void DHT11_Check();
char DHT11_Read();



/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 28_LM35_Temperature
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.0
 * 
 * Program Description: This program allows the PIC16F1718 to measure temperature 
 *                      using the LM35 temperature sensor. 
 * 
 * Hardware Description: The output of an SOIC LM35 temperature sensor is 
 *                       connected to pin A0. 
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Friday 26th, December, 2025, 2:25 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "ADC.h"

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
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    /////////////////////
    // Setup I2C
    ////////////////////
    
    /* I2C pins */
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    /* PPS mapping */
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS   = 0x0B;

    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;

    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;

    
    ////////////////////
    // Configure ADC
    ///////////////////
    
    // Fosc/32 ADC conversion time is 1.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
    
    // Configure the ADC pins you want to use
    ADC_ConfigurePin(ADC_AN0);
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void)
{
    initMain();
    I2C_Init();
    
    OLED_Init();
    OLED_SetOrientation(OLED_ORIENT_0);
    OLED_Clear();
    
    ADC_Init();
    
    uint16_t LM35;
    char Temperature[10];
    float celcius;
    int i;
    
    while (1)
    {
        LM35 = ADC_Read_Averaged(ADC_AN0, 8);

        float voltage = (LM35 * 5.0) / 1023.0;
        celcius = voltage * 100.0;

        OLED_Printf_Line(0, "Temp: %d C", (int)celcius);

        __delay_ms(500);
    }
}
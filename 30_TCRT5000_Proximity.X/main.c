/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 30_TCRT5000_Proximity
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 * 
 * Program Description: This program allows the PIC16F1718 to measure proximity 
 *                      by applying ambient-cancelled reflectance.
 * 
 * Hardware Description: The TCRT5000 is connected to the MCU. RC3 is connected 
 *                       to the LED via a 470 ohm resistor and the phototransistor 
 *                       is connected to the power supply via a 10k resistor 
 *                       which is then read by AN0. 
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Friday 26th, December, 2025, 2:40 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "ADC.h"

// IR LED
#define IR_LED_TRIS  TRISCbits.TRISC3
#define IR_LED_LAT   LATCbits.LATC3
#define IR_LED_ANS   ANSELCbits.ANSC3

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
    
    //////////////////////
    // Setup IR LED 
    /////////////////////
    IR_LED_ANS  = 0;     // RC3 as digital
    IR_LED_TRIS = 0;     // output
    IR_LED_LAT  = 0;     // start OFF   
    
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
    
    // Ambient-Cancelled Reflectance 
    uint16_t on, off;
    int16_t  signal;
    static uint16_t filt = 0;
    
    while (1)
    {
        IR_LED_LAT = 0;
        __delay_us(300);
        off = ADC_Read_Averaged(ADC_AN0, 8);

        IR_LED_LAT = 1;
        __delay_us(300);
        on = ADC_Read_Averaged(ADC_AN0, 8);

        signal = (int16_t)off - (int16_t)on;
        if (signal < 0) signal = 0;

        // faster EMA
        filt = (filt * 3 + (uint16_t)signal) / 4;

        OLED_Printf_Line(0, "OFF:%u ON:%u", off, on);
        OLED_Printf_Line(1, "IR:%u", filt);

        __delay_ms(20);
    }
}
/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 31_LDR_Light
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 * 
 * Program Description: This program allows the PIC16F1718 to measure light 
 *                      and darkness using a light dependant resistor, we use 
 *                      hysteresis to reduce flicker and smooth noise while 
 *                      detecting ambient light. The digital low pass filter 
 *                      we employ is a Exponential Moving average (EMA) filter. 
 *                      We use 0.125 alpha taking 87.5% of the previous value 
 *                      and 12.5% of the new value. 
 * 
 * Hardware Description: A LDR is connected in series with a 10k resistor, the 
 *                       center point it read into AN0. 
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Friday 26th, December, 2025, 3:38 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "ADC.h"

#define DARK_TH   300
#define LIGHT_TH  380     // hysteresis band

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
    
    uint16_t adc;
    static uint16_t filt = 0;
    static uint8_t isDark = 0;
    
    while (1)
    {
        // Read & average ADC
        adc = ADC_Read_Averaged(ADC_AN0, 16);

        // Smooth (EMA)
        filt = (filt * 7 + adc) / 8;

        // Hysteresis-based decision
        if (!isDark && filt < DARK_TH) {
            isDark = 1;
        }
        else if (isDark && filt > LIGHT_TH) {
            isDark = 0;
        }

        // Display
        OLED_Printf_Line(0, "Light: %u", filt);
        OLED_Printf_Line(1, isDark ? "DARK" : "LIGHT");

        __delay_ms(100);
    }
}
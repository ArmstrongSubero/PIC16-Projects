/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 16_ADC
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.3
 *                  * Updated for PIC16F1718 and added multiple channel access
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1718 to use the ADC
 *                      module
 * 
 * Hardware Description: Potentiometers are connected to PIN PA0 and PA1 and 
 *                       an SSD1306 is connected to the I2C bus. 
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Thursday 25th, December, 2025, 6:51 PM
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
    ADC_ConfigurePin(ADC_AN1);
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
    
    uint16_t adc0, adc1, adc2;
    
    while (1)
    {
        // Read from different channels - super easy!
        adc0 = ADC_Read_Averaged(ADC_AN0, 8);
        adc1 = ADC_Read_Averaged(ADC_AN1, 8);

        // Display them
        OLED_Printf_Line(0, "AN0: %u", adc0);
        OLED_Printf_Line(1, "AN1: %u", adc1);
        
        __delay_ms(100);
    }
}
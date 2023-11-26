/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 22_Internal_Temperature_Indicator
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1719 to use the internal 
 *                      temperature indicator module
 *                      
 *
 * Hardware Description: PIN RB2 of a the PIC16F1719 MCU is connected to 
 *                       a PL2303XX USB to UART converter cable 
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: November 24th, 2023, 5:30 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "EUSART.h"


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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
    RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    
    ////////////////////////
    // Configure Indicator
    ///////////////////////
    FVRCONbits.FVREN = 1;
    
    // Temperature indication in high range
    FVRCONbits.TSRNG = 1;
    
    // Enable temperature indicator 
    FVRCONbits.TSEN = 1;
    
    ///////////////////////
    // Configure ADC
    ///////////////////////
    
    // Fosc/32 ADC conversion time is 1.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
    
    // Set input channel to Internal Temperature Indicator
    ADCON0bits.CHS = 0b11101;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;  
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
    
    // Initialize EUSART module with 19200 baud
    EUSART_Initialize(19200);
     
    // variable to store conversion result
    int result;
    
    while(1)
    {    
      // Turn ADC on
      ADCON0bits.ADON = 1;
       
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL);
      
      EUSART_Write_Text("Read Data: ");
      EUSART_Write_Integer(result);
      EUSART_Write_Text("\n");
      __delay_ms(1000);
    }
    
    return;   
}

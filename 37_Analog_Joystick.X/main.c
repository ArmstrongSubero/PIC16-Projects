/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 37_Analog_Joystick
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1719 to use the ADC
 *                      module to read an analog joystick
 * 
 * Hardware Description: PIN RB2 of a the PIC16F1719 MCU is connected to 
 *                       a PL2303XX USB to UART converter cable and a 
 *                       analog joystick to AN12 (RB0) and AN10 (RB1)
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: MArch 25th, 2024, 3:34 AM
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
   
    // configure analog input pins 
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 1;
    
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSB1 = 1;
    
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
    
    ////////////////////
    // Configure ADC
    ///////////////////
     
    // Set A0 as input
    TRISAbits.TRISA0 = 1;
    
    // Set A0 as analog
    ANSELAbits.ANSA0 = 1;
    
    // Fosc/32 ADC conversion time is 1.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
    
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
     
    // variables to store conversion result
    int result;
    int result1;
    
    while(1)
    {    
     // Turn ADC on
      ADCON0bits.ADON = 1;
      
     // Set input channel to AN12
     ADCON0bits.CHS = 0b01100;
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL);
    
     // Set input channel to AN10
     ADCON0bits.CHS = 0b01010;
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result1 = ((ADRESH<<8)+ADRESL);
      
      if (result == 0)
      {
          EUSART_Write_Text("Up");
          EUSART_Write_Text("\n");
      }
      
      else if (result == 1023)
      {
          EUSART_Write_Text("Down");
          EUSART_Write_Text("\n");
      }
      
      if (result1 == 0)
      {
         EUSART_Write_Text("Right");
         EUSART_Write_Text("\n");
          
      }
      
      else if(result1 == 1023)
      {
         EUSART_Write_Text("Left");
         EUSART_Write_Text("\n");
      }
      
      // Update every second
      __delay_ms(1000);
    }
    
    return;   
}

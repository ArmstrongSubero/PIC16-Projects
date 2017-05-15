/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 25_Temperature_Indicator
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to turn on an LED based
 *                      on a Pushbutton
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN D1 and a
 *                       switch is connected to PIN B0
 *                      
 * Created November 4th, 2016, 1:08 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include <string.h>

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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    ////////////////////////
    // Configure FVR for
    // Temperature Indicator
    ////////////////////////
    
    // Enable the Temperature Indicator
    FVRCONbits.TSEN = 1;
    
    // Set the range to high
    FVRCONbits.TSRNG = 1;
    
    ////////////////////
    // Configure ADC
    ///////////////////
    
    // Fosc/32 ADC conversion time is 2.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
    
    // Set input channel to Temperature Indicator
    ADCON0bits.CHS = 0b11101;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
    
    //////////////////////
    // Configure the OLED
    //////////////////////
    
    /////////////////////
    // Setup I2C
    ////////////////////
    
     // Setup pins for I2C
     ANSELCbits.ANSC4 = 0;
     ANSELCbits.ANSC5 = 0;
     
     TRISCbits.TRISC4 = 1;
     TRISCbits.TRISC5 = 1;
     
     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

     RC4PPSbits.RC4PPS = 0x0011;   //RC4->MSSP:SDA;
     SSPDATPPSbits.SSPDATPPS = 0x0014;   //RC4->MSSP:SDA;
     SSPCLKPPSbits.SSPCLKPPS = 0x0015;   //RC5->MSSP:SCL;
     RC5PPSbits.RC5PPS = 0x0010;   //RC5->MSSP:SCL;

     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
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
    
    // variable to store conversion result
    int result = 0;
    int result1;
    
     // Initialize I2C
    I2C_Init();

    __delay_ms(100);
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();
    
    // Turn ADC on
    ADCON0bits.ADON = 1;
    
    
    while(1){
       
      // Sample Temp
        ADCON0bits.ADON = 1;

      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL);
                    
      
      
      ///////////////////////////
      // Calculate temperature
      //////////////////////////    
       OLED_YX( 0, 0 );
       OLED_Write_String("Temp:" ); 
       
       OLED_YX(1, 0 );
       OLED_Write_Integer(result);
       
       __delay_ms(1000);
       
    }
    
    return;
    
}

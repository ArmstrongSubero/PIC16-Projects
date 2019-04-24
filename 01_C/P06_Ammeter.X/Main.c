/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: P06_Ammeter
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
 *                             
 * Program Description: This project uses a PIC16F1719 interfaced with an ACS712
 *                      20A version to make an Ammeter. The meter is accurate
 *                      from 0.5A up an is intended to measure current within
 *                      the 0.5A to 10A range. 
 * 
 * Hardware Description: A SSD1306 based OLED is connected to a PIC16F1717 via 
 *                       a logic level converter to a SSD1306 based OLED as 
 *                       follows:
 *                        
 *                       GND --> GND
 *                       VCC --> VCC
 *                       SCL --> RC5
 *                       SDA --> RC4
 * 
 * There is also a ACS712 module with the output connected to RA0
 *                      
 * Created April 22nd, 2019, 3:56 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include <string.h>


// variables for conversion
 uint16_t convertedValue;
 uint16_t convertedValue1;
 double Voltage = 0;
 double Current = 0;
 double readVoltage = 0;
 
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
     
     
     // Set A0 as input
    TRISAbits.TRISA0 = 1;
    
    // Set A0 as analog
    ANSELAbits.ANSA0 = 1;
    
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
    
    // Set input channel to AN0
    ADCON0bits.CHS = 0b00000;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
    
   
    // Turn ADC on
    ADCON0bits.ADON = 1; 
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
    
    // Initialize I2C
    I2C_Init();

    __delay_ms(100);
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();

        while ( 1 ) {
            
            /////////////////////
            // Read Current
            ////////////////////
            
            // Set input channel to AN0
            ADCON0bits.CHS = 0b00000;
         
            //Voltage is Sensed 1000 Times for precision
            for(int i = 0; i < 1000; i++) {
                  // Sample CH0
                __delay_us(10);
                ADCON0bits.GO = 1;
                while (ADCON0bits.GO_nDONE);
               
               // Store ADC result
               convertedValue = ((ADRESH<<8)+ADRESL);
               
               // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
                Voltage = (Voltage + (.0049 * convertedValue));    
                __delay_ms(1);
            }
            
            Voltage = Voltage/1000;                        // calculate average voltage
            Current = (Voltage-2.5)/ 0.100;                // Sensed voltage is converted to current
            Current -= 0.07225;                            // offset
            
            
            OLED_YX( 0, 0 );
            OLED_Write_String( "A:" );
         
            OLED_YX( 0, 5);
            OLED_Write_Float(Current);
        }
    
    
    return; 
    
}

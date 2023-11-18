/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: P04_Temp_Fan
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This project builds a temperature controlled fan. When
 *                      the temperature rises above 35 Celsius a fan turns on
 *                      until the temperature drops to 35 Celsius or below.
 *                      
 * Hardware Description: A generic brushed hobby DC motor is connected to the 
 *                       SN754410 as per standard connections. The PWM signals
 *                       are emanating from RB0 and RB1. The LM34 temperature 
 *                       sensor is connected to PIN RE0 and an SSD1306 based 
 *                       OLED is connected as per header file.
 *                       
 *                      
 * Created April 18th, 2017, 4:36 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"

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
    
    ///////////////////////
    // Configure PWM Ports
    ///////////////////////
    
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
    
    // Set PIN B1 as output
    TRISBbits.TRISB1 = 0;
    
    // Turn off analog on PORTB
    ANSELB = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select PWM timer as Timer6 for CCP1 and CCP2
    CCPTMRSbits.C1TSEL = 0b10;
    CCPTMRSbits.C2TSEL = 0b10;
    
 
    // Enable timer Increments every 250 ns (16MHz clock) 1000/(16/4)
    // Period = 256 x 0.25 us = 64 us
    
    //                          Crystal Frequency 
    //    PWM Freq  = ----------------------------------------- 
    //                  (PRX + 1) * (TimerX Prescaler) * 4
    
    //    PWM Frequency = 16 000 000 / 256 * 1 * 4
    //    PWM Frequency = 15.625 kHz
    
    // Prescale = 1
    T6CONbits.T6CKPS = 0b00;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;
    
    // Set timer period
    PR6 = 255;
    
    
    //////////////////////////
    // Configure PWM
    /////////////////////////
    
    // Configure CCP1
     
    // LSB's of PWM duty cycle = 00
    CCP1CONbits.DC1B = 00;
    
    // Select PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // Configure CCP2
    
    // LSB's of PWM duty cycle = 00
    CCP2CONbits.DC2B = 00;
    
    // Select PWM mode
    CCP2CONbits.CCP2M = 0b1100;
    
      
    /////////////////////
    // Setup I2C
    //////////////////
    
    // Setup pins for I2C
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
     
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    
    
    //////////////////////////////
    // Configure PPS
    /////////////////////////////
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to PWM1
    RB0PPSbits.RB0PPS = 0b01100;
    
    // Set RB1 to PWM2
    RB1PPSbits.RB1PPS = 0b01101;
    
    RC4PPSbits.RC4PPS = 0x0011;   //RC4->MSSP:SDA;
    SSPDATPPSbits.SSPDATPPS = 0x0014;   //RC4->MSSP:SDA;
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;   //RC5->MSSP:SCL;
    RC5PPSbits.RC5PPS = 0x0010;   //RC5->MSSP:SCL;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
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
    ADCON0bits.CHS = 0x05;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
    
    // ADC Input channel PIN E0
    ANSELEbits.ANSE0 = 1;   
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
    
    __delay_ms(500);
    
    // Initialize OLED
    OLED_Init();
   
    __delay_ms(1000);
    
    // clear OLED
    OLED_Clear();
    
    // result to store ADC conversion
    float result;
          
    // variables for conversion
    float conversion10;
    float farenheit;
    float celsius;
    
    // PWM Off
    CCPR1L = 0;
    CCPR2L = 0;
    
    OLED_YX(0, 0);
    OLED_Write_String("Init");

    while(1){
        
        // Turn ADC on
        ADCON0bits.ADON = 1;
        
        // Sample CH0
        __delay_us(10);
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE);
      
        // Store ADC result
        result = ((ADRESH<<8)+ADRESL);
      
        // 10 bit conversion
        conversion10 = (result * 5000)/1024 ;
      
        // to Fahrenheit
        farenheit = conversion10 / 10;
      
        // to Celsius
        celsius = (farenheit - 32) * 5/9;
      
        // Display temperature
      
        OLED_YX(1, 0);
        OLED_Write_Integer((int)celsius);
      
        // Update every second
        __delay_ms(2000);
        
        
        // If temperature is more than 35C turn on fan
        if ((int)celsius > 35){
     
            // Forward
            CCPR1L = 127;
            CCPR2L = 0;
            
            // clear OLED
            OLED_Clear();
      
            OLED_YX(0, 0);
            OLED_Write_String("Warning!!");
      }
        
      // If less turn off fan
      else{
            OLED_YX(0, 0);
            OLED_Write_String("Temp OK");
            CCPR1L = 0;
            CCPR2L = 0; 
      }
            
    }
     return;    
}


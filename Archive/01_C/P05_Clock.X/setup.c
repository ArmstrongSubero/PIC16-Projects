/*
 * File: setup.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file for Nextion Touchscreen
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to setup for the clock
 *                      
 * Created on April 21st, 2017, 2:30 PM
 */


#include "setup.h"
#include "ds1302.h"
#include "oled.h"
#include "EUSART.h"
#include "touchscreen.h"

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
    
    // Setup pins for EUSART
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
   
    /////////////////////
    // Setup Serial
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
     
     RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
     RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;

     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
     
     // Setup RTCC pins
     TRISD = 0;
     ANSELD = 0;
     
      // Initialize I2C
    I2C_Init();

    __delay_ms(500);
    
    // Initialize OLED
    OLED_Init();
    
    __delay_ms(500);
    
    // Dim Touchscreen
    OLED_YX(0, 0);
    OLED_Write_String("Init");
    
    __delay_ms(1000);
   
    // clear OLED
    OLED_Clear();
    
    __delay_ms(500);
    
    
    // Initial time and date
    byte sec = 51;
    byte min = 59;
    byte hr = 23;
    byte day = 2;
    byte date = 30;
    byte month = 4;
    byte year = 17;
     
    // Initialize DS1302
    DS1302_Initialize(sec, min, hr, day, date, month, year);
    
     //Initialize EUSART module with 9600 baud
     EUSART_Initialize(9600);
    __delay_ms(2000);
    
     // clear OLED
    OLED_Clear();
    
    ///////////////////////
    // Configure Timer0
    //////////////////////
    
    // Select timer mode
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 0;
    
    // Set Prescaler to 256
    OPTION_REGbits.PS = 0b111;
    
    // enable Timer0 interrupt
    INTCONbits.TMR0IE = 1;

    // enable global interrupts
    ei();   
    
     
}

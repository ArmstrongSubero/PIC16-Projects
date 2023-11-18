/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 28_Sound
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program uses the KEYES KY-003 Hall Effect Sensor
 * 
 * Hardware Description: A Hall Effect sensor  is connected to PIN B0 and a 
 *                       SSD1306 OLED is connected as per header file.
 *
 *                      
 * Created April 15st, 2017, 12:26 PM
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
      
    /////////////////////
    // Setup OLED
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
     
     T0CKIPPSbits.T0CKIPPS = 0x08;   //RB0->TMR0:T0CKI;
  
     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
     
    ///////////////////////
    /// Configure Timer0
    //////////////////////
    
    // Select counter mode
    OPTION_REGbits.TMR0CS = 1;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 1;
    
    // Zero Timer
    TMR0 = 0;
    
    // Enable timer0 interrupts and clear interrupt flag
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0; 
     
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
}

/*******************************************************************************
 * Function: int ReadTimer(void)
 *
 * Returns: int readVal;
 *
 * Description: Returns the value of Timer0
 * 
 * Usage: int x;
 *        x = ReadTimer();
 ******************************************************************************/

uint8_t ReadTimer0(void)
{
    // Read value variable
    uint8_t readVal;

    // Set variable to timer0 value
    readVal = TMR0;

    // return value
    return readVal;
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
   
    // clear OLED
    OLED_Clear();
    
    __delay_ms(1000);
    
    // count variable
    uint8_t count = 0;
  
    while(1){ 
         
        // read timer with count
        count = ReadTimer0();
        
         OLED_YX(0, 0);
         OLED_Write_String("Current Count");
         
         OLED_YX(1, 0);
         OLED_Write_Integer(count);
         __delay_ms(1000);
         
     
         OLED_Clear();
    }
    
    return;   
}




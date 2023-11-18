/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 22_SPI
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      SPI interface
 *                      
 *           
 * Hardware Description: A HD44780 LCD is connected via PORTD and a MCP4131
 *                       digital potentiometer is connected as follows:
 *                        
 *                       Vss --> Vss
 *                       Vdd --> Vdd
 *                       SS  --> RD1
 *                       SCK --> RC3
 *                       SDI --> RC5
 *                       POB --> GND
 *                       POW --> LED via 1k resistor
 *                       POA --> Vdd
 *                     
 *                      
 * Created November 10th, 2016, 4:42 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"
#include "SPI.h"

void digiPot_write(int i);

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
    
    
    // Initialize LCD
    Lcd_Init();
    __delay_ms(100);
    Lcd_Clear();
    
    // Setup PORTC for SPI
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
     
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    SSPDATPPSbits.SSPDATPPS = 0x14;   //RC4->MSSP:SDI;
    RC3PPSbits.RC3PPS = 0x10;   //RC3->MSSP:SCK;
    RC5PPSbits.RC5PPS = 0x11;   //RC5->MSSP:SDO;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    
    // Initialize SPI
    SPI_Initialize();

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
    
    // Digipot variable
    int i;
    
    Lcd_Set_Cursor(1,1);
    __delay_ms(5);
    Lcd_Write_String("SPI Ready");
    __delay_ms(1000);
    Lcd_Clear();
    
    while(1){
       
      // Seven bit resolution
      for (i = 0; i <= 128; i++){  
          // Write Value
          digiPot_write(i);
          
          // Write to LCD
          Lcd_Set_Cursor(1,1);
          __delay_ms(5);
          Lcd_Write_Integer(i);
          __delay_ms(250);
          Lcd_Clear();
      }
    }
    
    return;
    
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Writes a particular value to a MCP4131 digital potentiometer 
 * 
 * Usage: digiPot_write(x);
 ******************************************************************************/

void digiPot_write(int i){
    // Set SS Low
    LATDbits.LATD1 = 0;
    
    // Slave address
    SPI_Exchange8bit(0x00);
    
    // Data
    SPI_Exchange8bit(i);
    
    // Set SS High
    LATDbits.LATD1 = 1;
}
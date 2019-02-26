/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I12_Nokia5110
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version: 1.0     
 *                
 * Program Description: This Program Allows PIC16F1717 to interface to a DHT11
 *                      temperature and humidity sensor
 *                      
 * Hardware Description: A Nokia 5110 LCD is connected via a logic level Conveter
 *                       as follows:
 *                        
 *                       Vcc  --> Vdd
 *                       Gnd  --> Vss
 *                       SCE  --> D0
 *                       RST  --> D1
 *                       DC   --> D2  (Via 10 k resistor)
 *                       SCK  --> RC3
 *                       MOSI --> RC5
 *                       LED  --> Vdd (Via 1k resistor)
 *                     
 *                       and the Data Pin of the DHT11 sensor is connected to
 *                       PIN D3
 * 
 * Created September 11th, 2018, 12:04 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "SPI.h"
#include "Nokia5110.h"
#include "DHT11.h"


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
    RC3PPSbits.RC3PPS = 0x10;         //RC3->MSSP:SCK;
    RC5PPSbits.RC5PPS = 0x11;         //RC5->MSSP:SDO;

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
    
    //Initialize LCD and clear screen
    LCD5110_init();
    LCD5110_clearScreen();
    
    char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
    char Checksum;
     
    while(1)
    {
       // Send start pulse to DHT11
       DHT11_Init();          
       
       // Wait for response
       DHT11_Check();
    
       // read 40-bit data from DHT11 module 
       RH_Integral = DHT11_Read();  
       RH_Decimal  = DHT11_Read();   
       T_Integral  = DHT11_Read();   
       T_Decimal   = DHT11_Read();    
       Checksum    = DHT11_Read();    
    
       
       // Display Humidity
       LCD5110_send(0x40 + 0, 0); //Y address
       LCD5110_send(0x80 + 0, 0); //X address
       LCD5110_sendString("Hum");
       LCD5110_send(0x40 + 0, 0); //Y address
       LCD5110_send(0x80 + 30, 0); //X address
       LCD5110_writeInteger(RH_Integral);
       
       
       // Display Temperature
       LCD5110_send(0x40 + 1, 0); //Y address
       LCD5110_send(0x80 + 0, 0); //X address
       LCD5110_sendString("Tem");
       LCD5110_send(0x40 + 1, 0); //Y address
       LCD5110_send(0x80 + 30, 0); //X address
       LCD5110_writeInteger(T_Integral);
     
  
      // check addition of humidity and temperature value equals to checksum 
      if(Checksum != (RH_Integral + RH_Decimal + T_Integral + T_Decimal))
      {  
       //Write text routines
       LCD5110_send(0x40 + 20, 0); //Y address
       LCD5110_send(0x80 + 0, 0);  //X address
       LCD5110_sendString("Error");
      }
        
     else
     {    
       //Write text routines
       LCD5110_send(0x40 + 20, 0); //Y address
       LCD5110_send(0x80 + 0, 0);  //X address
       LCD5110_sendString("No Err");
     }
    
      __delay_ms(1000);
      LCD5110_clearScreen();   
    }
    
    return;
}


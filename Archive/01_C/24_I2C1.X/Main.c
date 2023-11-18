/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 24_I2C
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      I2C interface
 *                      
 *           
 * Hardware Description: A HD44780 LCD is connected via PORTD and a 24LC16B
 *                       EEPROM chip is connected to the I2C bus
 *                        
 *                      
 * Created November 10th, 2016, 8:02 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"
#include "I2C.h"

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

int block_address = 0x00;   // Set the eeprom block address that we will write the data to
int word_address = 0x00;    // Set the eeprom word address that we will write the data to 
int eeprom_data = 0x09;     // This is the data  we are going to write
int incoming_data;


/*******************************************************************************
 * Function: void initmain(void)
 *
 * Returns: Nothing
 *
 * Description: Initializations for main
 ******************************************************************************/

void initmain(void){
     internal_16();
  
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
     
     //Setup for LCD
     TRISD = 0;
     ANSELD = 0;
    
     //Setup LCD
     Lcd_Init();
     __delay_ms(1000);
     Lcd_Clear();

}

/*******************************************************************************
 * Function: void main(void)
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void)
{
    initmain();
    I2C_Init();
    
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("I2C Ready");
    __delay_ms(1000);
    Lcd_Clear();

    while (1)
    {
       ///////////////////////////
       // Write EEPROM
       //////////////////////////
        
       Lcd_Set_Cursor(1,1);
       Lcd_Write_String("Write");
       __delay_ms(1000);
       Lcd_Clear();
       
       Send_I2C_StartBit();                    // send start bit
       Send_I2C_ControlByte(block_address,0);  // send control byte with R/W bit set low
       Send_I2C_Data(word_address);            // send word address
       Send_I2C_Data(eeprom_data);             // send data byte
       Send_I2C_StopBit();                     // send stop bit
       __delay_ms(200);
      
       /////////////////////////////
       // Read EEPROM
       ////////////////////////////
       
       Lcd_Set_Cursor(1,1);
       Lcd_Write_String("Read");
       __delay_ms(1000);
       Lcd_Clear();
       
      Send_I2C_StartBit();                    // send start bit
      Send_I2C_ControlByte(block_address,0);  // send control byte with R/W bit set low
      Send_I2C_Data(word_address);            // send word address

      Send_I2C_StartBit();                    // send start bit
      Send_I2C_ControlByte(block_address,1);  // send control byte with R/W bit set high
      incoming_data = Read_I2C_Data();        // now we read the data coming back from the eeprom
      Send_I2C_NAK();                         // send a the NAK to tell the eeprom we don't want any more data
      Send_I2C_StopBit();                     // and then send the stop bit
       
      Lcd_Set_Cursor(1,1);

      Lcd_Write_Integer(incoming_data);
      __delay_ms(1000);

      Lcd_Clear();
      
    }
}




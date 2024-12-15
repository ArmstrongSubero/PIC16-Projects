/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: P01_Temperature
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program gives a reading in celcius based on the 
 *                      output of a LM34 temperature sensor. The output is
 *                      displayed on an OLED.
 *           
 * Hardware Description: A LM34 is connected to PIN E0 and a SSD1306 OLED is
 *                       connected to the I2C bus.
 *                     
 *                      
 * Created March 22nd, 2017, 8:15 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"


int block_address = 0x00;   // Set the eeprom block address that we will write the data to
//int word_address = 0x04;    // Set the eeprom word address that we will write the data to 

int device_address = 0x0A;   // Set the eeprom block address that we will write the data to 
int incoming_data;

// result to store ADC conversion
float result;
    
// variables for conversion
float cel = 0.0;
          
// pointer for conversion
float *celsius = &cel;

void Read_Temperature();
void Write_Temperature(int word_address);
void Display_Temperature(int word_address);



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
    //////////////////
    
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
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();
  
    while(1){ 
        
        for (int i = 0; i <= 3; i++){
            Read_Temperature();
            Write_Temperature(i);
        }
        
       for (int i = 0; i <= 3; i++){
            Display_Temperature(i);   
        }
        
        // Update every second
        __delay_ms(1000);
    }
    
    return;
    
}


void Read_Temperature()
{   
     float conversion10;
     float farenheit; 
    
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
      *celsius = (farenheit - 32) * 5/9;
}

void Write_Temperature(int word_address)
{ 
       OLED_YX(0, 0);
       OLED_Write_String("Write");
       OLED_YX(1, 0);
       OLED_Write_Integer((int)*celsius);
       
       __delay_ms(1000);
       OLED_Clear();
       
       Send_I2C_StartBit();                    // send start bit
       Send_I2C_ControlByte(block_address,0);  // send control byte with R/W bit set low
       Send_I2C_Data(word_address);            // send word address
       Send_I2C_Data((int)*celsius);             // send data byte
       Send_I2C_StopBit();                     // send stop bit
}

void Display_Temperature(int word_address)
{
 
       OLED_YX(0, 0);
       OLED_Write_String("Get");
       __delay_ms(1000);
       
       Send_I2C_StartBit();                    // send start bit
       Send_I2C_ControlByte(block_address,0);  // send control byte with R/W bit set low
       Send_I2C_Data(word_address);            // send word address

      Send_I2C_StartBit();                    // send start bit
      Send_I2C_ControlByte(block_address,1);  // send control byte with R/W bit set high
      incoming_data = Read_I2C_Data();        // now we read the data coming back from the eeprom
      Send_I2C_NAK();                         // send a the NAK to tell the eeprom we don't want any more data
      Send_I2C_StopBit();                     // and then send the stop bit
       
      OLED_YX(1, 6);
      OLED_Write_Integer(word_address);
      
      OLED_YX(1, 0);
      OLED_Write_Integer(incoming_data);
      
      __delay_ms(1000);

      OLED_Clear();
   
}
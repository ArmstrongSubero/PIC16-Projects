/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: P03_IoT_WiFi
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program gives a reading in Celsius based on the 
 *                      output of a LM34 temperature sensor which is then sent
 *                      via WiFi using the ESP8266 ESP-12-F the output of which 
 *                      can be read in an web browser.  The program uses the
 *                      watchdog timer initially with a timeout of 4s then
 *                      once the server is operational has a timeout of 128s
 *                      after which the server will reboot.
 *           
 * Hardware Description: A LM34 is connected to PIN E0 and a SSD1306 OLED is
 *                       connected to the I2C bus. The ESP8266 is connected as 
 *                       follows:
 *                        GND    -> GND
 *                        TX     -> RB3
 *                        RX     -> RB2
 *                        GPIO15 -> GND
 *                        GPIO2  -> VCC
 *                        RST    -> VCC
 *                        EN     -> VCC
 *                        VCC    -> VCC
 *                     
 *                        External interrupt is connected to PINB0
 *                      
 * Created March 31st, 2017, 10:57 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include "EUSART.h"
#include <string.h>

    
// Buffer for UART transactions
char buf[50];

// Function prototypes
float Read_Temperature();
void server_Initialize();


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
    // Setup All Serial
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
     
     // Setup pins for EUSART
     RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
     RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;

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
    
    // Set E0 as ADC input channel5
    ANSELEbits.ANSE0 = 1;
     
    
    /////////////////////
    // Setup EUSART Pins
    /////////////////////
    
    // Setup PINS
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    //////////////////////////////////
    // Configure watchdog timer
    //////////////////////////////////
    
    // Set watchdog timeout for 4 seconds
    WDTCONbits.WDTPS = 0b01100;
    
    TRISDbits.TRISD1 = 1; 
    ANSELDbits.ANSD1 = 1;
    
   
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    
    /////////////////////////
    /// Configure Interrupts
    ////////////////////////
    
    // unlock PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00;
    
    // Set Interrupt pin to pin B0
    INTPPSbits.INTPPS = 0b01000;
    
    // lock   PPS 
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01; 
    
    // Trigger on falling edge
    OPTION_REGbits.INTEDG = 0;
    
    // Clear external interrupt flag
    INTCONbits.INTF = 0;
    
    //  Enable external interrupt
    INTCONbits.INTE = 1;
    
    // Enable global interrupt
    ei();
 
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
    
    CLRWDT();
    
    // Initialize EUSART
    EUSART_Initialize(9600);
     
    // Indicate start of server
    OLED_YX(0, 0);
    OLED_Write_String("START SERVER");
    __delay_ms(2000);
    
    CLRWDT();
    
    // Initialize the sever
    server_Initialize();
    
    // temperature variable
    float temp;
    
    while(1){ 
        
         // Clear OLED
         OLED_Clear();
         
         /////////////////////////////////
         // Read and Display temperature
         ////////////////////////////////
         temp = Read_Temperature();
         
         OLED_YX(0, 0);
         OLED_Write_String("Temperature:");
         OLED_YX(1, 0);
         OLED_Write_Integer(temp);
         __delay_ms(1000);
         OLED_Clear();
         
         /////////////////////////////////
         // Convert temperature to string
         ////////////////////////////////
         char* buff11;
         int status;
    
         buff11 = itoa(&status, temp, 10);
         strcat(buff11, "\r\n");
          
         /////////////////////////////////
         // Wait for connection request
         /////////////////////////////////
         EUSART_Read_Text(buf, 20); 
         
         //////////////////////////////////////
         // Display some of the received data
         /////////////////////////////////////
         OLED_YX(1, 0);
         OLED_Write_String(buf);
         __delay_ms(3000);
         OLED_Clear();
         
         ///////////////////////////////////////////
         // Send the temperature as 2 bytes of data
         //////////////////////////////////////////
         OLED_YX(0, 0);
         OLED_Write_String("Sending Data");
         EUSART_Write_Text("AT+CIPSEND=0,2\r\n");
        __delay_ms(5000);
        
         EUSART_Write_Text(buff11);
         
         EUSART_Read_Text(buf, 10); 
         OLED_YX(1, 0);
         OLED_Write_String(buf);
         __delay_ms(3000);
         OLED_Clear();
  
         /////////////////////////
         // Close connection
         ////////////////////////
         
         EUSART_Write_Text("AT+CIPCLOSE=0\r\n");
         __delay_ms(1000);
        
         EUSART_Read_Text(buf, 10); 
         OLED_YX(1, 0);
         OLED_Write_String(buf);
         __delay_ms(3000);
         OLED_Clear();
         
         // Reset EUSART
         RC1STAbits.SPEN = 0; 
         RC1STAbits.SPEN = 1; 
         
         // one this is complete clear watchdog
         CLRWDT();
    }
    
    return;   
}


/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Interrupt triggered on pushbutton press
 ******************************************************************************/

void interrupt isr(void){
    // Clear interrupt flag
    INTCONbits.INTF = 0;
    
    // Set watchdog timeout for 4 seconds
    WDTCONbits.WDTPS = 0b01100;
    
    // Re-initialize server
    server_Initialize();
}

/*******************************************************************************
 * Function: void server_Initialize(void)
 *
 * Returns: Nothing
 *
 * Description: Sets up ESP8266 as single connection server on port 80
 ******************************************************************************/
float Read_Temperature()
{   
     float conversion10;
     float farenheit; 
     float celsius;
     float result;
    
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
      
      return celsius;
}


/*******************************************************************************
 * Function: void server_Initialize(void)
 *
 * Returns: Nothing
 *
 * Description: Sets up ESP8266 as single connection server on port 80
 ******************************************************************************/

void server_Initialize()
{
    
        ///////////////////////
        // Send AT Command
        ///////////////////////
         CLRWDT();
         OLED_YX(0, 0);
         OLED_Write_String("Sending AT");
         EUSART_Write_Text("AT\r\n");
         EUSART_Read_Text(buf, 11);   
        
         OLED_YX(1, 0);
         OLED_Write_String(buf);
         __delay_ms(3000);
         OLED_Clear(); 
   
        ///////////////////////////////
        // Enable Single Connection
        ///////////////////////////////
         
         CLRWDT();
         OLED_YX(0, 0);
         OLED_Write_String("Sending CIPMUX");
         EUSART_Write_Text("AT+CIPMUX=0\r\n");
         EUSART_Read_Text(buf, 15);   
        
        OLED_YX(1, 0);
        OLED_Write_String(buf);
        __delay_ms(3000);
        OLED_Clear();
         
        CLRWDT();
        
        //////////////////////////////////
        // Configure as server on port 80
        //////////////////////////////////
        OLED_YX(0, 0);
        OLED_Write_String("Sending CIPSERVER");
        EUSART_Write_Text("AT+CIPSERVER=1,80\r\n");
         
        EUSART_Read_Text(buf, 15);   
        
        OLED_YX(1, 0);
        OLED_Write_String(buf);
        
        __delay_ms(3000);
        OLED_Clear();  
        
        CLRWDT();
        
        // Set watchdog timeout for 128 seconds
        WDTCONbits.WDTPS = 0b10001;
}


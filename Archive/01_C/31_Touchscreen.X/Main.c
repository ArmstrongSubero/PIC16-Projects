/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 31_Touchscreen
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate with a 
 *                      NX3224T024_011 2.4 inch Nextion Display. The display
 *                      communicates with the microcontroller via UART and
 *                      sends messages to the microcontroller which is displayed
 *                      on the SSD1306 OLED.
 *           
 * Hardware Description: A Nextion 2.4 inch touch screen and SSD1306 OLED is 
 *                       connected to the microcontroller as per header file.
 * 
 * Created April 15th, 2017, 9:30 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "EUSART.h"
#include "oled.h"
#include <string.h>
#include <stdbool.h>

// buffer for UART
char buf[50];

// Function prototypes
void touchscreen_command(char* string);

void moto_func(char* buf);
void plan_func(char* buf);
void conn_func(char* buf);
void bulb_func(char* buf);

////////////////////////////
// Bool support
///////////////////////////

typedef unsigned char bool;

#define true 1
#define false 0

// boolean for current state
bool on = false;

 
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
    
    // Setup pins for I2C
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
     
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    
    ///////////////////////
    // Setup Serial Comms
    ///////////////////////
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
    
    // Initialize EUSART module with 9600 baud
    EUSART_Initialize(9600);
    __delay_ms(2000);
    
    // Dim Touchscreen
    OLED_YX(0, 0);
    OLED_Write_String("Dim Screen");
  
    touchscreen_command("dim=30");
     
    // Update Touchscreen
    OLED_YX(0, 0);
    OLED_Write_String("Update Screen");
    
    touchscreen_command("t3.txt=\"16\"");
      
    OLED_Clear(); 
         
    while(1){
        
        // Read EUSART
        EUSART_Read_Text(buf, 11);
       
        // Check for which checkbox triggered
        bulb_func(buf);
        moto_func(buf);
        plan_func(buf);
        conn_func(buf);   
    }
    
    return;   
}

/*
 Send commands to Touchscreen
 */
void touchscreen_command(char* string)
{
    EUSART_Write_Text(string);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    EUSART_Write(0xFF);
    __delay_ms(1000);
}


/*
 Bulb Function Routines
 */
void bulb_func(char* buf)
{
   char* bulb1;
    
   bulb1 = strstr(buf, "bulb");
   
   if (bulb1 == NULL)
   {
       return;
   }
   
   else
   {
       if (!on){
       OLED_YX(0, 0);
       OLED_Write_String("Bulb On");
       __delay_ms(1000); 
       OLED_Clear(); 
       
        on = true;
       }
       
       else {
           OLED_YX(0, 0);
           OLED_Write_String("Bulb Off");
           __delay_ms(1000); 
           OLED_Clear(); 
       
          on = false; 
       }
   }
}

/*
 Motor function Routines
 */
void moto_func(char* buf)
{
   char* moto1;
    
   moto1 = strstr(buf, "moto");
   
   if (moto1 == NULL)
   {
       return;
   }
   
   else
   {
       if (!on){
       OLED_YX(0, 0);
       OLED_Write_String("Motor On");
       __delay_ms(1000); 
       OLED_Clear(); 
       
        on = true;
       }
       
       else {
           OLED_YX(0, 0);
           OLED_Write_String("Motor Off");
           __delay_ms(1000); 
           OLED_Clear(); 
       
          on = false; 
       }
   } 
}

/*
 Plant function routines
 */
void plan_func(char* buf)
{
   char* plant1;
    
   plant1 = strstr(buf, "plan");
   
   if (plant1 == NULL)
   {
       return;
   }
   
   else
   {
       if (!on){
       OLED_YX(0, 0);
       OLED_Write_String("Plant On");
       __delay_ms(1000); 
       OLED_Clear(); 
       
        on = true;
       }
       
       else {
           OLED_YX(0, 0);
           OLED_Write_String("Plant Off");
           __delay_ms(1000); 
           OLED_Clear(); 
       
          on = false; 
       }
   } 
}


/*
 Connection Function Routines
 */
void conn_func(char* buf)
{
   char* conn1;
    
   conn1 = strstr(buf, "conn");
   
   if (conn1 == NULL)
   {
       return;
   }
   
   else
   {
       if (!on){
       OLED_YX(0, 0);
       OLED_Write_String("Connected");
       __delay_ms(1000); 
       OLED_Clear(); 
       
        on = true;
       }
       
       else {
           OLED_YX(0, 0);
           OLED_Write_String("Disconnected");
           __delay_ms(1000); 
           OLED_Clear(); 
       
          on = false; 
       }
   } 
}
/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I18_DS1302
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to interface with a 
 *                      DS1302 time keeping chip.
 * 
 * Hardware Description: The DS1302 is connected to the microcontroller as 
 *                       follows:
 * 
 *                      CE   ->  RD0
 *                      SCLK ->  RD1
 *                      IO   ->  RD2 
 *                      
 *                       An SSD1306 is connected as per header file
 *                      
 * Created April 18th, 2017, 12:43 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include "ds1302.h"
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
     
     // Setup RTCC pins
     TRISD = 0;
     ANSELD = 0;
   
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
    
    __delay_ms(500);
   
    // clear OLED
    OLED_Clear();
    
    __delay_ms(500);
    
    // Initial time and date
    byte sec = 0;
    byte min = 59;
    byte hr = 10;
    byte day = 2;
    byte date = 18;
    byte month = 4;
    byte year = 17;
     
    // Initialize DS1302
    DS1302_Initialize(sec, min, hr, day, date, month, year);
    

    while(1){
          
          // Variables for string to be placed on OLED
          unsigned char yr1, mn1, date1, dy1, hr1, min1, sec1, line1[8];
          unsigned char yr2, mn2, date2, dy2, hr2, min2, sec2, line2[8];
          
          
          // Read DS1302 
          DS1302_Reset();
          DS1302_WriteByte(0xBF);	// clock burst 
		  
		  sec1 = DS1302_ReadByte();
          min1 = DS1302_ReadByte();
          hr1 = DS1302_ReadByte();
          date1 = DS1302_ReadByte();
          mn1 = DS1302_ReadByte();
          dy1 = DS1302_ReadByte();
          yr1 = DS1302_ReadByte();
          
          DS1302_Reset();
        
          // Convert all BCD data to Decimal time format
          
          // Year
          yr2 = (yr1 >> 4) * 10;
          yr2 += (yr1 & 15);
          
          // Month
          mn2 = (mn1 >> 4) * 10;
          mn2 = (mn1 & 15);
          
          // Date
          date2 = (date1 >> 4) * 10;
          date2 += (date1 & 15);
          
          // Hour
          hr2 = (hr1 >> 4) * 10;
          hr2 += (hr1 & 15);
          
          // Minute
          min2 = (min1 >> 4) * 10;
          min2 += (min1 & 15);
          
          // Seconds
          sec2 = (sec1 >> 4) * 10;
          sec2 += (sec1 & 15);
          
          
          /*
          line2[0]=((date2/10) % 10)+0x30;
          line2[1]=((date2) % 10)+0x30;
          line2[2]=0x2F; //symbol "/"
          line2[3]=((mn2/10) % 10)+0x30;
          line2[4]=((mn2) % 10)+0x30;
          line2[5]=0x2F;
          line2[6]=((yr2/10) % 10)+0x30;
          line2[7]=((yr2) % 10)+0x30;
          */
          
          
          // Array containing time in HH:MM:SS format
          line1[0]=((hr2/10) % 10)+0x30;
          line1[1]=((hr2) % 10)+0x30;
          line1[2]=0x3A; //symbol ":"
          line1[3]=((min2/10) % 10)+0x30;
          line1[4]=((min2) % 10)+0x30;
          line1[5]= 0x3A; // symbol ":"
          line1[6]=((sec2/10) % 10)+0x30;
          line1[7]=((sec2) % 10)+0x30;
           
         
          // Write time to OLED
          OLED_YX(0, 0);
          OLED_Write_String("Time: ");  
         
          OLED_YX(0, 6);
          OLED_Write_String(line1); 
    }
    
    return;
    
}


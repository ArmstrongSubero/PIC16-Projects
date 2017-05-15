/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 21_EUSART
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      EUSART module to a NEO-6M GPS module and display Latitude
 *                      and Longitude coordinates on an LCD.
 *           
 * Hardware Description: A NEO-6M GPS module is connected to the PIC16F1717 as
 *                       follows:
 *                        
 *                       PPS -> NC               
 *                       RXD -> TX
 *                       TXD -> RX
 *                       GND -> GND
 *                       VCC -> VCC
 *           
 *                      
 * Created April 18th, 2017, 12:51 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "EUSART.h"
#include "LCD.h"
#include <string.h>

// Variables 
volatile char c;
volatile char d;
   
char* data;
    
static char uartBuffer[300];
int i;
  
char* terminator;
char conversionString[8];

double lat = 0.0;
double lon = 0.0;

double *longitude = &lon;
double *latitude  = &lat;

// Function prototype
void read_gps();

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
    
    
    // Setup PINS
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISD = 0;
    ANSELD = 0;
    PORTD = 0;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
    RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    // set up UART 1 receive interrupt
    PIE1bits.RCIE = 1;
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
    Lcd_Init();
    Lcd_Clear();
    
    // Initialize EUSART module with 9600 baud
    EUSART_Initialize(9600);
    
    // give the module time to stabilize
    __delay_ms(100);
  
     
    while(1){
    
         Lcd_Set_Cursor(1,1);
              
         read_gps();
         
         // Write Latitude
         Lcd_Write_Float(*latitude);
      
         Lcd_Set_Cursor(2,1);
              
         // Write Longitude
         Lcd_Write_Float(*longitude);
         
         __delay_ms(2000);
         Lcd_Clear();  
    }
      
      
    return;
    
}


/*******************************************************************************
 * Function: void read_gps()
 *
 * Returns: Pointers to lat and lon
 *
 * Description: Function to read the GPS module
 * 
 * Usage: read_gps()
 ******************************************************************************/

void read_gps(){
    
    // Read characters from UART into buffer
    for(i=0; i<sizeof(uartBuffer)-1; i++)
    {
        d = EUSART_Read_Char(c);
        uartBuffer[i] = d;
    }
        
    // Last character is null terminator
    uartBuffer[sizeof(uartBuffer)-1] = '\0';
        
    
    // Look for needle in haystack to find string for GPGLL
    data = strstr(uartBuffer, "$GPGLL");   
    
    // if null exit
    if(data == NULL)
    {
        return;
    }
    
    // Find terminator
    terminator = strstr(data,",");
    
    
    // if null exit
    if(terminator == NULL)
    {
        return;
    }
    
    // If the first byte of the latitude field is ',', there is no info
    // so exit

    if(data[7] == ',')
    {
        return;
    }
    
    
    ///////////////////////////////////
    // Search buffer data for Latitude 
    // and Longitude values
    //////////////////////////////////
     
    data = terminator+1;
    
    terminator = strstr(data,",");
    
    if(terminator == NULL)
    {
        return;
    }
    
    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 2);
    *latitude = atof(conversionString);
    
    data += 2;
    *terminator = '\0';
    *latitude += (atof(data)/60);
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    if(*data == 'S')
    {
        *latitude *= -1;
    }

    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    memset(conversionString,0,sizeof(conversionString));
    memcpy(conversionString, data, 3);
    *longitude = atof(conversionString);
    
    data += 3;
    *terminator = '\0';
    *longitude += (atof(data)/60);
    
    data = terminator+1;
    terminator = strstr(data,",");
    if(terminator == NULL)
    {
        return;
    }
    if(*data == 'W')
    {
        *longitude *= -1;
    }
    
}
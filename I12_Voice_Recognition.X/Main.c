/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I12_Voice_Recognition
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      EUSART module to a EMIC 2 TTS module.
 *                      
 *           
 * Hardware Description: A EMIC 2 TTS module is connected to the PIC16F1717 as
 *                       follows:
 * 
 *                       RB2-> SIN;
 *                       RB3-> SOUT;
 *                       
 *                       The other pins on the EMIC2 TTS are connected as per 
 *                       datasheet.
 *                      
 * Created February 25th, 2017, 9:55 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "EUSART.h"
#include "LCD.h"
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
    
    
    // Setup PINS
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISDbits.TRISD0 = 0;
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
    
    TRISD = 0x00;
    ANSELD = 0x00;
    PORTD = 0x00;
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
    Lcd_Set_Cursor(1,1);
    
    // Write String
    Lcd_Write_String("Starting Now");
    
    __delay_ms(1000);
    

    // Initialize EUSART module with 9600 baud
    EUSART_Initialize(9600);
    
    // give the module time to stabilize
    __delay_ms(1000);
    Lcd_Clear();
    
     // Write String
      Lcd_Set_Cursor(1,1);
      Lcd_Write_String("Sending Command");
      __delay_ms(1000);
      Lcd_Clear();
    
      EUSART_Write(0xAA);
      EUSART_Write(0x05);
      EUSART_Write(0x30);
      EUSART_Write(0x00);
      EUSART_Write(0x01);
      EUSART_Write(0x02);
      EUSART_Write(0x0A);
      
     uint8_t boo[];
     
     int a;
     
     int x;
     int i;
     int y;
     
     int z;
    
    while(1){
        y = EUSART_Read();
        
        if (y = 170){
            
           
            boo[x] = EUSART_Read();
            
            
            x++;
            
           if (x == 10){
                break;
           }
        }
        
        for (int i = 0; i <= 5; i++){
            
            if (i > 0){
             Lcd_Set_Cursor(1,1);
             Lcd_Write_Integer(boo[i]);
             __delay_ms(3000);
             Lcd_Clear();
            }
        }
        
     
     
     
     //if (boo == 13) {
         //LATDbits.LATD0 = 1;
        // __delay_ms(2000);
     //}
    
     //else{
       //  LATDbits.LATD0 = 0;
    // }
      
    }
    
    return;
    
}

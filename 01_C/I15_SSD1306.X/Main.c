/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I08_SSD1306
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC16F1717 to be connected to a 
 *                      SSD1306 via the I2C bus. It demonstrates writing strings
 *                      together with writing integers and floating point
 *                      numbers.
 * 
 * Hardware Description: A SSD1306 based OLED is connected to a PIC16F1717 via 
 *                       a logic level converter to a SSD1306 based OLED as 
 *                       follows:
 *                        
 *                       GND --> GND
 *                       VCC --> VCC
 *                       SCL --> RC5
 *                       SDA --> RC4
 *                      
 * Created Friday 10th March, 2017, 8:05 PM
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

    __delay_ms(100);
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();
    
    // variables for counting
    int count = 0;
    float dec = 0.0;

        while ( 1 ) {
            
            /////////////////////
            // Strings
            ///////////////////
            
             OLED_YX( 0, 0 );
             OLED_Write_String( "OLED SSD1306" );
         
             OLED_YX(1, 0);
             OLED_Write_String ("No Buffer");
         
             OLED_YX(2, 0);
             OLED_Write_String("For XC8");
         
             OLED_YX(3,0);
             OLED_Write_String("by Armstrong");
             
             __delay_ms(1000);
             OLED_Clear();
            __delay_ms(100);
            
            /////////////////////
            // Integer Count
            ////////////////////
            
            for (count = 0; count <= 100; count++){
                OLED_YX( 0, 0 );
                OLED_Write_String( "Integer Count:" );
                OLED_YX(2, 0);
                OLED_Write_Integer(count);
                __delay_ms(100);
            }
            
            OLED_Clear();
            __delay_ms(100);
            
            
            //////////////////////
            // Float Count
            /////////////////////
            
            for(dec = 0.0; dec <= 20.0; dec+= 0.5)
            {
                OLED_YX( 0, 0 );
                OLED_Write_String( "Float Count:" );
                OLED_YX(2, 0);
                OLED_Write_Float(dec);
                __delay_ms(100);          
            }
            
           
            __delay_ms(100);
            OLED_Clear();
   }
    
    return; 
    
}

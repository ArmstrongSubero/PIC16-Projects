/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I08_Joystick
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                           
 * Program Description: This demonstrates using a joystick with a pic 
 *                      microcontroller.
 *                      
 * Hardware Description: The "Up-Down" potentiometer on the joystick is 
 *                       connected to PIN B0 and the "Left-Right" potentiometer
 *                       is connected to PIN B1. A 2x16 LCD with a
 *                       Samsung KS0066U controller is connected to PORTD as per
 *                       header file.
 *                                          
 * Created January 15th, 2017, 1:54 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"


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
    
    
    ////////////////////
    // Configure Ports
    ///////////////////
    TRISD = 0;
    PORTD = 0;
    ANSELD = 0;
    
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 1;
    
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSB1 = 1;
    
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
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
    
    // Initialize LCD
    Lcd_Init();
    __delay_ms(100);
    Lcd_Clear();
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
    
    // variables to store conversion result
    int result;
    int result1;

    // RB0 = AN12
    // RB1 = AN10
    
    while(1){
      // Turn ADC on
      ADCON0bits.ADON = 1;
      
     // Set input channel to AN12
     ADCON0bits.CHS = 0b01100;
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL);
    
  
     // Set input channel to AN10
     ADCON0bits.CHS = 0b01010;
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result1 = ((ADRESH<<8)+ADRESL);
    
      // Write result to LCD
      Lcd_Set_Cursor(1,1);
      __delay_ms(5);
     
      if (result == 0){
          Lcd_Write_String("Up");
      }
      
      else if (result == 1023){
          Lcd_Write_String("Down");
      }
      
      if (result1 == 0){
          Lcd_Write_String("Right");
      }
      
      else if (result1 == 1023){
          Lcd_Write_String("Left");
      }
      
      // Update every second
      __delay_ms(1000);
      Lcd_Clear();
    }
     return;    
}


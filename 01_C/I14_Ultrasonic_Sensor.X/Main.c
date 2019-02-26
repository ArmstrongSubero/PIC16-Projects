/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Internal OSC @ 16MHz, 5v
 * Program: I07_Ultrasonic_Sensor
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                           
 * Program Description: This demonstrates using a HC-SR04 ultrasonic distance
 *                      sensor with a pic microcontroller.
 *                      
 * Hardware Description: PIN C4 is connected to echo and PIN C5 is connected
 *                       to trigger of the ultrasonic sensor.
 *                                          
 * Created January 15th, 2017, 2:14 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"

#define TRIGGER_PIN RC5


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
    
    
    // ===============
    // Ultrasonic Pins
    // ===============    
    //Set RC4 as input and RC5 as input
    TRISCbits.TRISC4 = 1;   //Echo
    TRISCbits.TRISC5 = 0;   //Trigger
    
    //Turn off PORTC analog
    ANSELC = 0;

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
    
    //Initialize Timer1
    T1CON = 0x10; 
    
    // Variables
    int a;
    int ones;
    int tens;
    int hundreds;
    
    while(1){
        TMR1H = 0;                //Sets the Initial Value of Timer
        TMR1L = 0;                //Sets the Initial Value of Timer  
   
        TRIGGER_PIN = 1;          //TRIGGER HIGH
        __delay_us(10);           //10uS Delay 
        TRIGGER_PIN = 0;          //TRIGGER LOW

        while(!RC4);              //Waiting for Echo
        T1CONbits.TMR1ON = 1;     //Timer Starts
        while(RC4);               //Waiting for Echo goes LOW
        T1CONbits.TMR1ON = 0;     //Timer Stops

        a = (TMR1L | (TMR1H<<8)); //Reads Timer Value
        a = a/58.8;               //Converts Time to Distance
        a = a/2;                  //Timer Calibration
        a = a + 1;                //Distance Calibration
  
        // Ones
        ones = a % 10;
    
        // Tens 
        a = a/10;
        tens = a%10;
    
        // Hundreds
        a = a/10;
        hundreds = a%10;  
        
        Lcd_Write_Integer(hundreds);
        Lcd_Write_Integer(tens);
        Lcd_Write_Integer(ones);
     
        // Update every second
        __delay_ms(1000);
        Lcd_Clear();
    }
     return;    
}


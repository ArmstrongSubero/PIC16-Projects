/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F1719
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "I2C.h"
#include "oled.h"
#include "mcc_generated_files/pwm3.h"
#include <string.h>
#include <math.h>

float roundf(float x)
{
    return floor(x + 0.5f);
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
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
     
    // Set A0 as input
    TRISAbits.TRISA0 = 1;
    
    // Set A0 as analog
    ANSELAbits.ANSA0 = 1;
    
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
    ADCON0bits.CHS = 0b00000;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
       
    
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

    uint16_t convertedValue;
    uint16_t result;
    
    float outVolt;
    float desiredVolt = 13.8;
    float finalVolt;
       
    // Turn ADC on
    ADCON0bits.ADON = 1;
    
    uint16_t duty = 950;
    
    uint16_t minDuty = 800;
   
    PWM3_LoadDutyValue(duty); 
   
    int i;
    
    // 255
    while (1)
    {
        
        
        for (i = 0; i<= 10; i++)
        {
            // Sample CH0
            __delay_us(10);
            ADCON0bits.GO = 1;
            while (ADCON0bits.GO_nDONE);
      
            // Store ADC result
            result = ((ADRESH<<8)+ADRESL);
            
            outVolt = (float)result * 0.0050;  // get 5v value
            outVolt *= 6;                      // get 15v value
            finalVolt = roundf(outVolt);
               
               
            if (finalVolt < desiredVolt)
            {
                duty--;
                
                if (duty < minDuty)
                {
                    duty == minDuty;
                    
                }
                PWM3_LoadDutyValue(duty);
                
        
            }
            
            
            else if (finalVolt > desiredVolt)
            {
                duty++;
                PWM3_LoadDutyValue(duty);
           
           
            } 
            
            else if (finalVolt == desiredVolt)
            {
                duty = duty;
                PWM3_LoadDutyValue(duty);
                __delay_ms(5000);
            }
     
               
            __delay_ms(100);
            
        }
        
          OLED_YX( 0, 0 );
          OLED_Write_String( "Voltage:" );
          OLED_YX(2, 0);
          OLED_Write_Float(desiredVolt);  
    }
}
/**
 End of File
*/
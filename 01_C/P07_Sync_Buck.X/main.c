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
#include <string.h>
#include <math.h>
#include "I2C.h"
#include "oled.h"
#include "mcc_generated_files/pwm3.h"


float roundedVal(float x)
{
    float value = (int)(x * 100 + .5); 
    return (float)value / 100; 
}


#define BAT_MIN 11.5  // minimum battery voltage for 12V system
#define BAT_MAX 15.5 // maximum battery voltage for 12V system
#define BULK_CH_SP 14.2 // bulk charge set point for sealed lead acid battery // flooded type set it to 14.6V
#define FLOAT_CH_SP 13.8  //float charge set point for lead acid battery
#define LVD 11.5 //Low voltage disconnect setting for a 12V system

float bat_v = 0.0;
float *bat_volt = &bat_v;

float panel_v = 0.0;
float *panel_volt = &panel_v;

int system_v = 0;
int *system_volt = &system_v;

float bulk_charge_sp=0;
float float_charge_sp=0;
float lvd;
int charge_status = 0.0;
float solar_volt=0.0;
float Current = 0.0;
float intervolt;

/*****************PID Loop Variables*******************************************/
double setpoint, measured_value, error, output;
double previous_error = 0, integral = 0;
double Kp = 10, dt = 5, Ki = 2; 


void pid(unsigned int feedback, unsigned int setpoint);
void read_current(void);
void read_voltage(void);
void read_panel(void);

void system_voltage();
void set_point();
void set_volt();
void set_current();
void print_data();
void p_control();
void pid_control();

// 50% = 199 
float duty = 150.0;

float outVolt;
float finalVolt;   
uint16_t read;

    
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
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
    

    // Initialize I2C
    I2C_Init();
    __delay_ms(500);
    
    // Initialize OLED
    OLED_Init();
    __delay_ms(500);
   
    // clear OLED
    OLED_Clear();
    __delay_ms(100);
    
    
    // Set A0 as input
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    
    // Set A0 as analog
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;
    ANSELAbits.ANSA2 = 1;
 
    
    ////////////////////
    // Configure ADC
    ///////////////////
    
    // Fosc/32 ADC conversion time is 2.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is VDD
    ADCON1bits.ADPREF = 0b00;
    
    // Set input channel to AN0
    ADCON0bits.CHS = 0b00000;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;
    
    // Turn ADC on
    ADCON0bits.ADON = 1;
    
    // Load PWM
    PWM3_LoadDutyValue(90);
    
    while (1)
    {  
        read_panel();
        read_voltage();
        read_current();
        
        system_voltage();
        set_point();
        
        pid_control();
        print_data();        
   }
    return;
}

/*******************************************************************************
 * Function Implementations
 ******************************************************************************/

///////////////////////////////////////////////
// PID Loop Implementation
//////////////////////////////////////////////
void pid_control()
{
    setpoint = FLOAT_CH_SP;
    measured_value = *bat_volt;
         
    error = setpoint - measured_value;
    integral = integral + error*dt;
    output = Kp*error + Ki*integral;
    previous_error = error;
         
    duty = output;
        
    if (duty > 396) 
    {
        duty = 396;
    }
        
    if (duty < 40)
    {
        duty = 40;
    }
    
    PWM3_LoadDutyValue(duty);
}

///////////////////////////////////////////////
// Read Current
//////////////////////////////////////////////
void read_current()
{
    uint16_t convertedValue;
    float Voltage = 0;
    
    // Set input channel to AN0
    ADCON0bits.CHS = 0b00001;
    
      //Voltage is Sensed 1000 Times for precision
        for(int i = 0; i < 200; i++) {
            // Sample CH0
            __delay_us(10);
            ADCON0bits.GO = 1;
            while (ADCON0bits.GO_nDONE);
      
            // Store ADC result
            convertedValue = ((ADRESH<<8)+ADRESL); 
     
            Voltage = (Voltage + (.0049 * convertedValue));   // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
            __delay_ms(1);
      }
        
        Voltage = Voltage/200;                                // calculate average voltage
        
        Current = (Voltage - 2.5)/ 0.100;                      // Sensed voltage is converted to current
        Current = roundedVal(Current); 
}


///////////////////////////////////////////////
// Read Battery Voltage
//////////////////////////////////////////////
void read_voltage(void) 
{
    float sum = 0;
    float avg = 0;
    
    uint16_t result;
    
    // Set input channel to AN0
    ADCON0bits.CHS = 0b00000;
    
    for(int i = 0; i<= 200; i++)
    {
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL); 
     
      sum = sum + result;
     
      __delay_ms(2);
    }
     
    avg = sum / 200;
    
    float vin;
      
    vin = (avg * 5.0) / 1024.0;
    intervolt = vin;
    
    // cal = 17 / 1.825 = 9.315
    *bat_volt = intervolt * 6.0;
    
   
    if (*bat_volt < 0)
    {
     *bat_volt = 0;   
    }
    
    *bat_volt = roundedVal(*bat_volt);
}

///////////////////////////////////////////////
// Read Solar Panel Voltage
//////////////////////////////////////////////
void read_panel(void) 
{
    float sum = 0;
    float avg = 0;
    
    uint16_t result;
  
    // Set input channel to AN2
    ADCON0bits.CHS = 0b00010;
    
    for(int i = 0; i<= 200; i++)
    {
      // Sample CH0
      __delay_us(10);
      ADCON0bits.GO = 1;
      while (ADCON0bits.GO_nDONE);
      
      // Store ADC result
      result = ((ADRESH<<8)+ADRESL); 
     
      sum = sum + result;
     
      __delay_ms(2);
    }
     
    avg = sum / 200;
    
    
    float vin;
      
    vin = (avg * 5.0) / 1024.0;
    
    // cal = in / out
    *panel_volt = vin * 5.96;
   
   
    if (*panel_volt < 0)
    {
     *panel_volt = 0;   
    }
    
    *panel_volt = roundedVal(*panel_volt);
}

///////////////////////////////////////////////
// System Voltage
//////////////////////////////////////////////
void system_voltage(void)
{
    if ((*bat_volt > BAT_MIN) && (*bat_volt < BAT_MAX))
    {
        *system_volt = 12;
    }
     
    else if ((*bat_volt > BAT_MIN/2 ) && (*bat_volt < BAT_MAX/2))
    {
        *system_volt= 6;
    }   
}


///////////////////////////////////////////////
// Set Point
//////////////////////////////////////////////
void set_point(void)
{
  if (*system_volt == 12)
  {
     bulk_charge_sp = BULK_CH_SP;
     float_charge_sp = FLOAT_CH_SP;
     lvd = LVD;
  }
 
  else if(*system_volt == 6)
  {
     bulk_charge_sp = (BULK_CH_SP/2);
     float_charge_sp= (FLOAT_CH_SP/2);
     lvd = LVD/2;
  }
}
 

///////////////////////////////////////////////
// Print Data
//////////////////////////////////////////////
void print_data(void)
{
    // print battery voltage
    OLED_YX(0, 0 );
    OLED_Write_String( "Sol:" );
    OLED_YX(0, 6);
    OLED_Write_Float(*panel_volt); 
    
    //print current
    OLED_YX(1, 0 );
    OLED_Write_String( "Bat:" );
    OLED_YX(1, 6);
    OLED_Write_Float(*bat_volt); 
    
    // print solar voltage
    OLED_YX(2, 0 );
    OLED_Write_String( "Cur:" );
    OLED_YX(2, 6);
    OLED_Write_Float(Current);  
    
    // print charge status
    OLED_YX(3, 0 );
    OLED_Write_String( "Sta:" );
    OLED_YX(3, 6);
    
    if (charge_status == 0)
    {
        OLED_Write_String("Off");
    }
    
    else if (charge_status == 1)
    {
        OLED_Write_String("Bul");
    }
    
    else if (charge_status == 2)
    {
        OLED_Write_String("Flo");
    }  
}


/**
 End of File
*/
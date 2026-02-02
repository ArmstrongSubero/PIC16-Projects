/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 60_K_Type_Thermocouple
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: This Program reads a K-Type thermocouple using the 
 *                      MAX6675 and displays the temperature on an SSD1306 OLED.
 *                      Supports Celsius, Fahrenheit, and Kelvin display modes.
 *                      Button on RB3 cycles through temperature units. The 
 *                      K-Type thermocouple is rated for up to 1024 degrees 
 *                      Celsius. 
 * 
 * Hardware Description: 
 *     MAX6675 Connections:
 *         CS  -> RB0
 *         SCK -> RB1  
 *         SO  -> RB2
 *     
 *     SSD1306 OLED (I2C):
 *         SDA -> RC4 
 *         SCK -> RC5
 *     
 *     Button:
 *         Switch -> RB3 (active low, internal pullup)
 *                       
 * Created January 30th, 2026
 */

/*******************************************************************************
 * Includes and Defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "max6675.h"

// Button pin on RB3
#define BUTTON_TRIS     TRISBbits.TRISB3
#define BUTTON_ANSEL    ANSELBbits.ANSB3
#define BUTTON_PORT     PORTBbits.RB3
#define BUTTON_WPU      WPUBbits.WPUB3
#define BUTTON_PRESSED  (!BUTTON_PORT)

// Debounce delay
#define DEBOUNCE_MS     50

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void initMain(void);
void displayTemperature(float temp, uint8_t unit, uint8_t status);
const char* getUnitString(uint8_t unit);
const char* getUnitSymbol(uint8_t unit);

/*******************************************************************************
 * Function: void initMain(void)
 ******************************************************************************/
void initMain(void)
{
    // Run at 32 MHz
    internal_32();
    __delay_ms(10);
    
    //-------------------------------------------------------------------------
    // I2C pins for OLED
    //-------------------------------------------------------------------------
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    
    //-------------------------------------------------------------------------
    // PPS mapping for I2C
    //-------------------------------------------------------------------------
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 0;
    
    RC4PPSbits.RC4PPS = 0x11;       // RC4 -> SDA out
    SSPDATPPSbits.SSPDATPPS = 0x14; // SDA in <- RC4
    SSPCLKPPSbits.SSPCLKPPS = 0x15; // SCK in <- RC5
    RC5PPSbits.RC5PPS = 0x10;       // RC5 -> SCK out
    
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 1;
    
    //-------------------------------------------------------------------------
    // Button on RB3 with internal pull-up
    //-------------------------------------------------------------------------
    BUTTON_ANSEL = 0;       // Digital
    BUTTON_TRIS = 1;        // Input
    BUTTON_WPU = 1;         // Enable weak pull-up
    OPTION_REGbits.nWPUEN = 0;  // Enable global weak pull-ups
    
    //-------------------------------------------------------------------------
    // Initialize MAX6675
    //-------------------------------------------------------------------------
    MAX6675_Init();
}

/*******************************************************************************
 * Function: const char* getUnitString(uint8_t unit)
 ******************************************************************************/
const char* getUnitString(uint8_t unit)
{
    switch (unit)
    {
        case TEMP_FAHRENHEIT: return "Fahrenheit";
        case TEMP_KELVIN:     return "Kelvin";
        case TEMP_CELSIUS:
        default:              return "Celsius";
    }
}

/*******************************************************************************
 * Function: const char* getUnitSymbol(uint8_t unit)
 ******************************************************************************/
const char* getUnitSymbol(uint8_t unit)
{
    switch (unit)
    {
        case TEMP_FAHRENHEIT: return "F";
        case TEMP_KELVIN:     return "K";
        case TEMP_CELSIUS:
        default:              return "C";
    }
}

/*******************************************************************************
 * Function: void displayTemperature(float temp, uint8_t unit, uint8_t status)
 ******************************************************************************/
void displayTemperature(float temp, uint8_t unit, uint8_t status)
{
    if (status == MAX6675_THERMOCOUPLE_OK)
    {
        // Display temperature with unit
        // Using %d with manual decimal handling since OLED_Printf doesn't support %f
        int16_t temp_int = (int16_t)temp;
        uint8_t temp_frac = (uint8_t)((temp - (float)temp_int) * 10);
        if (temp_frac < 0) temp_frac = -temp_frac;
        
        OLED_Printf_Line(1, "Temp: %d.%d %s", temp_int, temp_frac, getUnitSymbol(unit));
        OLED_Printf_Line(2, "Mode: %s", getUnitString(unit));
    }
    else
    {
        OLED_Printf_Line(1, "TC OPEN!");
        OLED_Printf_Line(2, "Check wiring");
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();
    I2C_Init();
    
    OLED_Init();
    OLED_SetOrientation(OLED_ORIENT_0);
    OLED_Clear();
    
    // Display title
    OLED_Printf_Line(0, "MAX6675 K-TC");
    
    uint8_t unit = TEMP_CELSIUS;
    uint8_t status;
    float temperature = 0.0f;
    uint8_t button_was_pressed = 0;
    
    while (1)
    {
        //---------------------------------------------------------------------
        // Handle button press to change units
        //---------------------------------------------------------------------
        if (BUTTON_PRESSED)
        {
            if (!button_was_pressed)
            {
                __delay_ms(DEBOUNCE_MS);
                if (BUTTON_PRESSED)
                {
                    // Cycle through units: C -> F -> K -> C
                    unit++;
                    if (unit > TEMP_KELVIN)
                    {
                        unit = TEMP_CELSIUS;
                    }
                    button_was_pressed = 1;
                }
            }
        }
        else
        {
            button_was_pressed = 0;
        }
        
        //---------------------------------------------------------------------
        // Read temperature (single reading, use averaged for more stability)
        //---------------------------------------------------------------------
        status = MAX6675_ReadTemp(&temperature, unit);
        
        // For averaged readings (slower but more stable):
        // status = MAX6675_ReadTemp_Averaged(&temperature, unit, 4);
        
        //---------------------------------------------------------------------
        // Update display
        //---------------------------------------------------------------------
        displayTemperature(temperature, unit, status);
        
        // Small delay between readings
        // MAX6675 can do conversions every ~220ms for best accuracy
        __delay_ms(250);
    }
}
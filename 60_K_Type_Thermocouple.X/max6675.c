/*
 * File: MAX6675.c
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Compiler: XC8
 * 
 * Description: MAX6675 K-Type Thermocouple Interface Driver
 *              Bit-banged SPI communication
 *              
 * Protocol: The MAX6675 outputs 16 bits on falling edge of SCK:
 *           Bit 15: Dummy sign bit (always 0)
 *           Bit 14-3: 12-bit temperature data (MSB first)
 *           Bit 2: Thermocouple open flag (1 = open, 0 = connected)
 *           Bit 1: Device ID (always 0)
 *           Bit 0: Tri-state
 */

#include "max6675.h"
#include "PIC16F1718_Internal.h"

// Small delay for bit-bang timing (~1us at 32MHz)
#define SPI_DELAY() __delay_us(1)

/*******************************************************************************
 * void MAX6675_Init(void)
 * Initialize the MAX6675 interface pins
 ******************************************************************************/
void MAX6675_Init(void)
{
    // Disable analog functions on pins
    MAX6675_CS_ANSEL = 0;
    MAX6675_SCK_ANSEL = 0;
    MAX6675_SO_ANSEL = 0;
    
    // Configure pin directions
    MAX6675_CS_TRIS = 0;    // CS as output
    MAX6675_SCK_TRIS = 0;   // SCK as output
    MAX6675_SO_TRIS = 1;    // SO as input
    
    // Set initial states
    MAX6675_CS_LAT = 1;     // CS high (deselected)
    MAX6675_SCK_LAT = 0;    // SCK low (idle)
}

/*******************************************************************************
 * uint16_t MAX6675_ReadRaw(void)
 * Read raw 16-bit data from MAX6675
 ******************************************************************************/
uint16_t MAX6675_ReadRaw(void)
{
    uint16_t data = 0;
    uint8_t i;
    
    // Select the device
    MAX6675_CS_LAT = 0;
    SPI_DELAY();
    
    // Read 16 bits, MSB first
    // Data is shifted out on falling edge of SCK
    for (i = 0; i < 16; i++)
    {
        // Shift data left to make room for new bit
        data <<= 1;
        
        // Read the data bit BEFORE the clock pulse
        // MAX6675 presents data when CS goes low and on falling SCK edge
        if (MAX6675_SO_PORT)
        {
            data |= 0x0001;
        }
        
        // Clock pulse: high then low
        MAX6675_SCK_LAT = 1;
        SPI_DELAY();
        MAX6675_SCK_LAT = 0;
        SPI_DELAY();
    }
    
    // Deselect the device
    MAX6675_CS_LAT = 1;
    
    return data;
}

/*******************************************************************************
 * uint8_t MAX6675_ReadADC(uint16_t *adc_value)
 * Read temperature ADC value with status check
 ******************************************************************************/
uint8_t MAX6675_ReadADC(uint16_t *adc_value)
{
    uint16_t raw_data;
    
    raw_data = MAX6675_ReadRaw();
    
    // Check bit 2 for open thermocouple
    if (raw_data & 0x0004)
    {
        *adc_value = 0xFFFF;  // Invalid reading
        return MAX6675_OPEN_THERMOCOUPLE;
    }
    
    // Extract 12-bit temperature value (bits 14-3)
    // Shift right by 3 to remove lower bits, mask to 12 bits
    *adc_value = (raw_data >> 3) & 0x0FFF;
    
    return MAX6675_THERMOCOUPLE_OK;
}

/*******************************************************************************
 * uint8_t MAX6675_ReadADC_Averaged(uint16_t *adc_value, uint8_t samples)
 * Read averaged ADC value
 ******************************************************************************/
uint8_t MAX6675_ReadADC_Averaged(uint16_t *adc_value, uint8_t samples)
{
    uint32_t sum = 0;
    uint16_t reading;
    uint8_t i;
    uint8_t valid_samples = 0;
    
    // Limit samples
    if (samples == 0) samples = 1;
    if (samples > 32) samples = 32;
    
    for (i = 0; i < samples; i++)
    {
        if (MAX6675_ReadADC(&reading) == MAX6675_THERMOCOUPLE_OK)
        {
            sum += reading;
            valid_samples++;
        }
        
        // MAX6675 needs ~220ms between conversions for best accuracy
        // Using shorter delay for faster updates, adjust as needed
        __delay_ms(50);
    }
    
    if (valid_samples == 0)
    {
        *adc_value = 0xFFFF;
        return MAX6675_OPEN_THERMOCOUPLE;
    }
    
    *adc_value = (uint16_t)(sum / valid_samples);
    
    // Return OK only if all samples were valid
    return (valid_samples == samples) ? MAX6675_THERMOCOUPLE_OK : MAX6675_OPEN_THERMOCOUPLE;
}

/*******************************************************************************
 * float MAX6675_ConvertTemp(uint16_t adc_value, uint8_t unit)
 * Convert ADC value to temperature
 ******************************************************************************/
float MAX6675_ConvertTemp(uint16_t adc_value, uint8_t unit)
{
    float temp;
    
    // Convert to Celsius first (0.25°C per count)
    temp = (float)adc_value * MAX6675_RESOLUTION;
    
    switch (unit)
    {
        case TEMP_FAHRENHEIT:
            // Celsius to Fahrenheit: F = C * 1.8 + 32
            temp = (temp * 1.8f) + 32.0f;
            break;
            
        case TEMP_KELVIN:
            // Celsius to Kelvin: K = C + 273.15
            temp = temp + 273.15f;
            break;
            
        case TEMP_CELSIUS:
        default:
            // Already in Celsius
            break;
    }
    
    return temp;
}

/*******************************************************************************
 * uint8_t MAX6675_ReadTemp(float *temp, uint8_t unit)
 * Read temperature directly
 ******************************************************************************/
uint8_t MAX6675_ReadTemp(float *temp, uint8_t unit)
{
    uint16_t adc_value;
    uint8_t status;
    
    status = MAX6675_ReadADC(&adc_value);
    
    if (status == MAX6675_THERMOCOUPLE_OK)
    {
        *temp = MAX6675_ConvertTemp(adc_value, unit);
    }
    else
    {
        *temp = 0.0f;  // Invalid
    }
    
    return status;
}

/*******************************************************************************
 * uint8_t MAX6675_ReadTemp_Averaged(float *temp, uint8_t unit, uint8_t samples)
 * Read averaged temperature
 ******************************************************************************/
uint8_t MAX6675_ReadTemp_Averaged(float *temp, uint8_t unit, uint8_t samples)
{
    uint16_t adc_value;
    uint8_t status;
    
    status = MAX6675_ReadADC_Averaged(&adc_value, samples);
    
    if (status == MAX6675_THERMOCOUPLE_OK || adc_value != 0xFFFF)
    {
        *temp = MAX6675_ConvertTemp(adc_value, unit);
    }
    else
    {
        *temp = 0.0f;
    }
    
    return status;
}
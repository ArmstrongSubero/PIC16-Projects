/*
 * File: MAX6675.h
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Compiler: XC8
 * 
 * Description: MAX6675 K-Type Thermocouple Interface Driver
 *              Bit-banged SPI communication
 */

#ifndef MAX6675_H
#define MAX6675_H

#include <xc.h>
#include <stdint.h>

/*******************************************************************************
 * Pin Configuration - Adjust these for your hardware
 ******************************************************************************/
// Using PORTB pins for PIC16F1718
// CS  -> RB0
// SCK -> RB1
// SO  -> RB2
#define MAX6675_CS_TRIS     TRISBbits.TRISB0
#define MAX6675_SCK_TRIS    TRISBbits.TRISB1
#define MAX6675_SO_TRIS     TRISBbits.TRISB2

#define MAX6675_CS_LAT      LATBbits.LATB0
#define MAX6675_SCK_LAT     LATBbits.LATB1
#define MAX6675_SO_PORT     PORTBbits.RB2

#define MAX6675_CS_ANSEL    ANSELBbits.ANSB0
#define MAX6675_SCK_ANSEL   ANSELBbits.ANSB1
#define MAX6675_SO_ANSEL    ANSELBbits.ANSB2

/*******************************************************************************
 * Constants
 ******************************************************************************/
#define MAX6675_OPEN_THERMOCOUPLE   0x04
#define MAX6675_THERMOCOUPLE_OK     0x00

// Temperature units
#define TEMP_CELSIUS    0
#define TEMP_FAHRENHEIT 1
#define TEMP_KELVIN     2

// Conversion constants
#define MAX6675_RESOLUTION  0.25f   // 0.25°C per count

// Number of samples for averaging
#define MAX6675_AVG_SAMPLES 8

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * Initialize the MAX6675 interface pins
 */
void MAX6675_Init(void);

/**
 * Read raw 16-bit data from MAX6675
 * @return Raw 16-bit SPI data
 */
uint16_t MAX6675_ReadRaw(void);

/**
 * Read temperature with thermocouple status check
 * @param adc_value Pointer to store the 12-bit ADC value
 * @return MAX6675_THERMOCOUPLE_OK if connected, MAX6675_OPEN_THERMOCOUPLE if open
 */
uint8_t MAX6675_ReadADC(uint16_t *adc_value);

/**
 * Read temperature with averaging
 * @param adc_value Pointer to store the averaged 12-bit ADC value
 * @param samples Number of samples to average (1-32)
 * @return MAX6675_THERMOCOUPLE_OK if all readings valid, MAX6675_OPEN_THERMOCOUPLE if any open
 */
uint8_t MAX6675_ReadADC_Averaged(uint16_t *adc_value, uint8_t samples);

/**
 * Convert ADC value to temperature
 * @param adc_value 12-bit ADC reading
 * @param unit Temperature unit (TEMP_CELSIUS, TEMP_FAHRENHEIT, TEMP_KELVIN)
 * @return Temperature in specified unit
 */
float MAX6675_ConvertTemp(uint16_t adc_value, uint8_t unit);

/**
 * Read temperature directly (convenience function)
 * @param temp Pointer to store temperature value
 * @param unit Temperature unit (TEMP_CELSIUS, TEMP_FAHRENHEIT, TEMP_KELVIN)
 * @return MAX6675_THERMOCOUPLE_OK if valid, MAX6675_OPEN_THERMOCOUPLE if open
 */
uint8_t MAX6675_ReadTemp(float *temp, uint8_t unit);

/**
 * Read averaged temperature (convenience function)
 * @param temp Pointer to store temperature value
 * @param unit Temperature unit
 * @param samples Number of samples to average
 * @return MAX6675_THERMOCOUPLE_OK if valid, MAX6675_OPEN_THERMOCOUPLE if any open
 */
uint8_t MAX6675_ReadTemp_Averaged(float *temp, uint8_t unit, uint8_t samples);

#endif /* MAX6675_H */
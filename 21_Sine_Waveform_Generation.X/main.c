/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 21_Sine_Waveform_Generator
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 2.1
 *                
 * Program Description: Calibrated sine wave generator with frequency,
 *                      amplitude, and DC offset control effective range 
 *                      about 55 Hz to 1KHz. Default tuned for 1 kHz 
 * 
 * Hardware Description: Oscilloscope probe connected to pin RA2 (DAC1OUT1)
 *                       
 * Updated on Thursday 26th, December, 2025
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include <math.h>

#define TABLE_SIZE  256

// CALIBRATION: Overhead per sample in microseconds
// Adjust this value to calibrate frequency accuracy
#define LOOP_OVERHEAD_US  12  // Calibrated based on measurements

/*******************************************************************************
 * Sine Wave Configuration Structure
 ******************************************************************************/
typedef struct {
    uint16_t frequency_hz;  // Desired frequency in Hz
    uint8_t amplitude;      // Amplitude: 0-127 (0 = no signal, 127 = full swing)
    uint8_t dc_offset;      // DC offset: 0-255 (128 = centered at 2.5V)
    uint8_t table_skip;     // Skip samples for higher freq (1=all samples, 2=every other, etc)
} sine_config_t;

/*******************************************************************************
 * Global sine table
 ******************************************************************************/
uint8_t sineTable[TABLE_SIZE];

/*******************************************************************************
 * Function: void generateSineTable(uint8_t amplitude, uint8_t offset)
 ******************************************************************************/
void generateSineTable(uint8_t amplitude, uint8_t offset) 
{
    for(uint16_t i = 0; i < TABLE_SIZE; i++)
    {
        float sine_val = sin(i * 2.0 * M_PI / TABLE_SIZE);
        sineTable[i] = (uint8_t)(sine_val * amplitude + offset);
    }
}

/*******************************************************************************
 * Function: void delay_timer0_us(uint16_t us)
 ******************************************************************************/
void delay_timer0_us(uint16_t us)
{
    if (us == 0) return;
    
    // At 32 MHz: Fosc/4 = 8 MHz
    // With prescaler 1:2, Timer0 increments at 4 MHz
    // 1 us = 4 counts
    
    uint16_t counts = us << 2;  // Multiply by 4
    
    TMR0 = 0;
    INTCONbits.TMR0IF = 0;
    
    while(TMR0 < counts) {
        // Polling loop
    }
}

/*******************************************************************************
 * Function: uint16_t calculate_sample_delay(sine_config_t* config)
 *
 * Description: Calculate delay between samples with overhead compensation
 ******************************************************************************/
uint16_t calculate_sample_delay(sine_config_t* config)
{
    uint32_t period_us;
    uint16_t samples_per_cycle;
    uint16_t delay_us;
    
    if (config->frequency_hz == 0) return 1000;
    
    // Samples per cycle considering skip
    samples_per_cycle = TABLE_SIZE / config->table_skip;
    
    // Period in microseconds
    period_us = 1000000UL / config->frequency_hz;
    
    // Delay per sample
    delay_us = period_us / samples_per_cycle;
    
    // Subtract loop overhead
    if (delay_us > LOOP_OVERHEAD_US) {
        delay_us -= LOOP_OVERHEAD_US;
    } else {
        delay_us = 0;  // Running as fast as possible
    }
    
    return delay_us;
}

/*******************************************************************************
 * Function: void initMain()
 ******************************************************************************/
void initMain(){
    // Run at 32 MHz
    internal_32();
    __delay_ms(100);
    
    //////////////////////
    // Configure DAC1 (8-bit)
    /////////////////////
    
    // DAC enabled
    DAC1CON0bits.DAC1EN = 1;
    
    // DACOUT pin enabled
    DAC1CON0bits.DAC1OE1 = 1;
    
    // +ve source is Vdd
    DAC1CON0bits.DAC1PSS = 0;
    
    // -ve source is Vss
    DAC1CON0bits.DAC1NSS = 0;
    
    // Initial output is 0v
    DAC1CON1 = 0;
    
    ///////////////////////
    // Configure Timer0 for fast timing
    //////////////////////
    
    // Select timer mode (Fosc/4)
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 0;
    
    // Set Prescaler to 1:2 for fast counting
    OPTION_REGbits.PS = 0b000;
    
    // Zero Timer
    TMR0 = 0;
    INTCONbits.TMR0IF = 0;
}

/*******************************************************************************
 * Function: void generate_sine(sine_config_t* config)
 ******************************************************************************/
void generate_sine(sine_config_t* config)
{
    uint16_t index = 0;
    uint16_t sample_delay;
    
    // Generate the sine table with amplitude and offset
    generateSineTable(config->amplitude, config->dc_offset);
    
    // Calculate delay between samples
    sample_delay = calculate_sample_delay(config);
    
    while(1)
    {
        // Output current sample
        DAC1CON1 = sineTable[index];
        
        // Precise delay (compensated for overhead)
        if (sample_delay > 0) {
            delay_timer0_us(sample_delay);
        }
        
        // Advance index with skip
        index += config->table_skip;
        
        // Wrap around
        if (index >= TABLE_SIZE) {
            index = 0;
        }
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void) 
{
    initMain();
    
    sine_config_t my_sine;
    
    //===========================================================================
    // CONFIGURE YOUR SINE WAVE HERE
    //===========================================================================
    
    my_sine.frequency_hz = 1000;     // Target frequency in Hz
    my_sine.amplitude = 127;       // Amplitude: 0-127 (127 = full 5Vpp swing)
    my_sine.dc_offset = 128;       // DC offset: 0-255 (128 = centered at 2.5V)
    my_sine.table_skip = 4;        // Sample skip: 1=smooth, 2=faster/coarser
    
    //===========================================================================
    // CONFIGURATION GUIDE:
    //
    // FREQUENCY (frequency_hz):
    //   - 55 Hz to 100 Hz: Very smooth (table skip 1)
    //   - 150 Hz to 400 Hz: table skip 2
    //   - 100 Hz to 1 kHz: Excellent quality (table skip 2-4)
    //   - 1 kHz to 5 kHz: Good (consider table_skip 4+)
    //
    // AMPLITUDE (0-127):
    //   - 0: No signal
    //   - 64: Half amplitude (2.5Vpp centered)
    //   - 127: Full amplitude (5Vpp centered)
    //
    // DC OFFSET (0-255):
    //   - 0: Bottom rail (sine swings 0V to ~amplitude*2)
    //   - 128: Centered at 2.5V (recommended for symmetric swing)
    //   - 255: Top rail (sine swings down from 5V)
    //
    // TABLE_SKIP (1, 2, 4, 8):
    //   - 1: Use all 256 samples (smoothest)
    //   - 2: Use every other sample (128 samples, faster)
    //   - 4: Use every 4th sample (64 samples, high freq)
    //   - 8: Use every 8th sample (32 samples, very high freq)
    //
    // CALIBRATION:
    //   If frequency is still off after testing:
    //   - Measured frequency TOO LOW ? DECREASE LOOP_OVERHEAD_US
    //   - Measured frequency TOO HIGH ? INCREASE LOOP_OVERHEAD_US
    //   
    //   Current setting: LOOP_OVERHEAD_US = 12
    //===========================================================================
    
    // Generate the sine wave
    generate_sine(&my_sine);
    
    return;
}
/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 20_Ramp_Waveform_Generation
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 2.5
 *                
 * Program Description: Tunable ramp waveform generator using DAC1 
 *                      with Timer0 for precise microsecond timing
 * 
 * Hardware Description: Oscilloscope probe connected to pin RA2 (DAC1OUT1)
 *                       
 * Updated on Thursday 26th, December, 2025
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

// CALIBRATION: Overhead per step in microseconds
// Adjust this to fine-tune frequency accuracy
#define LOOP_OVERHEAD_US  12 // Typical DAC write + loop overhead

/*******************************************************************************
 * Ramp Configuration Structure
 ******************************************************************************/
typedef struct {
    uint8_t min_value;      // Start voltage (0-255): 0 = 0V, 255 = 5V
    uint8_t max_value;      // End voltage (0-255)
    uint8_t step_size;      // Increment per step (1-255)
    uint16_t frequency_hz;  // Desired frequency in Hz
    uint8_t mode;           // 0=sawtooth up, 1=triangle, 2=sawtooth down
    int8_t fine_tune;       // Fine tune: -127 to +127 (adjusts delay in microseconds)
} ramp_config_t;

/*******************************************************************************
 * Function: void delay_timer0_us(uint16_t us)
 * 
 * Description: Precise microsecond delay using Timer0 polling
 ******************************************************************************/
void delay_timer0_us(uint16_t us)
{
    if (us == 0) return;
    
    // At 32 MHz: Fosc/4 = 8 MHz
    // With prescaler 1:2, Timer0 increments at 4 MHz
    // 1 us = 4 counts
    
    uint16_t counts = us << 2;  // Multiply by 4 (us * 4)
    
    TMR0 = 0;
    INTCONbits.TMR0IF = 0;
    
    while(TMR0 < counts) {
        // Tight polling loop - very fast
    }
}

/*******************************************************************************
 * Function: uint16_t calculate_step_delay(ramp_config_t* config)
 ******************************************************************************/
uint16_t calculate_step_delay(ramp_config_t* config)
{
    uint16_t num_steps;
    uint32_t period_us;
    int32_t step_delay;  // Changed to signed for fine tuning
    
    // Calculate number of steps in one cycle
    if (config->mode == 1) {
        // Triangle: up AND down
        num_steps = ((config->max_value - config->min_value) / config->step_size) * 2;
    } else {
        // Sawtooth: only up OR down
        num_steps = (config->max_value - config->min_value) / config->step_size;
    }
    
    // Avoid division by zero
    if (num_steps == 0) num_steps = 1;
    if (config->frequency_hz == 0) return 1000;
    
    // Calculate period in microseconds
    period_us = 1000000UL / config->frequency_hz;
    
    // Calculate delay per step
    step_delay = period_us / num_steps;
    
    // Subtract loop overhead
    step_delay -= LOOP_OVERHEAD_US;
    
    // Apply fine tuning
    step_delay += config->fine_tune;
    
    // Minimum delay is 0 (run as fast as possible)
    if (step_delay < 0) step_delay = 0;
    
    return (uint16_t)step_delay;
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
    OPTION_REGbits.PS = 0b000;  // 1:2 prescaler = 4 MHz timer clock
    
    // Zero Timer
    TMR0 = 0;
    
    // Clear flag
    INTCONbits.TMR0IF = 0;
}

/*******************************************************************************
 * Function: void generate_ramp(ramp_config_t* config)
 ******************************************************************************/
void generate_ramp(ramp_config_t* config)
{
    uint8_t dac_value = config->min_value;
    int8_t direction = 1;
    uint16_t step_delay;
    
    // Calculate the step delay based on desired frequency
    step_delay = calculate_step_delay(config);
    
    // Set initial direction based on mode
    if (config->mode == 2) {
        dac_value = config->max_value;
        direction = -1;
    }
    
    while(1)
    {
        // Set DAC output
        DAC1CON1 = dac_value;
        
        // Precise delay using Timer0
        if (step_delay > 0) {
            delay_timer0_us(step_delay);
        }
        
        // Update value based on mode
        switch(config->mode)
        {
            case 0:  // Sawtooth up - FIXED VERSION
                // Check if next step would overflow
                if ((uint16_t)dac_value + config->step_size > config->max_value) {
                    dac_value = config->min_value;  // Reset to start
                } else {
                    dac_value += config->step_size;
                }
                break;
                
            case 1:  // Triangle wave
                if (direction > 0) {
                    if ((uint16_t)dac_value + config->step_size > config->max_value) {
                        dac_value = config->max_value;
                        direction = -1;
                    } else {
                        dac_value += config->step_size;
                    }
                } else {
                    if (dac_value <= config->min_value + config->step_size) {
                        dac_value = config->min_value;
                        direction = 1;
                    } else {
                        dac_value -= config->step_size;
                    }
                }
                break;
                
            case 2:  // Sawtooth down
                if (dac_value <= config->min_value + config->step_size) {
                    dac_value = config->max_value;
                } else {
                    dac_value -= config->step_size;
                }
                break;
        }
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void) 
{
    initMain();
    
    ramp_config_t my_ramp;
    
    //===========================================================================
    // CONFIGURE YOUR RAMP HERE
    //===========================================================================
    
    my_ramp.min_value = 0;         // Start voltage: 0-255 (0V to 5V)
    my_ramp.max_value = 255;       // End voltage: 0-255 (0V to 5V)
    my_ramp.step_size = 2;         // Step size: 1=smooth, higher=coarser
    my_ramp.frequency_hz = 500;    // Frequency in Hz
    my_ramp.mode = 1;              // Mode: 0=ramp up, 1=triangle, 2=ramp down
    my_ramp.fine_tune = -120;         // Fine tune: -127 to +127 microseconds
    
    //===========================================================================
    // TUNING GUIDE:
    //
    // COARSE TUNING (LOOP_OVERHEAD_US at top of file):
    //   - If ALL frequencies are consistently off by the same percentage
    //   - Adjust LOOP_OVERHEAD_US (currently 3)
    //   - Increase if frequencies too HIGH, decrease if too LOW
    //
    // FINE TUNING (fine_tune parameter):
    //   - For adjusting individual frequencies
    //   - Positive values = SLOWER frequency (add delay)
    //   - Negative values = FASTER frequency (reduce delay)
    //   
    //   Example: If 500 Hz measures as 480 Hz:
    //     - Too slow, need to speed up
    //     - Use negative fine_tune: my_ramp.fine_tune = -2;
    //   
    //   Example: If 500 Hz measures as 520 Hz:
    //     - Too fast, need to slow down
    //     - Use positive fine_tune: my_ramp.fine_tune = +2;
    //
    // FREQUENCY RANGE:
    //   - 1 Hz to 100 Hz: Very smooth with step_size=1
    //   - 100 Hz to 1 kHz: Excellent quality
    //   - 1 kHz to 10 kHz: Good (use step_size > 1 for very high freq)
    //
    // VOLTAGE CALCULATOR:
    //   Vout = (value / 256) × 5V
    //   Example: 128 = 2.5V, 64 = 1.25V, 192 = 3.75V
    //===========================================================================
    
    // Generate the ramp
    generate_ramp(&my_ramp);
    
    return;
}
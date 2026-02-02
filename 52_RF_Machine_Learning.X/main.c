/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 52_RF_Machine_Learning
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to use edge machine 
 *                      learning and demonstrates use of ML on the IRIS dataset.
 *                      This edge machine model uses less memory with a slight 
 *                      reduction in accuracy. 
 * 
 * Hardware Description: A CP2104 USB-UART converter is connected to TRISB2 and
 *                       TRISB3 
 *                       
 * Created Friday, January 30th, 2026, 2:25 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "ml.h" 

#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * Configuration
 ******************************************************************************/
#define RX_BUFFER_SIZE  48

// Class names matching the trained model
const char* class_names[ML_NUM_CLASSES] = {
    "Setosa",
    "Versicolor",
    "Virginica"
};

// Receive buffer
char rx_buffer[RX_BUFFER_SIZE];
unsigned char rx_index = 0;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void initMain(void);
void print_float(float val);
unsigned char parse_features(char *buffer, float *features);
void classify_and_print(float *features);
void run_demo(void);

/*******************************************************************************
 * Function: void initMain()
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);
    
    // TX pin
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    // RX pin
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    // PPS Setup
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;
    
    RB2PPSbits.RB2PPS = 0x14;   // RB2 -> TX
    RXPPSbits.RXPPS = 0x0B;     // RB3 -> RX
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;
}

/*******************************************************************************
 * Function: void print_float(float val)
 * Description: Print float with 1 decimal place
 ******************************************************************************/
void print_float(float val)
{
    int whole, frac;
    
    if (val < 0) {
        EUSART_Write('-');
        val = -val;
    }
    
    whole = (int)val;
    frac = (int)((val - (float)whole) * 10.0f);
    
    EUSART_Write_Integer(whole);
    EUSART_Write('.');
    EUSART_Write_Integer(frac);
}

/*******************************************************************************
 * Function: unsigned char parse_features()
 * Description: Parse comma-separated float values
 * Returns: Number of values parsed
 ******************************************************************************/
unsigned char parse_features(char *buffer, float *features)
{
    unsigned char count = 0;
    char *ptr = buffer;
    char *start = buffer;
    
    while (count < ML_NUM_FEATURES) {
        // Find comma or end
        while (*ptr != ',' && *ptr != '\0' && *ptr != '\r' && *ptr != '\n') {
            ptr++;
        }
        
        // Null-terminate this segment
        char end_char = *ptr;
        *ptr = '\0';
        
        // Parse the value
        if (strlen(start) > 0) {
            features[count] = (float)atof(start);
            count++;
        }
        
        // Move to next segment
        if (end_char == '\0' || end_char == '\r' || end_char == '\n') {
            break;
        }
        ptr++;
        start = ptr;
    }
    
    return count;
}

/*******************************************************************************
 * Function: void classify_and_print()
 * Description: Run classifier and print result
 ******************************************************************************/
void classify_and_print(float *features)
{
    signed char prediction;
    unsigned char i;
    
    // Print input
    EUSART_Write_Text("Input: [");
    for (i = 0; i < ML_NUM_FEATURES; i++) {
        print_float(features[i]);
        if (i < ML_NUM_FEATURES - 1) {
            EUSART_Write_Text(", ");
        }
    }
    EUSART_Write_Text("]\r\n");
    
    // Run prediction
    prediction = ml_predict(features);
    
    // Print result
    EUSART_Write_Text("Class: ");
    EUSART_Write_Text((char*)class_names[prediction]);
    EUSART_Write_Text(" (");
    EUSART_Write_Integer(prediction);
    EUSART_Write_Text(")\r\n");
}

/*******************************************************************************
 * Function: void run_demo()
 * Description: Run classifier on test samples
 ******************************************************************************/
void run_demo(void)
{
    // Test samples - one from each class
    float samples[3][ML_NUM_FEATURES] = {
        {5.1f, 3.5f, 1.4f, 0.2f},   // Setosa
        {6.0f, 2.9f, 4.5f, 1.5f},   // Versicolor
        {6.3f, 3.3f, 6.0f, 2.5f}    // Virginica
    };
    
    unsigned char i;
    
    EUSART_Write_Text("\r\n=== Demo Mode ===\r\n");
    
    for (i = 0; i < 3; i++) {
        EUSART_Write_Text("\r\nSample ");
        EUSART_Write_Integer(i + 1);
        EUSART_Write_Text(":\r\n");
        classify_and_print(samples[i]);
    }
    
    EUSART_Write_Text("\r\n=== Done ===\r\n");
}

/*******************************************************************************
 * Function: Main
 ******************************************************************************/
void main(void) 
{
    uint8_t rx_char;
    float features[ML_NUM_FEATURES];
    unsigned char num_parsed;
    
    initMain();
    EUSART_Initialize(19200);
    __delay_ms(500);
    
    // Welcome message
    EUSART_Write_Text("\r\n");
    EUSART_Write_Text("=========================\r\n");
    EUSART_Write_Text(" PIC16 ML Classifier\r\n");
    EUSART_Write_Text("=========================\r\n");
    EUSART_Write_Text("Commands:\r\n");
    EUSART_Write_Text("  d = Demo\r\n");
    EUSART_Write_Text("  Or send: 5.1,3.5,1.4,0.2\r\n");
    EUSART_Write_Text("=========================\r\n");
    EUSART_Write_Text("> ");
    
    // Clear buffer
    memset(rx_buffer, 0, RX_BUFFER_SIZE);
    rx_index = 0;
    
    while(1)
    {
        if (PIR1bits.RCIF) {
            rx_char = EUSART_Read();
            EUSART_Write(rx_char);  // Echo
            
            if (rx_char == '\r' || rx_char == '\n') {
                EUSART_Write_Text("\r\n");
                rx_buffer[rx_index] = '\0';
                
                // Process input
                if (rx_index > 0) {
                    if (rx_buffer[0] == 'd' || rx_buffer[0] == 'D') {
                        run_demo();
                    }
                    else {
                        // Try to parse as features
                        num_parsed = parse_features(rx_buffer, features);
                        
                        if (num_parsed == ML_NUM_FEATURES) {
                            classify_and_print(features);
                        }
                        else {
                            EUSART_Write_Text("Error: Need ");
                            EUSART_Write_Integer(ML_NUM_FEATURES);
                            EUSART_Write_Text(" values\r\n");
                        }
                    }
                }
                
                EUSART_Write_Text("> ");
                memset(rx_buffer, 0, RX_BUFFER_SIZE);
                rx_index = 0;
            }
            else if (rx_index < RX_BUFFER_SIZE - 1) {
                rx_buffer[rx_index++] = (char)rx_char;
            }
        }
    }
}
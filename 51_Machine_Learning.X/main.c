/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 51_Machine_Learning
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to use edge machine 
 *                      learning and demonstrates use of ML on the IRIS dataset.
 *                      This edge machine model uses more memory but has good 
 *                      accuracy. 
 * 
 * Hardware Description: A CP2104 USB-UART converter is connected to TRISB2 and
 *                       TRISB3 
 *                       
 * Created Friday, January 30th, 2026, 2:15 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "ml.h"
#include <stdlib.h>
#include <string.h>

#define RX_BUFFER_SIZE  64

/* Global variables */
char rx_buffer[RX_BUFFER_SIZE];
unsigned char rx_index = 0;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void initMain(void);
void print_menu(void);
void print_float(float val);
unsigned char parse_features(char *buffer, float *features);
void process_command(char *buffer);
void run_demo(void);


/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/
void initMain(void)
{
    // Run at 32 MHz
    internal_32();
    
    // Allow PLL startup time
    __delay_ms(100);
    
    // Setup TX pin
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    // Setup RX pin
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    // Setup PPS for EUSART
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;
    
    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS = 0x0B;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;
}

/*******************************************************************************
 * Function: void print_menu()
 ******************************************************************************/
void print_menu(void)
{
    EUSART_Write_Text("\r\n");
    EUSART_Write_Text("================================\r\n");
    EUSART_Write_Text("  PIC16 SVM Iris Classifier\r\n");
    EUSART_Write_Text("================================\r\n");
    EUSART_Write_Text("Commands:\r\n");
    EUSART_Write_Text("  d - Run demo\r\n");
    EUSART_Write_Text("  h - Help\r\n");
    EUSART_Write_Text("  Or: SL,SW,PL,PW\r\n");
    EUSART_Write_Text("  Ex: 5.1,3.5,1.4,0.2\r\n");
    EUSART_Write_Text("================================\r\n");
    EUSART_Write_Text("> ");
}

/*******************************************************************************
 * Function: void print_float(float val)
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
 ******************************************************************************/
unsigned char parse_features(char *buffer, float *features)
{
    unsigned char count = 0;
    char *token;
    char *saveptr = buffer;
    
    while (count < ML_NUM_FEATURES) {
        token = saveptr;
        while (*saveptr != ',' && *saveptr != '\0' && *saveptr != '\r' && *saveptr != '\n') {
            saveptr++;
        }
        
        if (*saveptr != '\0') {
            *saveptr = '\0';
            saveptr++;
        }
        
        if (strlen(token) > 0) {
            features[count] = (float)atof(token);
            count++;
        }
        
        if (*saveptr == '\0' || *saveptr == '\r' || *saveptr == '\n') {
            break;
        }
    }
    
    return count;
}

/*******************************************************************************
 * Function: void run_demo()
 ******************************************************************************/
void run_demo(void)
{
    float test_samples[3][ML_NUM_FEATURES] = {
        {5.1f, 3.5f, 1.4f, 0.2f},
        {6.0f, 2.9f, 4.5f, 1.5f},
        {6.3f, 3.3f, 6.0f, 2.5f}
    };
    
    unsigned char i, j;
    signed char prediction;
    
    EUSART_Write_Text("\r\n--- Demo ---\r\n");
    
    for (i = 0; i < 3; i++) {
        EUSART_Write_Text("\r\nSample ");
        EUSART_Write_Integer(i + 1);
        EUSART_Write_Text(": [");
        
        for (j = 0; j < ML_NUM_FEATURES; j++) {
            print_float(test_samples[i][j]);
            if (j < ML_NUM_FEATURES - 1) {
                EUSART_Write_Text(", ");
            }
        }
        EUSART_Write_Text("]\r\n");
        
        prediction = ml_predict(test_samples[i]);
        
        EUSART_Write_Text("Result: ");
        EUSART_Write_Text((char*)ml_get_class_name(prediction));
        EUSART_Write_Text("\r\n");
    }
    
    EUSART_Write_Text("\r\n--- Done ---\r\n");
}

/*******************************************************************************
 * Function: void process_command()
 ******************************************************************************/
void process_command(char *buffer)
{
    float features[ML_NUM_FEATURES];
    signed char prediction;
    unsigned char num_parsed;
    unsigned char i;
    
    if (strlen(buffer) == 0) {
        return;
    }
    
    if (buffer[0] == 'd' || buffer[0] == 'D') {
        run_demo();
        EUSART_Write_Text("> ");
        return;
    }
    
    if (buffer[0] == 'h' || buffer[0] == 'H' || buffer[0] == '?') {
        print_menu();
        return;
    }
    
    num_parsed = parse_features(buffer, features);
    
    if (num_parsed != ML_NUM_FEATURES) {
        EUSART_Write_Text("Error: Need 4 values\r\n");
        EUSART_Write_Text("> ");
        return;
    }
    
    EUSART_Write_Text("\r\nInput: [");
    for (i = 0; i < ML_NUM_FEATURES; i++) {
        print_float(features[i]);
        if (i < ML_NUM_FEATURES - 1) {
            EUSART_Write_Text(", ");
        }
    }
    EUSART_Write_Text("]\r\n");
    
    prediction = ml_predict(features);
    
    EUSART_Write_Text("Result: ");
    EUSART_Write_Text((char*)ml_get_class_name(prediction));
    EUSART_Write_Text("\r\n> ");
}

/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/
void main(void) 
{
    uint8_t rx_char;
    
    initMain();
    EUSART_Initialize(19200);
    __delay_ms(500);
    
    print_menu();
    
    memset(rx_buffer, 0, RX_BUFFER_SIZE);
    rx_index = 0;
    
    while(1)
    {
        if (PIR1bits.RCIF) {
            rx_char = EUSART_Read();
            EUSART_Write(rx_char);
            
            if (rx_char == '\r' || rx_char == '\n') {
                EUSART_Write_Text("\r\n");
                rx_buffer[rx_index] = '\0';
                process_command(rx_buffer);
                memset(rx_buffer, 0, RX_BUFFER_SIZE);
                rx_index = 0;
            }
            else if (rx_char == 0x08 || rx_char == 0x7F) {
                if (rx_index > 0) {
                    rx_index--;
                    rx_buffer[rx_index] = '\0';
                    EUSART_Write_Text(" \b");
                }
            }
            else if (rx_index < RX_BUFFER_SIZE - 1) {
                rx_buffer[rx_index++] = (char)rx_char;
            }
        }
    }
}

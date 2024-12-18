/*
 * File: PIC16F1719_Internal.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 32MHz, 5v
 * Program: Header file to setup PIC16F1719
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version:
 * 2.1
 *     * Updated for PIC16F1719
 *     * Updated Compiler and IDE versions
 * 2.0
 *     * Separated file into Header and C source file
 *     * Changed comments and layout
 *                  
 * Program Description: This program header will allows setup of configuration
 *                      bits and provides routines for setting up internal
 *                      oscillator and includes all devices and MCU modules
 *
 * Created on Friday 17th, November 2023, 9:56 PM
 ******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
// PIC16F1717 Configuration Bit Settings

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR and can be enabled with ZCDSEN bit.)
#pragma config PLLEN = OFF      // Phase Lock Loop enable (4x PLL is enabled when software sets the SPLLEN bit)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

//XC8 Standard Include
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

//Other Includes
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>


//For delay routines
#define _XTAL_FREQ 32000000

//MCU Modules Includes


//Internal oscillator setup
void internal_32(); // 32 MHz
void internal_16(); // 16 MHz
void internal_8();
void internal_4();
void internal_2();
void internal_1();
void internal_31(); // 31 kHz






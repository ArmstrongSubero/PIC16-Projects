/*
 * File: bool_support.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 I2C
 * Compiler: XC8 (v1.35, MPLAX X v3.10)
 * Program Version 1.0
 *                  
 * Program Description: This program header will allow addition of simple bool
 *                      support to XC8
 *
 * Created on March 10th, 2017, 8:00 PM
 */



////////////////////////////
// Bool support
///////////////////////////

typedef unsigned char bool;

#define true 1
#define false 0

// boolean for current state
bool on = false;
;
; File:     main.S
; Target:   PIC16F1718
; Author:   Armstrong Subero
; Compiler: pic-as (v2.30), MPLABX V5.45
;                
; Program Description: This Program Allows PIC16F1718 to Turn on an LED
; 
; Hardware Description: An LED is connected via a 1K resistor to PIN C3 
;                       and a pushbutton is connected via a 10k resistor to 
;                       PIN B0
;                       
; Created Spetember 25th, 2022, 8:45 PM
; Last Updated: Spetember 25th, 2022, 8:45 PM
 

PROCESSOR 16F1718
#include <xc.inc>
    
;configuration word 1
 CONFIG FOSC=INTOSC         // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
 CONFIG WDTE=OFF,PWRTE=OFF  // WDT & PWRT disabled
 CONFIG MCLRE=ON            // MCLR/VPP pin function is MCLR
 CONFIG CP=OFF              // Program & data memory unprotected
 CONFIG BOREN=ON            // Brown-out Reset enabled
 CONFIG CLKOUTEN=OFF        // CLKOUT function is disabled
 CONFIG IESO=ON             // Internal/External Switchover mode enabled
 CONFIG FCMEN=ON            // Fail-Safe Clock Monitor enabled

;configuration word 2
CONFIG WRT=OFF             // Write protection off
CONFIG PLLEN=ON            // 4x PLL enabled
CONFIG STVREN=ON           // Stack Over/underflow will cause a Reset
CONFIG BORV=LO             // Brown-out Reset Voltage low trip point
CONFIG LPBOR = OFF         // Low power BOR disabled
CONFIG LVP=OFF             // Low-voltage programming enabled
 
PSECT resetVec, class=CODE, delta=2
resetVec:
    PAGESEL main
    goto main
    
PSECT code 
main:
    bsf PORTB, 0       // setup pushbutton as input
    banksel ANSELB
    bcf ANSELB, 0
    
    banksel TRISC      // setup LED as output
    clrf TRISC 
    banksel LATC
    clrf LATC

MainLoop:
    banksel PORTB      // determine if switch is pressed
    btfsc PORTB, 0
    bra LedOff
    
LedOn:
    banksel LATC      // LED on
    bsf LATC, 3 
    bra MainLoop

LedOff:
    banksel LATC       // LED off
    bcf LATC, 3

    bra MainLoop        ; loop forever
    
    END resetVec
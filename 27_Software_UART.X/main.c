/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 27_Software_UART
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Cleaned up code
 *                  * Added additional comments
 *                  * Upgraded from PIC16F1717 to PIC16F1719
 *                
 * Program Description: This Program allows the PIC16F1719 to use a software 
 *                      UART
 * 
 * Hardware Description: A USB to UART converter is connected to PIN RE1
 *
 *                      
 * Created April 15st, 2017, 12:26 PM
 * Updated November 26th, 2023, 5:08 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "swuart.h"

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/

void initMain(){
    // Run at 16 MHz
    internal_16();
     
    ///////////////////////
    // Setup SW UART 
    //////////////////////
    TRISE = 0;
    ANSELE = 0;
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();

     // Initialize SW UART
     SUART_Init(); 
     __delay_ms(1000);
  
    while(1){ 
        
      SUART_Write_Text("Hello");
      __delay_ms(1000);
    }
    
    return;   
}




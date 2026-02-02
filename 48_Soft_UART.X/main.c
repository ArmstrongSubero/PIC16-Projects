/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 48_Soft_UART
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to demonstrate use of 
 *                      a software UART library, in this example we transmit 
 *                      a character and add one to it then echo it back 
 * 
 * Hardware Description: A CP2014 USB-UART converter is connected as follows:
 *                       RX -> RB0 
 *                       TX -> RB1
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 29th, January, 2026, 6:22 PM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.3         Updated to MPLABX v6.20 using XC8 v2.46 for PIC16F1718
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "SEUSART.h"


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
    internal_32();
    __delay_ms(100);

    // RB0 = RX input, RB1 = TX output
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 0;

    // disable analog on both pins
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;

    // idle high
    LATBbits.LATB1 = 1;
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
    initMain();
    SUART_Init();
    __delay_ms(500);

    SUART_Write_Text("\r\n=== SW UART INCREMENT ECHO TEST ===\r\n");
    SUART_Write_Text("Type a key. I will echo (key+1).\r\n");
    SUART_Write_Text("Example: 'A' -> 'B'\r\n\r\n");

    while (1)
    {
        unsigned char rx = SUART_Receive();   // returns 0x00 on timeout/error

        if (rx != 0x00)
        {
            unsigned char tx = rx + 1;

            SUART_Write_Text("RX='");
            SUART_Write_Char(rx);
            SUART_Write_Text("'  TX='");
            SUART_Write_Char(tx);
            SUART_Write_Text("'\r\n");
        }

        __delay_ms(5);  // tiny delay only (optional)
    }
}

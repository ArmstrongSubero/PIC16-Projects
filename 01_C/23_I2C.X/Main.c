/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 22_SPI
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      SPI interface
 *                      
 *           
 * Hardware Description: A HD44780 LCD is connected via PORTD and a MCP4131
 *                       digital potentiometer is connected as follows:
 *                        
 *                       Vss --> Vss
 *                       Vdd --> Vdd
 *                       SS  --> RD1
 *                       SCK --> RC3
 *                       SDI --> RC5
 *                       POB --> GND
 *                       POW --> LED via 1k resistor
 *                       POA --> Vdd
 *                     
 *                      
 * Created November 10th, 2016, 4:42 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"
#include "I2C.h"

#define LC164_ADDRESS     0x50   // slave device address

uint8_t LC164_Read(uint8_t addrlo, uint8_t *pData)
{
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    static I2C_TRANSACTION_REQUEST_BLOCK trb[2];
    
    I2C_MasterWriteTRBBuild(&trb[0], &addrlo, 1, LC164_ADDRESS);
    I2C_MasterReadTRBBuild(&trb[1], pData, 1, LC164_ADDRESS);                
    I2C_MasterTRBInsert(2, &trb[0], &status);
    
    while(status == I2C_MESSAGE_PENDING);      // blocking

    return (status == I2C_MESSAGE_COMPLETE); 
} 

uint8_t LC164_Write(uint8_t addrlo, uint8_t data)
{
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;
    static I2C_TRANSACTION_REQUEST_BLOCK trb[2];
    uint8_t pack[2];
    pack[0] = addrlo;
    pack[1] = data;
    I2C_MasterWriteTRBBuild(&trb[0], pack, 2, LC164_ADDRESS);
    I2C_MasterTRBInsert(1, &trb[0], &status);
    
    while(status == I2C_MESSAGE_PENDING);      // blocking

    return (status == I2C_MESSAGE_COMPLETE); 
} 

void I2C_PIN_Initialize(void)
{
    LATB = 0x0;
    WPUE = 0x8;
    LATA = 0x0;
    LATC = 0x40;
    WPUA = 0xFF;
    WPUB = 0xFF;
    WPUC = 0x8F;
    ANSELA = 0x3F;
    ANSELB = 0x3F;
    ANSELC = 0x84;
    TRISE = 0x8;
    TRISB = 0xFF;
    TRISC = 0xB7;
    TRISA = 0xFF;

    OPTION_REGbits.nWPUEN = 0x1;

    // interrupts-on-change are globally disabled
    INTCONbits.IOCIE = 0;
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RC4PPSbits.RC4PPS = 0x0011;   //RC4->MSSP:SDA;
    RC6PPSbits.RC6PPS = 0x0014;   //RC6->EUSART:TX;
    SSPDATPPSbits.SSPDATPPS = 0x0014;   //RC4->MSSP:SDA;
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;   //RC5->MSSP:SCL;
    RC5PPSbits.RC5PPS = 0x0010;   //RC5->MSSP:SCL;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}
void initmain(){
     internal_16();
  
    // initialize the device
    I2C_PIN_Initialize();
    I2C_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    //Setup for LCD
    TRISD = 0;
    ANSELD = 0;
    
    //Setup LCD
    Lcd_Init();
    __delay_ms(1000);
    Lcd_Clear();

    Lcd_Set_Cursor(1,1);

    Lcd_Write_String("Ready");
    __delay_ms(1000);

    Lcd_Clear();
}


void main(void)
{
    initmain();
    uint8_t temp;
    
    while (1)
    {
        if ( LC164_Read(0, &temp)){
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Acked and read: ");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_Integer(temp);
            __delay_ms(5000);
            Lcd_Clear();
        }
            
        else{
           Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Nacked");
         __delay_ms(5000);
         Lcd_Clear();
        }
         
        if ( LC164_Write(0, temp + 1)){
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Wrote");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_Integer(temp+1);
            __delay_ms(5000);
            Lcd_Clear();
        }
        else{
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Nack Write");
            __delay_ms(5000);
            Lcd_Clear();
        
        }
         
    }
}
/**
 End of File
*/



#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "DHT11.h"

static void initMain(void)
{
    internal_16();

    // I2C pins (RC4=SDA, RC5=SCL)
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x00;

    RC4PPSbits.RC4PPS = 0x0011;          // SDA out
    SSPDATPPSbits.SSPDATPPS = 0x0014;    // SDA in
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;    // SCL in
    RC5PPSbits.RC5PPS = 0x0010;          // SCL out

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x01;

    // DHT11 on RB3 -> make digital
    ANSELBbits.ANSB3 = 0;
}

void main(void)
{
    initMain();

    I2C_Init();
    __delay_ms(200);

    OLED_Init();
    OLED_Clear();

    OLED_Printf_Line(0, "DHT11 Ready");

    while (1)
    {
        uint8_t RH_Integral, RH_Decimal, T_Integral, T_Decimal;
        uint8_t Checksum;

        // Start + response
        DHT11_Init();
        DHT11_Check();

        // Read 40-bit payload
        RH_Integral = (uint8_t)DHT11_Read();
        RH_Decimal  = (uint8_t)DHT11_Read();
        T_Integral  = (uint8_t)DHT11_Read();
        T_Decimal   = (uint8_t)DHT11_Read();
        Checksum    = (uint8_t)DHT11_Read();

        // Verify checksum
        uint8_t sum = (uint8_t)(RH_Integral + RH_Decimal + T_Integral + T_Decimal);

        // Display
        OLED_Printf_Line(0, "Hum: %02u %%", RH_Integral);
        OLED_Printf_Line(1, "Temp:%02u C",  T_Integral);

        if (Checksum != sum)
            OLED_Printf_Line(2, "Checksum: ERR");
        else
            OLED_Printf_Line(2, "Checksum: OK ");

        __delay_ms(1500);
    }
}

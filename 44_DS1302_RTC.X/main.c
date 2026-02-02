#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "ds1302.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t sec, min, hr;
    uint8_t day, date, month, year;  // day=1..7, year=0..99
} rtc_time_t;

static void initMain(void)
{
    internal_16();

    // I2C pins (RC4=SDA, RC5=SCL)
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x00;
    RC4PPSbits.RC4PPS = 0x0011;
    SSPDATPPSbits.SSPDATPPS = 0x0014;
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;
    RC5PPSbits.RC5PPS = 0x0010;
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x01;

    // DS1302 pins (RB0/RB1/RB2)
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB2 = 0;

    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;

    CE = 0;
    SCLK = 0;
    IO = 0;
}

static void RTC_ReadBurst(rtc_time_t* t)
{
    // raw BCD reads
    uint8_t sec1, min1, hr1, date1, mn1, dy1, yr1;

    DS1302_Reset();
    DS1302_WriteByte(0xBF); // clock burst read

    sec1  = DS1302_ReadByte();
    min1  = DS1302_ReadByte();
    hr1   = DS1302_ReadByte();
    date1 = DS1302_ReadByte();
    mn1   = DS1302_ReadByte();
    dy1   = DS1302_ReadByte();
    yr1   = DS1302_ReadByte();

    DS1302_Reset();

    // BCD -> decimal
    t->sec   = get_dec(sec1);
    t->min   = get_dec(min1);
    t->hr    = get_dec(hr1);
    t->date  = get_dec(date1);
    t->month = get_dec(mn1);
    t->day   = get_dec(dy1);
    t->year  = get_dec(yr1);
}

static void UI_DrawTime(const rtc_time_t* t)
{
    OLED_Printf_Line(0, "Time: %02u:%02u:%02u", t->hr, t->min, t->sec);
}

static void UI_DrawDate(const rtc_time_t* t)
{
   OLED_Printf_Line(1, "Date: %02u/%02u/%02u", t->date, t->month, t->year);
}

void main(void)
{
    initMain();

    I2C_Init();
    __delay_ms(200);

    OLED_Init();
    OLED_Clear();

    // Only do this once to set the clock
    DS1302_Initialize(
        50,   // sec
        59,  // min
        23,  // hr
        2,   // day
        28,  // date
        12,   // month
        25   // year
    );

    rtc_time_t now;
    uint8_t last_sec = 255;
    uint8_t last_date = 0xFF;
    
    // draw once at boot
    RTC_ReadBurst(&now);
    UI_DrawTime(&now);
    UI_DrawDate(&now);
    last_sec = now.sec;
    last_date = now.date;

    while (1)
    {
        RTC_ReadBurst(&now);

        // Update UI only when second changes
        static uint8_t last_date = 0xFF;

        if (now.sec != last_sec)
        {
            last_sec = now.sec;
            UI_DrawTime(&now);

            if (now.date != last_date)
            {
                last_date = now.date;
                UI_DrawDate(&now);
            }
        }

        __delay_ms(50); // light polling; UI updates at 1Hz
    }
}

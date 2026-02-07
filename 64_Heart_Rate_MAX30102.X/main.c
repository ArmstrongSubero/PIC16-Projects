/*
 * File:    Main.c
 * Author:  Armstrong Subero
 * PIC:     16F1718 w/Int OSC @ 32MHz, 5v
 * Program: 64_Heart_Rate_MAX30102
 * Compiler: XC8
 * Program Version: 2.0
 *
 * Program Description:
 *     MAX30102 pulse oximeter on PIC16F1718. Ported from:
 *       - SparkFun MAX30105 Library (Peter Jansen / Nathan Seidle)
 *       - Maxim PBA (Peripheral Beat Amplitude) heart rate algorithm
 *       - Maxim MAXREFDES117 SpO2 algorithm
 *
 * Hardware Description:
 *     MAX30102 -> PIC16F1718:
 *         VDD   -> 3.3V
 *         GND   -> GND
 *         SDA   -> RC4 (4.7k pullup)
 *         SCL   -> RC5 (4.7k pullup)
 *         INT   -> NC  (polled mode)
 * 
 *         Additionally a CP2104 is connected to PIN RB2
 *
 * Created February 7th, 2026, 7:19 PM 
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "EUSART.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * MAX30102 Constants
 ******************************************************************************/
#define MAX30102_ADDR               0x57

/* Status Registers */
#define MAX30102_INTSTAT1           0x00
#define MAX30102_INTSTAT2           0x01
#define MAX30102_INTENABLE1         0x02
#define MAX30102_INTENABLE2         0x03

/* FIFO Registers */
#define MAX30102_FIFOWRITEPTR       0x04
#define MAX30102_FIFOOVERFLOW       0x05
#define MAX30102_FIFOREADPTR        0x06
#define MAX30102_FIFODATA           0x07

/* Configuration Registers */
#define MAX30102_FIFOCONFIG         0x08
#define MAX30102_MODECONFIG         0x09
#define MAX30102_SPO2CONFIG         0x0A
#define MAX30102_LED1_PULSEAMP      0x0C    /* Red */
#define MAX30102_LED2_PULSEAMP      0x0D    /* IR  */
#define MAX30102_MULTILEDCONFIG1    0x11
#define MAX30102_MULTILEDCONFIG2    0x12

/* Temperature */
#define MAX30102_DIETEMPINT         0x1F
#define MAX30102_DIETEMPFRAC        0x20
#define MAX30102_DIETEMPCONFIG      0x21

/* Part ID */
#define MAX30102_PARTID             0xFF
#define MAX30102_EXPECTED_PARTID    0x15

/* Mode masks and values (from SparkFun library) */
#define MAX30102_RESET_MASK         0xBF
#define MAX30102_RESET              0x40
#define MAX30102_SHUTDOWN_MASK      0x7F
#define MAX30102_SHUTDOWN           0x80
#define MAX30102_WAKEUP             0x00
#define MAX30102_MODE_MASK          0xF8
#define MAX30102_MODE_REDONLY       0x02
#define MAX30102_MODE_REDIRONLY     0x03

/* FIFO config masks */
#define MAX30102_SAMPLEAVG_MASK     ((uint8_t)~0xE0)
#define MAX30102_SAMPLEAVG_4        0x40
#define MAX30102_ROLLOVER_MASK      0xEF
#define MAX30102_ROLLOVER_ENABLE    0x10
#define MAX30102_A_FULL_MASK        0xF0

/* SpO2 config masks */
#define MAX30102_ADCRANGE_MASK      0x9F
#define MAX30102_ADCRANGE_4096      0x20
#define MAX30102_SAMPLERATE_MASK    0xE3
#define MAX30102_SAMPLERATE_100     0x04
#define MAX30102_PULSEWIDTH_MASK    0xFC
#define MAX30102_PULSEWIDTH_411     0x03

/* Multi-LED slot values */
#define MAX30102_SLOT1_MASK         0xF8
#define MAX30102_SLOT2_MASK         0x8F
#define SLOT_RED_LED                0x01
#define SLOT_IR_LED                 0x02

/*******************************************************************************
 * Millisecond Tick (TMR0)
 ******************************************************************************/
static volatile uint32_t millis_counter = 0;

static void TMR0_Init(void)
{
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.PSA    = 0;
    OPTION_REGbits.PS     = 0b100;  /* 1:32 */
    TMR0 = 6;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE    = 1;
    INTCONbits.PEIE   = 1;
}

void __interrupt() ISR(void)
{
    if (INTCONbits.TMR0IF)
    {
        TMR0 = 6;
        INTCONbits.TMR0IF = 0;
        millis_counter++;
    }
}

static uint32_t millis(void)
{
    uint32_t val;
    INTCONbits.GIE = 0;
    val = millis_counter;
    INTCONbits.GIE = 1;
    return val;
}

/*******************************************************************************
 * I2C Transport (using existing MSSP primitives)
 ******************************************************************************/

static uint8_t i2c_write_bytes(uint8_t addr7, uint8_t reg,
                                uint8_t *src, uint8_t len)
{
    if (I2C_Start() != I2C_OK) return 1;
    if (I2C_WriteByte(addr7 << 1) != I2C_OK)       { I2C_Stop(); return 2; }
    if (I2C_WriteByte(reg) != I2C_OK)               { I2C_Stop(); return 3; }
    for (uint8_t i = 0; i < len; i++)
    {
        if (I2C_WriteByte(src[i]) != I2C_OK)        { I2C_Stop(); return 4; }
    }
    I2C_Stop();
    return 0;
}

static uint8_t i2c_read_bytes(uint8_t addr7, uint8_t reg,
                               uint8_t *dst, uint8_t len)
{
    if (I2C_Start() != I2C_OK) return 1;
    if (I2C_WriteByte(addr7 << 1) != I2C_OK)       { I2C_Stop(); return 2; }
    if (I2C_WriteByte(reg) != I2C_OK)               { I2C_Stop(); return 3; }
    if (I2C_RepeatedStart() != I2C_OK)              { I2C_Stop(); return 4; }
    if (I2C_WriteByte((addr7 << 1) | 1) != I2C_OK) { I2C_Stop(); return 5; }
    for (uint8_t i = 0; i < len; i++)
    {
        bool ack = (i < (len - 1));
        if (I2C_ReadByte(&dst[i], ack) != I2C_OK)  { I2C_Stop(); return 6; }
    }
    I2C_Stop();
    return 0;
}

/*******************************************************************************
 * MAX30102 Register Helpers (mirrors SparkFun's readRegister8/writeRegister8)
 ******************************************************************************/

static uint8_t readRegister8(uint8_t reg)
{
    uint8_t val = 0;
    i2c_read_bytes(MAX30102_ADDR, reg, &val, 1);
    return val;
}

static void writeRegister8(uint8_t reg, uint8_t value)
{
    i2c_write_bytes(MAX30102_ADDR, reg, &value, 1);
}

/* SparkFun's bitMask: read-modify-write */
static void bitMask(uint8_t reg, uint8_t mask, uint8_t thing)
{
    uint8_t original = readRegister8(reg);
    original = original & mask;
    writeRegister8(reg, original | thing);
}

/*******************************************************************************
 * MAX30102 Driver (ported from SparkFun MAX30105 setup() flow)
 ******************************************************************************/

static void MAX30102_softReset(void)
{
    bitMask(MAX30102_MODECONFIG, MAX30102_RESET_MASK, MAX30102_RESET);

    /* Poll for reset bit to clear (max ~100ms) */
    uint32_t start = millis();
    while ((millis() - start) < 100)
    {
        uint8_t resp = readRegister8(MAX30102_MODECONFIG);
        if ((resp & MAX30102_RESET) == 0) break;
        __delay_ms(1);
    }
}

static void MAX30102_clearFIFO(void)
{
    writeRegister8(MAX30102_FIFOWRITEPTR, 0);
    writeRegister8(MAX30102_FIFOOVERFLOW, 0);
    writeRegister8(MAX30102_FIFOREADPTR, 0);
}

static bool MAX30102_Init(void)
{
    /* Verify part ID */
    if (readRegister8(MAX30102_PARTID) != MAX30102_EXPECTED_PARTID)
        return false;

    /* ---- SparkFun setup() flow ---- */

    /* Soft reset all registers to POR values */
    MAX30102_softReset();

    /*
     * FIFO Configuration
     * Sample average = 4, enable rollover
     */
    bitMask(MAX30102_FIFOCONFIG, MAX30102_SAMPLEAVG_MASK, MAX30102_SAMPLEAVG_4);
    bitMask(MAX30102_FIFOCONFIG, MAX30102_ROLLOVER_MASK, MAX30102_ROLLOVER_ENABLE);

    /*
     * Mode: Red + IR (SpO2 mode = 0x03)
     */
    bitMask(MAX30102_MODECONFIG, MAX30102_MODE_MASK, MAX30102_MODE_REDIRONLY);

    /*
     * SpO2 / Particle Sensing Config
     * ADC range   = 4096 nA
     * Sample rate = 100 Hz
     * Pulse width = 411 us (18-bit resolution)
     */
    bitMask(MAX30102_SPO2CONFIG, MAX30102_ADCRANGE_MASK, MAX30102_ADCRANGE_4096);
    bitMask(MAX30102_SPO2CONFIG, MAX30102_SAMPLERATE_MASK, MAX30102_SAMPLERATE_100);
    bitMask(MAX30102_SPO2CONFIG, MAX30102_PULSEWIDTH_MASK, MAX30102_PULSEWIDTH_411);

    /*
     * LED Pulse Amplitude
     * 0x1F = 6.4 mA, 0x47 = ~14 mA, 0x7F = 25.4 mA
     */
    writeRegister8(MAX30102_LED1_PULSEAMP, 0x24);  /* Red */
    writeRegister8(MAX30102_LED2_PULSEAMP, 0x24);  /* IR  */

    /*
     * Multi-LED Mode slot config
     * Slot 1 = Red, Slot 2 = IR
     */
    bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT1_MASK, SLOT_RED_LED);
    bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT2_MASK, (uint8_t)(SLOT_IR_LED << 4));

    /* Clear FIFO before starting */
    MAX30102_clearFIFO();

    return true;
}

/*
 * Read all available FIFO samples into caller's buffers.
 * Returns number of samples read (each sample = one Red + one IR value).
 * Mirrors SparkFun's check() function.
 */
static uint8_t MAX30102_check(uint32_t *red_buf, uint32_t *ir_buf,
                               uint8_t max_samples)
{
    /* Must read interrupt status to clear flags and allow FIFO updates */
    readRegister8(MAX30102_INTSTAT1);
    readRegister8(MAX30102_INTSTAT2);

    uint8_t rd_ptr = readRegister8(MAX30102_FIFOREADPTR);
    uint8_t wr_ptr = readRegister8(MAX30102_FIFOWRITEPTR);

    int8_t num_available = (int8_t)(wr_ptr - rd_ptr);
    if (num_available < 0) num_available += 32;
    if (num_available == 0) return 0;

    uint8_t to_read = (uint8_t)num_available;
    if (to_read > max_samples) to_read = max_samples;

    uint8_t count = 0;
    for (uint8_t s = 0; s < to_read; s++)
    {
        uint8_t buf[6];
        if (i2c_read_bytes(MAX30102_ADDR, MAX30102_FIFODATA, buf, 6) != 0)
            break;

        /* Red (LED1) = bytes 0-2, IR (LED2) = bytes 3-5, 18-bit */
        red_buf[count] = ((uint32_t)(buf[0] & 0x03) << 16) |
                         ((uint32_t)buf[1] << 8) |
                          (uint32_t)buf[2];

        ir_buf[count]  = ((uint32_t)(buf[3] & 0x03) << 16) |
                         ((uint32_t)buf[4] << 8) |
                          (uint32_t)buf[5];
        count++;
    }
    return count;
}

/*******************************************************************************
 * PBA Heart Rate Algorithm
 * (Ported from SparkFun heartRate.cpp / Maxim PBA)
 *
 * DC estimator + 23-tap symmetric FIR low-pass + zero-crossing detection
 ******************************************************************************/

/* FIR filter coefficients (symmetric 23-tap, from Maxim) */
static const uint16_t FIRCoeffs[12] = {
    172, 321, 579, 927, 1360, 1858, 2390, 2916, 3391, 3768, 4012, 4096
};

/* PBA state */
static int16_t  pba_IR_AC_Max = 20;
static int16_t  pba_IR_AC_Min = -20;
static int16_t  pba_IR_AC_Signal_Current = 0;
static int16_t  pba_IR_AC_Signal_Previous = 0;
static int16_t  pba_IR_AC_Signal_min = 0;
static int16_t  pba_IR_AC_Signal_max = 0;
static int16_t  pba_positiveEdge = 0;
static int16_t  pba_negativeEdge = 0;
static int32_t  pba_ir_avg_reg = 0;
static int16_t  pba_cbuf[32];
static uint8_t  pba_offset = 0;

static void pba_init(void)
{
    pba_IR_AC_Max = 20;
    pba_IR_AC_Min = -20;
    pba_IR_AC_Signal_Current = 0;
    pba_IR_AC_Signal_Previous = 0;
    pba_IR_AC_Signal_min = 0;
    pba_IR_AC_Signal_max = 0;
    pba_positiveEdge = 0;
    pba_negativeEdge = 0;
    pba_ir_avg_reg = 0;
    pba_offset = 0;
    for (uint8_t i = 0; i < 32; i++) pba_cbuf[i] = 0;
}

/* Average DC Estimator - removes DC with slow-tracking IIR */
static int16_t averageDCEstimator(int32_t *p, uint16_t x)
{
    *p += ((((int32_t)x << 15) - *p) >> 4);
    return (int16_t)(*p >> 15);
}

static int32_t mul16(int16_t x, int16_t y)
{
    return (int32_t)x * (int32_t)y;
}

/* Low-pass FIR filter (23-tap symmetric) */
static int16_t lowPassFIRFilter(int16_t din)
{
    pba_cbuf[pba_offset] = din;

    int32_t z = mul16(FIRCoeffs[11],
                      pba_cbuf[(pba_offset - 11) & 0x1F]);

    for (uint8_t i = 0; i < 11; i++)
    {
        z += mul16(FIRCoeffs[i],
                   pba_cbuf[(pba_offset - i) & 0x1F] +
                   pba_cbuf[(pba_offset - 22 + i) & 0x1F]);
    }

    pba_offset++;
    pba_offset %= 32;

    return (int16_t)(z >> 15);
}

/*
 * checkForBeat - exact port of SparkFun's PBA algorithm.
 * Takes raw IR sample, returns true if heartbeat detected.
 */
static bool checkForBeat(int32_t sample)
{
    bool beatDetected = false;

    pba_IR_AC_Signal_Previous = pba_IR_AC_Signal_Current;

    int16_t dc_est = averageDCEstimator(&pba_ir_avg_reg, (uint16_t)sample);
    pba_IR_AC_Signal_Current = lowPassFIRFilter((int16_t)(sample - dc_est));

    /* Positive zero crossing (rising edge) */
    if ((pba_IR_AC_Signal_Previous < 0) && (pba_IR_AC_Signal_Current >= 0))
    {
        pba_IR_AC_Max = pba_IR_AC_Signal_max;
        pba_IR_AC_Min = pba_IR_AC_Signal_min;

        pba_positiveEdge = 1;
        pba_negativeEdge = 0;
        pba_IR_AC_Signal_max = 0;

        if ((pba_IR_AC_Max - pba_IR_AC_Min) > 20 &&
            (pba_IR_AC_Max - pba_IR_AC_Min) < 1000)
        {
            beatDetected = true;
        }
    }

    /* Negative zero crossing (falling edge) */
    if ((pba_IR_AC_Signal_Previous > 0) && (pba_IR_AC_Signal_Current <= 0))
    {
        pba_positiveEdge = 0;
        pba_negativeEdge = 1;
        pba_IR_AC_Signal_min = 0;
    }

    /* Track max in positive half-cycle */
    if (pba_positiveEdge && (pba_IR_AC_Signal_Current > pba_IR_AC_Signal_Previous))
    {
        pba_IR_AC_Signal_max = pba_IR_AC_Signal_Current;
    }

    /* Track min in negative half-cycle */
    if (pba_negativeEdge && (pba_IR_AC_Signal_Current < pba_IR_AC_Signal_Previous))
    {
        pba_IR_AC_Signal_min = pba_IR_AC_Signal_Current;
    }

    return beatDetected;
}

/*******************************************************************************
 * SpO2 - Ratio of Ratios with Maxim Lookup Table
 *
 * Table: -45.060*R^2 + 30.354*R + 94.845
 ******************************************************************************/

static const uint8_t uch_spo2_table[184] = {
    95, 95, 95, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98,
    99, 99, 99, 99, 99, 99, 99, 99,100,100,100,100,100,100,100,100,
   100,100,100,100,100,100,100,100,100,100,100,100, 99, 99, 99, 99,
    99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 97, 97, 97, 97, 96, 96,
    96, 96, 95, 95, 95, 94, 94, 94, 93, 93, 93, 92, 92, 92, 91, 91,
    90, 90, 89, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 84, 84, 83,
    82, 82, 81, 81, 80, 80, 79, 78, 78, 77, 76, 76, 75, 74, 74, 73,
    72, 72, 71, 70, 69, 69, 68, 67, 66, 66, 65, 64, 63, 62, 62, 61,
    60, 59, 58, 57, 56, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,
    45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 31, 30, 29,
    28, 27, 26, 25, 23, 22, 21, 20, 19, 17, 16, 15, 14, 12, 11, 10,
     9,  7,  6,  5,  3,  2,  1
};

typedef struct {
    uint32_t ir_sum;
    uint32_t red_sum;
    uint32_t ir_max;
    uint32_t ir_min;
    uint32_t red_max;
    uint32_t red_min;
    uint16_t count;
} SpO2_Accum_t;

static SpO2_Accum_t spo2_acc;

static void spo2_reset(void)
{
    spo2_acc.ir_sum  = 0;
    spo2_acc.red_sum = 0;
    spo2_acc.ir_max  = 0;
    spo2_acc.ir_min  = 0x3FFFF;
    spo2_acc.red_max = 0;
    spo2_acc.red_min = 0x3FFFF;
    spo2_acc.count   = 0;
}

static void spo2_accumulate(uint32_t ir, uint32_t red)
{
    spo2_acc.ir_sum  += (ir >> 4);   /* Scale down to prevent overflow */
    spo2_acc.red_sum += (red >> 4);
    spo2_acc.count++;
    if (ir > spo2_acc.ir_max)   spo2_acc.ir_max = ir;
    if (ir < spo2_acc.ir_min)   spo2_acc.ir_min = ir;
    if (red > spo2_acc.red_max) spo2_acc.red_max = red;
    if (red < spo2_acc.red_min) spo2_acc.red_min = red;
}

static uint8_t spo2_compute(void)
{
    if (spo2_acc.count == 0) return 0;

    uint32_t ac_ir  = spo2_acc.ir_max  - spo2_acc.ir_min;
    uint32_t ac_red = spo2_acc.red_max - spo2_acc.red_min;
    uint32_t dc_ir  = spo2_acc.ir_sum  / spo2_acc.count;
    uint32_t dc_red = spo2_acc.red_sum / spo2_acc.count;

    if (ac_ir == 0 || dc_ir == 0 || dc_red == 0) return 0;

    /* R*100 = (ac_red * dc_ir * 100) / (ac_ir * dc_red) */
    uint32_t num = (ac_red >> 4) * dc_ir;
    uint32_t den = (ac_ir >> 4)  * dc_red;

    if (den == 0) return 0;

    uint32_t ratio_x100 = (num * 100UL) / den;

    if (ratio_x100 > 2 && ratio_x100 < 184)
        return uch_spo2_table[ratio_x100];

    return 0;
}

/*******************************************************************************
 * BPM - Running average of inter-beat intervals
 ******************************************************************************/

#define BPM_HISTORY     8

static uint32_t beat_times[BPM_HISTORY];
static uint16_t beat_intervals[BPM_HISTORY];
static uint8_t  beat_idx = 0;
static uint8_t  beat_count = 0;
static uint16_t beat_avg_interval = 0;

static void bpm_init(void)
{
    beat_idx = 0;
    beat_count = 0;
    beat_avg_interval = 0;
    for (uint8_t i = 0; i < BPM_HISTORY; i++)
    {
        beat_times[i] = 0;
        beat_intervals[i] = 0;
    }
}

/*
 * Record a beat. Returns true if the beat was accepted (not an outlier).
 * Outlier rejection: if we have a running average, reject intervals
 * that deviate more than 40% from the average.
 */
static bool bpm_record_beat(uint32_t now_ms)
{
    if (beat_count > 0)
    {
        uint8_t prev = (beat_idx - 1) % BPM_HISTORY;
        uint32_t interval = now_ms - beat_times[prev];

        /* Basic range: 273ms (220bpm) to 2000ms (30bpm) */
        if (interval < 273 || interval > 2000)
            return false;

        /* Outlier rejection once we have enough history */
        if (beat_count >= 3 && beat_avg_interval > 0)
        {
            uint32_t lo = (uint32_t)beat_avg_interval * 60 / 100;  /* -40% */
            uint32_t hi = (uint32_t)beat_avg_interval * 140 / 100; /* +40% */
            if (interval < lo || interval > hi)
                return false;  /* Too far from average, skip it */
        }

        /* Store interval */
        beat_intervals[beat_idx % BPM_HISTORY] = (uint16_t)interval;
    }

    beat_times[beat_idx % BPM_HISTORY] = now_ms;
    beat_idx++;
    if (beat_count < BPM_HISTORY) beat_count++;

    /* Update running average interval */
    if (beat_count >= 2)
    {
        uint32_t sum = 0;
        uint8_t valid = (beat_count < BPM_HISTORY) ? beat_count - 1 : BPM_HISTORY - 1;
        for (uint8_t i = 0; i < valid; i++)
        {
            uint8_t idx = (beat_idx - 1 - i) % BPM_HISTORY;
            sum += beat_intervals[idx];
        }
        if (valid > 0) beat_avg_interval = (uint16_t)(sum / valid);
    }

    return true;
}

static uint16_t bpm_calculate(void)
{
    if (beat_avg_interval == 0 || beat_count < 3) return 0;

    uint32_t bpm = 60000UL / (uint32_t)beat_avg_interval;
    if (bpm < 30 || bpm > 220) return 0;

    return (uint16_t)bpm;
}

/*******************************************************************************
 * UART Helpers (no printf)
 ******************************************************************************/

static void UART_PrintUint32(uint32_t val)
{
    char buf[11];
    int8_t i = 0;

    if (val == 0) { EUSART_Write_Text("0"); return; }
    while (val > 0) { buf[i++] = '0' + (val % 10); val /= 10; }
    for (i--; i >= 0; i--)
    {
        char c[2] = { buf[i], '\0' };
        EUSART_Write_Text(c);
    }
}

static void UART_PrintUint16(uint16_t val)
{
    UART_PrintUint32((uint32_t)val);
}

/*******************************************************************************
 * initMain
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);

    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;

    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;

    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS = 0x0B;
    RC4PPSbits.RC4PPS = 0x0011;
    SSPDATPPSbits.SSPDATPPS = 0x0014;
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;
    RC5PPSbits.RC5PPS = 0x0010;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;
}

/*******************************************************************************
 * Main
 ******************************************************************************/

#define FINGER_THRESHOLD    5000

void main(void)
{
    initMain();
    TMR0_Init();
    EUSART_Initialize(19200);
    I2C_Init();

    EUSART_Write_Text("\r\nMAX30102 Pulse Oximeter v2\r\n");
    EUSART_Write_Text("(SparkFun PBA Algorithm Port)\r\n");
    EUSART_Write_Text("----------------------------\r\n");

    if (MAX30102_Init())
    {
        EUSART_Write_Text("Init OK\r\n");
    }
    else
    {
        EUSART_Write_Text("Init FAILED! Check wiring.\r\n");
        while (1);
    }

    pba_init();
    spo2_reset();
    bpm_init();

    #define READ_BUF_SIZE   8
    uint32_t red_buf[READ_BUF_SIZE];
    uint32_t ir_buf[READ_BUF_SIZE];

    uint32_t last_print_ms  = 0;
    uint32_t last_beat_ms   = 0;
    uint16_t current_bpm    = 0;
    uint8_t  current_spo2   = 0;
    bool     finger_present = false;
    uint16_t no_finger_cnt  = 0;

    EUSART_Write_Text("Place finger on sensor...\r\n\r\n");

    while (1)
    {
        uint8_t n = MAX30102_check(red_buf, ir_buf, READ_BUF_SIZE);
        if (n == 0)
        {
            __delay_ms(1);
            continue;
        }

        uint32_t now = millis();

        for (uint8_t i = 0; i < n; i++)
        {
            uint32_t ir  = ir_buf[i];
            uint32_t red = red_buf[i];

            /* ---- Finger detection ---- */
            if (ir < FINGER_THRESHOLD)
            {
                no_finger_cnt++;
                if (no_finger_cnt > 50 && finger_present)
                {
                    finger_present = false;
                    current_bpm = 0;
                    current_spo2 = 0;
                    EUSART_Write_Text("-- Finger removed --\r\n");
                    pba_init();
                    spo2_reset();
                    bpm_init();
                }
                continue;
            }

            no_finger_cnt = 0;
            if (!finger_present)
            {
                finger_present = true;
                EUSART_Write_Text("-- Finger detected --\r\n");
                pba_init();
                spo2_reset();
                bpm_init();
                last_beat_ms = 0;
            }

            /* ---- Accumulate for SpO2 ---- */
            spo2_accumulate(ir, red);

            /* ---- PBA beat detection on IR ---- */
            if (checkForBeat((int32_t)ir))
            {
                uint32_t beat_now = millis();
                bool accepted;

                if (last_beat_ms > 0)
                {
                    accepted = bpm_record_beat(beat_now);
                    if (accepted)
                    {
                        current_bpm = bpm_calculate();

                        /* Only update SpO2 on accepted beats */
                        uint8_t s = spo2_compute();
                        if (s > 0) current_spo2 = s;
                    }
                }
                else
                {
                    /* First beat ? just record timestamp */
                    accepted = bpm_record_beat(beat_now);
                }
                last_beat_ms = beat_now;

                /* Reset accumulator for next beat cycle */
                spo2_reset();
            }
        }

        /* ---- Print once per second ---- */
        if (finger_present && (now - last_print_ms) >= 1000)
        {
            last_print_ms = now;

            EUSART_Write_Text("IR=");
            UART_PrintUint32(ir_buf[n - 1]);
            EUSART_Write_Text("  Red=");
            UART_PrintUint32(red_buf[n - 1]);

            if (current_bpm > 0)
            {
                EUSART_Write_Text("  BPM=");
                UART_PrintUint16(current_bpm);
            }
            else
            {
                EUSART_Write_Text("  BPM=---");
            }

            if (current_spo2 > 0)
            {
                EUSART_Write_Text("  SpO2=");
                UART_PrintUint16((uint16_t)current_spo2);
                EUSART_Write_Text("%");
            }
            else
            {
                EUSART_Write_Text("  SpO2=---%");
            }

            EUSART_Write_Text("\r\n");
        }
    }
}
/*
 * File:    Main.c
 * Author:  Armstrong Subero
 * PIC:     16F1718 w/Int OSC @ 32MHz, 5v
 * Program: 61_TOF_VL53L0XV2
 * Compiler: XC8
 * Program Version: 1.0
 *
 * Program Description:
 *     VL53L0X ToF ranging on PIC16F1718 using hardware I2C (MSSP)
 *     and EUSART for serial output. Single-file, no floats.
 *
 * Hardware Description:
 *     VL53L0X connected to PIC16F1718:
 *         VDD   -> 3.3V (or 5V with io_2v8 = true)
 *         GND   -> GND
 *         SDA   -> RC4 (4.7k pullup)
 *         SCL   -> RC5 (4.7k pullup)
 *         XSHUT -> RB5 (optional, for reset control)
 *         GPIO1 -> NC
 *
 * Created February 6th, 2026, 8:30 PM
 */

/*******************************************************************************
 * Includes and Defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "EUSART.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ---- User Configuration ---- */
// Uncomment to enable long range mode
//#define LONG_RANGE

// Uncomment ONE for speed vs accuracy tradeoff
#define HIGH_SPEED
//#define HIGH_ACCURACY

/* ---- VL53L0X Default I2C Address (7-bit) ---- */
#define VL53L0X_ADDRESS  0x29

/*******************************************************************************
 * Millisecond Tick (TMR0-based)
 *
 * TMR0 configured for ~1ms overflow at 32 MHz (Fosc/4 = 8 MHz)
 * Prescaler 1:32 -> TMR0 clk = 250 kHz -> 250 ticks = 1 ms
 * Preload TMR0 = 256 - 250 = 6
 ******************************************************************************/
static volatile uint32_t millis_counter = 0;

static void TMR0_Init(void)
{
    OPTION_REGbits.TMR0CS = 0;  /* Internal clock (Fosc/4) */
    OPTION_REGbits.PSA    = 0;  /* Prescaler assigned to TMR0 */
    OPTION_REGbits.PS     = 0b100; /* 1:32 prescaler */
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
 * VL53L0X Register Addresses
 ******************************************************************************/
#define SYSRANGE_START                          0x00
#define SYSTEM_SEQUENCE_CONFIG                  0x01
#define SYSTEM_INTERMEASUREMENT_PERIOD          0x04
#define SYSTEM_INTERRUPT_CONFIG_GPIO            0x0A
#define SYSTEM_INTERRUPT_CLEAR                  0x0B
#define RESULT_INTERRUPT_STATUS                 0x13
#define RESULT_RANGE_STATUS                     0x14
#define I2C_SLAVE_DEVICE_ADDRESS_REG            0x8A
#define MSRC_CONFIG_CONTROL                     0x60
#define FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT 0x44
#define FINAL_RANGE_CONFIG_VALID_PHASE_HIGH     0x48
#define FINAL_RANGE_CONFIG_VALID_PHASE_LOW      0x47
#define PRE_RANGE_CONFIG_VALID_PHASE_HIGH       0x57
#define PRE_RANGE_CONFIG_VALID_PHASE_LOW        0x56
#define PRE_RANGE_CONFIG_VCSEL_PERIOD           0x50
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI      0x51
#define FINAL_RANGE_CONFIG_VCSEL_PERIOD         0x70
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI    0x71
#define MSRC_CONFIG_TIMEOUT_MACROP              0x46
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_0        0xB0
#define GLOBAL_CONFIG_REF_EN_START_SELECT       0xB6
#define GLOBAL_CONFIG_VCSEL_WIDTH               0x32
#define DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD     0x4E
#define DYNAMIC_SPAD_REF_EN_START_OFFSET        0x4F
#define POWER_MANAGEMENT_GO1_POWER_FORCE        0x80
#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV       0x89
#define GPIO_HV_MUX_ACTIVE_HIGH                 0x84
#define OSC_CALIBRATE_VAL                       0xF8
#define ALGO_PHASECAL_LIM                       0x30
#define ALGO_PHASECAL_CONFIG_TIMEOUT            0x30

/*******************************************************************************
 * VL53L0X Macros
 ******************************************************************************/
#define decodeVcselPeriod(reg_val)      (((reg_val) + 1) << 1)
#define encodeVcselPeriod(period_pclks) (((period_pclks) >> 1) - 1)
#define calcMacroPeriod(vcsel_period_pclks) \
    ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)

/*******************************************************************************
 * VL53L0X Data Types
 ******************************************************************************/
typedef struct {
    uint8_t  address;
    uint8_t  stop_variable;
    uint8_t  last_status;
    bool     did_timeout;
    uint32_t io_timeout;
    uint32_t timeout_start_ms;
    uint32_t measurement_timing_budget_us;
} VL53L0X_Dev_t;

typedef struct {
    bool tcc, msrc, dss, pre_range, final_range;
} SeqEnables_t;

typedef struct {
    uint16_t pre_range_vcsel_period_pclks, final_range_vcsel_period_pclks;
    uint16_t msrc_dss_tcc_mclks, pre_range_mclks, final_range_mclks;
    uint32_t msrc_dss_tcc_us,    pre_range_us,    final_range_us;
} SeqTimeouts_t;

/*******************************************************************************
 * I2C Transport Layer for PIC16F1718
 *
 * Uses Armstrong's MSSP I2C driver primitives:
 *   I2C_Start, I2C_RepeatedStart, I2C_Stop, I2C_WriteByte, I2C_ReadByte
 ******************************************************************************/

/*
 * Write `len` bytes to register `reg` on 7-bit address `addr`.
 * START -> addr+W -> reg -> data[0..len-1] -> STOP
 */
static uint8_t tof_i2c_write(uint8_t addr, uint8_t reg, uint8_t *src, uint8_t len)
{
    if (I2C_Start() != I2C_OK) return 1;

    if (I2C_WriteByte(addr << 1) != I2C_OK)
    {
        I2C_Stop();
        return 2;
    }

    if (I2C_WriteByte(reg) != I2C_OK)
    {
        I2C_Stop();
        return 3;
    }

    for (uint8_t i = 0; i < len; i++)
    {
        if (I2C_WriteByte(src[i]) != I2C_OK)
        {
            I2C_Stop();
            return 4;
        }
    }

    I2C_Stop();
    return 0;
}

/*
 * Read `len` bytes starting at register `reg` from 7-bit address `addr`.
 * START -> addr+W -> reg -> RESTART -> addr+R -> data[0..len-1] -> STOP
 */
static uint8_t tof_i2c_read(uint8_t addr, uint8_t reg, uint8_t *dst, uint8_t len)
{
    /* Write phase: send register address */
    if (I2C_Start() != I2C_OK) return 1;

    if (I2C_WriteByte(addr << 1) != I2C_OK)
    {
        I2C_Stop();
        return 2;
    }

    if (I2C_WriteByte(reg) != I2C_OK)
    {
        I2C_Stop();
        return 3;
    }

    /* Repeated start for read phase */
    if (I2C_RepeatedStart() != I2C_OK)
    {
        I2C_Stop();
        return 4;
    }

    if (I2C_WriteByte((addr << 1) | 0x01) != I2C_OK)
    {
        I2C_Stop();
        return 5;
    }

    /* Read data bytes: ACK all except last (NAK) */
    for (uint8_t i = 0; i < len; i++)
    {
        bool ack = (i < (len - 1));
        if (I2C_ReadByte(&dst[i], ack) != I2C_OK)
        {
            I2C_Stop();
            return 6;
        }
    }

    I2C_Stop();
    return 0;
}

/*******************************************************************************
 * VL53L0X Register Access
 ******************************************************************************/

static void writeReg(VL53L0X_Dev_t *dev, uint8_t reg, uint8_t value)
{
    dev->last_status = tof_i2c_write(dev->address, reg, &value, 1);
}

static void writeReg16(VL53L0X_Dev_t *dev, uint8_t reg, uint16_t value)
{
    uint8_t buf[2];
    buf[0] = (uint8_t)(value >> 8);
    buf[1] = (uint8_t)(value & 0xFF);
    dev->last_status = tof_i2c_write(dev->address, reg, buf, 2);
}

static void writeReg32(VL53L0X_Dev_t *dev, uint8_t reg, uint32_t value)
{
    uint8_t buf[4];
    buf[0] = (uint8_t)(value >> 24);
    buf[1] = (uint8_t)(value >> 16);
    buf[2] = (uint8_t)(value >> 8);
    buf[3] = (uint8_t)(value & 0xFF);
    dev->last_status = tof_i2c_write(dev->address, reg, buf, 4);
}

static uint8_t readReg(VL53L0X_Dev_t *dev, uint8_t reg)
{
    uint8_t val = 0;
    dev->last_status = tof_i2c_read(dev->address, reg, &val, 1);
    return val;
}

static uint16_t readReg16(VL53L0X_Dev_t *dev, uint8_t reg)
{
    uint8_t buf[2] = {0};
    dev->last_status = tof_i2c_read(dev->address, reg, buf, 2);
    return ((uint16_t)buf[0] << 8) | (uint16_t)buf[1];
}

static uint32_t readReg32(VL53L0X_Dev_t *dev, uint8_t reg)
{
    uint8_t buf[4] = {0};
    dev->last_status = tof_i2c_read(dev->address, reg, buf, 4);
    return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) |
           ((uint32_t)buf[2] << 8)  | (uint32_t)buf[3];
}

static void writeMulti(VL53L0X_Dev_t *dev, uint8_t reg, uint8_t *src, uint8_t count)
{
    dev->last_status = tof_i2c_write(dev->address, reg, src, count);
}

static void readMulti(VL53L0X_Dev_t *dev, uint8_t reg, uint8_t *dst, uint8_t count)
{
    dev->last_status = tof_i2c_read(dev->address, reg, dst, count);
}

/*******************************************************************************
 * Timeout Helpers
 ******************************************************************************/

static void startTimeout(VL53L0X_Dev_t *dev)
{
    dev->timeout_start_ms = millis();
}

static bool checkTimeoutExpired(VL53L0X_Dev_t *dev)
{
    return (dev->io_timeout > 0 &&
            (millis() - dev->timeout_start_ms) > dev->io_timeout);
}

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
static bool     getSpadInfo(VL53L0X_Dev_t *dev, uint8_t *count, bool *type_is_aperture);
static void     getSequenceStepEnables(VL53L0X_Dev_t *dev, SeqEnables_t *en);
static void     getSequenceStepTimeouts(VL53L0X_Dev_t *dev, SeqEnables_t *en, SeqTimeouts_t *to);
static uint16_t decodeTimeout(uint16_t reg_val);
static uint16_t encodeTimeout(uint16_t timeout_mclks);
static uint32_t timeoutMclksToUs(uint16_t mclks, uint8_t vcsel_pclks);
static uint32_t timeoutUsToMclks(uint32_t us, uint8_t vcsel_pclks);
static bool     performSingleRefCal(VL53L0X_Dev_t *dev, uint8_t vhv_init_byte);
static uint8_t  getVcselPulsePeriod(VL53L0X_Dev_t *dev, uint8_t type);
static uint32_t getMeasurementTimingBudget(VL53L0X_Dev_t *dev);
static bool     setMeasurementTimingBudget(VL53L0X_Dev_t *dev, uint32_t budget_us);

/*******************************************************************************
 * VL53L0X_Init
 ******************************************************************************/
static bool VL53L0X_Init(VL53L0X_Dev_t *dev)
{
    /* VL53L0X_DataInit() */
    writeReg(dev, VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV,
             readReg(dev, VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV) | 0x01);

    writeReg(dev, 0x88, 0x00);

    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    dev->stop_variable = readReg(dev, 0x91);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x00);

    writeReg(dev, MSRC_CONFIG_CONTROL,
             readReg(dev, MSRC_CONFIG_CONTROL) | 0x12);

    /* 0.25 MCPS in Q9.7 = 32 */
    writeReg16(dev, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 32);

    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0xFF);

    /* VL53L0X_StaticInit() */
    uint8_t spad_count;
    bool spad_type_is_aperture;
    if (!getSpadInfo(dev, &spad_count, &spad_type_is_aperture))
        return false;

    uint8_t ref_spad_map[6];
    readMulti(dev, GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
    writeReg(dev, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);

    uint8_t first_spad = spad_type_is_aperture ? 12 : 0;
    uint8_t spads_en = 0;

    for (uint8_t i = 0; i < 48; i++)
    {
        if (i < first_spad || spads_en == spad_count)
            ref_spad_map[i / 8] &= ~(1 << (i % 8));
        else if ((ref_spad_map[i / 8] >> (i % 8)) & 0x1)
            spads_en++;
    }

    writeMulti(dev, GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

    /* Tuning settings */
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x09, 0x00);
    writeReg(dev, 0x10, 0x00);
    writeReg(dev, 0x11, 0x00);
    writeReg(dev, 0x24, 0x01);
    writeReg(dev, 0x25, 0xFF);
    writeReg(dev, 0x75, 0x00);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x4E, 0x2C);
    writeReg(dev, 0x48, 0x00);
    writeReg(dev, 0x30, 0x20);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x30, 0x09);
    writeReg(dev, 0x54, 0x00);
    writeReg(dev, 0x31, 0x04);
    writeReg(dev, 0x32, 0x03);
    writeReg(dev, 0x40, 0x83);
    writeReg(dev, 0x46, 0x25);
    writeReg(dev, 0x60, 0x00);
    writeReg(dev, 0x27, 0x00);
    writeReg(dev, 0x50, 0x06);
    writeReg(dev, 0x51, 0x00);
    writeReg(dev, 0x52, 0x96);
    writeReg(dev, 0x56, 0x08);
    writeReg(dev, 0x57, 0x30);
    writeReg(dev, 0x61, 0x00);
    writeReg(dev, 0x62, 0x00);
    writeReg(dev, 0x64, 0x00);
    writeReg(dev, 0x65, 0x00);
    writeReg(dev, 0x66, 0xA0);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x22, 0x32);
    writeReg(dev, 0x47, 0x14);
    writeReg(dev, 0x49, 0xFF);
    writeReg(dev, 0x4A, 0x00);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x7A, 0x0A);
    writeReg(dev, 0x7B, 0x00);
    writeReg(dev, 0x78, 0x21);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x23, 0x34);
    writeReg(dev, 0x42, 0x00);
    writeReg(dev, 0x44, 0xFF);
    writeReg(dev, 0x45, 0x26);
    writeReg(dev, 0x46, 0x05);
    writeReg(dev, 0x40, 0x40);
    writeReg(dev, 0x0E, 0x06);
    writeReg(dev, 0x20, 0x1A);
    writeReg(dev, 0x43, 0x40);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x34, 0x03);
    writeReg(dev, 0x35, 0x44);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x31, 0x04);
    writeReg(dev, 0x4B, 0x09);
    writeReg(dev, 0x4C, 0x05);
    writeReg(dev, 0x4D, 0x04);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x44, 0x00);
    writeReg(dev, 0x45, 0x20);
    writeReg(dev, 0x47, 0x08);
    writeReg(dev, 0x48, 0x28);
    writeReg(dev, 0x67, 0x00);
    writeReg(dev, 0x70, 0x04);
    writeReg(dev, 0x71, 0x01);
    writeReg(dev, 0x72, 0xFE);
    writeReg(dev, 0x76, 0x00);
    writeReg(dev, 0x77, 0x00);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x0D, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0x01, 0xF8);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x8E, 0x01);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x00);

    /* GPIO interrupt config */
    writeReg(dev, SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
    writeReg(dev, GPIO_HV_MUX_ACTIVE_HIGH,
             readReg(dev, GPIO_HV_MUX_ACTIVE_HIGH) & ~0x10);
    writeReg(dev, SYSTEM_INTERRUPT_CLEAR, 0x01);

    dev->measurement_timing_budget_us = getMeasurementTimingBudget(dev);
    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0xE8);
    setMeasurementTimingBudget(dev, dev->measurement_timing_budget_us);

    /* Reference calibration */
    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0x01);
    if (!performSingleRefCal(dev, 0x40)) return false;

    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0x02);
    if (!performSingleRefCal(dev, 0x00)) return false;

    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0xE8);
    return true;
}

/*******************************************************************************
 * Timing Budget
 ******************************************************************************/
static bool setMeasurementTimingBudget(VL53L0X_Dev_t *dev, uint32_t budget_us)
{
    SeqEnables_t  en;
    SeqTimeouts_t to;

    if (budget_us < 20000) return false;

    uint32_t used = 1320 + 960; /* StartOverhead + EndOverhead */

    getSequenceStepEnables(dev, &en);
    getSequenceStepTimeouts(dev, &en, &to);

    if (en.tcc)  used += (to.msrc_dss_tcc_us + 590);
    if (en.dss)  used += 2 * (to.msrc_dss_tcc_us + 690);
    else if (en.msrc) used += (to.msrc_dss_tcc_us + 660);
    if (en.pre_range) used += (to.pre_range_us + 660);

    if (en.final_range)
    {
        used += 550;
        if (used > budget_us) return false;

        uint32_t fr_timeout_us = budget_us - used;
        uint16_t fr_timeout_mclks = timeoutUsToMclks(fr_timeout_us, to.final_range_vcsel_period_pclks);
        if (en.pre_range) fr_timeout_mclks += to.pre_range_mclks;

        writeReg16(dev, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, encodeTimeout(fr_timeout_mclks));
        dev->measurement_timing_budget_us = budget_us;
    }
    return true;
}

static uint32_t getMeasurementTimingBudget(VL53L0X_Dev_t *dev)
{
    SeqEnables_t  en;
    SeqTimeouts_t to;

    uint32_t budget = 1910 + 960;

    getSequenceStepEnables(dev, &en);
    getSequenceStepTimeouts(dev, &en, &to);

    if (en.tcc)  budget += (to.msrc_dss_tcc_us + 590);
    if (en.dss)  budget += 2 * (to.msrc_dss_tcc_us + 690);
    else if (en.msrc) budget += (to.msrc_dss_tcc_us + 660);
    if (en.pre_range) budget += (to.pre_range_us + 660);
    if (en.final_range) budget += (to.final_range_us + 550);

    dev->measurement_timing_budget_us = budget;
    return budget;
}

/*******************************************************************************
 * VCSEL Pulse Period
 ******************************************************************************/
static bool setVcselPulsePeriod(VL53L0X_Dev_t *dev, uint8_t type, uint8_t period_pclks)
{
    uint8_t vcsel_reg = encodeVcselPeriod(period_pclks);
    SeqEnables_t  en;
    SeqTimeouts_t to;

    getSequenceStepEnables(dev, &en);
    getSequenceStepTimeouts(dev, &en, &to);

    if (type == 0) /* PreRange */
    {
        switch (period_pclks)
        {
            case 12: writeReg(dev, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x18); break;
            case 14: writeReg(dev, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x30); break;
            case 16: writeReg(dev, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x40); break;
            case 18: writeReg(dev, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x50); break;
            default: return false;
        }
        writeReg(dev, PRE_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
        writeReg(dev, PRE_RANGE_CONFIG_VCSEL_PERIOD, vcsel_reg);

        uint16_t new_pr = timeoutUsToMclks(to.pre_range_us, period_pclks);
        writeReg16(dev, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI, encodeTimeout(new_pr));

        uint16_t new_msrc = timeoutUsToMclks(to.msrc_dss_tcc_us, period_pclks);
        writeReg(dev, MSRC_CONFIG_TIMEOUT_MACROP, (new_msrc > 256) ? 255 : (new_msrc - 1));
    }
    else if (type == 1) /* FinalRange */
    {
        switch (period_pclks)
        {
            case 8:
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x10);
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_LOW,  0x08);
                writeReg(dev, GLOBAL_CONFIG_VCSEL_WIDTH, 0x02);
                writeReg(dev, ALGO_PHASECAL_CONFIG_TIMEOUT, 0x0C);
                writeReg(dev, 0xFF, 0x01);
                writeReg(dev, ALGO_PHASECAL_LIM, 0x30);
                writeReg(dev, 0xFF, 0x00);
                break;
            case 10:
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x28);
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_LOW,  0x08);
                writeReg(dev, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03);
                writeReg(dev, ALGO_PHASECAL_CONFIG_TIMEOUT, 0x09);
                writeReg(dev, 0xFF, 0x01);
                writeReg(dev, ALGO_PHASECAL_LIM, 0x20);
                writeReg(dev, 0xFF, 0x00);
                break;
            case 12:
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x38);
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_LOW,  0x08);
                writeReg(dev, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03);
                writeReg(dev, ALGO_PHASECAL_CONFIG_TIMEOUT, 0x08);
                writeReg(dev, 0xFF, 0x01);
                writeReg(dev, ALGO_PHASECAL_LIM, 0x20);
                writeReg(dev, 0xFF, 0x00);
                break;
            case 14:
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x48);
                writeReg(dev, FINAL_RANGE_CONFIG_VALID_PHASE_LOW,  0x08);
                writeReg(dev, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03);
                writeReg(dev, ALGO_PHASECAL_CONFIG_TIMEOUT, 0x07);
                writeReg(dev, 0xFF, 0x01);
                writeReg(dev, ALGO_PHASECAL_LIM, 0x20);
                writeReg(dev, 0xFF, 0x00);
                break;
            default: return false;
        }
        writeReg(dev, FINAL_RANGE_CONFIG_VCSEL_PERIOD, vcsel_reg);

        uint16_t new_fr = timeoutUsToMclks(to.final_range_us, period_pclks);
        if (en.pre_range) new_fr += to.pre_range_mclks;
        writeReg16(dev, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, encodeTimeout(new_fr));
    }
    else return false;

    setMeasurementTimingBudget(dev, dev->measurement_timing_budget_us);

    uint8_t seq_cfg = readReg(dev, SYSTEM_SEQUENCE_CONFIG);
    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, 0x02);
    performSingleRefCal(dev, 0x00);
    writeReg(dev, SYSTEM_SEQUENCE_CONFIG, seq_cfg);
    return true;
}

static uint8_t getVcselPulsePeriod(VL53L0X_Dev_t *dev, uint8_t type)
{
    if (type == 0)
        return decodeVcselPeriod(readReg(dev, PRE_RANGE_CONFIG_VCSEL_PERIOD));
    else if (type == 1)
        return decodeVcselPeriod(readReg(dev, FINAL_RANGE_CONFIG_VCSEL_PERIOD));
    return 255;
}

/*******************************************************************************
 * Continuous / Single-Shot Ranging
 ******************************************************************************/
static void startContinuous(VL53L0X_Dev_t *dev, uint32_t period_ms)
{
    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    writeReg(dev, 0x91, dev->stop_variable);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x00);

    if (period_ms != 0)
    {
        uint16_t osc_cal = readReg16(dev, OSC_CALIBRATE_VAL);
        if (osc_cal != 0) period_ms *= osc_cal;
        writeReg32(dev, SYSTEM_INTERMEASUREMENT_PERIOD, period_ms);
        writeReg(dev, SYSRANGE_START, 0x04);
    }
    else
    {
        writeReg(dev, SYSRANGE_START, 0x02);
    }
}

static void stopContinuous(VL53L0X_Dev_t *dev)
{
    writeReg(dev, SYSRANGE_START, 0x01);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    writeReg(dev, 0x91, 0x00);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
}

static uint16_t readRangeContinuousMm(VL53L0X_Dev_t *dev)
{
    startTimeout(dev);
    while ((readReg(dev, RESULT_INTERRUPT_STATUS) & 0x07) == 0)
    {
        if (checkTimeoutExpired(dev))
        {
            dev->did_timeout = true;
            return 65535;
        }
    }

    uint16_t range = readReg16(dev, RESULT_RANGE_STATUS + 10);
    writeReg(dev, SYSTEM_INTERRUPT_CLEAR, 0x01);
    return range;
}

static uint16_t readRangeSingleMm(VL53L0X_Dev_t *dev)
{
    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    writeReg(dev, 0x91, dev->stop_variable);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x00);

    writeReg(dev, SYSRANGE_START, 0x01);

    startTimeout(dev);
    while (readReg(dev, SYSRANGE_START) & 0x01)
    {
        if (checkTimeoutExpired(dev))
        {
            dev->did_timeout = true;
            return 65535;
        }
    }
    return readRangeContinuousMm(dev);
}

static bool timeoutOccurred(VL53L0X_Dev_t *dev)
{
    bool tmp = dev->did_timeout;
    dev->did_timeout = false;
    return tmp;
}

/*******************************************************************************
 * Internal: SPAD Info
 ******************************************************************************/
static bool getSpadInfo(VL53L0X_Dev_t *dev, uint8_t *count, bool *type_is_aperture)
{
    uint8_t tmp;

    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x00);
    writeReg(dev, 0xFF, 0x06);
    writeReg(dev, 0x83, readReg(dev, 0x83) | 0x04);
    writeReg(dev, 0xFF, 0x07);
    writeReg(dev, 0x81, 0x01);
    writeReg(dev, 0x80, 0x01);
    writeReg(dev, 0x94, 0x6b);
    writeReg(dev, 0x83, 0x00);

    startTimeout(dev);
    while (readReg(dev, 0x83) == 0x00)
    {
        if (checkTimeoutExpired(dev)) return false;
    }

    writeReg(dev, 0x83, 0x01);
    tmp = readReg(dev, 0x92);
    *count = tmp & 0x7f;
    *type_is_aperture = (tmp >> 7) & 0x01;

    writeReg(dev, 0x81, 0x00);
    writeReg(dev, 0xFF, 0x06);
    writeReg(dev, 0x83, readReg(dev, 0x83) & ~0x04);
    writeReg(dev, 0xFF, 0x01);
    writeReg(dev, 0x00, 0x01);
    writeReg(dev, 0xFF, 0x00);
    writeReg(dev, 0x80, 0x00);
    return true;
}

/*******************************************************************************
 * Internal: Sequence Step Enables/Timeouts
 ******************************************************************************/
static void getSequenceStepEnables(VL53L0X_Dev_t *dev, SeqEnables_t *en)
{
    uint8_t sc = readReg(dev, SYSTEM_SEQUENCE_CONFIG);
    en->tcc         = (sc >> 4) & 0x1;
    en->dss         = (sc >> 3) & 0x1;
    en->msrc        = (sc >> 2) & 0x1;
    en->pre_range   = (sc >> 6) & 0x1;
    en->final_range = (sc >> 7) & 0x1;
}

static void getSequenceStepTimeouts(VL53L0X_Dev_t *dev, SeqEnables_t *en, SeqTimeouts_t *to)
{
    to->pre_range_vcsel_period_pclks = getVcselPulsePeriod(dev, 0);
    to->msrc_dss_tcc_mclks = readReg(dev, MSRC_CONFIG_TIMEOUT_MACROP) + 1;
    to->msrc_dss_tcc_us = timeoutMclksToUs(to->msrc_dss_tcc_mclks, to->pre_range_vcsel_period_pclks);
    to->pre_range_mclks = decodeTimeout(readReg16(dev, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI));
    to->pre_range_us = timeoutMclksToUs(to->pre_range_mclks, to->pre_range_vcsel_period_pclks);
    to->final_range_vcsel_period_pclks = getVcselPulsePeriod(dev, 1);
    to->final_range_mclks = decodeTimeout(readReg16(dev, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI));
    if (en->pre_range)
        to->final_range_mclks -= to->pre_range_mclks;
    to->final_range_us = timeoutMclksToUs(to->final_range_mclks, to->final_range_vcsel_period_pclks);
}

/*******************************************************************************
 * Internal: Timeout Encode/Decode/Convert
 ******************************************************************************/
static uint16_t decodeTimeout(uint16_t reg_val)
{
    return (uint16_t)((reg_val & 0x00FF) <<
           (uint16_t)((reg_val & 0xFF00) >> 8)) + 1;
}

static uint16_t encodeTimeout(uint16_t timeout_mclks)
{
    uint32_t ls_byte = 0;
    uint16_t ms_byte = 0;
    if (timeout_mclks > 0)
    {
        ls_byte = timeout_mclks - 1;
        while ((ls_byte & 0xFFFFFF00) > 0)
        {
            ls_byte >>= 1;
            ms_byte++;
        }
        return (ms_byte << 8) | (ls_byte & 0xFF);
    }
    return 0;
}

static uint32_t timeoutMclksToUs(uint16_t mclks, uint8_t vcsel_pclks)
{
    uint32_t macro_ns = calcMacroPeriod(vcsel_pclks);
    return ((mclks * macro_ns) + (macro_ns / 2)) / 1000;
}

static uint32_t timeoutUsToMclks(uint32_t us, uint8_t vcsel_pclks)
{
    uint32_t macro_ns = calcMacroPeriod(vcsel_pclks);
    return (((us * 1000) + (macro_ns / 2)) / macro_ns);
}

/*******************************************************************************
 * Internal: performSingleRefCal
 ******************************************************************************/
static bool performSingleRefCal(VL53L0X_Dev_t *dev, uint8_t vhv_init_byte)
{
    writeReg(dev, SYSRANGE_START, 0x01 | vhv_init_byte);

    startTimeout(dev);
    while ((readReg(dev, RESULT_INTERRUPT_STATUS) & 0x07) == 0)
    {
        if (checkTimeoutExpired(dev)) return false;
    }

    writeReg(dev, SYSTEM_INTERRUPT_CLEAR, 0x01);
    writeReg(dev, SYSRANGE_START, 0x00);
    return true;
}

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 *              - 32 MHz internal oscillator with PLL
 *              - PPS mapping for EUSART (RB2=TX, RB3=RX)
 *              - PPS mapping for MSSP I2C (RC4=SDA, RC5=SCL)
 *              - XSHUT on RB5 for VL53L0X reset control
 *
 * Usage: initMain()
 ******************************************************************************/
void initMain(void)
{
    // Run at 32 MHz
    internal_32();

    // Allow PLL startup time ~2 ms
    __delay_ms(10);

    // EUSART TX pin
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;

    // I2C pins: digital, open-drain input (MSSP controls)
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    // XSHUT pin for VL53L0X reset
    TRISBbits.TRISB5 = 0;
    ANSELBbits.ANSB5 = 0;

    /////////////////////
    // Setup PPS
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RB2PPSbits.RB2PPS = 0x14;          // RB2 -> EUSART:TX
    RXPPSbits.RXPPS = 0x0B;            // RB3 -> EUSART:RX

    RC4PPSbits.RC4PPS = 0x0011;        // RC4 -> MSSP:SDA
    SSPDATPPSbits.SSPDATPPS = 0x0014;  // RC4 -> MSSP:SDA
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;  // RC5 -> MSSP:SCL
    RC5PPSbits.RC5PPS = 0x0010;        // RC5 -> MSSP:SCL

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
}

/*******************************************************************************
 * Main Application
 ******************************************************************************/
void main(void)
{
    initMain();

    /* Start millisecond tick */
    TMR0_Init();

    /* Initialize EUSART at 19200 baud */
    EUSART_Initialize(19200);

    /* Initialize I2C (100 kHz via MSSP) */
    I2C_Init();

    EUSART_Write_Text("\r\nVL53L0X on PIC16F1718\r\n");
    EUSART_Write_Text("---------------------\r\n");

    /* XSHUT hard reset sequence */
    LATBbits.LATB5 = 0;     /* Shut down sensor */
    __delay_ms(2);
    LATBbits.LATB5 = 1;     /* Power up sensor */
    __delay_ms(2);

    /* Create and initialize sensor */
    VL53L0X_Dev_t sensor = {
        .address     = VL53L0X_ADDRESS,
        .io_timeout  = 500,
        .did_timeout = false,
    };

    if (VL53L0X_Init(&sensor))
    {
        EUSART_Write_Text("Init OK\r\n");
    }
    else
    {
        EUSART_Write_Text("Init FAILED\r\n");
        while (1);
    }

#ifdef LONG_RANGE
    /* 0.10 MCPS in Q9.7 = 13 */
    writeReg16(&sensor, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 13);
    setVcselPulsePeriod(&sensor, 0, 18);  /* PreRange */
    setVcselPulsePeriod(&sensor, 1, 14);  /* FinalRange */
    EUSART_Write_Text("LONG RANGE\r\n");
#endif

#ifdef HIGH_SPEED
    setMeasurementTimingBudget(&sensor, 20000);
    EUSART_Write_Text("HIGH SPEED\r\n");
#elif defined(HIGH_ACCURACY)
    setMeasurementTimingBudget(&sensor, 200000);
    EUSART_Write_Text("HIGH ACCURACY\r\n");
#endif

    /* Start continuous back-to-back ranging */
    startContinuous(&sensor, 0);
    EUSART_Write_Text("Ranging...\r\n");

    while (1)
    {
        uint16_t range = readRangeContinuousMm(&sensor);

        if (timeoutOccurred(&sensor))
        {
            EUSART_Write_Text("TIMEOUT\r\n");
        }
        else
        {
            EUSART_Write_Text("\t");
            EUSART_Write_Integer((int)range);
            EUSART_Write_Text("\tmm\r\n");
        }
    }
}
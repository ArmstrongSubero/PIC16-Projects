/*
 * File:    Main.c
 * Author:  Armstrong Subero
 * PIC:     16F1718 w/Int OSC @ 32MHz, 5v
 * Program: 65_ACC_GYRO_MPU6050
 * Compiler: XC8
 * Program Version: 1.0
 *
 * Program Description:
 *     MPU6050 6-axis IMU on PIC16F1718 using hardware I2C (MSSP)
 *     and EUSART for serial output. Ported from CH32V003 version written by 
 *     Armstrong Subero.
 *     Features calibration, median-of-3 + IIR smoothing, and
 *     fixed-point output in mg / mdps / deg C.
 *
 * Hardware Description:
 *     MPU6050 connected to PIC16F1718:
 *         VDD   -> 3.3V
 *         GND   -> GND
 *         SDA   -> RC4 (4.7k pullup)
 *         SCL   -> RC5 (4.7k pullup)
 *         AD0   -> GND (address 0x68)
 *         INT   -> NC  (polled mode)
 *
 * Created February 7th, 2026
 */

/*******************************************************************************
 * Includes and Defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "EUSART.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * MPU6050 Constants
 ******************************************************************************/
#define MPU6050_ADDR        0x68    /* 7-bit, AD0=GND */

/* Register map */
#define REG_SMPLRT_DIV      0x19
#define REG_CONFIG          0x1A
#define REG_GYRO_CONFIG     0x1B
#define REG_ACCEL_CONFIG    0x1C
#define REG_FIFO_EN         0x23
#define REG_INT_PIN_CFG     0x37
#define REG_INT_ENABLE      0x38
#define REG_INT_STATUS      0x3A
#define REG_ACCEL_XOUT_H    0x3B
#define REG_USER_CTRL       0x6A
#define REG_PWR_MGMT_1      0x6B
#define REG_WHO_AM_I        0x75

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
 * MPU6050 Register Helpers
 ******************************************************************************/

static bool mpu_write_reg(uint8_t reg, uint8_t val)
{
    return (i2c_write_bytes(MPU6050_ADDR, reg, &val, 1) == 0);
}

static bool mpu_read_reg(uint8_t reg, uint8_t *val)
{
    return (i2c_read_bytes(MPU6050_ADDR, reg, val, 1) == 0);
}

static bool mpu_read_multi(uint8_t reg, uint8_t *buf, uint8_t len)
{
    return (i2c_read_bytes(MPU6050_ADDR, reg, buf, len) == 0);
}

/*******************************************************************************
 * MPU6050 Raw Data
 ******************************************************************************/

typedef struct {
    int16_t ax, ay, az;
    int16_t temp;
    int16_t gx, gy, gz;
} mpu_raw_t;

/* Frame sanity check (from CH32V003 version) */
static bool mpu_frame_sane(const uint8_t *b, uint8_t len)
{
    uint8_t orv = 0, andv = 0xFF;
    for (uint8_t i = 0; i < len; i++)
    {
        orv  |= b[i];
        andv &= b[i];
    }
    if (orv == 0x00 || andv == 0xFF) return false;

    int16_t traw = (int16_t)((uint16_t)b[6] << 8 | b[7]);
    if (traw < -15000 || traw > 15000) return false;

    return true;
}

static bool mpu_read_raw(mpu_raw_t *o)
{
    uint8_t b[14];

    for (uint8_t attempt = 0; attempt < 3; attempt++)
    {
        if (mpu_read_multi(REG_ACCEL_XOUT_H, b, 14) && mpu_frame_sane(b, 14))
        {
            o->ax   = (int16_t)((uint16_t)b[0]  << 8 | b[1]);
            o->ay   = (int16_t)((uint16_t)b[2]  << 8 | b[3]);
            o->az   = (int16_t)((uint16_t)b[4]  << 8 | b[5]);
            o->temp = (int16_t)((uint16_t)b[6]  << 8 | b[7]);
            o->gx   = (int16_t)((uint16_t)b[8]  << 8 | b[9]);
            o->gy   = (int16_t)((uint16_t)b[10] << 8 | b[11]);
            o->gz   = (int16_t)((uint16_t)b[12] << 8 | b[13]);
            return true;
        }
        __delay_ms(1);
    }
    return false;
}

static bool mpu_wait_data_ready(uint16_t timeout_ms)
{
    uint8_t st = 0;
    uint32_t start = millis();

    while ((millis() - start) < timeout_ms)
    {
        if (mpu_read_reg(REG_INT_STATUS, &st) && (st & 0x01))
            return true;
        __delay_ms(1);
    }
    return false;
}

/*******************************************************************************
 * MPU6050 Init
 ******************************************************************************/

static bool mpu_init(void)
{
    uint8_t who = 0;

    if (!mpu_read_reg(REG_WHO_AM_I, &who))
        return false;

    if ((who & 0x7E) != 0x68)
        return false;

    /* Wake up, PLL with X gyro reference */
    if (!mpu_write_reg(REG_PWR_MGMT_1, 0x01)) return false;
    __delay_ms(5);

    /* DLPF = 3 (~42 Hz bandwidth) */
    if (!mpu_write_reg(REG_CONFIG, 0x03)) return false;

    /* Sample rate = 1kHz / (1+9) = 100 Hz */
    if (!mpu_write_reg(REG_SMPLRT_DIV, 9)) return false;

    /* Gyro: +/- 250 dps */
    if (!mpu_write_reg(REG_GYRO_CONFIG, 0x00)) return false;

    /* Accel: +/- 2g */
    if (!mpu_write_reg(REG_ACCEL_CONFIG, 0x00)) return false;

    /* Disable FIFO, enable DRDY interrupt */
    mpu_write_reg(REG_USER_CTRL, 0x00);
    mpu_write_reg(REG_FIFO_EN, 0x00);
    mpu_write_reg(REG_INT_PIN_CFG, 0x00);
    mpu_write_reg(REG_INT_ENABLE, 0x01);

    return true;
}

/*******************************************************************************
 * Fixed-Point Scaling
 *
 * Accel: +/-2g  => 16384 LSB/g  => mg   = raw * 1000 / 16384
 * Gyro:  +/-250 => 131 LSB/dps  => mdps = raw * 1000 / 131
 * Temp:  degC = raw/340 + 36.53  => x100 = raw*100/340 + 3653
 ******************************************************************************/

static int32_t raw_to_mg(int16_t r)
{
    return ((int32_t)r * 1000 + (r >= 0 ? 8192 : -8192)) / 16384;
}

static int32_t raw_to_mdps(int16_t r)
{
    return ((int32_t)r * 1000 + (r >= 0 ? 65 : -65)) / 131;
}

static int32_t temp_to_c_x100(int16_t t)
{
    return ((int32_t)t * 100 + (t >= 0 ? 169 : -169)) / 340 + 3653;
}

/*******************************************************************************
 * Median-of-3
 ******************************************************************************/

static int32_t median3(int32_t a, int32_t b, int32_t c)
{
    if (a > b) { int32_t t = a; a = b; b = t; }
    if (b > c) { int32_t t = b; b = c; c = t; }
    if (a > b) { int32_t t = a; a = b; b = t; }
    return b;
}

/*******************************************************************************
 * Calibration and Filter State
 ******************************************************************************/

#define ACC_SMOOTH_SHIFT    3   /* alpha = 1/8 */
#define GYR_SMOOTH_SHIFT    2   /* alpha = 1/4 */

static int32_t g_ax_off_mg = 0, g_ay_off_mg = 0, g_az_off_mg = 0;
static int32_t g_gx_off_mdps = 0, g_gy_off_mdps = 0, g_gz_off_mdps = 0;

static int32_t s_ax = 0, s_ay = 0, s_az = 0;
static int32_t s_gx = 0, s_gy = 0, s_gz = 0;
static bool    filter_initialized = false;

static int32_t ax_hist[2], ay_hist[2], az_hist[2];
static int32_t gx_hist[2], gy_hist[2], gz_hist[2];

/*******************************************************************************
 * Calibration ? hold sensor flat and still
 ******************************************************************************/

#define CALIB_SAMPLES   200
#define CALIB_DELAY_MS  5

static bool mpu_calibrate(void)
{
    int32_t sax = 0, say = 0, saz = 0;
    int32_t sgx = 0, sgy = 0, sgz = 0;
    uint16_t good = 0;

    /* Narrower DLPF during calibration */
    mpu_write_reg(REG_CONFIG, 0x06);  /* ~5 Hz */
    __delay_ms(50);

    for (uint16_t i = 0; i < CALIB_SAMPLES; i++)
    {
        if (!mpu_wait_data_ready(20)) continue;

        mpu_raw_t r;
        if (mpu_read_raw(&r))
        {
            sax += raw_to_mg(r.ax);
            say += raw_to_mg(r.ay);
            saz += raw_to_mg(r.az);
            sgx += raw_to_mdps(r.gx);
            sgy += raw_to_mdps(r.gy);
            sgz += raw_to_mdps(r.gz);
            good++;
        }
        __delay_ms(CALIB_DELAY_MS);
    }

    if (good < 50) return false;

    g_ax_off_mg   = sax / (int32_t)good;
    g_ay_off_mg   = say / (int32_t)good;
    g_az_off_mg   = saz / (int32_t)good - 1000;  /* Expect +1g on Z */

    g_gx_off_mdps = sgx / (int32_t)good;
    g_gy_off_mdps = sgy / (int32_t)good;
    g_gz_off_mdps = sgz / (int32_t)good;

    /* Restore runtime DLPF */
    mpu_write_reg(REG_CONFIG, 0x03);
    __delay_ms(10);

    s_ax = 0; s_ay = 0; s_az = 1000;
    s_gx = 0; s_gy = 0; s_gz = 0;
    filter_initialized = false;

    for (uint8_t i = 0; i < 2; i++)
    {
        ax_hist[i] = 0; ay_hist[i] = 0; az_hist[i] = 0;
        gx_hist[i] = 0; gy_hist[i] = 0; gz_hist[i] = 0;
    }

    return true;
}

/*******************************************************************************
 * Filter Step: Median-of-3 + IIR Smoothing
 ******************************************************************************/

static void filter_step(const mpu_raw_t *r)
{
    int32_t ax = raw_to_mg(r->ax)   - g_ax_off_mg;
    int32_t ay = raw_to_mg(r->ay)   - g_ay_off_mg;
    int32_t az = raw_to_mg(r->az)   - g_az_off_mg;
    int32_t gx = raw_to_mdps(r->gx) - g_gx_off_mdps;
    int32_t gy = raw_to_mdps(r->gy) - g_gy_off_mdps;
    int32_t gz = raw_to_mdps(r->gz) - g_gz_off_mdps;

    /* Clamp */
    if (ax < -4000)   ax = -4000;   if (ax > 4000)   ax = 4000;
    if (ay < -4000)   ay = -4000;   if (ay > 4000)   ay = 4000;
    if (az < -4000)   az = -4000;   if (az > 4000)   az = 4000;
    if (gx < -250000) gx = -250000; if (gx > 250000) gx = 250000;
    if (gy < -250000) gy = -250000; if (gy > 250000) gy = 250000;
    if (gz < -250000) gz = -250000; if (gz > 250000) gz = 250000;

    /* Median-of-3 */
    int32_t ax_m = median3(ax_hist[0], ax_hist[1], ax);
    int32_t ay_m = median3(ay_hist[0], ay_hist[1], ay);
    int32_t az_m = median3(az_hist[0], az_hist[1], az);
    int32_t gx_m = median3(gx_hist[0], gx_hist[1], gx);
    int32_t gy_m = median3(gy_hist[0], gy_hist[1], gy);
    int32_t gz_m = median3(gz_hist[0], gz_hist[1], gz);

    ax_hist[1] = ax_hist[0]; ax_hist[0] = ax;
    ay_hist[1] = ay_hist[0]; ay_hist[0] = ay;
    az_hist[1] = az_hist[0]; az_hist[0] = az;
    gx_hist[1] = gx_hist[0]; gx_hist[0] = gx;
    gy_hist[1] = gy_hist[0]; gy_hist[0] = gy;
    gz_hist[1] = gz_hist[0]; gz_hist[0] = gz;

    /* IIR smoothing */
    if (!filter_initialized)
    {
        s_ax = ax_m; s_ay = ay_m; s_az = az_m;
        s_gx = gx_m; s_gy = gy_m; s_gz = gz_m;
        filter_initialized = true;
    }
    else
    {
        s_ax += (ax_m - s_ax) >> ACC_SMOOTH_SHIFT;
        s_ay += (ay_m - s_ay) >> ACC_SMOOTH_SHIFT;
        s_az += (az_m - s_az) >> ACC_SMOOTH_SHIFT;
        s_gx += (gx_m - s_gx) >> GYR_SMOOTH_SHIFT;
        s_gy += (gy_m - s_gy) >> GYR_SMOOTH_SHIFT;
        s_gz += (gz_m - s_gz) >> GYR_SMOOTH_SHIFT;
    }
}

/*******************************************************************************
 * UART Helpers
 ******************************************************************************/

static void UART_PrintInt32(int32_t val)
{
    char buf[12];
    int8_t i = 0;

    if (val < 0)
    {
        EUSART_Write_Text("-");
        if (val == (-2147483647L - 1))
        {
            EUSART_Write_Text("2147483648");
            return;
        }
        val = -val;
    }

    if (val == 0) { EUSART_Write_Text("0"); return; }

    while (val > 0) { buf[i++] = '0' + (val % 10); val /= 10; }
    for (i--; i >= 0; i--)
    {
        char c[2] = { buf[i], '\0' };
        EUSART_Write_Text(c);
    }
}

static void UART_PrintFixed100(int32_t val)
{
    if (val < 0) { EUSART_Write_Text("-"); val = -val; }

    UART_PrintInt32(val / 100);
    EUSART_Write_Text(".");
    int32_t frac = val % 100;
    if (frac < 10) EUSART_Write_Text("0");
    UART_PrintInt32(frac);
}

/*******************************************************************************
 * initMain
 ******************************************************************************/

void initMain(void)
{
    internal_32();
    __delay_ms(10);

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

void main(void)
{
    initMain();
    TMR0_Init();
    EUSART_Initialize(19200);
    I2C_Init();

    EUSART_Write_Text("\r\nMPU6050 on PIC16F1718\r\n");
    EUSART_Write_Text("Accel +/-2g, Gyro +/-250dps\r\n");
    EUSART_Write_Text("DLPF ~42Hz, 100Hz sample rate\r\n");
    EUSART_Write_Text("------------------------------\r\n");

    if (mpu_init())
    {
        EUSART_Write_Text("MPU6050 Init OK\r\n");
    }
    else
    {
        EUSART_Write_Text("MPU6050 Init FAILED!\r\n");
        EUSART_Write_Text("Check wiring (SDA=RC4, SCL=RC5)\r\n");
        while (1);
    }

    EUSART_Write_Text("Hold still for calibration...\r\n");
    if (mpu_calibrate())
    {
        EUSART_Write_Text("Calibration done\r\n");

        EUSART_Write_Text("Aoff mg: X=");
        UART_PrintInt32(g_ax_off_mg);
        EUSART_Write_Text(" Y=");
        UART_PrintInt32(g_ay_off_mg);
        EUSART_Write_Text(" Z=");
        UART_PrintInt32(g_az_off_mg);
        EUSART_Write_Text("\r\n");

        EUSART_Write_Text("Goff mdps: X=");
        UART_PrintInt32(g_gx_off_mdps);
        EUSART_Write_Text(" Y=");
        UART_PrintInt32(g_gy_off_mdps);
        EUSART_Write_Text(" Z=");
        UART_PrintInt32(g_gz_off_mdps);
        EUSART_Write_Text("\r\n\r\n");
    }
    else
    {
        EUSART_Write_Text("Calibration FAILED\r\n");
        EUSART_Write_Text("Continuing without calibration...\r\n\r\n");
    }

    uint32_t last_print_ms = 0;
    uint16_t read_errors = 0;

    while (1)
    {
        /* DRDY-gated read */
        if (!mpu_wait_data_ready(20))
        {
            read_errors++;
            if (read_errors > 10)
            {
                EUSART_Write_Text("I2C stall, re-init\r\n");
                I2C_Init();
                __delay_ms(10);
                mpu_init();
                read_errors = 0;
            }
            continue;
        }

        read_errors = 0;

        mpu_raw_t r;
        if (!mpu_read_raw(&r))
            continue;

        filter_step(&r);

        /* Print at ~10 Hz */
        uint32_t now = millis();
        if ((now - last_print_ms) >= 100)
        {
            last_print_ms = now;

            EUSART_Write_Text("ACC mg: X=");
            UART_PrintInt32(s_ax);
            EUSART_Write_Text(" Y=");
            UART_PrintInt32(s_ay);
            EUSART_Write_Text(" Z=");
            UART_PrintInt32(s_az);

            EUSART_Write_Text(" | GY mdps: X=");
            UART_PrintInt32(s_gx);
            EUSART_Write_Text(" Y=");
            UART_PrintInt32(s_gy);
            EUSART_Write_Text(" Z=");
            UART_PrintInt32(s_gz);

            EUSART_Write_Text(" | T=");
            UART_PrintFixed100(temp_to_c_x100(r.temp));
            EUSART_Write_Text("C");

            EUSART_Write_Text("\r\n");
        }

        __delay_ms(10);
    }
}
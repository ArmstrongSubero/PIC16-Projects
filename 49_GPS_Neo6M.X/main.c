/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/Int OSC @ 32MHz, 5v
 * Program: 49_GPS
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 * Program Version: 1.0
 *                
 * Program Description: This Program Allows PIC16F1718 to communicate via the
 *                      EUSART module to a NEO-6M GPS module and display Latitude
 *                      and Longitude coordinates on a software USART module. 
 *           
 * Hardware Description: A NEO-6M GPS module is connected to the PIC16F1718 as
 *                       follows:
 *                        
 *                       PPS -> NC               
 *                       RXD -> TX
 *                       TXD -> RX
 *                       GND -> GND
 *                       VCC -> VCC
 * 
 *                       Upgrades:
 *                          - Parse GGA for fix quality, sats, HDOP
 *                          - Gate RMC output on quality thresholds
 *                          - Average N samples for stable coordinates
 *                                 
 * Created April 18th, 2017, 12:51 PM
 * Updated January 29th, 2026,  8:56 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "SEUSART.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/* ---------------- Buffers (static, not stack) ---------------- */
static char line[96];
static char work[96];
static char *fld[20];

/* ---------------- SoftUART helpers ---------------- */
static void suart_puts(const char *s){ SUART_Write_Text((char*)s); }
static void suart_putc(char c){ SUART_Write_Char(c); }

static void suart_print_uint16(uint16_t v)
{
    char buf[6];
    char i = 0;
    if (v == 0) { suart_putc('0'); return; }
    while (v > 0 && i < (char)sizeof(buf)) { buf[i++] = (char)('0' + (v % 10)); v /= 10; }
    while (i--) suart_putc(buf[i]);
}

static void suart_print_int32(int32_t v)
{
    char buf[12];
    char i = 0;
    if (v == 0) { suart_putc('0'); return; }
    if (v < 0) { suart_putc('-'); v = -v; }
    while (v > 0 && i < (char)sizeof(buf)) { buf[i++] = (char)('0' + (v % 10)); v /= 10; }
    while (i--) suart_putc(buf[i]);
}

/* Print signed microdegrees as D.DDDDDD (no float) */
static void suart_print_microdeg(int32_t udeg)
{
    if (udeg < 0) { suart_putc('-'); udeg = -udeg; }
    int32_t whole = udeg / 1000000L;
    int32_t frac  = udeg % 1000000L;

    suart_print_int32(whole);
    suart_putc('.');

    int32_t div = 100000L;
    while (div > 0) {
        suart_putc((char)('0' + (frac / div)));
        frac %= div;
        div /= 10;
    }
}

/* ---------------- NMEA checksum ---------------- */
static int hex_nibble(char c)
{
    if (c >= '0' && c <= '9') return (int)(c - '0');
    if (c >= 'A' && c <= 'F') return (int)(c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (int)(c - 'a' + 10);
    return -1;
}

static uint8_t nmea_checksum_ok(const char *s)
{
    if (!s || s[0] != '$') return 0;
    uint8_t cs = 0;
    const char *p = s + 1;
    while (*p && *p != '*' && *p != '\r' && *p != '\n') cs ^= (uint8_t)(*p++);
    if (*p != '*') return 0;
    int hi = hex_nibble(*(p+1));
    int lo = hex_nibble(*(p+2));
    if (hi < 0 || lo < 0) return 0;
    return (cs == (uint8_t)((hi<<4) | lo));
}

/* ---------------- Read one NMEA sentence ---------------- */
/* Resync: if '$' appears mid-capture, restart sentence */
static unsigned int gps_read_line(char *buf, unsigned int maxlen)
{
    unsigned int n = 0;
    char c;

    if (maxlen < 4) return 0;

    do { c = EUSART_Read(); } while (c != '$');
    buf[n++] = '$';

    while (n < (maxlen - 1)) {
        c = EUSART_Read();

        if (c == '$') {         // resync
            n = 0;
            buf[n++] = '$';
            continue;
        }

        buf[n++] = c;
        if (c == '\n') break;
    }

    buf[n] = '\0';
    return n;
}

/* ---------------- CSV split (no strtok) ---------------- */
static uint8_t split_csv(char *s, char *out[], uint8_t maxf)
{
    uint8_t n = 0;
    if (!s || !*s) return 0;
    out[n++] = s;

    for (char *p = s; *p && n < maxf; ++p) {
        if (*p == ',') { *p = 0; out[n++] = p + 1; }
        if (*p == '*') { *p = 0; break; }
    }
    return n;
}

/* ---------------- Parse helpers ---------------- */
static uint8_t parse_u8(const char *s, uint8_t *out)
{
    if (!s || !*s) return 0;
    uint16_t v = 0;
    while (*s && isdigit((unsigned char)*s)) {
        v = (uint16_t)(v * 10 + (uint8_t)(*s - '0'));
        s++;
    }
    *out = (uint8_t)v;
    return 1;
}

/* Parse HDOP string like "0.96" into hdop_x100 (96).
   Accepts "", returns 0 on fail. */
static uint8_t parse_hdop_x100(const char *s, uint16_t *out)
{
    if (!s || !*s) return 0;
    uint16_t whole = 0;
    uint16_t frac = 0;
    uint16_t frac_scale = 1;

    // whole
    while (*s && isdigit((unsigned char)*s)) {
        whole = (uint16_t)(whole * 10 + (uint16_t)(*s - '0'));
        s++;
    }

    if (*s == '.') {
        s++;
        // take up to 2 digits
        if (*s && isdigit((unsigned char)*s)) { frac = (uint16_t)(frac * 10 + (uint16_t)(*s - '0')); frac_scale *= 10; s++; }
        if (*s && isdigit((unsigned char)*s)) { frac = (uint16_t)(frac * 10 + (uint16_t)(*s - '0')); frac_scale *= 10; s++; }
    }

    // scale frac to /100
    // if 1 digit => scale 10, if 2 digits => scale 100
    if (frac_scale == 1) { // no frac digits
        *out = (uint16_t)(whole * 100);
    } else if (frac_scale == 10) {
        *out = (uint16_t)(whole * 100 + frac * 10);
    } else { // 100
        *out = (uint16_t)(whole * 100 + frac);
    }
    return 1;
}

// Convert "ddmm.mmmm" or "dddmm.mmmm" ? signed micro-degrees
int coord_to_microdeg(const char *field, unsigned char is_lat, int32_t *out)
{
    int dlen = is_lat ? 2 : 3;
    int deg = 0;

    for (int i = 0; i < dlen; i++)
        deg = deg * 10 + (field[i] - '0');

    int min_int = (field[dlen] - '0') * 10 + (field[dlen+1] - '0');

    int frac = 0;
    int scale = 1;
    int i = dlen + 2;

    if (field[i] == '.') {
        i++;
        while (field[i] && field[i] >= '0' && field[i] <= '9' && scale < 1000000) {
            frac = frac * 10 + (field[i++] - '0');
            scale *= 10;
        }
    }

    int64_t micro = (int64_t)deg * 1000000LL;
    micro += ((int64_t)min_int * 1000000LL + 30) / 60;
    micro += ((int64_t)frac * 1000000LL + (int64_t)scale * 30)
             / ((int64_t)scale * 60);

    *out = (int32_t)micro;
    return 1;
}

/* ---------------- Quality state (from GGA) ---------------- */
static volatile uint8_t  gga_fixq = 0;     // 0 = invalid, 1 = GPS fix, 2 = DGPS, ...
static volatile uint8_t  gga_sats = 0;     // satellites used
static volatile uint16_t gga_hdop_x100 = 9999; // HDOP * 100
static volatile uint8_t  gga_seen = 0;

/* Quality thresholds you asked for */
#define MIN_SATS        6
#define MAX_HDOP_X100   250   // 2.50

static uint8_t quality_ok(void)
{
    if (!gga_seen) return 0;
    if (gga_fixq < 1) return 0;
    if (gga_sats < MIN_SATS) return 0;
    if (gga_hdop_x100 > MAX_HDOP_X100) return 0;
    return 1;
}

/* Parse GGA line: fields: 6=fixq, 7=sats, 8=hdop */
static void handle_gga(const char *nmea)
{
    strncpy(work, nmea, sizeof(work) - 1);
    work[sizeof(work) - 1] = 0;

    uint8_t nf = split_csv(work, fld, 20);
    if (nf < 9) return;

    uint8_t fixq = 0, sats = 0;
    uint16_t hd = 0;

    if (!parse_u8(fld[6], &fixq)) return;
    if (!parse_u8(fld[7], &sats)) return;
    if (!parse_hdop_x100(fld[8], &hd)) return;

    gga_fixq = fixq;
    gga_sats = sats;
    gga_hdop_x100 = hd;
    gga_seen = 1;
}

/* ---------------- Averaging ---------------- */
#define AVG_N  8   // try 8 first; if you want smoother: 16

static int64_t sum_lat = 0;
static int64_t sum_lon = 0;
static uint8_t avg_count = 0;

static void avg_reset(void)
{
    sum_lat = 0;
    sum_lon = 0;
    avg_count = 0;
}

static void avg_add(int32_t lat, int32_t lon)
{
    sum_lat += (int64_t)lat;
    sum_lon += (int64_t)lon;
    if (avg_count < AVG_N) avg_count++;
}

static uint8_t avg_ready(void)
{
    return (avg_count >= AVG_N);
}

static void avg_print(void)
{
    int32_t lat_avg = (int32_t)(sum_lat / (int64_t)AVG_N);
    int32_t lon_avg = (int32_t)(sum_lon / (int64_t)AVG_N);

    suart_puts("AVG Maps: ");
    suart_print_microdeg(lat_avg);
    suart_puts(", ");
    suart_print_microdeg(lon_avg);

    suart_puts("  (fixq=");
    suart_putc((char)('0' + gga_fixq));
    suart_puts(" sats=");
    suart_print_uint16(gga_sats);
    suart_puts(" hdop=");
    suart_print_uint16(gga_hdop_x100 / 100);
    suart_putc('.');
    suart_putc((char)('0' + (gga_hdop_x100 % 100) / 10));
    suart_putc((char)('0' + (gga_hdop_x100 % 10)));
    suart_puts(")\r\n");

    avg_reset();
}

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);

    // Soft UART pins RB0/RB1
    TRISBbits.TRISB0 = 1;  ANSELBbits.ANSB0 = 0;
    TRISBbits.TRISB1 = 0;  ANSELBbits.ANSB1 = 0;
    LATBbits.LATB1 = 1;

    // HW UART pins RB2/RB3 (GPS)
    TRISBbits.TRISB2 = 0;  ANSELBbits.ANSB2 = 0;
    TRISBbits.TRISB3 = 1;  ANSELBbits.ANSB3 = 0;

    // PPS
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x00;
    RB2PPSbits.RB2PPS = 0x14;   // RB2 -> EUSART:TX
    RXPPSbits.RXPPS   = 0x0B;   // RB3 -> EUSART:RX
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0x01;
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
    __delay_ms(200);

    EUSART_Initialize(9600);

    suart_puts("\r\n=== NEO-6M QUALITY FILTER + AVERAGING ===\r\n");
    suart_puts("Filter: fixq>=1, sats>=6, hdop<=2.50\r\n");
    suart_puts("Averaging: ");
    suart_putc((char)('0' + (AVG_N / 10)));
    suart_putc((char)('0' + (AVG_N % 10)));
    suart_puts(" samples\r\n\r\n");

    avg_reset();

    while (1)
    {
        gps_read_line(line, (unsigned int)sizeof(line));
        if (!nmea_checksum_ok(line)) continue;

        /* Keep quality updated from GGA */
        if (!strncmp(line, "$GPGGA", 6) || !strncmp(line, "$GNGGA", 6)) {
            handle_gga(line);
            // If quality drops, reset averaging so we don't mix bad with good
            if (!quality_ok()) avg_reset();
            continue;
        }

        /* Use only RMC for coordinates */
        if (strncmp(line, "$GPRMC", 6) && strncmp(line, "$GNRMC", 6)) continue;

        // Copy into work (split modifies)
        strncpy(work, line, sizeof(work) - 1);
        work[sizeof(work) - 1] = 0;

        uint8_t nf = split_csv(work, fld, 20);
        if (nf < 7) continue;

        // status must be A
        if (!fld[2] || fld[2][0] != 'A') {
            avg_reset();
            continue;
        }

        // Must pass quality gate
        if (!quality_ok()) {
            // Optional: show why occasionally
            // suart_puts("Waiting: need GGA good fix...\r\n");
            avg_reset();
            continue;
        }

        int32_t lat = 0, lon = 0;
        if (!coord_to_microdeg(fld[3], 1, &lat)) continue;
        if (fld[4] && fld[4][0] == 'S') lat = -lat;

        if (!coord_to_microdeg(fld[5], 0, &lon)) continue;
        if (fld[6] && fld[6][0] == 'W') lon = -lon;

        // Add to average
        avg_add(lat, lon);

        // When enough good samples, print averaged location
        if (avg_ready()) {
            avg_print();
        }
    }
}

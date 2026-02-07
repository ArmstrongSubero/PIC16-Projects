/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 63_Joystick
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.1
 *                  * Added auto-calibration at startup
 *
 * Program Description: This program reads a 2-axis analog joystick using the
 *                      ADC module and displays X/Y position plus direction
 *                      on an SSD1306 OLED display.
 *
 * Hardware Description: Joystick VRx connected to AN0 (RA0)
 *                       Joystick VRy connected to AN1 (RA1)
 *                       Joystick SW (button) connected to RB0 (digital input)
 *                       SSD1306 OLED on I2C bus (RC4/RC5)
 *
 * Created February 7th, 2026, 4:33 P< 
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"
#include "ADC.h"

// Joystick calibration
#define JOY_DEADZONE    80     // Dead zone threshold around center
#define JOY_MIN         0
#define JOY_MAX         1023

// Joystick direction flags
#define JOY_DIR_CENTER  0x00
#define JOY_DIR_UP      0x01
#define JOY_DIR_DOWN    0x02
#define JOY_DIR_LEFT    0x04
#define JOY_DIR_RIGHT   0x08

// Joystick button
#define JOY_BTN_PORT    PORTBbits.RB0
#define JOY_BTN_TRIS    TRISBbits.TRISB0
#define JOY_BTN_ANSEL   ANSELBbits.ANSB0

/*******************************************************************************
 * Joystick data structure
 ******************************************************************************/
typedef struct {
    uint16_t raw_x;        // Raw ADC value for X axis (0-1023)
    uint16_t raw_y;        // Raw ADC value for Y axis (0-1023)
    int16_t  x;            // Centered X value
    int16_t  y;            // Centered Y value
    uint8_t  direction;    // Direction bitmask
    uint8_t  button;       // Button state (1 = pressed)
} joystick_t;

/*******************************************************************************
 * Calibration variables (actual center readings from joystick at rest)
 ******************************************************************************/
static uint16_t joy_center_x = 512;
static uint16_t joy_center_y = 512;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void initMain(void);
void Joystick_Init(void);
void Joystick_Calibrate(void);
void Joystick_Read(joystick_t *joy);
uint8_t Joystick_GetDirection(joystick_t *joy);
const char* Joystick_DirectionString(uint8_t direction);

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 ******************************************************************************/
void initMain(){

    // Run at 32 MHz
    internal_32();

    // Allow PLL startup time ~2 ms
    __delay_ms(10);

    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;

    /////////////////////
    // Setup I2C
    ////////////////////

    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;
    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS   = 0x0B;
    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;
    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;

    ////////////////////
    // Configure ADC
    ///////////////////

    // Fosc/32 ADC conversion time is 1.0 us
    ADCON1bits.ADCS = 0b010;

    // Right justified
    ADCON1bits.ADFM = 1;

    // Vref- is Vss
    ADCON1bits.ADNREF = 0;

    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;

    // Configure ADC pins for joystick axes
    ADC_ConfigurePin(ADC_AN0);  // X axis
    ADC_ConfigurePin(ADC_AN1);  // Y axis
}

/*******************************************************************************
 * Function: void Joystick_Init(void)
 *
 * Returns: Nothing
 *
 * Description: Initializes joystick button pin as digital input with pull-up
 ******************************************************************************/
void Joystick_Init(void)
{
    // Configure button pin as digital input
    JOY_BTN_TRIS  = 1;   // Input
    JOY_BTN_ANSEL = 0;   // Digital

    // Enable weak pull-up on RB0 for button (active low)
    OPTION_REGbits.nWPUEN = 0;  // Enable global weak pull-ups
    WPUBbits.WPUB0 = 1;        // Enable pull-up on RB0
}

/*******************************************************************************
 * Function: void Joystick_Calibrate(void)
 *
 * Returns: Nothing
 *
 * Description: Reads joystick at rest to determine actual center position.
 *              Call this at startup with joystick untouched.
 ******************************************************************************/
void Joystick_Calibrate(void)
{
    // Average many samples for a stable center reading
    joy_center_x = ADC_Read_Averaged(ADC_AN0, 16);
    joy_center_y = ADC_Read_Averaged(ADC_AN1, 16);
}

/*******************************************************************************
 * Function: void Joystick_Read(joystick_t *joy)
 *
 * Returns: Nothing
 *
 * Description: Reads joystick X/Y axes and button, populates joystick struct
 ******************************************************************************/
void Joystick_Read(joystick_t *joy)
{
    // Read raw ADC values (averaged over 8 samples for stability)
    joy->raw_x = ADC_Read_Averaged(ADC_AN0, 8);
    joy->raw_y = ADC_Read_Averaged(ADC_AN1, 8);

    // Convert to centered signed values using calibrated center
    joy->x = (int16_t)joy->raw_x - (int16_t)joy_center_x;
    joy->y = (int16_t)joy->raw_y - (int16_t)joy_center_y;

    // Read button (active low with pull-up)
    joy->button = (JOY_BTN_PORT == 0) ? 1 : 0;

    // Determine direction
    joy->direction = Joystick_GetDirection(joy);
}

/*******************************************************************************
 * Function: uint8_t Joystick_GetDirection(joystick_t *joy)
 *
 * Returns: Direction bitmask (can be combined for diagonals)
 *
 * Description: Determines joystick direction with dead zone filtering
 ******************************************************************************/
uint8_t Joystick_GetDirection(joystick_t *joy)
{
    uint8_t dir = JOY_DIR_CENTER;

    // X axis: positive = RIGHT, negative = LEFT
    if (joy->x > JOY_DEADZONE)
        dir |= JOY_DIR_RIGHT;
    else if (joy->x < -JOY_DEADZONE)
        dir |= JOY_DIR_LEFT;

    // Y axis: positive = DOWN, negative = UP
    if (joy->y > JOY_DEADZONE)
        dir |= JOY_DIR_DOWN;
    else if (joy->y < -JOY_DEADZONE)
        dir |= JOY_DIR_UP;

    return dir;
}

/*******************************************************************************
 * Function: const char* Joystick_DirectionString(uint8_t direction)
 *
 * Returns: String representation of direction
 *
 * Description: Converts direction bitmask to human-readable string
 ******************************************************************************/
const char* Joystick_DirectionString(uint8_t direction)
{
    switch(direction)
    {
        case JOY_DIR_UP:                          return "UP      ";
        case JOY_DIR_DOWN:                        return "DOWN    ";
        case JOY_DIR_LEFT:                        return "LEFT    ";
        case JOY_DIR_RIGHT:                       return "RIGHT   ";
        case (JOY_DIR_UP | JOY_DIR_LEFT):         return "UP-LEFT ";
        case (JOY_DIR_UP | JOY_DIR_RIGHT):        return "UP-RIGHT";
        case (JOY_DIR_DOWN | JOY_DIR_LEFT):       return "DN-LEFT ";
        case (JOY_DIR_DOWN | JOY_DIR_RIGHT):      return "DN-RIGHT";
        default:                                  return "CENTER  ";
    }
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
    I2C_Init();

    OLED_Init();
    OLED_SetOrientation(OLED_ORIENT_0);
    OLED_Clear();

    ADC_Init();
    Joystick_Init();

    // Calibrate center - don't touch joystick during startup
    OLED_Printf_Line(0, "Calibrating...");
    OLED_Printf_Line(1, "Don't touch joy");
    __delay_ms(1000);
    Joystick_Calibrate();
    OLED_Clear();

    joystick_t joy;

    while (1)
    {
        Joystick_Read(&joy);

        // Display joystick data on OLED
        OLED_Printf_Line(0, "X:%4d  Y:%4d", joy.x, joy.y);
        OLED_Printf_Line(1, "Dir: %s", Joystick_DirectionString(joy.direction));
        OLED_Printf_Line(2, "Btn: %s", joy.button ? "PRESSED" : "---    ");
        OLED_Printf_Line(3, "RX:%4u RY:%4u", joy.raw_x, joy.raw_y);

        __delay_ms(100);
    }
}
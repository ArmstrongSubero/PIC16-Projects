#include "PIC16F1718_Internal.h"
#include "buzzer.h"

/*******************************************************************************
 * Display wiring
 * Segments: PORTC (LATC)
 * Digit enables: RB1..RB4 (RB0 reserved for buzzer PWM)
 ******************************************************************************/
#define DIG_MASK0 0b00000010u   // RB1 (rightmost: hundredths ones)
#define DIG_MASK1 0b00000100u   // RB2 (hundredths tens)
#define DIG_MASK2 0b00001000u   // RB3 (seconds ones)
#define DIG_MASK3 0b00010000u   // RB4 (seconds tens)
static const uint8_t digit_mask[4] = { DIG_MASK0, DIG_MASK1, DIG_MASK2, DIG_MASK3 };

#define BTN_START PORTAbits.RA0
#define BTN_INC   PORTAbits.RA1
#define BTN_DEC   PORTAbits.RA2

/*******************************************************************************
 * Globals used by ISR
 ******************************************************************************/
volatile uint8_t  digits[4]   = {0,0,0,0};
volatile uint8_t  scan_idx    = 0;

volatile uint32_t total_cs    = 2000;   // 10.00 seconds default (centiseconds)
volatile uint8_t  tick10ms    = 0;      // set by Timer1 ISR

/*******************************************************************************
 * 7-seg decode (0..9)
 ******************************************************************************/
static inline uint8_t seg(uint8_t num)
{
    switch(num)
    {
        case 0: return 0x3F;
        case 1: return 0x06;
        case 2: return 0x5B;
        case 3: return 0x4F;
        case 4: return 0x66;
        case 5: return 0x6D;
        case 6: return 0x7D;
        case 7: return 0x07;
        case 8: return 0x7F;
        case 9: return 0x6F;
        default: return 0x00;
    }
}

/*******************************************************************************
 * SS.tt update (centiseconds)
 ******************************************************************************/
static void updateDigits_SS_tt(uint32_t cs)
{
    uint32_t seconds = cs / 100;      // 0..99
    uint32_t hund    = cs % 100;      // 0..99

    uint8_t sec_tens = (uint8_t)((seconds / 10) % 10);
    uint8_t sec_ones = (uint8_t)(seconds % 10);
    uint8_t hun_tens = (uint8_t)((hund / 10) % 10);
    uint8_t hun_ones = (uint8_t)(hund % 10);

    // left->right: sec_tens sec_ones hun_tens hun_ones
    digits[3] = sec_tens;
    digits[2] = sec_ones;
    digits[1] = hun_tens;
    digits[0] = hun_ones;
}

/*******************************************************************************
 * Button helpers (ACTIVE-LOW)
 ******************************************************************************/
typedef struct
{
    uint8_t  prev;         // previous raw pin state
    uint16_t hold_ms;      // how long held (ms)
    uint16_t repeat_ms;    // accumulator for repeat timing (ms)
    uint8_t  fired_hold;   // whether we've started repeating
} hold_btn_t;

static uint8_t pressed_edge_active_low(uint8_t now, uint8_t *prev)
{
    uint8_t hit = ((*prev == 1) && (now == 0)) ? 1 : 0;
    *prev = now;
    return hit;
}

static uint16_t accel_interval_ms(uint16_t hold_ms)
{
    if(hold_ms < 800)   return 200;  // slow
    if(hold_ms < 1600)  return 120;  // faster
    if(hold_ms < 3000)  return 70;   // fast
    return 40;                      // very fast
}

static uint8_t hold_button_action(uint8_t pin_now, hold_btn_t *b, uint16_t tick_ms)
{
    if(pressed_edge_active_low(pin_now, &b->prev))
    {
        b->hold_ms = 0;
        b->repeat_ms = 0;
        b->fired_hold = 0;
        return 1; // tap
    }

    if(pin_now == 0)
    {
        b->hold_ms += tick_ms;

        if(b->hold_ms >= 450)
        {
            b->repeat_ms += tick_ms;
            uint16_t interval = accel_interval_ms(b->hold_ms);

            if(b->repeat_ms >= interval)
            {
                b->repeat_ms = 0;
                b->fired_hold = 1;
                return 1; // repeat
            }
        }
    }
    else
    {
        b->hold_ms = 0;
        b->repeat_ms = 0;
        b->fired_hold = 0;
    }

    return 0;
}

/*******************************************************************************
 * Cinematic beep scheduler (non-blocking, ticked every 10ms)
 ******************************************************************************/
typedef struct {
    uint8_t  enabled;
    uint16_t accum_ms;
    uint16_t on_accum_ms;
    uint16_t interval_ms;
    uint16_t on_ms;
    uint8_t  on;
    uint32_t freq;
    uint8_t  vol;
} beep_t;

static beep_t beep;

static uint16_t movie_interval_ms(uint32_t cs_remaining)
{
    uint32_t s = cs_remaining / 100;
    if(s >= 60) return 700;
    if(s >= 30) return 550;
    if(s >= 15) return 420;
    if(s >= 8)  return 320;
    if(s >= 4)  return 240;
    if(s >= 2)  return 170;
    return 120;
}

static void movie_params(uint32_t cs_remaining, uint32_t *freq, uint8_t *vol, uint16_t *on_ms)
{
    uint32_t s = cs_remaining / 100;

    if(s >= 30) { *freq = 2100; *vol = 50;  *on_ms = 35; return; }
    if(s >= 15) { *freq = 2300; *vol = 60;  *on_ms = 35; return; }
    if(s >= 8)  { *freq = 2500; *vol = 72;  *on_ms = 38; return; }
    if(s >= 4)  { *freq = 2900; *vol = 85;  *on_ms = 42; return; }
    if(s >= 2)  { *freq = 3300; *vol = 95;  *on_ms = 48; return; }
    *freq = 3800; *vol = 100; *on_ms = 55;
}

static void Beep_Reset(void)
{
    beep.enabled = 0;
    beep.accum_ms = 0;
    beep.on_accum_ms = 0;
    beep.on = 0;
    Buzzer_Stop();
}

static void Beep_Tick10ms(uint32_t cs_remaining)
{
    if(!beep.enabled || cs_remaining == 0) {
        Beep_Reset();
        return;
    }

    beep.interval_ms = movie_interval_ms(cs_remaining);
    movie_params(cs_remaining, &beep.freq, &beep.vol, &beep.on_ms);

    if(beep.on) {
        beep.on_accum_ms += 10;
        if(beep.on_accum_ms >= beep.on_ms) {
            beep.on = 0;
            beep.on_accum_ms = 0;
            Buzzer_Stop();
        }
    }

    beep.accum_ms += 10;
    if(beep.accum_ms >= beep.interval_ms) {
        beep.accum_ms = 0;
        Buzzer_Set(beep.freq, beep.vol);
        beep.on = 1;
        beep.on_accum_ms = 0;
    }
}

/*******************************************************************************
 * Timer2: display scan (fast enough to hide scanning)
 * Fosc=32MHz => Finst=8MHz
 * Prescale 16 => 500kHz tick
 * PR2=39 => 12.5kHz ISR => 3.125kHz per digit
 ******************************************************************************/
static void Timer2_Init_DisplayScan(void)
{
    T2CONbits.T2CKPS  = 0b10;   // prescale 16
    T2CONbits.T2OUTPS = 0b0000; // postscale 1
    PR2 = 39;
    TMR2 = 0;

    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;

    T2CONbits.TMR2ON = 1;
}

/*******************************************************************************
 * Timer1: 10ms system tick
 * Finst=8MHz, prescale 1:8 => 1MHz tick (1us/count)
 * 10ms => 10,000 counts
 * preload = 65536 - 10000 = 0xD8F0
 ******************************************************************************/
static void Timer1_Init_Tick10ms(void)
{
    T1CONbits.TMR1CS  = 0;
    T1CONbits.T1CKPS  = 0b11;   // 1:8
    T1CONbits.T1OSCEN = 0;

    TMR1H = 0xD8;
    TMR1L = 0xF0;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    T1CONbits.TMR1ON = 1;
}

/*******************************************************************************
 * init
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;

    // Segments
    TRISC = 0x00;
    LATC  = 0x00;

    // Digit enables RB1..RB4
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;

    // digits off RB1..RB4
    LATB &= 0b11100001;

    // Buttons
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;

    // Buzzer
    Buzzer_Init();
    Buzzer_Stop();
    
    // LED 
    TRISAbits.TRISA5 = 0;
    LATAbits.LATA5 = 0; 

    di(); updateDigits_SS_tt(total_cs); ei();

    Timer2_Init_DisplayScan();
    Timer1_Init_Tick10ms();

    INTCONbits.PEIE = 1;
    ei();
}

/*******************************************************************************
 * ISR: Timer2 = scan, Timer1 = 10ms tick
 ******************************************************************************/
void __interrupt() isr(void)
{
    // Timer2 display scan
    if(PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;

        // RB1..RB4 off
        LATB &= 0b11100001;

        // segments
        LATC = seg(digits[scan_idx]);

        // enable digit
        LATB |= digit_mask[scan_idx];

        scan_idx = (scan_idx + 1) & 0x03;
    }

    // Timer1 10ms tick
    if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;

        TMR1H = 0xD8;
        TMR1L = 0xF0;

        tick10ms = 1;
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();

    uint8_t running = 0;
    uint8_t prev_start = 1;

    hold_btn_t incBtn = { .prev = 1, .hold_ms = 0, .repeat_ms = 0, .fired_hold = 0 };
    hold_btn_t decBtn = { .prev = 1, .hold_ms = 0, .repeat_ms = 0, .fired_hold = 0 };

    Beep_Reset();

    while(1)
    {
        if(!tick10ms) continue;
        tick10ms = 0;

        // START/STOP toggle on press edge (exactly like your example)
        if(pressed_edge_active_low(BTN_START, &prev_start))
        {
            running = !running;

            if(running) {
                beep.enabled = 1;
                beep.accum_ms = 0;
                beep.on = 0;
                Buzzer_Stop();
            } else {
                Beep_Reset();
            }
        }

        // INC/DEC tap+hold accel 
        // Only allow when stopped, to set time cleanly
        if(!running)
        {
            if(hold_button_action(BTN_INC, &incBtn, 10))
            {
                // +1 second
                if(total_cs <= 9899) total_cs += 100;
                else total_cs = 9999;
            }

            if(hold_button_action(BTN_DEC, &decBtn, 10))
            {
                // -1 second
                if(total_cs >= 100) total_cs -= 100;
                else total_cs = 0;
            }
        }
        else
        {
            // optional: keep hold state clean while running
            incBtn.hold_ms = incBtn.repeat_ms = 0;
            decBtn.hold_ms = decBtn.repeat_ms = 0;
        }

        // Countdown in 10ms steps
        if(running)
        {
            if(total_cs > 0) total_cs--;
            else
            {
                running = 0;
                Beep_Reset();

                // final alarm (short block OK; scan still runs via Timer2)
                Buzzer_Set(3600, 100);
                __delay_ms(500);
                Buzzer_Stop();
                
                LATAbits.LATA5 = 1;
            }

            Beep_Tick10ms(total_cs);
        }

        // update digits atomically
        di();
        updateDigits_SS_tt(total_cs);
        ei();
    }
}

# 1 "main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main.c" 2
# 28 "main.c"
# 1 "./PIC16F1719_Internal.h" 1
# 24 "./PIC16F1719_Internal.h"
#pragma config FOSC = INTOSC
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config CLKOUTEN = OFF
#pragma config IESO = ON
#pragma config FCMEN = OFF


#pragma config WRT = OFF
#pragma config PPS1WAY = ON
#pragma config ZCDDIS = ON
#pragma config PLLEN = OFF
#pragma config STVREN = ON
#pragma config BORV = LO
#pragma config LPBOR = OFF
#pragma config LVP = OFF



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 3
extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\xc8debug.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 2 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 128 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 174 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);

long long atoll (const char *);

double atof (const char *);


float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);

long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);


unsigned long __strtoxl(const char * s, char ** endptr, int base, char is_signed);

unsigned long long __strtoxll(const char * s, char ** endptr, int base, char is_signed);
# 55 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdlib.h" 3
int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);

long long llabs (long long);


typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

typedef struct { long long quot, rem; } lldiv_t;


div_t div (int, int);
ldiv_t ldiv (long, long);

lldiv_t lldiv (long long, long long);


typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\xc8debug.h" 2 3







#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);
# 23 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 2 3

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\builtins.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdint.h" 1 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef short intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 179 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 215 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdint.h" 2 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\builtins.h" 2 3



#pragma intrinsic(__nop)
extern void __nop(void);
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\builtins.h" 3
#pragma intrinsic(_delay)
extern __attribute__((nonreentrant)) void _delay(uint32_t);
#pragma intrinsic(_delaywdt)
extern __attribute__((nonreentrant)) void _delaywdt(uint32_t);

#pragma intrinsic(_delay3)
extern __attribute__((nonreentrant)) void _delay3(uint8_t);
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 2 3




# 1 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 1 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\htc.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\htc.h" 2 3
# 6 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 2 3







# 1 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic_chip_select.h" 1 3
# 284 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic_chip_select.h" 3
# 1 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 1 3
# 44 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\__at.h" 1 3
# 45 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 2 3







extern volatile unsigned char INDF0 __attribute__((address(0x000)));

__asm("INDF0 equ 00h");


typedef union {
    struct {
        unsigned INDF0 :8;
    };
} INDF0bits_t;
extern volatile INDF0bits_t INDF0bits __attribute__((address(0x000)));
# 72 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INDF1 __attribute__((address(0x001)));

__asm("INDF1 equ 01h");


typedef union {
    struct {
        unsigned INDF1 :8;
    };
} INDF1bits_t;
extern volatile INDF1bits_t INDF1bits __attribute__((address(0x001)));
# 92 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PCL __attribute__((address(0x002)));

__asm("PCL equ 02h");


typedef union {
    struct {
        unsigned PCL :8;
    };
} PCLbits_t;
extern volatile PCLbits_t PCLbits __attribute__((address(0x002)));
# 112 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char STATUS __attribute__((address(0x003)));

__asm("STATUS equ 03h");


typedef union {
    struct {
        unsigned C :1;
        unsigned DC :1;
        unsigned Z :1;
        unsigned nPD :1;
        unsigned nTO :1;
    };
    struct {
        unsigned CARRY :1;
        unsigned :1;
        unsigned ZERO :1;
    };
} STATUSbits_t;
extern volatile STATUSbits_t STATUSbits __attribute__((address(0x003)));
# 171 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short FSR0 __attribute__((address(0x004)));



extern volatile unsigned char FSR0L __attribute__((address(0x004)));

__asm("FSR0L equ 04h");


typedef union {
    struct {
        unsigned FSR0L :8;
    };
} FSR0Lbits_t;
extern volatile FSR0Lbits_t FSR0Lbits __attribute__((address(0x004)));
# 195 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR0H __attribute__((address(0x005)));

__asm("FSR0H equ 05h");


typedef union {
    struct {
        unsigned FSR0H :8;
    };
} FSR0Hbits_t;
extern volatile FSR0Hbits_t FSR0Hbits __attribute__((address(0x005)));
# 215 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short FSR1 __attribute__((address(0x006)));



extern volatile unsigned char FSR1L __attribute__((address(0x006)));

__asm("FSR1L equ 06h");


typedef union {
    struct {
        unsigned FSR1L :8;
    };
} FSR1Lbits_t;
extern volatile FSR1Lbits_t FSR1Lbits __attribute__((address(0x006)));
# 239 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR1H __attribute__((address(0x007)));

__asm("FSR1H equ 07h");


typedef union {
    struct {
        unsigned FSR1H :8;
    };
} FSR1Hbits_t;
extern volatile FSR1Hbits_t FSR1Hbits __attribute__((address(0x007)));
# 259 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char BSR __attribute__((address(0x008)));

__asm("BSR equ 08h");


typedef union {
    struct {
        unsigned BSR :5;
    };
    struct {
        unsigned BSR0 :1;
        unsigned BSR1 :1;
        unsigned BSR2 :1;
        unsigned BSR3 :1;
        unsigned BSR4 :1;
    };
} BSRbits_t;
extern volatile BSRbits_t BSRbits __attribute__((address(0x008)));
# 311 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WREG __attribute__((address(0x009)));

__asm("WREG equ 09h");


typedef union {
    struct {
        unsigned WREG0 :8;
    };
} WREGbits_t;
extern volatile WREGbits_t WREGbits __attribute__((address(0x009)));
# 331 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PCLATH __attribute__((address(0x00A)));

__asm("PCLATH equ 0Ah");


typedef union {
    struct {
        unsigned PCLATH :7;
    };
} PCLATHbits_t;
extern volatile PCLATHbits_t PCLATHbits __attribute__((address(0x00A)));
# 351 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INTCON __attribute__((address(0x00B)));

__asm("INTCON equ 0Bh");


typedef union {
    struct {
        unsigned IOCIF :1;
        unsigned INTF :1;
        unsigned TMR0IF :1;
        unsigned IOCIE :1;
        unsigned INTE :1;
        unsigned TMR0IE :1;
        unsigned PEIE :1;
        unsigned GIE :1;
    };
    struct {
        unsigned :2;
        unsigned T0IF :1;
        unsigned :2;
        unsigned T0IE :1;
    };
} INTCONbits_t;
extern volatile INTCONbits_t INTCONbits __attribute__((address(0x00B)));
# 429 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PORTA __attribute__((address(0x00C)));

__asm("PORTA equ 0Ch");


typedef union {
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
        unsigned RA6 :1;
        unsigned RA7 :1;
    };
} PORTAbits_t;
extern volatile PORTAbits_t PORTAbits __attribute__((address(0x00C)));
# 491 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PORTB __attribute__((address(0x00D)));

__asm("PORTB equ 0Dh");


typedef union {
    struct {
        unsigned RB0 :1;
        unsigned RB1 :1;
        unsigned RB2 :1;
        unsigned RB3 :1;
        unsigned RB4 :1;
        unsigned RB5 :1;
        unsigned RB6 :1;
        unsigned RB7 :1;
    };
} PORTBbits_t;
extern volatile PORTBbits_t PORTBbits __attribute__((address(0x00D)));
# 553 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PORTC __attribute__((address(0x00E)));

__asm("PORTC equ 0Eh");


typedef union {
    struct {
        unsigned RC0 :1;
        unsigned RC1 :1;
        unsigned RC2 :1;
        unsigned RC3 :1;
        unsigned RC4 :1;
        unsigned RC5 :1;
        unsigned RC6 :1;
        unsigned RC7 :1;
    };
} PORTCbits_t;
extern volatile PORTCbits_t PORTCbits __attribute__((address(0x00E)));
# 615 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PORTD __attribute__((address(0x00F)));

__asm("PORTD equ 0Fh");


typedef union {
    struct {
        unsigned RD0 :1;
        unsigned RD1 :1;
        unsigned RD2 :1;
        unsigned RD3 :1;
        unsigned RD4 :1;
        unsigned RD5 :1;
        unsigned RD6 :1;
        unsigned RD7 :1;
    };
} PORTDbits_t;
extern volatile PORTDbits_t PORTDbits __attribute__((address(0x00F)));
# 677 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PORTE __attribute__((address(0x010)));

__asm("PORTE equ 010h");


typedef union {
    struct {
        unsigned RE0 :1;
        unsigned RE1 :1;
        unsigned RE2 :1;
        unsigned RE3 :1;
    };
} PORTEbits_t;
extern volatile PORTEbits_t PORTEbits __attribute__((address(0x010)));
# 715 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIR1 __attribute__((address(0x011)));

__asm("PIR1 equ 011h");


typedef union {
    struct {
        unsigned TMR1IF :1;
        unsigned TMR2IF :1;
        unsigned CCP1IF :1;
        unsigned SSP1IF :1;
        unsigned TXIF :1;
        unsigned RCIF :1;
        unsigned ADIF :1;
        unsigned TMR1GIF :1;
    };
} PIR1bits_t;
extern volatile PIR1bits_t PIR1bits __attribute__((address(0x011)));
# 777 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIR2 __attribute__((address(0x012)));

__asm("PIR2 equ 012h");


typedef union {
    struct {
        unsigned CCP2IF :1;
        unsigned TMR4IF :1;
        unsigned TMR6IF :1;
        unsigned BCL1IF :1;
        unsigned :1;
        unsigned C1IF :1;
        unsigned C2IF :1;
        unsigned OSFIF :1;
    };
} PIR2bits_t;
extern volatile PIR2bits_t PIR2bits __attribute__((address(0x012)));
# 834 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIR3 __attribute__((address(0x013)));

__asm("PIR3 equ 013h");


typedef union {
    struct {
        unsigned CLC1IF :1;
        unsigned CLC2IF :1;
        unsigned CLC3IF :1;
        unsigned CLC4IF :1;
        unsigned ZCDIF :1;
        unsigned COGIF :1;
        unsigned NCOIF :1;
    };
} PIR3bits_t;
extern volatile PIR3bits_t PIR3bits __attribute__((address(0x013)));
# 890 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TMR0 __attribute__((address(0x015)));

__asm("TMR0 equ 015h");


typedef union {
    struct {
        unsigned TMR0 :8;
    };
} TMR0bits_t;
extern volatile TMR0bits_t TMR0bits __attribute__((address(0x015)));
# 910 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short TMR1 __attribute__((address(0x016)));

__asm("TMR1 equ 016h");




extern volatile unsigned char TMR1L __attribute__((address(0x016)));

__asm("TMR1L equ 016h");


typedef union {
    struct {
        unsigned TMR1L :8;
    };
} TMR1Lbits_t;
extern volatile TMR1Lbits_t TMR1Lbits __attribute__((address(0x016)));
# 937 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TMR1H __attribute__((address(0x017)));

__asm("TMR1H equ 017h");


typedef union {
    struct {
        unsigned TMR1H :8;
    };
} TMR1Hbits_t;
extern volatile TMR1Hbits_t TMR1Hbits __attribute__((address(0x017)));
# 957 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T1CON __attribute__((address(0x018)));

__asm("T1CON equ 018h");


typedef union {
    struct {
        unsigned TMR1ON :1;
        unsigned :1;
        unsigned nT1SYNC :1;
        unsigned T1OSCEN :1;
        unsigned T1CKPS :2;
        unsigned TMR1CS :2;
    };
    struct {
        unsigned :4;
        unsigned T1CKPS0 :1;
        unsigned T1CKPS1 :1;
        unsigned TMR1CS0 :1;
        unsigned TMR1CS1 :1;
    };
} T1CONbits_t;
extern volatile T1CONbits_t T1CONbits __attribute__((address(0x018)));
# 1029 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T1GCON __attribute__((address(0x019)));

__asm("T1GCON equ 019h");


typedef union {
    struct {
        unsigned T1GSS :2;
        unsigned T1GVAL :1;
        unsigned T1GGO_nDONE :1;
        unsigned T1GSPM :1;
        unsigned T1GTM :1;
        unsigned T1GPOL :1;
        unsigned TMR1GE :1;
    };
    struct {
        unsigned T1GSS0 :1;
        unsigned T1GSS1 :1;
    };
} T1GCONbits_t;
extern volatile T1GCONbits_t T1GCONbits __attribute__((address(0x019)));
# 1099 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TMR2 __attribute__((address(0x01A)));

__asm("TMR2 equ 01Ah");


typedef union {
    struct {
        unsigned TMR2 :8;
    };
} TMR2bits_t;
extern volatile TMR2bits_t TMR2bits __attribute__((address(0x01A)));
# 1119 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PR2 __attribute__((address(0x01B)));

__asm("PR2 equ 01Bh");


typedef union {
    struct {
        unsigned PR2 :8;
    };
} PR2bits_t;
extern volatile PR2bits_t PR2bits __attribute__((address(0x01B)));
# 1139 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T2CON __attribute__((address(0x01C)));

__asm("T2CON equ 01Ch");


typedef union {
    struct {
        unsigned T2CKPS :2;
        unsigned TMR2ON :1;
        unsigned T2OUTPS :4;
    };
    struct {
        unsigned T2CKPS0 :1;
        unsigned T2CKPS1 :1;
        unsigned :1;
        unsigned T2OUTPS0 :1;
        unsigned T2OUTPS1 :1;
        unsigned T2OUTPS2 :1;
        unsigned T2OUTPS3 :1;
    };
} T2CONbits_t;
extern volatile T2CONbits_t T2CONbits __attribute__((address(0x01C)));
# 1210 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TRISA __attribute__((address(0x08C)));

__asm("TRISA equ 08Ch");


typedef union {
    struct {
        unsigned TRISA0 :1;
        unsigned TRISA1 :1;
        unsigned TRISA2 :1;
        unsigned TRISA3 :1;
        unsigned TRISA4 :1;
        unsigned TRISA5 :1;
        unsigned TRISA6 :1;
        unsigned TRISA7 :1;
    };
} TRISAbits_t;
extern volatile TRISAbits_t TRISAbits __attribute__((address(0x08C)));
# 1272 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TRISB __attribute__((address(0x08D)));

__asm("TRISB equ 08Dh");


typedef union {
    struct {
        unsigned TRISB0 :1;
        unsigned TRISB1 :1;
        unsigned TRISB2 :1;
        unsigned TRISB3 :1;
        unsigned TRISB4 :1;
        unsigned TRISB5 :1;
        unsigned TRISB6 :1;
        unsigned TRISB7 :1;
    };
} TRISBbits_t;
extern volatile TRISBbits_t TRISBbits __attribute__((address(0x08D)));
# 1334 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TRISC __attribute__((address(0x08E)));

__asm("TRISC equ 08Eh");


typedef union {
    struct {
        unsigned TRISC0 :1;
        unsigned TRISC1 :1;
        unsigned TRISC2 :1;
        unsigned TRISC3 :1;
        unsigned TRISC4 :1;
        unsigned TRISC5 :1;
        unsigned TRISC6 :1;
        unsigned TRISC7 :1;
    };
} TRISCbits_t;
extern volatile TRISCbits_t TRISCbits __attribute__((address(0x08E)));
# 1396 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TRISD __attribute__((address(0x08F)));

__asm("TRISD equ 08Fh");


typedef union {
    struct {
        unsigned TRISD0 :1;
        unsigned TRISD1 :1;
        unsigned TRISD2 :1;
        unsigned TRISD3 :1;
        unsigned TRISD4 :1;
        unsigned TRISD5 :1;
        unsigned TRISD6 :1;
        unsigned TRISD7 :1;
    };
} TRISDbits_t;
extern volatile TRISDbits_t TRISDbits __attribute__((address(0x08F)));
# 1458 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TRISE __attribute__((address(0x090)));

__asm("TRISE equ 090h");


typedef union {
    struct {
        unsigned TRISE0 :1;
        unsigned TRISE1 :1;
        unsigned TRISE2 :1;
        unsigned TRISE3 :1;
    };
} TRISEbits_t;
extern volatile TRISEbits_t TRISEbits __attribute__((address(0x090)));
# 1496 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIE1 __attribute__((address(0x091)));

__asm("PIE1 equ 091h");


typedef union {
    struct {
        unsigned TMR1IE :1;
        unsigned TMR2IE :1;
        unsigned CCP1IE :1;
        unsigned SSP1IE :1;
        unsigned TXIE :1;
        unsigned RCIE :1;
        unsigned ADIE :1;
        unsigned TMR1GIE :1;
    };
} PIE1bits_t;
extern volatile PIE1bits_t PIE1bits __attribute__((address(0x091)));
# 1558 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIE2 __attribute__((address(0x092)));

__asm("PIE2 equ 092h");


typedef union {
    struct {
        unsigned CCP2IE :1;
        unsigned TMR4IE :1;
        unsigned TMR6IE :1;
        unsigned BCL1IE :1;
        unsigned :1;
        unsigned C1IE :1;
        unsigned C2IE :1;
        unsigned OSFIE :1;
    };
} PIE2bits_t;
extern volatile PIE2bits_t PIE2bits __attribute__((address(0x092)));
# 1615 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PIE3 __attribute__((address(0x093)));

__asm("PIE3 equ 093h");


typedef union {
    struct {
        unsigned CLC1IE :1;
        unsigned CLC2IE :1;
        unsigned CLC3IE :1;
        unsigned CLC4IE :1;
        unsigned ZCDIE :1;
        unsigned COGIE :1;
        unsigned NCOIE :1;
    };
} PIE3bits_t;
extern volatile PIE3bits_t PIE3bits __attribute__((address(0x093)));
# 1671 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OPTION_REG __attribute__((address(0x095)));

__asm("OPTION_REG equ 095h");


typedef union {
    struct {
        unsigned PS :3;
        unsigned PSA :1;
        unsigned TMR0SE :1;
        unsigned TMR0CS :1;
        unsigned INTEDG :1;
        unsigned nWPUEN :1;
    };
    struct {
        unsigned PS0 :1;
        unsigned PS1 :1;
        unsigned PS2 :1;
        unsigned :1;
        unsigned T0SE :1;
        unsigned T0CS :1;
    };
} OPTION_REGbits_t;
extern volatile OPTION_REGbits_t OPTION_REGbits __attribute__((address(0x095)));
# 1754 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PCON __attribute__((address(0x096)));

__asm("PCON equ 096h");


typedef union {
    struct {
        unsigned nBOR :1;
        unsigned nPOR :1;
        unsigned nRI :1;
        unsigned nRMCLR :1;
        unsigned nRWDT :1;
        unsigned :1;
        unsigned STKUNF :1;
        unsigned STKOVF :1;
    };
} PCONbits_t;
extern volatile PCONbits_t PCONbits __attribute__((address(0x096)));
# 1811 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WDTCON __attribute__((address(0x097)));

__asm("WDTCON equ 097h");


typedef union {
    struct {
        unsigned SWDTEN :1;
        unsigned WDTPS :5;
    };
    struct {
        unsigned :1;
        unsigned WDTPS0 :1;
        unsigned WDTPS1 :1;
        unsigned WDTPS2 :1;
        unsigned WDTPS3 :1;
        unsigned WDTPS4 :1;
    };
} WDTCONbits_t;
extern volatile WDTCONbits_t WDTCONbits __attribute__((address(0x097)));
# 1870 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OSCTUNE __attribute__((address(0x098)));

__asm("OSCTUNE equ 098h");


typedef union {
    struct {
        unsigned TUN :6;
    };
    struct {
        unsigned TUN0 :1;
        unsigned TUN1 :1;
        unsigned TUN2 :1;
        unsigned TUN3 :1;
        unsigned TUN4 :1;
        unsigned TUN5 :1;
    };
} OSCTUNEbits_t;
extern volatile OSCTUNEbits_t OSCTUNEbits __attribute__((address(0x098)));
# 1928 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OSCCON __attribute__((address(0x099)));

__asm("OSCCON equ 099h");


typedef union {
    struct {
        unsigned SCS :2;
        unsigned :1;
        unsigned IRCF :4;
        unsigned SPLLEN :1;
    };
    struct {
        unsigned SCS0 :1;
        unsigned SCS1 :1;
        unsigned :1;
        unsigned IRCF0 :1;
        unsigned IRCF1 :1;
        unsigned IRCF2 :1;
        unsigned IRCF3 :1;
    };
} OSCCONbits_t;
extern volatile OSCCONbits_t OSCCONbits __attribute__((address(0x099)));
# 2000 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OSCSTAT __attribute__((address(0x09A)));

__asm("OSCSTAT equ 09Ah");


typedef union {
    struct {
        unsigned HFIOFS :1;
        unsigned LFIOFR :1;
        unsigned MFIOFR :1;
        unsigned HFIOFL :1;
        unsigned HFIOFR :1;
        unsigned OSTS :1;
        unsigned PLLR :1;
        unsigned SOSCR :1;
    };
} OSCSTATbits_t;
extern volatile OSCSTATbits_t OSCSTATbits __attribute__((address(0x09A)));
# 2062 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short ADRES __attribute__((address(0x09B)));

__asm("ADRES equ 09Bh");




extern volatile unsigned char ADRESL __attribute__((address(0x09B)));

__asm("ADRESL equ 09Bh");


typedef union {
    struct {
        unsigned ADRESL :8;
    };
} ADRESLbits_t;
extern volatile ADRESLbits_t ADRESLbits __attribute__((address(0x09B)));
# 2089 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ADRESH __attribute__((address(0x09C)));

__asm("ADRESH equ 09Ch");


typedef union {
    struct {
        unsigned ADRESH :8;
    };
} ADRESHbits_t;
extern volatile ADRESHbits_t ADRESHbits __attribute__((address(0x09C)));
# 2109 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ADCON0 __attribute__((address(0x09D)));

__asm("ADCON0 equ 09Dh");


typedef union {
    struct {
        unsigned ADON :1;
        unsigned GO_nDONE :1;
        unsigned CHS :5;
    };
    struct {
        unsigned :1;
        unsigned ADGO :1;
        unsigned CHS0 :1;
        unsigned CHS1 :1;
        unsigned CHS2 :1;
        unsigned CHS3 :1;
        unsigned CHS4 :1;
    };
    struct {
        unsigned :1;
        unsigned GO :1;
    };
} ADCON0bits_t;
extern volatile ADCON0bits_t ADCON0bits __attribute__((address(0x09D)));
# 2189 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ADCON1 __attribute__((address(0x09E)));

__asm("ADCON1 equ 09Eh");


typedef union {
    struct {
        unsigned ADPREF :2;
        unsigned ADNREF :1;
        unsigned :1;
        unsigned ADCS :3;
        unsigned ADFM :1;
    };
    struct {
        unsigned ADPREF0 :1;
        unsigned ADPREF1 :1;
    };
} ADCON1bits_t;
extern volatile ADCON1bits_t ADCON1bits __attribute__((address(0x09E)));
# 2242 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ADCON2 __attribute__((address(0x09F)));

__asm("ADCON2 equ 09Fh");


typedef union {
    struct {
        unsigned :4;
        unsigned TRIGSEL :4;
    };
    struct {
        unsigned :4;
        unsigned TRIGSEL0 :1;
        unsigned TRIGSEL1 :1;
        unsigned TRIGSEL2 :1;
        unsigned TRIGSEL3 :1;
    };
} ADCON2bits_t;
extern volatile ADCON2bits_t ADCON2bits __attribute__((address(0x09F)));
# 2290 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char LATA __attribute__((address(0x10C)));

__asm("LATA equ 010Ch");


typedef union {
    struct {
        unsigned LATA0 :1;
        unsigned LATA1 :1;
        unsigned LATA2 :1;
        unsigned LATA3 :1;
        unsigned LATA4 :1;
        unsigned LATA5 :1;
        unsigned LATA6 :1;
        unsigned LATA7 :1;
    };
} LATAbits_t;
extern volatile LATAbits_t LATAbits __attribute__((address(0x10C)));
# 2352 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char LATB __attribute__((address(0x10D)));

__asm("LATB equ 010Dh");


typedef union {
    struct {
        unsigned LATB0 :1;
        unsigned LATB1 :1;
        unsigned LATB2 :1;
        unsigned LATB3 :1;
        unsigned LATB4 :1;
        unsigned LATB5 :1;
        unsigned LATB6 :1;
        unsigned LATB7 :1;
    };
} LATBbits_t;
extern volatile LATBbits_t LATBbits __attribute__((address(0x10D)));
# 2414 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char LATC __attribute__((address(0x10E)));

__asm("LATC equ 010Eh");


typedef union {
    struct {
        unsigned LATC0 :1;
        unsigned LATC1 :1;
        unsigned LATC2 :1;
        unsigned LATC3 :1;
        unsigned LATC4 :1;
        unsigned LATC5 :1;
        unsigned LATC6 :1;
        unsigned LATC7 :1;
    };
} LATCbits_t;
extern volatile LATCbits_t LATCbits __attribute__((address(0x10E)));
# 2476 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char LATD __attribute__((address(0x10F)));

__asm("LATD equ 010Fh");


typedef union {
    struct {
        unsigned LATD0 :1;
        unsigned LATD1 :1;
        unsigned LATD2 :1;
        unsigned LATD3 :1;
        unsigned LATD4 :1;
        unsigned LATD5 :1;
        unsigned LATD6 :1;
        unsigned LATD7 :1;
    };
} LATDbits_t;
extern volatile LATDbits_t LATDbits __attribute__((address(0x10F)));
# 2538 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char LATE __attribute__((address(0x110)));

__asm("LATE equ 0110h");


typedef union {
    struct {
        unsigned LATE0 :1;
        unsigned LATE1 :1;
        unsigned LATE2 :1;
    };
} LATEbits_t;
extern volatile LATEbits_t LATEbits __attribute__((address(0x110)));
# 2570 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CM1CON0 __attribute__((address(0x111)));

__asm("CM1CON0 equ 0111h");


typedef union {
    struct {
        unsigned C1SYNC :1;
        unsigned C1HYS :1;
        unsigned C1SP :1;
        unsigned C1ZLF :1;
        unsigned C1POL :1;
        unsigned :1;
        unsigned C1OUT :1;
        unsigned C1ON :1;
    };
} CM1CON0bits_t;
extern volatile CM1CON0bits_t CM1CON0bits __attribute__((address(0x111)));
# 2627 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CM1CON1 __attribute__((address(0x112)));

__asm("CM1CON1 equ 0112h");


typedef union {
    struct {
        unsigned C1NCH :3;
        unsigned C1PCH :3;
        unsigned C1INTN :1;
        unsigned C1INTP :1;
    };
    struct {
        unsigned C1NCH0 :1;
        unsigned C1NCH1 :1;
        unsigned C1NCH2 :1;
        unsigned C1PCH0 :1;
        unsigned C1PCH1 :1;
        unsigned C1PCH2 :1;
    };
} CM1CON1bits_t;
extern volatile CM1CON1bits_t CM1CON1bits __attribute__((address(0x112)));
# 2703 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CM2CON0 __attribute__((address(0x113)));

__asm("CM2CON0 equ 0113h");


typedef union {
    struct {
        unsigned C2SYNC :1;
        unsigned C2HYS :1;
        unsigned C2SP :1;
        unsigned C2ZLF :1;
        unsigned C2POL :1;
        unsigned :1;
        unsigned C2OUT :1;
        unsigned C2ON :1;
    };
} CM2CON0bits_t;
extern volatile CM2CON0bits_t CM2CON0bits __attribute__((address(0x113)));
# 2760 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CM2CON1 __attribute__((address(0x114)));

__asm("CM2CON1 equ 0114h");


typedef union {
    struct {
        unsigned C2NCH :3;
        unsigned C2PCH :3;
        unsigned C2INTN :1;
        unsigned C2INTP :1;
    };
    struct {
        unsigned C2NCH0 :1;
        unsigned C2NCH1 :1;
        unsigned C2NCH2 :1;
        unsigned C2PCH0 :1;
        unsigned C2PCH1 :1;
        unsigned C2PCH2 :1;
    };
} CM2CON1bits_t;
extern volatile CM2CON1bits_t CM2CON1bits __attribute__((address(0x114)));
# 2836 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CMOUT __attribute__((address(0x115)));

__asm("CMOUT equ 0115h");


typedef union {
    struct {
        unsigned MC1OUT :1;
        unsigned MC2OUT :1;
    };
} CMOUTbits_t;
extern volatile CMOUTbits_t CMOUTbits __attribute__((address(0x115)));
# 2862 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char BORCON __attribute__((address(0x116)));

__asm("BORCON equ 0116h");


typedef union {
    struct {
        unsigned BORRDY :1;
        unsigned :5;
        unsigned BORFS :1;
        unsigned SBOREN :1;
    };
} BORCONbits_t;
extern volatile BORCONbits_t BORCONbits __attribute__((address(0x116)));
# 2895 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FVRCON __attribute__((address(0x117)));

__asm("FVRCON equ 0117h");


typedef union {
    struct {
        unsigned ADFVR :2;
        unsigned CDAFVR :2;
        unsigned TSRNG :1;
        unsigned TSEN :1;
        unsigned FVRRDY :1;
        unsigned FVREN :1;
    };
    struct {
        unsigned ADFVR0 :1;
        unsigned ADFVR1 :1;
        unsigned CDAFVR0 :1;
        unsigned CDAFVR1 :1;
    };
} FVRCONbits_t;
extern volatile FVRCONbits_t FVRCONbits __attribute__((address(0x117)));
# 2971 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char DAC1CON0 __attribute__((address(0x118)));

__asm("DAC1CON0 equ 0118h");


typedef union {
    struct {
        unsigned DAC1NSS :1;
        unsigned :1;
        unsigned DAC1PSS :2;
        unsigned DAC1OE2 :1;
        unsigned DAC1OE1 :1;
        unsigned :1;
        unsigned DAC1EN :1;
    };
    struct {
        unsigned :2;
        unsigned DAC1PSS0 :1;
        unsigned DAC1PSS1 :1;
    };
    struct {
        unsigned DACNSS :1;
        unsigned :1;
        unsigned DACPSS :2;
        unsigned DACOE0 :1;
        unsigned DACOE1 :1;
        unsigned :1;
        unsigned DACEN :1;
    };
    struct {
        unsigned :2;
        unsigned DACPSS0 :1;
        unsigned DACPSS1 :1;
    };
} DAC1CON0bits_t;
extern volatile DAC1CON0bits_t DAC1CON0bits __attribute__((address(0x118)));
# 3081 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char DAC1CON1 __attribute__((address(0x119)));

__asm("DAC1CON1 equ 0119h");


typedef union {
    struct {
        unsigned DAC1R :8;
    };
    struct {
        unsigned DAC1R0 :1;
        unsigned DAC1R1 :1;
        unsigned DAC1R2 :1;
        unsigned DAC1R3 :1;
        unsigned DAC1R4 :1;
        unsigned DAC1R5 :1;
        unsigned DAC1R6 :1;
        unsigned DAC1R7 :1;
    };
    struct {
        unsigned DACR0 :1;
        unsigned DACR1 :1;
        unsigned DACR2 :1;
        unsigned DACR3 :1;
        unsigned DACR4 :1;
        unsigned DACR5 :1;
        unsigned DACR6 :1;
        unsigned DACR7 :1;
    };
} DAC1CON1bits_t;
extern volatile DAC1CON1bits_t DAC1CON1bits __attribute__((address(0x119)));
# 3201 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char DAC2CON0 __attribute__((address(0x11A)));

__asm("DAC2CON0 equ 011Ah");


typedef union {
    struct {
        unsigned NSS :1;
        unsigned :1;
        unsigned PSS :2;
        unsigned OE2 :1;
        unsigned OE1 :1;
        unsigned :1;
        unsigned EN :1;
    };
    struct {
        unsigned :2;
        unsigned PSS0 :1;
        unsigned PSS1 :1;
    };
    struct {
        unsigned DACNSS :1;
        unsigned :1;
        unsigned DACPSS :2;
        unsigned DACOE2 :1;
        unsigned DACOE1 :1;
        unsigned :1;
        unsigned DACEN :1;
    };
    struct {
        unsigned :2;
        unsigned DACPSS0 :1;
        unsigned DACPSS1 :1;
    };
    struct {
        unsigned DAC2NSS :1;
        unsigned :1;
        unsigned DAC2PSS :2;
        unsigned DAC2OE2 :1;
        unsigned DAC2OE1 :1;
        unsigned :1;
        unsigned DAC2EN :1;
    };
    struct {
        unsigned :2;
        unsigned DAC2PSS0 :1;
        unsigned DAC2PSS1 :1;
    };
} DAC2CON0bits_t;
extern volatile DAC2CON0bits_t DAC2CON0bits __attribute__((address(0x11A)));
# 3360 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char DAC2REF __attribute__((address(0x11B)));

__asm("DAC2REF equ 011Bh");


extern volatile unsigned char DAC2CON1 __attribute__((address(0x11B)));

__asm("DAC2CON1 equ 011Bh");


typedef union {
    struct {
        unsigned DACR :5;
    };
    struct {
        unsigned DACR0 :1;
        unsigned DACR1 :1;
        unsigned DACR2 :1;
        unsigned DACR3 :1;
        unsigned DACR4 :1;
    };
    struct {
        unsigned R0 :1;
        unsigned R1 :1;
        unsigned R2 :1;
        unsigned R3 :1;
        unsigned R4 :1;
    };
    struct {
        unsigned DAC2R :5;
    };
    struct {
        unsigned DAC2R0 :1;
        unsigned DAC2R1 :1;
        unsigned DAC2R2 :1;
        unsigned DAC2R3 :1;
        unsigned DAC2R4 :1;
    };
    struct {
        unsigned REF0 :1;
        unsigned REF1 :1;
        unsigned REF2 :1;
        unsigned REF3 :1;
        unsigned REF4 :1;
        unsigned REF5 :1;
    };
    struct {
        unsigned DAC2REF0 :1;
        unsigned DAC2REF1 :1;
        unsigned DAC2REF2 :1;
        unsigned DAC2REF3 :1;
        unsigned DAC2REF4 :1;
        unsigned DAC2REF5 :1;
    };
} DAC2REFbits_t;
extern volatile DAC2REFbits_t DAC2REFbits __attribute__((address(0x11B)));
# 3563 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned DACR :5;
    };
    struct {
        unsigned DACR0 :1;
        unsigned DACR1 :1;
        unsigned DACR2 :1;
        unsigned DACR3 :1;
        unsigned DACR4 :1;
    };
    struct {
        unsigned R0 :1;
        unsigned R1 :1;
        unsigned R2 :1;
        unsigned R3 :1;
        unsigned R4 :1;
    };
    struct {
        unsigned DAC2R :5;
    };
    struct {
        unsigned DAC2R0 :1;
        unsigned DAC2R1 :1;
        unsigned DAC2R2 :1;
        unsigned DAC2R3 :1;
        unsigned DAC2R4 :1;
    };
    struct {
        unsigned REF0 :1;
        unsigned REF1 :1;
        unsigned REF2 :1;
        unsigned REF3 :1;
        unsigned REF4 :1;
        unsigned REF5 :1;
    };
    struct {
        unsigned DAC2REF0 :1;
        unsigned DAC2REF1 :1;
        unsigned DAC2REF2 :1;
        unsigned DAC2REF3 :1;
        unsigned DAC2REF4 :1;
        unsigned DAC2REF5 :1;
    };
} DAC2CON1bits_t;
extern volatile DAC2CON1bits_t DAC2CON1bits __attribute__((address(0x11B)));
# 3758 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ZCD1CON __attribute__((address(0x11C)));

__asm("ZCD1CON equ 011Ch");


typedef union {
    struct {
        unsigned ZCD1INTN :1;
        unsigned ZCD1INTP :1;
        unsigned :2;
        unsigned ZCD1POL :1;
        unsigned ZCD1OUT :1;
        unsigned :1;
        unsigned ZCD1EN :1;
    };
} ZCD1CONbits_t;
extern volatile ZCD1CONbits_t ZCD1CONbits __attribute__((address(0x11C)));
# 3804 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ANSELA __attribute__((address(0x18C)));

__asm("ANSELA equ 018Ch");


typedef union {
    struct {
        unsigned ANSA0 :1;
        unsigned ANSA1 :1;
        unsigned ANSA2 :1;
        unsigned ANSA3 :1;
        unsigned ANSA4 :1;
        unsigned ANSA5 :1;
    };
} ANSELAbits_t;
extern volatile ANSELAbits_t ANSELAbits __attribute__((address(0x18C)));
# 3854 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ANSELB __attribute__((address(0x18D)));

__asm("ANSELB equ 018Dh");


typedef union {
    struct {
        unsigned ANSB0 :1;
        unsigned ANSB1 :1;
        unsigned ANSB2 :1;
        unsigned ANSB3 :1;
        unsigned ANSB4 :1;
        unsigned ANSB5 :1;
    };
} ANSELBbits_t;
extern volatile ANSELBbits_t ANSELBbits __attribute__((address(0x18D)));
# 3904 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ANSELC __attribute__((address(0x18E)));

__asm("ANSELC equ 018Eh");


typedef union {
    struct {
        unsigned :2;
        unsigned ANSC2 :1;
        unsigned ANSC3 :1;
        unsigned ANSC4 :1;
        unsigned ANSC5 :1;
        unsigned ANSC6 :1;
        unsigned ANSC7 :1;
    };
} ANSELCbits_t;
extern volatile ANSELCbits_t ANSELCbits __attribute__((address(0x18E)));
# 3955 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ANSELD __attribute__((address(0x18F)));

__asm("ANSELD equ 018Fh");


typedef union {
    struct {
        unsigned ANSD0 :1;
        unsigned ANSD1 :1;
        unsigned ANSD2 :1;
        unsigned ANSD3 :1;
        unsigned ANSD4 :1;
        unsigned ANSD5 :1;
        unsigned ANSD6 :1;
        unsigned ANSD7 :1;
    };
} ANSELDbits_t;
extern volatile ANSELDbits_t ANSELDbits __attribute__((address(0x18F)));
# 4017 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ANSELE __attribute__((address(0x190)));

__asm("ANSELE equ 0190h");


typedef union {
    struct {
        unsigned ANSE0 :1;
        unsigned ANSE1 :1;
        unsigned ANSE2 :1;
    };
} ANSELEbits_t;
extern volatile ANSELEbits_t ANSELEbits __attribute__((address(0x190)));
# 4049 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short PMADR __attribute__((address(0x191)));

__asm("PMADR equ 0191h");




extern volatile unsigned char PMADRL __attribute__((address(0x191)));

__asm("PMADRL equ 0191h");


typedef union {
    struct {
        unsigned PMADRL :8;
    };
} PMADRLbits_t;
extern volatile PMADRLbits_t PMADRLbits __attribute__((address(0x191)));
# 4076 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PMADRH __attribute__((address(0x192)));

__asm("PMADRH equ 0192h");


typedef union {
    struct {
        unsigned PMADRH :7;
    };
} PMADRHbits_t;
extern volatile PMADRHbits_t PMADRHbits __attribute__((address(0x192)));
# 4096 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short PMDAT __attribute__((address(0x193)));

__asm("PMDAT equ 0193h");




extern volatile unsigned char PMDATL __attribute__((address(0x193)));

__asm("PMDATL equ 0193h");


typedef union {
    struct {
        unsigned PMDATL :8;
    };
} PMDATLbits_t;
extern volatile PMDATLbits_t PMDATLbits __attribute__((address(0x193)));
# 4123 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PMDATH __attribute__((address(0x194)));

__asm("PMDATH equ 0194h");


typedef union {
    struct {
        unsigned PMDATH :6;
    };
} PMDATHbits_t;
extern volatile PMDATHbits_t PMDATHbits __attribute__((address(0x194)));
# 4143 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PMCON1 __attribute__((address(0x195)));

__asm("PMCON1 equ 0195h");


typedef union {
    struct {
        unsigned RD :1;
        unsigned WR :1;
        unsigned WREN :1;
        unsigned WRERR :1;
        unsigned FREE :1;
        unsigned LWLO :1;
        unsigned CFGS :1;
    };
} PMCON1bits_t;
extern volatile PMCON1bits_t PMCON1bits __attribute__((address(0x195)));
# 4199 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PMCON2 __attribute__((address(0x196)));

__asm("PMCON2 equ 0196h");


typedef union {
    struct {
        unsigned PMCON2 :8;
    };
} PMCON2bits_t;
extern volatile PMCON2bits_t PMCON2bits __attribute__((address(0x196)));
# 4219 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char VREGCON __attribute__((address(0x197)));

__asm("VREGCON equ 0197h");


typedef union {
    struct {
        unsigned :1;
        unsigned VREGPM :1;
    };
} VREGCONbits_t;
extern volatile VREGCONbits_t VREGCONbits __attribute__((address(0x197)));
# 4240 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC1REG __attribute__((address(0x199)));

__asm("RC1REG equ 0199h");


extern volatile unsigned char RCREG __attribute__((address(0x199)));

__asm("RCREG equ 0199h");

extern volatile unsigned char RCREG1 __attribute__((address(0x199)));

__asm("RCREG1 equ 0199h");


typedef union {
    struct {
        unsigned RC1REG :8;
    };
} RC1REGbits_t;
extern volatile RC1REGbits_t RC1REGbits __attribute__((address(0x199)));







typedef union {
    struct {
        unsigned RC1REG :8;
    };
} RCREGbits_t;
extern volatile RCREGbits_t RCREGbits __attribute__((address(0x199)));






typedef union {
    struct {
        unsigned RC1REG :8;
    };
} RCREG1bits_t;
extern volatile RCREG1bits_t RCREG1bits __attribute__((address(0x199)));
# 4294 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TX1REG __attribute__((address(0x19A)));

__asm("TX1REG equ 019Ah");


extern volatile unsigned char TXREG1 __attribute__((address(0x19A)));

__asm("TXREG1 equ 019Ah");

extern volatile unsigned char TXREG __attribute__((address(0x19A)));

__asm("TXREG equ 019Ah");


typedef union {
    struct {
        unsigned TX1REG :8;
    };
} TX1REGbits_t;
extern volatile TX1REGbits_t TX1REGbits __attribute__((address(0x19A)));







typedef union {
    struct {
        unsigned TX1REG :8;
    };
} TXREG1bits_t;
extern volatile TXREG1bits_t TXREG1bits __attribute__((address(0x19A)));






typedef union {
    struct {
        unsigned TX1REG :8;
    };
} TXREGbits_t;
extern volatile TXREGbits_t TXREGbits __attribute__((address(0x19A)));
# 4348 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short SP1BRG __attribute__((address(0x19B)));

__asm("SP1BRG equ 019Bh");




extern volatile unsigned char SP1BRGL __attribute__((address(0x19B)));

__asm("SP1BRGL equ 019Bh");


extern volatile unsigned char SPBRG __attribute__((address(0x19B)));

__asm("SPBRG equ 019Bh");

extern volatile unsigned char SPBRG1 __attribute__((address(0x19B)));

__asm("SPBRG1 equ 019Bh");

extern volatile unsigned char SPBRGL __attribute__((address(0x19B)));

__asm("SPBRGL equ 019Bh");


typedef union {
    struct {
        unsigned SP1BRGL :8;
    };
} SP1BRGLbits_t;
extern volatile SP1BRGLbits_t SP1BRGLbits __attribute__((address(0x19B)));







typedef union {
    struct {
        unsigned SP1BRGL :8;
    };
} SPBRGbits_t;
extern volatile SPBRGbits_t SPBRGbits __attribute__((address(0x19B)));






typedef union {
    struct {
        unsigned SP1BRGL :8;
    };
} SPBRG1bits_t;
extern volatile SPBRG1bits_t SPBRG1bits __attribute__((address(0x19B)));






typedef union {
    struct {
        unsigned SP1BRGL :8;
    };
} SPBRGLbits_t;
extern volatile SPBRGLbits_t SPBRGLbits __attribute__((address(0x19B)));
# 4425 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SP1BRGH __attribute__((address(0x19C)));

__asm("SP1BRGH equ 019Ch");


extern volatile unsigned char SPBRGH __attribute__((address(0x19C)));

__asm("SPBRGH equ 019Ch");

extern volatile unsigned char SPBRGH1 __attribute__((address(0x19C)));

__asm("SPBRGH1 equ 019Ch");


typedef union {
    struct {
        unsigned SP1BRGH :8;
    };
} SP1BRGHbits_t;
extern volatile SP1BRGHbits_t SP1BRGHbits __attribute__((address(0x19C)));







typedef union {
    struct {
        unsigned SP1BRGH :8;
    };
} SPBRGHbits_t;
extern volatile SPBRGHbits_t SPBRGHbits __attribute__((address(0x19C)));






typedef union {
    struct {
        unsigned SP1BRGH :8;
    };
} SPBRGH1bits_t;
extern volatile SPBRGH1bits_t SPBRGH1bits __attribute__((address(0x19C)));
# 4479 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC1STA __attribute__((address(0x19D)));

__asm("RC1STA equ 019Dh");


extern volatile unsigned char RCSTA1 __attribute__((address(0x19D)));

__asm("RCSTA1 equ 019Dh");

extern volatile unsigned char RCSTA __attribute__((address(0x19D)));

__asm("RCSTA equ 019Dh");


typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADDEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
} RC1STAbits_t;
extern volatile RC1STAbits_t RC1STAbits __attribute__((address(0x19D)));
# 4548 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADDEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
} RCSTA1bits_t;
extern volatile RCSTA1bits_t RCSTA1bits __attribute__((address(0x19D)));
# 4602 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADDEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
} RCSTAbits_t;
extern volatile RCSTAbits_t RCSTAbits __attribute__((address(0x19D)));
# 4659 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TX1STA __attribute__((address(0x19E)));

__asm("TX1STA equ 019Eh");


extern volatile unsigned char TXSTA1 __attribute__((address(0x19E)));

__asm("TXSTA1 equ 019Eh");

extern volatile unsigned char TXSTA __attribute__((address(0x19E)));

__asm("TXSTA equ 019Eh");


typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned SENDB :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
} TX1STAbits_t;
extern volatile TX1STAbits_t TX1STAbits __attribute__((address(0x19E)));
# 4728 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned SENDB :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
} TXSTA1bits_t;
extern volatile TXSTA1bits_t TXSTA1bits __attribute__((address(0x19E)));
# 4782 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned SENDB :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
} TXSTAbits_t;
extern volatile TXSTAbits_t TXSTAbits __attribute__((address(0x19E)));
# 4839 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char BAUD1CON __attribute__((address(0x19F)));

__asm("BAUD1CON equ 019Fh");


extern volatile unsigned char BAUDCON1 __attribute__((address(0x19F)));

__asm("BAUDCON1 equ 019Fh");

extern volatile unsigned char BAUDCTL1 __attribute__((address(0x19F)));

__asm("BAUDCTL1 equ 019Fh");

extern volatile unsigned char BAUDCON __attribute__((address(0x19F)));

__asm("BAUDCON equ 019Fh");

extern volatile unsigned char BAUDCTL __attribute__((address(0x19F)));

__asm("BAUDCTL equ 019Fh");


typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
} BAUD1CONbits_t;
extern volatile BAUD1CONbits_t BAUD1CONbits __attribute__((address(0x19F)));
# 4906 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
} BAUDCON1bits_t;
extern volatile BAUDCON1bits_t BAUDCON1bits __attribute__((address(0x19F)));
# 4950 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
} BAUDCTL1bits_t;
extern volatile BAUDCTL1bits_t BAUDCTL1bits __attribute__((address(0x19F)));
# 4994 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
} BAUDCONbits_t;
extern volatile BAUDCONbits_t BAUDCONbits __attribute__((address(0x19F)));
# 5038 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
} BAUDCTLbits_t;
extern volatile BAUDCTLbits_t BAUDCTLbits __attribute__((address(0x19F)));
# 5085 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WPUA __attribute__((address(0x20C)));

__asm("WPUA equ 020Ch");


typedef union {
    struct {
        unsigned WPUA0 :1;
        unsigned WPUA1 :1;
        unsigned WPUA2 :1;
        unsigned WPUA3 :1;
        unsigned WPUA4 :1;
        unsigned WPUA5 :1;
        unsigned WPUA6 :1;
        unsigned WPUA7 :1;
    };
} WPUAbits_t;
extern volatile WPUAbits_t WPUAbits __attribute__((address(0x20C)));
# 5147 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WPUB __attribute__((address(0x20D)));

__asm("WPUB equ 020Dh");


typedef union {
    struct {
        unsigned WPUB0 :1;
        unsigned WPUB1 :1;
        unsigned WPUB2 :1;
        unsigned WPUB3 :1;
        unsigned WPUB4 :1;
        unsigned WPUB5 :1;
        unsigned WPUB6 :1;
        unsigned WPUB7 :1;
    };
} WPUBbits_t;
extern volatile WPUBbits_t WPUBbits __attribute__((address(0x20D)));
# 5209 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WPUC __attribute__((address(0x20E)));

__asm("WPUC equ 020Eh");


typedef union {
    struct {
        unsigned WPUC0 :1;
        unsigned WPUC1 :1;
        unsigned WPUC2 :1;
        unsigned WPUC3 :1;
        unsigned WPUC4 :1;
        unsigned WPUC5 :1;
        unsigned WPUC6 :1;
        unsigned WPUC7 :1;
    };
} WPUCbits_t;
extern volatile WPUCbits_t WPUCbits __attribute__((address(0x20E)));
# 5271 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WPUD __attribute__((address(0x20F)));

__asm("WPUD equ 020Fh");


typedef union {
    struct {
        unsigned WPUD0 :1;
        unsigned WPUD1 :1;
        unsigned WPUD2 :1;
        unsigned WPUD3 :1;
        unsigned WPUD4 :1;
        unsigned WPUD5 :1;
        unsigned WPUD6 :1;
        unsigned WPUD7 :1;
    };
} WPUDbits_t;
extern volatile WPUDbits_t WPUDbits __attribute__((address(0x20F)));
# 5333 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WPUE __attribute__((address(0x210)));

__asm("WPUE equ 0210h");


typedef union {
    struct {
        unsigned WPUE0 :1;
        unsigned WPUE1 :1;
        unsigned WPUE2 :1;
        unsigned WPUE3 :1;
    };
} WPUEbits_t;
extern volatile WPUEbits_t WPUEbits __attribute__((address(0x210)));
# 5371 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1BUF __attribute__((address(0x211)));

__asm("SSP1BUF equ 0211h");


extern volatile unsigned char SSPBUF __attribute__((address(0x211)));

__asm("SSPBUF equ 0211h");


typedef union {
    struct {
        unsigned SSP1BUF0 :1;
        unsigned SSP1BUF1 :1;
        unsigned SSP1BUF2 :1;
        unsigned SSP1BUF3 :1;
        unsigned SSP1BUF4 :1;
        unsigned SSP1BUF5 :1;
        unsigned SSP1BUF6 :1;
        unsigned SSP1BUF7 :1;
    };
    struct {
        unsigned BUF :8;
    };
    struct {
        unsigned BUF0 :1;
        unsigned BUF1 :1;
        unsigned BUF2 :1;
        unsigned BUF3 :1;
        unsigned BUF4 :1;
        unsigned BUF5 :1;
        unsigned BUF6 :1;
        unsigned BUF7 :1;
    };
    struct {
        unsigned SSP1BUF :8;
    };
} SSP1BUFbits_t;
extern volatile SSP1BUFbits_t SSP1BUFbits __attribute__((address(0x211)));
# 5502 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSP1BUF0 :1;
        unsigned SSP1BUF1 :1;
        unsigned SSP1BUF2 :1;
        unsigned SSP1BUF3 :1;
        unsigned SSP1BUF4 :1;
        unsigned SSP1BUF5 :1;
        unsigned SSP1BUF6 :1;
        unsigned SSP1BUF7 :1;
    };
    struct {
        unsigned BUF :8;
    };
    struct {
        unsigned BUF0 :1;
        unsigned BUF1 :1;
        unsigned BUF2 :1;
        unsigned BUF3 :1;
        unsigned BUF4 :1;
        unsigned BUF5 :1;
        unsigned BUF6 :1;
        unsigned BUF7 :1;
    };
    struct {
        unsigned SSP1BUF :8;
    };
} SSPBUFbits_t;
extern volatile SSPBUFbits_t SSPBUFbits __attribute__((address(0x211)));
# 5625 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1ADD __attribute__((address(0x212)));

__asm("SSP1ADD equ 0212h");


extern volatile unsigned char SSPADD __attribute__((address(0x212)));

__asm("SSPADD equ 0212h");


typedef union {
    struct {
        unsigned SSP1ADD0 :1;
        unsigned SSP1ADD1 :1;
        unsigned SSP1ADD2 :1;
        unsigned SSP1ADD3 :1;
        unsigned SSP1ADD4 :1;
        unsigned SSP1ADD5 :1;
        unsigned SSP1ADD6 :1;
        unsigned SSP1ADD7 :1;
    };
    struct {
        unsigned ADD :8;
    };
    struct {
        unsigned ADD0 :1;
        unsigned ADD1 :1;
        unsigned ADD2 :1;
        unsigned ADD3 :1;
        unsigned ADD4 :1;
        unsigned ADD5 :1;
        unsigned ADD6 :1;
        unsigned ADD7 :1;
    };
    struct {
        unsigned SSP1ADD :8;
    };
} SSP1ADDbits_t;
extern volatile SSP1ADDbits_t SSP1ADDbits __attribute__((address(0x212)));
# 5756 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSP1ADD0 :1;
        unsigned SSP1ADD1 :1;
        unsigned SSP1ADD2 :1;
        unsigned SSP1ADD3 :1;
        unsigned SSP1ADD4 :1;
        unsigned SSP1ADD5 :1;
        unsigned SSP1ADD6 :1;
        unsigned SSP1ADD7 :1;
    };
    struct {
        unsigned ADD :8;
    };
    struct {
        unsigned ADD0 :1;
        unsigned ADD1 :1;
        unsigned ADD2 :1;
        unsigned ADD3 :1;
        unsigned ADD4 :1;
        unsigned ADD5 :1;
        unsigned ADD6 :1;
        unsigned ADD7 :1;
    };
    struct {
        unsigned SSP1ADD :8;
    };
} SSPADDbits_t;
extern volatile SSPADDbits_t SSPADDbits __attribute__((address(0x212)));
# 5879 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1MSK __attribute__((address(0x213)));

__asm("SSP1MSK equ 0213h");


extern volatile unsigned char SSPMSK __attribute__((address(0x213)));

__asm("SSPMSK equ 0213h");


typedef union {
    struct {
        unsigned SSP1MSK0 :1;
        unsigned SSP1MSK1 :1;
        unsigned SSP1MSK2 :1;
        unsigned SSP1MSK3 :1;
        unsigned SSP1MSK4 :1;
        unsigned SSP1MSK5 :1;
        unsigned SSP1MSK6 :1;
        unsigned SSP1MSK7 :1;
    };
    struct {
        unsigned MSK :8;
    };
    struct {
        unsigned MSK0 :1;
        unsigned MSK1 :1;
        unsigned MSK2 :1;
        unsigned MSK3 :1;
        unsigned MSK4 :1;
        unsigned MSK5 :1;
        unsigned MSK6 :1;
        unsigned MSK7 :1;
    };
    struct {
        unsigned SSP1MSK :8;
    };
} SSP1MSKbits_t;
extern volatile SSP1MSKbits_t SSP1MSKbits __attribute__((address(0x213)));
# 6010 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSP1MSK0 :1;
        unsigned SSP1MSK1 :1;
        unsigned SSP1MSK2 :1;
        unsigned SSP1MSK3 :1;
        unsigned SSP1MSK4 :1;
        unsigned SSP1MSK5 :1;
        unsigned SSP1MSK6 :1;
        unsigned SSP1MSK7 :1;
    };
    struct {
        unsigned MSK :8;
    };
    struct {
        unsigned MSK0 :1;
        unsigned MSK1 :1;
        unsigned MSK2 :1;
        unsigned MSK3 :1;
        unsigned MSK4 :1;
        unsigned MSK5 :1;
        unsigned MSK6 :1;
        unsigned MSK7 :1;
    };
    struct {
        unsigned SSP1MSK :8;
    };
} SSPMSKbits_t;
extern volatile SSPMSKbits_t SSPMSKbits __attribute__((address(0x213)));
# 6133 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1STAT __attribute__((address(0x214)));

__asm("SSP1STAT equ 0214h");


extern volatile unsigned char SSPSTAT __attribute__((address(0x214)));

__asm("SSPSTAT equ 0214h");


typedef union {
    struct {
        unsigned BF :1;
        unsigned UA :1;
        unsigned R_nW :1;
        unsigned S :1;
        unsigned P :1;
        unsigned D_nA :1;
        unsigned CKE :1;
        unsigned SMP :1;
    };
} SSP1STATbits_t;
extern volatile SSP1STATbits_t SSP1STATbits __attribute__((address(0x214)));
# 6198 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned BF :1;
        unsigned UA :1;
        unsigned R_nW :1;
        unsigned S :1;
        unsigned P :1;
        unsigned D_nA :1;
        unsigned CKE :1;
        unsigned SMP :1;
    };
} SSPSTATbits_t;
extern volatile SSPSTATbits_t SSPSTATbits __attribute__((address(0x214)));
# 6255 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1CON1 __attribute__((address(0x215)));

__asm("SSP1CON1 equ 0215h");


extern volatile unsigned char SSPCON __attribute__((address(0x215)));

__asm("SSPCON equ 0215h");

extern volatile unsigned char SSPCON1 __attribute__((address(0x215)));

__asm("SSPCON1 equ 0215h");

extern volatile unsigned char SSP1CON __attribute__((address(0x215)));

__asm("SSP1CON equ 0215h");


typedef union {
    struct {
        unsigned SSPM :4;
        unsigned CKP :1;
        unsigned SSPEN :1;
        unsigned SSPOV :1;
        unsigned WCOL :1;
    };
    struct {
        unsigned SSPM0 :1;
        unsigned SSPM1 :1;
        unsigned SSPM2 :1;
        unsigned SSPM3 :1;
    };
} SSP1CON1bits_t;
extern volatile SSP1CON1bits_t SSP1CON1bits __attribute__((address(0x215)));
# 6336 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSPM :4;
        unsigned CKP :1;
        unsigned SSPEN :1;
        unsigned SSPOV :1;
        unsigned WCOL :1;
    };
    struct {
        unsigned SSPM0 :1;
        unsigned SSPM1 :1;
        unsigned SSPM2 :1;
        unsigned SSPM3 :1;
    };
} SSPCONbits_t;
extern volatile SSPCONbits_t SSPCONbits __attribute__((address(0x215)));
# 6398 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSPM :4;
        unsigned CKP :1;
        unsigned SSPEN :1;
        unsigned SSPOV :1;
        unsigned WCOL :1;
    };
    struct {
        unsigned SSPM0 :1;
        unsigned SSPM1 :1;
        unsigned SSPM2 :1;
        unsigned SSPM3 :1;
    };
} SSPCON1bits_t;
extern volatile SSPCON1bits_t SSPCON1bits __attribute__((address(0x215)));
# 6460 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SSPM :4;
        unsigned CKP :1;
        unsigned SSPEN :1;
        unsigned SSPOV :1;
        unsigned WCOL :1;
    };
    struct {
        unsigned SSPM0 :1;
        unsigned SSPM1 :1;
        unsigned SSPM2 :1;
        unsigned SSPM3 :1;
    };
} SSP1CONbits_t;
extern volatile SSP1CONbits_t SSP1CONbits __attribute__((address(0x215)));
# 6525 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1CON2 __attribute__((address(0x216)));

__asm("SSP1CON2 equ 0216h");


extern volatile unsigned char SSPCON2 __attribute__((address(0x216)));

__asm("SSPCON2 equ 0216h");


typedef union {
    struct {
        unsigned SEN :1;
        unsigned RSEN :1;
        unsigned PEN :1;
        unsigned RCEN :1;
        unsigned ACKEN :1;
        unsigned ACKDT :1;
        unsigned ACKSTAT :1;
        unsigned GCEN :1;
    };
} SSP1CON2bits_t;
extern volatile SSP1CON2bits_t SSP1CON2bits __attribute__((address(0x216)));
# 6590 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned SEN :1;
        unsigned RSEN :1;
        unsigned PEN :1;
        unsigned RCEN :1;
        unsigned ACKEN :1;
        unsigned ACKDT :1;
        unsigned ACKSTAT :1;
        unsigned GCEN :1;
    };
} SSPCON2bits_t;
extern volatile SSPCON2bits_t SSPCON2bits __attribute__((address(0x216)));
# 6647 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSP1CON3 __attribute__((address(0x217)));

__asm("SSP1CON3 equ 0217h");


extern volatile unsigned char SSPCON3 __attribute__((address(0x217)));

__asm("SSPCON3 equ 0217h");


typedef union {
    struct {
        unsigned DHEN :1;
        unsigned AHEN :1;
        unsigned SBCDE :1;
        unsigned SDAHT :1;
        unsigned BOEN :1;
        unsigned SCIE :1;
        unsigned PCIE :1;
        unsigned ACKTIM :1;
    };
} SSP1CON3bits_t;
extern volatile SSP1CON3bits_t SSP1CON3bits __attribute__((address(0x217)));
# 6712 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned DHEN :1;
        unsigned AHEN :1;
        unsigned SBCDE :1;
        unsigned SDAHT :1;
        unsigned BOEN :1;
        unsigned SCIE :1;
        unsigned PCIE :1;
        unsigned ACKTIM :1;
    };
} SSPCON3bits_t;
extern volatile SSPCON3bits_t SSPCON3bits __attribute__((address(0x217)));
# 6769 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ODCONA __attribute__((address(0x28C)));

__asm("ODCONA equ 028Ch");


typedef union {
    struct {
        unsigned ODA0 :1;
        unsigned ODA1 :1;
        unsigned ODA2 :1;
        unsigned ODA3 :1;
        unsigned ODA4 :1;
        unsigned ODA5 :1;
        unsigned ODA6 :1;
        unsigned ODA7 :1;
    };
} ODCONAbits_t;
extern volatile ODCONAbits_t ODCONAbits __attribute__((address(0x28C)));
# 6831 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ODCONB __attribute__((address(0x28D)));

__asm("ODCONB equ 028Dh");


typedef union {
    struct {
        unsigned ODB0 :1;
        unsigned ODB1 :1;
        unsigned ODB2 :1;
        unsigned ODB3 :1;
        unsigned ODB4 :1;
        unsigned ODB5 :1;
        unsigned ODB6 :1;
        unsigned ODB7 :1;
    };
} ODCONBbits_t;
extern volatile ODCONBbits_t ODCONBbits __attribute__((address(0x28D)));
# 6893 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ODCONC __attribute__((address(0x28E)));

__asm("ODCONC equ 028Eh");


typedef union {
    struct {
        unsigned ODC0 :1;
        unsigned ODC1 :1;
        unsigned ODC2 :1;
        unsigned ODC3 :1;
        unsigned ODC4 :1;
        unsigned ODC5 :1;
        unsigned ODC6 :1;
        unsigned ODC7 :1;
    };
} ODCONCbits_t;
extern volatile ODCONCbits_t ODCONCbits __attribute__((address(0x28E)));
# 6955 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ODCOND __attribute__((address(0x28F)));

__asm("ODCOND equ 028Fh");


typedef union {
    struct {
        unsigned ODD0 :1;
        unsigned ODD1 :1;
        unsigned ODD2 :1;
        unsigned ODD3 :1;
        unsigned ODD4 :1;
        unsigned ODD5 :1;
        unsigned ODD6 :1;
        unsigned ODD7 :1;
    };
} ODCONDbits_t;
extern volatile ODCONDbits_t ODCONDbits __attribute__((address(0x28F)));
# 7017 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char ODCONE __attribute__((address(0x290)));

__asm("ODCONE equ 0290h");


typedef union {
    struct {
        unsigned ODE0 :1;
        unsigned ODE1 :1;
        unsigned ODE2 :1;
    };
} ODCONEbits_t;
extern volatile ODCONEbits_t ODCONEbits __attribute__((address(0x290)));
# 7049 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short CCPR1 __attribute__((address(0x291)));

__asm("CCPR1 equ 0291h");




extern volatile unsigned char CCPR1L __attribute__((address(0x291)));

__asm("CCPR1L equ 0291h");


typedef union {
    struct {
        unsigned CCPR1L :8;
    };
} CCPR1Lbits_t;
extern volatile CCPR1Lbits_t CCPR1Lbits __attribute__((address(0x291)));
# 7076 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCPR1H __attribute__((address(0x292)));

__asm("CCPR1H equ 0292h");


typedef union {
    struct {
        unsigned CCPR1H :8;
    };
} CCPR1Hbits_t;
extern volatile CCPR1Hbits_t CCPR1Hbits __attribute__((address(0x292)));
# 7096 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCP1CON __attribute__((address(0x293)));

__asm("CCP1CON equ 0293h");


extern volatile unsigned char ECCP1CON __attribute__((address(0x293)));

__asm("ECCP1CON equ 0293h");


typedef union {
    struct {
        unsigned CCP1M :4;
        unsigned DC1B :2;
    };
    struct {
        unsigned CCP1M0 :1;
        unsigned CCP1M1 :1;
        unsigned CCP1M2 :1;
        unsigned CCP1M3 :1;
        unsigned DC1B0 :1;
        unsigned DC1B1 :1;
    };
    struct {
        unsigned :4;
        unsigned CCP1Y :1;
        unsigned CCP1X :1;
    };
} CCP1CONbits_t;
extern volatile CCP1CONbits_t CCP1CONbits __attribute__((address(0x293)));
# 7178 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned CCP1M :4;
        unsigned DC1B :2;
    };
    struct {
        unsigned CCP1M0 :1;
        unsigned CCP1M1 :1;
        unsigned CCP1M2 :1;
        unsigned CCP1M3 :1;
        unsigned DC1B0 :1;
        unsigned DC1B1 :1;
    };
    struct {
        unsigned :4;
        unsigned CCP1Y :1;
        unsigned CCP1X :1;
    };
} ECCP1CONbits_t;
extern volatile ECCP1CONbits_t ECCP1CONbits __attribute__((address(0x293)));
# 7252 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned short CCPR2 __attribute__((address(0x298)));

__asm("CCPR2 equ 0298h");




extern volatile unsigned char CCPR2L __attribute__((address(0x298)));

__asm("CCPR2L equ 0298h");


typedef union {
    struct {
        unsigned CCPR2L :8;
    };
} CCPR2Lbits_t;
extern volatile CCPR2Lbits_t CCPR2Lbits __attribute__((address(0x298)));
# 7279 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCPR2H __attribute__((address(0x299)));

__asm("CCPR2H equ 0299h");


typedef union {
    struct {
        unsigned CCPR2H :8;
    };
} CCPR2Hbits_t;
extern volatile CCPR2Hbits_t CCPR2Hbits __attribute__((address(0x299)));
# 7299 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCP2CON __attribute__((address(0x29A)));

__asm("CCP2CON equ 029Ah");


extern volatile unsigned char ECCP2CON __attribute__((address(0x29A)));

__asm("ECCP2CON equ 029Ah");


typedef union {
    struct {
        unsigned CCP2M :4;
        unsigned DC2B :2;
    };
    struct {
        unsigned CCP2M0 :1;
        unsigned CCP2M1 :1;
        unsigned CCP2M2 :1;
        unsigned CCP2M3 :1;
        unsigned DC2B0 :1;
        unsigned DC2B1 :1;
    };
    struct {
        unsigned :4;
        unsigned CCP2Y :1;
        unsigned CCP2X :1;
    };
} CCP2CONbits_t;
extern volatile CCP2CONbits_t CCP2CONbits __attribute__((address(0x29A)));
# 7381 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned CCP2M :4;
        unsigned DC2B :2;
    };
    struct {
        unsigned CCP2M0 :1;
        unsigned CCP2M1 :1;
        unsigned CCP2M2 :1;
        unsigned CCP2M3 :1;
        unsigned DC2B0 :1;
        unsigned DC2B1 :1;
    };
    struct {
        unsigned :4;
        unsigned CCP2Y :1;
        unsigned CCP2X :1;
    };
} ECCP2CONbits_t;
extern volatile ECCP2CONbits_t ECCP2CONbits __attribute__((address(0x29A)));
# 7455 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCPTMRS __attribute__((address(0x29E)));

__asm("CCPTMRS equ 029Eh");


typedef union {
    struct {
        unsigned C1TSEL :2;
        unsigned C2TSEL :2;
        unsigned P3TSEL :2;
        unsigned P4TSEL :2;
    };
    struct {
        unsigned C1TSEL0 :1;
        unsigned C1TSEL1 :1;
        unsigned C2TSEL0 :1;
        unsigned C2TSEL1 :1;
        unsigned P3TSEL0 :1;
        unsigned P3TSEL1 :1;
        unsigned P4TSEL0 :1;
        unsigned P4TSEL1 :1;
    };
} CCPTMRSbits_t;
extern volatile CCPTMRSbits_t CCPTMRSbits __attribute__((address(0x29E)));
# 7543 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SLRCONA __attribute__((address(0x30C)));

__asm("SLRCONA equ 030Ch");


typedef union {
    struct {
        unsigned SLRA0 :1;
        unsigned SLRA1 :1;
        unsigned SLRA2 :1;
        unsigned SLRA3 :1;
        unsigned SLRA4 :1;
        unsigned SLRA5 :1;
        unsigned SLRA6 :1;
        unsigned SLRA7 :1;
    };
} SLRCONAbits_t;
extern volatile SLRCONAbits_t SLRCONAbits __attribute__((address(0x30C)));
# 7605 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SLRCONB __attribute__((address(0x30D)));

__asm("SLRCONB equ 030Dh");


typedef union {
    struct {
        unsigned SLRB0 :1;
        unsigned SLRB1 :1;
        unsigned SLRB2 :1;
        unsigned SLRB3 :1;
        unsigned SLRB4 :1;
        unsigned SLRB5 :1;
        unsigned SLRB6 :1;
        unsigned SLRB7 :1;
    };
} SLRCONBbits_t;
extern volatile SLRCONBbits_t SLRCONBbits __attribute__((address(0x30D)));
# 7667 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SLRCONC __attribute__((address(0x30E)));

__asm("SLRCONC equ 030Eh");


typedef union {
    struct {
        unsigned SLRC0 :1;
        unsigned SLRC1 :1;
        unsigned SLRC2 :1;
        unsigned SLRC3 :1;
        unsigned SLRC4 :1;
        unsigned SLRC5 :1;
        unsigned SLRC6 :1;
        unsigned SLRC7 :1;
    };
} SLRCONCbits_t;
extern volatile SLRCONCbits_t SLRCONCbits __attribute__((address(0x30E)));
# 7729 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SLRCOND __attribute__((address(0x30F)));

__asm("SLRCOND equ 030Fh");


typedef union {
    struct {
        unsigned SLRD0 :1;
        unsigned SLRD1 :1;
        unsigned SLRD2 :1;
        unsigned SLRD3 :1;
        unsigned SLRD4 :1;
        unsigned SLRD5 :1;
        unsigned SLRD6 :1;
        unsigned SLRD7 :1;
    };
} SLRCONDbits_t;
extern volatile SLRCONDbits_t SLRCONDbits __attribute__((address(0x30F)));
# 7791 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SLRCONE __attribute__((address(0x310)));

__asm("SLRCONE equ 0310h");


typedef union {
    struct {
        unsigned SLRE0 :1;
        unsigned SLRE1 :1;
        unsigned SLRE2 :1;
    };
} SLRCONEbits_t;
extern volatile SLRCONEbits_t SLRCONEbits __attribute__((address(0x310)));
# 7823 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INLVLA __attribute__((address(0x38C)));

__asm("INLVLA equ 038Ch");


typedef union {
    struct {
        unsigned INLVLA0 :1;
        unsigned INLVLA1 :1;
        unsigned INLVLA2 :1;
        unsigned INLVLA3 :1;
        unsigned INLVLA4 :1;
        unsigned INLVLA5 :1;
        unsigned INLVLA6 :1;
        unsigned INLVLA7 :1;
    };
} INLVLAbits_t;
extern volatile INLVLAbits_t INLVLAbits __attribute__((address(0x38C)));
# 7885 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INLVLB __attribute__((address(0x38D)));

__asm("INLVLB equ 038Dh");


typedef union {
    struct {
        unsigned INLVLB0 :1;
        unsigned INLVLB1 :1;
        unsigned INLVLB2 :1;
        unsigned INLVLB3 :1;
        unsigned INLVLB4 :1;
        unsigned INLVLB5 :1;
        unsigned INLVLB6 :1;
        unsigned INLVLB7 :1;
    };
} INLVLBbits_t;
extern volatile INLVLBbits_t INLVLBbits __attribute__((address(0x38D)));
# 7947 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INLVLC __attribute__((address(0x38E)));

__asm("INLVLC equ 038Eh");


typedef union {
    struct {
        unsigned INLVLC0 :1;
        unsigned INLVLC1 :1;
        unsigned INLVLC2 :1;
        unsigned INLVLC3 :1;
        unsigned INLVLC4 :1;
        unsigned INLVLC5 :1;
        unsigned INLVLC6 :1;
        unsigned INLVLC7 :1;
    };
} INLVLCbits_t;
extern volatile INLVLCbits_t INLVLCbits __attribute__((address(0x38E)));
# 8009 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INLVLD __attribute__((address(0x38F)));

__asm("INLVLD equ 038Fh");


typedef union {
    struct {
        unsigned INLVLD0 :1;
        unsigned INLVLD1 :1;
        unsigned INLVLD2 :1;
        unsigned INLVLD3 :1;
        unsigned INLVLD4 :1;
        unsigned INLVLD5 :1;
        unsigned INLVLD6 :1;
        unsigned INLVLD7 :1;
    };
} INLVLDbits_t;
extern volatile INLVLDbits_t INLVLDbits __attribute__((address(0x38F)));
# 8071 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INLVLE __attribute__((address(0x390)));

__asm("INLVLE equ 0390h");


typedef union {
    struct {
        unsigned INLVLE0 :1;
        unsigned INLVLE1 :1;
        unsigned INLVLE2 :1;
        unsigned INLVLE3 :1;
    };
} INLVLEbits_t;
extern volatile INLVLEbits_t INLVLEbits __attribute__((address(0x390)));
# 8109 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCAP __attribute__((address(0x391)));

__asm("IOCAP equ 0391h");


typedef union {
    struct {
        unsigned IOCAP0 :1;
        unsigned IOCAP1 :1;
        unsigned IOCAP2 :1;
        unsigned IOCAP3 :1;
        unsigned IOCAP4 :1;
        unsigned IOCAP5 :1;
        unsigned IOCAP6 :1;
        unsigned IOCAP7 :1;
    };
} IOCAPbits_t;
extern volatile IOCAPbits_t IOCAPbits __attribute__((address(0x391)));
# 8171 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCAN __attribute__((address(0x392)));

__asm("IOCAN equ 0392h");


typedef union {
    struct {
        unsigned IOCAN0 :1;
        unsigned IOCAN1 :1;
        unsigned IOCAN2 :1;
        unsigned IOCAN3 :1;
        unsigned IOCAN4 :1;
        unsigned IOCAN5 :1;
        unsigned IOCAN6 :1;
        unsigned IOCAN7 :1;
    };
} IOCANbits_t;
extern volatile IOCANbits_t IOCANbits __attribute__((address(0x392)));
# 8233 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCAF __attribute__((address(0x393)));

__asm("IOCAF equ 0393h");


typedef union {
    struct {
        unsigned IOCAF0 :1;
        unsigned IOCAF1 :1;
        unsigned IOCAF2 :1;
        unsigned IOCAF3 :1;
        unsigned IOCAF4 :1;
        unsigned IOCAF5 :1;
        unsigned IOCAF6 :1;
        unsigned IOCAF7 :1;
    };
} IOCAFbits_t;
extern volatile IOCAFbits_t IOCAFbits __attribute__((address(0x393)));
# 8295 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCBP __attribute__((address(0x394)));

__asm("IOCBP equ 0394h");


typedef union {
    struct {
        unsigned IOCBP0 :1;
        unsigned IOCBP1 :1;
        unsigned IOCBP2 :1;
        unsigned IOCBP3 :1;
        unsigned IOCBP4 :1;
        unsigned IOCBP5 :1;
        unsigned IOCBP6 :1;
        unsigned IOCBP7 :1;
    };
} IOCBPbits_t;
extern volatile IOCBPbits_t IOCBPbits __attribute__((address(0x394)));
# 8357 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCBN __attribute__((address(0x395)));

__asm("IOCBN equ 0395h");


typedef union {
    struct {
        unsigned IOCBN0 :1;
        unsigned IOCBN1 :1;
        unsigned IOCBN2 :1;
        unsigned IOCBN3 :1;
        unsigned IOCBN4 :1;
        unsigned IOCBN5 :1;
        unsigned IOCBN6 :1;
        unsigned IOCBN7 :1;
    };
} IOCBNbits_t;
extern volatile IOCBNbits_t IOCBNbits __attribute__((address(0x395)));
# 8419 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCBF __attribute__((address(0x396)));

__asm("IOCBF equ 0396h");


typedef union {
    struct {
        unsigned IOCBF0 :1;
        unsigned IOCBF1 :1;
        unsigned IOCBF2 :1;
        unsigned IOCBF3 :1;
        unsigned IOCBF4 :1;
        unsigned IOCBF5 :1;
        unsigned IOCBF6 :1;
        unsigned IOCBF7 :1;
    };
} IOCBFbits_t;
extern volatile IOCBFbits_t IOCBFbits __attribute__((address(0x396)));
# 8481 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCCP __attribute__((address(0x397)));

__asm("IOCCP equ 0397h");


typedef union {
    struct {
        unsigned IOCCP0 :1;
        unsigned IOCCP1 :1;
        unsigned IOCCP2 :1;
        unsigned IOCCP3 :1;
        unsigned IOCCP4 :1;
        unsigned IOCCP5 :1;
        unsigned IOCCP6 :1;
        unsigned IOCCP7 :1;
    };
} IOCCPbits_t;
extern volatile IOCCPbits_t IOCCPbits __attribute__((address(0x397)));
# 8543 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCCN __attribute__((address(0x398)));

__asm("IOCCN equ 0398h");


typedef union {
    struct {
        unsigned IOCCN0 :1;
        unsigned IOCCN1 :1;
        unsigned IOCCN2 :1;
        unsigned IOCCN3 :1;
        unsigned IOCCN4 :1;
        unsigned IOCCN5 :1;
        unsigned IOCCN6 :1;
        unsigned IOCCN7 :1;
    };
} IOCCNbits_t;
extern volatile IOCCNbits_t IOCCNbits __attribute__((address(0x398)));
# 8605 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCCF __attribute__((address(0x399)));

__asm("IOCCF equ 0399h");


typedef union {
    struct {
        unsigned IOCCF0 :1;
        unsigned IOCCF1 :1;
        unsigned IOCCF2 :1;
        unsigned IOCCF3 :1;
        unsigned IOCCF4 :1;
        unsigned IOCCF5 :1;
        unsigned IOCCF6 :1;
        unsigned IOCCF7 :1;
    };
} IOCCFbits_t;
extern volatile IOCCFbits_t IOCCFbits __attribute__((address(0x399)));
# 8667 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCEP __attribute__((address(0x39D)));

__asm("IOCEP equ 039Dh");


typedef union {
    struct {
        unsigned :3;
        unsigned IOCEP3 :1;
    };
} IOCEPbits_t;
extern volatile IOCEPbits_t IOCEPbits __attribute__((address(0x39D)));
# 8688 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCEN __attribute__((address(0x39E)));

__asm("IOCEN equ 039Eh");


typedef union {
    struct {
        unsigned :3;
        unsigned IOCEN3 :1;
    };
} IOCENbits_t;
extern volatile IOCENbits_t IOCENbits __attribute__((address(0x39E)));
# 8709 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char IOCEF __attribute__((address(0x39F)));

__asm("IOCEF equ 039Fh");


typedef union {
    struct {
        unsigned :3;
        unsigned IOCEF3 :1;
    };
} IOCEFbits_t;
extern volatile IOCEFbits_t IOCEFbits __attribute__((address(0x39F)));
# 8730 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TMR4 __attribute__((address(0x415)));

__asm("TMR4 equ 0415h");


typedef union {
    struct {
        unsigned TMR4 :8;
    };
} TMR4bits_t;
extern volatile TMR4bits_t TMR4bits __attribute__((address(0x415)));
# 8750 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PR4 __attribute__((address(0x416)));

__asm("PR4 equ 0416h");


typedef union {
    struct {
        unsigned PR4 :8;
    };
} PR4bits_t;
extern volatile PR4bits_t PR4bits __attribute__((address(0x416)));
# 8770 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T4CON __attribute__((address(0x417)));

__asm("T4CON equ 0417h");


typedef union {
    struct {
        unsigned T4CKPS :2;
        unsigned TMR4ON :1;
        unsigned T4OUTPS :4;
    };
    struct {
        unsigned T4CKPS0 :1;
        unsigned T4CKPS1 :1;
        unsigned :1;
        unsigned T4OUTPS0 :1;
        unsigned T4OUTPS1 :1;
        unsigned T4OUTPS2 :1;
        unsigned T4OUTPS3 :1;
    };
} T4CONbits_t;
extern volatile T4CONbits_t T4CONbits __attribute__((address(0x417)));
# 8841 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TMR6 __attribute__((address(0x41C)));

__asm("TMR6 equ 041Ch");


typedef union {
    struct {
        unsigned TMR6 :8;
    };
} TMR6bits_t;
extern volatile TMR6bits_t TMR6bits __attribute__((address(0x41C)));
# 8861 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PR6 __attribute__((address(0x41D)));

__asm("PR6 equ 041Dh");


typedef union {
    struct {
        unsigned PR6 :8;
    };
} PR6bits_t;
extern volatile PR6bits_t PR6bits __attribute__((address(0x41D)));
# 8881 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T6CON __attribute__((address(0x41E)));

__asm("T6CON equ 041Eh");


typedef union {
    struct {
        unsigned T6CKPS :2;
        unsigned TMR6ON :1;
        unsigned T6OUTPS :4;
    };
    struct {
        unsigned T6CKPS0 :1;
        unsigned T6CKPS1 :1;
        unsigned :1;
        unsigned T6OUTPS0 :1;
        unsigned T6OUTPS1 :1;
        unsigned T6OUTPS2 :1;
        unsigned T6OUTPS3 :1;
    };
} T6CONbits_t;
extern volatile T6CONbits_t T6CONbits __attribute__((address(0x41E)));
# 8953 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile __uint24 NCO1ACC __attribute__((address(0x498)));


__asm("NCO1ACC equ 0498h");




extern volatile unsigned char NCO1ACCL __attribute__((address(0x498)));

__asm("NCO1ACCL equ 0498h");


typedef union {
    struct {
        unsigned NCO1ACC0 :1;
        unsigned NCO1ACC1 :1;
        unsigned NCO1ACC2 :1;
        unsigned NCO1ACC3 :1;
        unsigned NCO1ACC4 :1;
        unsigned NCO1ACC5 :1;
        unsigned NCO1ACC6 :1;
        unsigned NCO1ACC7 :1;
    };
    struct {
        unsigned NCO1ACC :8;
    };
} NCO1ACCLbits_t;
extern volatile NCO1ACCLbits_t NCO1ACCLbits __attribute__((address(0x498)));
# 9031 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1ACCH __attribute__((address(0x499)));

__asm("NCO1ACCH equ 0499h");


typedef union {
    struct {
        unsigned NCO1ACC8 :1;
        unsigned NCO1ACC9 :1;
        unsigned NCO1ACC10 :1;
        unsigned NCO1ACC11 :1;
        unsigned NCO1ACC12 :1;
        unsigned NCO1ACC13 :1;
        unsigned NCO1ACC14 :1;
        unsigned NCO1ACC15 :1;
    };
    struct {
        unsigned NCO1ACC :8;
    };
} NCO1ACCHbits_t;
extern volatile NCO1ACCHbits_t NCO1ACCHbits __attribute__((address(0x499)));
# 9101 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1ACCU __attribute__((address(0x49A)));

__asm("NCO1ACCU equ 049Ah");


typedef union {
    struct {
        unsigned NCO1ACC16 :1;
        unsigned NCO1ACC17 :1;
        unsigned NCO1ACC18 :1;
        unsigned NCO1ACC19 :1;
    };
    struct {
        unsigned NCO1ACC :8;
    };
} NCO1ACCUbits_t;
extern volatile NCO1ACCUbits_t NCO1ACCUbits __attribute__((address(0x49A)));
# 9148 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile __uint24 NCO1INC __attribute__((address(0x49B)));


__asm("NCO1INC equ 049Bh");




extern volatile unsigned char NCO1INCL __attribute__((address(0x49B)));

__asm("NCO1INCL equ 049Bh");


typedef union {
    struct {
        unsigned NCO1INC0 :1;
        unsigned NCO1INC1 :1;
        unsigned NCO1INC2 :1;
        unsigned NCO1INC3 :1;
        unsigned NCO1INC4 :1;
        unsigned NCO1INC5 :1;
        unsigned NCO1INC6 :1;
        unsigned NCO1INC7 :1;
    };
    struct {
        unsigned NCO1INC :8;
    };
} NCO1INCLbits_t;
extern volatile NCO1INCLbits_t NCO1INCLbits __attribute__((address(0x49B)));
# 9226 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1INCH __attribute__((address(0x49C)));

__asm("NCO1INCH equ 049Ch");


typedef union {
    struct {
        unsigned NCO1INC8 :1;
        unsigned NCO1INC9 :1;
        unsigned NCO1INC10 :1;
        unsigned NCO1INC11 :1;
        unsigned NCO1INC12 :1;
        unsigned NCO1INC13 :1;
        unsigned NCO1INC14 :1;
        unsigned NCO1INC15 :1;
    };
    struct {
        unsigned NCO1INC :8;
    };
} NCO1INCHbits_t;
extern volatile NCO1INCHbits_t NCO1INCHbits __attribute__((address(0x49C)));
# 9296 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1INCU __attribute__((address(0x49D)));

__asm("NCO1INCU equ 049Dh");


typedef union {
    struct {
        unsigned NCO1INC16 :1;
        unsigned NCO1INC17 :1;
        unsigned NCO1INC18 :1;
        unsigned NCO1INC19 :1;
    };
    struct {
        unsigned NCO1INC :8;
    };
} NCO1INCUbits_t;
extern volatile NCO1INCUbits_t NCO1INCUbits __attribute__((address(0x49D)));
# 9342 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1CON __attribute__((address(0x49E)));

__asm("NCO1CON equ 049Eh");


typedef union {
    struct {
        unsigned N1PFM :1;
        unsigned :3;
        unsigned N1POL :1;
        unsigned N1OUT :1;
        unsigned :1;
        unsigned N1EN :1;
    };
} NCO1CONbits_t;
extern volatile NCO1CONbits_t NCO1CONbits __attribute__((address(0x49E)));
# 9382 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char NCO1CLK __attribute__((address(0x49F)));

__asm("NCO1CLK equ 049Fh");


typedef union {
    struct {
        unsigned N1CKS0 :1;
        unsigned N1CKS1 :1;
        unsigned :3;
        unsigned N1PWS0 :1;
        unsigned N1PWS1 :1;
        unsigned N1PWS2 :1;
    };
    struct {
        unsigned N1CKS :4;
        unsigned :1;
        unsigned N1PWS :3;
    };
} NCO1CLKbits_t;
extern volatile NCO1CLKbits_t NCO1CLKbits __attribute__((address(0x49F)));
# 9442 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OPA1CON __attribute__((address(0x511)));

__asm("OPA1CON equ 0511h");


typedef union {
    struct {
        unsigned OPA1CH :2;
        unsigned :2;
        unsigned OPA1UG :1;
        unsigned :1;
        unsigned OPA1SP :1;
        unsigned OPA1EN :1;
    };
    struct {
        unsigned OPA1CH0 :1;
        unsigned OPA1CH1 :1;
    };
    struct {
        unsigned OPA1PCH :2;
    };
    struct {
        unsigned OPA1PCH0 :1;
        unsigned OPA1PCH1 :1;
    };
} OPA1CONbits_t;
extern volatile OPA1CONbits_t OPA1CONbits __attribute__((address(0x511)));
# 9518 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char OPA2CON __attribute__((address(0x515)));

__asm("OPA2CON equ 0515h");


typedef union {
    struct {
        unsigned OPA2CH :2;
        unsigned :2;
        unsigned OPA2UG :1;
        unsigned :1;
        unsigned OPA2SP :1;
        unsigned OPA2EN :1;
    };
    struct {
        unsigned OPA2CH0 :1;
        unsigned OPA2CH1 :1;
    };
    struct {
        unsigned OPA2PCH :2;
    };
    struct {
        unsigned OPA2PCH0 :1;
        unsigned OPA2PCH1 :1;
    };
} OPA2CONbits_t;
extern volatile OPA2CONbits_t OPA2CONbits __attribute__((address(0x515)));
# 9594 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM3DCL __attribute__((address(0x617)));

__asm("PWM3DCL equ 0617h");


typedef union {
    struct {
        unsigned :6;
        unsigned PWM3DCL :2;
    };
    struct {
        unsigned :6;
        unsigned PWM3DCL0 :1;
        unsigned PWM3DCL1 :1;
    };
} PWM3DCLbits_t;
extern volatile PWM3DCLbits_t PWM3DCLbits __attribute__((address(0x617)));
# 9630 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM3DCH __attribute__((address(0x618)));

__asm("PWM3DCH equ 0618h");


typedef union {
    struct {
        unsigned PWM3DCH :8;
    };
    struct {
        unsigned PWM3DCH0 :1;
        unsigned PWM3DCH1 :1;
        unsigned PWM3DCH2 :1;
        unsigned PWM3DCH3 :1;
        unsigned PWM3DCH4 :1;
        unsigned PWM3DCH5 :1;
        unsigned PWM3DCH6 :1;
        unsigned PWM3DCH7 :1;
    };
} PWM3DCHbits_t;
extern volatile PWM3DCHbits_t PWM3DCHbits __attribute__((address(0x618)));
# 9700 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM3CON __attribute__((address(0x619)));

__asm("PWM3CON equ 0619h");


extern volatile unsigned char PWM3CON0 __attribute__((address(0x619)));

__asm("PWM3CON0 equ 0619h");


typedef union {
    struct {
        unsigned :4;
        unsigned PWM3POL :1;
        unsigned PWM3OUT :1;
        unsigned :1;
        unsigned PWM3EN :1;
    };
} PWM3CONbits_t;
extern volatile PWM3CONbits_t PWM3CONbits __attribute__((address(0x619)));
# 9737 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned :4;
        unsigned PWM3POL :1;
        unsigned PWM3OUT :1;
        unsigned :1;
        unsigned PWM3EN :1;
    };
} PWM3CON0bits_t;
extern volatile PWM3CON0bits_t PWM3CON0bits __attribute__((address(0x619)));
# 9766 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM4DCL __attribute__((address(0x61A)));

__asm("PWM4DCL equ 061Ah");


typedef union {
    struct {
        unsigned :6;
        unsigned PWM4DCL :2;
    };
    struct {
        unsigned :6;
        unsigned PWM4DCL0 :1;
        unsigned PWM4DCL1 :1;
    };
} PWM4DCLbits_t;
extern volatile PWM4DCLbits_t PWM4DCLbits __attribute__((address(0x61A)));
# 9802 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM4DCH __attribute__((address(0x61B)));

__asm("PWM4DCH equ 061Bh");


typedef union {
    struct {
        unsigned PWM4DCH :8;
    };
    struct {
        unsigned PWM4DCH0 :1;
        unsigned PWM4DCH1 :1;
        unsigned PWM4DCH2 :1;
        unsigned PWM4DCH3 :1;
        unsigned PWM4DCH4 :1;
        unsigned PWM4DCH5 :1;
        unsigned PWM4DCH6 :1;
        unsigned PWM4DCH7 :1;
    };
} PWM4DCHbits_t;
extern volatile PWM4DCHbits_t PWM4DCHbits __attribute__((address(0x61B)));
# 9872 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PWM4CON __attribute__((address(0x61C)));

__asm("PWM4CON equ 061Ch");


extern volatile unsigned char PWM4CON0 __attribute__((address(0x61C)));

__asm("PWM4CON0 equ 061Ch");


typedef union {
    struct {
        unsigned :4;
        unsigned PWM4POL :1;
        unsigned PWM4OUT :1;
        unsigned :1;
        unsigned PWM4EN :1;
    };
} PWM4CONbits_t;
extern volatile PWM4CONbits_t PWM4CONbits __attribute__((address(0x61C)));
# 9909 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
typedef union {
    struct {
        unsigned :4;
        unsigned PWM4POL :1;
        unsigned PWM4OUT :1;
        unsigned :1;
        unsigned PWM4EN :1;
    };
} PWM4CON0bits_t;
extern volatile PWM4CON0bits_t PWM4CON0bits __attribute__((address(0x61C)));
# 9938 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1PHR __attribute__((address(0x691)));

__asm("COG1PHR equ 0691h");


typedef union {
    struct {
        unsigned G1PHR :6;
    };
    struct {
        unsigned G1PHR0 :1;
        unsigned G1PHR1 :1;
        unsigned G1PHR2 :1;
        unsigned G1PHR3 :1;
        unsigned G1PHR4 :1;
        unsigned G1PHR5 :1;
    };
} COG1PHRbits_t;
extern volatile COG1PHRbits_t COG1PHRbits __attribute__((address(0x691)));
# 9996 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1PHF __attribute__((address(0x692)));

__asm("COG1PHF equ 0692h");


typedef union {
    struct {
        unsigned G1PHF :6;
    };
    struct {
        unsigned G1PHF0 :1;
        unsigned G1PHF1 :1;
        unsigned G1PHF2 :1;
        unsigned G1PHF3 :1;
        unsigned G1PHF4 :1;
        unsigned G1PHF5 :1;
    };
} COG1PHFbits_t;
extern volatile COG1PHFbits_t COG1PHFbits __attribute__((address(0x692)));
# 10054 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1BLKR __attribute__((address(0x693)));

__asm("COG1BLKR equ 0693h");


typedef union {
    struct {
        unsigned G1BLKR :6;
    };
    struct {
        unsigned G1BLKR0 :1;
        unsigned G1BLKR1 :1;
        unsigned G1BLKR2 :1;
        unsigned G1BLKR3 :1;
        unsigned G1BLKR4 :1;
        unsigned G1BLKR5 :1;
    };
} COG1BLKRbits_t;
extern volatile COG1BLKRbits_t COG1BLKRbits __attribute__((address(0x693)));
# 10112 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1BLKF __attribute__((address(0x694)));

__asm("COG1BLKF equ 0694h");


typedef union {
    struct {
        unsigned G1BLKF :6;
    };
    struct {
        unsigned G1BLKF0 :1;
        unsigned G1BLKF1 :1;
        unsigned G1BLKF2 :1;
        unsigned G1BLKF3 :1;
        unsigned G1BLKF4 :1;
        unsigned G1BLKF5 :1;
    };
} COG1BLKFbits_t;
extern volatile COG1BLKFbits_t COG1BLKFbits __attribute__((address(0x694)));
# 10170 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1DBR __attribute__((address(0x695)));

__asm("COG1DBR equ 0695h");


typedef union {
    struct {
        unsigned G1DBR :6;
    };
    struct {
        unsigned G1DBR0 :1;
        unsigned G1DBR1 :1;
        unsigned G1DBR2 :1;
        unsigned G1DBR3 :1;
        unsigned G1DBR4 :1;
        unsigned G1DBR5 :1;
    };
} COG1DBRbits_t;
extern volatile COG1DBRbits_t COG1DBRbits __attribute__((address(0x695)));
# 10228 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1DBF __attribute__((address(0x696)));

__asm("COG1DBF equ 0696h");


typedef union {
    struct {
        unsigned G1DBF :6;
    };
    struct {
        unsigned G1DBF0 :1;
        unsigned G1DBF1 :1;
        unsigned G1DBF2 :1;
        unsigned G1DBF3 :1;
        unsigned G1DBF4 :1;
        unsigned G1DBF5 :1;
    };
} COG1DBFbits_t;
extern volatile COG1DBFbits_t COG1DBFbits __attribute__((address(0x696)));
# 10286 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1CON0 __attribute__((address(0x697)));

__asm("COG1CON0 equ 0697h");


typedef union {
    struct {
        unsigned G1MD :3;
        unsigned G1CS :2;
        unsigned :1;
        unsigned G1LD :1;
        unsigned G1EN :1;
    };
    struct {
        unsigned G1MD0 :1;
        unsigned G1MD1 :1;
        unsigned G1MD2 :1;
        unsigned G1CS0 :1;
        unsigned G1CS1 :1;
    };
} COG1CON0bits_t;
extern volatile COG1CON0bits_t COG1CON0bits __attribute__((address(0x697)));
# 10357 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1CON1 __attribute__((address(0x698)));

__asm("COG1CON1 equ 0698h");


typedef union {
    struct {
        unsigned G1POLA :1;
        unsigned G1POLB :1;
        unsigned G1POLC :1;
        unsigned G1POLD :1;
        unsigned :2;
        unsigned G1FDBS :1;
        unsigned G1RDBS :1;
    };
} COG1CON1bits_t;
extern volatile COG1CON1bits_t COG1CON1bits __attribute__((address(0x698)));
# 10408 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1RIS __attribute__((address(0x699)));

__asm("COG1RIS equ 0699h");


typedef union {
    struct {
        unsigned G1RIS0 :1;
        unsigned G1RIS1 :1;
        unsigned G1RIS2 :1;
        unsigned G1RIS3 :1;
        unsigned G1RIS4 :1;
        unsigned G1RIS5 :1;
        unsigned G1RIS6 :1;
        unsigned G1RIS7 :1;
    };
} COG1RISbits_t;
extern volatile COG1RISbits_t COG1RISbits __attribute__((address(0x699)));
# 10470 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1RSIM __attribute__((address(0x69A)));

__asm("COG1RSIM equ 069Ah");


typedef union {
    struct {
        unsigned G1RSIM0 :1;
        unsigned G1RSIM1 :1;
        unsigned G1RSIM2 :1;
        unsigned G1RSIM3 :1;
        unsigned G1RSIM4 :1;
        unsigned G1RSIM5 :1;
        unsigned G1RSIM6 :1;
        unsigned G1RSIM7 :1;
    };
} COG1RSIMbits_t;
extern volatile COG1RSIMbits_t COG1RSIMbits __attribute__((address(0x69A)));
# 10532 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1FIS __attribute__((address(0x69B)));

__asm("COG1FIS equ 069Bh");


typedef union {
    struct {
        unsigned G1FIS0 :1;
        unsigned G1FIS1 :1;
        unsigned G1FIS2 :1;
        unsigned G1FIS3 :1;
        unsigned G1FIS4 :1;
        unsigned G1FIS5 :1;
        unsigned G1FIS6 :1;
        unsigned G1FIS7 :1;
    };
} COG1FISbits_t;
extern volatile COG1FISbits_t COG1FISbits __attribute__((address(0x69B)));
# 10594 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1FSIM __attribute__((address(0x69C)));

__asm("COG1FSIM equ 069Ch");


typedef union {
    struct {
        unsigned G1FSIM0 :1;
        unsigned G1FSIM1 :1;
        unsigned G1FSIM2 :1;
        unsigned G1FSIM3 :1;
        unsigned G1FSIM4 :1;
        unsigned G1FSIM5 :1;
        unsigned G1FSIM6 :1;
        unsigned G1FSIM7 :1;
    };
} COG1FSIMbits_t;
extern volatile COG1FSIMbits_t COG1FSIMbits __attribute__((address(0x69C)));
# 10656 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1ASD0 __attribute__((address(0x69D)));

__asm("COG1ASD0 equ 069Dh");


typedef union {
    struct {
        unsigned :2;
        unsigned G1ASDAC :2;
        unsigned G1ASDBD :2;
        unsigned G1ARSEN :1;
        unsigned G1ASE :1;
    };
    struct {
        unsigned :2;
        unsigned G1ASDAC0 :1;
        unsigned G1ASDAC1 :1;
        unsigned G1ASDBD0 :1;
        unsigned G1ASDBD1 :1;
    };
} COG1ASD0bits_t;
extern volatile COG1ASD0bits_t COG1ASD0bits __attribute__((address(0x69D)));
# 10722 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1ASD1 __attribute__((address(0x69E)));

__asm("COG1ASD1 equ 069Eh");


typedef union {
    struct {
        unsigned G1AS0E :1;
        unsigned G1AS1E :1;
        unsigned G1AS2E :1;
        unsigned G1AS3E :1;
    };
} COG1ASD1bits_t;
extern volatile COG1ASD1bits_t COG1ASD1bits __attribute__((address(0x69E)));
# 10760 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COG1STR __attribute__((address(0x69F)));

__asm("COG1STR equ 069Fh");


typedef union {
    struct {
        unsigned G1STRA :1;
        unsigned G1STRB :1;
        unsigned G1STRC :1;
        unsigned G1STRD :1;
        unsigned G1SDATA :1;
        unsigned G1SDATB :1;
        unsigned G1SDATC :1;
        unsigned G1SDATD :1;
    };
} COG1STRbits_t;
extern volatile COG1STRbits_t COG1STRbits __attribute__((address(0x69F)));
# 10822 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PPSLOCK __attribute__((address(0xE0F)));

__asm("PPSLOCK equ 0E0Fh");


typedef union {
    struct {
        unsigned PPSLOCKED :1;
    };
} PPSLOCKbits_t;
extern volatile PPSLOCKbits_t PPSLOCKbits __attribute__((address(0xE0F)));
# 10842 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char INTPPS __attribute__((address(0xE10)));

__asm("INTPPS equ 0E10h");


typedef union {
    struct {
        unsigned INTPPS :5;
    };
} INTPPSbits_t;
extern volatile INTPPSbits_t INTPPSbits __attribute__((address(0xE10)));
# 10862 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T0CKIPPS __attribute__((address(0xE11)));

__asm("T0CKIPPS equ 0E11h");


typedef union {
    struct {
        unsigned T0CKIPPS :5;
    };
} T0CKIPPSbits_t;
extern volatile T0CKIPPSbits_t T0CKIPPSbits __attribute__((address(0xE11)));
# 10882 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T1CKIPPS __attribute__((address(0xE12)));

__asm("T1CKIPPS equ 0E12h");


typedef union {
    struct {
        unsigned T1CKIPPS :5;
    };
} T1CKIPPSbits_t;
extern volatile T1CKIPPSbits_t T1CKIPPSbits __attribute__((address(0xE12)));
# 10902 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char T1GPPS __attribute__((address(0xE13)));

__asm("T1GPPS equ 0E13h");


typedef union {
    struct {
        unsigned T1GPPS :5;
    };
} T1GPPSbits_t;
extern volatile T1GPPSbits_t T1GPPSbits __attribute__((address(0xE13)));
# 10922 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCP1PPS __attribute__((address(0xE14)));

__asm("CCP1PPS equ 0E14h");


typedef union {
    struct {
        unsigned CCP1PPS :5;
    };
} CCP1PPSbits_t;
extern volatile CCP1PPSbits_t CCP1PPSbits __attribute__((address(0xE14)));
# 10942 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CCP2PPS __attribute__((address(0xE15)));

__asm("CCP2PPS equ 0E15h");


typedef union {
    struct {
        unsigned CCP2PPS :5;
    };
} CCP2PPSbits_t;
extern volatile CCP2PPSbits_t CCP2PPSbits __attribute__((address(0xE15)));
# 10962 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char COGINPPS __attribute__((address(0xE17)));

__asm("COGINPPS equ 0E17h");


typedef union {
    struct {
        unsigned COGINPPS :5;
    };
} COGINPPSbits_t;
extern volatile COGINPPSbits_t COGINPPSbits __attribute__((address(0xE17)));
# 10982 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSPCLKPPS __attribute__((address(0xE20)));

__asm("SSPCLKPPS equ 0E20h");


typedef union {
    struct {
        unsigned SSPCLKPPS :5;
    };
} SSPCLKPPSbits_t;
extern volatile SSPCLKPPSbits_t SSPCLKPPSbits __attribute__((address(0xE20)));
# 11002 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSPDATPPS __attribute__((address(0xE21)));

__asm("SSPDATPPS equ 0E21h");


typedef union {
    struct {
        unsigned SSPDATPPS :5;
    };
} SSPDATPPSbits_t;
extern volatile SSPDATPPSbits_t SSPDATPPSbits __attribute__((address(0xE21)));
# 11022 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char SSPSSPPS __attribute__((address(0xE22)));

__asm("SSPSSPPS equ 0E22h");


typedef union {
    struct {
        unsigned SSPSSPPS :5;
    };
} SSPSSPPSbits_t;
extern volatile SSPSSPPSbits_t SSPSSPPSbits __attribute__((address(0xE22)));
# 11042 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RXPPS __attribute__((address(0xE24)));

__asm("RXPPS equ 0E24h");


typedef union {
    struct {
        unsigned RXPPS :5;
    };
} RXPPSbits_t;
extern volatile RXPPSbits_t RXPPSbits __attribute__((address(0xE24)));
# 11062 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CKPPS __attribute__((address(0xE25)));

__asm("CKPPS equ 0E25h");


typedef union {
    struct {
        unsigned CKPPS :5;
    };
} CKPPSbits_t;
extern volatile CKPPSbits_t CKPPSbits __attribute__((address(0xE25)));
# 11082 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLCIN0PPS __attribute__((address(0xE28)));

__asm("CLCIN0PPS equ 0E28h");


typedef union {
    struct {
        unsigned CLCIN0PPS :5;
    };
} CLCIN0PPSbits_t;
extern volatile CLCIN0PPSbits_t CLCIN0PPSbits __attribute__((address(0xE28)));
# 11102 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLCIN1PPS __attribute__((address(0xE29)));

__asm("CLCIN1PPS equ 0E29h");


typedef union {
    struct {
        unsigned CLCIN1PPS :5;
    };
} CLCIN1PPSbits_t;
extern volatile CLCIN1PPSbits_t CLCIN1PPSbits __attribute__((address(0xE29)));
# 11122 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLCIN2PPS __attribute__((address(0xE2A)));

__asm("CLCIN2PPS equ 0E2Ah");


typedef union {
    struct {
        unsigned CLCIN2PPS :5;
    };
} CLCIN2PPSbits_t;
extern volatile CLCIN2PPSbits_t CLCIN2PPSbits __attribute__((address(0xE2A)));
# 11142 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLCIN3PPS __attribute__((address(0xE2B)));

__asm("CLCIN3PPS equ 0E2Bh");


typedef union {
    struct {
        unsigned CLCIN3PPS :5;
    };
} CLCIN3PPSbits_t;
extern volatile CLCIN3PPSbits_t CLCIN3PPSbits __attribute__((address(0xE2B)));
# 11162 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA0PPS __attribute__((address(0xE90)));

__asm("RA0PPS equ 0E90h");


typedef union {
    struct {
        unsigned RA0PPS :5;
    };
} RA0PPSbits_t;
extern volatile RA0PPSbits_t RA0PPSbits __attribute__((address(0xE90)));
# 11182 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA1PPS __attribute__((address(0xE91)));

__asm("RA1PPS equ 0E91h");


typedef union {
    struct {
        unsigned RA1PPS :5;
    };
} RA1PPSbits_t;
extern volatile RA1PPSbits_t RA1PPSbits __attribute__((address(0xE91)));
# 11202 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA2PPS __attribute__((address(0xE92)));

__asm("RA2PPS equ 0E92h");


typedef union {
    struct {
        unsigned RA2PPS :5;
    };
} RA2PPSbits_t;
extern volatile RA2PPSbits_t RA2PPSbits __attribute__((address(0xE92)));
# 11222 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA3PPS __attribute__((address(0xE93)));

__asm("RA3PPS equ 0E93h");


typedef union {
    struct {
        unsigned RA3PPS :5;
    };
} RA3PPSbits_t;
extern volatile RA3PPSbits_t RA3PPSbits __attribute__((address(0xE93)));
# 11242 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA4PPS __attribute__((address(0xE94)));

__asm("RA4PPS equ 0E94h");


typedef union {
    struct {
        unsigned RA4PPS :5;
    };
} RA4PPSbits_t;
extern volatile RA4PPSbits_t RA4PPSbits __attribute__((address(0xE94)));
# 11262 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA5PPS __attribute__((address(0xE95)));

__asm("RA5PPS equ 0E95h");


typedef union {
    struct {
        unsigned RA5PPS :5;
    };
} RA5PPSbits_t;
extern volatile RA5PPSbits_t RA5PPSbits __attribute__((address(0xE95)));
# 11282 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA6PPS __attribute__((address(0xE96)));

__asm("RA6PPS equ 0E96h");


typedef union {
    struct {
        unsigned RA6PPS :5;
    };
} RA6PPSbits_t;
extern volatile RA6PPSbits_t RA6PPSbits __attribute__((address(0xE96)));
# 11302 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RA7PPS __attribute__((address(0xE97)));

__asm("RA7PPS equ 0E97h");


typedef union {
    struct {
        unsigned RA7PPS :5;
    };
} RA7PPSbits_t;
extern volatile RA7PPSbits_t RA7PPSbits __attribute__((address(0xE97)));
# 11322 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB0PPS __attribute__((address(0xE98)));

__asm("RB0PPS equ 0E98h");


typedef union {
    struct {
        unsigned RB0PPS :5;
    };
} RB0PPSbits_t;
extern volatile RB0PPSbits_t RB0PPSbits __attribute__((address(0xE98)));
# 11342 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB1PPS __attribute__((address(0xE99)));

__asm("RB1PPS equ 0E99h");


typedef union {
    struct {
        unsigned RB1PPS :5;
    };
} RB1PPSbits_t;
extern volatile RB1PPSbits_t RB1PPSbits __attribute__((address(0xE99)));
# 11362 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB2PPS __attribute__((address(0xE9A)));

__asm("RB2PPS equ 0E9Ah");


typedef union {
    struct {
        unsigned RB2PPS :5;
    };
} RB2PPSbits_t;
extern volatile RB2PPSbits_t RB2PPSbits __attribute__((address(0xE9A)));
# 11382 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB3PPS __attribute__((address(0xE9B)));

__asm("RB3PPS equ 0E9Bh");


typedef union {
    struct {
        unsigned RB3PPS :5;
    };
} RB3PPSbits_t;
extern volatile RB3PPSbits_t RB3PPSbits __attribute__((address(0xE9B)));
# 11402 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB4PPS __attribute__((address(0xE9C)));

__asm("RB4PPS equ 0E9Ch");


typedef union {
    struct {
        unsigned RB4PPS :5;
    };
} RB4PPSbits_t;
extern volatile RB4PPSbits_t RB4PPSbits __attribute__((address(0xE9C)));
# 11422 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB5PPS __attribute__((address(0xE9D)));

__asm("RB5PPS equ 0E9Dh");


typedef union {
    struct {
        unsigned RB5PPS :5;
    };
} RB5PPSbits_t;
extern volatile RB5PPSbits_t RB5PPSbits __attribute__((address(0xE9D)));
# 11442 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB6PPS __attribute__((address(0xE9E)));

__asm("RB6PPS equ 0E9Eh");


typedef union {
    struct {
        unsigned RB6PPS :5;
    };
} RB6PPSbits_t;
extern volatile RB6PPSbits_t RB6PPSbits __attribute__((address(0xE9E)));
# 11462 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RB7PPS __attribute__((address(0xE9F)));

__asm("RB7PPS equ 0E9Fh");


typedef union {
    struct {
        unsigned RB7PPS :5;
    };
} RB7PPSbits_t;
extern volatile RB7PPSbits_t RB7PPSbits __attribute__((address(0xE9F)));
# 11482 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC0PPS __attribute__((address(0xEA0)));

__asm("RC0PPS equ 0EA0h");


typedef union {
    struct {
        unsigned RC0PPS :5;
    };
} RC0PPSbits_t;
extern volatile RC0PPSbits_t RC0PPSbits __attribute__((address(0xEA0)));
# 11502 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC1PPS __attribute__((address(0xEA1)));

__asm("RC1PPS equ 0EA1h");


typedef union {
    struct {
        unsigned RC1PPS :5;
    };
} RC1PPSbits_t;
extern volatile RC1PPSbits_t RC1PPSbits __attribute__((address(0xEA1)));
# 11522 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC2PPS __attribute__((address(0xEA2)));

__asm("RC2PPS equ 0EA2h");


typedef union {
    struct {
        unsigned RC2PPS :5;
    };
} RC2PPSbits_t;
extern volatile RC2PPSbits_t RC2PPSbits __attribute__((address(0xEA2)));
# 11542 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC3PPS __attribute__((address(0xEA3)));

__asm("RC3PPS equ 0EA3h");


typedef union {
    struct {
        unsigned RC3PPS :5;
    };
} RC3PPSbits_t;
extern volatile RC3PPSbits_t RC3PPSbits __attribute__((address(0xEA3)));
# 11562 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC4PPS __attribute__((address(0xEA4)));

__asm("RC4PPS equ 0EA4h");


typedef union {
    struct {
        unsigned RC4PPS :5;
    };
} RC4PPSbits_t;
extern volatile RC4PPSbits_t RC4PPSbits __attribute__((address(0xEA4)));
# 11582 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC5PPS __attribute__((address(0xEA5)));

__asm("RC5PPS equ 0EA5h");


typedef union {
    struct {
        unsigned RC5PPS :5;
    };
} RC5PPSbits_t;
extern volatile RC5PPSbits_t RC5PPSbits __attribute__((address(0xEA5)));
# 11602 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC6PPS __attribute__((address(0xEA6)));

__asm("RC6PPS equ 0EA6h");


typedef union {
    struct {
        unsigned RC6PPS :5;
    };
} RC6PPSbits_t;
extern volatile RC6PPSbits_t RC6PPSbits __attribute__((address(0xEA6)));
# 11622 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RC7PPS __attribute__((address(0xEA7)));

__asm("RC7PPS equ 0EA7h");


typedef union {
    struct {
        unsigned RC7PPS :5;
    };
} RC7PPSbits_t;
extern volatile RC7PPSbits_t RC7PPSbits __attribute__((address(0xEA7)));
# 11642 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD0PPS __attribute__((address(0xEA8)));

__asm("RD0PPS equ 0EA8h");


typedef union {
    struct {
        unsigned RD0PPS :5;
    };
} RD0PPSbits_t;
extern volatile RD0PPSbits_t RD0PPSbits __attribute__((address(0xEA8)));
# 11662 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD1PPS __attribute__((address(0xEA9)));

__asm("RD1PPS equ 0EA9h");


typedef union {
    struct {
        unsigned RD1PPS :5;
    };
} RD1PPSbits_t;
extern volatile RD1PPSbits_t RD1PPSbits __attribute__((address(0xEA9)));
# 11682 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD2PPS __attribute__((address(0xEAA)));

__asm("RD2PPS equ 0EAAh");


typedef union {
    struct {
        unsigned RD2PPS :5;
    };
} RD2PPSbits_t;
extern volatile RD2PPSbits_t RD2PPSbits __attribute__((address(0xEAA)));
# 11702 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD3PPS __attribute__((address(0xEAB)));

__asm("RD3PPS equ 0EABh");


typedef union {
    struct {
        unsigned RD3PPS :5;
    };
} RD3PPSbits_t;
extern volatile RD3PPSbits_t RD3PPSbits __attribute__((address(0xEAB)));
# 11722 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD4PPS __attribute__((address(0xEAC)));

__asm("RD4PPS equ 0EACh");


typedef union {
    struct {
        unsigned RD4PPS :5;
    };
} RD4PPSbits_t;
extern volatile RD4PPSbits_t RD4PPSbits __attribute__((address(0xEAC)));
# 11742 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD5PPS __attribute__((address(0xEAD)));

__asm("RD5PPS equ 0EADh");


typedef union {
    struct {
        unsigned RD5PPS :5;
    };
} RD5PPSbits_t;
extern volatile RD5PPSbits_t RD5PPSbits __attribute__((address(0xEAD)));
# 11762 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD6PPS __attribute__((address(0xEAE)));

__asm("RD6PPS equ 0EAEh");


typedef union {
    struct {
        unsigned RD6PPS :5;
    };
} RD6PPSbits_t;
extern volatile RD6PPSbits_t RD6PPSbits __attribute__((address(0xEAE)));
# 11782 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RD7PPS __attribute__((address(0xEAF)));

__asm("RD7PPS equ 0EAFh");


typedef union {
    struct {
        unsigned RD7PPS :5;
    };
} RD7PPSbits_t;
extern volatile RD7PPSbits_t RD7PPSbits __attribute__((address(0xEAF)));
# 11802 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RE0PPS __attribute__((address(0xEB0)));

__asm("RE0PPS equ 0EB0h");


typedef union {
    struct {
        unsigned RE0PPS :5;
    };
} RE0PPSbits_t;
extern volatile RE0PPSbits_t RE0PPSbits __attribute__((address(0xEB0)));
# 11822 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RE1PPS __attribute__((address(0xEB1)));

__asm("RE1PPS equ 0EB1h");


typedef union {
    struct {
        unsigned RE1PPS :5;
    };
} RE1PPSbits_t;
extern volatile RE1PPSbits_t RE1PPSbits __attribute__((address(0xEB1)));
# 11842 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char RE2PPS __attribute__((address(0xEB2)));

__asm("RE2PPS equ 0EB2h");


typedef union {
    struct {
        unsigned RE2PPS :5;
    };
} RE2PPSbits_t;
extern volatile RE2PPSbits_t RE2PPSbits __attribute__((address(0xEB2)));
# 11862 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLCDATA __attribute__((address(0xF0F)));

__asm("CLCDATA equ 0F0Fh");


typedef union {
    struct {
        unsigned MLC1OUT :1;
        unsigned MLC2OUT :1;
        unsigned MLC3OUT :1;
        unsigned MLC4OUT :1;
    };
    struct {
        unsigned MCLC1OUT :1;
        unsigned MCLC2OUT :1;
        unsigned MCLC3OUT :1;
        unsigned MCLC4OUT :1;
    };
} CLCDATAbits_t;
extern volatile CLCDATAbits_t CLCDATAbits __attribute__((address(0xF0F)));
# 11926 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1CON __attribute__((address(0xF10)));

__asm("CLC1CON equ 0F10h");


typedef union {
    struct {
        unsigned LC1MODE :3;
        unsigned LC1INTN :1;
        unsigned LC1INTP :1;
        unsigned LC1OUT :1;
        unsigned :1;
        unsigned LC1EN :1;
    };
    struct {
        unsigned LC1MODE0 :1;
        unsigned LC1MODE1 :1;
        unsigned LC1MODE2 :1;
    };
    struct {
        unsigned MODE :3;
        unsigned INTN :1;
        unsigned INTP :1;
        unsigned OUT :1;
        unsigned :1;
        unsigned EN :1;
    };
    struct {
        unsigned MODE0 :1;
        unsigned MODE1 :1;
        unsigned MODE2 :1;
    };
} CLC1CONbits_t;
extern volatile CLC1CONbits_t CLC1CONbits __attribute__((address(0xF10)));
# 12044 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1POL __attribute__((address(0xF11)));

__asm("CLC1POL equ 0F11h");


typedef union {
    struct {
        unsigned LC1G1POL :1;
        unsigned LC1G2POL :1;
        unsigned LC1G3POL :1;
        unsigned LC1G4POL :1;
        unsigned :3;
        unsigned LC1POL :1;
    };
    struct {
        unsigned G1POL :1;
        unsigned G2POL :1;
        unsigned G3POL :1;
        unsigned G4POL :1;
        unsigned :3;
        unsigned POL :1;
    };
} CLC1POLbits_t;
extern volatile CLC1POLbits_t CLC1POLbits __attribute__((address(0xF11)));
# 12122 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1SEL0 __attribute__((address(0xF12)));

__asm("CLC1SEL0 equ 0F12h");


typedef union {
    struct {
        unsigned LC1D1S0 :1;
        unsigned LC1D1S1 :1;
        unsigned LC1D1S2 :1;
        unsigned LC1D1S3 :1;
        unsigned LC1D1S4 :1;
    };
    struct {
        unsigned LC1D1S :8;
    };
    struct {
        unsigned D1S :8;
    };
    struct {
        unsigned D1S0 :1;
        unsigned D1S1 :1;
        unsigned D1S2 :1;
        unsigned D1S3 :1;
        unsigned D1S4 :1;
    };
} CLC1SEL0bits_t;
extern volatile CLC1SEL0bits_t CLC1SEL0bits __attribute__((address(0xF12)));
# 12214 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1SEL1 __attribute__((address(0xF13)));

__asm("CLC1SEL1 equ 0F13h");


typedef union {
    struct {
        unsigned LC1D2S0 :1;
        unsigned LC1D2S1 :1;
        unsigned LC1D2S2 :1;
        unsigned LC1D2S3 :1;
        unsigned LC1D2S4 :1;
    };
    struct {
        unsigned LC1D2S :8;
    };
    struct {
        unsigned D2S :8;
    };
    struct {
        unsigned D2S0 :1;
        unsigned D2S1 :1;
        unsigned D2S2 :1;
        unsigned D2S3 :1;
        unsigned D2S4 :1;
    };
} CLC1SEL1bits_t;
extern volatile CLC1SEL1bits_t CLC1SEL1bits __attribute__((address(0xF13)));
# 12306 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1SEL2 __attribute__((address(0xF14)));

__asm("CLC1SEL2 equ 0F14h");


typedef union {
    struct {
        unsigned LC1D3S0 :1;
        unsigned LC1D3S1 :1;
        unsigned LC1D3S2 :1;
        unsigned LC1D3S3 :1;
        unsigned LC1D3S4 :1;
    };
    struct {
        unsigned LC1D3S :8;
    };
    struct {
        unsigned D3S :8;
    };
    struct {
        unsigned D3S0 :1;
        unsigned D3S1 :1;
        unsigned D3S2 :1;
        unsigned D3S3 :1;
        unsigned D3S4 :1;
    };
} CLC1SEL2bits_t;
extern volatile CLC1SEL2bits_t CLC1SEL2bits __attribute__((address(0xF14)));
# 12398 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1SEL3 __attribute__((address(0xF15)));

__asm("CLC1SEL3 equ 0F15h");


typedef union {
    struct {
        unsigned LC1D4S0 :1;
        unsigned LC1D4S1 :1;
        unsigned LC1D4S2 :1;
        unsigned LC1D4S3 :1;
        unsigned LC1D4S4 :1;
    };
    struct {
        unsigned LC1D4S :8;
    };
    struct {
        unsigned D4S :8;
    };
    struct {
        unsigned D4S0 :1;
        unsigned D4S1 :1;
        unsigned D4S2 :1;
        unsigned D4S3 :1;
        unsigned D4S4 :1;
    };
} CLC1SEL3bits_t;
extern volatile CLC1SEL3bits_t CLC1SEL3bits __attribute__((address(0xF15)));
# 12490 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1GLS0 __attribute__((address(0xF16)));

__asm("CLC1GLS0 equ 0F16h");


typedef union {
    struct {
        unsigned LC1G1D1N :1;
        unsigned LC1G1D1T :1;
        unsigned LC1G1D2N :1;
        unsigned LC1G1D2T :1;
        unsigned LC1G1D3N :1;
        unsigned LC1G1D3T :1;
        unsigned LC1G1D4N :1;
        unsigned LC1G1D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC1GLS0bits_t;
extern volatile CLC1GLS0bits_t CLC1GLS0bits __attribute__((address(0xF16)));
# 12602 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1GLS1 __attribute__((address(0xF17)));

__asm("CLC1GLS1 equ 0F17h");


typedef union {
    struct {
        unsigned LC1G2D1N :1;
        unsigned LC1G2D1T :1;
        unsigned LC1G2D2N :1;
        unsigned LC1G2D2T :1;
        unsigned LC1G2D3N :1;
        unsigned LC1G2D3T :1;
        unsigned LC1G2D4N :1;
        unsigned LC1G2D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC1GLS1bits_t;
extern volatile CLC1GLS1bits_t CLC1GLS1bits __attribute__((address(0xF17)));
# 12714 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1GLS2 __attribute__((address(0xF18)));

__asm("CLC1GLS2 equ 0F18h");


typedef union {
    struct {
        unsigned LC1G3D1N :1;
        unsigned LC1G3D1T :1;
        unsigned LC1G3D2N :1;
        unsigned LC1G3D2T :1;
        unsigned LC1G3D3N :1;
        unsigned LC1G3D3T :1;
        unsigned LC1G3D4N :1;
        unsigned LC1G3D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC1GLS2bits_t;
extern volatile CLC1GLS2bits_t CLC1GLS2bits __attribute__((address(0xF18)));
# 12826 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC1GLS3 __attribute__((address(0xF19)));

__asm("CLC1GLS3 equ 0F19h");


typedef union {
    struct {
        unsigned LC1G4D1N :1;
        unsigned LC1G4D1T :1;
        unsigned LC1G4D2N :1;
        unsigned LC1G4D2T :1;
        unsigned LC1G4D3N :1;
        unsigned LC1G4D3T :1;
        unsigned LC1G4D4N :1;
        unsigned LC1G4D4T :1;
    };
    struct {
        unsigned G4D1N :1;
        unsigned G4D1T :1;
        unsigned G4D2N :1;
        unsigned G4D2T :1;
        unsigned G4D3N :1;
        unsigned G4D3T :1;
        unsigned G4D4N :1;
        unsigned G4D4T :1;
    };
} CLC1GLS3bits_t;
extern volatile CLC1GLS3bits_t CLC1GLS3bits __attribute__((address(0xF19)));
# 12938 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2CON __attribute__((address(0xF1A)));

__asm("CLC2CON equ 0F1Ah");


typedef union {
    struct {
        unsigned LC2MODE :3;
        unsigned LC2INTN :1;
        unsigned LC2INTP :1;
        unsigned LC2OUT :1;
        unsigned :1;
        unsigned LC2EN :1;
    };
    struct {
        unsigned LC2MODE0 :1;
        unsigned LC2MODE1 :1;
        unsigned LC2MODE2 :1;
    };
    struct {
        unsigned MODE :3;
        unsigned INTN :1;
        unsigned INTP :1;
        unsigned OUT :1;
        unsigned :1;
        unsigned EN :1;
    };
    struct {
        unsigned MODE0 :1;
        unsigned MODE1 :1;
        unsigned MODE2 :1;
    };
} CLC2CONbits_t;
extern volatile CLC2CONbits_t CLC2CONbits __attribute__((address(0xF1A)));
# 13056 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2POL __attribute__((address(0xF1B)));

__asm("CLC2POL equ 0F1Bh");


typedef union {
    struct {
        unsigned LC2G1POL :1;
        unsigned LC2G2POL :1;
        unsigned LC2G3POL :1;
        unsigned LC2G4POL :1;
        unsigned :3;
        unsigned LC2POL :1;
    };
    struct {
        unsigned G1POL :1;
        unsigned G2POL :1;
        unsigned G3POL :1;
        unsigned G4POL :1;
        unsigned :3;
        unsigned POL :1;
    };
} CLC2POLbits_t;
extern volatile CLC2POLbits_t CLC2POLbits __attribute__((address(0xF1B)));
# 13134 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2SEL0 __attribute__((address(0xF1C)));

__asm("CLC2SEL0 equ 0F1Ch");


typedef union {
    struct {
        unsigned LC2D1S0 :1;
        unsigned LC2D1S1 :1;
        unsigned LC2D1S2 :1;
        unsigned LC2D1S3 :1;
        unsigned LC2D1S4 :1;
    };
    struct {
        unsigned LC2D1S :8;
    };
    struct {
        unsigned D1S :8;
    };
    struct {
        unsigned D1S0 :1;
        unsigned D1S1 :1;
        unsigned D1S2 :1;
        unsigned D1S3 :1;
        unsigned D1S4 :1;
    };
} CLC2SEL0bits_t;
extern volatile CLC2SEL0bits_t CLC2SEL0bits __attribute__((address(0xF1C)));
# 13226 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2SEL1 __attribute__((address(0xF1D)));

__asm("CLC2SEL1 equ 0F1Dh");


typedef union {
    struct {
        unsigned LC2D2S0 :1;
        unsigned LC2D2S1 :1;
        unsigned LC2D2S2 :1;
        unsigned LC2D2S3 :1;
        unsigned LC2D2S4 :1;
    };
    struct {
        unsigned LC2D2S :8;
    };
    struct {
        unsigned D2S :8;
    };
    struct {
        unsigned D2S0 :1;
        unsigned D2S1 :1;
        unsigned D2S2 :1;
        unsigned D2S3 :1;
        unsigned D2S4 :1;
    };
} CLC2SEL1bits_t;
extern volatile CLC2SEL1bits_t CLC2SEL1bits __attribute__((address(0xF1D)));
# 13318 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2SEL2 __attribute__((address(0xF1E)));

__asm("CLC2SEL2 equ 0F1Eh");


typedef union {
    struct {
        unsigned LC2D3S0 :1;
        unsigned LC2D3S1 :1;
        unsigned LC2D3S2 :1;
        unsigned LC2D3S3 :1;
        unsigned LC2D3S4 :1;
    };
    struct {
        unsigned LC2D3S :8;
    };
    struct {
        unsigned D3S :8;
    };
    struct {
        unsigned D3S0 :1;
        unsigned D3S1 :1;
        unsigned D3S2 :1;
        unsigned D3S3 :1;
        unsigned D3S4 :1;
    };
} CLC2SEL2bits_t;
extern volatile CLC2SEL2bits_t CLC2SEL2bits __attribute__((address(0xF1E)));
# 13410 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2SEL3 __attribute__((address(0xF1F)));

__asm("CLC2SEL3 equ 0F1Fh");


typedef union {
    struct {
        unsigned LC2D4S0 :1;
        unsigned LC2D4S1 :1;
        unsigned LC2D4S2 :1;
        unsigned LC2D4S3 :1;
        unsigned LC2D4S4 :1;
    };
    struct {
        unsigned LC2D4S :8;
    };
    struct {
        unsigned D4S :8;
    };
    struct {
        unsigned D4S0 :1;
        unsigned D4S1 :1;
        unsigned D4S2 :1;
        unsigned D4S3 :1;
        unsigned D4S4 :1;
    };
} CLC2SEL3bits_t;
extern volatile CLC2SEL3bits_t CLC2SEL3bits __attribute__((address(0xF1F)));
# 13502 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2GLS0 __attribute__((address(0xF20)));

__asm("CLC2GLS0 equ 0F20h");


typedef union {
    struct {
        unsigned LC2G1D1N :1;
        unsigned LC2G1D1T :1;
        unsigned LC2G1D2N :1;
        unsigned LC2G1D2T :1;
        unsigned LC2G1D3N :1;
        unsigned LC2G1D3T :1;
        unsigned LC2G1D4N :1;
        unsigned LC2G1D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC2GLS0bits_t;
extern volatile CLC2GLS0bits_t CLC2GLS0bits __attribute__((address(0xF20)));
# 13614 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2GLS1 __attribute__((address(0xF21)));

__asm("CLC2GLS1 equ 0F21h");


typedef union {
    struct {
        unsigned LC2G2D1N :1;
        unsigned LC2G2D1T :1;
        unsigned LC2G2D2N :1;
        unsigned LC2G2D2T :1;
        unsigned LC2G2D3N :1;
        unsigned LC2G2D3T :1;
        unsigned LC2G2D4N :1;
        unsigned LC2G2D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC2GLS1bits_t;
extern volatile CLC2GLS1bits_t CLC2GLS1bits __attribute__((address(0xF21)));
# 13726 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2GLS2 __attribute__((address(0xF22)));

__asm("CLC2GLS2 equ 0F22h");


typedef union {
    struct {
        unsigned LC2G3D1N :1;
        unsigned LC2G3D1T :1;
        unsigned LC2G3D2N :1;
        unsigned LC2G3D2T :1;
        unsigned LC2G3D3N :1;
        unsigned LC2G3D3T :1;
        unsigned LC2G3D4N :1;
        unsigned LC2G3D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC2GLS2bits_t;
extern volatile CLC2GLS2bits_t CLC2GLS2bits __attribute__((address(0xF22)));
# 13838 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC2GLS3 __attribute__((address(0xF23)));

__asm("CLC2GLS3 equ 0F23h");


typedef union {
    struct {
        unsigned LC2G4D1N :1;
        unsigned LC2G4D1T :1;
        unsigned LC2G4D2N :1;
        unsigned LC2G4D2T :1;
        unsigned LC2G4D3N :1;
        unsigned LC2G4D3T :1;
        unsigned LC2G4D4N :1;
        unsigned LC2G4D4T :1;
    };
    struct {
        unsigned G4D1N :1;
        unsigned G4D1T :1;
        unsigned G4D2N :1;
        unsigned G4D2T :1;
        unsigned G4D3N :1;
        unsigned G4D3T :1;
        unsigned G4D4N :1;
        unsigned G4D4T :1;
    };
} CLC2GLS3bits_t;
extern volatile CLC2GLS3bits_t CLC2GLS3bits __attribute__((address(0xF23)));
# 13950 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3CON __attribute__((address(0xF24)));

__asm("CLC3CON equ 0F24h");


typedef union {
    struct {
        unsigned LC3MODE :3;
        unsigned LC3INTN :1;
        unsigned LC3INTP :1;
        unsigned LC3OUT :1;
        unsigned :1;
        unsigned LC3EN :1;
    };
    struct {
        unsigned LC3MODE0 :1;
        unsigned LC3MODE1 :1;
        unsigned LC3MODE2 :1;
    };
    struct {
        unsigned MODE :3;
        unsigned INTN :1;
        unsigned INTP :1;
        unsigned OUT :1;
        unsigned :1;
        unsigned EN :1;
    };
    struct {
        unsigned MODE0 :1;
        unsigned MODE1 :1;
        unsigned MODE2 :1;
    };
} CLC3CONbits_t;
extern volatile CLC3CONbits_t CLC3CONbits __attribute__((address(0xF24)));
# 14068 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3POL __attribute__((address(0xF25)));

__asm("CLC3POL equ 0F25h");


typedef union {
    struct {
        unsigned LC3G1POL :1;
        unsigned LC3G2POL :1;
        unsigned LC3G3POL :1;
        unsigned LC3G4POL :1;
        unsigned :3;
        unsigned LC3POL :1;
    };
    struct {
        unsigned G1POL :1;
        unsigned G2POL :1;
        unsigned G3POL :1;
        unsigned G4POL :1;
        unsigned :3;
        unsigned POL :1;
    };
} CLC3POLbits_t;
extern volatile CLC3POLbits_t CLC3POLbits __attribute__((address(0xF25)));
# 14146 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3SEL0 __attribute__((address(0xF26)));

__asm("CLC3SEL0 equ 0F26h");


typedef union {
    struct {
        unsigned LC3D1S0 :1;
        unsigned LC3D1S1 :1;
        unsigned LC3D1S2 :1;
        unsigned LC3D1S3 :1;
        unsigned LC3D1S4 :1;
    };
    struct {
        unsigned LC3D1S :8;
    };
    struct {
        unsigned D1S :8;
    };
    struct {
        unsigned D1S0 :1;
        unsigned D1S1 :1;
        unsigned D1S2 :1;
        unsigned D1S3 :1;
        unsigned D1S4 :1;
    };
} CLC3SEL0bits_t;
extern volatile CLC3SEL0bits_t CLC3SEL0bits __attribute__((address(0xF26)));
# 14238 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3SEL1 __attribute__((address(0xF27)));

__asm("CLC3SEL1 equ 0F27h");


typedef union {
    struct {
        unsigned LC3D2S0 :1;
        unsigned LC3D2S1 :1;
        unsigned LC3D2S2 :1;
        unsigned LC3D2S3 :1;
        unsigned LC3D2S4 :1;
    };
    struct {
        unsigned LC3D2S :8;
    };
    struct {
        unsigned D2S :8;
    };
    struct {
        unsigned D2S0 :1;
        unsigned D2S1 :1;
        unsigned D2S2 :1;
        unsigned D2S3 :1;
        unsigned D2S4 :1;
    };
} CLC3SEL1bits_t;
extern volatile CLC3SEL1bits_t CLC3SEL1bits __attribute__((address(0xF27)));
# 14330 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3SEL2 __attribute__((address(0xF28)));

__asm("CLC3SEL2 equ 0F28h");


typedef union {
    struct {
        unsigned LC3D3S0 :1;
        unsigned LC3D3S1 :1;
        unsigned LC3D3S2 :1;
        unsigned LC3D3S3 :1;
        unsigned LC3D3S4 :1;
    };
    struct {
        unsigned LC3D3S :8;
    };
    struct {
        unsigned D3S :8;
    };
    struct {
        unsigned D3S0 :1;
        unsigned D3S1 :1;
        unsigned D3S2 :1;
        unsigned D3S3 :1;
        unsigned D3S4 :1;
    };
} CLC3SEL2bits_t;
extern volatile CLC3SEL2bits_t CLC3SEL2bits __attribute__((address(0xF28)));
# 14422 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3SEL3 __attribute__((address(0xF29)));

__asm("CLC3SEL3 equ 0F29h");


typedef union {
    struct {
        unsigned LC3D4S0 :1;
        unsigned LC3D4S1 :1;
        unsigned LC3D4S2 :1;
        unsigned LC3D4S3 :1;
        unsigned LC3D4S4 :1;
    };
    struct {
        unsigned LC3D4S :8;
    };
    struct {
        unsigned D4S :8;
    };
    struct {
        unsigned D4S0 :1;
        unsigned D4S1 :1;
        unsigned D4S2 :1;
        unsigned D4S3 :1;
        unsigned D4S4 :1;
    };
} CLC3SEL3bits_t;
extern volatile CLC3SEL3bits_t CLC3SEL3bits __attribute__((address(0xF29)));
# 14514 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3GLS0 __attribute__((address(0xF2A)));

__asm("CLC3GLS0 equ 0F2Ah");


typedef union {
    struct {
        unsigned LC3G1D1N :1;
        unsigned LC3G1D1T :1;
        unsigned LC3G1D2N :1;
        unsigned LC3G1D2T :1;
        unsigned LC3G1D3N :1;
        unsigned LC3G1D3T :1;
        unsigned LC3G1D4N :1;
        unsigned LC3G1D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC3GLS0bits_t;
extern volatile CLC3GLS0bits_t CLC3GLS0bits __attribute__((address(0xF2A)));
# 14626 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3GLS1 __attribute__((address(0xF2B)));

__asm("CLC3GLS1 equ 0F2Bh");


typedef union {
    struct {
        unsigned LC3G2D1N :1;
        unsigned LC3G2D1T :1;
        unsigned LC3G2D2N :1;
        unsigned LC3G2D2T :1;
        unsigned LC3G2D3N :1;
        unsigned LC3G2D3T :1;
        unsigned LC3G2D4N :1;
        unsigned LC3G2D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC3GLS1bits_t;
extern volatile CLC3GLS1bits_t CLC3GLS1bits __attribute__((address(0xF2B)));
# 14738 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3GLS2 __attribute__((address(0xF2C)));

__asm("CLC3GLS2 equ 0F2Ch");


typedef union {
    struct {
        unsigned LC3G3D1N :1;
        unsigned LC3G3D1T :1;
        unsigned LC3G3D2N :1;
        unsigned LC3G3D2T :1;
        unsigned LC3G3D3N :1;
        unsigned LC3G3D3T :1;
        unsigned LC3G3D4N :1;
        unsigned LC3G3D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC3GLS2bits_t;
extern volatile CLC3GLS2bits_t CLC3GLS2bits __attribute__((address(0xF2C)));
# 14850 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC3GLS3 __attribute__((address(0xF2D)));

__asm("CLC3GLS3 equ 0F2Dh");


typedef union {
    struct {
        unsigned LC3G4D1N :1;
        unsigned LC3G4D1T :1;
        unsigned LC3G4D2N :1;
        unsigned LC3G4D2T :1;
        unsigned LC3G4D3N :1;
        unsigned LC3G4D3T :1;
        unsigned LC3G4D4N :1;
        unsigned LC3G4D4T :1;
    };
    struct {
        unsigned G4D1N :1;
        unsigned G4D1T :1;
        unsigned G4D2N :1;
        unsigned G4D2T :1;
        unsigned G4D3N :1;
        unsigned G4D3T :1;
        unsigned G4D4N :1;
        unsigned G4D4T :1;
    };
} CLC3GLS3bits_t;
extern volatile CLC3GLS3bits_t CLC3GLS3bits __attribute__((address(0xF2D)));
# 14962 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4CON __attribute__((address(0xF2E)));

__asm("CLC4CON equ 0F2Eh");


typedef union {
    struct {
        unsigned LC4MODE :3;
        unsigned LC4INTN :1;
        unsigned LC4INTP :1;
        unsigned LC4OUT :1;
        unsigned :1;
        unsigned LC4EN :1;
    };
    struct {
        unsigned LC4MODE0 :1;
        unsigned LC4MODE1 :1;
        unsigned LC4MODE2 :1;
    };
    struct {
        unsigned MODE :3;
        unsigned INTN :1;
        unsigned INTP :1;
        unsigned OUT :1;
        unsigned :1;
        unsigned EN :1;
    };
    struct {
        unsigned MODE0 :1;
        unsigned MODE1 :1;
        unsigned MODE2 :1;
    };
} CLC4CONbits_t;
extern volatile CLC4CONbits_t CLC4CONbits __attribute__((address(0xF2E)));
# 15080 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4POL __attribute__((address(0xF2F)));

__asm("CLC4POL equ 0F2Fh");


typedef union {
    struct {
        unsigned LC4G1POL :1;
        unsigned LC4G2POL :1;
        unsigned LC4G3POL :1;
        unsigned LC4G4POL :1;
        unsigned :3;
        unsigned LC4POL :1;
    };
    struct {
        unsigned G1POL :1;
        unsigned G2POL :1;
        unsigned G3POL :1;
        unsigned G4POL :1;
        unsigned :3;
        unsigned POL :1;
    };
} CLC4POLbits_t;
extern volatile CLC4POLbits_t CLC4POLbits __attribute__((address(0xF2F)));
# 15158 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4SEL0 __attribute__((address(0xF30)));

__asm("CLC4SEL0 equ 0F30h");


typedef union {
    struct {
        unsigned LC4D1S0 :1;
        unsigned LC4D1S1 :1;
        unsigned LC4D1S2 :1;
        unsigned LC4D1S3 :1;
        unsigned LC4D1S4 :1;
    };
    struct {
        unsigned LC4D1S :8;
    };
    struct {
        unsigned D1S :8;
    };
    struct {
        unsigned D1S0 :1;
        unsigned D1S1 :1;
        unsigned D1S2 :1;
        unsigned D1S3 :1;
        unsigned D1S4 :1;
    };
} CLC4SEL0bits_t;
extern volatile CLC4SEL0bits_t CLC4SEL0bits __attribute__((address(0xF30)));
# 15250 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4SEL1 __attribute__((address(0xF31)));

__asm("CLC4SEL1 equ 0F31h");


typedef union {
    struct {
        unsigned LC4D2S0 :1;
        unsigned LC4D2S1 :1;
        unsigned LC4D2S2 :1;
        unsigned LC4D2S3 :1;
        unsigned LC4D2S4 :1;
    };
    struct {
        unsigned LC4D2S :8;
    };
    struct {
        unsigned D2S :8;
    };
    struct {
        unsigned D2S0 :1;
        unsigned D2S1 :1;
        unsigned D2S2 :1;
        unsigned D2S3 :1;
        unsigned D2S4 :1;
    };
} CLC4SEL1bits_t;
extern volatile CLC4SEL1bits_t CLC4SEL1bits __attribute__((address(0xF31)));
# 15342 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4SEL2 __attribute__((address(0xF32)));

__asm("CLC4SEL2 equ 0F32h");


typedef union {
    struct {
        unsigned LC4D3S0 :1;
        unsigned LC4D3S1 :1;
        unsigned LC4D3S2 :1;
        unsigned LC4D3S3 :1;
        unsigned LC4D3S4 :1;
    };
    struct {
        unsigned LC4D3S :8;
    };
    struct {
        unsigned D3S :8;
    };
    struct {
        unsigned D3S0 :1;
        unsigned D3S1 :1;
        unsigned D3S2 :1;
        unsigned D3S3 :1;
        unsigned D3S4 :1;
    };
} CLC4SEL2bits_t;
extern volatile CLC4SEL2bits_t CLC4SEL2bits __attribute__((address(0xF32)));
# 15434 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4SEL3 __attribute__((address(0xF33)));

__asm("CLC4SEL3 equ 0F33h");


typedef union {
    struct {
        unsigned LC4D4S0 :1;
        unsigned LC4D4S1 :1;
        unsigned LC4D4S2 :1;
        unsigned LC4D4S3 :1;
        unsigned LC4D4S4 :1;
    };
    struct {
        unsigned LC4D4S :8;
    };
    struct {
        unsigned D4S :8;
    };
    struct {
        unsigned D4S0 :1;
        unsigned D4S1 :1;
        unsigned D4S2 :1;
        unsigned D4S3 :1;
        unsigned D4S4 :1;
    };
} CLC4SEL3bits_t;
extern volatile CLC4SEL3bits_t CLC4SEL3bits __attribute__((address(0xF33)));
# 15526 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4GLS0 __attribute__((address(0xF34)));

__asm("CLC4GLS0 equ 0F34h");


typedef union {
    struct {
        unsigned LC4G1D1N :1;
        unsigned LC4G1D1T :1;
        unsigned LC4G1D2N :1;
        unsigned LC4G1D2T :1;
        unsigned LC4G1D3N :1;
        unsigned LC4G1D3T :1;
        unsigned LC4G1D4N :1;
        unsigned LC4G1D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC4GLS0bits_t;
extern volatile CLC4GLS0bits_t CLC4GLS0bits __attribute__((address(0xF34)));
# 15638 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4GLS1 __attribute__((address(0xF35)));

__asm("CLC4GLS1 equ 0F35h");


typedef union {
    struct {
        unsigned LC4G2D1N :1;
        unsigned LC4G2D1T :1;
        unsigned LC4G2D2N :1;
        unsigned LC4G2D2T :1;
        unsigned LC4G2D3N :1;
        unsigned LC4G2D3T :1;
        unsigned LC4G2D4N :1;
        unsigned LC4G2D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC4GLS1bits_t;
extern volatile CLC4GLS1bits_t CLC4GLS1bits __attribute__((address(0xF35)));
# 15750 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4GLS2 __attribute__((address(0xF36)));

__asm("CLC4GLS2 equ 0F36h");


typedef union {
    struct {
        unsigned LC4G3D1N :1;
        unsigned LC4G3D1T :1;
        unsigned LC4G3D2N :1;
        unsigned LC4G3D2T :1;
        unsigned LC4G3D3N :1;
        unsigned LC4G3D3T :1;
        unsigned LC4G3D4N :1;
        unsigned LC4G3D4T :1;
    };
    struct {
        unsigned D1N :1;
        unsigned D1T :1;
        unsigned D2N :1;
        unsigned D2T :1;
        unsigned D3N :1;
        unsigned D3T :1;
        unsigned D4N :1;
        unsigned D4T :1;
    };
} CLC4GLS2bits_t;
extern volatile CLC4GLS2bits_t CLC4GLS2bits __attribute__((address(0xF36)));
# 15862 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char CLC4GLS3 __attribute__((address(0xF37)));

__asm("CLC4GLS3 equ 0F37h");


typedef union {
    struct {
        unsigned LC4G4D1N :1;
        unsigned LC4G4D1T :1;
        unsigned LC4G4D2N :1;
        unsigned LC4G4D2T :1;
        unsigned LC4G4D3N :1;
        unsigned LC4G4D3T :1;
        unsigned LC4G4D4N :1;
        unsigned LC4G4D4T :1;
    };
    struct {
        unsigned G4D1N :1;
        unsigned G4D1T :1;
        unsigned G4D2N :1;
        unsigned G4D2T :1;
        unsigned G4D3N :1;
        unsigned G4D3T :1;
        unsigned G4D4N :1;
        unsigned G4D4T :1;
    };
} CLC4GLS3bits_t;
extern volatile CLC4GLS3bits_t CLC4GLS3bits __attribute__((address(0xF37)));
# 15974 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char STATUS_SHAD __attribute__((address(0xFE4)));

__asm("STATUS_SHAD equ 0FE4h");


typedef union {
    struct {
        unsigned C_SHAD :1;
        unsigned DC_SHAD :1;
        unsigned Z_SHAD :1;
    };
} STATUS_SHADbits_t;
extern volatile STATUS_SHADbits_t STATUS_SHADbits __attribute__((address(0xFE4)));
# 16006 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char WREG_SHAD __attribute__((address(0xFE5)));

__asm("WREG_SHAD equ 0FE5h");


typedef union {
    struct {
        unsigned WREG_SHAD :8;
    };
} WREG_SHADbits_t;
extern volatile WREG_SHADbits_t WREG_SHADbits __attribute__((address(0xFE5)));
# 16026 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char BSR_SHAD __attribute__((address(0xFE6)));

__asm("BSR_SHAD equ 0FE6h");


typedef union {
    struct {
        unsigned BSR_SHAD :5;
    };
} BSR_SHADbits_t;
extern volatile BSR_SHADbits_t BSR_SHADbits __attribute__((address(0xFE6)));
# 16046 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char PCLATH_SHAD __attribute__((address(0xFE7)));

__asm("PCLATH_SHAD equ 0FE7h");


typedef union {
    struct {
        unsigned PCLATH_SHAD :7;
    };
} PCLATH_SHADbits_t;
extern volatile PCLATH_SHADbits_t PCLATH_SHADbits __attribute__((address(0xFE7)));
# 16066 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR0L_SHAD __attribute__((address(0xFE8)));

__asm("FSR0L_SHAD equ 0FE8h");


typedef union {
    struct {
        unsigned FSR0L_SHAD :8;
    };
} FSR0L_SHADbits_t;
extern volatile FSR0L_SHADbits_t FSR0L_SHADbits __attribute__((address(0xFE8)));
# 16086 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR0H_SHAD __attribute__((address(0xFE9)));

__asm("FSR0H_SHAD equ 0FE9h");


typedef union {
    struct {
        unsigned FSR0H_SHAD :8;
    };
} FSR0H_SHADbits_t;
extern volatile FSR0H_SHADbits_t FSR0H_SHADbits __attribute__((address(0xFE9)));
# 16106 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR1L_SHAD __attribute__((address(0xFEA)));

__asm("FSR1L_SHAD equ 0FEAh");


typedef union {
    struct {
        unsigned FSR1L_SHAD :8;
    };
} FSR1L_SHADbits_t;
extern volatile FSR1L_SHADbits_t FSR1L_SHADbits __attribute__((address(0xFEA)));
# 16126 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char FSR1H_SHAD __attribute__((address(0xFEB)));

__asm("FSR1H_SHAD equ 0FEBh");


typedef union {
    struct {
        unsigned FSR1H_SHAD :8;
    };
} FSR1H_SHADbits_t;
extern volatile FSR1H_SHADbits_t FSR1H_SHADbits __attribute__((address(0xFEB)));
# 16146 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char STKPTR __attribute__((address(0xFED)));

__asm("STKPTR equ 0FEDh");


typedef union {
    struct {
        unsigned STKPTR :5;
    };
} STKPTRbits_t;
extern volatile STKPTRbits_t STKPTRbits __attribute__((address(0xFED)));
# 16166 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TOSL __attribute__((address(0xFEE)));

__asm("TOSL equ 0FEEh");


typedef union {
    struct {
        unsigned TOSL :8;
    };
} TOSLbits_t;
extern volatile TOSLbits_t TOSLbits __attribute__((address(0xFEE)));
# 16186 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile unsigned char TOSH __attribute__((address(0xFEF)));

__asm("TOSH equ 0FEFh");


typedef union {
    struct {
        unsigned TOSH :7;
    };
} TOSHbits_t;
extern volatile TOSHbits_t TOSHbits __attribute__((address(0xFEF)));
# 16216 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\proc\\pic16f1719.h" 3
extern volatile __bit ABDEN __attribute__((address(0xCF8)));


extern volatile __bit ABDOVF __attribute__((address(0xCFF)));


extern volatile __bit ACKDT __attribute__((address(0x10B5)));


extern volatile __bit ACKEN __attribute__((address(0x10B4)));


extern volatile __bit ACKSTAT __attribute__((address(0x10B6)));


extern volatile __bit ACKTIM __attribute__((address(0x10BF)));


extern volatile __bit ADD0 __attribute__((address(0x1090)));


extern volatile __bit ADD1 __attribute__((address(0x1091)));


extern volatile __bit ADD2 __attribute__((address(0x1092)));


extern volatile __bit ADD3 __attribute__((address(0x1093)));


extern volatile __bit ADD4 __attribute__((address(0x1094)));


extern volatile __bit ADD5 __attribute__((address(0x1095)));


extern volatile __bit ADD6 __attribute__((address(0x1096)));


extern volatile __bit ADD7 __attribute__((address(0x1097)));


extern volatile __bit ADDEN __attribute__((address(0xCEB)));


extern volatile __bit ADFM __attribute__((address(0x4F7)));


extern volatile __bit ADFVR0 __attribute__((address(0x8B8)));


extern volatile __bit ADFVR1 __attribute__((address(0x8B9)));


extern volatile __bit ADGO __attribute__((address(0x4E9)));


extern volatile __bit ADIE __attribute__((address(0x48E)));


extern volatile __bit ADIF __attribute__((address(0x8E)));


extern volatile __bit ADNREF __attribute__((address(0x4F2)));


extern volatile __bit ADON __attribute__((address(0x4E8)));


extern volatile __bit ADPREF0 __attribute__((address(0x4F0)));


extern volatile __bit ADPREF1 __attribute__((address(0x4F1)));


extern volatile __bit AHEN __attribute__((address(0x10B9)));


extern volatile __bit ANSA0 __attribute__((address(0xC60)));


extern volatile __bit ANSA1 __attribute__((address(0xC61)));


extern volatile __bit ANSA2 __attribute__((address(0xC62)));


extern volatile __bit ANSA3 __attribute__((address(0xC63)));


extern volatile __bit ANSA4 __attribute__((address(0xC64)));


extern volatile __bit ANSA5 __attribute__((address(0xC65)));


extern volatile __bit ANSB0 __attribute__((address(0xC68)));


extern volatile __bit ANSB1 __attribute__((address(0xC69)));


extern volatile __bit ANSB2 __attribute__((address(0xC6A)));


extern volatile __bit ANSB3 __attribute__((address(0xC6B)));


extern volatile __bit ANSB4 __attribute__((address(0xC6C)));


extern volatile __bit ANSB5 __attribute__((address(0xC6D)));


extern volatile __bit ANSC2 __attribute__((address(0xC72)));


extern volatile __bit ANSC3 __attribute__((address(0xC73)));


extern volatile __bit ANSC4 __attribute__((address(0xC74)));


extern volatile __bit ANSC5 __attribute__((address(0xC75)));


extern volatile __bit ANSC6 __attribute__((address(0xC76)));


extern volatile __bit ANSC7 __attribute__((address(0xC77)));


extern volatile __bit ANSD0 __attribute__((address(0xC78)));


extern volatile __bit ANSD1 __attribute__((address(0xC79)));


extern volatile __bit ANSD2 __attribute__((address(0xC7A)));


extern volatile __bit ANSD3 __attribute__((address(0xC7B)));


extern volatile __bit ANSD4 __attribute__((address(0xC7C)));


extern volatile __bit ANSD5 __attribute__((address(0xC7D)));


extern volatile __bit ANSD6 __attribute__((address(0xC7E)));


extern volatile __bit ANSD7 __attribute__((address(0xC7F)));


extern volatile __bit ANSE0 __attribute__((address(0xC80)));


extern volatile __bit ANSE1 __attribute__((address(0xC81)));


extern volatile __bit ANSE2 __attribute__((address(0xC82)));


extern volatile __bit BCL1IE __attribute__((address(0x493)));


extern volatile __bit BCL1IF __attribute__((address(0x93)));


extern volatile __bit BF __attribute__((address(0x10A0)));


extern volatile __bit BOEN __attribute__((address(0x10BC)));


extern volatile __bit BORFS __attribute__((address(0x8B6)));


extern volatile __bit BORRDY __attribute__((address(0x8B0)));


extern volatile __bit BRG16 __attribute__((address(0xCFB)));


extern volatile __bit BRGH __attribute__((address(0xCF2)));


extern volatile __bit BSR0 __attribute__((address(0x40)));


extern volatile __bit BSR1 __attribute__((address(0x41)));


extern volatile __bit BSR2 __attribute__((address(0x42)));


extern volatile __bit BSR3 __attribute__((address(0x43)));


extern volatile __bit BSR4 __attribute__((address(0x44)));


extern volatile __bit BUF0 __attribute__((address(0x1088)));


extern volatile __bit BUF1 __attribute__((address(0x1089)));


extern volatile __bit BUF2 __attribute__((address(0x108A)));


extern volatile __bit BUF3 __attribute__((address(0x108B)));


extern volatile __bit BUF4 __attribute__((address(0x108C)));


extern volatile __bit BUF5 __attribute__((address(0x108D)));


extern volatile __bit BUF6 __attribute__((address(0x108E)));


extern volatile __bit BUF7 __attribute__((address(0x108F)));


extern volatile __bit C1HYS __attribute__((address(0x889)));


extern volatile __bit C1IE __attribute__((address(0x495)));


extern volatile __bit C1IF __attribute__((address(0x95)));


extern volatile __bit C1INTN __attribute__((address(0x896)));


extern volatile __bit C1INTP __attribute__((address(0x897)));


extern volatile __bit C1NCH0 __attribute__((address(0x890)));


extern volatile __bit C1NCH1 __attribute__((address(0x891)));


extern volatile __bit C1NCH2 __attribute__((address(0x892)));


extern volatile __bit C1ON __attribute__((address(0x88F)));


extern volatile __bit C1OUT __attribute__((address(0x88E)));


extern volatile __bit C1PCH0 __attribute__((address(0x893)));


extern volatile __bit C1PCH1 __attribute__((address(0x894)));


extern volatile __bit C1PCH2 __attribute__((address(0x895)));


extern volatile __bit C1POL __attribute__((address(0x88C)));


extern volatile __bit C1SP __attribute__((address(0x88A)));


extern volatile __bit C1SYNC __attribute__((address(0x888)));


extern volatile __bit C1TSEL0 __attribute__((address(0x14F0)));


extern volatile __bit C1TSEL1 __attribute__((address(0x14F1)));


extern volatile __bit C1ZLF __attribute__((address(0x88B)));


extern volatile __bit C2HYS __attribute__((address(0x899)));


extern volatile __bit C2IE __attribute__((address(0x496)));


extern volatile __bit C2IF __attribute__((address(0x96)));


extern volatile __bit C2INTN __attribute__((address(0x8A6)));


extern volatile __bit C2INTP __attribute__((address(0x8A7)));


extern volatile __bit C2NCH0 __attribute__((address(0x8A0)));


extern volatile __bit C2NCH1 __attribute__((address(0x8A1)));


extern volatile __bit C2NCH2 __attribute__((address(0x8A2)));


extern volatile __bit C2ON __attribute__((address(0x89F)));


extern volatile __bit C2OUT __attribute__((address(0x89E)));


extern volatile __bit C2PCH0 __attribute__((address(0x8A3)));


extern volatile __bit C2PCH1 __attribute__((address(0x8A4)));


extern volatile __bit C2PCH2 __attribute__((address(0x8A5)));


extern volatile __bit C2POL __attribute__((address(0x89C)));


extern volatile __bit C2SP __attribute__((address(0x89A)));


extern volatile __bit C2SYNC __attribute__((address(0x898)));


extern volatile __bit C2TSEL0 __attribute__((address(0x14F2)));


extern volatile __bit C2TSEL1 __attribute__((address(0x14F3)));


extern volatile __bit C2ZLF __attribute__((address(0x89B)));


extern volatile __bit CARRY __attribute__((address(0x18)));


extern volatile __bit CCP1IE __attribute__((address(0x48A)));


extern volatile __bit CCP1IF __attribute__((address(0x8A)));


extern volatile __bit CCP1M0 __attribute__((address(0x1498)));


extern volatile __bit CCP1M1 __attribute__((address(0x1499)));


extern volatile __bit CCP1M2 __attribute__((address(0x149A)));


extern volatile __bit CCP1M3 __attribute__((address(0x149B)));


extern volatile __bit CCP1X __attribute__((address(0x149D)));


extern volatile __bit CCP1Y __attribute__((address(0x149C)));


extern volatile __bit CCP2IE __attribute__((address(0x490)));


extern volatile __bit CCP2IF __attribute__((address(0x90)));


extern volatile __bit CCP2M0 __attribute__((address(0x14D0)));


extern volatile __bit CCP2M1 __attribute__((address(0x14D1)));


extern volatile __bit CCP2M2 __attribute__((address(0x14D2)));


extern volatile __bit CCP2M3 __attribute__((address(0x14D3)));


extern volatile __bit CCP2X __attribute__((address(0x14D5)));


extern volatile __bit CCP2Y __attribute__((address(0x14D4)));


extern volatile __bit CDAFVR0 __attribute__((address(0x8BA)));


extern volatile __bit CDAFVR1 __attribute__((address(0x8BB)));


extern volatile __bit CFGS __attribute__((address(0xCAE)));


extern volatile __bit CHS0 __attribute__((address(0x4EA)));


extern volatile __bit CHS1 __attribute__((address(0x4EB)));


extern volatile __bit CHS2 __attribute__((address(0x4EC)));


extern volatile __bit CHS3 __attribute__((address(0x4ED)));


extern volatile __bit CHS4 __attribute__((address(0x4EE)));


extern volatile __bit CKE __attribute__((address(0x10A6)));


extern volatile __bit CKP __attribute__((address(0x10AC)));


extern volatile __bit CLC1IE __attribute__((address(0x498)));


extern volatile __bit CLC1IF __attribute__((address(0x98)));


extern volatile __bit CLC2IE __attribute__((address(0x499)));


extern volatile __bit CLC2IF __attribute__((address(0x99)));


extern volatile __bit CLC3IE __attribute__((address(0x49A)));


extern volatile __bit CLC3IF __attribute__((address(0x9A)));


extern volatile __bit CLC4IE __attribute__((address(0x49B)));


extern volatile __bit CLC4IF __attribute__((address(0x9B)));


extern volatile __bit COGIE __attribute__((address(0x49D)));


extern volatile __bit COGIF __attribute__((address(0x9D)));


extern volatile __bit CREN __attribute__((address(0xCEC)));


extern volatile __bit CSRC __attribute__((address(0xCF7)));


extern volatile __bit C_SHAD __attribute__((address(0x7F20)));


extern volatile __bit DAC1EN __attribute__((address(0x8C7)));


extern volatile __bit DAC1NSS __attribute__((address(0x8C0)));


extern volatile __bit DAC1OE1 __attribute__((address(0x8C5)));


extern volatile __bit DAC1OE2 __attribute__((address(0x8C4)));


extern volatile __bit DAC1PSS0 __attribute__((address(0x8C2)));


extern volatile __bit DAC1PSS1 __attribute__((address(0x8C3)));


extern volatile __bit DAC1R0 __attribute__((address(0x8C8)));


extern volatile __bit DAC1R1 __attribute__((address(0x8C9)));


extern volatile __bit DAC1R2 __attribute__((address(0x8CA)));


extern volatile __bit DAC1R3 __attribute__((address(0x8CB)));


extern volatile __bit DAC1R4 __attribute__((address(0x8CC)));


extern volatile __bit DAC1R5 __attribute__((address(0x8CD)));


extern volatile __bit DAC1R6 __attribute__((address(0x8CE)));


extern volatile __bit DAC1R7 __attribute__((address(0x8CF)));


extern volatile __bit DAC2EN __attribute__((address(0x8D7)));


extern volatile __bit DAC2NSS __attribute__((address(0x8D0)));


extern volatile __bit DAC2OE1 __attribute__((address(0x8D5)));


extern volatile __bit DAC2OE2 __attribute__((address(0x8D4)));


extern volatile __bit DAC2PSS0 __attribute__((address(0x8D2)));


extern volatile __bit DAC2PSS1 __attribute__((address(0x8D3)));


extern volatile __bit DAC2R0 __attribute__((address(0x8D8)));


extern volatile __bit DAC2R1 __attribute__((address(0x8D9)));


extern volatile __bit DAC2R2 __attribute__((address(0x8DA)));


extern volatile __bit DAC2R3 __attribute__((address(0x8DB)));


extern volatile __bit DAC2R4 __attribute__((address(0x8DC)));


extern volatile __bit DAC2REF0 __attribute__((address(0x8D8)));


extern volatile __bit DAC2REF1 __attribute__((address(0x8D9)));


extern volatile __bit DAC2REF2 __attribute__((address(0x8DA)));


extern volatile __bit DAC2REF3 __attribute__((address(0x8DB)));


extern volatile __bit DAC2REF4 __attribute__((address(0x8DC)));


extern volatile __bit DAC2REF5 __attribute__((address(0x8DD)));


extern volatile __bit DACOE0 __attribute__((address(0x8C4)));


extern volatile __bit DACOE2 __attribute__((address(0x8D4)));


extern volatile __bit DACR5 __attribute__((address(0x8CD)));


extern volatile __bit DACR6 __attribute__((address(0x8CE)));


extern volatile __bit DACR7 __attribute__((address(0x8CF)));


extern volatile __bit DC __attribute__((address(0x19)));


extern volatile __bit DC1B0 __attribute__((address(0x149C)));


extern volatile __bit DC1B1 __attribute__((address(0x149D)));


extern volatile __bit DC2B0 __attribute__((address(0x14D4)));


extern volatile __bit DC2B1 __attribute__((address(0x14D5)));


extern volatile __bit DC_SHAD __attribute__((address(0x7F21)));


extern volatile __bit DHEN __attribute__((address(0x10B8)));


extern volatile __bit D_nA __attribute__((address(0x10A5)));


extern volatile __bit FERR __attribute__((address(0xCEA)));


extern volatile __bit FREE __attribute__((address(0xCAC)));


extern volatile __bit FVREN __attribute__((address(0x8BF)));


extern volatile __bit FVRRDY __attribute__((address(0x8BE)));


extern volatile __bit G1ARSEN __attribute__((address(0x34EE)));


extern volatile __bit G1AS0E __attribute__((address(0x34F0)));


extern volatile __bit G1AS1E __attribute__((address(0x34F1)));


extern volatile __bit G1AS2E __attribute__((address(0x34F2)));


extern volatile __bit G1AS3E __attribute__((address(0x34F3)));


extern volatile __bit G1ASDAC0 __attribute__((address(0x34EA)));


extern volatile __bit G1ASDAC1 __attribute__((address(0x34EB)));


extern volatile __bit G1ASDBD0 __attribute__((address(0x34EC)));


extern volatile __bit G1ASDBD1 __attribute__((address(0x34ED)));


extern volatile __bit G1ASE __attribute__((address(0x34EF)));


extern volatile __bit G1BLKF0 __attribute__((address(0x34A0)));


extern volatile __bit G1BLKF1 __attribute__((address(0x34A1)));


extern volatile __bit G1BLKF2 __attribute__((address(0x34A2)));


extern volatile __bit G1BLKF3 __attribute__((address(0x34A3)));


extern volatile __bit G1BLKF4 __attribute__((address(0x34A4)));


extern volatile __bit G1BLKF5 __attribute__((address(0x34A5)));


extern volatile __bit G1BLKR0 __attribute__((address(0x3498)));


extern volatile __bit G1BLKR1 __attribute__((address(0x3499)));


extern volatile __bit G1BLKR2 __attribute__((address(0x349A)));


extern volatile __bit G1BLKR3 __attribute__((address(0x349B)));


extern volatile __bit G1BLKR4 __attribute__((address(0x349C)));


extern volatile __bit G1BLKR5 __attribute__((address(0x349D)));


extern volatile __bit G1CS0 __attribute__((address(0x34BB)));


extern volatile __bit G1CS1 __attribute__((address(0x34BC)));


extern volatile __bit G1DBF0 __attribute__((address(0x34B0)));


extern volatile __bit G1DBF1 __attribute__((address(0x34B1)));


extern volatile __bit G1DBF2 __attribute__((address(0x34B2)));


extern volatile __bit G1DBF3 __attribute__((address(0x34B3)));


extern volatile __bit G1DBF4 __attribute__((address(0x34B4)));


extern volatile __bit G1DBF5 __attribute__((address(0x34B5)));


extern volatile __bit G1DBR0 __attribute__((address(0x34A8)));


extern volatile __bit G1DBR1 __attribute__((address(0x34A9)));


extern volatile __bit G1DBR2 __attribute__((address(0x34AA)));


extern volatile __bit G1DBR3 __attribute__((address(0x34AB)));


extern volatile __bit G1DBR4 __attribute__((address(0x34AC)));


extern volatile __bit G1DBR5 __attribute__((address(0x34AD)));


extern volatile __bit G1EN __attribute__((address(0x34BF)));


extern volatile __bit G1FDBS __attribute__((address(0x34C6)));


extern volatile __bit G1FIS0 __attribute__((address(0x34D8)));


extern volatile __bit G1FIS1 __attribute__((address(0x34D9)));


extern volatile __bit G1FIS2 __attribute__((address(0x34DA)));


extern volatile __bit G1FIS3 __attribute__((address(0x34DB)));


extern volatile __bit G1FIS4 __attribute__((address(0x34DC)));


extern volatile __bit G1FIS5 __attribute__((address(0x34DD)));


extern volatile __bit G1FIS6 __attribute__((address(0x34DE)));


extern volatile __bit G1FIS7 __attribute__((address(0x34DF)));


extern volatile __bit G1FSIM0 __attribute__((address(0x34E0)));


extern volatile __bit G1FSIM1 __attribute__((address(0x34E1)));


extern volatile __bit G1FSIM2 __attribute__((address(0x34E2)));


extern volatile __bit G1FSIM3 __attribute__((address(0x34E3)));


extern volatile __bit G1FSIM4 __attribute__((address(0x34E4)));


extern volatile __bit G1FSIM5 __attribute__((address(0x34E5)));


extern volatile __bit G1FSIM6 __attribute__((address(0x34E6)));


extern volatile __bit G1FSIM7 __attribute__((address(0x34E7)));


extern volatile __bit G1LD __attribute__((address(0x34BE)));


extern volatile __bit G1MD0 __attribute__((address(0x34B8)));


extern volatile __bit G1MD1 __attribute__((address(0x34B9)));


extern volatile __bit G1MD2 __attribute__((address(0x34BA)));


extern volatile __bit G1PHF0 __attribute__((address(0x3490)));


extern volatile __bit G1PHF1 __attribute__((address(0x3491)));


extern volatile __bit G1PHF2 __attribute__((address(0x3492)));


extern volatile __bit G1PHF3 __attribute__((address(0x3493)));


extern volatile __bit G1PHF4 __attribute__((address(0x3494)));


extern volatile __bit G1PHF5 __attribute__((address(0x3495)));


extern volatile __bit G1PHR0 __attribute__((address(0x3488)));


extern volatile __bit G1PHR1 __attribute__((address(0x3489)));


extern volatile __bit G1PHR2 __attribute__((address(0x348A)));


extern volatile __bit G1PHR3 __attribute__((address(0x348B)));


extern volatile __bit G1PHR4 __attribute__((address(0x348C)));


extern volatile __bit G1PHR5 __attribute__((address(0x348D)));


extern volatile __bit G1POLA __attribute__((address(0x34C0)));


extern volatile __bit G1POLB __attribute__((address(0x34C1)));


extern volatile __bit G1POLC __attribute__((address(0x34C2)));


extern volatile __bit G1POLD __attribute__((address(0x34C3)));


extern volatile __bit G1RDBS __attribute__((address(0x34C7)));


extern volatile __bit G1RIS0 __attribute__((address(0x34C8)));


extern volatile __bit G1RIS1 __attribute__((address(0x34C9)));


extern volatile __bit G1RIS2 __attribute__((address(0x34CA)));


extern volatile __bit G1RIS3 __attribute__((address(0x34CB)));


extern volatile __bit G1RIS4 __attribute__((address(0x34CC)));


extern volatile __bit G1RIS5 __attribute__((address(0x34CD)));


extern volatile __bit G1RIS6 __attribute__((address(0x34CE)));


extern volatile __bit G1RIS7 __attribute__((address(0x34CF)));


extern volatile __bit G1RSIM0 __attribute__((address(0x34D0)));


extern volatile __bit G1RSIM1 __attribute__((address(0x34D1)));


extern volatile __bit G1RSIM2 __attribute__((address(0x34D2)));


extern volatile __bit G1RSIM3 __attribute__((address(0x34D3)));


extern volatile __bit G1RSIM4 __attribute__((address(0x34D4)));


extern volatile __bit G1RSIM5 __attribute__((address(0x34D5)));


extern volatile __bit G1RSIM6 __attribute__((address(0x34D6)));


extern volatile __bit G1RSIM7 __attribute__((address(0x34D7)));


extern volatile __bit G1SDATA __attribute__((address(0x34FC)));


extern volatile __bit G1SDATB __attribute__((address(0x34FD)));


extern volatile __bit G1SDATC __attribute__((address(0x34FE)));


extern volatile __bit G1SDATD __attribute__((address(0x34FF)));


extern volatile __bit G1STRA __attribute__((address(0x34F8)));


extern volatile __bit G1STRB __attribute__((address(0x34F9)));


extern volatile __bit G1STRC __attribute__((address(0x34FA)));


extern volatile __bit G1STRD __attribute__((address(0x34FB)));


extern volatile __bit GCEN __attribute__((address(0x10B7)));


extern volatile __bit GIE __attribute__((address(0x5F)));


extern volatile __bit GO __attribute__((address(0x4E9)));


extern volatile __bit GO_nDONE __attribute__((address(0x4E9)));


extern volatile __bit HFIOFL __attribute__((address(0x4D3)));


extern volatile __bit HFIOFR __attribute__((address(0x4D4)));


extern volatile __bit HFIOFS __attribute__((address(0x4D0)));


extern volatile __bit INLVLA0 __attribute__((address(0x1C60)));


extern volatile __bit INLVLA1 __attribute__((address(0x1C61)));


extern volatile __bit INLVLA2 __attribute__((address(0x1C62)));


extern volatile __bit INLVLA3 __attribute__((address(0x1C63)));


extern volatile __bit INLVLA4 __attribute__((address(0x1C64)));


extern volatile __bit INLVLA5 __attribute__((address(0x1C65)));


extern volatile __bit INLVLA6 __attribute__((address(0x1C66)));


extern volatile __bit INLVLA7 __attribute__((address(0x1C67)));


extern volatile __bit INLVLB0 __attribute__((address(0x1C68)));


extern volatile __bit INLVLB1 __attribute__((address(0x1C69)));


extern volatile __bit INLVLB2 __attribute__((address(0x1C6A)));


extern volatile __bit INLVLB3 __attribute__((address(0x1C6B)));


extern volatile __bit INLVLB4 __attribute__((address(0x1C6C)));


extern volatile __bit INLVLB5 __attribute__((address(0x1C6D)));


extern volatile __bit INLVLB6 __attribute__((address(0x1C6E)));


extern volatile __bit INLVLB7 __attribute__((address(0x1C6F)));


extern volatile __bit INLVLC0 __attribute__((address(0x1C70)));


extern volatile __bit INLVLC1 __attribute__((address(0x1C71)));


extern volatile __bit INLVLC2 __attribute__((address(0x1C72)));


extern volatile __bit INLVLC3 __attribute__((address(0x1C73)));


extern volatile __bit INLVLC4 __attribute__((address(0x1C74)));


extern volatile __bit INLVLC5 __attribute__((address(0x1C75)));


extern volatile __bit INLVLC6 __attribute__((address(0x1C76)));


extern volatile __bit INLVLC7 __attribute__((address(0x1C77)));


extern volatile __bit INLVLD0 __attribute__((address(0x1C78)));


extern volatile __bit INLVLD1 __attribute__((address(0x1C79)));


extern volatile __bit INLVLD2 __attribute__((address(0x1C7A)));


extern volatile __bit INLVLD3 __attribute__((address(0x1C7B)));


extern volatile __bit INLVLD4 __attribute__((address(0x1C7C)));


extern volatile __bit INLVLD5 __attribute__((address(0x1C7D)));


extern volatile __bit INLVLD6 __attribute__((address(0x1C7E)));


extern volatile __bit INLVLD7 __attribute__((address(0x1C7F)));


extern volatile __bit INLVLE0 __attribute__((address(0x1C80)));


extern volatile __bit INLVLE1 __attribute__((address(0x1C81)));


extern volatile __bit INLVLE2 __attribute__((address(0x1C82)));


extern volatile __bit INLVLE3 __attribute__((address(0x1C83)));


extern volatile __bit INTE __attribute__((address(0x5C)));


extern volatile __bit INTEDG __attribute__((address(0x4AE)));


extern volatile __bit INTF __attribute__((address(0x59)));


extern volatile __bit IOCAF0 __attribute__((address(0x1C98)));


extern volatile __bit IOCAF1 __attribute__((address(0x1C99)));


extern volatile __bit IOCAF2 __attribute__((address(0x1C9A)));


extern volatile __bit IOCAF3 __attribute__((address(0x1C9B)));


extern volatile __bit IOCAF4 __attribute__((address(0x1C9C)));


extern volatile __bit IOCAF5 __attribute__((address(0x1C9D)));


extern volatile __bit IOCAF6 __attribute__((address(0x1C9E)));


extern volatile __bit IOCAF7 __attribute__((address(0x1C9F)));


extern volatile __bit IOCAN0 __attribute__((address(0x1C90)));


extern volatile __bit IOCAN1 __attribute__((address(0x1C91)));


extern volatile __bit IOCAN2 __attribute__((address(0x1C92)));


extern volatile __bit IOCAN3 __attribute__((address(0x1C93)));


extern volatile __bit IOCAN4 __attribute__((address(0x1C94)));


extern volatile __bit IOCAN5 __attribute__((address(0x1C95)));


extern volatile __bit IOCAN6 __attribute__((address(0x1C96)));


extern volatile __bit IOCAN7 __attribute__((address(0x1C97)));


extern volatile __bit IOCAP0 __attribute__((address(0x1C88)));


extern volatile __bit IOCAP1 __attribute__((address(0x1C89)));


extern volatile __bit IOCAP2 __attribute__((address(0x1C8A)));


extern volatile __bit IOCAP3 __attribute__((address(0x1C8B)));


extern volatile __bit IOCAP4 __attribute__((address(0x1C8C)));


extern volatile __bit IOCAP5 __attribute__((address(0x1C8D)));


extern volatile __bit IOCAP6 __attribute__((address(0x1C8E)));


extern volatile __bit IOCAP7 __attribute__((address(0x1C8F)));


extern volatile __bit IOCBF0 __attribute__((address(0x1CB0)));


extern volatile __bit IOCBF1 __attribute__((address(0x1CB1)));


extern volatile __bit IOCBF2 __attribute__((address(0x1CB2)));


extern volatile __bit IOCBF3 __attribute__((address(0x1CB3)));


extern volatile __bit IOCBF4 __attribute__((address(0x1CB4)));


extern volatile __bit IOCBF5 __attribute__((address(0x1CB5)));


extern volatile __bit IOCBF6 __attribute__((address(0x1CB6)));


extern volatile __bit IOCBF7 __attribute__((address(0x1CB7)));


extern volatile __bit IOCBN0 __attribute__((address(0x1CA8)));


extern volatile __bit IOCBN1 __attribute__((address(0x1CA9)));


extern volatile __bit IOCBN2 __attribute__((address(0x1CAA)));


extern volatile __bit IOCBN3 __attribute__((address(0x1CAB)));


extern volatile __bit IOCBN4 __attribute__((address(0x1CAC)));


extern volatile __bit IOCBN5 __attribute__((address(0x1CAD)));


extern volatile __bit IOCBN6 __attribute__((address(0x1CAE)));


extern volatile __bit IOCBN7 __attribute__((address(0x1CAF)));


extern volatile __bit IOCBP0 __attribute__((address(0x1CA0)));


extern volatile __bit IOCBP1 __attribute__((address(0x1CA1)));


extern volatile __bit IOCBP2 __attribute__((address(0x1CA2)));


extern volatile __bit IOCBP3 __attribute__((address(0x1CA3)));


extern volatile __bit IOCBP4 __attribute__((address(0x1CA4)));


extern volatile __bit IOCBP5 __attribute__((address(0x1CA5)));


extern volatile __bit IOCBP6 __attribute__((address(0x1CA6)));


extern volatile __bit IOCBP7 __attribute__((address(0x1CA7)));


extern volatile __bit IOCCF0 __attribute__((address(0x1CC8)));


extern volatile __bit IOCCF1 __attribute__((address(0x1CC9)));


extern volatile __bit IOCCF2 __attribute__((address(0x1CCA)));


extern volatile __bit IOCCF3 __attribute__((address(0x1CCB)));


extern volatile __bit IOCCF4 __attribute__((address(0x1CCC)));


extern volatile __bit IOCCF5 __attribute__((address(0x1CCD)));


extern volatile __bit IOCCF6 __attribute__((address(0x1CCE)));


extern volatile __bit IOCCF7 __attribute__((address(0x1CCF)));


extern volatile __bit IOCCN0 __attribute__((address(0x1CC0)));


extern volatile __bit IOCCN1 __attribute__((address(0x1CC1)));


extern volatile __bit IOCCN2 __attribute__((address(0x1CC2)));


extern volatile __bit IOCCN3 __attribute__((address(0x1CC3)));


extern volatile __bit IOCCN4 __attribute__((address(0x1CC4)));


extern volatile __bit IOCCN5 __attribute__((address(0x1CC5)));


extern volatile __bit IOCCN6 __attribute__((address(0x1CC6)));


extern volatile __bit IOCCN7 __attribute__((address(0x1CC7)));


extern volatile __bit IOCCP0 __attribute__((address(0x1CB8)));


extern volatile __bit IOCCP1 __attribute__((address(0x1CB9)));


extern volatile __bit IOCCP2 __attribute__((address(0x1CBA)));


extern volatile __bit IOCCP3 __attribute__((address(0x1CBB)));


extern volatile __bit IOCCP4 __attribute__((address(0x1CBC)));


extern volatile __bit IOCCP5 __attribute__((address(0x1CBD)));


extern volatile __bit IOCCP6 __attribute__((address(0x1CBE)));


extern volatile __bit IOCCP7 __attribute__((address(0x1CBF)));


extern volatile __bit IOCEF3 __attribute__((address(0x1CFB)));


extern volatile __bit IOCEN3 __attribute__((address(0x1CF3)));


extern volatile __bit IOCEP3 __attribute__((address(0x1CEB)));


extern volatile __bit IOCIE __attribute__((address(0x5B)));


extern volatile __bit IOCIF __attribute__((address(0x58)));


extern volatile __bit IRCF0 __attribute__((address(0x4CB)));


extern volatile __bit IRCF1 __attribute__((address(0x4CC)));


extern volatile __bit IRCF2 __attribute__((address(0x4CD)));


extern volatile __bit IRCF3 __attribute__((address(0x4CE)));


extern volatile __bit LATA0 __attribute__((address(0x860)));


extern volatile __bit LATA1 __attribute__((address(0x861)));


extern volatile __bit LATA2 __attribute__((address(0x862)));


extern volatile __bit LATA3 __attribute__((address(0x863)));


extern volatile __bit LATA4 __attribute__((address(0x864)));


extern volatile __bit LATA5 __attribute__((address(0x865)));


extern volatile __bit LATA6 __attribute__((address(0x866)));


extern volatile __bit LATA7 __attribute__((address(0x867)));


extern volatile __bit LATB0 __attribute__((address(0x868)));


extern volatile __bit LATB1 __attribute__((address(0x869)));


extern volatile __bit LATB2 __attribute__((address(0x86A)));


extern volatile __bit LATB3 __attribute__((address(0x86B)));


extern volatile __bit LATB4 __attribute__((address(0x86C)));


extern volatile __bit LATB5 __attribute__((address(0x86D)));


extern volatile __bit LATB6 __attribute__((address(0x86E)));


extern volatile __bit LATB7 __attribute__((address(0x86F)));


extern volatile __bit LATC0 __attribute__((address(0x870)));


extern volatile __bit LATC1 __attribute__((address(0x871)));


extern volatile __bit LATC2 __attribute__((address(0x872)));


extern volatile __bit LATC3 __attribute__((address(0x873)));


extern volatile __bit LATC4 __attribute__((address(0x874)));


extern volatile __bit LATC5 __attribute__((address(0x875)));


extern volatile __bit LATC6 __attribute__((address(0x876)));


extern volatile __bit LATC7 __attribute__((address(0x877)));


extern volatile __bit LATD0 __attribute__((address(0x878)));


extern volatile __bit LATD1 __attribute__((address(0x879)));


extern volatile __bit LATD2 __attribute__((address(0x87A)));


extern volatile __bit LATD3 __attribute__((address(0x87B)));


extern volatile __bit LATD4 __attribute__((address(0x87C)));


extern volatile __bit LATD5 __attribute__((address(0x87D)));


extern volatile __bit LATD6 __attribute__((address(0x87E)));


extern volatile __bit LATD7 __attribute__((address(0x87F)));


extern volatile __bit LATE0 __attribute__((address(0x880)));


extern volatile __bit LATE1 __attribute__((address(0x881)));


extern volatile __bit LATE2 __attribute__((address(0x882)));


extern volatile __bit LC1D1S0 __attribute__((address(0x7890)));


extern volatile __bit LC1D1S1 __attribute__((address(0x7891)));


extern volatile __bit LC1D1S2 __attribute__((address(0x7892)));


extern volatile __bit LC1D1S3 __attribute__((address(0x7893)));


extern volatile __bit LC1D1S4 __attribute__((address(0x7894)));


extern volatile __bit LC1D2S0 __attribute__((address(0x7898)));


extern volatile __bit LC1D2S1 __attribute__((address(0x7899)));


extern volatile __bit LC1D2S2 __attribute__((address(0x789A)));


extern volatile __bit LC1D2S3 __attribute__((address(0x789B)));


extern volatile __bit LC1D2S4 __attribute__((address(0x789C)));


extern volatile __bit LC1D3S0 __attribute__((address(0x78A0)));


extern volatile __bit LC1D3S1 __attribute__((address(0x78A1)));


extern volatile __bit LC1D3S2 __attribute__((address(0x78A2)));


extern volatile __bit LC1D3S3 __attribute__((address(0x78A3)));


extern volatile __bit LC1D3S4 __attribute__((address(0x78A4)));


extern volatile __bit LC1D4S0 __attribute__((address(0x78A8)));


extern volatile __bit LC1D4S1 __attribute__((address(0x78A9)));


extern volatile __bit LC1D4S2 __attribute__((address(0x78AA)));


extern volatile __bit LC1D4S3 __attribute__((address(0x78AB)));


extern volatile __bit LC1D4S4 __attribute__((address(0x78AC)));


extern volatile __bit LC1EN __attribute__((address(0x7887)));


extern volatile __bit LC1G1D1N __attribute__((address(0x78B0)));


extern volatile __bit LC1G1D1T __attribute__((address(0x78B1)));


extern volatile __bit LC1G1D2N __attribute__((address(0x78B2)));


extern volatile __bit LC1G1D2T __attribute__((address(0x78B3)));


extern volatile __bit LC1G1D3N __attribute__((address(0x78B4)));


extern volatile __bit LC1G1D3T __attribute__((address(0x78B5)));


extern volatile __bit LC1G1D4N __attribute__((address(0x78B6)));


extern volatile __bit LC1G1D4T __attribute__((address(0x78B7)));


extern volatile __bit LC1G1POL __attribute__((address(0x7888)));


extern volatile __bit LC1G2D1N __attribute__((address(0x78B8)));


extern volatile __bit LC1G2D1T __attribute__((address(0x78B9)));


extern volatile __bit LC1G2D2N __attribute__((address(0x78BA)));


extern volatile __bit LC1G2D2T __attribute__((address(0x78BB)));


extern volatile __bit LC1G2D3N __attribute__((address(0x78BC)));


extern volatile __bit LC1G2D3T __attribute__((address(0x78BD)));


extern volatile __bit LC1G2D4N __attribute__((address(0x78BE)));


extern volatile __bit LC1G2D4T __attribute__((address(0x78BF)));


extern volatile __bit LC1G2POL __attribute__((address(0x7889)));


extern volatile __bit LC1G3D1N __attribute__((address(0x78C0)));


extern volatile __bit LC1G3D1T __attribute__((address(0x78C1)));


extern volatile __bit LC1G3D2N __attribute__((address(0x78C2)));


extern volatile __bit LC1G3D2T __attribute__((address(0x78C3)));


extern volatile __bit LC1G3D3N __attribute__((address(0x78C4)));


extern volatile __bit LC1G3D3T __attribute__((address(0x78C5)));


extern volatile __bit LC1G3D4N __attribute__((address(0x78C6)));


extern volatile __bit LC1G3D4T __attribute__((address(0x78C7)));


extern volatile __bit LC1G3POL __attribute__((address(0x788A)));


extern volatile __bit LC1G4D1N __attribute__((address(0x78C8)));


extern volatile __bit LC1G4D1T __attribute__((address(0x78C9)));


extern volatile __bit LC1G4D2N __attribute__((address(0x78CA)));


extern volatile __bit LC1G4D2T __attribute__((address(0x78CB)));


extern volatile __bit LC1G4D3N __attribute__((address(0x78CC)));


extern volatile __bit LC1G4D3T __attribute__((address(0x78CD)));


extern volatile __bit LC1G4D4N __attribute__((address(0x78CE)));


extern volatile __bit LC1G4D4T __attribute__((address(0x78CF)));


extern volatile __bit LC1G4POL __attribute__((address(0x788B)));


extern volatile __bit LC1INTN __attribute__((address(0x7883)));


extern volatile __bit LC1INTP __attribute__((address(0x7884)));


extern volatile __bit LC1MODE0 __attribute__((address(0x7880)));


extern volatile __bit LC1MODE1 __attribute__((address(0x7881)));


extern volatile __bit LC1MODE2 __attribute__((address(0x7882)));


extern volatile __bit LC1OUT __attribute__((address(0x7885)));


extern volatile __bit LC1POL __attribute__((address(0x788F)));


extern volatile __bit LC2D1S0 __attribute__((address(0x78E0)));


extern volatile __bit LC2D1S1 __attribute__((address(0x78E1)));


extern volatile __bit LC2D1S2 __attribute__((address(0x78E2)));


extern volatile __bit LC2D1S3 __attribute__((address(0x78E3)));


extern volatile __bit LC2D1S4 __attribute__((address(0x78E4)));


extern volatile __bit LC2D2S0 __attribute__((address(0x78E8)));


extern volatile __bit LC2D2S1 __attribute__((address(0x78E9)));


extern volatile __bit LC2D2S2 __attribute__((address(0x78EA)));


extern volatile __bit LC2D2S3 __attribute__((address(0x78EB)));


extern volatile __bit LC2D2S4 __attribute__((address(0x78EC)));


extern volatile __bit LC2D3S0 __attribute__((address(0x78F0)));


extern volatile __bit LC2D3S1 __attribute__((address(0x78F1)));


extern volatile __bit LC2D3S2 __attribute__((address(0x78F2)));


extern volatile __bit LC2D3S3 __attribute__((address(0x78F3)));


extern volatile __bit LC2D3S4 __attribute__((address(0x78F4)));


extern volatile __bit LC2D4S0 __attribute__((address(0x78F8)));


extern volatile __bit LC2D4S1 __attribute__((address(0x78F9)));


extern volatile __bit LC2D4S2 __attribute__((address(0x78FA)));


extern volatile __bit LC2D4S3 __attribute__((address(0x78FB)));


extern volatile __bit LC2D4S4 __attribute__((address(0x78FC)));


extern volatile __bit LC2EN __attribute__((address(0x78D7)));


extern volatile __bit LC2G1D1N __attribute__((address(0x7900)));


extern volatile __bit LC2G1D1T __attribute__((address(0x7901)));


extern volatile __bit LC2G1D2N __attribute__((address(0x7902)));


extern volatile __bit LC2G1D2T __attribute__((address(0x7903)));


extern volatile __bit LC2G1D3N __attribute__((address(0x7904)));


extern volatile __bit LC2G1D3T __attribute__((address(0x7905)));


extern volatile __bit LC2G1D4N __attribute__((address(0x7906)));


extern volatile __bit LC2G1D4T __attribute__((address(0x7907)));


extern volatile __bit LC2G1POL __attribute__((address(0x78D8)));


extern volatile __bit LC2G2D1N __attribute__((address(0x7908)));


extern volatile __bit LC2G2D1T __attribute__((address(0x7909)));


extern volatile __bit LC2G2D2N __attribute__((address(0x790A)));


extern volatile __bit LC2G2D2T __attribute__((address(0x790B)));


extern volatile __bit LC2G2D3N __attribute__((address(0x790C)));


extern volatile __bit LC2G2D3T __attribute__((address(0x790D)));


extern volatile __bit LC2G2D4N __attribute__((address(0x790E)));


extern volatile __bit LC2G2D4T __attribute__((address(0x790F)));


extern volatile __bit LC2G2POL __attribute__((address(0x78D9)));


extern volatile __bit LC2G3D1N __attribute__((address(0x7910)));


extern volatile __bit LC2G3D1T __attribute__((address(0x7911)));


extern volatile __bit LC2G3D2N __attribute__((address(0x7912)));


extern volatile __bit LC2G3D2T __attribute__((address(0x7913)));


extern volatile __bit LC2G3D3N __attribute__((address(0x7914)));


extern volatile __bit LC2G3D3T __attribute__((address(0x7915)));


extern volatile __bit LC2G3D4N __attribute__((address(0x7916)));


extern volatile __bit LC2G3D4T __attribute__((address(0x7917)));


extern volatile __bit LC2G3POL __attribute__((address(0x78DA)));


extern volatile __bit LC2G4D1N __attribute__((address(0x7918)));


extern volatile __bit LC2G4D1T __attribute__((address(0x7919)));


extern volatile __bit LC2G4D2N __attribute__((address(0x791A)));


extern volatile __bit LC2G4D2T __attribute__((address(0x791B)));


extern volatile __bit LC2G4D3N __attribute__((address(0x791C)));


extern volatile __bit LC2G4D3T __attribute__((address(0x791D)));


extern volatile __bit LC2G4D4N __attribute__((address(0x791E)));


extern volatile __bit LC2G4D4T __attribute__((address(0x791F)));


extern volatile __bit LC2G4POL __attribute__((address(0x78DB)));


extern volatile __bit LC2INTN __attribute__((address(0x78D3)));


extern volatile __bit LC2INTP __attribute__((address(0x78D4)));


extern volatile __bit LC2MODE0 __attribute__((address(0x78D0)));


extern volatile __bit LC2MODE1 __attribute__((address(0x78D1)));


extern volatile __bit LC2MODE2 __attribute__((address(0x78D2)));


extern volatile __bit LC2OUT __attribute__((address(0x78D5)));


extern volatile __bit LC2POL __attribute__((address(0x78DF)));


extern volatile __bit LC3D1S0 __attribute__((address(0x7930)));


extern volatile __bit LC3D1S1 __attribute__((address(0x7931)));


extern volatile __bit LC3D1S2 __attribute__((address(0x7932)));


extern volatile __bit LC3D1S3 __attribute__((address(0x7933)));


extern volatile __bit LC3D1S4 __attribute__((address(0x7934)));


extern volatile __bit LC3D2S0 __attribute__((address(0x7938)));


extern volatile __bit LC3D2S1 __attribute__((address(0x7939)));


extern volatile __bit LC3D2S2 __attribute__((address(0x793A)));


extern volatile __bit LC3D2S3 __attribute__((address(0x793B)));


extern volatile __bit LC3D2S4 __attribute__((address(0x793C)));


extern volatile __bit LC3D3S0 __attribute__((address(0x7940)));


extern volatile __bit LC3D3S1 __attribute__((address(0x7941)));


extern volatile __bit LC3D3S2 __attribute__((address(0x7942)));


extern volatile __bit LC3D3S3 __attribute__((address(0x7943)));


extern volatile __bit LC3D3S4 __attribute__((address(0x7944)));


extern volatile __bit LC3D4S0 __attribute__((address(0x7948)));


extern volatile __bit LC3D4S1 __attribute__((address(0x7949)));


extern volatile __bit LC3D4S2 __attribute__((address(0x794A)));


extern volatile __bit LC3D4S3 __attribute__((address(0x794B)));


extern volatile __bit LC3D4S4 __attribute__((address(0x794C)));


extern volatile __bit LC3EN __attribute__((address(0x7927)));


extern volatile __bit LC3G1D1N __attribute__((address(0x7950)));


extern volatile __bit LC3G1D1T __attribute__((address(0x7951)));


extern volatile __bit LC3G1D2N __attribute__((address(0x7952)));


extern volatile __bit LC3G1D2T __attribute__((address(0x7953)));


extern volatile __bit LC3G1D3N __attribute__((address(0x7954)));


extern volatile __bit LC3G1D3T __attribute__((address(0x7955)));


extern volatile __bit LC3G1D4N __attribute__((address(0x7956)));


extern volatile __bit LC3G1D4T __attribute__((address(0x7957)));


extern volatile __bit LC3G1POL __attribute__((address(0x7928)));


extern volatile __bit LC3G2D1N __attribute__((address(0x7958)));


extern volatile __bit LC3G2D1T __attribute__((address(0x7959)));


extern volatile __bit LC3G2D2N __attribute__((address(0x795A)));


extern volatile __bit LC3G2D2T __attribute__((address(0x795B)));


extern volatile __bit LC3G2D3N __attribute__((address(0x795C)));


extern volatile __bit LC3G2D3T __attribute__((address(0x795D)));


extern volatile __bit LC3G2D4N __attribute__((address(0x795E)));


extern volatile __bit LC3G2D4T __attribute__((address(0x795F)));


extern volatile __bit LC3G2POL __attribute__((address(0x7929)));


extern volatile __bit LC3G3D1N __attribute__((address(0x7960)));


extern volatile __bit LC3G3D1T __attribute__((address(0x7961)));


extern volatile __bit LC3G3D2N __attribute__((address(0x7962)));


extern volatile __bit LC3G3D2T __attribute__((address(0x7963)));


extern volatile __bit LC3G3D3N __attribute__((address(0x7964)));


extern volatile __bit LC3G3D3T __attribute__((address(0x7965)));


extern volatile __bit LC3G3D4N __attribute__((address(0x7966)));


extern volatile __bit LC3G3D4T __attribute__((address(0x7967)));


extern volatile __bit LC3G3POL __attribute__((address(0x792A)));


extern volatile __bit LC3G4D1N __attribute__((address(0x7968)));


extern volatile __bit LC3G4D1T __attribute__((address(0x7969)));


extern volatile __bit LC3G4D2N __attribute__((address(0x796A)));


extern volatile __bit LC3G4D2T __attribute__((address(0x796B)));


extern volatile __bit LC3G4D3N __attribute__((address(0x796C)));


extern volatile __bit LC3G4D3T __attribute__((address(0x796D)));


extern volatile __bit LC3G4D4N __attribute__((address(0x796E)));


extern volatile __bit LC3G4D4T __attribute__((address(0x796F)));


extern volatile __bit LC3G4POL __attribute__((address(0x792B)));


extern volatile __bit LC3INTN __attribute__((address(0x7923)));


extern volatile __bit LC3INTP __attribute__((address(0x7924)));


extern volatile __bit LC3MODE0 __attribute__((address(0x7920)));


extern volatile __bit LC3MODE1 __attribute__((address(0x7921)));


extern volatile __bit LC3MODE2 __attribute__((address(0x7922)));


extern volatile __bit LC3OUT __attribute__((address(0x7925)));


extern volatile __bit LC3POL __attribute__((address(0x792F)));


extern volatile __bit LC4D1S0 __attribute__((address(0x7980)));


extern volatile __bit LC4D1S1 __attribute__((address(0x7981)));


extern volatile __bit LC4D1S2 __attribute__((address(0x7982)));


extern volatile __bit LC4D1S3 __attribute__((address(0x7983)));


extern volatile __bit LC4D1S4 __attribute__((address(0x7984)));


extern volatile __bit LC4D2S0 __attribute__((address(0x7988)));


extern volatile __bit LC4D2S1 __attribute__((address(0x7989)));


extern volatile __bit LC4D2S2 __attribute__((address(0x798A)));


extern volatile __bit LC4D2S3 __attribute__((address(0x798B)));


extern volatile __bit LC4D2S4 __attribute__((address(0x798C)));


extern volatile __bit LC4D3S0 __attribute__((address(0x7990)));


extern volatile __bit LC4D3S1 __attribute__((address(0x7991)));


extern volatile __bit LC4D3S2 __attribute__((address(0x7992)));


extern volatile __bit LC4D3S3 __attribute__((address(0x7993)));


extern volatile __bit LC4D3S4 __attribute__((address(0x7994)));


extern volatile __bit LC4D4S0 __attribute__((address(0x7998)));


extern volatile __bit LC4D4S1 __attribute__((address(0x7999)));


extern volatile __bit LC4D4S2 __attribute__((address(0x799A)));


extern volatile __bit LC4D4S3 __attribute__((address(0x799B)));


extern volatile __bit LC4D4S4 __attribute__((address(0x799C)));


extern volatile __bit LC4EN __attribute__((address(0x7977)));


extern volatile __bit LC4G1D1N __attribute__((address(0x79A0)));


extern volatile __bit LC4G1D1T __attribute__((address(0x79A1)));


extern volatile __bit LC4G1D2N __attribute__((address(0x79A2)));


extern volatile __bit LC4G1D2T __attribute__((address(0x79A3)));


extern volatile __bit LC4G1D3N __attribute__((address(0x79A4)));


extern volatile __bit LC4G1D3T __attribute__((address(0x79A5)));


extern volatile __bit LC4G1D4N __attribute__((address(0x79A6)));


extern volatile __bit LC4G1D4T __attribute__((address(0x79A7)));


extern volatile __bit LC4G1POL __attribute__((address(0x7978)));


extern volatile __bit LC4G2D1N __attribute__((address(0x79A8)));


extern volatile __bit LC4G2D1T __attribute__((address(0x79A9)));


extern volatile __bit LC4G2D2N __attribute__((address(0x79AA)));


extern volatile __bit LC4G2D2T __attribute__((address(0x79AB)));


extern volatile __bit LC4G2D3N __attribute__((address(0x79AC)));


extern volatile __bit LC4G2D3T __attribute__((address(0x79AD)));


extern volatile __bit LC4G2D4N __attribute__((address(0x79AE)));


extern volatile __bit LC4G2D4T __attribute__((address(0x79AF)));


extern volatile __bit LC4G2POL __attribute__((address(0x7979)));


extern volatile __bit LC4G3D1N __attribute__((address(0x79B0)));


extern volatile __bit LC4G3D1T __attribute__((address(0x79B1)));


extern volatile __bit LC4G3D2N __attribute__((address(0x79B2)));


extern volatile __bit LC4G3D2T __attribute__((address(0x79B3)));


extern volatile __bit LC4G3D3N __attribute__((address(0x79B4)));


extern volatile __bit LC4G3D3T __attribute__((address(0x79B5)));


extern volatile __bit LC4G3D4N __attribute__((address(0x79B6)));


extern volatile __bit LC4G3D4T __attribute__((address(0x79B7)));


extern volatile __bit LC4G3POL __attribute__((address(0x797A)));


extern volatile __bit LC4G4D1N __attribute__((address(0x79B8)));


extern volatile __bit LC4G4D1T __attribute__((address(0x79B9)));


extern volatile __bit LC4G4D2N __attribute__((address(0x79BA)));


extern volatile __bit LC4G4D2T __attribute__((address(0x79BB)));


extern volatile __bit LC4G4D3N __attribute__((address(0x79BC)));


extern volatile __bit LC4G4D3T __attribute__((address(0x79BD)));


extern volatile __bit LC4G4D4N __attribute__((address(0x79BE)));


extern volatile __bit LC4G4D4T __attribute__((address(0x79BF)));


extern volatile __bit LC4G4POL __attribute__((address(0x797B)));


extern volatile __bit LC4INTN __attribute__((address(0x7973)));


extern volatile __bit LC4INTP __attribute__((address(0x7974)));


extern volatile __bit LC4MODE0 __attribute__((address(0x7970)));


extern volatile __bit LC4MODE1 __attribute__((address(0x7971)));


extern volatile __bit LC4MODE2 __attribute__((address(0x7972)));


extern volatile __bit LC4OUT __attribute__((address(0x7975)));


extern volatile __bit LC4POL __attribute__((address(0x797F)));


extern volatile __bit LFIOFR __attribute__((address(0x4D1)));


extern volatile __bit LWLO __attribute__((address(0xCAD)));


extern volatile __bit MC1OUT __attribute__((address(0x8A8)));


extern volatile __bit MC2OUT __attribute__((address(0x8A9)));


extern volatile __bit MCLC1OUT __attribute__((address(0x7878)));


extern volatile __bit MCLC2OUT __attribute__((address(0x7879)));


extern volatile __bit MCLC3OUT __attribute__((address(0x787A)));


extern volatile __bit MCLC4OUT __attribute__((address(0x787B)));


extern volatile __bit MFIOFR __attribute__((address(0x4D2)));


extern volatile __bit MLC1OUT __attribute__((address(0x7878)));


extern volatile __bit MLC2OUT __attribute__((address(0x7879)));


extern volatile __bit MLC3OUT __attribute__((address(0x787A)));


extern volatile __bit MLC4OUT __attribute__((address(0x787B)));


extern volatile __bit MSK0 __attribute__((address(0x1098)));


extern volatile __bit MSK1 __attribute__((address(0x1099)));


extern volatile __bit MSK2 __attribute__((address(0x109A)));


extern volatile __bit MSK3 __attribute__((address(0x109B)));


extern volatile __bit MSK4 __attribute__((address(0x109C)));


extern volatile __bit MSK5 __attribute__((address(0x109D)));


extern volatile __bit MSK6 __attribute__((address(0x109E)));


extern volatile __bit MSK7 __attribute__((address(0x109F)));


extern volatile __bit N1CKS0 __attribute__((address(0x24F8)));


extern volatile __bit N1CKS1 __attribute__((address(0x24F9)));


extern volatile __bit N1EN __attribute__((address(0x24F7)));


extern volatile __bit N1OUT __attribute__((address(0x24F5)));


extern volatile __bit N1PFM __attribute__((address(0x24F0)));


extern volatile __bit N1POL __attribute__((address(0x24F4)));


extern volatile __bit N1PWS0 __attribute__((address(0x24FD)));


extern volatile __bit N1PWS1 __attribute__((address(0x24FE)));


extern volatile __bit N1PWS2 __attribute__((address(0x24FF)));


extern volatile __bit NCO1ACC0 __attribute__((address(0x24C0)));


extern volatile __bit NCO1ACC1 __attribute__((address(0x24C1)));


extern volatile __bit NCO1ACC10 __attribute__((address(0x24CA)));


extern volatile __bit NCO1ACC11 __attribute__((address(0x24CB)));


extern volatile __bit NCO1ACC12 __attribute__((address(0x24CC)));


extern volatile __bit NCO1ACC13 __attribute__((address(0x24CD)));


extern volatile __bit NCO1ACC14 __attribute__((address(0x24CE)));


extern volatile __bit NCO1ACC15 __attribute__((address(0x24CF)));


extern volatile __bit NCO1ACC16 __attribute__((address(0x24D0)));


extern volatile __bit NCO1ACC17 __attribute__((address(0x24D1)));


extern volatile __bit NCO1ACC18 __attribute__((address(0x24D2)));


extern volatile __bit NCO1ACC19 __attribute__((address(0x24D3)));


extern volatile __bit NCO1ACC2 __attribute__((address(0x24C2)));


extern volatile __bit NCO1ACC3 __attribute__((address(0x24C3)));


extern volatile __bit NCO1ACC4 __attribute__((address(0x24C4)));


extern volatile __bit NCO1ACC5 __attribute__((address(0x24C5)));


extern volatile __bit NCO1ACC6 __attribute__((address(0x24C6)));


extern volatile __bit NCO1ACC7 __attribute__((address(0x24C7)));


extern volatile __bit NCO1ACC8 __attribute__((address(0x24C8)));


extern volatile __bit NCO1ACC9 __attribute__((address(0x24C9)));


extern volatile __bit NCO1INC0 __attribute__((address(0x24D8)));


extern volatile __bit NCO1INC1 __attribute__((address(0x24D9)));


extern volatile __bit NCO1INC10 __attribute__((address(0x24E2)));


extern volatile __bit NCO1INC11 __attribute__((address(0x24E3)));


extern volatile __bit NCO1INC12 __attribute__((address(0x24E4)));


extern volatile __bit NCO1INC13 __attribute__((address(0x24E5)));


extern volatile __bit NCO1INC14 __attribute__((address(0x24E6)));


extern volatile __bit NCO1INC15 __attribute__((address(0x24E7)));


extern volatile __bit NCO1INC16 __attribute__((address(0x24E8)));


extern volatile __bit NCO1INC17 __attribute__((address(0x24E9)));


extern volatile __bit NCO1INC18 __attribute__((address(0x24EA)));


extern volatile __bit NCO1INC19 __attribute__((address(0x24EB)));


extern volatile __bit NCO1INC2 __attribute__((address(0x24DA)));


extern volatile __bit NCO1INC3 __attribute__((address(0x24DB)));


extern volatile __bit NCO1INC4 __attribute__((address(0x24DC)));


extern volatile __bit NCO1INC5 __attribute__((address(0x24DD)));


extern volatile __bit NCO1INC6 __attribute__((address(0x24DE)));


extern volatile __bit NCO1INC7 __attribute__((address(0x24DF)));


extern volatile __bit NCO1INC8 __attribute__((address(0x24E0)));


extern volatile __bit NCO1INC9 __attribute__((address(0x24E1)));


extern volatile __bit NCOIE __attribute__((address(0x49E)));


extern volatile __bit NCOIF __attribute__((address(0x9E)));


extern volatile __bit NSS __attribute__((address(0x8D0)));


extern volatile __bit ODA0 __attribute__((address(0x1460)));


extern volatile __bit ODA1 __attribute__((address(0x1461)));


extern volatile __bit ODA2 __attribute__((address(0x1462)));


extern volatile __bit ODA3 __attribute__((address(0x1463)));


extern volatile __bit ODA4 __attribute__((address(0x1464)));


extern volatile __bit ODA5 __attribute__((address(0x1465)));


extern volatile __bit ODA6 __attribute__((address(0x1466)));


extern volatile __bit ODA7 __attribute__((address(0x1467)));


extern volatile __bit ODB0 __attribute__((address(0x1468)));


extern volatile __bit ODB1 __attribute__((address(0x1469)));


extern volatile __bit ODB2 __attribute__((address(0x146A)));


extern volatile __bit ODB3 __attribute__((address(0x146B)));


extern volatile __bit ODB4 __attribute__((address(0x146C)));


extern volatile __bit ODB5 __attribute__((address(0x146D)));


extern volatile __bit ODB6 __attribute__((address(0x146E)));


extern volatile __bit ODB7 __attribute__((address(0x146F)));


extern volatile __bit ODC0 __attribute__((address(0x1470)));


extern volatile __bit ODC1 __attribute__((address(0x1471)));


extern volatile __bit ODC2 __attribute__((address(0x1472)));


extern volatile __bit ODC3 __attribute__((address(0x1473)));


extern volatile __bit ODC4 __attribute__((address(0x1474)));


extern volatile __bit ODC5 __attribute__((address(0x1475)));


extern volatile __bit ODC6 __attribute__((address(0x1476)));


extern volatile __bit ODC7 __attribute__((address(0x1477)));


extern volatile __bit ODD0 __attribute__((address(0x1478)));


extern volatile __bit ODD1 __attribute__((address(0x1479)));


extern volatile __bit ODD2 __attribute__((address(0x147A)));


extern volatile __bit ODD3 __attribute__((address(0x147B)));


extern volatile __bit ODD4 __attribute__((address(0x147C)));


extern volatile __bit ODD5 __attribute__((address(0x147D)));


extern volatile __bit ODD6 __attribute__((address(0x147E)));


extern volatile __bit ODD7 __attribute__((address(0x147F)));


extern volatile __bit ODE0 __attribute__((address(0x1480)));


extern volatile __bit ODE1 __attribute__((address(0x1481)));


extern volatile __bit ODE2 __attribute__((address(0x1482)));


extern volatile __bit OE1 __attribute__((address(0x8D5)));


extern volatile __bit OE2 __attribute__((address(0x8D4)));


extern volatile __bit OERR __attribute__((address(0xCE9)));


extern volatile __bit OPA1CH0 __attribute__((address(0x2888)));


extern volatile __bit OPA1CH1 __attribute__((address(0x2889)));


extern volatile __bit OPA1EN __attribute__((address(0x288F)));


extern volatile __bit OPA1PCH0 __attribute__((address(0x2888)));


extern volatile __bit OPA1PCH1 __attribute__((address(0x2889)));


extern volatile __bit OPA1SP __attribute__((address(0x288E)));


extern volatile __bit OPA1UG __attribute__((address(0x288C)));


extern volatile __bit OPA2CH0 __attribute__((address(0x28A8)));


extern volatile __bit OPA2CH1 __attribute__((address(0x28A9)));


extern volatile __bit OPA2EN __attribute__((address(0x28AF)));


extern volatile __bit OPA2PCH0 __attribute__((address(0x28A8)));


extern volatile __bit OPA2PCH1 __attribute__((address(0x28A9)));


extern volatile __bit OPA2SP __attribute__((address(0x28AE)));


extern volatile __bit OPA2UG __attribute__((address(0x28AC)));


extern volatile __bit OSFIE __attribute__((address(0x497)));


extern volatile __bit OSFIF __attribute__((address(0x97)));


extern volatile __bit OSTS __attribute__((address(0x4D5)));


extern volatile __bit P3TSEL0 __attribute__((address(0x14F4)));


extern volatile __bit P3TSEL1 __attribute__((address(0x14F5)));


extern volatile __bit P4TSEL0 __attribute__((address(0x14F6)));


extern volatile __bit P4TSEL1 __attribute__((address(0x14F7)));


extern volatile __bit PCIE __attribute__((address(0x10BE)));


extern volatile __bit PEIE __attribute__((address(0x5E)));


extern volatile __bit PEN __attribute__((address(0x10B2)));


extern volatile __bit PLLR __attribute__((address(0x4D6)));


extern volatile __bit PPSLOCKED __attribute__((address(0x7078)));


extern volatile __bit PS0 __attribute__((address(0x4A8)));


extern volatile __bit PS1 __attribute__((address(0x4A9)));


extern volatile __bit PS2 __attribute__((address(0x4AA)));


extern volatile __bit PSA __attribute__((address(0x4AB)));


extern volatile __bit PSS0 __attribute__((address(0x8D2)));


extern volatile __bit PSS1 __attribute__((address(0x8D3)));


extern volatile __bit PWM3DCH0 __attribute__((address(0x30C0)));


extern volatile __bit PWM3DCH1 __attribute__((address(0x30C1)));


extern volatile __bit PWM3DCH2 __attribute__((address(0x30C2)));


extern volatile __bit PWM3DCH3 __attribute__((address(0x30C3)));


extern volatile __bit PWM3DCH4 __attribute__((address(0x30C4)));


extern volatile __bit PWM3DCH5 __attribute__((address(0x30C5)));


extern volatile __bit PWM3DCH6 __attribute__((address(0x30C6)));


extern volatile __bit PWM3DCH7 __attribute__((address(0x30C7)));


extern volatile __bit PWM3DCL0 __attribute__((address(0x30BE)));


extern volatile __bit PWM3DCL1 __attribute__((address(0x30BF)));


extern volatile __bit PWM3EN __attribute__((address(0x30CF)));


extern volatile __bit PWM3OUT __attribute__((address(0x30CD)));


extern volatile __bit PWM3POL __attribute__((address(0x30CC)));


extern volatile __bit PWM4DCH0 __attribute__((address(0x30D8)));


extern volatile __bit PWM4DCH1 __attribute__((address(0x30D9)));


extern volatile __bit PWM4DCH2 __attribute__((address(0x30DA)));


extern volatile __bit PWM4DCH3 __attribute__((address(0x30DB)));


extern volatile __bit PWM4DCH4 __attribute__((address(0x30DC)));


extern volatile __bit PWM4DCH5 __attribute__((address(0x30DD)));


extern volatile __bit PWM4DCH6 __attribute__((address(0x30DE)));


extern volatile __bit PWM4DCH7 __attribute__((address(0x30DF)));


extern volatile __bit PWM4DCL0 __attribute__((address(0x30D6)));


extern volatile __bit PWM4DCL1 __attribute__((address(0x30D7)));


extern volatile __bit PWM4EN __attribute__((address(0x30E7)));


extern volatile __bit PWM4OUT __attribute__((address(0x30E5)));


extern volatile __bit PWM4POL __attribute__((address(0x30E4)));


extern volatile __bit R0 __attribute__((address(0x8D8)));


extern volatile __bit R1 __attribute__((address(0x8D9)));


extern volatile __bit R2 __attribute__((address(0x8DA)));


extern volatile __bit R3 __attribute__((address(0x8DB)));


extern volatile __bit R4 __attribute__((address(0x8DC)));


extern volatile __bit RA0 __attribute__((address(0x60)));


extern volatile __bit RA1 __attribute__((address(0x61)));


extern volatile __bit RA2 __attribute__((address(0x62)));


extern volatile __bit RA3 __attribute__((address(0x63)));


extern volatile __bit RA4 __attribute__((address(0x64)));


extern volatile __bit RA5 __attribute__((address(0x65)));


extern volatile __bit RA6 __attribute__((address(0x66)));


extern volatile __bit RA7 __attribute__((address(0x67)));


extern volatile __bit RB0 __attribute__((address(0x68)));


extern volatile __bit RB1 __attribute__((address(0x69)));


extern volatile __bit RB2 __attribute__((address(0x6A)));


extern volatile __bit RB3 __attribute__((address(0x6B)));


extern volatile __bit RB4 __attribute__((address(0x6C)));


extern volatile __bit RB5 __attribute__((address(0x6D)));


extern volatile __bit RB6 __attribute__((address(0x6E)));


extern volatile __bit RB7 __attribute__((address(0x6F)));


extern volatile __bit RC0 __attribute__((address(0x70)));


extern volatile __bit RC1 __attribute__((address(0x71)));


extern volatile __bit RC2 __attribute__((address(0x72)));


extern volatile __bit RC3 __attribute__((address(0x73)));


extern volatile __bit RC4 __attribute__((address(0x74)));


extern volatile __bit RC5 __attribute__((address(0x75)));


extern volatile __bit RC6 __attribute__((address(0x76)));


extern volatile __bit RC7 __attribute__((address(0x77)));


extern volatile __bit RCEN __attribute__((address(0x10B3)));


extern volatile __bit RCIDL __attribute__((address(0xCFE)));


extern volatile __bit RCIE __attribute__((address(0x48D)));


extern volatile __bit RCIF __attribute__((address(0x8D)));


extern volatile __bit RD __attribute__((address(0xCA8)));


extern volatile __bit RD0 __attribute__((address(0x78)));


extern volatile __bit RD1 __attribute__((address(0x79)));


extern volatile __bit RD2 __attribute__((address(0x7A)));


extern volatile __bit RD3 __attribute__((address(0x7B)));


extern volatile __bit RD4 __attribute__((address(0x7C)));


extern volatile __bit RD5 __attribute__((address(0x7D)));


extern volatile __bit RD6 __attribute__((address(0x7E)));


extern volatile __bit RD7 __attribute__((address(0x7F)));


extern volatile __bit RE0 __attribute__((address(0x80)));


extern volatile __bit RE1 __attribute__((address(0x81)));


extern volatile __bit RE2 __attribute__((address(0x82)));


extern volatile __bit RE3 __attribute__((address(0x83)));


extern volatile __bit REF0 __attribute__((address(0x8D8)));


extern volatile __bit REF1 __attribute__((address(0x8D9)));


extern volatile __bit REF2 __attribute__((address(0x8DA)));


extern volatile __bit REF3 __attribute__((address(0x8DB)));


extern volatile __bit REF4 __attribute__((address(0x8DC)));


extern volatile __bit REF5 __attribute__((address(0x8DD)));


extern volatile __bit RSEN __attribute__((address(0x10B1)));


extern volatile __bit RX9 __attribute__((address(0xCEE)));


extern volatile __bit RX9D __attribute__((address(0xCE8)));


extern volatile __bit R_nW __attribute__((address(0x10A2)));


extern volatile __bit SBCDE __attribute__((address(0x10BA)));


extern volatile __bit SBOREN __attribute__((address(0x8B7)));


extern volatile __bit SCIE __attribute__((address(0x10BD)));


extern volatile __bit SCKP __attribute__((address(0xCFC)));


extern volatile __bit SCS0 __attribute__((address(0x4C8)));


extern volatile __bit SCS1 __attribute__((address(0x4C9)));


extern volatile __bit SDAHT __attribute__((address(0x10BB)));


extern volatile __bit SEN __attribute__((address(0x10B0)));


extern volatile __bit SENDB __attribute__((address(0xCF3)));


extern volatile __bit SLRA0 __attribute__((address(0x1860)));


extern volatile __bit SLRA1 __attribute__((address(0x1861)));


extern volatile __bit SLRA2 __attribute__((address(0x1862)));


extern volatile __bit SLRA3 __attribute__((address(0x1863)));


extern volatile __bit SLRA4 __attribute__((address(0x1864)));


extern volatile __bit SLRA5 __attribute__((address(0x1865)));


extern volatile __bit SLRA6 __attribute__((address(0x1866)));


extern volatile __bit SLRA7 __attribute__((address(0x1867)));


extern volatile __bit SLRB0 __attribute__((address(0x1868)));


extern volatile __bit SLRB1 __attribute__((address(0x1869)));


extern volatile __bit SLRB2 __attribute__((address(0x186A)));


extern volatile __bit SLRB3 __attribute__((address(0x186B)));


extern volatile __bit SLRB4 __attribute__((address(0x186C)));


extern volatile __bit SLRB5 __attribute__((address(0x186D)));


extern volatile __bit SLRB6 __attribute__((address(0x186E)));


extern volatile __bit SLRB7 __attribute__((address(0x186F)));


extern volatile __bit SLRC0 __attribute__((address(0x1870)));


extern volatile __bit SLRC1 __attribute__((address(0x1871)));


extern volatile __bit SLRC2 __attribute__((address(0x1872)));


extern volatile __bit SLRC3 __attribute__((address(0x1873)));


extern volatile __bit SLRC4 __attribute__((address(0x1874)));


extern volatile __bit SLRC5 __attribute__((address(0x1875)));


extern volatile __bit SLRC6 __attribute__((address(0x1876)));


extern volatile __bit SLRC7 __attribute__((address(0x1877)));


extern volatile __bit SLRD0 __attribute__((address(0x1878)));


extern volatile __bit SLRD1 __attribute__((address(0x1879)));


extern volatile __bit SLRD2 __attribute__((address(0x187A)));


extern volatile __bit SLRD3 __attribute__((address(0x187B)));


extern volatile __bit SLRD4 __attribute__((address(0x187C)));


extern volatile __bit SLRD5 __attribute__((address(0x187D)));


extern volatile __bit SLRD6 __attribute__((address(0x187E)));


extern volatile __bit SLRD7 __attribute__((address(0x187F)));


extern volatile __bit SLRE0 __attribute__((address(0x1880)));


extern volatile __bit SLRE1 __attribute__((address(0x1881)));


extern volatile __bit SLRE2 __attribute__((address(0x1882)));


extern volatile __bit SMP __attribute__((address(0x10A7)));


extern volatile __bit SOSCR __attribute__((address(0x4D7)));


extern volatile __bit SPEN __attribute__((address(0xCEF)));


extern volatile __bit SPLLEN __attribute__((address(0x4CF)));


extern volatile __bit SREN __attribute__((address(0xCED)));


extern volatile __bit SSP1ADD0 __attribute__((address(0x1090)));


extern volatile __bit SSP1ADD1 __attribute__((address(0x1091)));


extern volatile __bit SSP1ADD2 __attribute__((address(0x1092)));


extern volatile __bit SSP1ADD3 __attribute__((address(0x1093)));


extern volatile __bit SSP1ADD4 __attribute__((address(0x1094)));


extern volatile __bit SSP1ADD5 __attribute__((address(0x1095)));


extern volatile __bit SSP1ADD6 __attribute__((address(0x1096)));


extern volatile __bit SSP1ADD7 __attribute__((address(0x1097)));


extern volatile __bit SSP1BUF0 __attribute__((address(0x1088)));


extern volatile __bit SSP1BUF1 __attribute__((address(0x1089)));


extern volatile __bit SSP1BUF2 __attribute__((address(0x108A)));


extern volatile __bit SSP1BUF3 __attribute__((address(0x108B)));


extern volatile __bit SSP1BUF4 __attribute__((address(0x108C)));


extern volatile __bit SSP1BUF5 __attribute__((address(0x108D)));


extern volatile __bit SSP1BUF6 __attribute__((address(0x108E)));


extern volatile __bit SSP1BUF7 __attribute__((address(0x108F)));


extern volatile __bit SSP1IE __attribute__((address(0x48B)));


extern volatile __bit SSP1IF __attribute__((address(0x8B)));


extern volatile __bit SSP1MSK0 __attribute__((address(0x1098)));


extern volatile __bit SSP1MSK1 __attribute__((address(0x1099)));


extern volatile __bit SSP1MSK2 __attribute__((address(0x109A)));


extern volatile __bit SSP1MSK3 __attribute__((address(0x109B)));


extern volatile __bit SSP1MSK4 __attribute__((address(0x109C)));


extern volatile __bit SSP1MSK5 __attribute__((address(0x109D)));


extern volatile __bit SSP1MSK6 __attribute__((address(0x109E)));


extern volatile __bit SSP1MSK7 __attribute__((address(0x109F)));


extern volatile __bit SSPEN __attribute__((address(0x10AD)));


extern volatile __bit SSPM0 __attribute__((address(0x10A8)));


extern volatile __bit SSPM1 __attribute__((address(0x10A9)));


extern volatile __bit SSPM2 __attribute__((address(0x10AA)));


extern volatile __bit SSPM3 __attribute__((address(0x10AB)));


extern volatile __bit SSPOV __attribute__((address(0x10AE)));


extern volatile __bit STKOVF __attribute__((address(0x4B7)));


extern volatile __bit STKUNF __attribute__((address(0x4B6)));


extern volatile __bit SWDTEN __attribute__((address(0x4B8)));


extern volatile __bit SYNC __attribute__((address(0xCF4)));


extern volatile __bit T0CS __attribute__((address(0x4AD)));


extern volatile __bit T0IE __attribute__((address(0x5D)));


extern volatile __bit T0IF __attribute__((address(0x5A)));


extern volatile __bit T0SE __attribute__((address(0x4AC)));


extern volatile __bit T1CKPS0 __attribute__((address(0xC4)));


extern volatile __bit T1CKPS1 __attribute__((address(0xC5)));


extern volatile __bit T1GGO_nDONE __attribute__((address(0xCB)));


extern volatile __bit T1GPOL __attribute__((address(0xCE)));


extern volatile __bit T1GSPM __attribute__((address(0xCC)));


extern volatile __bit T1GSS0 __attribute__((address(0xC8)));


extern volatile __bit T1GSS1 __attribute__((address(0xC9)));


extern volatile __bit T1GTM __attribute__((address(0xCD)));


extern volatile __bit T1GVAL __attribute__((address(0xCA)));


extern volatile __bit T1OSCEN __attribute__((address(0xC3)));


extern volatile __bit T2CKPS0 __attribute__((address(0xE0)));


extern volatile __bit T2CKPS1 __attribute__((address(0xE1)));


extern volatile __bit T2OUTPS0 __attribute__((address(0xE3)));


extern volatile __bit T2OUTPS1 __attribute__((address(0xE4)));


extern volatile __bit T2OUTPS2 __attribute__((address(0xE5)));


extern volatile __bit T2OUTPS3 __attribute__((address(0xE6)));


extern volatile __bit T4CKPS0 __attribute__((address(0x20B8)));


extern volatile __bit T4CKPS1 __attribute__((address(0x20B9)));


extern volatile __bit T4OUTPS0 __attribute__((address(0x20BB)));


extern volatile __bit T4OUTPS1 __attribute__((address(0x20BC)));


extern volatile __bit T4OUTPS2 __attribute__((address(0x20BD)));


extern volatile __bit T4OUTPS3 __attribute__((address(0x20BE)));


extern volatile __bit T6CKPS0 __attribute__((address(0x20F0)));


extern volatile __bit T6CKPS1 __attribute__((address(0x20F1)));


extern volatile __bit T6OUTPS0 __attribute__((address(0x20F3)));


extern volatile __bit T6OUTPS1 __attribute__((address(0x20F4)));


extern volatile __bit T6OUTPS2 __attribute__((address(0x20F5)));


extern volatile __bit T6OUTPS3 __attribute__((address(0x20F6)));


extern volatile __bit TMR0CS __attribute__((address(0x4AD)));


extern volatile __bit TMR0IE __attribute__((address(0x5D)));


extern volatile __bit TMR0IF __attribute__((address(0x5A)));


extern volatile __bit TMR0SE __attribute__((address(0x4AC)));


extern volatile __bit TMR1CS0 __attribute__((address(0xC6)));


extern volatile __bit TMR1CS1 __attribute__((address(0xC7)));


extern volatile __bit TMR1GE __attribute__((address(0xCF)));


extern volatile __bit TMR1GIE __attribute__((address(0x48F)));


extern volatile __bit TMR1GIF __attribute__((address(0x8F)));


extern volatile __bit TMR1IE __attribute__((address(0x488)));


extern volatile __bit TMR1IF __attribute__((address(0x88)));


extern volatile __bit TMR1ON __attribute__((address(0xC0)));


extern volatile __bit TMR2IE __attribute__((address(0x489)));


extern volatile __bit TMR2IF __attribute__((address(0x89)));


extern volatile __bit TMR2ON __attribute__((address(0xE2)));


extern volatile __bit TMR4IE __attribute__((address(0x491)));


extern volatile __bit TMR4IF __attribute__((address(0x91)));


extern volatile __bit TMR4ON __attribute__((address(0x20BA)));


extern volatile __bit TMR6IE __attribute__((address(0x492)));


extern volatile __bit TMR6IF __attribute__((address(0x92)));


extern volatile __bit TMR6ON __attribute__((address(0x20F2)));


extern volatile __bit TRIGSEL0 __attribute__((address(0x4FC)));


extern volatile __bit TRIGSEL1 __attribute__((address(0x4FD)));


extern volatile __bit TRIGSEL2 __attribute__((address(0x4FE)));


extern volatile __bit TRIGSEL3 __attribute__((address(0x4FF)));


extern volatile __bit TRISA0 __attribute__((address(0x460)));


extern volatile __bit TRISA1 __attribute__((address(0x461)));


extern volatile __bit TRISA2 __attribute__((address(0x462)));


extern volatile __bit TRISA3 __attribute__((address(0x463)));


extern volatile __bit TRISA4 __attribute__((address(0x464)));


extern volatile __bit TRISA5 __attribute__((address(0x465)));


extern volatile __bit TRISA6 __attribute__((address(0x466)));


extern volatile __bit TRISA7 __attribute__((address(0x467)));


extern volatile __bit TRISB0 __attribute__((address(0x468)));


extern volatile __bit TRISB1 __attribute__((address(0x469)));


extern volatile __bit TRISB2 __attribute__((address(0x46A)));


extern volatile __bit TRISB3 __attribute__((address(0x46B)));


extern volatile __bit TRISB4 __attribute__((address(0x46C)));


extern volatile __bit TRISB5 __attribute__((address(0x46D)));


extern volatile __bit TRISB6 __attribute__((address(0x46E)));


extern volatile __bit TRISB7 __attribute__((address(0x46F)));


extern volatile __bit TRISC0 __attribute__((address(0x470)));


extern volatile __bit TRISC1 __attribute__((address(0x471)));


extern volatile __bit TRISC2 __attribute__((address(0x472)));


extern volatile __bit TRISC3 __attribute__((address(0x473)));


extern volatile __bit TRISC4 __attribute__((address(0x474)));


extern volatile __bit TRISC5 __attribute__((address(0x475)));


extern volatile __bit TRISC6 __attribute__((address(0x476)));


extern volatile __bit TRISC7 __attribute__((address(0x477)));


extern volatile __bit TRISD0 __attribute__((address(0x478)));


extern volatile __bit TRISD1 __attribute__((address(0x479)));


extern volatile __bit TRISD2 __attribute__((address(0x47A)));


extern volatile __bit TRISD3 __attribute__((address(0x47B)));


extern volatile __bit TRISD4 __attribute__((address(0x47C)));


extern volatile __bit TRISD5 __attribute__((address(0x47D)));


extern volatile __bit TRISD6 __attribute__((address(0x47E)));


extern volatile __bit TRISD7 __attribute__((address(0x47F)));


extern volatile __bit TRISE0 __attribute__((address(0x480)));


extern volatile __bit TRISE1 __attribute__((address(0x481)));


extern volatile __bit TRISE2 __attribute__((address(0x482)));


extern volatile __bit TRISE3 __attribute__((address(0x483)));


extern volatile __bit TRMT __attribute__((address(0xCF1)));


extern volatile __bit TSEN __attribute__((address(0x8BD)));


extern volatile __bit TSRNG __attribute__((address(0x8BC)));


extern volatile __bit TUN0 __attribute__((address(0x4C0)));


extern volatile __bit TUN1 __attribute__((address(0x4C1)));


extern volatile __bit TUN2 __attribute__((address(0x4C2)));


extern volatile __bit TUN3 __attribute__((address(0x4C3)));


extern volatile __bit TUN4 __attribute__((address(0x4C4)));


extern volatile __bit TUN5 __attribute__((address(0x4C5)));


extern volatile __bit TX9 __attribute__((address(0xCF6)));


extern volatile __bit TX9D __attribute__((address(0xCF0)));


extern volatile __bit TXEN __attribute__((address(0xCF5)));


extern volatile __bit TXIE __attribute__((address(0x48C)));


extern volatile __bit TXIF __attribute__((address(0x8C)));


extern volatile __bit UA __attribute__((address(0x10A1)));


extern volatile __bit VREGPM __attribute__((address(0xCB9)));


extern volatile __bit WCOL __attribute__((address(0x10AF)));


extern volatile __bit WDTPS0 __attribute__((address(0x4B9)));


extern volatile __bit WDTPS1 __attribute__((address(0x4BA)));


extern volatile __bit WDTPS2 __attribute__((address(0x4BB)));


extern volatile __bit WDTPS3 __attribute__((address(0x4BC)));


extern volatile __bit WDTPS4 __attribute__((address(0x4BD)));


extern volatile __bit WPUA0 __attribute__((address(0x1060)));


extern volatile __bit WPUA1 __attribute__((address(0x1061)));


extern volatile __bit WPUA2 __attribute__((address(0x1062)));


extern volatile __bit WPUA3 __attribute__((address(0x1063)));


extern volatile __bit WPUA4 __attribute__((address(0x1064)));


extern volatile __bit WPUA5 __attribute__((address(0x1065)));


extern volatile __bit WPUA6 __attribute__((address(0x1066)));


extern volatile __bit WPUA7 __attribute__((address(0x1067)));


extern volatile __bit WPUB0 __attribute__((address(0x1068)));


extern volatile __bit WPUB1 __attribute__((address(0x1069)));


extern volatile __bit WPUB2 __attribute__((address(0x106A)));


extern volatile __bit WPUB3 __attribute__((address(0x106B)));


extern volatile __bit WPUB4 __attribute__((address(0x106C)));


extern volatile __bit WPUB5 __attribute__((address(0x106D)));


extern volatile __bit WPUB6 __attribute__((address(0x106E)));


extern volatile __bit WPUB7 __attribute__((address(0x106F)));


extern volatile __bit WPUC0 __attribute__((address(0x1070)));


extern volatile __bit WPUC1 __attribute__((address(0x1071)));


extern volatile __bit WPUC2 __attribute__((address(0x1072)));


extern volatile __bit WPUC3 __attribute__((address(0x1073)));


extern volatile __bit WPUC4 __attribute__((address(0x1074)));


extern volatile __bit WPUC5 __attribute__((address(0x1075)));


extern volatile __bit WPUC6 __attribute__((address(0x1076)));


extern volatile __bit WPUC7 __attribute__((address(0x1077)));


extern volatile __bit WPUD0 __attribute__((address(0x1078)));


extern volatile __bit WPUD1 __attribute__((address(0x1079)));


extern volatile __bit WPUD2 __attribute__((address(0x107A)));


extern volatile __bit WPUD3 __attribute__((address(0x107B)));


extern volatile __bit WPUD4 __attribute__((address(0x107C)));


extern volatile __bit WPUD5 __attribute__((address(0x107D)));


extern volatile __bit WPUD6 __attribute__((address(0x107E)));


extern volatile __bit WPUD7 __attribute__((address(0x107F)));


extern volatile __bit WPUE0 __attribute__((address(0x1080)));


extern volatile __bit WPUE1 __attribute__((address(0x1081)));


extern volatile __bit WPUE2 __attribute__((address(0x1082)));


extern volatile __bit WPUE3 __attribute__((address(0x1083)));


extern volatile __bit WR __attribute__((address(0xCA9)));


extern volatile __bit WREN __attribute__((address(0xCAA)));


extern volatile __bit WRERR __attribute__((address(0xCAB)));


extern volatile __bit WUE __attribute__((address(0xCF9)));


extern volatile __bit ZCD1EN __attribute__((address(0x8E7)));


extern volatile __bit ZCD1INTN __attribute__((address(0x8E0)));


extern volatile __bit ZCD1INTP __attribute__((address(0x8E1)));


extern volatile __bit ZCD1OUT __attribute__((address(0x8E5)));


extern volatile __bit ZCD1POL __attribute__((address(0x8E4)));


extern volatile __bit ZCDIE __attribute__((address(0x49C)));


extern volatile __bit ZCDIF __attribute__((address(0x9C)));


extern volatile __bit ZERO __attribute__((address(0x1A)));


extern volatile __bit Z_SHAD __attribute__((address(0x7F22)));


extern volatile __bit nBOR __attribute__((address(0x4B0)));


extern volatile __bit nPD __attribute__((address(0x1B)));


extern volatile __bit nPOR __attribute__((address(0x4B1)));


extern volatile __bit nRI __attribute__((address(0x4B2)));


extern volatile __bit nRMCLR __attribute__((address(0x4B3)));


extern volatile __bit nRWDT __attribute__((address(0x4B4)));


extern volatile __bit nT1SYNC __attribute__((address(0xC2)));


extern volatile __bit nTO __attribute__((address(0x1C)));


extern volatile __bit nWPUEN __attribute__((address(0x4AF)));
# 285 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic_chip_select.h" 2 3
# 14 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 2 3
# 76 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 3
__attribute__((__unsupported__("The " "FLASH_READ" " macro function is no longer supported. Please use the MPLAB X MCC."))) unsigned char __flash_read(unsigned short addr);

__attribute__((__unsupported__("The " "FLASH_WRITE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_write(unsigned short addr, unsigned short data);

__attribute__((__unsupported__("The " "FLASH_ERASE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_erase(unsigned short addr);



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\eeprom_routines.h" 1 3
# 84 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 2 3
# 118 "C:/Program Files/Microchip/MPLABX/v6.15/packs/Microchip/PIC12-16F1xxx_DFP/1.6.241/xc8\\pic\\include\\pic.h" 3
extern __bank0 unsigned char __resetbits;
extern __bank0 __bit __powerdown;
extern __bank0 __bit __timeout;
# 28 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\xc.h" 2 3
# 45 "./PIC16F1719_Internal.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdio.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 12 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 143 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef short ssize_t;
# 255 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 409 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);





int ungetc(int, FILE *);
int getch(void);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);





void putch(char);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 46 "./PIC16F1719_Internal.h" 2





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stdbool.h" 1 3
# 51 "./PIC16F1719_Internal.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stddef.h" 1 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 138 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int ptrdiff_t;
# 20 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\stddef.h" 2 3
# 52 "./PIC16F1719_Internal.h" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 1 3
# 15 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 39 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\bits/alltypes.h" 3
typedef float float_t;




typedef double double_t;
# 16 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 2 3
# 42 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 3
int __fpclassifyf(float);







int __signbitf(float);
# 59 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 3
double acos(double);
float acosf(float);
long double acosl(long double);



double acosh(double);
float acoshf(float);
long double acoshl(long double);



double asin(double);
float asinf(float);
long double asinl(long double);



double asinh(double);
float asinhf(float);
long double asinhl(long double);



double atan(double);
float atanf(float);
long double atanl(long double);



double atan2(double, double);
float atan2f(float, float);
long double atan2l(long double, long double);



double atanh(double);
float atanhf(float);
long double atanhl(long double);



double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);



double ceil(double);
float ceilf(float);
long double ceill(long double);



double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);



double cos(double);
float cosf(float);
long double cosl(long double);



double cosh(double);
float coshf(float);
long double coshl(long double);



double erf(double);
float erff(float);
long double erfl(long double);



double erfc(double);
float erfcf(float);
long double erfcl(long double);



double exp(double);
float expf(float);
long double expl(long double);



double exp2(double);
float exp2f(float);
long double exp2l(long double);



double expm1(double);
float expm1f(float);
long double expm1l(long double);



double fabs(double);
float fabsf(float);
long double fabsl(long double);



double fdim(double, double);
float fdimf(float, float);
long double fdiml(long double, long double);



double floor(double);
float floorf(float);
long double floorl(long double);



double fma(double, double, double);
float fmaf(float, float, float);
long double fmal(long double, long double, long double);



double fmax(double, double);
float fmaxf(float, float);
long double fmaxl(long double, long double);



double fmin(double, double);
float fminf(float, float);
long double fminl(long double, long double);



double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);



double frexp(double, int *);
float frexpf(float, int *);
long double frexpl(long double, int *);



double hypot(double, double);
float hypotf(float, float);
long double hypotl(long double, long double);



int ilogb(double);
int ilogbf(float);
int ilogbl(long double);



double ldexp(double, int);
float ldexpf(float, int);
long double ldexpl(long double, int);




double lgamma(double);
float lgammaf(float);
long double lgammal(long double);




long long llrint(double);
long long llrintf(float);
long long llrintl(long double);



long long llround(double);
long long llroundf(float);
long long llroundl(long double);




double log(double);
float logf(float);
long double logl(long double);



double log10(double);
float log10f(float);
long double log10l(long double);



double log1p(double);
float log1pf(float);
long double log1pl(long double);



double log2(double);
float log2f(float);
long double log2l(long double);



double logb(double);
float logbf(float);
long double logbl(long double);



long lrint(double);
long lrintf(float);
long lrintl(long double);



long lround(double);
long lroundf(float);
long lroundl(long double);



double modf(double, double *);
float modff(float, float *);
long double modfl(long double, long double *);



double nan(const char *);
float nanf(const char *);
long double nanl(const char *);



double nearbyint(double);
float nearbyintf(float);
long double nearbyintl(long double);



double nextafter(double, double);
float nextafterf(float, float);
long double nextafterl(long double, long double);



double nexttoward(double, long double);
float nexttowardf(float, long double);
long double nexttowardl(long double, long double);
# 326 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 3
double pow(double, double);
__attribute__((nonreentrant)) float powf(float, float);
long double powl(long double, long double);



double remainder(double, double);
float remainderf(float, float);
long double remainderl(long double, long double);



double remquo(double, double, int *);
float remquof(float, float, int *);
long double remquol(long double, long double, int *);



double rint(double);
float rintf(float);
long double rintl(long double);



double round(double);
float roundf(float);
long double roundl(long double);



double scalbln(double, long);
float scalblnf(float, long);
long double scalblnl(long double, long);



double scalbn(double, int);
float scalbnf(float, int);
long double scalbnl(long double, int);



double sin(double);
float sinf(float);
long double sinl(long double);



double sinh(double);
float sinhf(float);
long double sinhl(long double);



double sqrt(double);
float sqrtf(float);
long double sqrtl(long double);



double tan(double);
float tanf(float);
long double tanl(long double);



double tanh(double);
float tanhf(float);
long double tanhl(long double);



double tgamma(double);
float tgammaf(float);
long double tgammal(long double);



double trunc(double);
float truncf(float);
long double truncl(long double);
# 431 "C:\\Program Files\\Microchip\\xc8\\v2.45\\pic\\include\\c99\\math.h" 3
extern int signgam;

double j0(double);
double j1(double);
double jn(int, double);

double y0(double);
double y1(double);
double yn(int, double);
# 53 "./PIC16F1719_Internal.h" 2
# 63 "./PIC16F1719_Internal.h"
void internal_32();
void internal_16();
void internal_8();
void internal_4();
void internal_2();
void internal_1();
void internal_31();
# 28 "main.c" 2
# 41 "main.c"
void initMain(){

    internal_32();


    TRISDbits.TRISD1 = 0;
}
# 57 "main.c"
void main(void) {
    initMain();

    while(1){

        LATDbits.LATD1 = !LATDbits.LATD1;

        _delay((unsigned long)((500)*(32000000/4000.0)));
    }

    return;

}

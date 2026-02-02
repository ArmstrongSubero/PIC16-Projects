#ifndef DHT11_H
#define DHT11_H

#include "PIC16F1718_Internal.h"

// DHT11 Data pin on RB3 (change if you want)
#define Dat_Output     LATBbits.LATB3
#define Dat_Input      PORTBbits.RB3
#define Dat_Direction  TRISBbits.TRISB3

void DHT11_Init(void);
void DHT11_Check(void);
char DHT11_Read(void);

#endif

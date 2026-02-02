/*******************************************************************************
 * ADC Channel Definitions
 ******************************************************************************/
typedef enum {
    ADC_AN0 = 0,    // RA0
    ADC_AN1 = 1,    // RA1
    ADC_AN2 = 2,    // RA2
    ADC_AN3 = 3,    // RA3
    ADC_AN4 = 4,    // RA4
    ADC_AN5 = 5,    // RA5
    ADC_AN8 = 8,    // RB0
    ADC_AN9 = 9,    // RB1
    ADC_AN10 = 10,  // RB3
    ADC_AN11 = 11,  // RB4
    ADC_AN12 = 12   // RB5
} adc_channel_t;

/*******************************************************************************
 * Function: uint16_t ADC_Read(adc_channel_t channel)
 *
 * Description: Read ADC value from specified channel
 * Returns: 10-bit ADC result (0-1023)
 * Usage: result = ADC_Read(ADC_AN0);
 ******************************************************************************/
uint16_t ADC_Read(adc_channel_t channel)
{
    // Select ADC channel
    ADCON0bits.CHS = (uint8_t)channel;
    
    // Turn ADC on
    ADCON0bits.ADON = 1;
    
    // CRITICAL: Longer acquisition time after channel switch
    // Datasheet recommends ~5us minimum, use 20us to be safe
    __delay_us(20);  // Changed from 10us
    
    // Start conversion
    ADCON0bits.GO = 1;
    
    // Wait for conversion to complete
    while (ADCON0bits.GO_nDONE);
    
    // Return 10-bit result
    return (uint16_t)((ADRESH << 8) + ADRESL);
}

/*******************************************************************************
 * Function: void ADC_ConfigurePin(adc_channel_t channel)
 *
 * Description: Configure a pin for ADC use
 * Usage: ADC_ConfigurePin(ADC_AN1);
 ******************************************************************************/
void ADC_ConfigurePin(adc_channel_t channel)
{
    switch(channel) {
        case ADC_AN0:  TRISAbits.TRISA0 = 1; ANSELAbits.ANSA0 = 1; break;
        case ADC_AN1:  TRISAbits.TRISA1 = 1; ANSELAbits.ANSA1 = 1; break;
        case ADC_AN2:  TRISAbits.TRISA2 = 1; ANSELAbits.ANSA2 = 1; break;
        case ADC_AN3:  TRISAbits.TRISA3 = 1; ANSELAbits.ANSA3 = 1; break;
        case ADC_AN4:  TRISAbits.TRISA4 = 1; ANSELAbits.ANSA4 = 1; break;
        case ADC_AN5:  TRISAbits.TRISA5 = 1; ANSELAbits.ANSA5 = 1; break;
        case ADC_AN8:  TRISBbits.TRISB0 = 1; ANSELBbits.ANSB0 = 1; break;
        case ADC_AN9:  TRISBbits.TRISB1 = 1; ANSELBbits.ANSB1 = 1; break;
        case ADC_AN10: TRISBbits.TRISB3 = 1; ANSELBbits.ANSB3 = 1; break;
        case ADC_AN11: TRISBbits.TRISB4 = 1; ANSELBbits.ANSB4 = 1; break;
        case ADC_AN12: TRISBbits.TRISB5 = 1; ANSELBbits.ANSB5 = 1; break;
    }
}

/*******************************************************************************
 * Function: void ADC_Init(void)
 *
 * Description: Initialize ADC module (call once)
 * Usage: ADC_Init();
 ******************************************************************************/
void ADC_Init(void)
{
    // Fosc/32 ADC conversion time is 1.0 us at 32MHz
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
}


/*******************************************************************************
 * Function: uint16_t ADC_Read_Averaged(adc_channel_t channel, uint8_t samples)
 *
 * Description: Read ADC with averaging to reduce noise
 * Returns: Averaged 10-bit ADC result
 * Usage: result = ADC_Read_Averaged(ADC_AN0, 4);
 ******************************************************************************/
uint16_t ADC_Read_Averaged(adc_channel_t channel, uint8_t samples)
{
    uint32_t sum = 0;
    
    // Select channel and let it settle once
    ADCON0bits.CHS = (uint8_t)channel;
    ADCON0bits.ADON = 1;
    __delay_us(20);
    
    // Take multiple samples
    for (uint8_t i = 0; i < samples; i++)
    {
        // Start conversion
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE);
        
        sum += (uint16_t)((ADRESH << 8) + ADRESL);
        
        // Small delay between samples
        if (i < samples - 1) __delay_us(5);
    }
    
    return (uint16_t)(sum / samples);
}
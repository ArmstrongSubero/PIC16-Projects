/**
  TMR6 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr6.h

  @Summary
    This is the generated header file for the TMR6 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for TMR6.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F1719
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef TMR6_H
#define TMR6_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
  Section: Macro Declarations
*/

/**
  Section: TMR6 APIs
*/

/**
  @Summary
    Initializes the TMR6 module.

  @Description
    This function initializes the TMR6 Registers.
    This function must be called before any other TMR6 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize TMR6 module
        TMR6_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR6_Initialize(void);

/**
  @Summary
    This function starts the TMR6.

  @Description
    This function starts the TMR6 operation.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Do something else...
    </code>
*/
void TMR6_StartTimer(void);

/**
  @Summary
    This function stops the TMR6.

  @Description
    This function stops the TMR6 operation.
    This function must be called after the start of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Do something else...

    // Stop TMR6;
    TMR6_StopTimer();
    </code>
*/
void TMR6_StopTimer(void);

/**
  @Summary
    Reads the TMR6 register.

  @Description
    This function reads the TMR6 register value and return it.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR6 register.

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Read the current value of TMR6
    if(0 == TMR6_ReadTimer())
    {
        // Do something else...

        // Reload the TMR value
        TMR6_Reload();
    }
    </code>
*/
uint8_t TMR6_ReadTimer(void);

/**
  @Summary
    Writes the TMR6 register.

  @Description
    This function writes the TMR6 register.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    timerVal - Value to write into TMR6 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR6 register
        if(ZERO == TMR6_ReadTimer())
        {
            // Do something else...

            // Write the TMR6 register
            TMR6_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR6_WriteTimer(uint8_t timerVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to PR6 register.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    periodVal - Value to load into TMR6 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD1 0x80
    #define PERIOD2 0x40
    #define ZERO    0x00

    while(1)
    {
        // Read the TMR6 register
        if(ZERO == TMR6_ReadTimer())
        {
            // Do something else...

            if(flag)
            {
                flag = 0;

                // Load Period 1 value
                TMR6_LoadPeriodRegister(PERIOD1);
            }
            else
            {
                 flag = 1;

                // Load Period 2 value
                TMR6_LoadPeriodRegister(PERIOD2);
            }
        }

        // Do something else...
    }
    </code>
*/
void TMR6_LoadPeriodRegister(uint8_t periodVal);

/**
  @Summary
    Boolean routine to poll or to check for the match flag on the fly.

  @Description
    This function is called to check for the timer match flag.
    This function is used in timer polling method.

  @Preconditions
    Initialize  the TMR6 module before calling this routine.

  @Param
    None

  @Returns
    true - timer match has occurred.
    false - timer match has not occurred.

  @Example
    <code>
    while(1)
    {
        // check the match flag
        if(TMR6_HasOverflowOccured())
        {
            // Do something else...

            // Reload the TMR6 value
            TMR6_Reload();
        }
    }
    </code>
*/
bool TMR6_HasOverflowOccured(void);

 #ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // TMR6_H
/**
 End of File
*/


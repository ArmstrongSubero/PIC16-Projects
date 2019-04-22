/**
   NCO1 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    nco1.h

   @Summary
     This is the generated header file for the NCO1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This header file provides APIs for driver for NCO1.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
         Device            :  PIC16F1719
         Driver Version    :  2.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.00 or later
         MPLAB             :  MPLAB X 5.10
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

#ifndef NCO1_H
 #define NCO1_H
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: NCO1 Module APIs
*/

/**
  @Summary
    Initializes the NCO1_Initialize

  @Description
    This routine initializes the NCO1_Initialize
    This routine must be called before any other NCO1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment

 @Example
    <code>
    NCO1_Initialize();
    </code>
 */
void NCO1_Initialize(void);

/**
  @Summary
    Determines if output status is high or low.

  @Description
    This routine returns the NCO1 output status.
    high - Indicates output is high
    low - Indicates output is low

  @Preconditions
    NCO1_Initialize() function should have been called
	before calling this function.

  @Param
    None

  @Returns
    high - Indicates output is high
    low - Indicates output is low

  @Example
    <code>
    NCO1_Initialize();
    if(NCO1_GetOutputStatus())
    {
        // User code..
    }
    else
    {
         // User code..
    }
    </code>
 */
bool NCO1_GetOutputStatus(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //NCO1_H
/**
 End of File
*/



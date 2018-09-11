/**
  MSSP Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    spi.c

  @Summary
    This is the generated driver implementation file for the MSSP driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for MSSP.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC16F1717
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "SPI.h"

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

/**
  Section: Macro Declarations
*/

#define DUMMY_DATA 0x0

/**
  Section: SPI Module APIs
*/

/**
  @Summary
    Initializes the SPI

  @Description
    This routine initializes the SPI.
    This routine must be called before any other MSSP routine is called.
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
    uint8_t     myWriteBuffer[MY_BUFFER_SIZE];
    uint8_t     myReadBuffer[MY_BUFFER_SIZE];
    uint8_t     writeData;
    uint8_t     readData;
    uint8_t     total;

    SPI_Initialize();

    total = 0;
    do
    {
        total = SPI_Exchange8bitBuffer(&myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

        // Do something else...

    } while(total < MY_BUFFER_SIZE);

    readData = SPI_Exchange8bit(writeData);
    </code>
 */

void SPI_Initialize(void)
{
   // Set the SPI module to the options selected in the User Interface

    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Active to Idle; D_nA lastbyte_address; 
    SSP1STAT = 0x40;

    // SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:Low, Active:High; SSPM FOSC/64; 
    SSP1CON1 = 0x22;

    // SSP1ADD 0; 
    SSP1ADD = 0x00;
}

/**
  @Summary
    Exchanges a data byte over SPI

  @Description
    This routine exchanges a data byte over SPI bus.
    This is a blocking routine.

  @Preconditions
    The SPI_Initialize() routine should be called
    prior to use this routine.

  @Param
    data - data byte to be transmitted over SPI bus

  @Returns
    The received byte over SPI bus

  @Example
    <code>
    uint8_t     writeData;
    uint8_t     readData;
    uint8_t     readDummy;

    SPI_Initialize();

    // for transmission over SPI bus
    readDummy = SPI_Exchange8bit(writeData);

    // for reception over SPI bus
    readData = SPI_Exchange8bit(DUMMY_DATA);
    </code>
 */

uint8_t SPI_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSPBUF = data;

    while(SSP1STATbits.BF == SPI_RX_IN_PROGRESS)
    {
    }

    return (SSPBUF);
}

/**
  @Summary
    Exchanges buffer of data over SPI

  @Description
    This routine exchanges buffer of data (of size one byte) over SPI bus.
    This is a blocking routine.

  @Preconditions
    The SPI_Initialize() routine should be called
    prior to use this routine.

  @Param
    dataIn  - Buffer of data to be transmitted over SPI.
    bufLen  - Number of bytes to be exchanged.
    dataOut - Buffer of data to be received over SPI.

  @Returns
    Number of bytes exchanged over SPI.

  @Example
    <code>
    uint8_t     myWriteBuffer[MY_BUFFER_SIZE];
    uint8_t     myReadBuffer[MY_BUFFER_SIZE];
    uint8_t     total;

    SPI_Initialize();

    total = 0;
    do
    {
        total = SPI_Exchange8bitBuffer(&myWriteBuffer[total], MY_BUFFER_SIZE - total, &myWriteBuffer[total]);

        // Do something else...

    } while(total < MY_BUFFER_SIZE);
    </code>
 */

uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    SPI_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(DUMMY_DATA);

                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}


bool SPI_IsBufferFull(void)
{
    return (SSP1STATbits.BF);
}

/**
  @Summary
    Clears the status of write collision.

  @Description
    This routine clears the status of write collision.

  @Preconditions
    The SPI_Initialize() routine must have been called prior to use this routine.

  @Param
    None

  @Returns
    None

  @Example
    if(SPI_HasWriteCollisionOccured())
    {
        SPI_ClearWriteCollisionStatus();
    }
*/

bool SPI_HasWriteCollisionOccured(void)
{
    return (SSP1CON1bits.WCOL);
}

void SPI_ClearWriteCollisionStatus(void)
{
    SSP1CON1bits.WCOL = 0;
}
/**
 End of File
*/
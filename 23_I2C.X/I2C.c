#include "I2C.h"


void interrupt INTERRUPT_InterruptManager (void)
{
   // interrupt handler
    if(PIE2bits.BCL1IE == 1 && PIR2bits.BCL1IF == 1)
    {
        I2C_BusCollisionISR();
    }
    else if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
    {
        I2C_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

/**
  I2C Driver Queue Status Type

  @Summary
    Defines the type used for the transaction queue status.

  @Description
    This defines type used to keep track of the queue status.
 */

typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}I2C_TR_QUEUE_STATUS;

/**
  I2C Driver Queue Entry Type

  @Summary
    Defines the object used for an entry in the i2c queue items.

  @Description
    This defines the object in the i2c queue. Each entry is a composed
    of a list of TRBs, the number of the TRBs and the status of the
    currently processed TRB.
 */
typedef struct
{
    uint8_t                             count;          // a count of trb's in the trb list
    I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list;     // pointer to the trb list
    I2C_MESSAGE_STATUS            *pTrFlag;       // set with the error of the last trb sent.
                                                        // if all trb's are sent successfully,
                                                        // then this is I2C_MESSAGE_COMPLETE
} I2C_TR_QUEUE_ENTRY;

/**
  I2C Master Driver Object Type

  @Summary
    Defines the object that manages the i2c master.

  @Description
    This defines the object that manages the sending and receiving of
    i2c master transactions.
  */

typedef struct
{
    /* Read/Write Queue */
    I2C_TR_QUEUE_ENTRY          *pTrTail;       // tail of the queue
    I2C_TR_QUEUE_ENTRY          *pTrHead;       // head of the queue
    I2C_TR_QUEUE_STATUS         trStatus;       // status of the last transaction
    uint8_t                         i2cDoneFlag;    // flag to indicate the current
                                                    // transaction is done
    uint8_t                         i2cErrors;      // keeps track of errors


} I2C_OBJECT ;

/**
  I2C Master Driver State Enumeration

  @Summary
    Defines the different states of the i2c master.

  @Description
    This defines the different states that the i2c master
    used to process transactions on the i2c bus.
*/

typedef enum
{
    S_MASTER_IDLE,
    S_MASTER_RESTART,
    S_MASTER_SEND_ADDR,
    S_MASTER_SEND_DATA,
    S_MASTER_SEND_STOP,
    S_MASTER_ACK_ADDR,
    S_MASTER_RCV_DATA,
    S_MASTER_RCV_STOP,
    S_MASTER_ACK_RCV_DATA,
    S_MASTER_NOACK_STOP,
    S_MASTER_SEND_ADDR_10BIT_LSB,
    S_MASTER_10BIT_RESTART,
    
} I2C_MASTER_STATES;

/**
 Section: Macro Definitions
*/

/* defined for I2C */

#ifndef I2C_CONFIG_TR_QUEUE_LENGTH
        #define I2C_CONFIG_TR_QUEUE_LENGTH 1
#endif

#define I2C_TRANSMIT_REG                       SSP1BUF                 // Defines the transmit register used to send data.
#define I2C_RECEIVE_REG                        SSP1BUF                 // Defines the receive register used to receive data.

// The following control bits are used in the I2C state machine to manage
// the I2C module and determine next states.
#define I2C_WRITE_COLLISION_STATUS_BIT         SSP1CON1bits.WCOL     // Defines the write collision status bit.
#define I2C_MODE_SELECT_BITS                   SSP1CON1bits.SSPM     // I2C Master Mode control bit.
#define I2C_MASTER_ENABLE_CONTROL_BITS         SSP1CON1bits.SSPEN    // I2C port enable control bit.

#define I2C_START_CONDITION_ENABLE_BIT         SSP1CON2bits.SEN      // I2C START control bit.
#define I2C_REPEAT_START_CONDITION_ENABLE_BIT  SSP1CON2bits.RSEN     // I2C Repeated START control bit.
#define I2C_RECEIVE_ENABLE_BIT                 SSP1CON2bits.RCEN     // I2C Receive enable control bit.
#define I2C_STOP_CONDITION_ENABLE_BIT          SSP1CON2bits.PEN      // I2C STOP control bit.
#define I2C_ACKNOWLEDGE_ENABLE_BIT             SSP1CON2bits.ACKEN    // I2C ACK start control bit.
#define I2C_ACKNOWLEDGE_DATA_BIT               SSP1CON2bits.ACKDT    // I2C ACK data control bit.
#define I2C_ACKNOWLEDGE_STATUS_BIT             SSP1CON2bits.ACKSTAT  // I2C ACK status bit.

#define I2C_7bit    true
/**
 Section: Local Functions
*/

void I2C_FunctionComplete(void);
void I2C_Stop(I2C_MESSAGE_STATUS completion_code);

/**
 Section: Local Variables
*/

static I2C_TR_QUEUE_ENTRY                  i2c_tr_queue[I2C_CONFIG_TR_QUEUE_LENGTH];
static I2C_OBJECT                          i2c_object;
static I2C_MASTER_STATES                   i2c_state = S_MASTER_IDLE;
static uint8_t                                 i2c_trb_count = 0;

static I2C_TRANSACTION_REQUEST_BLOCK       *p_i2c_trb_current = NULL;
static I2C_TR_QUEUE_ENTRY                  *p_i2c_current = NULL;


/**
  Section: Driver Interface
*/


void I2C_Initialize(void)
{
    i2c_object.pTrHead = i2c_tr_queue;
    i2c_object.pTrTail = i2c_tr_queue;
    i2c_object.trStatus.s.empty = true;
    i2c_object.trStatus.s.full = false;

    i2c_object.i2cErrors = 0;

    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD_I2C; SSPOV no_overflow; 
    SSP1CON1 = 0x28;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // Baud Rate Generator Value: SSP1ADD 18;   
    SSP1ADD = 0x12;

   
    // clear the master interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;
    
}

        
uint8_t I2C_ErrorCountGet(void)
{
    uint8_t ret;

    ret = i2c_object.i2cErrors;
    return ret;
}

void I2C_ISR ( void )
{
  
    static uint8_t  *pi2c_buf_ptr;
    static uint16_t i2c_address         = 0;
    static uint8_t  i2c_bytes_left      = 0;
    static uint8_t  i2c_10bit_address_restart = 0;

    PIR1bits.SSP1IF = 0;

    // Check first if there was a collision.
    // If we have a Write Collision, reset and go to idle state */
    if(I2C_WRITE_COLLISION_STATUS_BIT)
    {
        // clear the Write colision
        I2C_WRITE_COLLISION_STATUS_BIT = 0;
        i2c_state = S_MASTER_IDLE;
        *(p_i2c_current->pTrFlag) = I2C_MESSAGE_FAIL;

        // reset the buffer pointer
        p_i2c_current = NULL;

        return;
    }

    /* Handle the correct i2c state */
    switch(i2c_state)
    {
        case S_MASTER_IDLE:    /* In reset state, waiting for data to send */

            if(i2c_object.trStatus.s.empty != true)
            {
                // grab the item pointed by the head
                p_i2c_current     = i2c_object.pTrHead;
                i2c_trb_count     = i2c_object.pTrHead->count;
                p_i2c_trb_current = i2c_object.pTrHead->ptrb_list;

                i2c_object.pTrHead++;

                // check if the end of the array is reached
                if(i2c_object.pTrHead == (i2c_tr_queue + I2C_CONFIG_TR_QUEUE_LENGTH))
                {
                    // adjust to restart at the beginning of the array
                    i2c_object.pTrHead = i2c_tr_queue;
                }

                // since we moved one item to be processed, we know
                // it is not full, so set the full status to false
                i2c_object.trStatus.s.full = false;

                // check if the queue is empty
                if(i2c_object.pTrHead == i2c_object.pTrTail)
                {
                    // it is empty so set the empty status to true
                    i2c_object.trStatus.s.empty = true;
                }

                // send the start condition
                I2C_START_CONDITION_ENABLE_BIT = 1;
                
                // start the i2c request
                i2c_state = S_MASTER_SEND_ADDR;
            }

            break;

        case S_MASTER_RESTART:

            /* check for pending i2c Request */

            // ... trigger a REPEATED START
            I2C_REPEAT_START_CONDITION_ENABLE_BIT = 1;

            // start the i2c request
            i2c_state = S_MASTER_SEND_ADDR;

            break;

        case S_MASTER_SEND_ADDR_10BIT_LSB:

            if(I2C_ACKNOWLEDGE_STATUS_BIT)
            {
                i2c_object.i2cErrors++;
                I2C_Stop(I2C_MESSAGE_ADDRESS_NO_ACK);
            }
            else
            {
                // Remove bit 0 as R/W is never sent here
                I2C_TRANSMIT_REG = (i2c_address >> 1) & 0x00FF;

                // determine the next state, check R/W
                if(i2c_address & 0x01)
                {
                    // if this is a read we must repeat start
                    // the bus to perform a read
                    i2c_state = S_MASTER_10BIT_RESTART;
                }
                else
                {
                    // this is a write continue writing data
                    i2c_state = S_MASTER_SEND_DATA;
                }
            }

            break;

        case S_MASTER_10BIT_RESTART:

            if(I2C_ACKNOWLEDGE_STATUS_BIT)
            {
                i2c_object.i2cErrors++;
                I2C_Stop(I2C_MESSAGE_ADDRESS_NO_ACK);
            }
            else
            {
                // ACK Status is good
                // restart the bus
                I2C_REPEAT_START_CONDITION_ENABLE_BIT = 1;

                // fudge the address so S_MASTER_SEND_ADDR works correctly
                // we only do this on a 10-bit address resend
                i2c_address = 0x00F0 | ((i2c_address >> 8) & 0x0006);

                // set the R/W flag
                i2c_address |= 0x0001;

                // set the address restart flag so we do not change the address
                i2c_10bit_address_restart = 1;

                // Resend the address as a read
                i2c_state = S_MASTER_SEND_ADDR;
            }

            break;

        case S_MASTER_SEND_ADDR:

            /* Start has been sent, send the address byte */

            /* Note: 
                On a 10-bit address resend (done only during a 10-bit
                device read), the original i2c_address was modified in
                S_MASTER_10BIT_RESTART state. So the check if this is
                a 10-bit address will fail and a normal 7-bit address
                is sent with the R/W bit set to read. The flag
                i2c_10bit_address_restart prevents the  address to
                be re-written.
             */
            if(i2c_10bit_address_restart != 1)
            {
                // extract the information for this message
                i2c_address    = p_i2c_trb_current->address;
                pi2c_buf_ptr   = p_i2c_trb_current->pbuffer;
                i2c_bytes_left = p_i2c_trb_current->length;
            }

            // check for 10-bit address
            if(!I2C_7bit && (0x0 != i2c_address))
            {  
                if (0 == i2c_10bit_address_restart)
                {
                    // we have a 10 bit address
                    // send bits<9:8>
                    // mask bit 0 as this is always a write                    
                    I2C_TRANSMIT_REG = 0xF0 | ((i2c_address >> 8) & 0x0006);
                    i2c_state = S_MASTER_SEND_ADDR_10BIT_LSB;
                }
                else
                {
                    // resending address bits<9:8> to trigger read
                    I2C_TRANSMIT_REG = i2c_address;
                    i2c_state = S_MASTER_ACK_ADDR;
                    // reset the flag so the next access is ok
                    i2c_10bit_address_restart = 0;
                }
            }
            else
            {
                // Transmit the address
                I2C_TRANSMIT_REG = i2c_address;
                if(i2c_address & 0x01)
                {
                    // Next state is to wait for address to be acked
                    i2c_state = S_MASTER_ACK_ADDR;
                }
                else
                {
                    // Next state is transmit
                    i2c_state = S_MASTER_SEND_DATA;
                }
            }
            break;

        case S_MASTER_SEND_DATA:

            // Make sure the previous byte was acknowledged
            if(I2C_ACKNOWLEDGE_STATUS_BIT)
            {
                // Transmission was not acknowledged
                i2c_object.i2cErrors++;

                // Reset the Ack flag
                I2C_ACKNOWLEDGE_STATUS_BIT = 0;

                // Send a stop flag and go back to idle
                I2C_Stop(I2C_DATA_NO_ACK);

            }
            else
            {
                // Did we send them all ?
                if(i2c_bytes_left-- == 0U)
                {
                    // yup sent them all!

                    // update the trb pointer
                    p_i2c_trb_current++;

                    // are we done with this string of requests?
                    if(--i2c_trb_count == 0)
                    {
                        I2C_Stop(I2C_MESSAGE_COMPLETE);
                    }
                    else
                    {
                        // no!, there are more TRB to be sent.
                        //I2C_START_CONDITION_ENABLE_BIT = 1;

                        // In some cases, the slave may require
                        // a restart instead of a start. So use this one
                        // instead.
                        I2C_REPEAT_START_CONDITION_ENABLE_BIT = 1;

                        // start the i2c request
                        i2c_state = S_MASTER_SEND_ADDR;

                    }
                }
                else
                {
                    // Grab the next data to transmit
                    I2C_TRANSMIT_REG = *pi2c_buf_ptr++;
                }
            }
            break;

        case S_MASTER_ACK_ADDR:

            /* Make sure the previous byte was acknowledged */
            if(I2C_ACKNOWLEDGE_STATUS_BIT)
            {

                // Transmission was not acknowledged
                i2c_object.i2cErrors++;

                // Send a stop flag and go back to idle
                I2C_Stop(I2C_MESSAGE_ADDRESS_NO_ACK);

                // Reset the Ack flag
                I2C_ACKNOWLEDGE_STATUS_BIT = 0;
            }
            else
            {
                I2C_RECEIVE_ENABLE_BIT = 1;
                i2c_state = S_MASTER_ACK_RCV_DATA;
            }
            break;

        case S_MASTER_RCV_DATA:

            /* Acknowledge is completed.  Time for more data */

            // Next thing is to ack the data
            i2c_state = S_MASTER_ACK_RCV_DATA;

            // Set up to receive a byte of data
            I2C_RECEIVE_ENABLE_BIT = 1;

            break;

        case S_MASTER_ACK_RCV_DATA:

            // Grab the byte of data received and acknowledge it
            *pi2c_buf_ptr++ = I2C_RECEIVE_REG;

            // Check if we received them all?
            if(--i2c_bytes_left)
            {

                /* No, there's more to receive */

                // No, bit 7 is clear.  Data is ok
                // Set the flag to acknowledge the data
                I2C_ACKNOWLEDGE_DATA_BIT = 0;

                // Wait for the acknowledge to complete, then get more
                i2c_state = S_MASTER_RCV_DATA;
            }
            else
            {

                // Yes, it's the last byte.  Don't ack it
                // Flag that we will nak the data
                I2C_ACKNOWLEDGE_DATA_BIT = 1;

                I2C_FunctionComplete();
            }

            // Initiate the acknowledge
            I2C_ACKNOWLEDGE_ENABLE_BIT = 1;
            break;

        case S_MASTER_RCV_STOP:                
        case S_MASTER_SEND_STOP:

            // Send the stop flag
            I2C_Stop(I2C_MESSAGE_COMPLETE);
            break;

        default:

            // This case should not happen, if it does then
            // terminate the transfer
            i2c_object.i2cErrors++;
            I2C_Stop(I2C_LOST_STATE);
            break;

    }
}

void I2C_FunctionComplete(void)
{

    // update the trb pointer
    p_i2c_trb_current++;

    // are we done with this string of requests?
    if(--i2c_trb_count == 0)
    {
        i2c_state = S_MASTER_SEND_STOP;
    }
    else
    {
        i2c_state = S_MASTER_RESTART;
    }

}

void I2C_Stop(I2C_MESSAGE_STATUS completion_code)
{
    // then send a stop
    I2C_STOP_CONDITION_ENABLE_BIT = 1;

    // make sure the flag pointer is not NULL
    if (p_i2c_current->pTrFlag != NULL)
    {
        // update the flag with the completion code
        *(p_i2c_current->pTrFlag) = completion_code;
    }

    // Done, back to idle
    i2c_state = S_MASTER_IDLE;
    
}

void I2C_MasterWrite(
                                uint8_t *pdata,
                                uint8_t length,
                                uint16_t address,
                                I2C_MESSAGE_STATUS *pflag)
{
    static I2C_TRANSACTION_REQUEST_BLOCK   trBlock;

    // check if there is space in the queue
    if (i2c_object.trStatus.s.full != true)
    {
        I2C_MasterWriteTRBBuild(&trBlock, pdata, length, address);
        I2C_MasterTRBInsert(1, &trBlock, pflag);
    }
    else
    {
        *pflag = I2C_MESSAGE_FAIL;
    }

}

void I2C_MasterRead(
                                uint8_t *pdata,
                                uint8_t length,
                                uint16_t address,
                                I2C_MESSAGE_STATUS *pflag)
{
    static I2C_TRANSACTION_REQUEST_BLOCK   trBlock;


    // check if there is space in the queue
    if (i2c_object.trStatus.s.full != true)
    {
        I2C_MasterReadTRBBuild(&trBlock, pdata, length, address);
        I2C_MasterTRBInsert(1, &trBlock, pflag);
    }
    else
    {
        *pflag = I2C_MESSAGE_FAIL;
    }

}

void I2C_MasterTRBInsert(
                                uint8_t count,
                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list,
                                I2C_MESSAGE_STATUS *pflag)
{

    // check if there is space in the queue
    if (i2c_object.trStatus.s.full != true)
    {
        *pflag = I2C_MESSAGE_PENDING;

        i2c_object.pTrTail->ptrb_list = ptrb_list;
        i2c_object.pTrTail->count     = count;
        i2c_object.pTrTail->pTrFlag   = pflag;
        i2c_object.pTrTail++;

        // check if the end of the array is reached
        if (i2c_object.pTrTail == (i2c_tr_queue + I2C_CONFIG_TR_QUEUE_LENGTH))
        {
            // adjust to restart at the beginning of the array
            i2c_object.pTrTail = i2c_tr_queue;
        }

        // since we added one item to be processed, we know
        // it is not empty, so set the empty status to false
        i2c_object.trStatus.s.empty = false;

        // check if full
        if (i2c_object.pTrHead == i2c_object.pTrTail)
        {
            // it is full, set the full status to true
            i2c_object.trStatus.s.full = true;
        }

    }
    else
    {
        *pflag = I2C_MESSAGE_FAIL;
    }

    // for interrupt based
    if (*pflag == I2C_MESSAGE_PENDING)
    {
        while(i2c_state != S_MASTER_IDLE);
        {
            // force the task to run since we know that the queue has
            // something that needs to be sent
            PIR1bits.SSP1IF = true;
        }
    }   // block until request is complete

}

void I2C_MasterReadTRBBuild(
                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb,
                                uint8_t *pdata,
                                uint8_t length,
                                uint16_t address)
{
    ptrb->address  = address << 1;
    // make this a read
    ptrb->address |= 0x01;
    ptrb->length   = length;
    ptrb->pbuffer  = pdata;
}

void I2C_MasterWriteTRBBuild(
                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb,
                                uint8_t *pdata,
                                uint8_t length,
                                uint16_t address)
{
    ptrb->address = address << 1;
    ptrb->length  = length;
    ptrb->pbuffer = pdata;
}

bool I2C_MasterQueueIsEmpty(void)
{
    return(i2c_object.trStatus.s.empty);
}

bool I2C_MasterQueueIsFull(void)
{
    return(i2c_object.trStatus.s.full);
}        
        
void I2C_BusCollisionISR( void )
{
    // enter bus collision handling code here
}        
        

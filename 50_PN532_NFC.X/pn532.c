/*
 * File: pn532.c
 * PN532 NFC Driver for PIC16F1718/1719 using I2C
 * With NTAG/Ultralight read/write and NDEF text extraction
 */

#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "EUSART.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pn532.h"

/* ---------------- PN532 I2C Constants ---------------- */

#define PN532_I2C_ADDR7              0x24

#define PN532_I2C_BUSY               0x00
#define PN532_I2C_READY              0x01

#define PN532_PREAMBLE               0x00
#define PN532_STARTCODE1             0x00
#define PN532_STARTCODE2             0xFF
#define PN532_POSTAMBLE              0x00

#define PN532_HOSTTOPN532            0xD4
#define PN532_PN532TOHOST            0xD5

#define PN532_COMMAND_GETFIRMWAREVERSION  0x02
#define PN532_COMMAND_SAMCONFIGURATION    0x14
#define PN532_COMMAND_INLISTPASSIVETARGET 0x4A
#define PN532_COMMAND_INDATAEXCHANGE      0x40

#define PN532_MIFARE_ISO14443A       0x00

#define PN532_FRAME_MAX_LENGTH       255
#define PN532_DEFAULT_TIMEOUT        1000

/* MIFARE/NTAG Commands */
#define MIFARE_CMD_READ              0x30
#define MIFARE_CMD_WRITE             0xA0
#define MIFARE_ULTRALIGHT_CMD_WRITE  0xA2
#define NTAG_CMD_FAST_READ           0x3A  // Read multiple pages at once

/* MIFARE Classic Commands */
#define MIFARE_CMD_AUTH_A            0x60  // Authenticate with Key A
#define MIFARE_CMD_AUTH_B            0x61  // Authenticate with Key B

/* Block sizes */
#define MIFARE_BLOCK_LENGTH          16
#define NTAG2XX_BLOCK_LENGTH         4
#define MIFARE_KEY_LENGTH            6

/* Default MIFARE Classic keys */
static const uint8_t MIFARE_DEFAULT_KEY[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/* Common MIFARE keys to try - ORDER MATTERS! */
static const uint8_t MIFARE_COMMON_KEYS[][6] = {
    {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},  // MAD key (Sector 0) - TRY FIRST!
    {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7},  // NDEF key (Sectors 1-5)
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Factory default (Sectors 6-15)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // All zeros
    {0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5},  // Common alternate
};
#define NUM_COMMON_KEYS 5

/* Error codes */
#define PN532_ERROR_NONE             0x00

static const uint8_t PN532_ACK[] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};

static uint8_t pn532_packetbuffer[PN532_FRAME_MAX_LENGTH + 16];

/* ---------------- NDEF Text Extraction Globals ---------------- */

#define NDEF_TEXT_MAX_LEN  128

static uint8_t g_last_dump[64];
static uint8_t g_last_dump_len = 0;

/* ---------------- Debug Helper ---------------- */

static void print_hex8(uint8_t v)
{
    const char hex[] = "0123456789ABCDEF";
    char s[3];
    s[0] = hex[(v >> 4) & 0x0F];
    s[1] = hex[v & 0x0F];
    s[2] = '\0';
    EUSART_Write_Text(s);
}

static void print_hex_array(uint8_t* data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        print_hex8(data[i]);
        if (i < length - 1) EUSART_Write_Text(" ");
    }
}

static void print_ascii_char(uint8_t c)
{
    if (c >= 32 && c <= 126) {
        char s[2] = {(char)c, '\0'};
        EUSART_Write_Text(s);
    } else {
        EUSART_Write_Text(".");
    }
}

/* ---------------- Bus Recovery ---------------- */

static void I2C_BusRecover_RC4_RC5(void)
{
    SSPCONbits.SSPEN = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;

    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
    LATCbits.LATC5 = 1;
    __delay_us(10);

    for (uint8_t i = 0; i < 9; i++) {
        LATCbits.LATC5 = 0; __delay_us(10);
        LATCbits.LATC5 = 1; __delay_us(10);
    }

    TRISCbits.TRISC4 = 0;
    LATCbits.LATC4 = 0; __delay_us(10);
    LATCbits.LATC5 = 1; __delay_us(10);
    LATCbits.LATC4 = 1; __delay_us(10);

    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    SSPCONbits.SSPEN = 1;
    SSPCON1bits.SSPOV = 0;
    SSPCON1bits.WCOL  = 0;
    PIR1bits.SSP1IF   = 0;
    PIR2bits.BCL1IF   = 0;
}

/* ---------------- Low-level I2C Helpers ---------------- */

static I2C_Status_t pn532_i2c_write_raw(const uint8_t *data, uint16_t len)
{
    I2C_Status_t st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte((uint8_t)((PN532_I2C_ADDR7 << 1) | 0u));
    if (st != I2C_OK) { (void)I2C_Stop(); return st; }

    for (uint16_t i = 0; i < len; i++) {
        st = I2C_WriteByte(data[i]);
        if (st != I2C_OK) { (void)I2C_Stop(); return st; }
    }

    (void)I2C_Stop();
    return I2C_OK;
}

static I2C_Status_t pn532_i2c_read_raw(uint8_t *out, uint16_t len)
{
    uint8_t status = 0;

    I2C_Status_t st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte((uint8_t)((PN532_I2C_ADDR7 << 1) | 1u));
    if (st != I2C_OK) { (void)I2C_Stop(); return st; }

    st = I2C_ReadByte(&status, true);
    if (st != I2C_OK) { (void)I2C_Stop(); return st; }

    if (status != PN532_I2C_READY) {
        (void)I2C_Stop();
        return I2C_NAK;
    }

    for (uint16_t i = 0; i < len; i++) {
        bool ack = (i != (len - 1));
        st = I2C_ReadByte(&out[i], ack);
        if (st != I2C_OK) { (void)I2C_Stop(); return st; }
    }

    (void)I2C_Stop();
    return I2C_OK;
}

static bool pn532_wait_ready(uint32_t timeout_ms)
{
    while (timeout_ms--)
    {
        uint8_t status = 0;

        I2C_Status_t st = I2C_Start();
        if (st != I2C_OK) { 
            I2C_BusRecover_RC4_RC5(); 
            __delay_ms(1); 
            continue; 
        }

        st = I2C_WriteByte((uint8_t)((PN532_I2C_ADDR7 << 1) | 1u));
        if (st != I2C_OK) { 
            (void)I2C_Stop(); 
            __delay_ms(1); 
            continue; 
        }

        st = I2C_ReadByte(&status, false);
        (void)I2C_Stop();

        if (st == I2C_OK && status == PN532_I2C_READY)
            return true;

        __delay_ms(1);
    }
    return false;
}

/* ---------------- PN532 Frame Functions ---------------- */
uint8_t frame[PN532_FRAME_MAX_LENGTH + 8];
static int PN532_WriteFrame(const uint8_t* data, uint16_t length)
{
    if (length > PN532_FRAME_MAX_LENGTH || length < 1) {
        return PN532_STATUS_ERROR;
    }

    
    uint16_t idx = 0;
    uint8_t checksum = 0;

    frame[idx++] = PN532_PREAMBLE;
    frame[idx++] = PN532_STARTCODE1;
    frame[idx++] = PN532_STARTCODE2;

    frame[idx++] = (uint8_t)(length & 0xFF);
    frame[idx++] = (uint8_t)((~length + 1) & 0xFF);

    for (uint16_t i = 0; i < length; i++) {
        frame[idx++] = data[i];
        checksum += data[i];
    }

    frame[idx++] = (uint8_t)((~checksum + 1) & 0xFF);
    frame[idx++] = PN532_POSTAMBLE;

    if (pn532_i2c_write_raw(frame, idx) != I2C_OK) {
        I2C_BusRecover_RC4_RC5();
        return PN532_STATUS_ERROR;
    }

    return PN532_STATUS_OK;
}

static int PN532_ReadFrame(uint8_t* response, uint16_t max_length)
{
    uint16_t read_len = (max_length + 10 > 64) ? 64 : (max_length + 10);
    
    if (pn532_i2c_read_raw(pn532_packetbuffer, read_len) != I2C_OK) {
        return PN532_STATUS_ERROR;
    }

    uint8_t offset = 0;
    while (offset < read_len && pn532_packetbuffer[offset] == 0x00) {
        offset++;
    }

    if (offset >= read_len || pn532_packetbuffer[offset] != 0xFF) {
        return PN532_STATUS_ERROR;
    }
    offset++;

    if (offset + 1 >= read_len) {
        return PN532_STATUS_ERROR;
    }

    uint8_t frame_len = pn532_packetbuffer[offset];
    uint8_t lcs = pn532_packetbuffer[offset + 1];

    if ((uint8_t)(frame_len + lcs) != 0x00) {
        return PN532_STATUS_ERROR;
    }

    if (offset + 2 + frame_len + 1 > read_len) {
        return PN532_STATUS_ERROR;
    }

    uint8_t checksum = 0;
    for (uint8_t i = 0; i < frame_len + 1; i++) {
        checksum += pn532_packetbuffer[offset + 2 + i];
    }
    if (checksum != 0x00) {
        return PN532_STATUS_ERROR;
    }

    uint8_t copy_len = (frame_len < max_length) ? frame_len : max_length;
    memcpy(response, &pn532_packetbuffer[offset + 2], copy_len);

    return frame_len;
}

static int PN532_ReadAck(void)
{
    uint8_t ack[6];

    if (pn532_i2c_read_raw(ack, sizeof(ack)) != I2C_OK) {
        return PN532_STATUS_ERROR;
    }

    for (uint8_t i = 0; i < 6; i++) {
        if (ack[i] != PN532_ACK[i]) {
            return PN532_STATUS_ERROR;
        }
    }
    return PN532_STATUS_OK;
}

/* ---------------- Core Call Function ---------------- */
uint8_t frame_data[PN532_FRAME_MAX_LENGTH];
static int PN532_CallFunction(uint8_t cmd, const uint8_t *params, uint8_t params_len,
                              uint8_t *resp, uint8_t resp_len, uint16_t timeout_ms)
{
    
    uint8_t frame_len = 0;

    frame_data[frame_len++] = PN532_HOSTTOPN532;
    frame_data[frame_len++] = cmd;

    for (uint8_t i = 0; i < params_len; i++) {
        frame_data[frame_len++] = params[i];
    }

    if (PN532_WriteFrame(frame_data, frame_len) != PN532_STATUS_OK) {
        return PN532_STATUS_ERROR;
    }

    if (!pn532_wait_ready(timeout_ms)) {
        return PN532_STATUS_ERROR;
    }

    if (PN532_ReadAck() != PN532_STATUS_OK) {
        return PN532_STATUS_ERROR;
    }

    if (!pn532_wait_ready(timeout_ms)) {
        return PN532_STATUS_ERROR;
    }

    uint8_t resp_buf[64];
    int frame_result = PN532_ReadFrame(resp_buf, sizeof(resp_buf));
    if (frame_result < 2) {
        return PN532_STATUS_ERROR;
    }

    if (resp_buf[0] != PN532_PN532TOHOST) {
        return PN532_STATUS_ERROR;
    }
    if (resp_buf[1] != (uint8_t)(cmd + 1)) {
        return PN532_STATUS_ERROR;
    }

    uint8_t data_len = (uint8_t)(frame_result - 2);
    uint8_t copy_len = (data_len < resp_len) ? data_len : resp_len;
    
    if (resp != NULL && copy_len > 0) {
        memcpy(resp, &resp_buf[2], copy_len);
    }

    return data_len;
}

/* ---------------- High-Level APIs ---------------- */

int PN532_Init_PIC(void)
{
    I2C_BusRecover_RC4_RC5();
    __delay_ms(10);
    return PN532_STATUS_OK;
}

int PN532_GetFirmwareVersion(uint8_t *version)
{
    if (!version) return PN532_STATUS_ERROR;

    int result = PN532_CallFunction(PN532_COMMAND_GETFIRMWAREVERSION,
                                    NULL, 0,
                                    version, 4,
                                    500);
    
    return (result >= 4) ? PN532_STATUS_OK : PN532_STATUS_ERROR;
}

int PN532_SamConfiguration(void)
{
    uint8_t params[3] = {0x01, 0x14, 0x01};
    
    int result = PN532_CallFunction(PN532_COMMAND_SAMCONFIGURATION,
                                    params, sizeof(params),
                                    NULL, 0,
                                    500);
    
    return (result >= 0) ? PN532_STATUS_OK : PN532_STATUS_ERROR;
}

int PN532_ReadPassiveTarget(uint8_t *uid, uint8_t card_baud, uint32_t timeout_ms)
{
    uint8_t params[2] = {0x01, card_baud};
    uint8_t resp[20];

    int result = PN532_CallFunction(PN532_COMMAND_INLISTPASSIVETARGET,
                                    params, sizeof(params),
                                    resp, sizeof(resp),
                                    (uint16_t)timeout_ms);

    if (result < 6) {
        return PN532_STATUS_ERROR;
    }

    if (resp[0] != 0x01) {
        return PN532_STATUS_ERROR;
    }

    uint8_t uid_len = resp[5];
    if (uid_len == 0 || uid_len > 10) {
        return PN532_STATUS_ERROR;
    }

    if (uid != NULL) {
        memcpy(uid, &resp[6], uid_len);
    }

    return uid_len;
}

/* ---------------- NTAG/Ultralight Block Read/Write ---------------- */

int PN532_Ntag2xxReadBlock(uint8_t* response, uint8_t block_number)
{
    // InDataExchange params: [Tg=0x01] [CMD=READ] [Block#]
    uint8_t params[3] = {0x01, MIFARE_CMD_READ, block_number};
    uint8_t buff[MIFARE_BLOCK_LENGTH + 1];  // Status + 16 bytes (but NTAG returns 4)

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, sizeof(params),
                                    buff, sizeof(buff),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 1) {
        return PN532_STATUS_ERROR;
    }

    // buff[0] is error code
    if (buff[0] != PN532_ERROR_NONE) {
        return buff[0];
    }

    // Copy 4 bytes for NTAG/Ultralight
    for (uint8_t i = 0; i < NTAG2XX_BLOCK_LENGTH; i++) {
        response[i] = buff[i + 1];
    }

    return PN532_ERROR_NONE;
}

/*
 * Read multiple pages at once using FAST_READ command.
 * start_page: First page to read
 * end_page: Last page to read (inclusive)
 * response: Buffer for data (must be large enough: (end-start+1)*4 bytes)
 * Returns: Number of bytes read, or error code
 */
int PN532_Ntag2xxFastRead(uint8_t* response, uint8_t start_page, uint8_t end_page)
{
    // InDataExchange params: [Tg=0x01] [CMD=FAST_READ] [StartPage] [EndPage]
    uint8_t params[4] = {0x01, NTAG_CMD_FAST_READ, start_page, end_page};
    uint8_t buff[64];  // Max we can read in one go
    
    uint8_t num_pages = end_page - start_page + 1;
    uint8_t expected_bytes = num_pages * 4;
    
    if (expected_bytes > 60) {
        return PN532_STATUS_ERROR;  // Too many pages requested
    }

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, sizeof(params),
                                    buff, sizeof(buff),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 1) {
        return PN532_STATUS_ERROR;
    }

    // buff[0] is error code
    if (buff[0] != PN532_ERROR_NONE) {
        return buff[0];
    }

    // Copy data (skip status byte)
    uint8_t bytes_read = (uint8_t)(result - 1);
    for (uint8_t i = 0; i < bytes_read; i++) {
        response[i] = buff[i + 1];
    }

    return bytes_read;
}

int PN532_Ntag2xxWriteBlock(const uint8_t* data, uint8_t block_number)
{
    // InDataExchange params: [Tg=0x01] [CMD=WRITE_UL] [Block#] [4 bytes data]
    uint8_t params[3 + NTAG2XX_BLOCK_LENGTH];
    uint8_t response[1];

    params[0] = 0x01;
    params[1] = MIFARE_ULTRALIGHT_CMD_WRITE;
    params[2] = block_number;

    for (uint8_t i = 0; i < NTAG2XX_BLOCK_LENGTH; i++) {
        params[3 + i] = data[i];
    }

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, sizeof(params),
                                    response, sizeof(response),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 1) {
        return PN532_STATUS_ERROR;
    }

    return response[0];  // Return error code (0 = success)
}

/* ---------------- MIFARE Classic Functions ---------------- */

#define PN532_COMMAND_INDATAEXCHANGE_AUTH  0x40

/*
 * Authenticate a MIFARE Classic block using InDataExchange.
 * The PN532 handles the crypto internally.
 * 
 * uid: Card UID (from ReadPassiveTarget)
 * uid_len: Length of UID (usually 4)
 * block_number: Block to authenticate (0-63 for 1K)
 * key_type: MIFARE_CMD_AUTH_A (0x60) or MIFARE_CMD_AUTH_B (0x61)
 * key: 6-byte key
 * Returns: 0 on success, error code on failure
 */
int PN532_MifareClassicAuth(const uint8_t* uid, uint8_t uid_len,
                            uint8_t block_number, uint8_t key_type,
                            const uint8_t* key)
{
    /*
     * InDataExchange for MIFARE auth:
     * [Tg] [AuthCmd] [BlockAddr] [KeyA/B 6 bytes] [UID 4 bytes]
     * 
     * Tg = 0x01 (target 1, from InListPassiveTarget)
     * AuthCmd = 0x60 (Key A) or 0x61 (Key B)
     * BlockAddr = block number to auth
     * Key = 6 bytes
     * UID = first 4 bytes of card UID
     */
    uint8_t params[3 + 6 + 4];  // Tg + AuthCmd + Block + Key(6) + UID(4)
    uint8_t response[1] = {0xFF};

    params[0] = 0x01;           // Target number (from InListPassiveTarget)
    params[1] = key_type;       // 0x60=KeyA, 0x61=KeyB
    params[2] = block_number;   // Block address

    // Key (6 bytes)
    for (uint8_t i = 0; i < 6; i++) {
        params[3 + i] = key[i];
    }

    // UID (first 4 bytes)
    for (uint8_t i = 0; i < 4; i++) {
        params[9 + i] = uid[i];
    }

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, 13,  // Always 13 bytes
                                    response, sizeof(response),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 0) {
        return PN532_STATUS_ERROR;
    }
    
    // Response[0] should be 0x00 for success
    return response[0];
}

/*
 * Read a 16-byte block from MIFARE Classic.
 * Must authenticate the sector first!
 * response: 16-byte buffer for block data
 * block_number: Block to read (0-63 for 1K)
 * Returns: 0 on success, error code on failure
 */
int PN532_MifareClassicReadBlock(uint8_t* response, uint8_t block_number)
{
    uint8_t params[3] = {0x01, MIFARE_CMD_READ, block_number};
    uint8_t buff[MIFARE_BLOCK_LENGTH + 1];  // Status + 16 bytes

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, sizeof(params),
                                    buff, sizeof(buff),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 1) {
        return PN532_STATUS_ERROR;
    }

    if (buff[0] != PN532_ERROR_NONE) {
        return buff[0];
    }

    // Copy 16 bytes
    for (uint8_t i = 0; i < MIFARE_BLOCK_LENGTH; i++) {
        response[i] = buff[i + 1];
    }

    return PN532_ERROR_NONE;
}

/* Global buffers for MIFARE Classic (PIC stack is limited) */
static uint8_t mf_buffer[MIFARE_BLOCK_LENGTH];
static uint8_t mf_current_uid[10];
static uint8_t mf_current_uid_len;
static uint8_t mf_ndef_data[64];  // Buffer to store NDEF data from MIFARE Classic
static char mf_text[32];          // Store extracted text
static uint8_t mf_text_len = 0;

/*
 * Read NDEF text from MIFARE Classic card.
 * Assumes card is already selected and Sector 1 contains NDEF data.
 * text_out: Buffer for extracted text
 * max_len: Size of buffer
 * Returns: PN532_STATUS_OK if text found, PN532_STATUS_ERROR otherwise
 */
int PN532_MifareClassicGetNdefText(const uint8_t* uid, uint8_t uid_len,
                                    char* text_out, uint8_t max_len)
{
    int auth_result;
    int read_result;
    int sel;
    uint8_t i;
    uint8_t k;
    
    if (!text_out || max_len == 0) return PN532_STATUS_ERROR;
    
    // Try each key to authenticate Sector 1 (block 4)
    auth_result = PN532_STATUS_ERROR;
    
    for (k = 0; k < NUM_COMMON_KEYS; k++) {
        // Select the card
        sel = PN532_ReadPassiveTarget(mf_current_uid, PN532_MIFARE_ISO14443A, 500);
        if (sel <= 0) continue;
        
        __delay_ms(10);
        
        // Try to authenticate block 4 (Sector 1)
        auth_result = PN532_MifareClassicAuth(uid, uid_len, 4,
                                               MIFARE_CMD_AUTH_A,
                                               MIFARE_COMMON_KEYS[k]);
        if (auth_result == PN532_ERROR_NONE) {
            break;  // Found working key
        }
    }
    
    if (auth_result != PN532_ERROR_NONE) {
        return PN532_STATUS_ERROR;
    }
    
    // Read blocks 4 and 5 (NDEF data in Sector 1)
    read_result = PN532_MifareClassicReadBlock(mf_ndef_data, 4);
    if (read_result != PN532_ERROR_NONE) return PN532_STATUS_ERROR;
    
    read_result = PN532_MifareClassicReadBlock(&mf_ndef_data[16], 5);
    if (read_result != PN532_ERROR_NONE) return PN532_STATUS_ERROR;
    
    // Parse NDEF TLV
    // Format: 03 [len] D1 01 [payload_len] 54 [status] [lang 2 bytes] [text...]
    if (mf_ndef_data[0] != 0x03) {
        return PN532_STATUS_ERROR;  // Not NDEF TLV
    }
    
    uint8_t tlv_len = mf_ndef_data[1];
    if (tlv_len < 5) return PN532_STATUS_ERROR;
    
    // Check for Text record (D1 01 xx 54)
    if (mf_ndef_data[2] != 0xD1 || mf_ndef_data[4] != 0x54) {
        return PN532_STATUS_ERROR;  // Not a text record
    }
    
    uint8_t payload_len = mf_ndef_data[5];
    uint8_t status_byte = mf_ndef_data[6];
    uint8_t lang_len = status_byte & 0x3F;  // Lower 6 bits
    
    // Text starts after: TLV(2) + header(4) + status(1) + lang(lang_len)
    uint8_t text_offset = 7 + lang_len;
    uint8_t text_len = payload_len - 1 - lang_len;
    
    if (text_len == 0 || text_offset + text_len > 32) {
        return PN532_STATUS_ERROR;
    }
    
    // Copy text
    uint8_t copy_len = (text_len < max_len - 1) ? text_len : (max_len - 1);
    for (i = 0; i < copy_len; i++) {
        text_out[i] = mf_ndef_data[text_offset + i];
    }
    text_out[copy_len] = '\0';
    
    return PN532_STATUS_OK;
}

/*
 * Dump MIFARE Classic 1K card (sectors 0-15).
 * Tries multiple common keys for authentication.
 * Only re-selects card when absolutely necessary.
 */
void PN532_DumpMifareClassic(const uint8_t* uid, uint8_t uid_len)
{
    int auth_result;
    int read_result;
    int sel_result;
    uint8_t first_block;
    uint8_t block_num;
    bool authenticated;
    uint8_t key_used;
    uint8_t last_key_used = 0xFF;  // Track which key worked last
    
    // Clear text buffer
    mf_text_len = 0;
    mf_text[0] = '\0';
    
    // Copy original UID
    for (uint8_t i = 0; i < uid_len; i++) {
        mf_current_uid[i] = uid[i];
    }
    mf_current_uid_len = uid_len;

    EUSART_Write_Text("\n=== MIFARE Classic 1K Dump ===\n");
    EUSART_Write_Text("UID: ");
    print_hex_array((uint8_t*)uid, uid_len);
    EUSART_Write_Text("\n");

    for (uint8_t sector = 0; sector < 16; sector++) {
        first_block = sector * 4;
        
        EUSART_Write_Text("\n[S");
        EUSART_Write_Integer(sector);
        EUSART_Write_Text("] ");

        authenticated = false;
        key_used = 0;
        
        // Try each key
        for (uint8_t k = 0; k < NUM_COMMON_KEYS && !authenticated; k++) {
            // Re-select card
            sel_result = PN532_ReadPassiveTarget(mf_current_uid, PN532_MIFARE_ISO14443A, 500);
            if (sel_result <= 0) {
                EUSART_Write_Text("NO CARD\n");
                goto dump_done;  // Exit cleanly
            }
            __delay_ms(10);
            
            // Try Key A
            auth_result = PN532_MifareClassicAuth(mf_current_uid, mf_current_uid_len, 
                                                   first_block,
                                                   MIFARE_CMD_AUTH_A,
                                                   MIFARE_COMMON_KEYS[k]);
            if (auth_result == PN532_ERROR_NONE) {
                authenticated = true;
                key_used = k;
                last_key_used = k;
                break;
            }
        }

        if (!authenticated) {
            EUSART_Write_Text("FAIL\n");
            last_key_used = 0xFF;
            continue;
        }

        // Show which key worked
        EUSART_Write_Text("OK key#");
        EUSART_Write_Integer(key_used);
        EUSART_Write_Text("\n");

        // Read all 4 blocks in this sector
        for (uint8_t block = 0; block < 4; block++) {
            block_num = first_block + block;
            
            read_result = PN532_MifareClassicReadBlock(mf_buffer, block_num);

            EUSART_Write_Text(" ");
            if (block_num < 10) EUSART_Write_Text(" ");
            EUSART_Write_Integer(block_num);
            EUSART_Write_Text(": ");

            if (read_result == PN532_ERROR_NONE) {
                print_hex_array(mf_buffer, MIFARE_BLOCK_LENGTH);
                
                // If this is block 4 (Sector 1, first data block), check for NDEF
                if (block_num == 4) {
                    // NDEF TLV format in block 4:
                    // [0]=03 (NDEF TLV type)
                    // [1]=length
                    // [2]=D1 (NDEF record: MB+ME+SR+TNF=well-known)
                    // [3]=type length (01)
                    // [4]=payload length
                    // [5]=54 ('T' = Text record type)
                    // [6]=status byte (lang length in lower 6 bits)
                    // [7,8]=language code "en"
                    // [9+]=text data
                    
                    if (mf_buffer[0] == 0x03 && mf_buffer[2] == 0xD1 && mf_buffer[5] == 0x54) {
                        uint8_t payload_len = mf_buffer[4];
                        uint8_t lang_len = mf_buffer[6] & 0x3F;
                        uint8_t text_start = 7 + lang_len;  // Skip status + language
                        uint8_t text_len = payload_len - 1 - lang_len;
                        
                        if (text_len > 0 && text_len < 30) {
                            mf_text_len = 0;
                            // Copy from block 4 (bytes 9-15 = 7 chars max)
                            for (uint8_t t = 0; t < text_len && text_start + t < 16; t++) {
                                mf_text[mf_text_len++] = (char)mf_buffer[text_start + t];
                            }
                            mf_text[mf_text_len] = '\0';
                        }
                    }
                }
                
                // If this is block 5 and we have partial text, append rest
                if (block_num == 5 && mf_text_len > 0 && mf_text_len < 30) {
                    // Check if there's more text (text continues until FE terminator)
                    for (uint8_t t = 0; t < 16 && mf_text_len < 30; t++) {
                        if (mf_buffer[t] == 0xFE || mf_buffer[t] == 0x00) {
                            break;  // Terminator or padding
                        }
                        mf_text[mf_text_len++] = (char)mf_buffer[t];
                    }
                    mf_text[mf_text_len] = '\0';
                }
            } else {
                EUSART_Write_Text("ERR 0x");
                print_hex8(read_result);
            }
            
            EUSART_Write_Text("\n");
        }
    }

dump_done:
    EUSART_Write_Text("\n=== Done ===\n");
    
    // Print extracted text if found
    if (mf_text_len > 0) {
        EUSART_Write_Text(">>> Text: \"");
        EUSART_Write_Text(mf_text);
        EUSART_Write_Text("\"\n");
    }
}

/*
 * Write a 16-byte block to MIFARE Classic.
 * Must authenticate the sector first!
 * WARNING: Writing to block 0 can brick the card!
 * WARNING: Writing wrong data to sector trailer locks the sector!
 */
int PN532_MifareClassicWriteBlock(const uint8_t* data, uint8_t block_number)
{
    uint8_t params[3 + MIFARE_BLOCK_LENGTH];
    uint8_t response[1];

    params[0] = 0x01;
    params[1] = MIFARE_CMD_WRITE;
    params[2] = block_number;

    for (uint8_t i = 0; i < MIFARE_BLOCK_LENGTH; i++) {
        params[3 + i] = data[i];
    }

    int result = PN532_CallFunction(PN532_COMMAND_INDATAEXCHANGE,
                                    params, sizeof(params),
                                    response, sizeof(response),
                                    PN532_DEFAULT_TIMEOUT);

    if (result < 1) {
        return PN532_STATUS_ERROR;
    }

    return response[0];
}

/*
 * Create a sector trailer with specified keys.
 * trailer: 16-byte output buffer
 * key_a: 6-byte Key A (NULL = 0xFFFFFFFFFFFF)
 * key_b: 6-byte Key B (NULL = 0xFFFFFFFFFFFF)
 * 
 * Access bits set to factory default (full access with both keys)
 */
void PN532_MakeSectorTrailer(uint8_t* trailer, 
                              const uint8_t* key_a,
                              const uint8_t* key_b)
{
    // Key A (bytes 0-5)
    if (key_a) {
        for (uint8_t i = 0; i < 6; i++) trailer[i] = key_a[i];
    } else {
        for (uint8_t i = 0; i < 6; i++) trailer[i] = 0xFF;
    }

    // Access bits (bytes 6-9) - factory default
    trailer[6] = 0xFF;
    trailer[7] = 0x07;
    trailer[8] = 0x80;
    trailer[9] = 0x69;

    // Key B (bytes 10-15)
    if (key_b) {
        for (uint8_t i = 0; i < 6; i++) trailer[10 + i] = key_b[i];
    } else {
        for (uint8_t i = 0; i < 6; i++) trailer[10 + i] = 0xFF;
    }
}

/*
 * Write new keys to a sector (change authentication keys).
 * Must be authenticated to the sector first!
 * 
 * sector: Sector number (0-15)
 * new_key_a: New Key A (NULL keeps 0xFF)
 * new_key_b: New Key B (NULL keeps 0xFF)
 * 
 * WARNING: If you forget the new keys, the sector is PERMANENTLY LOCKED!
 */
int PN532_MifareWriteKeys(uint8_t sector, 
                          const uint8_t* new_key_a,
                          const uint8_t* new_key_b)
{
    uint8_t trailer[16];
    uint8_t trailer_block = (sector * 4) + 3;
    
    // Build new trailer
    PN532_MakeSectorTrailer(trailer, new_key_a, new_key_b);
    
    // Write it
    return PN532_MifareClassicWriteBlock(trailer, trailer_block);
}

/* ---------------- NDEF TLV Parsing ---------------- */

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

/*
 * Find NDEF TLV (type 0x03) in card dump.
 * TLVs start at page 4 (byte offset 16).
 */
static int tlv_find_ndef(const uint8_t *buf, uint8_t len, 
                         const uint8_t **ndef, uint8_t *ndef_len)
{
    if (!buf || len < 18) return -1;

    uint8_t i = 16;  // Start at page 4
    
    while (i < len) {
        uint8_t t = buf[i++];

        if (t == 0x00) {            // NULL TLV padding
            continue;
        } else if (t == 0xFE) {     // Terminator TLV
            break;
        }

        if (i >= len) return -1;

        uint8_t L = 0;
        if (buf[i] == 0xFF) {       // 3-byte length format
            if (i + 2 >= len) return -1;
            L = buf[i + 2];         // Just use low byte for small tags
            i += 3;
        } else {
            L = buf[i++];
        }

        if (i + L > len) return -1;

        if (t == 0x03) {            // NDEF Message TLV
            *ndef = &buf[i];
            *ndef_len = L;
            return 0;
        }

        i += L;  // Skip unknown TLV
    }
    return -1;
}

/*
 * Extract text from NDEF "T" (Text) record.
 */
static int ndef_get_text(const uint8_t *ndef, uint8_t ndef_len, 
                         char *out, uint8_t out_size)
{
    if (!ndef || ndef_len < 3 || !out || out_size == 0) return -1;

    uint8_t hdr = ndef[0];
    uint8_t type_len = ndef[1];

    uint8_t idx = 2;
    uint8_t payload_len = 0;

    // Short Record?
    if (hdr & 0x10) {  // SR bit
        if (idx >= ndef_len) return -1;
        payload_len = ndef[idx++];
    } else {
        // Long record - skip 4-byte length, use last byte
        if (idx + 3 >= ndef_len) return -1;
        payload_len = ndef[idx + 3];
        idx += 4;
    }

    // ID Length present?
    if (hdr & 0x08) {  // IL bit
        if (idx >= ndef_len) return -1;
        uint8_t id_len = ndef[idx++];
        if (idx + id_len > ndef_len) return -1;
        idx += id_len;
    }

    // Type
    if (idx + type_len > ndef_len) return -1;
    const uint8_t *type = &ndef[idx];
    idx += type_len;

    // Payload
    if (idx + payload_len > ndef_len) return -1;
    const uint8_t *payload = &ndef[idx];

    // Must be Well-known Text: TNF=0x01, type="T"
    if (!((hdr & 0x07) == 0x01 && type_len == 1 && type[0] == 'T')) {
        return -1;
    }
    
    if (payload_len == 0) return -1;

    uint8_t status = payload[0];
    uint8_t lang_len = status & 0x3F;  // Lower 6 bits = language code length
    
    if (1 + lang_len > payload_len) return -1;

    const uint8_t *text = &payload[1 + lang_len];
    uint8_t text_len = payload_len - 1 - lang_len;

    uint8_t copy_len = MIN(text_len, out_size - 1);
    memcpy(out, text, copy_len);
    out[copy_len] = '\0';
    
    return 0;
}

/* ---------------- High-Level Card Reading ---------------- */

/*
 * Dump all blocks from an NTAG/Ultralight card and print to UART.
 * Uses FAST_READ to get all pages in one command (more reliable).
 * Also extracts NDEF text if present.
 */
char text[NDEF_TEXT_MAX_LEN];
void PN532_DumpNtagCard(void)
{
    EUSART_Write_Text("\n=== NTAG Card Dump ===\n");

    // Clear dump buffer
    memset(g_last_dump, 0, sizeof(g_last_dump));
    g_last_dump_len = 0;

    // Try FAST_READ first (reads pages 0-15 in one command)
    int result = PN532_Ntag2xxFastRead(g_last_dump, 0, 15);
    
    if (result > 0) {
        // Success - display the data
        g_last_dump_len = (uint8_t)result;
        uint8_t num_pages = (uint8_t)(result / 4);
        
        for (uint8_t page = 0; page < num_pages; page++) {
            uint8_t* data = &g_last_dump[page * 4];
            
            EUSART_Write_Text("Page ");
            if (page < 10) EUSART_Write_Text(" ");
            EUSART_Write_Integer(page);
            EUSART_Write_Text(": ");

            // Print hex
            print_hex_array(data, NTAG2XX_BLOCK_LENGTH);

            // Print ASCII
            EUSART_Write_Text(" | ");
            for (uint8_t i = 0; i < NTAG2XX_BLOCK_LENGTH; i++) {
                print_ascii_char(data[i]);
            }

            // Block description
            if (page == 0) {
                EUSART_Write_Text(" [UID/MFG]");
            } else if (page == 1) {
                EUSART_Write_Text(" [UID]");
            } else if (page == 2) {
                EUSART_Write_Text(" [Internal]");
            } else if (page == 3) {
                EUSART_Write_Text(" [CC]");
            } else {
                EUSART_Write_Text(" [Data]");
            }

            EUSART_Write_Text("\n");
        }

        EUSART_Write_Text("\nRead ");
        EUSART_Write_Integer(num_pages);
        EUSART_Write_Text(" pages OK\n");
        
    } else {
        // FAST_READ failed, fall back to page-by-page
        EUSART_Write_Text("FAST_READ failed (0x");
        print_hex8((uint8_t)(-result));
        EUSART_Write_Text("), trying page-by-page...\n");
        
        uint8_t buffer[NTAG2XX_BLOCK_LENGTH];
        uint8_t blocks_read = 0;

        for (uint8_t block = 0; block < 16; block++) {
            int error = PN532_Ntag2xxReadBlock(buffer, block);

            if (error == PN532_ERROR_NONE) {
                blocks_read++;

                g_last_dump[block * 4 + 0] = buffer[0];
                g_last_dump[block * 4 + 1] = buffer[1];
                g_last_dump[block * 4 + 2] = buffer[2];
                g_last_dump[block * 4 + 3] = buffer[3];

                EUSART_Write_Text("Page ");
                if (block < 10) EUSART_Write_Text(" ");
                EUSART_Write_Integer(block);
                EUSART_Write_Text(": ");
                print_hex_array(buffer, NTAG2XX_BLOCK_LENGTH);
                EUSART_Write_Text(" | ");
                for (uint8_t i = 0; i < NTAG2XX_BLOCK_LENGTH; i++) {
                    print_ascii_char(buffer[i]);
                }
                EUSART_Write_Text("\n");
            } else {
                EUSART_Write_Text("Page ");
                if (block < 10) EUSART_Write_Text(" ");
                EUSART_Write_Integer(block);
                EUSART_Write_Text(" err 0x");
                print_hex8(error);
                EUSART_Write_Text("\n");
            }
            
            __delay_ms(10);
        }

        g_last_dump_len = 64;
        EUSART_Write_Text("\nRead ");
        EUSART_Write_Integer(blocks_read);
        EUSART_Write_Text(" pages\n");
    }

    // Try to extract NDEF text
    
    if (PN532_GetNdefText(text, sizeof(text)) == PN532_STATUS_OK) {
        EUSART_Write_Text("\nNDEF Text: ");
        EUSART_Write_Text(text);
        EUSART_Write_Text("\n");
    } else {
        EUSART_Write_Text("\nNo NDEF text record found\n");
    }
}

/*
 * Get NDEF text from last card dump.
 * Call PN532_DumpNtagCard() first to read the card.
 * Returns PN532_STATUS_OK if text was found.
 */
int PN532_GetNdefText(char *text_out, uint8_t max_len)
{
    if (!text_out || max_len == 0 || g_last_dump_len == 0) {
        return PN532_STATUS_ERROR;
    }

    const uint8_t *ndef = NULL;
    uint8_t ndef_len = 0;

    if (tlv_find_ndef(g_last_dump, g_last_dump_len, &ndef, &ndef_len) != 0) {
        return PN532_STATUS_ERROR;
    }

    if (ndef_get_text(ndef, ndef_len, text_out, max_len) != 0) {
        return PN532_STATUS_ERROR;
    }

    return PN532_STATUS_OK;
}

/*
 * Clear the stored card dump.
 */
void PN532_ClearDump(void)
{
    memset(g_last_dump, 0, sizeof(g_last_dump));
    g_last_dump_len = 0;
}
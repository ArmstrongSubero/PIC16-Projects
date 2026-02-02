/*
 * File: pn532.h
 * PN532 NFC Driver for PIC16F1718/1719 using I2C
 * With NTAG/Ultralight read/write and NDEF text extraction
 */

#ifndef PN532_PIC_I2C_H
#define PN532_PIC_I2C_H

#include <stdint.h>
#include <stdbool.h>

/* Status codes */
#define PN532_STATUS_ERROR  (-1)
#define PN532_STATUS_OK     (0)

/* Card baud rates for ReadPassiveTarget */
#define PN532_MIFARE_ISO14443A  0x00

/* ---------------- Core Functions ---------------- */

/*
 * Initialize the PN532 driver.
 * Call this once after I2C is initialized.
 */
int PN532_Init_PIC(void);

/*
 * Get PN532 firmware version.
 * version: 4-byte buffer [IC, Ver, Rev, Support]
 */
int PN532_GetFirmwareVersion(uint8_t* version);

/*
 * Configure the Security Access Module.
 * Must be called before reading cards.
 */
int PN532_SamConfiguration(void);

/*
 * Wait for and read a passive target (NFC card).
 * uid: Buffer for UID (at least 10 bytes)
 * card_baud: Use PN532_MIFARE_ISO14443A
 * timeout_ms: How long to wait for a card
 * Returns: UID length on success, PN532_STATUS_ERROR on failure
 */
int PN532_ReadPassiveTarget(uint8_t* uid, uint8_t card_baud, uint32_t timeout_ms);

/* ---------------- NTAG/Ultralight Functions ---------------- */

/*
 * Read a 4-byte page from NTAG/Ultralight card.
 * response: 4-byte buffer for page data
 * block_number: Page number (0-15 typical, up to 44 for NTAG216)
 * Returns: 0 on success, error code on failure
 */
int PN532_Ntag2xxReadBlock(uint8_t* response, uint8_t block_number);

/*
 * Read multiple pages at once using FAST_READ (more reliable).
 * response: Buffer for data (must be (end-start+1)*4 bytes)
 * start_page: First page to read
 * end_page: Last page to read (inclusive)
 * Returns: Number of bytes read on success, negative error code on failure
 */
int PN532_Ntag2xxFastRead(uint8_t* response, uint8_t start_page, uint8_t end_page);

/*
 * Write a 4-byte page to NTAG/Ultralight card.
 * data: 4 bytes to write
 * block_number: Page number (4+ for user data)
 * Returns: 0 on success, error code on failure
 */
int PN532_Ntag2xxWriteBlock(const uint8_t* data, uint8_t block_number);

/* ---------------- MIFARE Classic Functions ---------------- */

/* Authentication key types */
#define MIFARE_CMD_AUTH_A  0x60
#define MIFARE_CMD_AUTH_B  0x61

/*
 * Authenticate a MIFARE Classic sector.
 * Must call before reading/writing blocks in that sector.
 * uid: Card UID from ReadPassiveTarget
 * uid_len: UID length (usually 4)
 * block_number: Any block in the sector to authenticate
 * key_type: MIFARE_CMD_AUTH_A or MIFARE_CMD_AUTH_B
 * key: 6-byte authentication key
 * Returns: 0 on success, error code on failure
 */
int PN532_MifareClassicAuth(const uint8_t* uid, uint8_t uid_len,
                            uint8_t block_number, uint8_t key_type,
                            const uint8_t* key);

/*
 * Read a 16-byte block from MIFARE Classic.
 * Must authenticate the sector first!
 * response: 16-byte buffer
 * block_number: Block to read (0-63 for 1K, 0-255 for 4K)
 * Returns: 0 on success, error code on failure
 */
int PN532_MifareClassicReadBlock(uint8_t* response, uint8_t block_number);

/*
 * Dump entire MIFARE Classic 1K card to UART.
 * Tries multiple common keys automatically.
 * uid: Card UID
 * uid_len: UID length
 */
void PN532_DumpMifareClassic(const uint8_t* uid, uint8_t uid_len);

/*
 * Write a 16-byte block to MIFARE Classic.
 * Must authenticate first!
 * WARNING: Block 0 and sector trailers are dangerous to write!
 */
int PN532_MifareClassicWriteBlock(const uint8_t* data, uint8_t block_number);

/*
 * Create a sector trailer buffer with specified keys.
 * trailer: 16-byte output buffer
 * key_a: 6-byte Key A (NULL = default 0xFFFFFFFFFFFF)
 * key_b: 6-byte Key B (NULL = default 0xFFFFFFFFFFFF)
 */
void PN532_MakeSectorTrailer(uint8_t* trailer, 
                              const uint8_t* key_a,
                              const uint8_t* key_b);

/*
 * Write new keys to a sector.
 * Must authenticate to sector first!
 * WARNING: Forgetting keys = PERMANENTLY LOCKED sector!
 */
int PN532_MifareWriteKeys(uint8_t sector, 
                          const uint8_t* new_key_a,
                          const uint8_t* new_key_b);

/*
 * Read NDEF text from MIFARE Classic card.
 * uid: Card UID
 * uid_len: UID length
 * text_out: Buffer for text
 * max_len: Buffer size
 * Returns: PN532_STATUS_OK if text found
 */
int PN532_MifareClassicGetNdefText(const uint8_t* uid, uint8_t uid_len,
                                    char* text_out, uint8_t max_len);

/* ---------------- NDEF Functions ---------------- */

/*
 * Dump entire NTAG card (pages 0-15) to UART.
 * Also stores data for NDEF extraction.
 */
void PN532_DumpNtagCard(void);

/*
 * Get NDEF text from last dumped card.
 * Call PN532_DumpNtagCard() first.
 * text_out: Buffer for extracted text
 * max_len: Size of buffer
 * Returns: PN532_STATUS_OK if text found
 */
int PN532_GetNdefText(char *text_out, uint8_t max_len);

/*
 * Clear stored card dump data.
 */
void PN532_ClearDump(void);

#endif /* PN532_PIC_I2C_H */
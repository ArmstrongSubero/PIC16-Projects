#define SD_TIMEOUT 4096

extern unsigned char SDRdata[512];
extern unsigned char SDWdata[512];

void SDcard_init(void);
void SDcard_read_block(unsigned long address);
void SDcard_write_block(unsigned long address);

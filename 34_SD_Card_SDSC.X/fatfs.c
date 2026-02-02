#include <xc.h>
#include <stdint.h>
#include <stdlib.h>

#include "fatfs.h"
#include "sdcard.h"
#include "EUSART.h"

// holds partition 1 PBR address
unsigned long part1_addr;
// number of bytes per sector
unsigned int sector_size;
// number of sectors per cluster
unsigned char sectors_cluster;
// number of reserved sectors
unsigned int sectors_reserved;
// number of FAT copies
unsigned char FAT_copies;
// number of possible root entries
unsigned int root_entries;
// number of sectors per FAT
unsigned int sectors_FAT;

// FAT addresses
unsigned long FAT_address[2];
// root directory table start address
unsigned long rootdir_start;
// data region start address
unsigned long datareg_start;

// file specific variables
unsigned int  cluster_number;          // starting cluster number of file
unsigned long start_sector_address;    // starting sector of cluster address
unsigned long current_sector_address;  // sector address of current sector
unsigned char current_sector = 0;      // current sector number
unsigned int  entry_addr;              // entry address in root directory table
unsigned int  byte_number = 0;         // number of byte in sector
unsigned long file_length = 0;         // file length

// ---- minimal debug helpers ----
static inline void dbg(const char *s)
{
    EUSART_Write_Text((char*)s); // cast because your API isn't const-correct
}

static inline void dbg_nl(void)
{
    EUSART_Write('\n');
}

// Print 32-bit value as hex (no stdlib ltoa required)
static void dbg_hex32(unsigned long v)
{
    static const char hex[] = "0123456789ABCDEF";
    char buf[11]; // "0x" + 8 digits + '\0'
    buf[0] = '0';
    buf[1] = 'x';
    for (int i = 0; i < 8; i++)
    {
        unsigned char nib = (v >> (28 - 4*i)) & 0x0F;
        buf[2 + i] = hex[nib];
    }
    buf[10] = '\0';
    dbg(buf);
}

// Print 16-bit value as decimal using your helper
static void dbg_u16_dec(unsigned int v)
{
    EUSART_Write_Integer((int)v);
}

void mount_disk(void)
{
    // read sector 0 (MBR) from card
    SDcard_read_block(0x00000000);

    // read partition 1 LBA from MBR (little endian)
    part1_addr  = (unsigned long)SDRdata[0x01C6];
    part1_addr |= ((unsigned long)SDRdata[0x01C7] << 8);
    part1_addr |= ((unsigned long)SDRdata[0x01C8] << 16);
    part1_addr |= ((unsigned long)SDRdata[0x01C9] << 24);

    // convert LBA (sectors) to byte address (SDSC-style)
    part1_addr *= 0x00000200UL;

    // read first sector (PBR) of partition 1
    SDcard_read_block(part1_addr);

    // read out BPB fields
    sector_size = (unsigned int)SDRdata[0x000B];
    sector_size |= ((unsigned int)SDRdata[0x000C] << 8);

    sectors_cluster = SDRdata[0x000D];

    sectors_reserved  = (unsigned int)SDRdata[0x000E];
    sectors_reserved |= ((unsigned int)SDRdata[0x000F] << 8);

    FAT_copies = SDRdata[0x0010];

    root_entries  = (unsigned int)SDRdata[0x0011];
    root_entries |= ((unsigned int)SDRdata[0x0012] << 8);

    sectors_FAT  = (unsigned int)SDRdata[0x0016];
    sectors_FAT |= ((unsigned int)SDRdata[0x0017] << 8);

    // calculate addresses of both FAT copies (byte addresses)
    FAT_address[0] = part1_addr + ((unsigned long)sectors_reserved * (unsigned long)sector_size);
    FAT_address[1] = FAT_address[0] + ((unsigned long)sectors_FAT * (unsigned long)sector_size);

    // calculate root directory table start address
    rootdir_start = FAT_address[1] + ((unsigned long)sectors_FAT * (unsigned long)sector_size);

    // calculate start address of data region
    datareg_start = rootdir_start + ((unsigned long)root_entries * 32UL);

    // optional debug
    dbg("Mounted disk.\n");
    dbg("PBR @ "); dbg_hex32(part1_addr); dbg_nl();
}

void file_create(const unsigned char* filename)
{
    // read first sector of FAT1
    SDcard_read_block(FAT_address[0]);

    // find first unallocated cluster (NOTE: only searches within this one FAT sector)
    dbg("Searching first unallocated cluster...");
    for (cluster_number = 0; cluster_number < 0xFFFF; cluster_number++)
    {
        unsigned int idx = (unsigned int)(cluster_number * 2U);
        if (idx + 1U >= 512U) break; // prevent buffer overrun in this simplified implementation

        if ((SDRdata[idx] == 0) && (SDRdata[idx + 1] == 0))
            break;
    }
    dbg("done!\n");

    // allocate cluster in FAT
    for (unsigned int i = 0; i < 512; i++)
        SDWdata[i] = SDRdata[i];

    {
        unsigned int idx = (unsigned int)(cluster_number * 2U);
        if (idx + 1U < 512U)
        {
            SDWdata[idx]     = 0xFF;
            SDWdata[idx + 1] = 0xFF;
        }
    }

    // write new FAT to both fat copies
    SDcard_write_block(FAT_address[0]);
    SDcard_write_block(FAT_address[1]);

    // calculate address of first sector in cluster
    start_sector_address =
        datareg_start +
        ((unsigned long)(cluster_number - 2U) *
         (unsigned long)sectors_cluster *
         (unsigned long)sector_size);

    current_sector = 0;

    dbg("Cluster number: ");
    dbg_u16_dec(cluster_number);
    dbg_nl();

    dbg("Sector 0 address: ");
    dbg_hex32(start_sector_address);
    dbg_nl();

    // read first sector of root directory table
    SDcard_read_block(rootdir_start);

    // search first unallocated entry (NOTE: only searches first 512B sector)
    dbg("Searching first unallocated root table entry...");
    for (entry_addr = 0; entry_addr < 0x0200; entry_addr += 32)
    {
        if ((SDRdata[entry_addr] == 0xE5) || (SDRdata[entry_addr] == 0x00))
            break;
    }
    dbg("done!\n");

    dbg("Entry offset: ");
    dbg_hex32((unsigned long)entry_addr);
    dbg_nl();

    // copy read table block to SDWdata
    for (unsigned int i = 0; i < 512; i++)
        SDWdata[i] = SDRdata[i];

    // create 8.3 filename (very simplified: copies characters excluding '.')
    unsigned char offset = 0;
    while (*filename)
    {
        if (*filename != '.')
        {
            SDWdata[entry_addr + offset] = *filename;
            filename++;
            offset++;
        }
        else
        {
            filename++;
        }
        if (offset >= 11) break; // do not overrun 8.3 name field
    }

    // attribute byte: archive
    SDWdata[entry_addr + 0x0B] = 0x20;

    // timestamps (kept as your constants)
    SDWdata[entry_addr + 0x0C] = 0x00;
    SDWdata[entry_addr + 0x0D] = 0x00;

    SDWdata[entry_addr + 0x0E] = 0x00;
    SDWdata[entry_addr + 0x0F] = 0x60;

    SDWdata[entry_addr + 0x10] = 0x21;
    SDWdata[entry_addr + 0x11] = 0x24;

    SDWdata[entry_addr + 0x12] = 0x21;
    SDWdata[entry_addr + 0x13] = 0x24;

    SDWdata[entry_addr + 0x14] = 0x00;
    SDWdata[entry_addr + 0x15] = 0x00;

    SDWdata[entry_addr + 0x16] = 0x00;
    SDWdata[entry_addr + 0x17] = 0x60;

    SDWdata[entry_addr + 0x18] = 0x21;
    SDWdata[entry_addr + 0x19] = 0x24;

    // starting cluster
    SDWdata[entry_addr + 0x1A] = (unsigned char)(cluster_number & 0xFF);
    SDWdata[entry_addr + 0x1B] = (unsigned char)((cluster_number >> 8) & 0xFF);

    // initial size 0
    SDWdata[entry_addr + 0x1C] = 0x00;
    SDWdata[entry_addr + 0x1D] = 0x00;
    SDWdata[entry_addr + 0x1E] = 0x00;
    SDWdata[entry_addr + 0x1F] = 0x00;

    // write directory sector back
    SDcard_write_block(rootdir_start);
}

void sector_open(void)
{
    current_sector_address =
        start_sector_address +
        ((unsigned long)current_sector * (unsigned long)sector_size);

    SDcard_read_block(current_sector_address);

    dbg("Address of current sector: ");
    dbg_hex32(current_sector_address);
    dbg_nl();

    for (unsigned int i = 0; i < 512; i++)
        SDWdata[i] = SDRdata[i];
}

void sector_close(void)
{
    SDcard_write_block(current_sector_address);
}

void file_append(const unsigned char* string)
{
    while (*string)
    {
        if (byte_number < 512)
        {
            SDWdata[byte_number] = *string;
            string++;
            byte_number++;
            file_length++;
        }
        else
        {
            sector_close();
            byte_number = 0;
            current_sector++;
            sector_open();
        }
    }
}

void file_update_size(void)
{
    SDcard_read_block(rootdir_start);

    for (unsigned int i = 0; i < 512; i++)
        SDWdata[i] = SDRdata[i];

    dbg("File size: ");
    dbg_hex32(file_length);
    dbg_nl();

    SDWdata[entry_addr + 0x1C] = (unsigned char)(file_length & 0xFF);
    SDWdata[entry_addr + 0x1D] = (unsigned char)((file_length >> 8) & 0xFF);
    SDWdata[entry_addr + 0x1E] = (unsigned char)((file_length >> 16) & 0xFF);
    SDWdata[entry_addr + 0x1F] = (unsigned char)((file_length >> 24) & 0xFF);

    SDcard_write_block(rootdir_start);
}

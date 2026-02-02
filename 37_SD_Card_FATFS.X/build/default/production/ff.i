# 1 "ff.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ff.c" 2
# 22 "ff.c"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\string.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\string.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\string.h" 2 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 128 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 174 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 421 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 22 "ff.c" 2

# 1 "./ff.h" 1
# 30 "./ff.h"
# 1 "./ffconf.h" 1
# 30 "./ff.h" 2
# 49 "./ff.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\stdint.h" 1 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef short intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 179 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 215 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\c99\\stdint.h" 2 3
# 49 "./ff.h" 2

typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;
typedef WORD WCHAR;
# 83 "./ff.h"
typedef DWORD FSIZE_t;
typedef DWORD LBA_t;
# 106 "./ff.h"
typedef char TCHAR;
# 150 "./ff.h"
typedef struct {
 BYTE fs_type;
 BYTE pdrv;
 BYTE ldrv;
 BYTE n_fats;
 BYTE wflag;
 BYTE fsi_flag;
 WORD id;
 WORD n_rootdir;
 WORD csize;







 DWORD last_clst;
 DWORD free_clst;




 DWORD n_fatent;
 DWORD fsize;
 LBA_t winsect;
 LBA_t volbase;
 LBA_t fatbase;
 LBA_t dirbase;
 LBA_t database;
# 188 "./ff.h"
 BYTE win[512];
} FATFS;





typedef struct {
 FATFS* fs;
 WORD id;
 BYTE attr;
 BYTE stat;
 DWORD sclust;
 FSIZE_t objsize;
# 212 "./ff.h"
} FFOBJID;





typedef struct {
 FFOBJID obj;
 BYTE flag;
 BYTE err;
 FSIZE_t fptr;
 DWORD clust;
 LBA_t sect;

 LBA_t dir_sect;
 BYTE* dir_ptr;







} FIL;





typedef struct {
 FFOBJID obj;
 DWORD dptr;
 DWORD clust;
 LBA_t sect;
 BYTE* dir;
 BYTE fn[12];






} DIR;





typedef struct {
 FSIZE_t fsize;
 WORD fdate;
 WORD ftime;




 BYTE fattrib;




 TCHAR fname[12 + 1];

} FILINFO;





typedef struct {
 BYTE fmt;
 BYTE n_fat;
 UINT align;
 UINT n_root;
 DWORD au_size;
} MKFS_PARM;





typedef enum {
 FR_OK = 0,
 FR_DISK_ERR,
 FR_INT_ERR,
 FR_NOT_READY,
 FR_NO_FILE,
 FR_NO_PATH,
 FR_INVALID_NAME,
 FR_DENIED,
 FR_EXIST,
 FR_INVALID_OBJECT,
 FR_WRITE_PROTECTED,
 FR_INVALID_DRIVE,
 FR_NOT_ENABLED,
 FR_NO_FILESYSTEM,
 FR_MKFS_ABORTED,
 FR_TIMEOUT,
 FR_LOCKED,
 FR_NOT_ENOUGH_CORE,
 FR_TOO_MANY_OPEN_FILES,
 FR_INVALID_PARAMETER
} FRESULT;
# 323 "./ff.h"
FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);
FRESULT f_close (FIL* fp);
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);
FRESULT f_truncate (FIL* fp);
FRESULT f_sync (FIL* fp);
FRESULT f_opendir (DIR* dp, const TCHAR* path);
FRESULT f_closedir (DIR* dp);
FRESULT f_readdir (DIR* dp, FILINFO* fno);
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);
FRESULT f_findnext (DIR* dp, FILINFO* fno);
FRESULT f_mkdir (const TCHAR* path);
FRESULT f_unlink (const TCHAR* path);
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);
FRESULT f_stat (const TCHAR* path, FILINFO* fno);
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);
FRESULT f_chdir (const TCHAR* path);
FRESULT f_chdrive (const TCHAR* path);
FRESULT f_getcwd (TCHAR* buff, UINT len);
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);
FRESULT f_setlabel (const TCHAR* label);
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);
FRESULT f_expand (FIL* fp, FSIZE_t fsz, BYTE opt);
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);
FRESULT f_mkfs (const TCHAR* path, const MKFS_PARM* opt, void* work, UINT len);
FRESULT f_fdisk (BYTE pdrv, const LBA_t ptbl[], void* work);
FRESULT f_setcp (WORD cp);
int f_putc (TCHAR c, FIL* fp);
int f_puts (const TCHAR* str, FIL* cp);
int f_printf (FIL* fp, const TCHAR* str, ...);
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);
# 23 "ff.c" 2

# 1 "./diskio.h" 1
# 17 "./diskio.h"
typedef BYTE DSTATUS;


typedef enum {
 RES_OK = 0,
 RES_ERROR,
 RES_WRPRT,
 RES_NOTRDY,
 RES_PARERR
} DRESULT;






DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count);

DRESULT disk_write (BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count);


DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);

void disk_timerproc (void);
# 24 "ff.c" 2
# 464 "ff.c"
static FATFS *FatFs[1];
static WORD Fsid;
# 597 "ff.c"
static const BYTE ExCvt[] = {0x80,0x9A,0x45,0x41,0x8E,0x41,0x8F,0x80,0x45,0x45,0x45,0x49,0x49,0x49,0x8E,0x8F, 0x90,0x92,0x92,0x4F,0x99,0x4F,0x55,0x55,0x59,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F, 0x41,0x49,0x4F,0x55,0xA5,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF, 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF, 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF, 0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF, 0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF, 0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF};
# 619 "ff.c"
static WORD ld_16 (const BYTE* ptr)
{
 WORD rv;

 rv = ptr[1];
 rv = rv << 8 | ptr[0];
 return rv;
}

static DWORD ld_32 (const BYTE* ptr)
{
 DWORD rv;

 rv = ptr[3];
 rv = rv << 8 | ptr[2];
 rv = rv << 8 | ptr[1];
 rv = rv << 8 | ptr[0];
 return rv;
}
# 657 "ff.c"
static void st_16 (BYTE* ptr, WORD val)
{
 *ptr++ = (BYTE)val; val >>= 8;
 *ptr++ = (BYTE)val;
}

static void st_32 (BYTE* ptr, DWORD val)
{
 *ptr++ = (BYTE)val; val >>= 8;
 *ptr++ = (BYTE)val; val >>= 8;
 *ptr++ = (BYTE)val; val >>= 8;
 *ptr++ = (BYTE)val;
}
# 693 "ff.c"
static int dbc_1st (BYTE c)
{
# 706 "ff.c"
 if (c != 0) return 0;

 return 0;
}



static int dbc_2nd (BYTE c)
{
# 728 "ff.c"
 if (c != 0) return 0;

 return 0;
}
# 1057 "ff.c"
static FRESULT sync_window (
 FATFS* fs
)
{
 FRESULT res = FR_OK;


 if (fs->wflag) {
  if (disk_write(fs->pdrv, fs->win, fs->winsect, 1) == RES_OK) {
   fs->wflag = 0;
   if (fs->winsect - fs->fatbase < fs->fsize) {
    if (fs->n_fats == 2) disk_write(fs->pdrv, fs->win, fs->winsect + fs->fsize, 1);
   }
  } else {
   res = FR_DISK_ERR;
  }
 }
 return res;
}



static FRESULT move_window (
 FATFS* fs,
 LBA_t sect
)
{
 FRESULT res = FR_OK;


 if (sect != fs->winsect) {

  res = sync_window(fs);

  if (res == FR_OK) {
   if (disk_read(fs->pdrv, fs->win, sect, 1) != RES_OK) {
    sect = (LBA_t)0 - 1;
    res = FR_DISK_ERR;
   }
   fs->winsect = sect;
  }
 }
 return res;
}
# 1110 "ff.c"
static FRESULT sync_fs (
 FATFS* fs
)
{
 FRESULT res;


 res = sync_window(fs);
 if (res == FR_OK) {
  if (fs->fsi_flag == 1) {
   fs->fsi_flag = 0;
   if (fs->fs_type == 3) {

    memset(fs->win, 0, sizeof fs->win);
    st_32(fs->win + 0, 0x41615252);
    st_32(fs->win + 484, 0x61417272);
    st_32(fs->win + 488, fs->free_clst);
    st_32(fs->win + 492, fs->last_clst);
    st_32(fs->win + 508, 0xAA550000);
    disk_write(fs->pdrv, fs->win, fs->winsect = fs->volbase + 1, 1);
   }
# 1143 "ff.c"
  }

  if (disk_ioctl(fs->pdrv, 0, 0) != RES_OK) res = FR_DISK_ERR;
 }

 return res;
}
# 1159 "ff.c"
static LBA_t clst2sect (
 FATFS* fs,
 DWORD clst
)
{
 clst -= 2;
 if (clst >= fs->n_fatent - 2) return 0;
 return fs->database + (LBA_t)fs->csize * clst;
}
# 1176 "ff.c"
static DWORD get_fat (
 FFOBJID* obj,
 DWORD clst
)
{
 UINT wc, bc;
 DWORD val;
 FATFS *fs = obj->fs;


 if (clst < 2 || clst >= fs->n_fatent) {
  val = 1;

 } else {
  val = 0xFFFFFFFF;

  switch (fs->fs_type) {
  case 1 :
   bc = (UINT)clst; bc += bc / 2;
   if (move_window(fs, fs->fatbase + (bc / ((UINT)512))) != FR_OK) break;
   wc = fs->win[bc++ % ((UINT)512)];
   if (move_window(fs, fs->fatbase + (bc / ((UINT)512))) != FR_OK) break;
   wc |= fs->win[bc % ((UINT)512)] << 8;
   val = (clst & 1) ? (wc >> 4) : (wc & 0xFFF);
   break;

  case 2 :
   if (move_window(fs, fs->fatbase + (clst / (((UINT)512) / 2))) != FR_OK) break;
   val = ld_16(fs->win + clst * 2 % ((UINT)512));
   break;

  case 3 :
   if (move_window(fs, fs->fatbase + (clst / (((UINT)512) / 4))) != FR_OK) break;
   val = ld_32(fs->win + clst * 4 % ((UINT)512)) & 0x0FFFFFFF;
   break;
# 1238 "ff.c"
  default:
   val = 1;
  }
 }

 return val;
}
# 1254 "ff.c"
static FRESULT put_fat (
 FATFS* fs,
 DWORD clst,
 DWORD val
)
{
 UINT bc;
 BYTE *p;
 FRESULT res = FR_INT_ERR;


 if (clst >= 2 && clst < fs->n_fatent) {
  switch (fs->fs_type) {
  case 1:
   bc = (UINT)clst; bc += bc / 2;
   res = move_window(fs, fs->fatbase + (bc / ((UINT)512)));
   if (res != FR_OK) break;
   p = fs->win + bc++ % ((UINT)512);
   *p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;
   fs->wflag = 1;
   res = move_window(fs, fs->fatbase + (bc / ((UINT)512)));
   if (res != FR_OK) break;
   p = fs->win + bc % ((UINT)512);
   *p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));
   fs->wflag = 1;
   break;

  case 2:
   res = move_window(fs, fs->fatbase + (clst / (((UINT)512) / 2)));
   if (res != FR_OK) break;
   st_16(fs->win + clst * 2 % ((UINT)512), (WORD)val);
   fs->wflag = 1;
   break;

  case 3:



   res = move_window(fs, fs->fatbase + (clst / (((UINT)512) / 4)));
   if (res != FR_OK) break;
   if (!0 || fs->fs_type != 4) {
    val = (val & 0x0FFFFFFF) | (ld_32(fs->win + clst * 4 % ((UINT)512)) & 0xF0000000);
   }
   st_32(fs->win + clst * 4 % ((UINT)512), val);
   fs->wflag = 1;
   break;
  }
 }
 return res;
}
# 1444 "ff.c"
static FRESULT remove_chain (
 FFOBJID* obj,
 DWORD clst,
 DWORD pclst
)
{
 FRESULT res = FR_OK;
 DWORD nxt;
 FATFS *fs = obj->fs;







 if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;


 if (pclst != 0 && (!0 || fs->fs_type != 4 || obj->stat != 2)) {
  res = put_fat(fs, pclst, 0xFFFFFFFF);
  if (res != FR_OK) return res;
 }


 do {
  nxt = get_fat(obj, clst);
  if (nxt == 0) break;
  if (nxt == 1) return FR_INT_ERR;
  if (nxt == 0xFFFFFFFF) return FR_DISK_ERR;
  if (!0 || fs->fs_type != 4) {
   res = put_fat(fs, clst, 0);
   if (res != FR_OK) return res;
  }
  if (fs->free_clst < fs->n_fatent - 2) {
   fs->free_clst++;
   fs->fsi_flag |= 1;
  }
# 1500 "ff.c"
  clst = nxt;
 } while (clst < fs->n_fatent);
# 1529 "ff.c"
 return FR_OK;
}
# 1539 "ff.c"
static DWORD create_chain (
 FFOBJID* obj,
 DWORD clst
)
{
 DWORD cs, ncl, scl;
 FRESULT res;
 FATFS *fs = obj->fs;


 if (clst == 0) {
  scl = fs->last_clst;
  if (scl == 0 || scl >= fs->n_fatent) scl = 1;
 }
 else {
  cs = get_fat(obj, clst);
  if (cs < 2) return 1;
  if (cs == 0xFFFFFFFF) return cs;
  if (cs < fs->n_fatent) return cs;
  scl = clst;
 }
 if (fs->free_clst == 0) return 0;
# 1588 "ff.c"
 {
  ncl = 0;
  if (scl == clst) {
   ncl = scl + 1;
   if (ncl >= fs->n_fatent) ncl = 2;
   cs = get_fat(obj, ncl);
   if (cs == 1 || cs == 0xFFFFFFFF) return cs;
   if (cs != 0) {
    cs = fs->last_clst;
    if (cs >= 2 && cs < fs->n_fatent) scl = cs;
    ncl = 0;
   }
  }
  if (ncl == 0) {
   ncl = scl;
   for (;;) {
    ncl++;
    if (ncl >= fs->n_fatent) {
     ncl = 2;
     if (ncl > scl) return 0;
    }
    cs = get_fat(obj, ncl);
    if (cs == 0) break;
    if (cs == 1 || cs == 0xFFFFFFFF) return cs;
    if (ncl == scl) return 0;
   }
  }
  res = put_fat(fs, ncl, 0xFFFFFFFF);
  if (res == FR_OK && clst != 0) {
   res = put_fat(fs, clst, ncl);
  }
 }

 if (res == FR_OK) {
  fs->last_clst = ncl;
  if (fs->free_clst > 0 && fs->free_clst <= fs->n_fatent - 2) {
   fs->free_clst--;
   fs->fsi_flag |= 1;
  }
 } else {
  ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;
 }

 return ncl;
}
# 1675 "ff.c"
static FRESULT dir_clear (
 FATFS *fs,
 DWORD clst
)
{
 LBA_t sect;
 UINT n, szb;
 BYTE *ibuf;


 if (sync_window(fs) != FR_OK) return FR_DISK_ERR;
 sect = clst2sect(fs, clst);
 fs->winsect = sect;
 memset(fs->win, 0, sizeof fs->win);
# 1699 "ff.c"
 {
  ibuf = fs->win; szb = 1;
  for (n = 0; n < fs->csize && disk_write(fs->pdrv, ibuf, sect + n, szb) == RES_OK; n += szb) ;
 }
 return (n == fs->csize) ? FR_OK : FR_DISK_ERR;
}
# 1714 "ff.c"
static FRESULT dir_sdi (
 DIR* dp,
 DWORD ofs
)
{
 DWORD csz, clst;
 FATFS *fs = dp->obj.fs;


 if (ofs >= (DWORD)((0 && fs->fs_type == 4) ? 0x10000000 : 0x200000) || ofs % 32) {
  return FR_INT_ERR;
 }
 dp->dptr = ofs;
 clst = dp->obj.sclust;
 if (clst == 0 && fs->fs_type >= 3) {
  clst = (DWORD)fs->dirbase;
  if (0) dp->obj.stat = 0;
 }

 if (clst == 0) {
  if (ofs / 32 >= fs->n_rootdir) return FR_INT_ERR;
  dp->sect = fs->dirbase;

 } else {
  csz = (DWORD)fs->csize * ((UINT)512);
  while (ofs >= csz) {
   clst = get_fat(&dp->obj, clst);
   if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
   if (clst < 2 || clst >= fs->n_fatent) return FR_INT_ERR;
   ofs -= csz;
  }
  dp->sect = clst2sect(fs, clst);
 }
 dp->clust = clst;
 if (dp->sect == 0) return FR_INT_ERR;
 dp->sect += ofs / ((UINT)512);
 dp->dir = fs->win + (ofs % ((UINT)512));

 return FR_OK;
}
# 1762 "ff.c"
static FRESULT dir_next (
 DIR* dp,
 int stretch
)
{
 DWORD ofs, clst;
 FATFS *fs = dp->obj.fs;


 ofs = dp->dptr + 32;
 if (ofs >= (DWORD)((0 && fs->fs_type == 4) ? 0x10000000 : 0x200000)) dp->sect = 0;
 if (dp->sect == 0) return FR_NO_FILE;

 if (ofs % ((UINT)512) == 0) {
  dp->sect++;

  if (dp->clust == 0) {
   if (ofs / 32 >= fs->n_rootdir) {
    dp->sect = 0; return FR_NO_FILE;
   }
  }
  else {
   if ((ofs / ((UINT)512) & (fs->csize - 1)) == 0) {
    clst = get_fat(&dp->obj, dp->clust);
    if (clst <= 1) return FR_INT_ERR;
    if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
    if (clst >= fs->n_fatent) {

     if (!stretch) {
      dp->sect = 0; return FR_NO_FILE;
     }
     clst = create_chain(&dp->obj, dp->clust);
     if (clst == 0) return FR_DENIED;
     if (clst == 1) return FR_INT_ERR;
     if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
     if (dir_clear(fs, clst) != FR_OK) return FR_DISK_ERR;
     if (0) dp->obj.stat |= 4;




    }
    dp->clust = clst;
    dp->sect = clst2sect(fs, clst);
   }
  }
 }
 dp->dptr = ofs;
 dp->dir = fs->win + ofs % ((UINT)512);

 return FR_OK;
}
# 1823 "ff.c"
static FRESULT dir_alloc (
 DIR* dp,
 UINT n_ent
)
{
 FRESULT res;
 UINT n;
 FATFS *fs = dp->obj.fs;


 res = dir_sdi(dp, 0);
 if (res == FR_OK) {
  n = 0;
  do {
   res = move_window(fs, dp->sect);
   if (res != FR_OK) break;



   if (dp->dir[0] == 0xE5 || dp->dir[0] == 0) {

    if (++n == n_ent) break;
   } else {
    n = 0;
   }
   res = dir_next(dp, 1);
  } while (res == FR_OK);
 }

 if (res == FR_NO_FILE) res = FR_DENIED;
 return res;
}
# 1865 "ff.c"
static DWORD ld_clust (
 FATFS* fs,
 const BYTE* dir
)
{
 DWORD cl;

 cl = ld_16(dir + 26);
 if (fs->fs_type == 3) {
  cl |= (DWORD)ld_16(dir + 20) << 16;
 }

 return cl;
}



static void st_clust (
 FATFS* fs,
 BYTE* dir,
 DWORD cl
)
{
 st_16(dir + 26, (WORD)cl);
 if (fs->fs_type == 3) {
  st_16(dir + 20, (WORD)(cl >> 16));
 }
}
# 2334 "ff.c"
static FRESULT dir_read (
 DIR* dp,
 int vol
)
{
 FRESULT res = FR_NO_FILE;
 FATFS *fs = dp->obj.fs;
 BYTE attr, et;




 while (dp->sect) {
  res = move_window(fs, dp->sect);
  if (res != FR_OK) break;
  et = dp->dir[0];
  if (et == 0) {
   res = FR_NO_FILE; break;
  }
# 2369 "ff.c"
  {
   dp->obj.attr = attr = dp->dir[11] & 0x3F;
# 2391 "ff.c"
   if (et != 0xE5 && et != '.' && attr != 0x0F && (int)((attr & ~0x20) == 0x08) == vol) {
    break;
   }

  }
  res = dir_next(dp, 0);
  if (res != FR_OK) break;
 }

 if (res != FR_OK) dp->sect = 0;
 return res;
}
# 2412 "ff.c"
static FRESULT dir_find (
 DIR* dp
)
{
 FRESULT res;
 FATFS *fs = dp->obj.fs;
 BYTE et;




 res = dir_sdi(dp, 0);
 if (res != FR_OK) return res;
# 2449 "ff.c"
 do {
  res = move_window(fs, dp->sect);
  if (res != FR_OK) break;
  et = dp->dir[0];
  if (et == 0) { res = FR_NO_FILE; break; }
# 2477 "ff.c"
  dp->obj.attr = dp->dir[11] & 0x3F;
  if (!(dp->dir[11] & 0x08) && !memcmp(dp->dir, dp->fn, 11)) break;

  res = dir_next(dp, 0);
 } while (res == FR_OK);

 return res;
}
# 2494 "ff.c"
static FRESULT dir_register (
 DIR* dp
)
{
 FRESULT res;
 FATFS *fs = dp->obj.fs;
# 2578 "ff.c"
 res = dir_alloc(dp, 1);




 if (res == FR_OK) {
  res = move_window(fs, dp->sect);
  if (res == FR_OK) {
   memset(dp->dir, 0, 32);
   memcpy(dp->dir + 0, dp->fn, 11);



   fs->wflag = 1;
  }
 }

 return res;
}
# 2607 "ff.c"
static FRESULT dir_remove (
 DIR* dp
)
{
 FRESULT res;
 FATFS *fs = dp->obj.fs;
# 2634 "ff.c"
 res = move_window(fs, dp->sect);
 if (res == FR_OK) {
  dp->dir[0] = 0xE5;
  fs->wflag = 1;
 }


 return res;
}
# 2653 "ff.c"
static void get_fileinfo (
 DIR* dp,
 FILINFO* fno
)
{
 UINT si, di;





 TCHAR c;



 fno->fname[0] = 0;
 if (dp->sect == 0) return;
# 2774 "ff.c"
 si = di = 0;
 while (si < 11) {
  c = (TCHAR)dp->dir[si++];
  if (c == ' ') continue;
  if (c == 0x05) c = 0xE5;
  if (si == 9) fno->fname[di++] = '.';
  fno->fname[di++] = c;
 }
 fno->fname[di] = 0;


 fno->fattrib = dp->dir[11] & 0x3F;
 fno->fsize = ld_32(dp->dir + 28);
 fno->ftime = ld_16(dp->dir + 22 + 0);
 fno->fdate = ld_16(dp->dir + 22 + 2);




}
# 2892 "ff.c"
static FRESULT create_name (
 DIR* dp,
 const TCHAR** path
)
{
# 3025 "ff.c"
 BYTE c, d;
 BYTE *sfn;
 UINT ni, si, i;
 const char *p;


 p = *path; sfn = dp->fn;
 memset(sfn, ' ', 11);
 si = i = 0; ni = 8;
# 3052 "ff.c"
 for (;;) {
  c = (BYTE)p[si++];
  if (c <= ' ') break;
  if (((c) == '/' || (c) == '\\')) {
   while (((p[si]) == '/' || (p[si]) == '\\')) si++;
   break;
  }
  if (c == '.' || i >= ni) {
   if (ni == 11 || c != '.') return FR_INVALID_NAME;
   i = 8; ni = 11;
   continue;
  }





  if (c >= 0x80) {
   c = ExCvt[c & 0x7F];
  }

  if (dbc_1st(c)) {
   d = (BYTE)p[si++];
   if (!dbc_2nd(d) || i >= ni - 1) return FR_INVALID_NAME;
   sfn[i++] = c;
   sfn[i++] = d;
  } else {
   if (strchr("*+,:;<=>[]|\"\?\x7F", (int)c)) return FR_INVALID_NAME;
   if (((c) >= 'a' && (c) <= 'z')) c -= 0x20;
   sfn[i++] = c;
  }
 }
 *path = &p[si];
 if (i == 0) return FR_INVALID_NAME;

 if (sfn[0] == 0xE5) sfn[0] = 0x05;
 sfn[11] = (c <= ' ' || p[si] <= ' ') ? 0x04 : 0;

 return FR_OK;

}
# 3101 "ff.c"
static FRESULT follow_path (
 DIR* dp,
 const TCHAR* path
)
{
 FRESULT res;
 BYTE ns;
 FATFS *fs = dp->obj.fs;
# 3117 "ff.c"
 {
  while (((*path) == '/' || (*path) == '\\')) path++;
  dp->obj.sclust = 0;
 }
# 3142 "ff.c"
 if ((UINT)*path < ' ') {
  dp->fn[11] = 0x80;
  res = dir_sdi(dp, 0);

 } else {
  for (;;) {
   res = create_name(dp, &path);
   if (res != FR_OK) break;
   ns = dp->fn[11];
# 3171 "ff.c"
   res = dir_find(dp);
   if (res != FR_OK) {
    if (res == FR_NO_FILE) {
     if (0 && (ns & 0x20)) {
      if (!(ns & 0x04)) continue;
      dp->fn[11] = 0x80;
      res = FR_OK;
     } else {
      if (!(ns & 0x04)) res = FR_NO_PATH;
     }
    }
    break;
   }
# 3194 "ff.c"
   if (ns & 0x04) break;

   if (!(dp->obj.attr & 0x10)) {
    res = FR_NO_PATH; break;
   }





   {
    dp->obj.sclust = ld_clust(fs, fs->win + dp->dptr % ((UINT)512));
   }
  }
 }

 return res;
}
# 3220 "ff.c"
static int get_ldnumber (
 const TCHAR** path
)
{
 const TCHAR *tp;
 const TCHAR *tt;
 TCHAR chr;
 int i;





 tt = tp = *path;
 if (!tp) return -1;
 do {
  chr = *tt++;
 } while (!((UINT)(chr) < (0 ? ' ' : '!')) && chr != ':');

 if (chr == ':') {
  i = 1;
  if (((*tp) >= '0' && (*tp) <= '9') && tp + 2 == tt) {
   i = (int)*tp - '0';
  }
# 3257 "ff.c"
  if (i >= 1) return -1;
  *path = tt;
  return i;
 }
# 3282 "ff.c"
 return 0;

}
# 3367 "ff.c"
static UINT check_fs (
 FATFS* fs,
 LBA_t sect
)
{
 WORD w, sign;
 BYTE b;


 fs->wflag = 0; fs->winsect = (LBA_t)0 - 1;
 if (move_window(fs, sect) != FR_OK) return 4;
 sign = ld_16(fs->win + 510);



 b = fs->win[0];
 if (b == 0xEB || b == 0xE9 || b == 0xE8) {
  if (sign == 0xAA55 && !memcmp(fs->win + 82, "FAT32   ", 8)) {
   return 0;
  }

  w = ld_16(fs->win + 11);
  b = fs->win[13];
  if ((w & (w - 1)) == 0 && w >= 512 && w <= 512
   && b != 0 && (b & (b - 1)) == 0
   && ld_16(fs->win + 14) != 0
   && (UINT)fs->win[16] - 1 <= 1
   && ld_16(fs->win + 17) != 0
   && (ld_16(fs->win + 19) >= 128 || ld_32(fs->win + 32) >= 0x10000)
   && ld_16(fs->win + 22) != 0) {
    return 0;
  }
 }
 return sign == 0xAA55 ? 2 : 3;
}





static UINT find_volume (
 FATFS* fs,
 UINT part
)
{
 UINT fmt, i;
 DWORD mbr_pt[4];


 fmt = check_fs(fs, 0);
 if (fmt != 2 && (fmt >= 3 || part == 0)) return fmt;
# 3443 "ff.c"
 if (0 && part > 4) return 3;
 for (i = 0; i < 4; i++) {
  mbr_pt[i] = ld_32(fs->win + 446 + i * 16 + 8);
 }
 i = part ? part - 1 : 0;
 do {
  fmt = mbr_pt[i] ? check_fs(fs, mbr_pt[i]) : 3;
 } while (part == 0 && fmt >= 2 && ++i < 4);
 return fmt;
}
# 3461 "ff.c"
static FRESULT mount_volume (
 const TCHAR** path,
 FATFS** rfs,
 BYTE mode
)
{
 int vol;
 FATFS *fs;
 DSTATUS stat;
 LBA_t bsect;
 UINT fmt;



 *rfs = 0;
 vol = get_ldnumber(path);
 if (vol < 0) return FR_INVALID_DRIVE;


 fs = FatFs[vol];
 if (!fs) return FR_NOT_ENABLED;



 *rfs = fs;

 mode &= (BYTE)~0x01;
 if (fs->fs_type != 0) {
  stat = disk_status(fs->pdrv);
  if (!(stat & 0x01)) {
   if (!0 && mode && (stat & 0x04)) {
    return FR_WRITE_PROTECTED;
   }
   return FR_OK;
  }
 }




 fs->fs_type = 0;
 stat = disk_initialize(fs->pdrv);
 if (stat & 0x01) {
  return FR_NOT_READY;
 }
 if (!0 && mode && (stat & 0x04)) {
  return FR_WRITE_PROTECTED;
 }






 fmt = find_volume(fs, 0);
 if (fmt == 4) return FR_DISK_ERR;
 if (fmt >= 2) return FR_NO_FILESYSTEM;
 bsect = fs->winsect;
# 3585 "ff.c"
 {
  DWORD tsect, sysect, fasize, nclst, szbfat;
  WORD nrsv;

  if (ld_16(fs->win + 11) != ((UINT)512)) return FR_NO_FILESYSTEM;

  fasize = ld_16(fs->win + 22);
  if (fasize == 0) fasize = ld_32(fs->win + 36);
  fs->fsize = fasize;

  fs->n_fats = fs->win[16];
  if (fs->n_fats != 1 && fs->n_fats != 2) return FR_NO_FILESYSTEM;
  fasize *= fs->n_fats;

  fs->csize = fs->win[13];
  if (fs->csize == 0 || (fs->csize & (fs->csize - 1))) return FR_NO_FILESYSTEM;

  fs->n_rootdir = ld_16(fs->win + 17);
  if (fs->n_rootdir % (((UINT)512) / 32)) return FR_NO_FILESYSTEM;

  tsect = ld_16(fs->win + 19);
  if (tsect == 0) tsect = ld_32(fs->win + 32);

  nrsv = ld_16(fs->win + 14);
  if (nrsv == 0) return FR_NO_FILESYSTEM;


  sysect = nrsv + fasize + fs->n_rootdir / (((UINT)512) / 32);
  if (tsect < sysect) return FR_NO_FILESYSTEM;
  nclst = (tsect - sysect) / fs->csize;
  if (nclst == 0) return FR_NO_FILESYSTEM;
  fmt = 0;
  if (nclst <= 0x0FFFFFF5) fmt = 3;
  if (nclst <= 0xFFF5) fmt = 2;
  if (nclst <= 0xFF5) fmt = 1;
  if (fmt == 0) return FR_NO_FILESYSTEM;


  fs->n_fatent = nclst + 2;
  fs->volbase = bsect;
  fs->fatbase = bsect + nrsv;
  fs->database = bsect + sysect;
  if (fmt == 3) {
   if (ld_16(fs->win + 42) != 0) return FR_NO_FILESYSTEM;
   if (fs->n_rootdir != 0) return FR_NO_FILESYSTEM;
   fs->dirbase = ld_32(fs->win + 44);
   szbfat = fs->n_fatent * 4;
  } else {
   if (fs->n_rootdir == 0) return FR_NO_FILESYSTEM;
   fs->dirbase = fs->fatbase + fasize;
   szbfat = (fmt == 2) ?
    fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
  }
  if (fs->fsize < (szbfat + (((UINT)512) - 1)) / ((UINT)512)) return FR_NO_FILESYSTEM;



  fs->last_clst = fs->free_clst = 0xFFFFFFFF;
  fs->fsi_flag = 0x80;
  if (fmt == 3
   && ld_16(fs->win + 48) == 1
   && move_window(fs, bsect + 1) == FR_OK)
  {
   fs->fsi_flag = 0;
   if ( ld_32(fs->win + 0) == 0x41615252
    && ld_32(fs->win + 484) == 0x61417272
    && ld_32(fs->win + 508) == 0xAA550000)
   {

    fs->free_clst = ld_32(fs->win + 488);


    fs->last_clst = ld_32(fs->win + 492);

   }
  }

 }

 fs->fs_type = (BYTE)fmt;
 fs->id = ++Fsid;
# 3685 "ff.c"
 return FR_OK;
}
# 3695 "ff.c"
static FRESULT validate (
 FFOBJID* obj,
 FATFS** rfs
)
{
 FRESULT res = FR_INVALID_OBJECT;


 if (obj && obj->fs && obj->fs->fs_type && obj->id == obj->fs->id) {
# 3715 "ff.c"
  if (!(disk_status(obj->fs->pdrv) & 0x01)) {
   res = FR_OK;
  }

 }
 *rfs = (res == FR_OK) ? obj->fs : 0;
 return res;
}
# 3739 "ff.c"
FRESULT f_mount (
 FATFS* fs,
 const TCHAR* path,
 BYTE opt
)
{
 FATFS *cfs;
 int vol;
 FRESULT res;
 const TCHAR *rp = path;



 vol = get_ldnumber(&rp);
 if (vol < 0) return FR_INVALID_DRIVE;

 cfs = FatFs[vol];
 if (cfs) {
  FatFs[vol] = 0;






  cfs->fs_type = 0;
 }

 if (fs) {
  fs->pdrv = (BYTE)(vol);
# 3782 "ff.c"
  fs->fs_type = 0;
  FatFs[vol] = fs;
 }

 if (opt == 0) return FR_OK;

 res = mount_volume(&path, &fs, 0);
 return res;
}
# 3799 "ff.c"
FRESULT f_open (
 FIL* fp,
 const TCHAR* path,
 BYTE mode
)
{
 FRESULT res;
 DIR dj;
 FATFS *fs;



 if (!fp) return FR_INVALID_OBJECT;


 mode &= 0 ? 0x01 : 0x01 | 0x02 | 0x08 | 0x04 | 0x10 | 0x30;
 res = mount_volume(&path, &fs, mode);

 if (res == FR_OK) {
  fp->obj.fs = fs;
  dj.obj.fs = fs;
                   ;
  res = follow_path(&dj, path);

  if (res == FR_OK) {
   if (dj.fn[11] & 0x80) {
    res = FR_INVALID_NAME;
   }





  }

  if (mode & (0x08 | 0x10 | 0x04)) {
   if (res != FR_OK) {
    if (res == FR_NO_FILE) {



     res = dir_register(&dj);

    }
    mode |= 0x08;
   }
   else {
    if (mode & 0x04) {
     res = FR_EXIST;
    } else {
     if (dj.obj.attr & (0x01 | 0x10)) res = FR_DENIED;
    }
   }
   if (res == FR_OK && (mode & 0x08)) {
    DWORD tm = ((DWORD)(2025 - 1980) << 25 | (DWORD)1 << 21 | (DWORD)1 << 16);
# 3872 "ff.c"
    {
     DWORD cl;

     st_32(dj.dir + 14, tm);
     st_32(dj.dir + 22, tm);
     cl = ld_clust(fs, dj.dir);
     dj.dir[11] = 0x20;
     st_clust(fs, dj.dir, 0);
     st_32(dj.dir + 28, 0);
     fs->wflag = 1;
     if (cl != 0) {
      LBA_t sc = fs->winsect;

      res = remove_chain(&dj.obj, cl, 0);
      if (res == FR_OK) {
       res = move_window(fs, sc);
       fs->last_clst = cl - 1;
      }
     }
    }
   }
  }
  else {
   if (res == FR_OK) {
    if (dj.obj.attr & 0x10) {
     res = FR_NO_FILE;
    } else {
     if ((mode & 0x02) && (dj.obj.attr & 0x01)) {
      res = FR_DENIED;
     }
    }
   }
  }
  if (res == FR_OK) {
   if (mode & 0x08) mode |= 0x40;
   fp->dir_sect = fs->winsect;
   fp->dir_ptr = dj.dir;




  }
# 3927 "ff.c"
  if (res == FR_OK) {





   {
    fp->obj.sclust = ld_clust(fs, dj.dir);
    fp->obj.objsize = ld_32(dj.dir + 28);
   }



   fp->obj.id = fs->id;
   fp->flag = mode;
   fp->err = 0;
   fp->sect = 0;
   fp->fptr = 0;




   if ((mode & 0x20) && fp->obj.objsize > 0) {
    DWORD bcs, clst;
    FSIZE_t ofs;

    fp->fptr = fp->obj.objsize;
    bcs = (DWORD)fs->csize * ((UINT)512);
    clst = fp->obj.sclust;
    for (ofs = fp->obj.objsize; res == FR_OK && ofs > bcs; ofs -= bcs) {
     clst = get_fat(&fp->obj, clst);
     if (clst <= 1) res = FR_INT_ERR;
     if (clst == 0xFFFFFFFF) res = FR_DISK_ERR;
    }
    fp->clust = clst;
    if (res == FR_OK && ofs % ((UINT)512)) {
     LBA_t sec = clst2sect(fs, clst);

     if (sec == 0) {
      res = FR_INT_ERR;
     } else {
      fp->sect = sec + (DWORD)(ofs / ((UINT)512));



     }
    }



   }

  }

                 ;
 }

 if (res != FR_OK) fp->obj.fs = 0;

 return res;
}
# 3996 "ff.c"
FRESULT f_read (
 FIL* fp,
 void* buff,
 UINT btr,
 UINT* br
)
{
 FRESULT res;
 FATFS *fs;
 LBA_t sect;
 FSIZE_t remain;
 UINT rcnt, cc, csect;
 BYTE *rbuff = (BYTE*)buff;


 *br = 0;
 res = validate(&fp->obj, &fs);
 if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) return res;
 if (!(fp->flag & 0x01)) return FR_DENIED;
 remain = fp->obj.objsize - fp->fptr;
 if (btr > remain) btr = (UINT)remain;

 for ( ; btr > 0; btr -= rcnt, *br += rcnt, rbuff += rcnt, fp->fptr += rcnt) {
  if (fp->fptr % ((UINT)512) == 0) {
   csect = (UINT)(fp->fptr / ((UINT)512) & (fs->csize - 1));
   if (csect == 0) {
    DWORD clst;

    if (fp->fptr == 0) {
     clst = fp->obj.sclust;
    } else {





     {
      clst = get_fat(&fp->obj, fp->clust);
     }
    }
    if (clst < 2) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
    if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
    fp->clust = clst;
   }
   sect = clst2sect(fs, fp->clust);
   if (sect == 0) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
   sect += csect;
   cc = btr / ((UINT)512);
   if (cc > 0) {
    if (csect + cc > fs->csize) {
     cc = fs->csize - csect;
    }
    if (disk_read(fs->pdrv, rbuff, sect, cc) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };


    if (fs->wflag && fs->winsect - sect < cc) {
     memcpy(rbuff + ((fs->winsect - sect) * ((UINT)512)), fs->win, ((UINT)512));
    }






    rcnt = ((UINT)512) * cc;
    continue;
   }
# 4074 "ff.c"
   fp->sect = sect;
  }
  rcnt = ((UINT)512) - (UINT)fp->fptr % ((UINT)512);
  if (rcnt > btr) rcnt = btr;

  if (move_window(fs, fp->sect) != FR_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
  memcpy(rbuff, fs->win + fp->fptr % ((UINT)512), rcnt);



 }

 return FR_OK;
}
# 4097 "ff.c"
FRESULT f_write (
 FIL* fp,
 const void* buff,
 UINT btw,
 UINT* bw
)
{
 FRESULT res;
 FATFS *fs;
 DWORD clst;
 LBA_t sect;
 UINT wcnt, cc, csect;
 const BYTE *wbuff = (const BYTE*)buff;


 *bw = 0;
 res = validate(&fp->obj, &fs);
 if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) return res;
 if (!(fp->flag & 0x02)) return FR_DENIED;


 if ((!0 || fs->fs_type != 4) && (DWORD)(fp->fptr + btw) < (DWORD)fp->fptr) {
  btw = (UINT)(0xFFFFFFFF - (DWORD)fp->fptr);
 }

 for ( ; btw > 0; btw -= wcnt, *bw += wcnt, wbuff += wcnt, fp->fptr += wcnt, fp->obj.objsize = (fp->fptr > fp->obj.objsize) ? fp->fptr : fp->obj.objsize) {
  if (fp->fptr % ((UINT)512) == 0) {
   csect = (UINT)(fp->fptr / ((UINT)512)) & (fs->csize - 1);
   if (csect == 0) {
    if (fp->fptr == 0) {
     clst = fp->obj.sclust;
     if (clst == 0) {
      clst = create_chain(&fp->obj, 0);
     }
    } else {





     {
      clst = create_chain(&fp->obj, fp->clust);
     }
    }
    if (clst == 0) break;
    if (clst == 1) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
    if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
    fp->clust = clst;
    if (fp->obj.sclust == 0) fp->obj.sclust = clst;
   }

   if (fs->winsect == fp->sect && sync_window(fs) != FR_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };






   sect = clst2sect(fs, fp->clust);
   if (sect == 0) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
   sect += csect;
   cc = btw / ((UINT)512);
   if (cc > 0) {
    if (csect + cc > fs->csize) {
     cc = fs->csize - csect;
    }
    if (disk_write(fs->pdrv, wbuff, sect, cc) != RES_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };


    if (fs->winsect - sect < cc) {
     memcpy(fs->win, wbuff + ((fs->winsect - sect) * ((UINT)512)), ((UINT)512));
     fs->wflag = 0;
    }







    wcnt = ((UINT)512) * cc;
    continue;
   }

   if (fp->fptr >= fp->obj.objsize) {
    if (sync_window(fs) != FR_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
    fs->winsect = sect;
   }







   fp->sect = sect;
  }
  wcnt = ((UINT)512) - (UINT)fp->fptr % ((UINT)512);
  if (wcnt > btw) wcnt = btw;

  if (move_window(fs, fp->sect) != FR_OK) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
  memcpy(fs->win + fp->fptr % ((UINT)512), wbuff, wcnt);
  fs->wflag = 1;




 }

 fp->flag |= 0x40;

 return FR_OK;
}
# 4218 "ff.c"
FRESULT f_sync (
 FIL* fp
)
{
 FRESULT res;
 FATFS *fs;


 res = validate(&fp->obj, &fs);
 if (res == FR_OK) {
  if (fp->flag & 0x40) {
# 4269 "ff.c"
   {
    res = move_window(fs, fp->dir_sect);
    if (res == FR_OK) {
     BYTE *dir = fp->dir_ptr;

     dir[11] |= 0x20;
     st_clust(fp->obj.fs, dir, fp->obj.sclust);
     st_32(dir + 28, (DWORD)fp->obj.objsize);
     st_32(dir + 22, ((DWORD)(2025 - 1980) << 25 | (DWORD)1 << 21 | (DWORD)1 << 16));
     st_16(dir + 18, 0);
     fs->wflag = 1;
     res = sync_fs(fs);
     fp->flag &= (BYTE)~0x40;
    }
   }
  }
 }

 return res;
}
# 4299 "ff.c"
FRESULT f_close (
 FIL* fp
)
{
 FRESULT res;
 FATFS *fs;


 res = f_sync(fp);
 if (res == FR_OK)

 {
  res = validate(&fp->obj, &fs);
  if (res == FR_OK) {




   fp->obj.fs = 0;




  }
 }
 return res;
}
# 4555 "ff.c"
FRESULT f_lseek (
 FIL* fp,
 FSIZE_t ofs
)
{
 FRESULT res;
 FATFS *fs;
 DWORD clst, bcs;
 LBA_t nsect;
 FSIZE_t ifptr;


 res = validate(&fp->obj, &fs);
 if (res == FR_OK) res = (FRESULT)fp->err;





 if (res != FR_OK) return res;
# 4633 "ff.c"
 {



  if (ofs > fp->obj.objsize && (0 || !(fp->flag & 0x02))) {
   ofs = fp->obj.objsize;
  }
  ifptr = fp->fptr;
  fp->fptr = nsect = 0;
  if (ofs > 0) {
   bcs = (DWORD)fs->csize * ((UINT)512);
   if (ifptr > 0 &&
    (ofs - 1) / bcs >= (ifptr - 1) / bcs) {
    fp->fptr = (ifptr - 1) & ~(FSIZE_t)(bcs - 1);
    ofs -= fp->fptr;
    clst = fp->clust;
   } else {
    clst = fp->obj.sclust;

    if (clst == 0) {
     clst = create_chain(&fp->obj, 0);
     if (clst == 1) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
     if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
     fp->obj.sclust = clst;
    }

    fp->clust = clst;
   }
   if (clst != 0) {
    while (ofs > bcs) {
     ofs -= bcs; fp->fptr += bcs;

     if (fp->flag & 0x02) {
      if (0 && fp->fptr > fp->obj.objsize) {
       fp->obj.objsize = fp->fptr;
       fp->flag |= 0x40;
      }
      clst = create_chain(&fp->obj, clst);
      if (clst == 0) {
       ofs = 0; break;
      }
     } else

     {
      clst = get_fat(&fp->obj, clst);
     }
     if (clst == 0xFFFFFFFF) { fp->err = (BYTE)(FR_DISK_ERR); return FR_DISK_ERR; };
     if (clst <= 1 || clst >= fs->n_fatent) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
     fp->clust = clst;
    }
    fp->fptr += ofs;
    if (ofs % ((UINT)512)) {
     nsect = clst2sect(fs, clst);
     if (nsect == 0) { fp->err = (BYTE)(FR_INT_ERR); return FR_INT_ERR; };
     nsect += (DWORD)(ofs / ((UINT)512));
    }
   }
  }
  if (!0 && fp->fptr > fp->obj.objsize) {
   fp->obj.objsize = fp->fptr;
   fp->flag |= 0x40;
  }
  if (fp->fptr % ((UINT)512) && nsect != fp->sect) {
# 4705 "ff.c"
   fp->sect = nsect;
  }
 }

 return res;
}
# 4719 "ff.c"
FRESULT f_opendir (
 DIR* dp,
 const TCHAR* path
)
{
 FRESULT res;
 FATFS *fs;



 if (!dp) return FR_INVALID_OBJECT;

 res = mount_volume(&path, &fs, 0);
 if (res == FR_OK) {
  dp->obj.fs = fs;
                   ;
  res = follow_path(dp, path);
  if (res == FR_OK) {
   if (!(dp->fn[11] & 0x80)) {
    if (dp->obj.attr & 0x10) {





     {
      dp->obj.sclust = ld_clust(fs, dp->dir);
     }
    } else {
     res = FR_NO_PATH;
    }
   }
   if (res == FR_OK) {
    dp->obj.id = fs->id;
    res = dir_sdi(dp, 0);
# 4764 "ff.c"
   }
  }
                 ;
  if (res == FR_NO_FILE) res = FR_NO_PATH;
 }
 if (res != FR_OK) dp->obj.fs = 0;

 return res;
}
# 4781 "ff.c"
FRESULT f_closedir (
 DIR *dp
)
{
 FRESULT res;
 FATFS *fs;


 res = validate(&dp->obj, &fs);
 if (res == FR_OK) {




  dp->obj.fs = 0;




 }
 return res;
}
# 4811 "ff.c"
FRESULT f_readdir (
 DIR* dp,
 FILINFO* fno
)
{
 FRESULT res;
 FATFS *fs;



 res = validate(&dp->obj, &fs);
 if (res == FR_OK) {
  if (!fno) {
   res = dir_sdi(dp, 0);
  } else {
                    ;
   fno->fname[0] = 0;
   res = dir_read(dp, 0);
   if (res == FR_NO_FILE) res = FR_OK;
   if (res == FR_OK) {
    get_fileinfo(dp, fno);
    res = dir_next(dp, 0);
    if (res == FR_NO_FILE) res = FR_OK;
   }
                  ;
  }
 }

 if (fno && res != FR_OK) fno->fname[0] = 0;
 return res;
}
# 4902 "ff.c"
FRESULT f_stat (
 const TCHAR* path,
 FILINFO* fno
)
{
 FRESULT res;
 DIR dj;




 res = mount_volume(&path, &dj.obj.fs, 0);

 if (res == FR_OK) {
                          ;
  res = follow_path(&dj, path);
  if (res == FR_OK) {
   if (dj.fn[11] & 0x80) {
    res = FR_INVALID_NAME;
   } else {
    if (fno) get_fileinfo(&dj, fno);
   }
  }
                 ;
 }

 if (fno && res != FR_OK) fno->fname[0] = 0;
 return res;
}
# 4939 "ff.c"
FRESULT f_getfree (
 const TCHAR* path,
 DWORD* nclst,
 FATFS** fatfs
)
{
 FRESULT res;
 FATFS *fs;
 DWORD nfree, clst, stat;
 LBA_t sect;
 UINT i;
 FFOBJID obj;



 res = mount_volume(&path, &fs, 0);

 if (res == FR_OK) {
  *fatfs = fs;

  if (fs->free_clst <= fs->n_fatent - 2) {
   *nclst = fs->free_clst;
  } else {

   nfree = 0;
   if (fs->fs_type == 1) {
    clst = 2; obj.fs = fs;
    do {
     stat = get_fat(&obj, clst);
     if (stat == 0xFFFFFFFF) {
      res = FR_DISK_ERR; break;
     }
     if (stat == 1) {
      res = FR_INT_ERR; break;
     }
     if (stat == 0) nfree++;
    } while (++clst < fs->n_fatent);
   } else {
# 4998 "ff.c"
    {
     clst = fs->n_fatent;
     sect = fs->fatbase;
     i = 0;
     do {
      if (i == 0) {
       res = move_window(fs, sect++);
       if (res != FR_OK) break;
      }
      if (fs->fs_type == 2) {
       if (ld_16(fs->win + i) == 0) nfree++;
       i += 2;
      } else {
       if ((ld_32(fs->win + i) & 0x0FFFFFFF) == 0) nfree++;
       i += 4;
      }
      i %= ((UINT)512);
     } while (--clst);
    }
   }
   if (res == FR_OK) {
    *nclst = nfree;
    fs->free_clst = nfree;
    fs->fsi_flag |= 1;
   }
  }
 }

 return res;
}
# 5036 "ff.c"
FRESULT f_truncate (
 FIL* fp
)
{
 FRESULT res;
 FATFS *fs;
 DWORD ncl;



 res = validate(&fp->obj, &fs);
 if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) return res;
 if (!(fp->flag & 0x02)) return FR_DENIED;

 if (fp->fptr < fp->obj.objsize) {
  if (fp->fptr == 0) {
   res = remove_chain(&fp->obj, fp->obj.sclust, 0);
   fp->obj.sclust = 0;
  } else {
   ncl = get_fat(&fp->obj, fp->clust);
   res = FR_OK;
   if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
   if (ncl == 1) res = FR_INT_ERR;
   if (res == FR_OK && ncl < fs->n_fatent) {
    res = remove_chain(&fp->obj, ncl, fp->clust);
   }
  }
  fp->obj.objsize = fp->fptr;
  fp->flag |= 0x40;
# 5074 "ff.c"
  if (res != FR_OK) { fp->err = (BYTE)(res); return res; };
 }

 return res;
}
# 5087 "ff.c"
FRESULT f_unlink (
 const TCHAR* path
)
{
 FRESULT res;
 FATFS *fs;
 DIR dj, sdj;
 DWORD dclst = 0;






 res = mount_volume(&path, &fs, 0x02);
 if (res == FR_OK) {
  dj.obj.fs = fs;
                   ;
  res = follow_path(&dj, path);
  if (res == FR_OK) {
   if (dj.fn[11] & (0x20 | 0x80)) {
    res = FR_INVALID_NAME;
   } else if (dj.obj.attr & 0x01) {
    res = FR_DENIED;




   }
  }
  if (res == FR_OK) {







   {
    dclst = ld_clust(fs, dj.dir);
   }
   if (dj.obj.attr & 0x10) {





    {
     sdj.obj.fs = fs;
     sdj.obj.sclust = dclst;






     res = dir_sdi(&sdj, 0);
     if (res == FR_OK) {
      res = dir_read(&sdj, 0);
      if (res == FR_OK) res = FR_DENIED;
      if (res == FR_NO_FILE) res = FR_OK;
     }
    }
   }
  }
  if (res == FR_OK) {
   res = dir_remove(&dj);
   if (res == FR_OK && dclst != 0) {



    res = remove_chain(&dj.obj, dclst, 0);

   }
   if (res == FR_OK) res = sync_fs(fs);
  }
                 ;
 }

 return res;
}
# 5176 "ff.c"
FRESULT f_mkdir (
 const TCHAR* path
)
{
 FRESULT res;
 FATFS *fs;
 DIR dj;
 FFOBJID sobj;
 DWORD dcl, pcl, tm;



 res = mount_volume(&path, &fs, 0x02);
 if (res == FR_OK) {
  dj.obj.fs = fs;
                   ;
  res = follow_path(&dj, path);
  if (res == FR_OK) {
   res = (dj.fn[11] & (0x20 | 0x80)) ? FR_INVALID_NAME : FR_EXIST;
  }
  if (res == FR_NO_FILE) {
   sobj.fs = fs;
   dcl = create_chain(&sobj, 0);
   res = FR_OK;
   if (dcl == 0) res = FR_DENIED;
   if (dcl == 1) res = FR_INT_ERR;
   if (dcl == 0xFFFFFFFF) res = FR_DISK_ERR;
   tm = ((DWORD)(2025 - 1980) << 25 | (DWORD)1 << 21 | (DWORD)1 << 16);
   if (res == FR_OK) {
    res = dir_clear(fs, dcl);
    if (res == FR_OK) {
     if (!0 || fs->fs_type != 4) {
      memset(fs->win + 0, ' ', 11);
      fs->win[0] = '.';
      fs->win[11] = 0x10;
      st_32(fs->win + 22, tm);
      st_clust(fs, fs->win, dcl);
      memcpy(fs->win + 32, fs->win, 32);
      fs->win[32 + 1] = '.'; pcl = dj.obj.sclust;
      st_clust(fs, fs->win + 32, pcl);
      fs->wflag = 1;
     }
     res = dir_register(&dj);
    }
   }
   if (res == FR_OK) {
# 5234 "ff.c"
    {
     st_32(dj.dir + 14, tm);
     st_32(dj.dir + 22, tm);
     st_clust(fs, dj.dir, dcl);
     dj.dir[11] = 0x10;
     fs->wflag = 1;
    }
    if (res == FR_OK) {
     res = sync_fs(fs);
    }
   } else {
    remove_chain(&sobj, dcl, 0);
   }
  }
                 ;
 }

 return res;
}
# 5261 "ff.c"
FRESULT f_rename (
 const TCHAR* path_old,
 const TCHAR* path_new
)
{
 FRESULT res;
 FATFS *fs;
 DIR djo, djn;
 BYTE buf[0 ? 32 * 2 : 32], *dir;



 get_ldnumber(&path_new);
 res = mount_volume(&path_old, &fs, 0x02);
 if (res == FR_OK) {
  djo.obj.fs = fs;
                   ;
  res = follow_path(&djo, path_old);
  if (res == FR_OK) {
   if (djo.fn[11] & (0x20 | 0x80)) {
    res = FR_INVALID_NAME;




   }
  }
  if (res == FR_OK) {
# 5326 "ff.c"
   {
    memcpy(buf, djo.dir, 32);
    memcpy(&djn, &djo, sizeof djn);
    res = follow_path(&djn, path_new);
    if (res == FR_OK) {
     res = (djn.obj.sclust == djo.obj.sclust && djn.dptr == djo.dptr) ? FR_NO_FILE : FR_EXIST;
    }
    if (res == FR_NO_FILE) {
     res = dir_register(&djn);
     if (res == FR_OK) {
      dir = djn.dir;
      memcpy(dir + 13, buf + 13, 32 - 13);
      dir[11] = buf[11];
      if (!(dir[11] & 0x10)) dir[11] |= 0x20;
      fs->wflag = 1;
      if ((dir[11] & 0x10) && djo.obj.sclust != djn.obj.sclust) {
       LBA_t sect = clst2sect(fs, ld_clust(fs, dir));

       if (sect == 0) {
        res = FR_INT_ERR;
       } else {

        res = move_window(fs, sect);
        dir = fs->win + 32 * 1;
        if (res == FR_OK && dir[1] == '.') {
         st_clust(fs, dir, djn.obj.sclust);
         fs->wflag = 1;
        }
       }
      }
     }
    }
   }
   if (res == FR_OK) {
    res = dir_remove(&djo);
    if (res == FR_OK) {
     res = sync_fs(fs);
    }
   }

  }
                 ;
 }

 return res;
}

/******************************* LICENCE **************************************
* Any code in this file may be redistributed or modified under the terms of
* the GNU General Public Licence as published by the Free Software 
* Foundation; version 2 of the licence.
****************************** END LICENCE ***********************************/

/******************************************************************************
* Author:
* Andrew Smith, http://littlesvr.ca/misc/contactandrew.php
*
* Contributors:
* 
******************************************************************************/

/********************************* PURPOSE ************************************
* bk.h
* This header file is the public interface to bkisofs.
******************************** END PURPOSE *********************************/

#ifndef bk_h
#define bk_h

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "bkError.h"

/* can be |ed */
#define FNTYPE_9660 1
#define FNTYPE_ROCKRIDGE 2
#define FNTYPE_JOLIET 4

/* many library functions rely on this being at least 256 */
#define NCHARS_FILE_ID_MAX_STORE 256

/* options for VolInfo.bootMediaType */
#define BOOT_MEDIA_NONE 0
#define BOOT_MEDIA_NO_EMULATION 1
#define BOOT_MEDIA_1_2_FLOPPY 2
#define BOOT_MEDIA_1_44_FLOPPY 3
#define BOOT_MEDIA_2_88_FLOPPY 4
#define BOOT_MEDIA_HARD_DISK 5

/* warning message string lengths in VolInfo */
#define BK_WARNING_MAX_LEN 512

#define BK_BASE_PTR(item) ((BkFileBase*)(item))
#define BK_DIR_PTR(item) ((BkDir*)(item))
#define BK_FILE_PTR(item) ((BkFile*)(item))

typedef struct BkFileBase
{
    char name[NCHARS_FILE_ID_MAX_STORE]; /* '\0' terminated */
    unsigned posixFileMode; /* file type and permissions */
    
    struct BkFileBase* next;
    
} BkFileBase;

/*******************************************************************************
* BkDir
* linked list node
* information about a directory and it's contents */
typedef struct BkDir
{
    BkFileBase base; /* intended to be accessed using a cast */
    
    BkFileBase* children; /* child directories, files, etc. */
    
} BkDir;

/*******************************************************************************
* BkFile
* linked list node
* information about a file, whether on the image or on the filesystem */
typedef struct BkFile
{
    BkFileBase base; /* intended to be accessed using a cast */
    
    unsigned size; /* in bytes, don't need off_t because it's stored 
                   * in a 32bit unsigned int on the iso */
    bool onImage;
    off_t position; /* if on image, in bytes */
    char* pathAndName; /* if on filesystem, full path + filename
                       * is to be freed by whenever the File is freed */
    
} BkFile;

/*******************************************************************************
* VolInfo
* information about a volume (one image)
* strings are '\0' terminated */
typedef struct
{
    /* private bk use  */
    unsigned filenameTypes;
    off_t pRootDrOffset; /* primary (9660 and maybe rockridge) */
    off_t sRootDrOffset; /* secondary (joliet), 0 if does not exist */
    off_t bootRecordSectorNumberOffset;
    int imageForReading;
    ino_t imageForReadingInode; /* to know which file was open for reading
                                * (filename is not reliable) */
    const BkFile* bootRecordOnImage; /* if visible, pointer to the file in the 
                                     *  directory tree */
    char warningMessage[BK_WARNING_MAX_LEN];
    bool rootRead; /* did i read the root record inside volume descriptor? */
    bool stopOperation; /* cancel current opertion */
    int imageForWriting;
    unsigned char* writeCache;
    unsigned char* writeCacheStatus;
    off_t wcOffset;
    off_t wcNumBytesUsed;
    void(*writeProgressFunction)(void);
    
    /* public use, read only */
    time_t creationTime;
    BkDir dirTree;
    unsigned char bootMediaType;
    unsigned bootRecordSize;       /* in bytes */
    bool bootRecordIsOnImage;      /* unused if visible (flag below) */
    unsigned bootRecordOffset;     /* if on image */
    char* bootRecordPathAndName;   /* if on filesystem */
    bool bootRecordIsVisible;      /* whether boot record is a visible file 
                                   *  on the image */
    
    /* public use, read/write */
    char volId[33];
    char publisher[129];
    char dataPreparer[129];
    unsigned posixFileDefaults;    /* for extracting */
    unsigned posixDirDefaults;     /* for extracting or creating on iso */
    bool(*warningCbk)(const char*);
    
} VolInfo;

/* public bkisofs functions */

/* adding */
int bk_add_boot_record(VolInfo* volInfo, const char* srcPathAndName, 
                       int bootMediaType);
int bk_add(VolInfo* volInfo, const char* srcPathAndName, 
           const char* destPathStr);
int bk_create_dir(VolInfo* volInfo, const char* destPathStr, 
                  const char* newDirName);

/* deleting */
void bk_delete_boot_record(VolInfo* volInfo);
int bk_delete(VolInfo* volInfo, const char* pathAndName);

/* extracting */
int bk_extract_boot_record(const VolInfo* volInfo, const char* destPathAndName, 
                           unsigned destFilePerms);
int bk_extract(VolInfo* volInfo, const char* srcPathAndName, 
               const char* destDir, bool keepPermissions, 
               void(*progressFunction)(void));

/* getters */
unsigned bk_estimate_iso_size(const VolInfo* volInfo, int filenameTypes);
time_t bk_get_creation_time(const VolInfo* volInfo);
int bk_get_dir_from_string(const VolInfo* volInfo, const char* pathStr, 
                           BkDir** dirFoundPtr);
const char* bk_get_publisher(const VolInfo* volInfo);
const char* bk_get_volume_name(const VolInfo* volInfo);
char* bk_get_error_string(int errorId);

/* setters */
void bk_cancel_operation(VolInfo* volInfo);
void bk_destroy_vol_info(VolInfo* volInfo);
int bk_init_vol_info(VolInfo* volInfo);
int bk_set_boot_file(VolInfo* volInfo, const char* srcPathAndName);
void bk_set_publisher(VolInfo* volInfo, const char* publisher);
void bk_set_vol_name(VolInfo* volInfo, const char* volName);

/* reading */
int bk_open_image(VolInfo* volInfo, const char* filename);
int bk_read_dir_tree(VolInfo* volInfo, int filenameType, bool readPosix);
int bk_read_vol_info(VolInfo* volInfo);

/* writing */
int bk_write_image(const char* newImagePathAndName, VolInfo* volInfo, 
                   time_t creationTime, int filenameTypes, 
                   void(*progressFunction)(void));

#endif

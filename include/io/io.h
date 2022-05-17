/*========================================
      FILE OPERATIONS HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_IO_H
#define TESCORE_IO_H

#include "../model/datamodel.h"     // Needed for Datasheet context
#include "../model/renderctx.h"     // Needed for Renderctx context
#include "../io/lib/aes.h"

#define MAXADDRLENGTH 509                   // Standard string char limit for ANSI Compatibility
#define DEFAULTFILEADDRESS "../demo.txt"    // Default demo.txt outside ../cmake-build-debug

// Scripts
void script_fileopsTesting();
void fetchData(FILE*, char* [], char* [], int);
void closeFile(FILE*);

// FILEOPS
void file_fetch_Datasheetctx(FILE*);
Renderctx render_init_ctx(DATASHEET sessionSheet);

// SAFEGUARD

// RENDER SYSTEM OPERATIONS

// DATASHEET OPERATIONS

// SORT MODULES
SUBSHEET rankerModule();
SUBSHEET masterlistModule();
#endif

/*
 * typedef struct Safeguardctx {
    struct      AES_ctx ctx;
    uint8_t*    encrypted_dataBuffer,
                decrypted_dataBuffer,
                passphrase,
                saltIV;
    uint8_t     bufferSize;
    uint64_t    padding;
    char*       plain_strSrcBuffer;
} Safeguardctx;
 * */
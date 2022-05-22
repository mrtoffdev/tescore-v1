/*========================================
      INPUT / OUTPUT
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_IO_H
#define TESCORE_IO_H

#include "../model/models.h"        // Needed for Datasheet context
#include "../model/renderctx.h"     // Needed for Renderctx context

#define MAXADDRLENGTH 509                   // Standard string char limit for ANSI Compatibility
#define MAXMASTERLEN 5000
#define DEFAULTFILEADDRESS "../demo.txt"    // Default demo.txt outside ../cmake-build-debug

// Scripts
void script_fileopsTesting();
void fetchData(FILE*, char* [], char* [], int);
void closeFile(FILE*);

void CRUD_TEST(Sheetctx in_sctxmaster);

// FETCH / INIT CONTEXTS
Sheetctx init_sheetdefctx();
Renderctx init_renderctx(Sheetctx in_sctx);

// ENTRY POINT
Sheetctx save_readsheetctx();
void save_writesheetctx(Sheetctx in_sctxmaster, const char* out_fileaddress);

// DECONSTRUCTOR
Sheetctx sheet_deconststr(char* in_strmasterlist, char* in_fileaddress);
void sheet_conststr(Sheetctx in_sctxmaster, char* out_strmasterlist);

// FILE OPERATIONS
void file_writemasterlist(const char* in_fileaddress, const char* in_strbuffer);
char* file_readmasterlist(FILE* in_file);

// UTILS
size_t util_fetchmastersize(Sheetctx in_sctx);

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
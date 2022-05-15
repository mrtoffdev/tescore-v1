/*========================================
      FILE OPERATIONS HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_IO_H
#define TESCORE_IO_H

// Models
#include "../model/datamodel.h"     // Needed for Datasheet context
#include "../model/renderctx.h"     // Needed for Renderctx context
#include "../io/lib/aes.h"

// Interface Parameters
#define MAXADDRLENGTH 509                   // Standard string char limit for ANSI Compatibility
#define DEFAULTFILEADDRESS "../demo.txt"    // Default demo.txt outside ../cmake-build-debug


/*========================================
                  Testing
  ========================================*/
void testing(const char* plain_strSrcBuffer);
void fetchData(FILE*, char* [], char* [], int);
void closeFile(FILE*);

/*========================================
 *              FILE OPS
  ========================================*/

// ENCRYPTION UTILS
void enc_writeBufferData(char* file_outDest, uint8_t* src_outBuffer, uint64_t size);
void fileops_decryptBuffer(struct AES_ctx ctx, uint8_t* encryptedBuffer, uint8_t* key, uint8_t* iv, size_t bufferSize, char* srcBuffer);

void sheet_encryptBuffer(FILE*);
void sheet_decryptBuffer(FILE*);
void file_fetch_Datasheetctx(FILE*);

// RENDER SYSTEM OPERATIONS
Renderctx render_init_ctx(DATASHEET sessionSheet);

// DATASHEET OPERATIONS
void fetch_gradeTable(DATASHEET Datactx, int distributionTable[11][2]);
void fetch_studentDistTable(DATASHEET Datactx);

void datasheet_init_demo();
void appendIndex(INDEX);
void delIndex(INDEX);

DATASHEET initSheetDemo();

/*========================================
                    SORT
  ========================================*/
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
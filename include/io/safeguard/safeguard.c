/*========================================
    FILE OPERATIONS
    Head Author: Christopher Abadillos Jr.
    Contributor: Jovic Francis Rayco
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io.h"
#include "../../render/view/render.h"
#include "../lib/aes.h"

#define DEBUGMODE 1
#define MAXSTRBUFFERSIZE 3344
#define INTERNALKEY "tescoreinternals"
#define INTERNALIV "XXXCCCVVVIIIOOOE"
#define BLKLEN 16

typedef enum {
    READ_STR = 0,
    READ_HEX = 1,
    READ_BLK = 2,
} OPERATION_CODE;

//#region =========== PRIVATE FUNCTIONS ===========

// FETCH
size_t fetch_rawbuffersize(const char* in_strbuffer);
size_t fetch_strbuffersize(const char* in_strbuffer);
size_t fetch_blockunits(const char* in_strbuffer, OPERATION_CODE mode);

// GENERATE
void sgt_aeshexbuffer(const char* in_strbuffer, uint8_t out_aeshexbuffer[][16]);
void hgt_aesstrbuffer(const uint8_t in_hexbuffer[][16], char* out_aesstrbuffer, size_t blocks);

void sgt_strhexbuffer(const char* in_strhexbuffer, uint8_t out_hexbuffer[][16]);
void hgt_strmaster(const uint8_t in_strhexbuffer[][16], char out_strbuffer[], size_t blocks);

void proc_encryptbuffer(const char* in_strmasterbuffer, char* out_encmasterbuffer);
void proc_decryptbuffer(const char* in_strmasterhexbuffer, char* out_decmasterstrbuffer);

//#region Legacy Protoypes
uint64_t    fetch_maxBufferAlloc(char* plain_srcStrBuffer);
size_t      enc_fetchBlockCount(char* plain_srcStrBuffer);
size_t      enc_fetchBlockCountfromHex(char* raw_srcStrBuffer);
char*       pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize);

void        enc_generateHexBufferFromStr(const char* plain_srcStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);
void        enc_generateStrBufferFromHex(const uint8_t* ctx_hexBufferContainer, char* ctx_DecodeStrBuffer, size_t ctx_hexBufferSize);
void        enc_translateStrHexBuffertoHex(const char* ctx_srcHexStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);

void        enc_AES_encryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferEncryptableBlocks[][16], uint8_t ctx_BufferEncryptedBlocks[][16], size_t ctx_inBufferBlocks);
void        enc_AES_decryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferDecryptableBlocks[][16], uint8_t ctx_BufferDecryptedBlocks[][16], size_t ctx_inBufferBlocks);

void        enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_dsmblStrBuffer[][16], size_t ctx_blocks);
void        enc_dsmblHexBuffer(const uint8_t* plain_srcHexBuffer, uint8_t ctx_BufferEncryptableBlock[][16], size_t ctx_blocks);

void        enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks);

void        enc_generateHexBlocks(uint8_t* ctx_hexBufferContainer, char plain_srcStrBuffer);

void        hex_removeBufferPadding(uint8_t* ctx_inRawBuffer, uint64_t size);
//#endregion

//#endregion

void script_fileopsTesting(){

    // ISOLATED ENCRYPTION TEST ===========================
//    char* teststring = "Jacob Joseph John 100\n" // Simulates what that string encoded masterlist should look like
//                       "Lorax of the Trees 90\n"
//                       "Jimmy proton 80\n";
//
//    size_t blocks = fetch_blockunits(teststring, READ_STR);
//    char* encryptedstring = calloc(1, (blocks * 16) * 2); // ENCRYPTED STRING SHOULD BE TWICE THE NUMBER OF DATA PER BLOCK BECAUSE HEX VALUES USE 2 CHARACTERS
//
//    proc_encryptbuffer(teststring, encryptedstring);
//
//    printf("Encrypted String:\n%s\n\n", encryptedstring);
//    ops_filewritemasterlist("../demo.dib", encryptedstring, WRITE);

    // ISOLATED DECRYPTION TEST ===========================
    char *encryptedteststring = file_readmasterlist("../demo.dib");
    size_t hexblocks = fetch_blockunits(encryptedteststring, READ_HEX);
    char* decryptedstring = calloc(1, hexblocks * 16);

    // decrypt
    proc_decryptbuffer(encryptedteststring, decryptedstring);

    system("pause");
}

// FETCH
size_t fetch_rawbuffersize(const char* in_strbuffer){
    return strlen(in_strbuffer) / 2;
}
size_t fetch_strbuffersize(const char* in_strbuffer){
    return strlen(in_strbuffer);
}
size_t fetch_blockunits(const char* in_strbuffer, OPERATION_CODE mode){
    size_t in_size = strlen(in_strbuffer);
    size_t blocks = 0;
    size_t nterms = in_size / 16;
    switch (mode) {
        case 0:
            blocks = (in_size + nterms) / 16;
            if ((in_size + nterms) % 16 != 0) blocks++;
            return blocks;
            break;

        case 1:
            return (strlen(in_strbuffer) / 2) / 16;
            break;

        default:
            break;
    }
    return blocks;
}

void proc_encryptbuffer(const char* in_strmasterbuffer, char* out_encmasterbuffer){
    DEBUGMODE == 1 ? printf("From: proc_encryptbuffer(): =========\n\n") : 0;

    // Fetch ctx
    size_t blocks = fetch_blockunits(in_strmasterbuffer, READ_STR);

    DEBUGMODE == 1 ? printf("Blocks Received: %d\n\n", blocks) : 0;

    // Call outside function for str to strhex_blocks conversion
    uint8_t teststringblockcontainer[blocks][16];
    sgt_strhexbuffer(in_strmasterbuffer, teststringblockcontainer);

    if (DEBUGMODE == 1){
        printf("From: proc_encryptbuffer(): =========\n\nString converted to hex:\n\n");
        // print blocks
        for (int i = 0; i < blocks; ++i) {
            for (int j = 0; j < 16; ++j) {
                printf("%.2x", teststringblockcontainer[i][j]);
            }
        }
    }

    uint8_t teststringencrypted[blocks][16];

    struct AES_ctx ctx;
    AES_init_ctx(&ctx, INTERNALKEY);
    AES_init_ctx_iv(&ctx, INTERNALKEY, INTERNALIV);

    // Call outside function to encrypt
    enc_AES_encryptBufferBlocks(ctx, teststringblockcontainer, teststringencrypted, blocks);

//    char *malloctest = calloc(1, (blocks * 16) * 2);
    hgt_aesstrbuffer(teststringencrypted, out_encmasterbuffer, blocks);
}
void proc_decryptbuffer(const char* in_strmasterhexbuffer, char* out_decmasterstrbuffer){
    DEBUGMODE == 1 ? printf("From: proc_decryptbuffer(): =========\n\n") : 0;
    // Fetch ctx
    size_t blocks = fetch_blockunits(in_strmasterhexbuffer, READ_HEX);

    DEBUGMODE == 1 ? printf("Blocks Received: %d\n\n", blocks) : 0;

    // Call outside function for strhex to hex_blocks conversion
    uint8_t in_strhexblocks[blocks][16];
    sgt_aeshexbuffer(in_strmasterhexbuffer, in_strhexblocks);

    if (DEBUGMODE == 1){
        printf("From: proc_decryptbuffer(): =========\n\n");
        printf("StringHex converted to Hex:\n\n");
        // print blocks
        for (int i = 0; i < blocks; ++i) {
            for (int j = 0; j < 16; ++j) {
                printf("%.2x", in_strhexblocks[i][j]);
            }
        }
    }

    DEBUGMODE == 1 ? printf("\n\n", blocks) : 0;
    uint8_t in_strhexdecrypted[blocks][16];
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, INTERNALKEY);
    AES_init_ctx_iv(&ctx, INTERNALKEY, INTERNALIV);
    enc_AES_decryptBufferBlocks(ctx, in_strhexblocks, in_strhexdecrypted, blocks);

//    // print blocks
//    for (int i = 0; i < blocks; ++i) {
//        for (int j = 0; j < 16; ++j) {
//            printf("%.2x", in_strhexdecrypted[i][j]);
//        }
//    }

    char *decryptedstring = calloc(1, blocks * 16);
    hgt_strmaster(in_strhexdecrypted, decryptedstring, blocks);
    strncpy(out_decmasterstrbuffer, decryptedstring, blocks * 16);
    printf("\n\nDecrypted String: \n\n%s\n", out_decmasterstrbuffer);
}

void sgt_aeshexbuffer(const char* in_strbuffer, uint8_t out_aeshexbuffer[][16]){
    DEBUGMODE == 1 ? printf("From: sgt_aeshexbuffer(): =========\n\n") : 0;
    DEBUGMODE == 1 ? printf("Received HexString: (char*)\n\n%s\n\n", in_strbuffer) : 0;

    // Fetch ctx
    size_t buffersize = strlen(in_strbuffer);
    size_t blocks = fetch_blockunits(in_strbuffer, READ_HEX);

    // Translate strhex to hex
    char hexctr[2];
    int ctr_buffer = 0;
    uint8_t hexbuffer[buffersize / 2];

    DEBUGMODE == 1 ? printf("Current hexbuffer digits: (uint8_t[])\n\n") : 0;
    for (int i = 0; i < buffersize; i+=2) {
        // Take 2 chars & store as hex digit
        hexctr[0] = in_strbuffer[i];
        hexctr[1] = in_strbuffer[i+1];
        hexbuffer[ctr_buffer] = (int)strtol(hexctr, NULL, 16);
        DEBUGMODE == 1 ? printf("%.2x", hexbuffer[ctr_buffer]) : 0;
        ctr_buffer++;
    }

    DEBUGMODE == 1 ? printf("\n\nCurrent hexbuffer digit in container: (uint8_t[][16])\n\n") : 0;
    // Reset counter and assemble blocks
    ctr_buffer = 0;
    for (int i = 0; i < blocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            out_aeshexbuffer[i][j] = hexbuffer[ctr_buffer];
            DEBUGMODE == 1 ? printf("%.2x", hexbuffer[ctr_buffer]) : 0;
            ctr_buffer++;
        }
    }
    DEBUGMODE == 1 ? printf("\n\n") : 0;
    // Note: aeshexbuffer has to be disassembled in blocks of 16 bytes for the decryption algorithm
}
void hgt_aesstrbuffer(const uint8_t in_hexbuffer[][16], char* out_aesstrbuffer, size_t blocks){
    DEBUGMODE == 1 ? printf("From: hgt_aesstrbuffer(): =========\n\nCurrent hexbuffer:\n") : 0;
    // Fetch ctx
    char hexbuffer[3];

    for (int i = 0; i < blocks; ++i) {
        for (int j = 0; j < 16; j++) {
            snprintf(hexbuffer, 3,"%.2x", in_hexbuffer[i][j]);
            strncat(out_aesstrbuffer, hexbuffer, 3);
            DEBUGMODE == 1 ? printf("%s", hexbuffer) : 0;
        }
    }

    DEBUGMODE == 1 ? printf("\n\n", hexbuffer) : 0;
    // Note: no need to disassemble into blocks of 16 bytes since this the strbuffer is to be written through filestream
}

void sgt_strhexbuffer(const char* in_strhexbuffer, uint8_t out_hexbuffer[][16]){
    DEBUGMODE == 1 ? printf("From: sgt_strhexbuffer(): =========\n\n") : 0;

    // Fetch ctx
    size_t blocks = fetch_blockunits(in_strhexbuffer, READ_STR);
    size_t bufferlen = strlen(in_strhexbuffer);

    char ctr_block[16];
    int ctr_str = 0;
    size_t lastindex = 0;
    for (int i = 0; i < blocks; ++i) {
        DEBUGMODE == 1 ? printf("Current Block: %d\n\n", i+1) : 0;

        // Reset blockContainer & auto pad everything with ':'
        for (int j = 0; j < 16; ++j) {
            if (j == 15) {
                // Auto append null terminator
                ctr_block[j] = '\0';
            } else {
                ctr_block[j] = ':';
            }
        }

        // Disassemble strbuffer to hex
        for (uint64_t j = 0; j < 15; ++j) {
            if (lastindex < bufferlen){
                ctr_block[j] = in_strhexbuffer[lastindex];

                DEBUGMODE == 1 ? printf("%c ", ctr_block[j]) : 0;
                lastindex++;
            } else {
                ctr_block[j] = ':';
            }
        }

        // Assemble into output hexbuffer
        for (int j = 0; j < 16; ++j) {
            out_hexbuffer[i][j] = ctr_block[j];
        }

        DEBUGMODE == 1 ? printf("\nCurrent Block String: %s\n\n", out_hexbuffer[i]) : 0;
    }

}
void hgt_strmaster(const uint8_t in_strhexbuffer[][16], char out_strbuffer[], size_t blocks){

    // Disassemble blocks into string of 16 bytes
    char blockstring[16];

    for (int i = 0; i < blocks; ++i) {
        // Reset blockstring
        for (int j = 0; j < 16; ++j) {
            blockstring[j] = ' ';
        }

        // Assemble string for block i
        for (int j = 0; j < 16; ++j) {
            if ((char)in_strhexbuffer[i][j] != ':'){
                blockstring[j] = (char)in_strhexbuffer[i][j];
            }
        }

        // Append string to out
        strncat(out_strbuffer, blockstring, 16);
    }
}

void enc_AES_encryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferEncryptableBlocks[][16], uint8_t ctx_BufferEncryptedBlocks[][16], size_t ctx_inBufferBlocks){
    DEBUGMODE == 1 ? printf("\n\nFrom: enc_AES_encryptBufferBlocks(): =========\n\nEncrypted hex:\n\n") : 0;
    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        uint8_t ctx_BufferBlockEncryptable[16];
        // Create a encryptable buffer block
        for (int j = 0; j < 16; ++j) {
            ctx_BufferBlockEncryptable[j] = ctx_BufferEncryptableBlocks[i][j];
        }

        // Emcryption Function in AES128.h
        AES_CBC_encrypt_buffer(&ctx, ctx_BufferBlockEncryptable, 16);

        // Insert encrypted buffer into container
//        DEBUGMODE == 1 ? printf("Buffer Block: ") : 0;
        for (int j = 0; j < 16; ++j) {
            ctx_BufferEncryptedBlocks[i][j] = ctx_BufferBlockEncryptable[j];
            DEBUGMODE == 1 ? printf("%.2x", ctx_BufferEncryptedBlocks[i][j]) : 0;
        }
    }
    DEBUGMODE == 1 ? printf("\n\n") : 0;
}
void enc_AES_decryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferDecryptableBlocks[][16], uint8_t ctx_BufferDecryptedBlocks[][16], size_t ctx_inBufferBlocks){

    DEBUGMODE == 1 ? printf("\nDecryption:\n\n") : 0 ;
    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        // Create a temporary holder of the decryptable block
        uint8_t ctx_BufferBlockDecryptable[16];

        // Create a decryptable buffer block
        DEBUGMODE == 1 ? printf("Current Decryptable Block:\n") : 0 ;
        for (int j = 0; j < 16; ++j) {
            ctx_BufferBlockDecryptable[j] = ctx_BufferDecryptableBlocks[i][j];
            DEBUGMODE == 1 ? printf("%.2x", ctx_BufferBlockDecryptable[j]) : 0 ;
        }
        DEBUGMODE == 1 ? printf("\n") : 0 ;

        AES_CBC_decrypt_buffer(&ctx, ctx_BufferBlockDecryptable, 16);

        DEBUGMODE == 1 ? printf("Post Decrypted Block:\n") : 0 ;

        // Insert decrypted buffer into container
//        DEBUGMODE == 1 ? printf("Buffer Block: ") : 0;
        for (int j = 0; j < 16; ++j) {
            ctx_BufferDecryptedBlocks[i][j] = ctx_BufferBlockDecryptable[j];
            DEBUGMODE == 1 ? printf("%.2x", ctx_BufferBlockDecryptable[j]) : 0;
        }
        DEBUGMODE == 1 ? printf("\n") : 0;
    }
}

// DEBUG
void dbg_printbuffer(){

}

//#region Legacy Functions
void legacy_fileopsTesting(){
//    struct AES_ctx ctx;
//
//    //#region ENCRYPTION DETAILS
//    uint8_t key[] = INTERNALKEY;
//    uint8_t iv[]  = INTERNALIV;
//    //#endregion
//
//    //#region TESTING DATA
//    char decoded[] =                  "A university that is imbued with"
//                                      " a dynamic, relevant, and arespo"
//                                      "nsive research culture dedicated"
//                                      " towards the generation and diss"
//                                      "emination of information and tec"
//                                      "hnology that address, institutio"
//                                      "nal, regional, and national deve"
//                                      "lopment needs.";
//
//    char* demo_rawHexBufferString =   "ce1171bc29f807baaeb27b6386fe8b8e"
//                                      "5de9fffcc2cb84303dd2544251eb7e5a"
//                                      "785b44020c06f07d4967bd81b0f93f99"
//                                      "19c2de0e2d9e5f05b6552b862488a60c"
//                                      "1614818924295630d25bdcd06cf44fc6"
//                                      "0d61e032af0549d5f193200fd381edf7"
//                                      "5a541387f8ca3c173e61b3e39636e8a5"
//                                      "c70cf0194615fff988e2a23b733cd9e7"
//                                      "45e2d95d348ebeb494b541c84d32aff7"
//                                      "51fbb5fe3bbafa5b9eaa1ba2c531d8e6"
//                                      "c98ed41481c0373d034285b7e8ed46d4"
//                                      "60b28f84fa2123253437bdc57ea5cbb9"
//                                      "272f64f67d82032147b0adb0f4579f1c"
//                                      "78819af215ba534ab935e5faa41b99bc"
//                                      "c793e815a34db608c3adaa9e4f09f170"
//                                      "aef9e2ea1288635caf28f1076cf65732";
//
//    char* demo_DecrawHexBufferString= "4120756e697665727369747920746800"
//                                      "617420697320696d6275656420776900"
//                                      "746820612064796e616d69632c207200"
//                                      "656c6576616e742c20616e6420617200"
//                                      "6573706f6e7369766520726573656100"
//                                      "7263682063756c747572652064656400"
//                                      "69636174656420746f77617264732000"
//                                      "7468652067656e65726174696f6e2000"
//                                      "616e642064697373656d696e61746900"
//                                      "6f6e206f6620696e666f726d61746900"
//                                      "6f6e20616e6420746563686e6f6c6f00"
//                                      "67792074686174206164647265737300"
//                                      "2c20696e737469747574696f6e616c00"
//                                      "2c20726567696f6e616c2c20616e6400"
//                                      "206e6174696f6e616c20646576656c00"
//                                      "6f706d656e74206e656564732e303000";
//    //#endregion
//
//    //#region SUB DECRYPTION TEST =====================================================================
//
//    // Fetch strBuffer details
//    size_t  demo_strSize = strlen(demo_rawHexBufferString);
//    size_t  demo_blockSize = enc_fetchBlockCountfromHex(demo_rawHexBufferString);
//    printf("Raw Buffer Size: %d\n", demo_strSize);
//    printf("Actual Buffer Size: %d\n", demo_strSize/2);
//    printf("Block Size: %d\n", demo_blockSize);
//
//    // Translate whole buffer into hex
//    uint8_t demo_translatedHexValues[demo_strSize];
//    enc_translateStrHexBuffertoHex(demo_rawHexBufferString, demo_translatedHexValues, demo_strSize);
//
//    printf("StrBuffer to Buffer: \n\n");
//    for (int i = 0; i < demo_blockSize * 16; ++i) {
//        printf("%.2x", demo_translatedHexValues[i]);
//    }
//
//    printf("\n\nSize of translated buffer: %d\n\n", sizeof demo_translatedHexValues);
//
//    // Divide into blocks and insert hex
//    uint8_t demo_BufferDecryptableBlock[demo_blockSize][16];
//    enc_dsmblHexBuffer(demo_translatedHexValues, demo_BufferDecryptableBlock, demo_blockSize); //TODO FIX
//
//    printf("Disassembled Buffer (Decryptable Buffer): \n");
//    for (int i = 0; i < demo_blockSize; ++i) {
//        for (int j = 0; j < 16; ++j) {
//            printf("%.2x", demo_BufferDecryptableBlock[i][j]);
//        }
//        printf("\n");
//    }
//
//    // Insert into custom decrypt function
//    uint8_t demo_BufferDecryptedBlocks[demo_blockSize][16];
//
//    AES_init_ctx_iv(&ctx, key, iv); //TODO VERY IMPORTANT TO INIT IV EVERY PROCESS
//    enc_AES_decryptBufferBlocks(ctx, demo_BufferDecryptableBlock, demo_BufferDecryptedBlocks, demo_blockSize);
//
//    #endregion
//
//    #region MAIN ENCRYPTION TEST ====================================================================
//
//    // Encryption Requirements
//    size_t ctx_inBufferBlocks = enc_fetchBlockCount(decoded);
//    uint64_t ctx_inBufferAlloc = fetch_maxBufferAlloc(decoded);
//
//    char        ctx_dsmblStrBuffer[ctx_inBufferBlocks][16];
//    uint8_t     ctx_dsmblHexBuffer[ctx_inBufferBlocks][16];
//
//    // Create disassembled char*
//    enc_dsmblStrBuffer(decoded, ctx_dsmblStrBuffer, ctx_inBufferBlocks);
//    enc_generateHexBufferEncryptable(ctx_dsmblStrBuffer, ctx_dsmblHexBuffer, ctx_inBufferBlocks);
//
//    printf("String Generated: \n\n");
//    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
//        printf("%s", ctx_dsmblStrBuffer[i]);
//    }
//
//    if (DEBUGMODE == 1){
//        printf("\n\nUnencrypted Buffer: \n\n");
//        for (int i = 0; i < ctx_inBufferBlocks; ++i) {
//            printf("Buffer Block: ");
//            for (int j = 0; j < 16; ++j) {
//                printf("%.2x", ctx_dsmblHexBuffer[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n\nBuffer Size: %d\n", ctx_inBufferAlloc);
//        printf("Blocks Used: %d\n\n", ctx_inBufferBlocks);
//    }
//
//    // ENCRYPTION PROCESS =============================================================================
//
//    uint8_t ctx_BufferEncryptableBlocks[ctx_inBufferBlocks][16];
//    uint8_t ctx_BufferEncryptedBlocks[ctx_inBufferBlocks][16];
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    enc_AES_encryptBufferBlocks(ctx, ctx_dsmblHexBuffer, ctx_BufferEncryptedBlocks, ctx_inBufferBlocks);
//
//    // DECRYPTION PROCESS =============================================================================
//
//    uint8_t ctx_BufferDecryptableBlocks[ctx_inBufferBlocks][16];
//    uint8_t ctx_BufferDecryptedBlocks[ctx_inBufferBlocks][16];
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    enc_AES_decryptBufferBlocks(ctx, ctx_BufferEncryptedBlocks, ctx_BufferDecryptedBlocks, ctx_inBufferBlocks);
//
// ================================================================================================
//
//    char* finalString = malloc(1000);
//    char placeholderstr[16];
//    enc_generateStrBufferFromHex(ctx_BufferDecryptableBlocks, finalString, ctx_inBufferAlloc);
//
//    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
//        strncat(finalString, (char*) ctx_BufferDecryptableBlocks, 16);
//    }
//
//    #endregion
//
}

uint64_t    fetch_maxBufferAlloc(char* plain_srcStrBuffer){
    //TODO FUNCT UPDATE
    uint64_t bufferSize = 0;
    uint64_t strBufferSize = strlen(plain_srcStrBuffer);
    while (strBufferSize > bufferSize){
        bufferSize += 16;
    }
    return bufferSize;
}
size_t      enc_fetchBlockCount(char* plain_srcStrBuffer){
    //TODO FUNCT PASS
    size_t bufferSize = strlen(plain_srcStrBuffer); // Raw Buffer
    size_t processedBuffer = bufferSize/16 + bufferSize; // Considers the null termination char for every block end
    size_t blocksProcessed = processedBuffer / 16; // Raw Buffer w/ null-term consideration / 16 bytes per block

    if (strlen(plain_srcStrBuffer) % 16 != 0) blocksProcessed++; // Extra block if raw buffer has excess bytes
    return blocksProcessed;
}
size_t      enc_fetchBlockCountfromHex(char* raw_srcStrBuffer){
    return (strlen(raw_srcStrBuffer) / 16) / 2;
}
char*       pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize){
    char* ctx_finalStrBuffer = malloc(ctx_targetBufferSize);

    size_t srclength = strlen(plain_strSrcBuffer); //10
    size_t padding = ctx_targetBufferSize - srclength; //6

    strcpy(ctx_finalStrBuffer, plain_strSrcBuffer);
    uint64_t indexPosition = srclength;
    while (padding > 0){
        if (padding == 1){
            strncat(&ctx_finalStrBuffer[indexPosition], "\0", 1);
        }
        strncat(&ctx_finalStrBuffer[indexPosition], "0", 1);
        indexPosition++;
        padding--;
    }

    return ctx_finalStrBuffer;
}

// ENCRYPTION
void enc_generateHexBufferFromStr(const char* plain_srcStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize){

    // Initializes ctx_hexBufferContainer with hex translation of plain_srcStrBuffer
    for (int i = 0; i < ctx_strBufferSize; i++) {
        ctx_hexBufferContainer[i] = plain_srcStrBuffer[i];
    }
}
void enc_generateStrBufferFromHex(const uint8_t* ctx_hexBufferContainer, char* ctx_DecodeStrBuffer, size_t ctx_hexBufferSize){

    // Initializes ctx_DecodeStrBuffer with char translation of ctx_hexBufferContainer
    for (int i = 0; i < ctx_hexBufferSize; i++) {
        ctx_DecodeStrBuffer[i] = (char)ctx_hexBufferContainer[i];
    }
}

// Generate Utils
void enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks){
    // TODO PASS BUT HEX BUFFER SHOULD BE PRINTED ONE BY ONE
    for (int i = 0; i < ctx_blocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            ctx_dsmblHexBuffer[i][j] = ctx_dsmblStrBuffer[i][j];
        }
    }
}

// DECRYPTION
void enc_translateStrHexBuffertoHex(const char* ctx_srcHexStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize){
    // Initializes ctx_hexBufferContainer with hex translation of plain_srcStrBuffer
    char temp_hexDigitContainer[2];
    int counter = 0;
    for (int i = 0; i < ctx_strBufferSize; i+=2) {
        temp_hexDigitContainer[0] = ctx_srcHexStrBuffer[i];
        temp_hexDigitContainer[1] = ctx_srcHexStrBuffer[i+1];

        ctx_hexBufferContainer[counter] = (int)strtol(temp_hexDigitContainer, NULL, 16);
        counter++;
    }
}
void enc_dsmblHexBuffer(const uint8_t* plain_srcHexBuffer, uint8_t ctx_BufferEncryptableBlock[][16], size_t ctx_blocks){
    const short debugMode = 0;
    debugMode == 1 ? ("Block Size: %d\n", ctx_blocks) : 0;
    uint64_t lastIndex = 0; // Keep progress in internal for loop

    for (int i = 0; i < ctx_blocks; ++i) {
        // For every block
        debugMode == 1 ? printf("Current Block: %d\n", i+1) : 0;

        // Reset blockContainer
        for (int j = 0; j < 16; ++j) {
            ctx_BufferEncryptableBlock[i][j] = plain_srcHexBuffer[lastIndex];
            lastIndex++;
        }

    }
}

// Disassembly Utils
void enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_StringEncryptableBlocks[][16], size_t ctx_blocks){
    const short debugMode = 0;
    if (debugMode == 1) printf("Block Size: %d\n", ctx_blocks);
    uint64_t lastIndex = 0; // Keep progress in internal for loop
    size_t totalBufferSize = ctx_blocks * 16;
    size_t strBufferLength = strlen(plain_srcStrBuffer);
    char blockStrContainer[16];

    for (int i = 0; i < ctx_blocks; ++i) {
        // For every block
        if (debugMode == 1) printf("Current Block: %d\n", i+1);

        // Reset blockContainer
        for (int j = 0; j < 16; ++j) {
            blockStrContainer[j] = '0';
            if (j == 15) {
                // Auto append null term
                blockStrContainer[j] = '\0';
            }
        }

        for (uint64_t j = 0; j < 15; ++j) {
            if (lastIndex < strBufferLength){
                blockStrContainer[j] = plain_srcStrBuffer[lastIndex];

                if (debugMode == 1) printf("Current Char: %c\n", plain_srcStrBuffer[lastIndex]);
                lastIndex++;
            } else {
                blockStrContainer[j] = '0';
            }
        }

        for (int j = 0; j < 16; ++j) {
            ctx_StringEncryptableBlocks[i][j] = blockStrContainer[j];
        }
        if (debugMode == 1) printf("Current Block String: %s\n", ctx_StringEncryptableBlocks[i]);

    }
}
void hex_removeBufferPadding(uint8_t* ctx_inRawBuffer, uint64_t size){
    uint64_t index = size-1;
    while (ctx_inRawBuffer[index] == '0'){
        ctx_inRawBuffer[index] = ' ';
        index--;
    }
    ctx_inRawBuffer[index+1] = '\0';
}


void encryptMasterlist(char* ctx_masterListStrBuffer, char* ctx_EncryptedMasterListStr){


    struct AES_ctx ctx;
    uint8_t key[] = INTERNALKEY;
    uint8_t iv[]  = INTERNALIV;

    // Encryption Requirements
    size_t ctx_inBufferBlocks = enc_fetchBlockCount(ctx_masterListStrBuffer);
    uint64_t ctx_inBufferAlloc = fetch_maxBufferAlloc(ctx_masterListStrBuffer);

    char        ctx_dsmblStrBuffer[ctx_inBufferBlocks][16];
    uint8_t     ctx_dsmblHexBuffer[ctx_inBufferBlocks][16];

    // Create disassembled char*
    enc_dsmblStrBuffer(ctx_masterListStrBuffer, ctx_dsmblStrBuffer, ctx_inBufferBlocks);
    enc_generateHexBufferEncryptable(ctx_dsmblStrBuffer, ctx_dsmblHexBuffer, ctx_inBufferBlocks);

    printf("String Generated: \n\n");
    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        printf("%s", ctx_dsmblStrBuffer[i]);
    }

    if (DEBUGMODE == 1){
        printf("\n\nUnencrypted Buffer: \n\n");
        for (int i = 0; i < ctx_inBufferBlocks; ++i) {
            printf("Buffer Block: ");
            for (int j = 0; j < 16; ++j) {
                printf("%.2x", ctx_dsmblHexBuffer[i][j]);
            }
            printf("\n");
        }
        printf("\n\nBuffer Size: %d\n", ctx_inBufferAlloc);
        printf("Blocks Used: %d\n\n", ctx_inBufferBlocks);
    }

    uint8_t ctx_BufferEncryptableBlocks[ctx_inBufferBlocks][16];
    uint8_t ctx_BufferEncryptedBlocks[ctx_inBufferBlocks][16];

    AES_init_ctx_iv(&ctx, key, iv);
    enc_AES_encryptBufferBlocks(ctx, ctx_dsmblHexBuffer, ctx_BufferEncryptedBlocks, ctx_inBufferBlocks);


}
void decryptMasterList(char* ctx_masterListHexBuffer, char* ctx_decryptedMasterListStr){

    struct AES_ctx ctx;
    uint8_t key[] = INTERNALKEY;
    uint8_t iv[]  = INTERNALIV;

    // Fetch strBuffer details
    size_t  demo_strSize = strlen(ctx_masterListHexBuffer);
    size_t  demo_blockSize = enc_fetchBlockCountfromHex(ctx_masterListHexBuffer);
    printf("Raw Buffer Size: %d\n", demo_strSize);
    printf("Actual Buffer Size: %d\n", demo_strSize/2);
    printf("Block Size: %d\n", demo_blockSize);

    // Translate whole buffer into hex
    uint8_t demo_translatedHexValues[demo_strSize];
    enc_translateStrHexBuffertoHex(ctx_masterListHexBuffer, demo_translatedHexValues, demo_strSize);

    printf("StrBuffer to Buffer: \n\n");
    for (int i = 0; i < demo_blockSize * 16; ++i) {
        printf("%.2x", demo_translatedHexValues[i]);
    }

    printf("\n\nSize of translated buffer: %d\n\n", sizeof demo_translatedHexValues);

    // Divide into blocks and insert hex
    uint8_t demo_BufferDecryptableBlock[demo_blockSize][16];
    enc_dsmblHexBuffer(demo_translatedHexValues, demo_BufferDecryptableBlock, demo_blockSize); //TODO FIX

    printf("Disassembled Buffer (Decryptable Buffer): \n");
    for (int i = 0; i < demo_blockSize; ++i) {
        for (int j = 0; j < 16; ++j) {
            printf("%.2x", demo_BufferDecryptableBlock[i][j]);
        }
        printf("\n");
    }

    // Insert into custom decrypt function
    uint8_t demo_BufferDecryptedBlocks[demo_blockSize][16];

    AES_init_ctx_iv(&ctx, key, iv); //TODO VERY IMPORTANT TO INIT IV EVERY PROCESS
    enc_AES_decryptBufferBlocks(ctx, demo_BufferDecryptableBlock, demo_BufferDecryptedBlocks, demo_blockSize);

}

void fileops_encryptBuffer(struct AES_ctx ctx){}
void fileops_decryptBuffer(struct AES_ctx ctx, uint8_t* ctx_rawBufferContainer, uint8_t* key, uint8_t* iv, size_t bufferSize, char* srcBuffer){

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, ctx_rawBufferContainer, bufferSize);

    uint64_t buffer_totalLength = strlen(srcBuffer);
    printf("\nDecrypted buffer:\n");

    for (int i = 0; i < bufferSize; ++i) {
        printf("%.2x", ctx_rawBufferContainer[i]);
    }

    printf("\n%s\n\n",(char *)ctx_rawBufferContainer);

    printf("Last 15 chars in rev order: ");
    for (uint64_t i = bufferSize-1; i > bufferSize - 15; i--) {
        printf("%c", ctx_rawBufferContainer[i]);
    }

    hex_removeBufferPadding(ctx_rawBufferContainer, bufferSize);

    // Checking Integrity
    uint64_t srclength = strlen(srcBuffer);
    int lostData = 0;
    for (int i = 0; i < srclength; ++i) {
        if ((ctx_rawBufferContainer[i] != srcBuffer[i]) && ctx_rawBufferContainer[i] != ' '){
            lostData++;
        }
    }

    if (lostData != 0){
        printf("Integrity Check Failed: Lost Data = %d", lostData);
    } else {
        printf("Integrity Check Verified: Lost Data = %d", lostData);
    }
}

// TO REMOVE / DISABLE
//DATASHEET fetchSheetData(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){
//    int MASTERSHEETID = 0;
//    int RANKERSHEETID = 0;
//
//
//    // DATASHEET CONTAINER
//    DATASHEET outDataSheet;
//    outDataSheet.masterlistCollection = returnSheet;
//    outDataSheet.rankedCollection = rankerSheet;
//
//    int collectionSize = 10;
//    collectionSize = sizeof rankerSheet.container / sizeof rankerSheet.container[1];
//
////    char *collection[][collectionSize] = {};
//    char* tempString = malloc(MAXADDRLENGTH);
//    for (int i = 0; i < collectionSize; i++){
//        // Check if fscanf is successful, if it fails, then we finish the scanning. Ensures that first input must be a name
//        if (((fscanf(DIB, "%s", tempString)) == 1) && ((tempString[0] >= 65) && (tempString[0] <= 90)))
//        {
//            // Check if there are more strings/names
//            while((tempString[0] >= 65) && (tempString[0] <= 90))
//            {
//                strcat(indexNameArr[i], strcat(tempString, " "));
//                fscanf(DIB, "%s", tempString); //
//            }
//            // Stringplaceholder is a number at this point.
//            indexValueArr[i] = tempString;
//            // print both name and int
//            // printf("%s%d\n", name_parray[i], score_array[i]);
//            lineCount++;
//        }
//        else
//        {
//            break;
//        }
//    }
//    return outDataSheet;
//}

// WORKING
void sheet_writeBufferData(char* file_outDest, uint8_t* src_outBuffer, uint64_t size){
    FILE* localFileHandler;
    localFileHandler = fopen(file_outDest, "w");

    fprintf(localFileHandler, "%s\n", "Raw Buffer Data:");
    for (int i = 0; i < size; i++) {
        fprintf(localFileHandler, "%.2x", src_outBuffer[i]);
    }
    fprintf(localFileHandler, "\n\n%s\n", "Decoded Data:");
    fprintf(localFileHandler, "%s", src_outBuffer);
    fclose(localFileHandler);
}
void file_fetch_Datasheetctx(FILE* dataSheetFile){

    // FILE INIT CHECK
    while(dataSheetFile == NULL){

        clearScreen();

        char* FileAddress = malloc(MAXADDRLENGTH); // 509 bytes for 509 UTF-8 Characters following ANSI Compat
        indentCursor(5);
        printf("Enter Datasheet Name: (Default: demo.txt) \n\n");
        indentCursor(6);
        scanf("%s", FileAddress);

        if ((dataSheetFile = fopen(FileAddress,"r")) == NULL){

            // OPEN DEFAULT FILE PROMPT
            clearScreen();
            indentCursor(5);
            printf("Invalid Filename. Use built in demo? (y/n): ");

            char temp;
            scanf("%s", &temp);
            clearScreen(); // CLEAR SCREEN AFTER GETTING PROMPT RESPONSE

            if((temp == 'Y') || (temp == 'y')){
                clearScreen();

                dataSheetFile = fopen(DEFAULTFILEADDRESS, "r");
                indentCursor(6);
                puts("Loaded default input file.\n\n");
                indentCursor(6);
                system("pause");

            } else {
                clearScreen();
                indentCursor(5);
                puts("Cannot load file. Please enter a valid filename.\n\n");
                indentCursor(5);
                system("pause");
            }
        }
    }

    clearScreen();
}
void file_InitDefaultDatasheetCtx(){

}
void file_AssembleDatasheetFromStrHexBuffer(char* strDatasheetBuffer){

    char*   stread_currentBuffer = malloc(30);
    size_t  stread_currentBufferSize = 0;
    size_t  stread_EOFtermCounter = 0;

    // Keeps incrementing till EOF
    while ( strDatasheetBuffer[stread_currentBufferSize] != '<' &&
        strDatasheetBuffer[stread_currentBufferSize-1] != '>'){

        char stread_currentChar = strDatasheetBuffer[stread_currentBufferSize];
        char* bufferContainer = malloc(509);
        size_t sizeOfCharBeforeOperationSymbol = 0;
        size_t plusCount = 0;


        switch (stread_currentChar) {
            case '\n':
                // If newline found, reset all globals if not on subsheet finding mode

            case '+':
                if (plusCount == 1){


                    plusCount = 0;
                } else {
                    plusCount++;
                }
                break;
        }


        if (stread_currentChar == '\n'){

        }

        sizeOfCharBeforeOperationSymbol++;
        stread_currentBufferSize++;
    }

//    char *collection[][5] = {};
//    char *tempString;
//    for (int i = 0; i < SIZE; i++){
//        // Check if fscanf is successful, if it fails, then we finish the scanning. Ensures that first input must be a name
//        if (((fscanf(DIB, "%s", tempString)) == 1) && ((tempString[0] >= 65) && (tempString[0] <= 90)))
//        {
//            // Check if there are more strings/names
//            while((tempString[0] >= 65) && (tempString[0] <= 90))
//            {
//                strcat(indexNameArr[i], strcat(tempString, " "));
//                fscanf(DIB, "%s", tempString); //
//            }
//            // Stringplaceholder is a number at this point.
//            indexValueArr[i] = atoi(tempString);
//            // print both name and int
//            // printf("%s%d\n", name_parray[i], score_array[i]);
//            lineCount++;
//        }
//        else
//        {
//            break;
//        }
//    }

}
void file_DisassembleMasterlist(){
//    SUBSHEET RankerListContainer = {};
//    SUBSHEET MasterlistContainer ={{
//            {"Fridge Grills", 85},
//            {"Window Tab Post", 92},
//            {"Roof Leaf", 96},
//            {"Coconut Rock", 79},
//            {"Shirt Switch Root", 86},
//            {"Screen Fruit", 88},
//            {"White Fan", 94},
//            {"Light Wall", 82},
//            {"Cloud Plane", 77},
//            {"Escaped Post", 97}
//    }};
//
//    DATASHEET sampleSheet = {
//            RankerListContainer,
//            MasterlistContainer,
//        };

}
void file_WriteDatasheettoFile(){
}

//#endregion


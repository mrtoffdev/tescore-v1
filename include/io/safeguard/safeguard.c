/*========================================
    SAFEGUARD ENCRYPTION / DECRYPTION
    Head Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io.h"
#include "safeguard.h"

#define DEBUGMODE 0
#define INTERNALKEY "tescoreinternals"
#define INTERNALIV "XXXCCCVVVIIIOOOE"

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

void enc_AES_encryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferEncryptableBlocks[][16], uint8_t ctx_BufferEncryptedBlocks[][16], size_t ctx_inBufferBlocks);
void enc_AES_decryptBufferBlocks(struct AES_ctx ctx, uint8_t ctx_BufferDecryptableBlocks[][16], uint8_t ctx_BufferDecryptedBlocks[][16], size_t ctx_inBufferBlocks);
//#endregion


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
        AES_init_ctx_iv(&ctx, INTERNALKEY, INTERNALIV);
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

        AES_init_ctx_iv(&ctx, INTERNALKEY, INTERNALIV);
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
//
//    // ISOLATED DECRYPTION TEST ===========================
//    char *encryptedteststring = file_readmasterlist("../demo.dib");
//    size_t hexblocks = fetch_blockunits(encryptedteststring, READ_HEX);
//    char* decryptedstring = calloc(1, hexblocks * 16);
//
//    // decrypt
//    proc_decryptbuffer(encryptedteststring, decryptedstring);
//
//    system("pause");
}


/*========================================
      FILE DECRYPTION
      Authors: Christopher Abadillos Jr.
               Jovic Francis Rayco
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "../render/view/render.h"
#include "lib/aes.h"

#define AES256 1

//#region =========== PRIVATE FUNCTIONS ===========

//#region =========== DOCS ===========
/*
    VARIABLE NAMING SCHEME

    char*       plain_srcStrBuffer          - Container of Plaintext to be encoded
    uint8_t     ctx_hexBufferContainer      - Container of H


    FUNCTIONS: enc_ is for pre_encryption | dec_ is for post_encryption / decryption

    enc_generateHexBufferFromStr()                  - Generates a uint8_t translation of input char* plain_srcStrBuffer
    enc_generateHexBufferFromStr()                  - Generates a char* translation of input uint8_t ctx_hexBufferContainer
    enc_translateStrHexBuffertoHex()                - Generates a uint8_t initialized with string encoded hex data ctx_srcHexStrBuffer

    enc_dsmblStrBuffer()                            - Disassembles the char* into a char* array of 16 bits

 */
//#endregion

// UTILITY
uint64_t    fetch_maxBufferAlloc(char* plain_srcStrBuffer);
size_t      enc_fetchBlockCount(char* plain_srcStrBuffer);
char*       pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize);

void        enc_generateHexBufferFromStr(const char* plain_srcStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);
void        enc_generateStrBufferFromHex(const uint8_t* ctx_hexBufferContainer, char* ctx_DecodeStrBuffer, size_t ctx_hexBufferSize);
void        enc_translateStrHexBuffertoHex(const char* ctx_srcHexStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);

void        enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_dsmblStrBuffer[][16], size_t ctx_blocks);
void        enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks);

void        enc_generateHexBlocks(uint8_t* ctx_hexBufferContainer, char plain_srcStrBuffer);

void        hex_removeBufferPadding(uint8_t* ctx_inRawBuffer, uint64_t size);

//RETURN


//#endregion

//#region TESTING OPS
void testing(const char* plain_strSrcBuffer){
    FILE* localFile;
    struct AES_ctx ctx;

    char* inputbuffer = "as;dfkldjsf;skladfjasd;f00000000";
    uint8_t key[] = "hellotherethisis";
    uint8_t iv[]  = "tescoreinternals";
    size_t inStrSize = 1024;
    uint8_t str[inStrSize];

//    uint8_t container[] = {0x49,0x6E,0x74, 0x65, 0x67, 0x72, 0x69, 0x74, 0x79};
    char decoded[] = "Paradox has been of interest to humankind since ancient times. More than a decade ago Rosemarie Rizzo Parse specified paradoxical patterns of human relating in her nursing theory man-living-health. Since that time there has been increasing recognition by nurse researchers that paradox is an inherent aspect of human experience and an important dimension of health. The purpose of this article is to describe the phenomenon of living paradox as an inherent aspect of human experience and health. The author explores the historical development of paradox";

    size_t ctx_inBufferBlocks = enc_fetchBlockCount(decoded);
    uint64_t ctx_inBufferAlloc = fetch_maxBufferAlloc(decoded);

    // Encryption Requirements
    char        ctx_dsmblStrBuffer[ctx_inBufferBlocks][16];
    uint8_t     ctx_dsmblHexBuffer[ctx_inBufferBlocks][16];
    char*       lineone = calloc(2, 16);

    // Create disassembled char*
    enc_dsmblStrBuffer(decoded, ctx_dsmblStrBuffer, ctx_inBufferBlocks);
    enc_generateHexBufferEncryptable(ctx_dsmblStrBuffer, ctx_dsmblHexBuffer, ctx_inBufferBlocks);

//    char a = 'A';
//    uint8_t b[1][2];
//    b[0][0] = a;
//    printf("%.2x", b[0][0]);

    printf("String Generated: \n\n");
    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        printf("%s", ctx_dsmblStrBuffer[i]);
    }

    // Raw buffer

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


    //#region Encryption Time woo
    AES_init_ctx_iv(&ctx, key, iv);
    uint8_t ctx_BufferBlockContainer[16];

    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            ctx_BufferBlockContainer[j] = ctx_dsmblHexBuffer[i][j];
        }
        AES_CBC_encrypt_buffer(&ctx, ctx_BufferBlockContainer, 16);
        printf("Buffer Block: ");
        for (int k = 0; k < 16; ++k) {
            printf("%.2x", ctx_BufferBlockContainer[k]);
        }
        printf("\n");
    }
    //#endregion

    //#region Decryption Time woo
    printf("\n\nDecryption:\n\n");
    AES_init_ctx_iv(&ctx, key, iv);
    uint8_t ctx_CleanBufferBlockContainer[16];
    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            ctx_CleanBufferBlockContainer[j] = ctx_BufferBlockContainer[j];
        }
        AES_CBC_decrypt_buffer(&ctx, ctx_BufferBlockContainer, 16);
        printf("Buffer Block: ");
        for (int k = 0; k < 16; ++k) {
            printf("%.2x", ctx_CleanBufferBlockContainer[k]);
        }
        printf("\n");
    }
    //#endregion

//    strncat(lineone, ctx_dsmblStrBuffer[0], 16);
//    strncat(lineone, ctx_dsmblStrBuffer[1], 16);

//    printf("Current Block Count: %d\n", ctx_inBufferBlocks);
//    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
//        for (int j = 0; j < 16; ++j) {
////            printf("Current StrBuffer Values: %s\n", ctx_dsmblStrBuffer[i]);
//            ctx_dsmblHexBuffer[i][j] = ctx_dsmblStrBuffer[i][j];
//        }
//    }

//    for (int i = 0; i < ctx_inBufferBlocks; ++i) {
//        printf("Current Block (Hex Container): %.2x\n", ctx_dsmblHexBuffer[i]);
//    }

//    // insert plaintxt to uint8_t arr[]
//    for (int i = 0; i < inStrSize; ++i) {
//        str[i] = plain_strSrcBuffer[i];
//    }

//            uint8_t str[] = "The FitnessGram Pacer Test is a multistage aerobic capacity test that progressively gets more difficult as it continues. The 20 meter pacer test will begin in 30 seconds. Line up at the start. The running speed starts slowly, but gets faster each minute after you hear this signal. [beep] A single lap should be completed each time you hear this sound. [ding] Remember to run in a straight line, and run as long as possible. The second time you fail to complete a lap before the sound, your test is over. The test will begin on the word start. On your mark, get ready, start.0tescoreinternals";

//    // print all buffer
//    uint8_t testBar[2];
//    char testChar[2] = "jk";
//    testBar[0] = (int)testChar[0];
//    testBar[1] = (int)testChar[1];
//    printf("%x", testBar[0]);
//    printf("%x", testBar[1]);
//
//    printf("\n raw buffer \n");
//    for (int i = 0; i < inStrSize; ++i) {
//        fprintf(localFile,"%.2x", str[i]);
//    }
//    fprintf(localFile, "\n\n");
//    AES_init_ctx_iv(&ctx, key, iv);
//    AES_CBC_encrypt_buffer(&ctx, str, inStrSize);
//
//    printf("\n Encrypted buffer\n");
//
//    for (int i = 0; i < inStrSize; ++i) {
//        fprintf(localFile,"%.2x", str[i]);
//    }
//    fprintf(localFile, "\n\n");
//    printf("\n Decrypted buffer\n");
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    AES_CBC_decrypt_buffer(&ctx, str, inStrSize);
//
//    for (int i = 0; i < inStrSize; ++i) {
//        fprintf(localFile,"%.2x", str[i]);
//    }
//
//    fclose(localFile);
//    printf("\n");


//
//    struct AES_ctx ctx;
//
//    //#region TESTING ENCRYPTED BUFFER HANDLING
//
//    //#region Encrypted Buffer
//    char* encryptedBuffer = "46a3db430b2a525e14eb3f0415496085"
//                            "427f176ade887ae67042307c09a66635"
//                            "efa30635bbc7f2ed0e0fe5604198632d"
//                            "7d336459ee99ddef429826a8256da775"
//                            "28d0626363fd68a41638e22349efd833"
//                            "0f477ea4b3a75d3912f83f3b997a3669"
//                            "c2d2182412628e60484f4c80891f966d"
//                            "8a04c51627637cef3ea5d2d9633d3bd7";
//    //#endregion
//
////    uint32_t ctx_encBufferLength = strlen(ctx_rawBufferContainer);
////    uint8_t encryptedBufferTestbench[ctx_encBufferLength/2]; // Decrypted Buffer is always n/2 of encrypted buffer size
////
////    // ENCRYPTED BUFFER HANDLER
////    printf("Encrypted Buffer length: %d\n", ctx_encBufferLength);
////    hex_disassembleCharBuffer(encryptedBufferTestbench, ctx_rawBufferContainer);
//
//    //#endregion
//
//    //#region BUFFER DISASSEMBLER
////    char hextempcontainer[2];
////    int counter = 0;
////    for (int i = 0; i < encryptedBufferLength; i+=2) {
////        hextempcontainer[0] = ctx_rawBufferContainer[i];
////        hextempcontainer[1] = ctx_rawBufferContainer[i+1];
////
////        encryptedBufferTestbench[counter] = (int)strtol(hextempcontainer, NULL, 16);
////        counter++;
////    }
//    //#endregion
//
//    //#region GENERATE KEY CONTAINER
//    uint8_t     key[] = "aaaaaaaaaaaaaaaa";
//    uint8_t     iv[]  = "bbbbbbbbbbbbbbbb";
//
//    //#endregion
//
//    //#region =========== MAIN ENCRYPTION PROCESS ===========
//
//    // SIZE: FETCH BUFFER SIZE FOR SRC STRING BUFFER
//    size_t      ctx_targetBufferSize = fetch_maxBufferAlloc(plain_strSrcBuffer);
//    // VAR: FINAL STRING BUFFER FOR CONVERSION
//    char*       ctx_finalStrBuffer = pad_strBuffer(plain_strSrcBuffer, ctx_targetBufferSize);
//
//    printf("Final Padded Str: \n\n%s\n\n", ctx_finalStrBuffer); //TODO PASS
//
//    size_t      ctx_srcBufferLen = strlen(plain_strSrcBuffer);
//    size_t      ctx_FStrBufferLen = strlen(ctx_finalStrBuffer);
//    printf("Final Padded Str Length: %d\n", ctx_FStrBufferLen);
//
//    uint8_t     ctx_rawBufferContainer[ctx_targetBufferSize];  // VAR: FINAL RAW BUFFER CONTAINER FOR CONVERSION
//    enc_generateHexBuffer(ctx_rawBufferContainer, ctx_finalStrBuffer, ctx_targetBufferSize);
//
//    printf("SizeOf Hex Buffer Container: %d\n", sizeof ctx_rawBufferContainer);
//    printf("Encoded String (Unencrypted): \n\n");
//    for (int i = 0; i < ctx_targetBufferSize; ++i) {
//        printf("%.2x", ctx_finalStrBuffer[i]);
//    }
////    enc_writeBufferData("C:\\demo.txt", ctx_rawBufferContainer, finalStrBuffer_length);
//
////    hex_removeBufferPadding(ctx_rawBufferContainer, finalStrBuffer_length);
//
//    printf("\n\nSize of Translated Buffer: %d\n\n", sizeof ctx_rawBufferContainer / sizeof ctx_rawBufferContainer[0]);
//    printf("Decoded String: \n\n%s\n\n", ctx_rawBufferContainer);
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    AES_CBC_encrypt_buffer(&ctx, ctx_rawBufferContainer, ctx_targetBufferSize);
//
//    printf("Encoded String (Encrypted): \n\n");
//    for (int i = 0; i < ctx_targetBufferSize; ++i) {
//        printf("%.2x", ctx_finalStrBuffer[i]);
//    }
//
//    //#region LEGACY CODE
//    // Insert final buffer into uint8_t encryptable container
////    for (int i = 0; i < buffer_totalLength; ++i) {
////        encryptable_finalBuffer[i] = buffer_finalBufferctx[i];
////    }
////
////    uint8_t str[sizeof buffer_finalBufferctx - 1];
////
////    for (int i = 0; i < sizeof buffer_finalBufferctx - 1; ++i) {
////        str[i] = encryptable_finalBuffer[i];
////    }
////
////    printf( "============ INPUT ==========\n\n"
////            "%s"
////            "\n\n=============================\n\n", sample_inputStrBuffer);
////
////    printf("Input String Size: %d\n", stringbuffer_length);
////    printf("Padding Size (%d): %s\n", strlen(padding), padding);
////    printf("Buffer Total Length: ", buffer_totalLength);
////    printf("Encryptable Buffer Size (Len): %d\n", bufferSize);
////    printf("1st Char of encryptable: %c\n\n", buffer_finalBufferctx);
////    printf("=========== CHARACTER BUFFER ===========\n\n%s\n\n========================================\n\n", buffer_finalBufferctx);
////    printf("Final Buffer Size: %d\n\n", sizeof buffer_finalBufferctx);
////    printf("=========== RAW FINAL BUFFER ===========\n\n%s\n\n========================================\n", (char *)encryptable_finalBuffer);
////    printf("Size of buffer: %d", sizeof str);
////    printf("\nRaw Buffer\n\n");
////    for (int i = 0; i < buffer_totalLength; ++i) {
////        printf("%.2x", encryptable_finalBuffer[i]);
////    }
////
////    printf("\nEncrypted buffer\n\n");
////
////    for (int i = 0; i < buffer_totalLength; ++i) {
////        printf("%.2x", encryptable_finalBuffer[i]);
////    }
//
//    //#region LEGACY CODE (DECRYPTION ALGORITHM)
////
////    printf("\n Decrypted buffer\n");
////
////    AES_init_ctx_iv(&ctx, key, iv);
////    AES_CBC_decrypt_buffer(&ctx, encryptable_finalBuffer, bufferSize);
////
////    for (int i = 0; i < bufferSize; ++i) {
////        printf("%.2x", encryptable_finalBuffer[i]);
////    }
////
////    int removedPadding = 0;
////    for (uint64_t i = bufferSize-1; i > bufferSize-1 - paddingamt; --i) {
////        encryptable_finalBuffer[i] = ' ';
////        removedPadding++;
////    }
////    printf("Removed Padding: %d\n", removedPadding);
////
//////    for (int i = 0; i < 32; ++i) {
//////        printf("%.2x", str[i]);
//////    }
////    printf("%s\n\n",(char *) &encryptable_finalBuffer);
////
////    // Checking Integrity
////    int lostData = 0;
////    for (int i = 0; i < stringbuffer_length; ++i) {
////        if ((encryptable_finalBuffer[i] != sample_inputStrBuffer[i]) && encryptable_finalBuffer[i] != ' '){
////            lostData++;
////        }
////    }
////
////    if (lostData != 0){
////        printf("Integrity Check Failed: Lost Data = %d", lostData);
////    } else {
////        printf("Integrity Check Verified: Lost Data = %d", lostData);
////    }
////#endregion
////#endregion
//
////    fileops_decryptBuffer(ctx, ctx_rawBufferContainer, key, iv, ctx_targetBufferSize, plain_strSrcBuffer);

}

//#region =========== UTILITY ===========
uint64_t fetch_maxBufferAlloc(char* plain_srcStrBuffer){
    //TODO FUNCT UPDATE
    uint64_t bufferSize = 0;
    uint64_t strBufferSize = strlen(plain_srcStrBuffer);
    while (strBufferSize > bufferSize){
        bufferSize += 16;
    }
    return bufferSize;
}
size_t enc_fetchBlockCount(char* plain_srcStrBuffer){
    //TODO FUNCT PASS
    size_t bufferSize = strlen(plain_srcStrBuffer); // Raw Buffer
    size_t processedBuffer = bufferSize/16 + bufferSize; // Considers the null termination char for every block end
    size_t blocksProcessed = processedBuffer / 16; // Raw Buffer w/ null-term consideration / 16 bytes per block

    if (strlen(plain_srcStrBuffer) % 16 != 0) blocksProcessed++; // Extra block if raw buffer has excess bytes
    return blocksProcessed;
}
char* pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize){
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

void enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_dsmblStrBuffer[][16], size_t ctx_blocks){
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
            ctx_dsmblStrBuffer[i][j] = blockStrContainer[j];
        }
        if (debugMode == 1) printf("Current Block String: %s\n", ctx_dsmblStrBuffer[i]);

    }
}
void enc_dsmblHexBuffer(const uint8_t* plain);

void enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks){
    // TODO PASS BUT HEX BUFFER SHOULD BE PRINTED ONE BY ONE
    for (int i = 0; i < ctx_blocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            ctx_dsmblHexBuffer[i][j] = ctx_dsmblStrBuffer[i][j];
        }
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
//#endregion

//#region =========== ENCRYPTION / DECRYPTION ===========

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

// VOID
void sheet_fetch_ctx(FILE* dataSheetFile){

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
            printf("Invalid Filename. Use default file? (y/n): ");

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

// RETURN
DATASHEET fetchSheetData(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){
    int MASTERSHEETID = 0;
    int RANKERSHEETID = 0;

    // SUBSHEET CONTAINERS
    SUBSHEET returnSheet;
    if(returnSheet.id != MASTERSHEETID)
        returnSheet.id = MASTERSHEETID;

    SUBSHEET rankerSheet;
    if(rankerSheet.id != RANKERSHEETID)
        rankerSheet.id = RANKERSHEETID;

    // DATASHEET CONTAINER
    DATASHEET outDataSheet;
    outDataSheet.masterlistCollection = returnSheet;
    outDataSheet.rankedCollection = rankerSheet;

    int collectionSize = 10;
    collectionSize = sizeof rankerSheet.container / sizeof rankerSheet.container[1];

//    char *collection[][collectionSize] = {};
    char* tempString = malloc(MAXADDRLENGTH);
    for (int i = 0; i < collectionSize; i++){
        // Check if fscanf is successful, if it fails, then we finish the scanning. Ensures that first input must be a name
        if (((fscanf(DIB, "%s", tempString)) == 1) && ((tempString[0] >= 65) && (tempString[0] <= 90)))
        {
            // Check if there are more strings/names
            while((tempString[0] >= 65) && (tempString[0] <= 90))
            {
                strcat(indexNameArr[i], strcat(tempString, " "));
                fscanf(DIB, "%s", tempString); //
            }
            // Stringplaceholder is a number at this point.
            indexValueArr[i] = tempString;
            // print both name and int
            // printf("%s%d\n", name_parray[i], score_array[i]);
            lineCount++;
        }
        else
        {
            break;
        }
    }
    return outDataSheet;
}
//#endregion

//#region =========== FILE WRITING ===========
void enc_writeBufferData(char* file_outDest, uint8_t* src_outBuffer, uint64_t size){
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
//#endregion

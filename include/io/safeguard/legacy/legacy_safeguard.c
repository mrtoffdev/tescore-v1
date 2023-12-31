//uint64_t    fetch_maxBufferAlloc(char* plain_srcStrBuffer);
//size_t      enc_fetchBlockCount(char* plain_srcStrBuffer);
//size_t      enc_fetchBlockCountfromHex(char* raw_srcStrBuffer);
//char*       pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize);
//
//void        enc_generateHexBufferFromStr(const char* plain_srcStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);
//void        enc_generateStrBufferFromHex(const uint8_t* ctx_hexBufferContainer, char* ctx_DecodeStrBuffer, size_t ctx_hexBufferSize);
//void        enc_translateStrHexBuffertoHex(const char* ctx_srcHexStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize);
//
//
//void        enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_dsmblStrBuffer[][16], size_t ctx_blocks);
//void        enc_dsmblHexBuffer(const uint8_t* plain_srcHexBuffer, uint8_t ctx_BufferEncryptableBlock[][16], size_t ctx_blocks);
//
//void        enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks);
//
//void        enc_generateHexBlocks(uint8_t* ctx_hexBufferContainer, char plain_srcStrBuffer);
//
//void        hex_removeBufferPadding(uint8_t* ctx_inRawBuffer, uint64_t size);
//
//#region Legacy Functions
//void legacy_fileopsTesting(){
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
//}
//
//uint64_t    fetch_maxBufferAlloc(char* plain_srcStrBuffer){
//    //TODO FUNCT UPDATE
//    uint64_t bufferSize = 0;
//    uint64_t strBufferSize = strlen(plain_srcStrBuffer);
//    while (strBufferSize > bufferSize){
//        bufferSize += 16;
//    }
//    return bufferSize;
//}
//size_t      enc_fetchBlockCount(char* plain_srcStrBuffer){
//    //TODO FUNCT PASS
//    size_t bufferSize = strlen(plain_srcStrBuffer); // Raw Buffer
//    size_t processedBuffer = bufferSize/16 + bufferSize; // Considers the null termination char for every block end
//    size_t blocksProcessed = processedBuffer / 16; // Raw Buffer w/ null-term consideration / 16 bytes per block
//
//    if (strlen(plain_srcStrBuffer) % 16 != 0) blocksProcessed++; // Extra block if raw buffer has excess bytes
//    return blocksProcessed;
//}
//size_t      enc_fetchBlockCountfromHex(char* raw_srcStrBuffer){
//    return (strlen(raw_srcStrBuffer) / 16) / 2;
//}
//char*       pad_strBuffer(char* plain_strSrcBuffer, size_t ctx_targetBufferSize){
//    char* ctx_finalStrBuffer = malloc(ctx_targetBufferSize);
//
//    size_t srclength = strlen(plain_strSrcBuffer); //10
//    size_t padding = ctx_targetBufferSize - srclength; //6
//
//    strcpy(ctx_finalStrBuffer, plain_strSrcBuffer);
//    uint64_t indexPosition = srclength;
//    while (padding > 0){
//        if (padding == 1){
//            strncat(&ctx_finalStrBuffer[indexPosition], "\0", 1);
//        }
//        strncat(&ctx_finalStrBuffer[indexPosition], "0", 1);
//        indexPosition++;
//        padding--;
//    }
//
//    return ctx_finalStrBuffer;
//}
//
// ENCRYPTION
//void enc_generateHexBufferFromStr(const char* plain_srcStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize){
//
//    // Initializes ctx_hexBufferContainer with hex translation of plain_srcStrBuffer
//    for (int i = 0; i < ctx_strBufferSize; i++) {
//        ctx_hexBufferContainer[i] = plain_srcStrBuffer[i];
//    }
//}
//void enc_generateStrBufferFromHex(const uint8_t* ctx_hexBufferContainer, char* ctx_DecodeStrBuffer, size_t ctx_hexBufferSize){
//
//    // Initializes ctx_DecodeStrBuffer with char translation of ctx_hexBufferContainer
//    for (int i = 0; i < ctx_hexBufferSize; i++) {
//        ctx_DecodeStrBuffer[i] = (char)ctx_hexBufferContainer[i];
//    }
//}
//
// Generate Utils
//void enc_generateHexBufferEncryptable(char ctx_dsmblStrBuffer[][16], uint8_t ctx_dsmblHexBuffer[][16], size_t ctx_blocks){
//    // TODO PASS BUT HEX BUFFER SHOULD BE PRINTED ONE BY ONE
//    for (int i = 0; i < ctx_blocks; ++i) {
//        for (int j = 0; j < 16; ++j) {
//            ctx_dsmblHexBuffer[i][j] = ctx_dsmblStrBuffer[i][j];
//        }
//    }
//}

// DECRYPTION
//void enc_translateStrHexBuffertoHex(const char* ctx_srcHexStrBuffer, uint8_t* ctx_hexBufferContainer, size_t ctx_strBufferSize){
//    // Initializes ctx_hexBufferContainer with hex translation of plain_srcStrBuffer
//    char temp_hexDigitContainer[2];
//    int counter = 0;
//    for (int i = 0; i < ctx_strBufferSize; i+=2) {
//        temp_hexDigitContainer[0] = ctx_srcHexStrBuffer[i];
//        temp_hexDigitContainer[1] = ctx_srcHexStrBuffer[i+1];
//
//        ctx_hexBufferContainer[counter] = (int)strtol(temp_hexDigitContainer, NULL, 16);
//        counter++;
//    }
//}
//void enc_dsmblHexBuffer(const uint8_t* plain_srcHexBuffer, uint8_t ctx_BufferEncryptableBlock[][16], size_t ctx_blocks){
//    const short debugMode = 0;
//    debugMode == 1 ? ("Block Size: %d\n", ctx_blocks) : 0;
//    uint64_t lastIndex = 0; // Keep progress in internal for loop
//
//    for (int i = 0; i < ctx_blocks; ++i) {
//        // For every block
//        debugMode == 1 ? printf("Current Block: %d\n", i+1) : 0;
//
//        // Reset blockContainer
//        for (int j = 0; j < 16; ++j) {
//            ctx_BufferEncryptableBlock[i][j] = plain_srcHexBuffer[lastIndex];
//            lastIndex++;
//        }
//
//    }
//}
//
// Disassembly Utils
//void enc_dsmblStrBuffer(const char* plain_srcStrBuffer, char ctx_StringEncryptableBlocks[][16], size_t ctx_blocks){
//    const short debugMode = 0;
//    if (debugMode == 1) printf("Block Size: %d\n", ctx_blocks);
//    uint64_t lastIndex = 0; // Keep progress in internal for loop
//    size_t totalBufferSize = ctx_blocks * 16;
//    size_t strBufferLength = strlen(plain_srcStrBuffer);
//    char blockStrContainer[16];
//
//    for (int i = 0; i < ctx_blocks; ++i) {
//        // For every block
//        if (debugMode == 1) printf("Current Block: %d\n", i+1);
//
//        // Reset blockContainer
//        for (int j = 0; j < 16; ++j) {
//            blockStrContainer[j] = '0';
//            if (j == 15) {
//                // Auto append null term
//                blockStrContainer[j] = '\0';
//            }
//        }
//
//        for (uint64_t j = 0; j < 15; ++j) {
//            if (lastIndex < strBufferLength){
//                blockStrContainer[j] = plain_srcStrBuffer[lastIndex];
//
//                if (debugMode == 1) printf("Current Char: %c\n", plain_srcStrBuffer[lastIndex]);
//                lastIndex++;
//            } else {
//                blockStrContainer[j] = '0';
//            }
//        }
//
//        for (int j = 0; j < 16; ++j) {
//            ctx_StringEncryptableBlocks[i][j] = blockStrContainer[j];
//        }
//        if (debugMode == 1) printf("Current Block String: %s\n", ctx_StringEncryptableBlocks[i]);
//
//    }
//}
//void hex_removeBufferPadding(uint8_t* ctx_inRawBuffer, uint64_t size){
//    uint64_t index = size-1;
//    while (ctx_inRawBuffer[index] == '0'){
//        ctx_inRawBuffer[index] = ' ';
//        index--;
//    }
//    ctx_inRawBuffer[index+1] = '\0';
//}
//
//
//void encryptMasterlist(char* ctx_masterListStrBuffer, char* ctx_EncryptedMasterListStr){
//
//
//    struct AES_ctx ctx;
//    uint8_t key[] = INTERNALKEY;
//    uint8_t iv[]  = INTERNALIV;
//
//    // Encryption Requirements
//    size_t ctx_inBufferBlocks = enc_fetchBlockCount(ctx_masterListStrBuffer);
//    uint64_t ctx_inBufferAlloc = fetch_maxBufferAlloc(ctx_masterListStrBuffer);
//
//    char        ctx_dsmblStrBuffer[ctx_inBufferBlocks][16];
//    uint8_t     ctx_dsmblHexBuffer[ctx_inBufferBlocks][16];
//
//    // Create disassembled char*
//    enc_dsmblStrBuffer(ctx_masterListStrBuffer, ctx_dsmblStrBuffer, ctx_inBufferBlocks);
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
//    uint8_t ctx_BufferEncryptableBlocks[ctx_inBufferBlocks][16];
//    uint8_t ctx_BufferEncryptedBlocks[ctx_inBufferBlocks][16];
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    enc_AES_encryptBufferBlocks(ctx, ctx_dsmblHexBuffer, ctx_BufferEncryptedBlocks, ctx_inBufferBlocks);
//
//
//}
//void decryptMasterList(char* ctx_masterListHexBuffer, char* ctx_decryptedMasterListStr){
//
//    struct AES_ctx ctx;
//    uint8_t key[] = INTERNALKEY;
//    uint8_t iv[]  = INTERNALIV;
//
//    // Fetch strBuffer details
//    size_t  demo_strSize = strlen(ctx_masterListHexBuffer);
//    size_t  demo_blockSize = enc_fetchBlockCountfromHex(ctx_masterListHexBuffer);
//    printf("Raw Buffer Size: %d\n", demo_strSize);
//    printf("Actual Buffer Size: %d\n", demo_strSize/2);
//    printf("Block Size: %d\n", demo_blockSize);
//
//    // Translate whole buffer into hex
//    uint8_t demo_translatedHexValues[demo_strSize];
//    enc_translateStrHexBuffertoHex(ctx_masterListHexBuffer, demo_translatedHexValues, demo_strSize);
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
//}
//
//void fileops_encryptBuffer(struct AES_ctx ctx){}
//void fileops_decryptBuffer(struct AES_ctx ctx, uint8_t* ctx_rawBufferContainer, uint8_t* key, uint8_t* iv, size_t bufferSize, char* srcBuffer){
//
//    AES_init_ctx_iv(&ctx, key, iv);
//    AES_CBC_decrypt_buffer(&ctx, ctx_rawBufferContainer, bufferSize);
//
//    uint64_t buffer_totalLength = strlen(srcBuffer);
//    printf("\nDecrypted buffer:\n");
//
//    for (int i = 0; i < bufferSize; ++i) {
//        printf("%.2x", ctx_rawBufferContainer[i]);
//    }
//
//    printf("\n%s\n\n",(char *)ctx_rawBufferContainer);
//
//    printf("Last 15 chars in rev order: ");
//    for (uint64_t i = bufferSize-1; i > bufferSize - 15; i--) {
//        printf("%c", ctx_rawBufferContainer[i]);
//    }
//
//    hex_removeBufferPadding(ctx_rawBufferContainer, bufferSize);
//
//    // Checking Integrity
//    uint64_t srclength = strlen(srcBuffer);
//    int lostData = 0;
//    for (int i = 0; i < srclength; ++i) {
//        if ((ctx_rawBufferContainer[i] != srcBuffer[i]) && ctx_rawBufferContainer[i] != ' '){
//            lostData++;
//        }
//    }
//
//    if (lostData != 0){
//        printf("Integrity Check Failed: Lost Data = %d", lostData);
//    } else {
//        printf("Integrity Check Verified: Lost Data = %d", lostData);
//    }
//}
//
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
//
// WORKING
//void sheet_writeBufferData(char* file_outDest, uint8_t* src_outBuffer, uint64_t size){
//    FILE* localFileHandler;
//    localFileHandler = fopen(file_outDest, "w");
//
//    fprintf(localFileHandler, "%s\n", "Raw Buffer Data:");
//    for (int i = 0; i < size; i++) {
//        fprintf(localFileHandler, "%.2x", src_outBuffer[i]);
//    }
//    fprintf(localFileHandler, "\n\n%s\n", "Decoded Data:");
//    fprintf(localFileHandler, "%s", src_outBuffer);
//    fclose(localFileHandler);
//}
//void file_fetch_Datasheetctx(FILE* dataSheetFile){
//
//    // FILE INIT CHECK
//    while(dataSheetFile == NULL){
//
//        clearScreen();
//
//        char* FileAddress = malloc(MAXADDRLENGTH); // 509 bytes for 509 UTF-8 Characters following ANSI Compat
//        indentCursor(5);
//        printf("Enter Datasheet Name: (Default: demo.txt) \n\n");
//        indentCursor(6);
//        scanf("%s", FileAddress);
//
//        if ((dataSheetFile = fopen(FileAddress,"r")) == NULL){
//
//            // OPEN DEFAULT FILE PROMPT
//            clearScreen();
//            indentCursor(5);
//            printf("Invalid Filename. Use built in demo? (y/n): ");
//
//            char temp;
//            scanf("%s", &temp);
//            clearScreen(); // CLEAR SCREEN AFTER GETTING PROMPT RESPONSE
//
//            if((temp == 'Y') || (temp == 'y')){
//                clearScreen();
//
//                dataSheetFile = fopen(DEFAULTFILEADDRESS, "r");
//                indentCursor(6);
//                puts("Loaded default input file.\n\n");
//                indentCursor(6);
//                system("pause");
//
//            } else {
//                clearScreen();
//                indentCursor(5);
//                puts("Cannot load file. Please enter a valid filename.\n\n");
//                indentCursor(5);
//                system("pause");
//            }
//        }
//    }
//
//    clearScreen();
//}
//void file_InitDefaultDatasheetCtx(){
//
//}
//void file_AssembleDatasheetFromStrHexBuffer(char* strDatasheetBuffer){
//
//    char*   stread_currentBuffer = malloc(30);
//    size_t  stread_currentBufferSize = 0;
//    size_t  stread_EOFtermCounter = 0;
//
//    // Keeps incrementing till EOF
//    while ( strDatasheetBuffer[stread_currentBufferSize] != '<' &&
//            strDatasheetBuffer[stread_currentBufferSize-1] != '>'){
//
//        char stread_currentChar = strDatasheetBuffer[stread_currentBufferSize];
//        char* bufferContainer = malloc(509);
//        size_t sizeOfCharBeforeOperationSymbol = 0;
//        size_t plusCount = 0;
//
//
//        switch (stread_currentChar) {
//            case '\n':
//                // If newline found, reset all globals if not on subsheet finding mode
//
//            case '+':
//                if (plusCount == 1){
//
//
//                    plusCount = 0;
//                } else {
//                    plusCount++;
//                }
//                break;
//        }
//
//
//        if (stread_currentChar == '\n'){
//
//        }
//
//        sizeOfCharBeforeOperationSymbol++;
//        stread_currentBufferSize++;
//    }
//
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
//
//}
//void file_DisassembleMasterlist(){
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
//
//}
//void file_WriteDatasheettoFile(){
//}
//
//#endregion
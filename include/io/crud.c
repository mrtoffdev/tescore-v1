/*========================================
      CRUD OPERATIONS
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RENDER UTILS
#include "../render/view/render.h"

// FILE OPERATIONS / CRUD
#include "../io/io.h"

// ENCRYPTION / DECRYPTION
#include "../io/safeguard/safeguard.h"

// SORT ALGORITHMS
#include "../proc/proc.h"

#define DEBUGMODE 1

// TEST SCRIPTS
void CRUD_TEST(Sheetctx in_sctxmaster){
//    char* strmasterenc = "a8525e2a75499e55f6add2ede49a8e4e2c99b3cdf9591fd55f8cfe6a5202f3f89a75575589dcf55d9a6a02575a820e14865be0ecc7bb52910e0b008da007b39781ec9a93f96c70d8dd0dcfd59ca04d5b64af0798cb9153e590d648a9df4aa051b29a2347a597b00b5fd9be083ed39b5ecd5d04a347ccb735a213926a267279ea1d8e98937ea9b3095eb7764b184741ad26d28591033cd0f47b73403efb9d3b79bbe0e0b38dda2caba01b223510aad19baf7ffdba04a123f7c1fd32ce61bc3b4ff0c3a237c32e5f40f707820d6d724b255d5595bf34784df6507d224cfcf1221a170bf3b85aebe3091b5a0efbf34dabd22b62f602bd138cb7dec7b577d09cd78c39762b36edf2f2355adc98f54e101bd348c0316f0cc12f23afc8e398b2b1102e3a58660c197a8f0efe26b4df34086eba69c5f9accc33a835e5a13e979e730b4e4176beda2ea5e3627ce54476804c3c177cc7a02a53fc3c70d4fbbdabc7fc9dd733746e065fe4d0d18915222cf699daa2e937b4be3460e7ed4bae85b77da556e240656fec4006d2c465ece8290bde57a01a03a79dcfd841674fbdd34ebf0e188c5f6f85f7d22931551b6142af183e406283e01c252fb836d370b049b456e25ac2145dbd683005cf5c8a479302a58f3649d929621e148ba3a9da3dde066cad0656f3a3fa9bdb324b2ea91b7095295291e6e145f9b0aeff4bea96a20c2c2adb14e36af19666f6cbe8e976262b43bb3cf2ccfe8c5a02b1a3e3655e86cd0bfa8a72e186404918216dcdaaaa3a4ca1154edc4bcbc82b7ae322ca3c9a918b35b3926167097eca9e44cde3c288da660edba017de97cf44e783a2dc7131bccc3aea0b69ef769546aacd29c02991d74b4c46571713d139cc960946425c4317e6953a8c0883a7d213db8a9da03b43d8beb0826483e8";
//    char* outfile = malloc(MAXMASTERLEN);
//
//    proc_decryptbuffer(strmasterenc, outfile);
//    printf("\n\nOutfile found: \n\n%s\n\n", outfile);
//    system("pause");
//    save_writesheetctx(in_sctxmaster);
    save_writesheetctx(in_sctxmaster, "C:\\makefile2.dib");
}

// -> ENTRY POINTS <-
Sheetctx save_readsheetctx(){
    scan: // <- Callback function for address rejection / cancel operation

    // Print Dialogue
    clearScreen();
    indentCursor(5);
    printf("Enter Datasheet Location: (Default: default) \n\n");
    indentCursor(6);

    // Fetch contexts
    char def_fileaddress[MAXADDRLENGTH] = "default";
    char* FileAddress = calloc(1, 509); // 509 bytes for 509 UTF-8 Characters following ANSI Compat
    scanf("%s", FileAddress);
    size_t in_addrlen = strlen(FileAddress);
    FILE* in_file = fopen(FileAddress, "r");

    // Check file extension if correct & is not using default secret
    char* extension = ".dib";
    int pass = 0;
    int ctr = 3;
    for (size_t i = in_addrlen-1; i > in_addrlen-5; --i) {
        FileAddress[i] == extension[ctr] ? pass++: 0;
        printf("Checking File Extension: %c to %c", FileAddress[i], extension[ctr]);
        ctr--;
    }
    if ((pass < 3) && !(strcmp(FileAddress, def_fileaddress) == 0)){
        clearScreen();
        indentCursor(5);
        puts("Invalid file extension. Please open a (.dib) file.\n");
        indentCursor(5);
        system("pause");
        goto scan;
    }

    // Insert default dataset
    if (strcmp(FileAddress, def_fileaddress) == 0){
        Sheetctx out_sctx; // Prepare out_sctx
        // Fetch default
        out_sctx = init_sheetdefctx();
        // Print Dialogue
        indentCursor(6);
        puts("Loaded embedded default sheet.\n\n");
        indentCursor(6);
        system("pause");
        clearScreen();
        return out_sctx;
    } else

    // If file opened in FileAddress does not exist
    if(!in_file){
        clearScreen();
        indentCursor(5);

        // Prompt to create new sheet at that address
        printf("Invalid Filename. Create new sheet in %s? (y/n): ", FileAddress);

        char temp;
        scanf("%s", &temp);

        if((temp == 'Y') || (temp == 'y')){
             Sheetctx out_blanksctx = {
                     FileAddress,
                     "tescoreinternals",
                     FileAddress,
             };

//            fclose(in_file);
            in_file = fopen(FileAddress,"w+");
            fprintf(in_file, "%s", out_blanksctx.address);
            fclose(in_file);

            // Print Dialogue
            clearScreen();
            indentCursor(6);
            printf("Saved address: %s\n", FileAddress);
            puts("Created new Sheet.\n\n");
            indentCursor(6);
            system("pause");
            clearScreen();
            return out_blanksctx;

        } else {
            // Print Dialogue & Restart Loop
            clearScreen();
            indentCursor(5);
            puts("Cannot load file. Please enter a valid filename.\n\n");
            indentCursor(5);
            system("pause");
            goto scan;
        }
    } else {
        Sheetctx out_readsctx;
        char* in_strmasterlist = file_readmasterlist(in_file);
        char* in_decryptedstrmaster = malloc(MAXMASTERLEN);

        proc_decryptbuffer(in_strmasterlist, in_decryptedstrmaster);
        printf("\n\nOutfile found: \n\n%s\n\n", in_decryptedstrmaster);

        out_readsctx = sheet_deconststr(in_decryptedstrmaster);
        system("pause");
        clearScreen();
        return out_readsctx;
    }

}
void save_writesheetctx(Sheetctx in_sctxmaster, const char* out_fileaddress){
    // Process: Fetch Sheetctx >> Sort Masterlist >>
    size_t size_chk = util_fetchmastersize(in_sctxmaster);

    // Print received masterlist contents:
    if (DEBUGMODE == 1){
        printf("Received Data: \n"
               "Size of Masterlist: %d\n"
               "Masterlist Contents: \n\n", size_chk);
        for (int i = 0; i < size_chk; ++i) {
            printf("%s : %d\n", in_sctxmaster.masterlist[i].indexName, in_sctxmaster.masterlist[i].value);
        }
        putchar('\n');
    }

    // Deconstruct Sheetctx to String
    char* out_strmaster = calloc(LIMIT_INDEX, MAXMASTERLEN);
    sheet_conststr(in_sctxmaster, out_strmaster);

    // Encrypt Buffer
    char* out_encstrmaster = calloc(LIMIT_INDEX, MAXMASTERLEN);
    proc_encryptbuffer(out_strmaster, out_encstrmaster);

    // Write to File
    file_writemasterlist(out_fileaddress, out_encstrmaster);

    printf("\nConstructed StrMaster:\n\n%s\n\n", out_strmaster);
    printf("\nEncrypted StrMaster:\n\n%s\n\n", out_encstrmaster);
    system("pause");
}

// UTILS
size_t util_fetchmastersize(Sheetctx in_sctx){
    size_t size_chk = 0;
    while ((in_sctx.masterlist[size_chk].indexName[0] > 64 && in_sctx.masterlist[size_chk].indexName[0]< 91) ||
           (in_sctx.masterlist[size_chk].indexName[0] > 96 && in_sctx.masterlist[size_chk].indexName[0]< 123)){
        size_chk++;
    }
    return size_chk;
}

// INIT DEFAULT CONTEXTS
Renderctx init_renderctx(Sheetctx in_sctx){
    Renderctx ctx = {
            in_sctx,
            'X',
            '1',
            0,
            1,
            1,
            1,
            0,
            10,
            in_sctx.name,
    };

    // Initialize Default Values
//    ctx.SessionSheet = in_sctx;                         // Fetch Sheet
//    strcpy(ctx.sheetName, in_sctx.name);   // Insert Sheetctx name prop
//    ctx.NAVKEY = '1';                                   // Points to Default Panel Selection (Graph)
//    ctx.handlerMode = 0;                                // 0 : Active Handler | 1 : Inactive Handler
//    ctx.operationMode = 1;                              // 1 : View | 2 : Select | 3 : Edit
//    ctx.sessionPanelID = 1;                             // ID of panel to render
//    ctx.renderCellIndex = 1;                            // Index of cursor in lists | Default: 1
//    ctx.renderCellX = 'X';                              // Default RenderCell Key

    return ctx;
}
Sheetctx init_sheetdefctx(){
    DEBUGMODE == 1 ? printf("From init_sheetdefctx: ------------------------\n"): 0;
    //#region Sample Masterlist Dataset
    Sheetctx sample = {
            "Sheetname",
            "Passphrase",
            "nonsave",
            {{"Fridge Grills", 85},
            {"Window Tab Post", 92},
            {"Roof Leaf", 96},
            {"Coconut Rock", 79},
            {"Shirt Switch Root", 86},
            {"Screen Fruit", 88},
            {"White Fan", 94},
            {"Light Wall", 82},
            {"Cloud Plane", 77},
            {"Escaped Post", 97},
            {"Cheryl Webster", 89},
            {"Ayrton Alford", 45},
            {"Zayyan Calderon", 23},
            {"Lorena Vaughan", 0},
            {"Hudson Burn", 0},
            {"Amari Sharples", 0},
            {"Beatrice Flowers", 0},
            {"Ellouise Ponce", 0},
            {"Zahid Arnold", 0},
            {"Ciaron Wynn", 0},
            {"Mikayla Nicholson", 98},
            {"Riley-Jay Carney", 79},
            {"Jan Good", 50},
            {"Neil Pritchard", 88},
            {"Emelie Yu", 87},
            {"Ada Medina", 87},
            {"Gideon Solis", 89},
            {"Darin Rivas", 90},
            {"Yasmine Wade", 99},
            {"Aydin Wyatt", 100},
            {"Eilish Whyte", 100},
            {"Polly Bullock", 100},
            {"Tony Emery", 100},
            {"Darci Melton", 100},
            {"Jo Corona", 100},
            {"Lachlan Trevino", 95},
            {"Clifford Johns", 79},
            {"Darla Robbins", 85},
            {"Jorja Mcclain", 60},
            {"Jorja Mcclain", 65}
    }};
    //#endregion

    Sheetctx out_sctx = {
            "Demo_sheet.dib",
            "Admin",
            "apasswordof16byt",
    };

    size_t in_mastersize = util_fetchmastersize(sample);
    DEBUGMODE == 1 ? printf("Sample Size: %d\n", in_mastersize): 0;
    for (int i = 0; i < in_mastersize; ++i) {
        out_sctx.masterlist[i] = sample.masterlist[i];
    }
    //#endregion
    return out_sctx;
}

// DECONSTRUCTION / CONSTRUCTION
Sheetctx sheet_deconststr(char* in_strmasterlist){
    // Fetch Ctx:
    size_t in_lines = 0;
    size_t in_len = strlen(in_strmasterlist);

    DEBUGMODE == 1 ? printf("Received String Len: %d\n", in_len): 0;
    DEBUGMODE == 1 ? printf("Received String: \n\n%s\n\n", in_strmasterlist): 0;

    // Containers
    char out_names[LIMIT_INDEX][MAXNAMECHARLIMIT];
    long out_grades[LIMIT_INDEX];

    // Counters
    size_t ln_end= 0;
    size_t ln_start = 0;
    size_t pendingindex = 0;

    // Main disassembly logic
    for (int cursor = 0; cursor < in_len; cursor++) {
        // Iterate through all masterlist characters

        if (in_strmasterlist[cursor] == '\n'){
//            ln_size = 0; // Reset line size
            ln_end = cursor; // Set current cursor as line end '\n'

            size_t ln_size = ln_end - ln_start; // Fetch how many characters in a line
            char ln_charctr[ln_size];

            DEBUGMODE == 1 ? printf("Line Size: %d\n", ln_size): 0;

            // Insert line into linectr
            for (size_t i = 0; i < ln_size; ++i) {
                ln_charctr[i] = in_strmasterlist[ln_start];
//                printf("Current char: %c\n", iter_currentline[i]);
//                currentlinesize++;
                ln_start++;
            }

            ln_start++; // Skip over newline char
            DEBUGMODE == 1 ? printf("Line Break Found. Current Line: %s\n", ln_charctr): 0;

            // Separate names and grades
            char* temp_namectr;
            long temp_gradectr;

            temp_gradectr = strtol(ln_charctr, &temp_namectr, 10);

            DEBUGMODE == 1 ? printf("Current name stored in temp: %s\n", temp_namectr): 0;
            DEBUGMODE == 1 ? printf("Current grade: %d\n", temp_gradectr): 0;

            // Insert to Array
            out_grades[pendingindex] = temp_gradectr;
            strcpy(out_names[pendingindex], temp_namectr);
            pendingindex++;

            // Clear block container
            for (int i = 0; i < ln_size; ++i) {
                ln_charctr[i] = 0;
            }

            in_lines++;
        }

    }

    // Print Stored String: Debug
    if (DEBUGMODE == 1){
        printf("Lines found: %d\n", in_lines);
        for (int i = 0; i < in_lines; ++i) {
            printf("Name: %s - Grade: %d\n", out_names[i], out_grades[i]);
        }
    }

    // Assemble Sheetctx
    Sheetctx out_sctxmaster = {
            "DIB Sheet",
            "passphrase"
    };
    for (int i = 0; i < in_lines; ++i) {
        out_sctxmaster.masterlist[i].value = (short)out_grades[i];
        strcpy(out_sctxmaster.masterlist[i].indexName, out_names[i]);
    }

    // Debug
    for (int i = 0; i < in_lines; ++i) {
        printf("Stored Index: %d,\nName: %s Grade: %d\n", i, out_sctxmaster.masterlist[i].indexName, out_sctxmaster.masterlist[i].value);
    }

    DEBUGMODE == 1 ? system("pause"): 0;
    return out_sctxmaster;
}
void sheet_conststr(Sheetctx in_sctxmaster, char* out_strmasterlist){
    // Fetch ctx
    size_t indexct = util_fetchmastersize(in_sctxmaster);
    DEBUGMODE == 1 ? printf("Deconstructor Received Size: %d\n", indexct): 0;

    module_alphasort(&in_sctxmaster, 0, indexct-1);

    // Deconstruct sheet to str
    DEBUGMODE == 1 ? printf("Deconstructor Progress: \n\n"): 0;
    for (size_t i = 0; i < indexct; i++) {
        // Fetch grade
        char temp_gradectr[4];
        snprintf(temp_gradectr, 4,"%hd", in_sctxmaster.masterlist[i].value); // Convert Graded to StrGrade

        DEBUGMODE == 1 ? printf("Entry No %d: ", i): 0;
        printf("%s %s\n", temp_gradectr, in_sctxmaster.masterlist[i].indexName);

        strcat(out_strmasterlist, temp_gradectr); // Insert Grade
        strcat(out_strmasterlist, in_sctxmaster.masterlist[i].indexName); // Insert Name

        strcat(out_strmasterlist,"\n"); // Break Line
    };

    DEBUGMODE == 1 ? ("Deconstructed String\n\n%s\n\n", out_strmasterlist): 0;
}

// FILE OPERATIONS
void file_writemasterlist(const char* in_fileaddress, const char* in_strbuffer){
    FILE* outfile;
    outfile = fopen(in_fileaddress, "w");
    printf("Written File:\n\n%s\n\n", in_strbuffer);
    fprintf(outfile, in_strbuffer);
    fclose(outfile);
}
char* file_readmasterlist(FILE* in_file){
    char* in_strbuffer = calloc(1, 4096);
    printf("Read File\n");
    fscanf(in_file, "%s", in_strbuffer);
    fclose(in_file);
    return in_strbuffer;
}

//#region LEGACY =============
// DATASHEET OPERATIONS
void fetchData(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){



}
void fetch_gradeTable(Sheetctx Datactx, int distributionTable[11][2]){
    // Placeholder Data
    uint8_t unsortedGradeRounds[10][2] = {
            {99, 2},
            {98, 4},
            {100, 10},
            {47, 26},
            {80, 5},
            {72, 7},
            {94, 10},
            {87, 2},
            {69, 3},
            {91, 9}
    };

    uint8_t gradeTable[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    uint8_t collection_size = sizeof unsortedGradeRounds / sizeof unsortedGradeRounds[0];

    for (int y = 0; y < 11; ++y) {
        // MATCH MATRIX[N][0] WITH GRADE SCALING
        distributionTable[y][0] = gradeTable[y];
    }

//    for (int y = 0; y < 11; ++y) {
//
//        for (int x = 0; x < collection_size; ++x) {
//            if(
//                // GRADE ATTAINED IS LESS/EQUAL TO GRADE TABLE
//                (unsortedGradeRounds[x][0] >= distributionTable[y][0]) &&
//                // GRADE IS LESS THAN LOWER GRADE TABLE
//                (unsortedGradeRounds[x][0] < distributionTable[y+1][0])){
//
//                distributionTable[y][1] += unsortedGradeRounds[x][1];
//            }
//        }
//    }
}

// DEV TEST FUNCTION
void file_InitMasterlist();
//#endregion






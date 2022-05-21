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

// SORT ALGORITHMS
#include "../proc/proc.h"

#define SIZE 10
#define DEBUGMODE 1

// TEST SCRIPTS
void CRUD_TEST(){
    // Construction test
    Sheetctx samplesheet = {
            "Sheetname",
            "passphrase",
            {
                    {"Henry Godlot", 90},
                    {"Jacob Holmes", 100},
                    {"John Handwick", 50},
            },
            3
    };

    char *assembled_strmaster = calloc(1,MAXMASTERLEN);

    sheet_conststr(samplesheet, assembled_strmaster);
    DEBUGMODE == 1 ? printf("Finished Construction Test: \n"): 0;
    DEBUGMODE == 1 ? printf("Received String:\n\n%s\n\n", assembled_strmaster): 0;
    system("pause");

    // Deconstruction Test
//    char* samplestr = "John Holmes 100\nJacob Josh 98\nJoshua Jeremiah 97\nHans Crook 89\nWilly Wonkers 88";
    DEBUGMODE == 1 ? printf("Strlen from CRUD_TEST: %d\n", strlen(assembled_strmaster)): 0;

    sheet_deconststr(assembled_strmaster);
    system("pause");
}

// ENTRY POINTS
Sheetctx save_readsheetctx(){
    Sheetctx out_sctx;
    FILE* in_file;
    char* FileAddress = malloc(MAXADDRLENGTH); // 509 bytes for 509 UTF-8 Characters following ANSI Compat

    // Print Dialogue
    indentCursor(5);
    printf("Enter Datasheet Name: (Default: demo.txt) \n\n");
    indentCursor(6);

    // Fetch FileAddress
    scanf("%s", FileAddress);
    in_file = fopen(FileAddress,"r");

    char var_defaultload = 'N';
    while(in_file == NULL && var_defaultload == 'N'){
        clearScreen();

        // OPEN DEFAULT FILE PROMPT
        clearScreen();
        indentCursor(5);
        printf("Invalid Filename. Use built in demo? (y/n): ");

        char temp;
        scanf("%s", &temp);

        if((temp == 'Y') || (temp == 'y')){
            clearScreen();

            // Load Embedded Defaults
            out_sctx = init_sheetdefctx();

            // Print Dialogue
            indentCursor(6);
            puts("Loaded default input file.\n\n");
            indentCursor(6);
            var_defaultload = 'Y';
            system("pause");
            break;
        } else {

            // Print Dialogue & Restart Loop
            clearScreen();
            indentCursor(5);
            puts("Cannot load file. Please enter a valid filename.\n\n");
            indentCursor(5);
            system("pause");
        }

    }
    if (in_file != NULL){

    }

    clearScreen();
    return out_sctx;
}
void save_writesheetctx(){
    // Process: Fetch Sheetctx >> Sort Masterlist >>

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
    //#region Sample Masterlist Dataset
    Index samplesize[] = {
            {"Fridge Grills", 85},
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
    };
    //#endregion

    Sheetctx out_sctx = {
            "Demo_sheet.dib",
            "Admin",
            "apasswordof16byt",
    };

    DEBUGMODE == 1 ? printf("Sample Size: %d\n", sizeof samplesize / sizeof samplesize[0]): 0;

    out_sctx.masterlist[0] = samplesize[0];
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

            DEBUGMODE == 1 ? ("Line Size: %d\n", ln_size): 0;

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
    return out_sctxmaster;
}
void sheet_conststr(Sheetctx in_sctxmaster, char* out_strmasterlist){
    // Fetch ctx
    size_t indexct = sizeof in_sctxmaster.masterlist / sizeof in_sctxmaster.masterlist[0];
    DEBUGMODE == 1 ? printf("Current masterlist size: %d\n", indexct): 0;

    for (int i = 0; i < in_sctxmaster.size; ++i) {
        char temp_gradectr[3];
        snprintf(temp_gradectr, 4,"%hd", in_sctxmaster.masterlist[i].value); // Convert Graded to StrGrade
        strcat(out_strmasterlist, temp_gradectr); // Insert Grade
        strcat(out_strmasterlist, in_sctxmaster.masterlist[i].indexName); // Insert Name
        strcat(out_strmasterlist,"\n"); // Break Line
    }

    DEBUGMODE == 1 ? ("%s", out_strmasterlist): 0;
}

// FILE OPERATIONS
void file_writemasterlist(const char* in_fileaddress, const char* in_strbuffer){
    FILE* outfile;
    outfile = fopen(in_fileaddress, "w");
    printf("Written File:\n\n%s\n\n", in_strbuffer);
    fprintf(outfile, in_strbuffer);
    fclose(outfile);
}
char* file_readmasterlist(const char* in_fileaddress){
    char* in_strbuffer = calloc(1, 4096);
    FILE* infile;
    infile = fopen(in_fileaddress, "r");
    printf("Read File\n");
    fscanf(infile, "%s", in_strbuffer);
    fclose(infile);
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






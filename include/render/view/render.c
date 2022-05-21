/*========================================
      FRAME RENDERING
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "render.h"
#include "../../proc/proc.h"

#define DEBUGMODE 1

// CLEAR SCREEN DEFS
#define WINCLR "cls"
#define GNUCLR "clr"
#define REGEXCLR1 "\e[1;1H\e[2J"
#define REGEXCLR2 "\x1b[2J\x1b[H"

int         gradeScaling[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
            studentScaling[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
char*       sheetName = "SHORTNAME";
char*       matrixGraph[10][11];

// Framebuffer
void refreshFrame(Renderctx in_rctx, Sheetctx in_sctx, char commandLog[10][509]){
    // Process: Sheetctx >> RankerModule == Return: Index[10](Ranked) >> Generator == Index[i].name(char) Index[i].value(char) == ctx_masterlist[i][i]

    //#region Sample Sheet
    Sheetctx samplesheet = {
            "Sheetname",
            "passphrase",
            {
                    {"Jacob Holmes", 100},
                    {"John Handwick", 50},
                    {"Henry Godlot", 90},
            },
            3
    };
    //#endregion

    //#region Reset Screen
    clearScreen();
    renderWhiteSpace(3);
    //#endregion

    // FETCH CTX
    size_t size_chk = 0;
    while ((samplesheet.masterlist[size_chk].indexName[0] > 64 && samplesheet.masterlist[size_chk].indexName[0]< 90) ||
            (samplesheet.masterlist[size_chk].indexName[0] > 96 && samplesheet.masterlist[size_chk].indexName[0]< 123)){
        size_chk++;
    }
    DEBUGMODE == 1 ? printf("Estimated Masterlist Size: %d\n", size_chk): 0;

    // MASTERLIST DECONSTRUCTOR
    char* ctx_masterlist[size_chk][2]; // Local Masterlist in String Format

    DEBUGMODE == 1 ? printf("\nChecking Data: \n", size_chk): 0;
    for (int i = 0; i < size_chk; ++i) {
        if ((samplesheet.masterlist[i].indexName[0] > 64 && samplesheet.masterlist[i].indexName[0] < 90) ||
            (samplesheet.masterlist[i].indexName[0] > 96 && samplesheet.masterlist[i].indexName[0] < 123)){

            DEBUGMODE == 1 ? printf("Starting char found: %c Masterlist Size: %d\n", samplesheet.masterlist[i].indexName[0], i+1) : 0;
            ctx_masterlist[i][0] = samplesheet.masterlist[i].indexName;

            int gr_val = samplesheet.masterlist[i].value;
            char* temp = malloc(3);
            itoa(gr_val, temp, 10);
            ctx_masterlist[i][1] = temp;
        } else {
            ctx_masterlist[i][0] = " ";
            ctx_masterlist[i][1] = " ";
        }
    }

    // Print Fetched Data
    if (DEBUGMODE == 1){
        printf("\n\nFetched Data: %d\n", size_chk);
        for (int i = 0; i < size_chk; ++i) {
            printf("%s : %s\n", ctx_masterlist[i][0], ctx_masterlist[i][1]);
        }
    }

    // CALL SORT FUNCTIONS -------------------------------------------------------------

    // ALPHAMERGE SORT
    Index out_master[LIMIT_STUDENTS];
    module_alphasort(&samplesheet, 0, size_chk - 1);

    if (DEBUGMODE == 1){
        printf("\n\nMergesort Out: \n", size_chk);
        for (int i = 0; i < size_chk; ++i) {
            printf("%s : %d\n",samplesheet.masterlist[i].indexName, samplesheet.masterlist[i].value);
        };
    }

    //#region Ranking Module Prep
    // RANKER SORT
    Index out_ranked[10];
    module_ranksort(in_rctx.SessionSheet, out_ranked);

    char* rg_names[10];
    short rg_grades[10];

    // Print Ranked Containers
    if (DEBUGMODE == 1){
        printf("Fetched Ranker List: \n");
        for (int i = 0; i < size_chk; ++i) {
            printf("Name: %s Grade: %hd", rg_names, rg_grades);
        }
    }
    //#endregion

    //#region UPPER PANEL

    // HEADER
    renderSeparator(2);
    renderHeader(in_rctx);
    renderSeparator(3);

    // PANELS : BAR GRAPH MATRIX & TOP RANKERS
    generateGraph(in_rctx.SessionSheet);

    renderMatrixRankerRow(rg_names, rg_grades, in_rctx);

    renderSeparator(3);

    // BAR GRAPH MATRIX : INDEX VALUE REFERENCE
    renderSubHeader(gradeScaling, "DefaultDemoSheet");
    renderSeparator(3);

    //#endregion

    //#region LOWER PANEL
    renderMasterListHeader(in_rctx.sessionPanelID);
    renderSeparator(3);

    renderMasterListRow(in_rctx.SessionSheet.masterlist, in_rctx.renderCellIndex, in_rctx.renderCellX, in_rctx.sessionPanelID);

    renderSeparator(4);

    //#endregion

    printf("\t[ Command Log ] : ");
    printf("%s", commandLog[0]);
}

// Utils
void clearScreen(){
    // Clear screen function is isolated for non-win32 clrscr adaptations
    system(WINCLR);
}
void indentCursor(short spaces){
    for (int i = 0; i < spaces; ++i) {
        printf("\t");
    }
}
void generateGraph(Sheetctx in_sctx){
    //#region Sample Data
    int     unsortedGradeRounds[10][2] = {
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
    //#endregion

    // Fetch ctx
    size_t size = sizeof(in_sctx.masterlist) / sizeof(in_sctx.masterlist[0]);

    // Generate Graph Reference Table
    int     studentCountReference[11][2] = {0};
    for (int y = 0; y < 11; ++y) {
        // MATCH MATRIX[N][0] WITH GRADE SCALING
        studentCountReference[y][0] = gradeScaling[y];
    }
    // Fetch no. of students within grade range
    for (int y = 0; y < 11; ++y) {
        for (int x = 0; x < 40; ++x) {
            if ((in_sctx.masterlist[x].value >= studentCountReference[y][0]) &&
                // GRADE IS LESS THAN LOWER GRADE TABLE
                (in_sctx.masterlist[x].value < studentCountReference[y+1][0])){
                studentCountReference[y][1]++;
            }
        }
    }
    //#region Legacy Code
//    for (int y = 0; y < 11; ++y) {
//        for (int x = 0; x < 11; ++x) {
//            if(
//                // GRADE ATTAINED IS LESS/EQUAL TO GRADE TABLE
//                    (unsortedGradeRounds[x][0] >= studentCountReference[y][0]) &&
//                    // GRADE IS LESS THAN LOWER GRADE TABLE
//                    (unsortedGradeRounds[x][0] < studentCountReference[y+1][0])){
//
//                studentCountReference[y][1] += unsortedGradeRounds[x][1];
//            }
//        }
//    }

//    for (int i = 0; i < 11; ++i) {
//        printf("%d - %d\n", studentCountReference[i][0], studentCountReference[i][1]);
//    }

//    for (int i = 0; i < 11; ++i) {
//        printf("%d - %d\n", studentCountReference[i][0], studentCountReference[i][1]);
//    }
    //#endregion

    //#region MATRIX GENERATOR

    /*  RENDER METHOD
        Renders characters from top to bottom, left to right
        Y coord decrements from indexCount to 0
        X coord increments from indexValue[0] to indexValue[MAX]
        Cell value compares to 2 arrs studentScaling[] > y & gradeScaling[] > x
    */

    for (int y = 9; y >= 0; y--) {

        int inverseY = 0; // INVERSE Y FOR GRADE SCALING
        char* barSymbol = "█";

        for (int x = 0; x < 11; ++x) {

            if( (
                    // CHECK IF LATCHED ON CORRECT GRADE COLUMN

                    // NUMBER OF INDEXES ARE LESS/EQUAL THAN SCALE BUT HIGHER THAN PREV. SCALE
                    (studentCountReference[x][1] <= studentScaling[y]) &&
                    (studentCountReference[x][1] > studentScaling[y-1]))){

                matrixGraph[y][x] = barSymbol;

            } else {
                matrixGraph[y][x] = " ";
            }

            // FILL IN GAPS BASED ON HIGHEST POINT
            if (matrixGraph[y+1][x] == barSymbol){
                matrixGraph[y][x] = barSymbol;
            }
        }

        inverseY++;
    }
    //#endregion
} //TODO FIXED

// Panels
void renderHeader(Renderctx in_rctx){
    short sessionStudentCount = sizeof(in_rctx.SessionSheet.masterlist) / sizeof(in_rctx.SessionSheet.masterlist[0]);

    if(in_rctx.sessionPanelID == 1){
        printf("\t|\x1B[38;5;16m\x1B[48;5;7m");
        printf("                       - Data Sheet -                      ");
        printf("\x1B[38;5;15m\x1B[48;5;0m|");
    } else {
        printf("\t│\t\t\t- Data Sheet -\t\t\t    │");
    }

    if(in_rctx.sessionPanelID == 2){
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("     - Top 10 Rankings / %4d -    ", sessionStudentCount);
        printf("\x1B[38;5;15m\x1B[48;5;0m");

        printf("|\x1B[38;5;16m\x1B[48;5;7m");
        printf("   Score   ");
        printf("\x1B[38;5;15m\x1B[48;5;0m|\n");
    } else {
        printf("     - Top 10 Rankings / %4d -    ", sessionStudentCount);
        printf("|   Score   |\n");
    }

} //TODO FIXED
void renderSubHeader(){
    // INDENT
    printf("\t│    ");

    for (int i = 0; i < 11; i++) {
        printf("|%4d", gradeScaling[i]);
    }

    printf("│ Sheet Name: %-30s    │\n", sheetName);

    //#region Legacy Code
    //    printf("\t|    |%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d| Sheet Name: %-18s \t|\t    |\n",
    //           gradeScaling[0],
    //           gradeScaling[1],
    //           gradeScaling[2],
    //           gradeScaling[3],
    //           gradeScaling[4],
    //           gradeScaling[5],
    //           gradeScaling[6],
    //           gradeScaling[7],
    //           gradeScaling[8],
    //           gradeScaling[9],
    //           gradeScaling[10],
    //           sheetName);
    //#endregion
} //TODO NOTHING TO CHANGE

void renderMatrixRankerRow(char* rg_names[10], short* rg_grades, Renderctx in_rctx){

    // Fetch ctx
    short selectionID = in_rctx.renderCellIndex;
    short panelID = in_rctx.sessionPanelID;
    char selectionX = in_rctx.renderCellX;

    uint8_t inverseY = 0;

    // Y AXIS
    for (int y = 9; y >= 0; y--) {
        printf("\t");
        printf("│%4d│", studentScaling[y]);

        // X AXIS
        for (int x = 0; x < 11; ++x) {

            printf(" %s%s ", matrixGraph[y][x], matrixGraph[y][x]);

            if(x != 10){
                printf(" ");
            }
        }

        if((panelID == 2) && (selectionID == inverseY)){
            switch (selectionX) {
                case 'X':
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    &rg_names[inverseY] != NULL ? printf("  • %-27s    ", rg_names[inverseY]):
                    printf("  • %-27s    ", " ");

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    &rg_grades[inverseY] != NULL ? printf("   %4d    ", rg_grades[inverseY]) :
                    printf("   %4s    ", " ");

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                case 'L':
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    &rg_names[inverseY] != NULL ? printf("  • %-27s    ", rg_names[inverseY]):
                    printf("  • %-27s    ", " ");

                    printf("\x1B[38;5;15m\x1B[48;5;0m");

                    &rg_grades[inverseY] != NULL ? printf("   %4d    ", rg_grades[inverseY]) :
                    printf("   %4s    ", " ");
                    break;

                case 'R':
                    &rg_names[inverseY] != NULL ? printf("  • %-27s    ", rg_names[inverseY]):
                    printf("  • %-27s    ", " ");

                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    &rg_grades[inverseY] != NULL ? printf("   %4d    ", rg_grades[inverseY]) :
                    printf("   %4s    ", " ");

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                default:
                    rg_names != NULL && rg_grades != NULL ? printf("│  • %-27s    │   %4d    │\n", rg_names[inverseY], rg_grades[inverseY]):
                    printf("│  • %-27s    │   %4s    │\n", " ", " ");
                    break;
            }
        } else {
            rg_names != NULL && rg_grades != NULL ? printf("│  • %-27s    │   %4d    │\n", rg_names[inverseY], rg_grades[inverseY]):
            printf("│  • %-27s    │   %4s    │\n", " ", " ");
        }

        inverseY++;
    }

    //#region LEGACY CODE
//    for (int i = 0; i < rowScale; ++i) {
//        printf("\t|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|  • Barack Obama \t\t\t|    100    |\n",
//               studentScaling[i],
//               bottom[0],
//               bottom[1],
//               bottom[2],
//               bottom[3],
//               bottom[4],
//               bottom[5],
//               bottom[6],
//               bottom[7],
//               bottom[8],
//               bottom[9],
//               bottom[10]);
//    }
//#endregion

} //TODO FIXED

void renderMasterListHeader(short panelID){
    if(panelID == 3){
        printf("\t│");
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("                               - Student Submission List -                                     ");
        printf("\x1B[38;5;15m\x1B[48;5;0m");

        printf("│");
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("           ");
        printf("\x1B[38;5;15m\x1B[48;5;0m");
        printf("│\n");

    } else {
        printf("\t│\t\t\t\t- Student Submission List -\t\t\t\t\t│           │\n");
    }
}
void renderMasterListRow(Index sctx_masterlist[], short selectionID, char selectionX, short panelID){
    for (int i = 0; i < 10; ++i) {
        if (panelID == 3 && selectionID == i){
            switch (selectionX) {
                case 'X':
                    printf("\t|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf(" • %-90s  ", sctx_masterlist[i].indexName);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", sctx_masterlist[i].value);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                case 'L':
                    printf("\t|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf(" • %-90s  ", sctx_masterlist[i].indexName);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("|   %4d    │\n", sctx_masterlist[i].value);
                    break;

                case 'R':
                    printf("\t| • %-90s  |", sctx_masterlist[i].indexName);
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", sctx_masterlist[i].value);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                default:
                    defaultMasterListRow(sctx_masterlist[i].indexName, sctx_masterlist[i].value);
                    break;
            }
        } else defaultMasterListRow(sctx_masterlist[i].indexName, sctx_masterlist[i].value);

    }
}
void defaultMasterListRow(char* indexName, int indexVal){
    printf("\t| • %-90s  |   %4d    │\n", indexName, indexVal);
}

void terminatePrompt(){
    exit(0);
}

void renderWhiteSpace(int spaceSize){
    for (int i = 0; i < spaceSize; ++i) {
        printf("\n");
    }
}
void renderSeparator(short id){
    if(id == 1){
        puts("\t─────────────────────────────────────────────────────────────────────────────────────────────────────────────");
    } else
    if (id == 2){
        puts("\t┌───────────────────────────────────────────────────────────────────────────────────────────────────────────┐");
    } else
    if (id == 3){
        puts("\t├───────────────────────────────────────────────────────────────────────────────────────────────────────────┤");
    } else
    if (id == 4){
        puts("\t┕───────────────────────────────────────────────────────────────────────────────────────────────────────────┘");
    }
//    puts("\t-------------------------------------------------------------------------------------------------------------");

}


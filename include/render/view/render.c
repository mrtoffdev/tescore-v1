<<<<<<< HEAD
#include <stdio.h>
#include <conio.h>

#include "render.h"

#define MAX_PASS_CHAR 30

void refreshFrame(){

    printf("\tTesting Render Frame\n");

    int navIndex = 1;
    int maxBackSpace = 0;
    int passChar = 0;

    printf("----  Renderer Debug: ----\n");
    printf("-----------------------------------\n"
           "|                                 |\n");
    printf("-----------------------------------");
    printf("\x1b[1A");
    printf("\x1b[33D");

    while (navIndex != EOF){
        navIndex = _getch();

        maxBackSpace = maxBackSpace < 0 ? 0 : maxBackSpace;

        if (navIndex != 8 && passChar <= MAX_PASS_CHAR){
            maxBackSpace++;
            passChar++;
            printf("%c",navIndex);
        }

        if (navIndex == 8 && maxBackSpace > 0){
            maxBackSpace--;
            printf("\x1b[1D");
            printf(" ");
            printf("\x1b[1D");
        }
    }

}
// Notes:
// #include <windows.h>
// SetConsoleOutputCP(CP_UTF8);
=======
/*========================================
      FRAME RENDERING
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "render.h"
#include "../../proc/proc.h"
#include "../../io/io.h"

#define DEBUGMODE 0

// CLEAR SCREEN DEFS
#define WINCLR "cls"
#define GNUCLR "clr"
#define REGEXCLR1 "\e[1;1H\e[2J"
#define REGEXCLR2 "\x1b[2J\x1b[H"

int         gradeScaling[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
            studentScaling[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
char*       sheetName = " ";
char*       matrixGraph[10][11];

// Framebuffer
void refreshFrame(Renderctx* in_rctx, Sheetctx* in_sctx, char commandLog[10][509], uint8_t rd_frameID){
    // Process: Sheetctx >> RankerModule == Return: Index[10](Ranked) >>
    // Generator == Index[i].name(char) Index[i].value(char) == ctx_masterlist[i][i]
    //#region Reset Screen
    clearScreen();
    renderWhiteSpace(3);
    //#endregion

    // Main Frame
    if (rd_frameID == 0){
        //#region INITIALIZE DATA
        // FETCH CTX
        size_t size_chk = util_fetchmastersize(*in_sctx);
        sheetName = in_sctx->name;

        if (DEBUGMODE == 1) {
            printf("Current RenderIndex: %d\n", in_rctx->renderCellIndex);
            printf("Masterlist Size: %d\n", util_fetchmastersize(*in_sctx));
            printf("Current Cell Selection: %c\n", in_rctx->renderCellX);
            printf("Current Operation Mode: %d\n", in_rctx->operationMode);
            DEBUGMODE == 1 ? printf("Estimated Masterlist Size: %d\n", size_chk) : 0;
        }

        //#region Legacy Deconstructor
//    // MASTERLIST DECONSTRUCTOR
//    char* ctx_masterlist[size_chk][2]; // Local Masterlist in String Format
//
//    DEBUGMODE == 1 ? printf("\nChecking Data: \n", size_chk): 0;
//    for (int i = 0; i < size_chk; ++i) {
//        if ((in_sctx->masterlist[i].indexName[0] > 64 && in_sctx->masterlist[i].indexName[0] < 90) ||
//            (in_sctx->masterlist[i].indexName[0] > 96 && in_sctx->masterlist[i].indexName[0] < 123)){
//
//            DEBUGMODE == 1 ? printf("Starting char found: %c Masterlist Size: %d\n", in_sctx->masterlist[i].indexName[0], i+1) : 0;
//            ctx_masterlist[i][0] = in_sctx->masterlist[i].indexName;
//
//            int gr_val = in_sctx->masterlist[i].value;
//            char* temp = malloc(3);
//            itoa(gr_val, temp, 10);
//            ctx_masterlist[i][1] = temp;
//        } else {
//            ctx_masterlist[i][0] = " ";
//            ctx_masterlist[i][1] = " ";
//        }
//    }
//
//    // Print Fetched Data
//    if (DEBUGMODE == 1){
//        printf("\n\nFetched Data: %d\n", size_chk);
//        for (int i = 0; i < size_chk; ++i) {
//            printf("%s : %s\n", ctx_masterlist[i][0], ctx_masterlist[i][1]);
//        }
//    }
        //#endregion

        // -> CALL SORT FUNCTIONS <-

        // DEBUG: Print Merge Sorted Masterlist
        if (DEBUGMODE == 1) {
            printf("\n\nMergesort Out: \n", size_chk);
            for (int i = 0; i < size_chk; ++i) {
                printf("%s : %d\n", in_sctx->masterlist[i].indexName, in_sctx->masterlist[i].value);
            };
        }

        // RANKER SORT -------------------------------------------------------------
        Index out_ranked[10];
        module_ranksort(*in_sctx, out_ranked);

        // DEBUG: Print received data from Ranker Mod
        if (DEBUGMODE == 1) {
            puts("Received from Ranker:\n\n");
            for (int i = 0; i < 10; ++i) {
                printf("%s : %d\n", out_ranked[i].indexName, out_ranked[i].value);
            }
            putchar('\n');
        }

        // RANKER DECONSTRUCTOR
        char rg_collection[10][2][MAXNAMECHARLIMIT];

        if (size_chk >= 10) {

            for (int i = 0; i < 10; ++i) {
                char int_ctr[4];
                strcpy(int_ctr, " "); // clear container
                int rankval = out_ranked[i].value;
                snprintf(int_ctr, 4, "%d", rankval);

                size_t wordsize = strlen(out_ranked[i].indexName);
                strncpy(rg_collection[i][0], out_ranked[i].indexName, wordsize);
                rg_collection[i][0][wordsize] = '\0';
                strncpy(rg_collection[i][1], int_ctr, strlen(out_ranked[i].indexName));
                strncat(rg_collection[i][1], "\0", 1);
            }

        } else if (size_chk < 10) {

            for (int i = 0; i < size_chk; ++i) {
                char int_ctr[4];
                strcpy(int_ctr, " "); // clear container
                int rankval = out_ranked[i].value;
                snprintf(int_ctr, 4, "%d", rankval);

                size_t wordsize = strlen(out_ranked[i].indexName);
                strncpy(rg_collection[i][0], out_ranked[i].indexName, strlen(out_ranked[i].indexName));
                rg_collection[i][0][wordsize] = '\0';
                strncpy(rg_collection[i][1], int_ctr, strlen(out_ranked[i].indexName));
                strncat(rg_collection[i][1], "\0", 1);
            }
            for (size_t i = size_chk; i < 10; ++i) {
                strncpy(rg_collection[i][0], " \0", 2);
                strncpy(rg_collection[i][1], " \0", 2);
            }
        }

        // DEBUG: Print received data in rg_collection
        if (DEBUGMODE == 1) {
            puts("Deconstructed from Ranker:");
            for (int i = 0; i < 10; ++i) {
                printf("%s : %s\n", rg_collection[i][0], rg_collection[i][1]);
            }
            putchar('\n');
        }
        //#endregion

        //#region UPPER PANEL
        renderSeparator(2);
        renderHeader(*in_rctx, *in_sctx);
        renderSeparator(3);

        generateGraph(*in_sctx); // Prep graph for matrixranker

        renderMatrixRankerRow(rg_collection, *in_rctx); // Render prepped graph

        renderSeparator(3);

        // BAR GRAPH MATRIX : INDEX VALUE REFERENCE
        renderSubHeader(gradeScaling, "DefaultDemoSheet");
        renderSeparator(3);
        //#endregion
        //#region LOWER PANEL
        renderMasterListHeader(in_rctx->sessionPanelID);
        renderSeparator(3);

        renderMasterListRow(in_sctx->masterlist, *in_rctx);

        renderSeparator(4);

        //#endregion

        printf("\t[ Command Log ] : ");
        printf("%s", commandLog[0]);
    }
    else
    if (rd_frameID == 1){
        frame_helperpanel();

    }
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
    // Fetch ctx
    size_t size = util_fetchmastersize(in_sctx);

    // Generate Graph Reference Table
    int studentCountReference[11][2] = {0};
    for (int y = 0; y < 11; ++y) {
        // MATCH MATRIX[N][0] WITH GRADE SCALING
        studentCountReference[y][0] = gradeScaling[y];
    }
    // Fetch no. of students within grade range
    for (int y = 0; y < 11; ++y) {
        for (int x = 0; x < size; ++x) {
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
void frame_helperpanel(){
    renderWhiteSpace(3);
    renderSeparator(2);
    renderWhiteSpace(3);
    printf("\t\t  - [H]                    Show Helper Panel\n\n");
    printf("\t\t  - [1][2][3]              1: Graph Panel 2: Ranking Panel 3: Masterlist\n");
    printf("\t\t  - [W][S]                 Move cursor up | Move cursor down\n");
    printf("\t\t  - [A][D]                 Move cursor left | Move cursor right (Only in Editing Mode)\n");
    printf("\t\t  - [T]                    Create New Cell\n");
    printf("\t\t  - [E]                    Editing Mode\n");
    printf("\t\t  - [Q]                    Exit Editing Mode / Cancel Delete Cell / Quit Program\n");
    printf("\t\t  - [R]                    Delete Cell\n");
    printf("\n\n\n\n\t\t\t\t\tPress Spacebar [_] to Exit Helper Panel\n");
    renderWhiteSpace(3);
    renderSeparator(4);
    renderWhiteSpace(3);
}
void renderHeader(Renderctx in_rctx, Sheetctx in_sctx){
    size_t sessionStudentCount = util_fetchmastersize(in_sctx);

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
        printf("|%-4d", gradeScaling[i]);
    }

    printf("│ Sheet Name: %-30s    │\n", sheetName);

} //TODO NOTHING TO CHANGE

void renderMatrixRankerRow(char rg_collection[][2][MAXNAMECHARLIMIT], Renderctx in_rctx){

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

                    printf("  • %-29s  ", &rg_collection[inverseY][0]);

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    printf("   %4s    ", &rg_collection[inverseY][1]);

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                case 'L':
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    printf("  • %-29s  ", &rg_collection[inverseY][0]);

                    printf("\x1B[38;5;15m\x1B[48;5;0m");

                    printf("   %4s    ", &rg_collection[inverseY][1]);
                    break;

                case 'R':
                    printf("  • %-29s  ", &rg_collection[inverseY][0]);

                    printf("\x1B[38;5;16m\x1B[48;5;7m");

                    printf("   %4s    ", &rg_collection[inverseY][1]);

                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                default:
                    printf("│  • %-29s  │   %4s    │\n", &rg_collection[inverseY][0], &rg_collection[inverseY][1]);
                    break;
            }
        } else {
            printf("│  • %-29s  │   %4s    │\n", &rg_collection[inverseY][0], &rg_collection[inverseY][1]);
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

void renderMasterListRow(Index sctx_masterlist[], Renderctx in_rctx){
    // Fetch ctx
    size_t selectionID = in_rctx.renderCellIndex;
    size_t panelID = in_rctx.sessionPanelID;
    char selectionX = in_rctx.renderCellX;

    // Adjust masterlist buffer position based on selection

    for (size_t i = in_rctx.buffer_start; i < in_rctx.buffer_end; ++i) {
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

>>>>>>> main

/*========================================
      FRAME RENDERING
      Author: Christopher Abadillos Jr.
  ========================================*/

/* RENDERING SYSTEM

    FUNCTION CALLS
        - refreshFrame()    : Renders the main interactive GUI for the first time
        - terminatePrompt() : Renders the program termination prompt

    BAR GRAPH - 2D Char Matrix System
        - Divide the number of students into 10
            - If divisible by 10, set all notches with $Quotient increments
            - If not divisible by 10, divide by 9, set all notches with $Quotient increments, and set the last / highest notch to remainder
                - e.g. 81 =

    REFRESHING FRAMES
        - Refresh call will re-render all three panels
        - refreshFrame() will also be the primary call when rendering the panels for the first time

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "render.h"

//#region PRIVATE PROTS
void generateGraph();
//#endregion

//#region GLOBAL VARS
DATASHEET   RAWDEMOSHEET;
SUBSHEET    RAWUNSORTEDSHEET,
            RAWSORTEDSHEET,
            RAWMASTERLISTSHEET;

int         gradeScaling[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
            studentScaling[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

char*       sheetName;
char*       matrixGraph[10][11];
//#endregion

// =========== MAIN PANELS ===========
void refreshFrame(DATASHEET sessionSheet, char* commandLog){

    /* REFRESH FRAME SEQUENCE
        + Start Benchmark Clock
        + Clear Screen Buffer
        + Render UI Elements
            - Separator
            - Header (Number of Students)
            - Separator
            - Upper Rows
                - x10 formatted lines
            - Separator
            - Sub Header
            - Separator
                - x10 formatted lines
        + Display Command Log
            - Format: <TimeLog><Message

        NOTE:
            INDEX COUNT INCREMENTS FROM B TO T > SIDE OF GRAPH
                ARR[] INCREMENTS FROM END TO START
            INDEX VALUE INCREMENTS FROM R TO L > BOTTOM OF GRAPH
    */

    // UNIT TEST CLOCKS
    clock_t refreshFrameExecTimeBegin = clock();

    // CLEAR SCREEN BEFORE SHOWING NEW FRAME
    clearScreen();

    // FETCH TOTAL INDEX COUNT : DIV TOTAL BYTE SIZE OF COLLECTION BY ELEMENT BYTE SIZE
    int indexCount = sizeof (sessionSheet.masterlistCollection.container) / sizeof (sessionSheet.masterlistCollection.container[0]);

    renderWhiteSpace(3);

    //#region UPPER PANEL

        // HEADER
        renderSeparator();
        renderHeader(indexCount);
        renderSeparator();

        // PANELS : BAR GRAPH MATRIX & TOP RANKERS

        generateGraph();
        renderMatrixRankerRow(matrixGraph);

        renderSeparator();

        // BAR GRAPH MATRIX : INDEX VALUE REFERENCE
        renderSubHeader(gradeScaling, "DefaultDemoSheet");

        renderSeparator();


    //#endregion

    //#region LOWER PANEL

        renderMasterListHeader();
        for(int i = 0; i < 10; i++){
            renderMasterListRow();
        }
        renderSeparator();

    //#endregion

    clock_t refreshFrameExecTimeEnd = clock();

    // COMMAND LOG
    printf("\t[ Command Log ] : ");
    if(commandLog == NULL){
        printf("refreshFrame() Execution Time: %f seconds\n", (((double)refreshFrameExecTimeEnd - refreshFrameExecTimeBegin) / CLOCKS_PER_SEC));
    } else {
        printf("%s", commandLog);
    }


}

//#region =========== PROMPTS ===========
void terminatePrompt(){

}
//#endregion

//#region =========== UI ELEMENTS ===========
void clearScreen(){
//    printf("\e[1;1H\e[2J");
    system("cls");
//    printf("\x1b[2J\x1b[H");
}

void renderWhiteSpace(int spaceSize){
    for (int i = 0; i < spaceSize; ++i) {
        printf("\n");
    }
}

void renderSeparator(){
    puts("\t-------------------------------------------------------------------------------------------------------------");

}

void indentCursor(){
    printf("\t");
}

void generateGraph(){

    //#region INIT LOCAL VARIABLES

    // RAW GRADE SHEET COLLECTION
    int     unsortedGradeRounds[10][2] = {
            {99, 2},
            {98, 4},
            {100, 10},
            {23, 3},
            {80, 5},
            {72, 7},
            {94, 10},
            {87, 2},
            {69, 3},
            {91, 9}
    };
    //#endregion

    //#region COUNT REFERENCE TABLE : For Rounding up IndexCount per IndexValue

    int     studentCountReference[11][2] = {0};

    for (int y = 0; y < 11; ++y) {
        // MATCH MATRIX[N][0] WITH GRADE SCALING
        studentCountReference[y][0] = gradeScaling[y];
    }

    for (int y = 0; y < 11; ++y) {
        for (int x = 0; x < 11; ++x) {
            if(
                // GRADE ATTAINED IS LESS/EQUAL TO GRADE TABLE
                (unsortedGradeRounds[x][0] >= studentCountReference[y][0]) &&
                // GRADE IS LESS THAN LOWER GRADE TABLE
                (unsortedGradeRounds[x][0] < studentCountReference[y+1][0])){

                studentCountReference[y][1] += unsortedGradeRounds[x][1];
            }
        }
    }

//    for (int i = 0; i < 11; ++i) {
//        printf("%d - %d\n", studentCountReference[i][0], studentCountReference[i][1]);
//    }

    //#endregion

    //#region TEST SNIPPETS
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
}
//#endregion

//#region =========== UI PANELS ===========
void renderHeader(int sessionStudentCount){
    printf("\t|\t\t\t- Data Sheet -\t\t\t    |\t - Top 10 Students / %4d - \t|   Score   |\n",
           sessionStudentCount);
}

void renderSubHeader(){
    int bottom[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // INDENT
    printf("\t|    ");

    for (int i = 0; i < 11; i++) {
        printf("|%4d", gradeScaling[i]);
    }

    printf("| Sheet Name: %-18s \t|\t    |\n", sheetName);

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
}

void renderMatrixRankerRow(){

    for (int y = 9; y >= 0; y--) {
        int inverseY = 0;
        printf("\t");
        printf("|%4d|", studentScaling[y]);

        for (int x = 0; x < 11; ++x) {

            printf(" %s%s ", matrixGraph[y][x], matrixGraph[y][x]);

            if(x != 10){
                printf(" ");
            }
        }

        printf("|  • Barack Obama \t\t\t|    100    |\n");
        inverseY++;
    }

    //#region test code
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

}


void renderMasterListHeader(){
    printf("\t|\t\t\t\t- Student Submission List -\t\t\t\t\t|           |\n");
}

void renderMasterListRow(){
    printf("\t| • %-90s  |    %4d   |\n", "Michael Reeves", 23);
}
//#endregion

//#region =========== TESTS ===========

//#endregion

//#region =========== REFERENCES ===========
/* ENABLING UTF8 SUPPORT FOR MICROSOFT WINDOWS CONSOLES

    #include <windows.h>
    SetConsoleOutputCP(CP_UTF8);

*/

/*  ANSI REFERENCES
    BLOCK CHARACTER : █

 */
//#endregion
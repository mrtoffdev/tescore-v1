/*========================================
      FRAME RENDERING
      Author: Christopher Abadillos Jr.
  ========================================*/

//#region =========== DOCS ===========

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

/* ENABLING UTF8 SUPPORT FOR MICROSOFT WINDOWS CONSOLES

    #include <windows.h>
    SetConsoleOutputCP(CP_UTF8);

*/

/*
    ANSI REFERENCES

        BLOCK CHARACTER     : █
        VERTICAL SEPARATOR  : │
*/

//#endregion

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "render.h"
#include "../../sort/ranker/rankerModule.h"

//#region GLOBAL VARS
int         gradeScaling[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
            studentScaling[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
char*       sheetName = "SHORTNAME";
char*       matrixGraph[10][11];
//#endregion

//#region =========== UI UTILS ===========

void refreshFrame(Renderctx ctx, char commandLog[10][509]){

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

    // PREP CONSOLE WINDOW FOR NEW FRAME
    clearScreen();
    renderWhiteSpace(3);

    // FETCH TOTAL INDEX COUNT : DIV TOTAL BYTE SIZE OF COLLECTION BY ELEMENT BYTE SIZE
    int indexCount = sizeof (ctx.SessionSheet.masterlistCollection.container) / sizeof (ctx.SessionSheet.masterlistCollection.container[0]);

    //#region UPPER PANEL

    // HEADER
    renderSeparator(2);
    renderHeader(ctx);
    renderSeparator(3);

    // PANELS : BAR GRAPH MATRIX & TOP RANKERS
    generateGraph();

    // Ranker Implementation
    SUBSHEET sampleSubsheet =
    {
        1,
        2,
        {   
             {"Fridge Grills", 85},
             {"Window Tab Post", 92},
             {"Roof Leaf", 96},
             {"Coconut Rock", 79},
             {"Shirt Switch Root", 86},
             {"Screen Fruit", 88},
             {"White Fan", 94},
             {"Light Wall", 82},
             {"Cloud Plane", 77},
             {"Escaped Post", 97}
        }
    };

    SUBSHEET sample2Subsheet =
    {
        1,
        2,
        {   
             {"Fridge Grills", 85},
             {"Window Tab Post", 92},
             {"Roof Leaf", 96},
             {"Coconut Rock", 79},
             {"Shirt Switch Root", 86},
             {"Screen Fruit", 88},
             {"White Fan", 94},
             {"Light Wall", 82},
             {"Cloud Plane", 77},
             {"Escaped Post", 97}
        }
    };

    DATASHEET sampleSheet = 
    {
        "name",
        "author",
        sampleSubsheet,
        sample2Subsheet,
    };

    SUBSHEET returnedSubsheet = ranker(sampleSheet.rankedCollection);

    // PLACEHOLDER
    char* renderableIndexNames[10] = {
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
            "Leni Robredo",
    };

    int renderableIndexValues[10] = {
            100,
            100,
            100,
            100,
            100,
            100,
            100,
            100,
            100,
            100,
    };

    // still part of ranker implementation
    for(int i = 0; i<10; i++)
    {
        renderableIndexNames[i] = returnedSubsheet.container[i].indexName;
        renderableIndexValues[i] = returnedSubsheet.container[i].value;
        printf("%-30s\t%d\n", renderableIndexNames[i], renderableIndexValues[i]);
    }

    renderMatrixRankerRow(
            renderableIndexNames,
            renderableIndexValues,
            ctx.renderCellIndex,
            ctx.renderCellX,
            ctx.sessionPanelID);

    renderSeparator(3);

    // BAR GRAPH MATRIX : INDEX VALUE REFERENCE
    renderSubHeader(gradeScaling, "DefaultDemoSheet");
    renderSeparator(3);

    //#endregion

    //#region LOWER PANEL
    renderMasterListHeader(ctx.sessionPanelID);
    renderSeparator(3);


    renderMasterListRow("Keanu Reeves", 98, ctx.renderCellIndex, ctx.renderCellX, ctx.sessionPanelID);

    renderSeparator(4);

    //#endregion

    //#region COMMAND LOG

    clock_t refreshFrameExecTimeEnd = clock();

    printf("\t[ Command Log ] : ");
    if(commandLog[0] == NULL){
        float xTime = (float)(refreshFrameExecTimeEnd - refreshFrameExecTimeBegin) / CLOCKS_PER_SEC;;
        printf("refreshFrame() Execution Time: %f seconds\n", xTime);
    } else {
        printf("%s", commandLog[0]);
    }

    //#endregion

}

void clearScreen(){

    // ALTS
    //    printf("\e[1;1H\e[2J");
    //    printf("\x1b[2J\x1b[H");

    system("cls");
}

void indentCursor(short spaces){
    for (int i = 0; i < spaces; ++i) {
        printf("\t");
    }
}

void generateGraph(){

    //#region INIT LOCAL VARIABLES

    // RAW GRADE SHEET COLLECTION
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

void renderHeader(Renderctx ctx){
    short sessionStudentCount = 10; //TODO REMOVE / REPLACE
    if(ctx.sessionPanelID == 1){
        printf("\t|");
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("                       - Data Sheet -                      ");
        printf("\x1B[38;5;15m\x1B[48;5;0m");
        printf("|");
    } else {
        printf("\t│\t\t\t- Data Sheet -\t\t\t    │");
    }

    if(ctx.sessionPanelID == 2){
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("     - Top 10 Students / %4d -    ", sessionStudentCount);
        printf("\x1B[38;5;15m\x1B[48;5;0m");

        printf("|");
        printf("\x1B[38;5;16m\x1B[48;5;7m");
        printf("   Score   ");
        printf("\x1B[38;5;15m\x1B[48;5;0m");
        printf("|\n");
    } else {
        printf("     - Top 10 Students / %4d -    ", sessionStudentCount);
        printf("|   Score   |\n");
    }

}

void renderSubHeader(){
    int bottom[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

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
}

void renderMatrixRankerRow(char* indexNameContainer[10], int* indexValContainer, short selectionID, char selectionX, short panelID ){
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
                    printf("  • %-27s    ", indexNameContainer[inverseY]);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", indexValContainer[inverseY]);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                case 'L':
                    printf("│");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("  • %-27s    ", indexNameContainer[inverseY]);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│   %4d    │\n", indexValContainer[inverseY]);
                    break;

                case 'R':
                    printf("│  • %-27s    │", indexNameContainer[inverseY]);
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", indexValContainer[inverseY]);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                default:
                    printf("│  • %-27s    │   %4d    │\n", indexNameContainer[inverseY], indexValContainer[inverseY]);
                    break;
            }
        } else {
            printf("│  • %-27s    │   %4d    │\n", indexNameContainer[inverseY], indexValContainer[inverseY]);
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

}

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

void renderMasterListRow(char* indexName, int indexVal, short selectionID, char selectionX, short panelID){
    for (int i = 0; i < 10; ++i) {
        if (panelID == 3 && selectionID == i){
            switch (selectionX) {
                case 'X':
                    printf("\t|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf(" • %-90s  ", indexName);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", indexVal);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                case 'L':
                    printf("\t|");
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf(" • %-90s  ", indexName);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("|   %4d    │\n", indexVal);
                    break;

                case 'R':
                    printf("\t| • %-90s  |",indexName);
                    printf("\x1B[38;5;16m\x1B[48;5;7m");
                    printf("   %4d    ", indexVal);
                    printf("\x1B[38;5;15m\x1B[48;5;0m");
                    printf("│\n");
                    break;

                default:
                    defaultMasterListRow(indexName, indexVal);
                    break;
            }
        } else defaultMasterListRow(indexName, indexVal);

    }



}

void defaultMasterListRow(char* indexName, int indexVal){
    printf("\t| • %-90s  |   %4d    │\n", indexName, indexVal);
}

//#endregion


//#region =========== PROMPTS ===========

void terminatePrompt(){
    exit(0);
}

//#endregion

//#region =========== UI ELEMENTS ===========

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

//#endregion

//#region =========== TESTS ===========

//#endregion

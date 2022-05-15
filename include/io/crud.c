/*========================================
      CRUD OPERATIONS
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"

#define SIZE 10

// RENDER SYSTEM OPERATIONS
Renderctx render_init_ctx(DATASHEET sessionSheet){
    Renderctx ctx;
    // Initialize Default Values
    ctx.SessionSheet = sessionSheet;          // Fetch Sheet
    ctx.sheetName = "SheetName.dib";          // Default Sheet Name
    ctx.NAVKEY = '1';                         // Points to Default Panel Selection (Graph)
    ctx.handlerMode = 0;                      // 0 : Active Handler | 1 : Inactive Handler
    ctx.operationMode = 1;                  // 1 : View | 2 : Select | 3 : Edit
    ctx.sessionPanelID = 1;                 // ID of panel to render
    ctx.renderCellIndex = 1;                // Index of cursor in lists | Default: 1
    ctx.renderCellX = 'X';

    return ctx;
}

// DATASHEET OPERATIONS
void fetchData(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){

    char *collection[][5] = {};
    char *tempString;
    for (int i = 0; i < SIZE; i++){
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
            indexValueArr[i] = atoi(tempString);
            // print both name and int
            // printf("%s%d\n", name_parray[i], score_array[i]);
            lineCount++;
        }
        else
        {
            break;
        }
    }

}

void fetch_gradeTable(DATASHEET Datactx, int distributionTable[11][2]){
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

DATASHEET initSheetDemo(){

    DATASHEET return_dataSheet;
    return_dataSheet.author="admin";
    return_dataSheet.name="masterlist";

    // GENERATE CONTENTS
    for (short i = 0; i < 10; ++i) {

        INDEX insertIndex;
        char indexNameAppend[100] = "Jacob ";

        insertIndex.indexName = indexNameAppend;
        insertIndex.value = i * 12;

        return_dataSheet.rankedCollection.container[i] = insertIndex;
        return_dataSheet.masterlistCollection.container[i] = insertIndex;
    }

    return return_dataSheet;
}


void fetch_studentDistTable(DATASHEET Datactx){

}




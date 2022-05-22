//#region LEGACY =============
// DATASHEET OPERATIONS
//void fetchData(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){
//
//
//
//}
//void fetch_gradeTable(Sheetctx Datactx, int distributionTable[11][2]){
//    // Placeholder Data
//    uint8_t unsortedGradeRounds[10][2] = {
//            {99, 2},
//            {98, 4},
//            {100, 10},
//            {47, 26},
//            {80, 5},
//            {72, 7},
//            {94, 10},
//            {87, 2},
//            {69, 3},
//            {91, 9}
//    };
//
//    uint8_t gradeTable[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    uint8_t collection_size = sizeof unsortedGradeRounds / sizeof unsortedGradeRounds[0];
//
//    for (int y = 0; y < 11; ++y) {
//        // MATCH MATRIX[N][0] WITH GRADE SCALING
//        distributionTable[y][0] = gradeTable[y];
//    }
//
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
//}

// DEV TEST FUNCTION
//void file_InitMasterlist();
//#endregion
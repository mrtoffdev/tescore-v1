/*========================================
      FILE DECRYPTION
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "../render/view/render.h"

void testing(char* FileAddress){
    FILE *DIB = openFile(FileAddress);

    char *temp = malloc(MAXADDRLENGTH);
    fscanf(DIB, "%s", temp);
    puts("\n\n---------- Read File Contents ----------\n");
    printf("%s\n", temp);
    free(temp);
}

FILE* openFile(char* FileAddress){
    FILE *returnDIB;

    if ((returnDIB = fopen(FileAddress,"r")) == NULL){

        // default file prompt
        clearScreen();
        printf("Invalid Filename. Use default file? (y/n): ");

        char temp;
        scanf("%s", &temp);

        clearScreen();
        if((temp == 'Y') || (temp == 'y')){
            clearScreen();

            returnDIB = fopen(DEFAULTFILEADDRESS, "r");
            puts("Loaded default input file.");
            system("pause");
            return returnDIB;
        } else {
            clearScreen();
            puts("Cannot load file. Please enter a valid filename.");
            system("pause");
        }
    }

    clearScreen();
    return returnDIB;
}

DATASHEET fetchDataSheet(FILE* DIB, char* indexNameArr[], char* indexValueArr[], int lineCount){

    // SUBSHEET CONTAINERS
    SUBSHEET masterSheet;
    if(masterSheet.id != MASTERSHEETID)
        masterSheet.id = MASTERSHEETID;

    SUBSHEET rankerSheet;
    if(rankerSheet.id != RANKERSHEETID)
        rankerSheet.id = RANKERSHEETID;

    // DATASHEET CONTAINER
    DATASHEET outDataSheet;
    outDataSheet.masterlistCollection = masterSheet;
    outDataSheet.rankedCollection = rankerSheet;

    int collectionSize = 10;
    collectionSize = sizeof rankerSheet.container / sizeof rankerSheet.container[1];

//    char *collection[][collectionSize] = {};
    char *tempString;
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
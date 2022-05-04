#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../model/sheet.h"

#define SIZE 10

void append(){



}

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




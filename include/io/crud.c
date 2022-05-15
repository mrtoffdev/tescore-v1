/*========================================
      CRUD OPERATIONS
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../model/sheet.h"

#include "../sort/ranker/rankerModule.h"
#include "../sort/masterlist/alphaMergeSort.h"



#define SIZE 100

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


// TEST FUNCTIONS

DATASHEET initSheetDemo(){
    DATASHEET localInitSheet;
    SUBSHEET RAWUNSORTEDSHEET;
    SUBSHEET RAWSORTEDSHEET;
    SUBSHEET RAWMASTERLISTSHEET;
    localInitSheet.author="admin";
    localInitSheet.name="masterlist";
    
    char* renderableIndexNames[10] = {
            "Keni Lobredo",
            "Meni Nobredo",
            "Eeni Fobredo",
            "Qeni Robredo",
            "Oeni Pobredo",
            "Aeni Bobredo",
            "Seni Tobredo",
            "Geni Hobredo",
            "Ieni Jobredo",
            "Ceni Dobredo",
    };

    int renderableIndexValues[10] = {
            95,
            95,
            90,
            91,
            95,
            99,
            93,
            90,
            92,
            80,
    };

    // GENERATE CONTENTS
    /**for (short i = 0; i < 10; ++i) {
        INDEX insertIndex;
        char indexNameAppend[100] = "Jacob ";
//        sprintf(indexNameAppend, "%d", i);
        insertIndex.indexName = indexNameAppend;
        insertIndex.value = i * 12;

        localInitSheet.rankedCollection.container[i] = insertIndex;
        localInitSheet.masterlistCollection.container[i] = insertIndex;
    }**/
    
    // pass placeholder values into subsheet struct
    RAWUNSORTEDSHEET.size = 10;
    RAWUNSORTEDSHEET.id = 3; //unsorted ID
    for (int i=0; i<10; i++) {
		RAWUNSORTEDSHEET.container[i].indexName = renderableIndexNames[i];
		RAWUNSORTEDSHEET.container[i].value = renderableIndexValues[i];
	}
	
	// sort subsheet using ranker module
	RAWSORTEDSHEET = ranker(RAWUNSORTEDSHEET);//, 10);
	
	//sort masterlist
	alphaMergeSort(&RAWUNSORTEDSHEET, 0, 9);
	RAWMASTERLISTSHEET = RAWUNSORTEDSHEET;
	
	localInitSheet.rankedCollection = RAWSORTEDSHEET;
	localInitSheet.masterlistCollection = RAWMASTERLISTSHEET;

    return localInitSheet;
}




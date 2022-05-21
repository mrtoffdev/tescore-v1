/*========================================
      MASTERLIST SORT ALGORITHMS TESTS
      Author: Jerome Loria
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphaMergeSort.h"

int main(void) {
    
    int subsheetBasicSize = 10;

    // Testing Datasheet
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

    // testing modified code
    alphaMergeSort(&sampleSheet.masterlistCollection, 0, subsheetBasicSize-1);
    for (int i = 0; i<subsheetBasicSize; i++)
    {
        printf("%-30s\t%d\n", sampleSheet.masterlistCollection.container[i].indexName, sampleSheet.masterlistCollection.container[i].value);
    }
    
    return 0;
}

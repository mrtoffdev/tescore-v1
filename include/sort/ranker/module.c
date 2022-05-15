/*========================================
      TOP 10 RANKING SORT MODULE
      Author: Jovic Francis Rayco
  ========================================*/
#include <stdio.h>
#include <string.h>

#include "rankerModule.h"

//#region LOCAL FUNCTION PROTOTYPES
SUBSHEET ranker(SUBSHEET unsortedSubsheet);
void bubbleSort(char string_array[][LIMIT], short score_array[], int lines);
//#endregion

//#region Module Test
// int main(void)
// {
// // Sample subsheet
// /* NOTE:The initialization had two (or three) sets of curly braces since this is the least
// *  confusing/error prone way for me to say 'samplesubsheet.unsortedlist = {items}'. Using the latter
// *  leads to errors for some reason
// */
//    SUBSHEET sampleSubsheet =
//    {
//        1,
//        2,
//        {   
//             {"Fridge Grills", 85},
//             {"Window Tab Post", 92},
//             {"Roof Leaf", 96},
//             {"Coconut Rock", 79},
//             {"Shirt Switch Root", 86},
//             {"Screen Fruit", 88},
//             {"White Fan", 94},
//             {"Light Wall", 82},
//             {"Cloud Plane", 77},
//             {"Escaped Post", 97}
//        }
//    };

//    SUBSHEET sample2Subsheet =
//    {
//        1,
//        2,
//        {   
//             {"Fridge Grills", 85},
//             {"Window Tab Post", 92},
//             {"Roof Leaf", 96},
//             {"Coconut Rock", 79},
//             {"Shirt Switch Root", 86},
//             {"Screen Fruit", 88},
//             {"White Fan", 94},
//             {"Light Wall", 82},
//             {"Cloud Plane", 77},
//             {"Escaped Post", 97}
//        }
//    };

//     DATASHEET sampleSheet = 
//     {
//         "name",
//         "author",
//         sampleSubsheet,
//         sample2Subsheet,
//     };

//     /*
//     typedef struct  DATASHEET {
//     char*       name,
//                 author;
//     SUBSHEET    rankedCollection;
//     SUBSHEET    masterlistCollection;
//     } DATASHEET;
//     */

// // Passing the subsheet as an argument to the function and returning as a sorted subsheet
// SUBSHEET returnedSubsheet = ranker(sampleSheet.rankedCollection);

// // List is sorted at this point. Just printing the sorted subsheet //
// for (int i = 0; i<10; i++)
// {
//    printf("%-30s\t%d\n", returnedSubsheet.container[i].indexName, returnedSubsheet.container[i].value);
// }
// printf("\n");
// return 0;
// }
//#endregion

// NOTE: The argument here is passed by value. Do inform me if you want this to pass by reference.
SUBSHEET ranker(SUBSHEET unsortedSubsheet)
{
    SUBSHEET sortedSubsheet;
    int lines;
    size_t size = 0;
    
    for (int i = 0; unsortedSubsheet.container[i].indexName != NULL; i++)
    {
        size++;
    }

    short score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];
    for (int i = 0; i<size; i++)
    {
        score_array[i] = unsortedSubsheet.container[i].value;
        strcpy(name_parray[i], unsortedSubsheet.container[i].indexName);
    }

    bubbleSort(name_parray, score_array, size);

    // Placing the sorted values to the new subsheet
    for (int i = 0; i<size; i++)
    {
        sortedSubsheet.container[i].indexName = name_parray[i];
        sortedSubsheet.container[i].value = score_array[i];
    }

    SUBSHEET returnedSubsheet;
    for (int i = 0; i<10; i++)
    {
        returnedSubsheet.container[i].indexName = sortedSubsheet.container[i].indexName;
        returnedSubsheet.container[i].value = sortedSubsheet.container[i].value;
    }

    return returnedSubsheet;
}

void bubbleSort(char string_array[][LIMIT], short score_array[], int lines)
{
    int pass, i;
    short intSwap;
    char stringswap[LIMIT];

    for(pass = 1; pass < lines; pass++)
    {
        for(i = 0; i < lines-pass; i++)
        {
            // Sorts based on grades
            if(score_array[i] < score_array[i+1]) 
            {
                intSwap = score_array[i];
                score_array[i] = score_array[i+1];
                score_array[i+1] = intSwap;

                strcpy(stringswap, string_array[i]);
                strcpy(string_array[i], string_array[i+1]);
                strcpy(string_array[i+1], stringswap);
            }
            // Else if grades are equal, sort alphabetically
            else if ((score_array[i] == score_array[i+1]) && (strcmp(string_array[i], string_array[i+1]) > 0))
            {
                strcpy(stringswap, string_array[i]);
                strcpy(string_array[i], string_array[i+1]);
                strcpy(string_array[i+1], stringswap);
            }
        }
    }
}

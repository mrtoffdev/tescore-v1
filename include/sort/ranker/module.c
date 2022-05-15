/*========================================
      TOP 10 RANKING SORT MODULE
      Author: Jovic Francis Rayco
  ========================================*/
#include <stdio.h>
#include <string.h>

#include "rankerModule.h"

//#region Main
typedef struct record
{
    char* studentName;
    short int studentScore;
} record;

//typedef struct SUBSHEET
//{
//    record unsortedList[100];
//    /* NOTE: This is the only problem tbh if we really want dynamic sizes.
//    *  I also cannot use macro definitions here for some reason.
//    */
//} subsheet;

//#endregion

//#region Module Test
//int rankerModule(void)
//{
//// Sample subsheet
///* NOTE:The initialization had two (or three) sets of curly braces since this is the least
//*  confusing/error prone way for me to say 'samplesubsheet.unsortedlist = {items}'. Using the latter
//*  leads to errors for some reason
//*/
////    SUBSHEET sampleSubsheet =
////    {
////        {   // unsortedList
////            {"Harvar D Three Four Five", 100},
////            {"Ox Twelve", 100},
////            {"Tree Force", 21},
////            {"Four", 92},
////            {"Place", 90},
////            {"Reee Za", 92},
////            {"Ra", 96},
////            {"Eight", 90},
////            {"Nine", 100},
////            {"Ten", 88},
////            {"Eleven", 88},
////        }
////    };
////
//// Passing the subsheet as an argument to the function and returning as a sorted subsheet
////SUBSHEET sortedSubsheet = ranker(sampleSubsheet);
////
////// List is sorted at this point. Just printing the sorted subsheet //
////for (int i = 0; i<10; i++)
////{
////    printf("%-30s\t%d\n", sortedSubsheet.unsortedList[i].studentName, sortedSubsheet.unsortedList[i].studentScore);
////}
////printf("\n");
//return 0;
//}
//#endregion

//#region LOCAL FUNCTION PROTOTYPES
void bubbleSort(char string_array[][LIMIT], short score_array[], int lines);
//#endregion

// NOTE: The argument here is passed by value. Do inform me if you want this to pass by reference.
SUBSHEET ranker(SUBSHEET unsortedSubsheet)//, int size)
{
    SUBSHEET sortedSubsheet;
    int lines,
        size = 0;
    
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

    return sortedSubsheet;
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

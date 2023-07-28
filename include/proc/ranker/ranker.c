/*========================================
      TOP 10 RANKING SORT MODULE
      Author: Jovic Francis Rayco
  ========================================*/
#include <stdio.h>
#include <string.h>
#include "../proc.h"
#include "../../io/io.h"

#define DEBUGMODE 0

void bubbleSort(char string_array[][LIMIT_STRLEN], short score_array[], size_t lines);

void module_ranksort(Sheetctx in_sctx, Index out_ranked[10])
{
    // FETCH CTX
    size_t size = util_fetchmastersize(in_sctx);
    DEBUGMODE == 1 ? printf("Ranker Module - Received Size: %d\n", size): 0;

    // ISOLATE DATA FROM in_sctx TO TEMP CONTAINERS
    short scores[LIMIT_STUDENTS] = {0};
    char names[LIMIT_STUDENTS][LIMIT_STRLEN];

    for (int i = 0; i<size; i++)
    {
        scores[i] = in_sctx.masterlist[i].value;
        strcpy(names[i], in_sctx.masterlist[i].indexName);
    }

    if (DEBUGMODE == 1){
        printf("Received Data: \n");
        for (int i = 0; i < size; ++i) {
            printf("%s : %d\n", names[i], scores[i]);
        }

    }

    // CALL OUTSIDE FUNCTION FOR SORT
    bubbleSort(names, scores, size);

    // ISOLATE ONLY THE TOP 10
    for (int i = 0; i < 10; i++)
    {
        strcpy(out_ranked[i].indexName, names[i]);
        out_ranked[i].value = scores[i];
    }

}
void bubbleSort(char string_array[][LIMIT_STRLEN], short score_array[], size_t lines)
{
    short intSwap;
    char stringswap[LIMIT_STRLEN];

    for(int pass = 1; pass < lines; pass++)
    {
        for(int i = 0; i < lines-pass; i++)
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
            // Else if grades are equal, proc alphabetically
            else if ((score_array[i] == score_array[i+1]) && (strcmp(string_array[i], string_array[i+1]) > 0))
            {
                strcpy(stringswap, string_array[i]);
                strcpy(string_array[i], string_array[i+1]);
                strcpy(string_array[i+1], stringswap);
            }
        }
    }
}
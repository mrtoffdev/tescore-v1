#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define LIMIT 1000
// Top 10 student sorting algorithm.

typedef struct index
{
    char* studentName;
    short int studentScore;
} index;

typedef struct subsheet
{
    index unsortedList[100];
} subsheet;

void bubbleSort(char string_array[][LIMIT], int score_array[], int lines);
subsheet rankSorterMkII(subsheet subsheetvar);

int main(void)
{
    // Placeholder for arguments
    subsheet sampleSubsheet = 
    {
        {   // unsortedList
            {"Harvar D Three Four Five", 100}, 
            {"Ox Twelve", 100}, 
            {"Tree Force", 21}, 
            {"Four", 92}, 
            {"Place", 90},
            {"Reee Za", 92},
            {"Ra", 96},
            {"Eight", 90},
            {"Nine", 100},
            {"Ten", 88},
            {"Eleven", 88},
        }
    };
    
    subsheet sortedSubsheet = rankSorterMkII(sampleSubsheet);

    // // List is sorted at this point //
    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%d\n", sortedSubsheet.unsortedList[i].studentName, sortedSubsheet.unsortedList[i].studentScore);
    }
    printf("\n");
    return 0;
}

subsheet rankSorterMkII(subsheet subsheetvar)
{
    subsheet newSubsheet;
    int lines, i, size;
    for (int i = 0; subsheetvar.unsortedList[i].studentName != NULL; i++)
    {
        size++;
    }

    int score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];

    for (i = 0; i<size; i++)
    {
        score_array[i] = subsheetvar.unsortedList[i].studentScore;
        strcpy(name_parray[i], subsheetvar.unsortedList[i].studentName);
        lines++;
    }

    bubbleSort(name_parray, score_array, size);

    for (int i = 0; i<size; i++)
    {
        newSubsheet.unsortedList[i].studentScore = score_array[i];
        newSubsheet.unsortedList[i].studentName = name_parray[i];
    }

    return newSubsheet;
}

// // needs amount of lines
void bubbleSort(char string_array[][LIMIT], int score_array[], int lines)
{
    int pass, size, i, intswap;
    char stringswap[LIMIT];

    for(pass = 1; pass < lines; pass++)
    {
        for(i = 0; i < lines-pass; i++)
        {
            if(score_array[i] < score_array[i+1])
            {
                intswap = score_array[i];
                score_array[i] = score_array[i+1];
                score_array[i+1] = intswap;

                strcpy(stringswap, string_array[i]);
                strcpy(string_array[i], string_array[i+1]);
                strcpy(string_array[i+1], stringswap);
            }
            else if ((score_array[i] == score_array[i+1]) && (strcmp(string_array[i], string_array[i+1]) > 0))
            {
                strcpy(stringswap, string_array[i]);
                strcpy(string_array[i], string_array[i+1]);
                strcpy(string_array[i+1], stringswap);
            }
        }
    }
}

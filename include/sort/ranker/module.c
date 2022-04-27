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
    /* NOTE: This is the only problem tbh if we really want dynamic sizes. 
    *  I also cannot use macro definitions here for some reason.
    */
} subsheet;

void bubbleSort(char string_array[][LIMIT], int score_array[], int lines);
subsheet ranker(subsheet subsheetvar);

int main(void)
{
    // Sample subsheet
    /* NOTE:The initialization had two (or three) sets of curly braces since this is the least
    *  confusing/error prone way for me to say 'samplesubsheet.unsortedlist = {items}'. Using the latter
    *  leads to errors for some reason
    */
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
    
    // Passing the subsheet as an argument to the function and returning as a sorted subsheet
    subsheet sortedSubsheet = ranker(sampleSubsheet);

    // List is sorted at this point. Just printing the sorted subsheet //
    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%d\n", sortedSubsheet.unsortedList[i].studentName, sortedSubsheet.unsortedList[i].studentScore);
    }
    printf("\n");
    return 0;
}

// NOTE: The argument here is passed by value. Do inform me if you want this to pass by reference.
subsheet ranker(subsheet subsheetvar)
{
    subsheet newSubsheet;
    int lines, i, size;
    
    // Finding the size of the subsheetvar.unsortedList[i] since the sizeof way did not work
    for (int i = 0; subsheetvar.unsortedList[i].studentName != NULL; i++)
    {
        size++;
    }

    // Getting the values/kinda 'disassembling' the subsheet.
    int score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];
    for (i = 0; i<size; i++)
    {
        score_array[i] = subsheetvar.unsortedList[i].studentScore;
        strcpy(name_parray[i], subsheetvar.unsortedList[i].studentName);
        lines++;
    }

    // NOTE: I once tried placing my bubblesort code in this function, but it lead to errors for some reason.
    bubbleSort(name_parray, score_array, size);

    // Placing the sorted values to the new subsheet
    for (int i = 0; i<size; i++)
    {
        newSubsheet.unsortedList[i].studentScore = score_array[i];
        newSubsheet.unsortedList[i].studentName = name_parray[i];
    }

    return newSubsheet;
}

// Standard bubbleSort code
void bubbleSort(char string_array[][LIMIT], int score_array[], int lines)
{
    int pass, i, intswap;
    char stringswap[LIMIT];

    for(pass = 1; pass < lines; pass++)
    {
        for(i = 0; i < lines-pass; i++)
        {
            // Sorts based on grades
            if(score_array[i] < score_array[i+1]) 
            {
                intswap = score_array[i];
                score_array[i] = score_array[i+1];
                score_array[i+1] = intswap;

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define LIMIT 1000
// Top 10 student sorting algorithm.

void bubbleSortDemo(char string_array[][LIMIT], int score_array[], int lines);
void rankSorter(char* class[][2], int entry_count); // We return an array of pointers and take an array of pointers

int main(void)
{
    // Opening file
    char* class[][2] = 
    {
        {"Harvar D Three Four Five", "100"}, 
        {"Ox Twelve", "200"}, 
        {"Tree Force", "21"}, 
        {"Four", "92"}, 
        {"Place", "90"},
        {"Reee Za", "92"},
        {"Ra", "96"},
        {"Eight", "90"},
        {"Nine", "100"},
        {"Ten", "88"},
        {"Eleven", "88"},
    };

    int lines = 0;
    // Placing entries to other containers
    int score_array[SIZE] = {0};
    for (int i = 0; i<11; i++) // need better placeholder for 11
    {
        score_array[i] = atoi(class[i][1]);
        printf("%d\n", score_array[i]);
    }
    printf("\n");
    char name_parray[SIZE][LIMIT];
    for (int i = 0; i<11; i++)
    {
        strcpy(name_parray[i], *class[i]);
        printf("%s\n", name_parray[i]);
        lines++;
    }

    //bubbleSortDemo(name_parray, score_array, lines);

    // List is sorted at this point //
    return 0;
}

void rankSorter(char* class[][2], int entry_count)
{

}

// needs amount of lines
void bubbleSortDemo(char string_array[][LIMIT], int score_array[], int lines)
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

/*
void ranker(char* class[], int entry_count)
{
    // Variables
    

    // Getting inputs from 2D Array/Array of pointers class


    // Sort the entries by grade


    // Return sorted list
}









    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%d\n", name_parray[i], score_array[i]);
    }
    printf("\n");
*/
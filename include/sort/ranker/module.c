#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define LIMIT 1000
// Top 10 student sorting algorithm.

void rankSorter(char* class[SIZE][2], int size);

int main(void)
{
    // Placeholders for arguments
    int size = 11;
    char* class[SIZE][2] = 
    {
        {"Harvar D Three Four Five", "100"}, 
        {"Ox Twelve", "100"}, 
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

    rankSorter(class, size);

    // List is sorted at this point //
    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%s\n", *class[i], class[i][1]);
    }
    printf("\n");
    return 0;
}

void rankSorter(char* class[SIZE][2], int size)
{
    int score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];
    int lines = 0;
    
    for (int i = 0; i<size; i++)
    {
        score_array[i] = atoi(class[i][1]);
        strcpy(name_parray[i], *class[i]);
        lines++;
    }

    int pass, i, intswap;
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

                strcpy(stringswap, name_parray[i]);
                strcpy(name_parray[i], name_parray[i+1]);
                strcpy(name_parray[i+1], stringswap);
            }
            else if ((score_array[i] == score_array[i+1]) && (strcmp(name_parray[i], name_parray[i+1]) > 0))
            {
                strcpy(stringswap, name_parray[i]);
                strcpy(name_parray[i], name_parray[i+1]);
                strcpy(name_parray[i+1], stringswap);
            }
        }
    }

    // Tries to place the values of name_parray and score_array to the class 2D pointer array//
    // It fails likely because of the sizes of the strings of name_parray and score_array are incompatible(?)//

    // for (int i = 0; i<size; i++)
    // {
    //     sprintf(class[i][1], "%d", score_array[i]);
    //     strcpy(*class[i], name_parray[i]);
    // }
}

// // needs amount of lines
// void bubbleSort(char string_array[][LIMIT], int score_array[], int lines)
// {
//     int pass, size, i, intswap;
//     char stringswap[LIMIT];

//     for(pass = 1; pass < lines; pass++)
//     {
//         for(i = 0; i < lines-pass; i++)
//         {
//             if(score_array[i] < score_array[i+1])
//             {
//                 intswap = score_array[i];
//                 score_array[i] = score_array[i+1];
//                 score_array[i+1] = intswap;

//                 strcpy(stringswap, string_array[i]);
//                 strcpy(string_array[i], string_array[i+1]);
//                 strcpy(string_array[i+1], stringswap);
//             }
//             else if ((score_array[i] == score_array[i+1]) && (strcmp(string_array[i], string_array[i+1]) > 0))
//             {
//                 strcpy(stringswap, string_array[i]);
//                 strcpy(string_array[i], string_array[i+1]);
//                 strcpy(string_array[i+1], stringswap);
//             }
//         }
//     }
// }
// // Placing entries to other containers
// int score_array[SIZE] = {0};
// char name_parray[SIZE][LIMIT];
// int lines = 0;
    
// for (int i = 0; i<size; i++) // need better placeholder for size
// {
//     score_array[i] = atoi(class[i][1]);
//     strcpy(name_parray[i], *class[i]);
//     lines++;
// }

// for (int i = 0; i<11; i++)
// {
//     printf("%s %d\n", name_parray[i], score_array[i]);
// }
// printf("\n");

// bubbleSort(name_parray, score_array, lines);
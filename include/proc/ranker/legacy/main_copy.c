#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define LIMIT 1000
// Top 10 student sorting algorithm.

void bubbleSortDemo(char string_array[][LIMIT], int score_array[], int lines);
void rankSorter(char* class[SIZE][2], int size); // We return an array of pointers and take an array of pointers

typedef struct masterlist
{
    int data;
} masterlist;

typedef struct sortedlist
{int data;}sortedlist;

struct datasheet 
{
    masterlist master[SIZE];
    sortedlist sort[SIZE];
};

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

    // Placing entries to other containers
    int score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];
    int lines = 0;
    
    for (int i = 0; i<size; i++) // need better placeholder for size
    {
        score_array[i] = atoi(class[i][1]);
        strcpy(name_parray[i], *class[i]);
        lines++;
    }

    for (int i = 0; i<11; i++)
    {
        printf("%s %d\n", name_parray[i], score_array[i]);
    }
    printf("\n");

    bubbleSortDemo(name_parray, score_array, lines);

    // List is sorted at this point //
    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%d\n", name_parray[i], score_array[i]);
    }
    printf("\n");
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
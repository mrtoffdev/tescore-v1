#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
#define LIMIT 1000
// Top 10 student sorting algorithm.

void bubbleSortDemo(char string_array[][LIMIT], int score_array[], int lines);

int main(void)
{
    FILE* input_file;
    input_file = fopen("Students.txt", "r");
    if (input_file == NULL)
    {
        printf("Error loading file\n");
        return 1;
    }

    int lines = 0;
    int score_array[SIZE] = {0};
    char name_parray[SIZE][LIMIT];
    char stringplaceholder[LIMIT];
    for (int i = 0; i < SIZE; i++)
    {
        // Check if fscanf is successful, if it fails, then we finish the scanning. Ensures that first input must be a name
        if (((fscanf(input_file, "%s", stringplaceholder)) == 1) && ((stringplaceholder[0] >= 65) && (stringplaceholder[0] <= 90)))
        {
            // Check if there are more strings/names
            while((stringplaceholder[0] >= 65) && (stringplaceholder[0] <= 90))
            {
                strcat(name_parray[i], strcat(stringplaceholder, " "));
                fscanf(input_file, "%s", stringplaceholder); // 
            }
            // Stringplaceholder is a number at this point.
            score_array[i] = atoi(stringplaceholder);
            // print both name and int
            printf("%s%d\n", name_parray[i], score_array[i]);
            lines++;
        }
        else
        {
            break;
        }
    }

    printf("\n");
    bubbleSortDemo(name_parray, score_array, lines);

    for (int i = 0; i<10; i++)
    {
        printf("%-30s\t%d\n", name_parray[i], score_array[i]);
    }
    printf("\n");

    fclose(input_file);

    return 0;
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
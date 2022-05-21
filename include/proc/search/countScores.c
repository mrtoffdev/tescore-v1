#include <stdio.h>

#include "strec.h"
#include "countScores.h"

#define MAX 999

// function: counts the occurences of
// specified scores in student records
void countScores(int scores[MAX], int scoreArrSize, \
    struct strec studentList[MAX], int studentListSize, int results[MAX][2]) {
    
    int i, j;
    for (i=0; i<scoreArrSize; i++) {
        results[i][0] = scores[i];
        results[i][1] = 0; //default value
    }
    
    // iterate over student scores
    for (i=0; i<studentListSize; i++) {
        // compare to input scores
        for (j=0; j<scoreArrSize; j++) {
            if (studentList[i].score == scores[j]) {
                // increment corresponding index
                // in result array
                results[j][1]++;
            }
        }
    }
    
    return;
}

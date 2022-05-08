#include <stdio.h>

#include "strec.h"
#include "countScores.h"

#define MAX 999

// function: counts the occurences of
// specified scores in student records
// returns pointer to result array
void countScores(int scores[MAX], int scoreArrSize, \
    struct strec studentList[MAX], int studentListSize, int results[MAX][2]) {
    
    int i, j;
    for (i=0; i<scoreArrSize; i++) {
        results[i][0] = scores[i];
        results[i][1] = 0; //default value
    }
    
    // iterate over student scores
    // compare to input scores
    
    
    
    // increment corresponding index
    // in result array
    
    return;
}

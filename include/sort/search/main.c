#include <stdio.h>

#include "strec.h"
#include "countScores.h"

#define MAX 999

int main() {
    
    int scores[5] = {45, 23, 65, 88, 97};
    struct strec studentList[3] = {
        {"Whatthe Lul", 23},
        {"Hoshippe Waaka", 88},
        {"Kal Owelgogo", 90},
    };
    
    int results[MAX][2];
    countScores(scores, 5, studentList, 3, results);
    
    // test 1
    if (results[0][1] == 0) printf("*");
    else printf("x");
    
    // test 2
    if (results[1][1] == 1) printf("*");
    else printf("x");
    
    //test 3
    if (results[3][1] == 0) printf("*");
    else printf("x");
    
    // end of tests
    
    return 0;
}

#include <stdio.h>

#include "strec.h"
#include "countScores.h"

int main() {
    
    int scores[5] = {45, 23, 65, 88, 97};
    struct strec studentList[3] = {
        {"Whatthe Lul", 23},
        {"Hoshippe Waaka", 88},
        {"Kal Owelgogo", 90},
    };
    
    int* scoreOccurences = countScores(scores, studentList);
    
    return 0;
}

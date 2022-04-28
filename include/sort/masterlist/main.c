#include <stdio.h>
#include <string.h>

#include "alphabeticallySort.h"

#define MAX 999

int main() {
    
    // sample student list
    char *studentList[3][MAX] = {
        {"Bu Yaoze", "87"},
        {"Fei Wazai", "90"},
        {"Aine Hakum", "93"}
    };
    
    alphabeticallySort(studentList, 3);
    
    // test 1
    if (strcmp(studentList[0][0], "Aine Hakum") == 0) printf("*");
    else printf("x");
    
    // test 2
    if (strcmp(studentList[2][0], "Fei Wazai") == 0) printf("*");
    else printf("x");
    
    // test 3
    if (strcmp(studentList[1][0], "Bu Yaoze") == 0) printf("*");
    else printf("x");
    
    // end of tests
    printf("\n");
    
    return 0;
}

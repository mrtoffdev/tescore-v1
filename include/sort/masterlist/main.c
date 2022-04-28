#include <stdio.h>
#include <string.h>

#include "alphabeticallySort.h"
#include "alphaMergeSort.h"

#define MAX 999

int main() {
    
    // sample student list
    struct strec studentList[3];
    strcpy(studentList[0].name, "Zebra Helicopter");
    studentList[0].score = 83;
    strcpy(studentList[1].name, "Apple Bus"); 
    studentList[1].score = 95;
    strcpy(studentList[2].name, "Nylon Jeepney"); 
    studentList[2].score = 91;
    
    alphabeticallySort(studentList, 3);
    
    // test 1
    if (strcmp(studentList[0].name, "Apple Bus") == 0) printf("*");
    else printf("x");
    
    // test 2
    if (strcmp(studentList[2].name, "Zebra Helicopter") == 0) printf("*");
    else printf("x");
    
    // test 3
    if (strcmp(studentList[1].name, "Nylon Jeepney") == 0) printf("*");
    else printf("x");
    
    // reshuffle for merge sort version
    strcpy(studentList[0].name, "Zebra Helicopter");
    studentList[0].score = 83;
    strcpy(studentList[1].name, "Apple Bus"); 
    studentList[1].score = 95;
    strcpy(studentList[2].name, "Nylon Jeepney"); 
    studentList[2].score = 91;
    
    alphaMergeSort(studentList, 0, 2);
    
    // test 4
    if (strcmp(studentList[0].name, "Apple Bus") == 0) printf("*");
    else printf("x");
    
    // test 5
    if (strcmp(studentList[2].name, "Zebra Helicopter") == 0) printf("*");
    else printf("x");
    
    // test 6
    if (strcmp(studentList[1].name, "Nylon Jeepney") == 0) printf("*");
    else printf("x");
    
    // end of tests
    printf("\n");
    
    return 0;
}

/*========================================
      MASTERLIST SORT ALGORITHMS TESTS
      Author: Jerome Loria
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabeticallySort.h"
#include "alphaMergeSort.h"

#define MAX 999

int main() {
    
    int basicSize = 3,
        extendedSize = 10,
        i;

    int subsheeBasicSize = 10;

    //#region =========== TESTS ===========

    // Generate List of 3 Units
    struct strec studentList[3];
    strcpy(studentList[0].name, "Zebra Helicopter");
    studentList[0].score = 83;
    strcpy(studentList[1].name, "Apple Bus"); 
    studentList[1].score = 95;
    strcpy(studentList[2].name, "Nylon Jeepney"); 
    studentList[2].score = 91;

    // // Testing Datasheet
    // SUBSHEET sampleSubsheet =
    // {
    //     1,
    //     2,
    //     {   
    //          {"Fridge Grills", 85},
    //          {"Window Tab Post", 92},
    //          {"Roof Leaf", 96},
    //          {"Coconut Rock", 79},
    //          {"Shirt Switch Root", 86},
    //          {"Screen Fruit", 88},
    //          {"White Fan", 94},
    //          {"Light Wall", 82},
    //          {"Cloud Plane", 77},
    //          {"Escaped Post", 97}
    //     }
    // };

    // SUBSHEET sample2Subsheet =
    // {
    //     1,
    //     2,
    //     {   
    //          {"Fridge Grills", 85},
    //          {"Window Tab Post", 92},
    //          {"Roof Leaf", 96},
    //          {"Coconut Rock", 79},
    //          {"Shirt Switch Root", 86},
    //          {"Screen Fruit", 88},
    //          {"White Fan", 94},
    //          {"Light Wall", 82},
    //          {"Cloud Plane", 77},
    //          {"Escaped Post", 97}
    //     }
    // };

    // DATASHEET sampleSheet = 
    // {
    //     "name",
    //     "author",
    //     sampleSubsheet,
    //     sample2Subsheet,
    // };

    // Generator Init Data
    char *studentData[10][2] = {
        {"Fridge Grills", "85"},
        {"Window Tab Post", "92"},
        {"Roof Leaf", "96"},
        {"Coconut Rock", "79"},
        {"Shirt Switch Root", "86"},
        {"Screen Fruit", "88"},
        {"White Fan", "94"},
        {"Light Wall", "82"},
        {"Cloud Plane", "77"},
        {"Escaped Post", "97"}
    };
    
    // Generate Extended List of 10 units
    struct strec extendedList[10];
    for (i=0; i<extendedSize; i++) {
        strcpy(extendedList[i].name, studentData[i][0]);
        extendedList[i].score = atoi(studentData[i][1]);
    }
    
    // basic masterlist generator
    // with basic tests
    alphabeticallySort(studentList, basicSize);   
    // test 1
    if (strcmp(studentList[0].name, "Apple Bus") == 0) printf("*");
    else printf("x");  
    // test 2
    if (strcmp(studentList[2].name, "Zebra Helicopter") == 0) printf("*");
    else printf("x");  
    // test 3
    if (strcmp(studentList[1].name, "Nylon Jeepney") == 0) printf("*");
    else printf("x");
    
    // revert the basic arrangement 
    // for merge sort version testing
    strcpy(studentList[0].name, "Zebra Helicopter");
    studentList[0].score = 83;
    strcpy(studentList[1].name, "Apple Bus"); 
    studentList[1].score = 95;
    strcpy(studentList[2].name, "Nylon Jeepney"); 
    studentList[2].score = 91;
    
    // merge sort masterlist generator
    // with basic tests
    alphaMergeSort(studentList, 0, basicSize-1);
    // test 4
    if (strcmp(studentList[0].name, "Apple Bus") == 0) printf("*");
    else printf("x");
    // test 5
    if (strcmp(studentList[2].name, "Zebra Helicopter") == 0) printf("*");
    else printf("x");   
    // test 6
    if (strcmp(studentList[1].name, "Nylon Jeepney") == 0) printf("*");
    else printf("x");

    // // testing modified code
    // alphaMergeSortSubsheet(&sampleSheet.masterlistCollection, 0, basicSize-1);
    // for (int i = 0; i<basicSize; i++)
    // {
    //     printf("%-30s\t%d\n", sampleSheet.masterlistCollection.container[i].indexName, sampleSheet.masterlistCollection.container[i].value);
    // }
    
    
    // basic masterlist generator
    // tested on extended list
    alphabeticallySort(extendedList, extendedSize);
    // test 7
    if (strcmp(extendedList[0].name, "Cloud Plane") == 0) printf("*");
    else printf("x");
    // test 8
    if (strcmp(extendedList[1].name, "Coconut Rock") == 0) printf("*");
    else printf("x");   
    // test 9
    if (strcmp(extendedList[9].name, "Window Tab Post") == 0) printf("*");
    else printf("x");
    
    // revert the extended arrangement 
    // for merge sort version testing
    for (i=0; i<extendedSize; i++) {
        strcpy(extendedList[i].name, studentData[i][0]);
        extendedList[i].score = atoi(studentData[i][1]);
    }
    
    // merge sort masterlist generator
    // tested on extended list
    alphaMergeSort(extendedList, 0, extendedSize-1);
    // test 10
    if (strcmp(extendedList[0].name, "Cloud Plane") == 0) printf("*");
    else printf("x");
    // test 11
    if (strcmp(extendedList[1].name, "Coconut Rock") == 0) printf("*");
    else printf("x");   
    // test 12
    if (strcmp(extendedList[9].name, "Window Tab Post") == 0) printf("*");
    else printf("x");
    
    // end of tests
    printf("\n");
    
    return 0;
}

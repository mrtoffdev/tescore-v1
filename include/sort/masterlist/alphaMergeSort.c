/*========================================
      MASTERLIST : MERGE SORT
      Author: Jerome Loria
  ========================================*/

#include <string.h>
#include <stdio.h>

#include "alphaMergeSort.h"

#define MAX 999

// void alphaMerge(struct strec studentList[MAX], int i1, int j1, int i2, int j2);
void alphaMerge(SUBSHEET *subsheet, int i1, int j1, int i2, int j2);

// void alphaMergeSort(struct strec studentList[MAX], int start, int end) {
    
//     int middle;
//     if (start < end) {
//         middle = (start+end)/2;
//         alphaMergeSort(studentList, start, middle);
//         alphaMergeSort(studentList, middle+1, end);
//         alphaMerge(studentList, start, middle, middle+1, end);
//     }
// }

void alphaMergeSort(SUBSHEET* subsheet, const int start, int end) {
    
    int middle;
    if (start < end) {
        middle = (start+end)/2;
        alphaMergeSort(subsheet, start, middle);
        alphaMergeSort(subsheet, middle+1, end);
        alphaMerge(subsheet, start, middle, middle+1, end);
    }
}

// int main(void) {
    
//     int subsheetBasicSize = 10;

//     // Testing Datasheet
//     SUBSHEET sampleSubsheet =
//     {
//         1,
//         2,
//         {   
//              {"Fridge Grills", 85},
//              {"Window Tab Post", 92},
//              {"Roof Leaf", 96},
//              {"Coconut Rock", 79},
//              {"Shirt Switch Root", 86},
//              {"Screen Fruit", 88},
//              {"White Fan", 94},
//              {"Light Wall", 82},
//              {"Cloud Plane", 77},
//              {"Escaped Post", 97}
//         }
//     };

//     SUBSHEET sample2Subsheet =
//     {
//         1,
//         2,
//         {   
//              {"Fridge Grills", 85},
//              {"Window Tab Post", 92},
//              {"Roof Leaf", 96},
//              {"Coconut Rock", 79},
//              {"Shirt Switch Root", 86},
//              {"Screen Fruit", 88},
//              {"White Fan", 94},
//              {"Light Wall", 82},
//              {"Cloud Plane", 77},
//              {"Escaped Post", 97}
//         }
//     };

//     DATASHEET sampleSheet = 
//     {
//         "name",
//         "author",
//         sampleSubsheet,
//         sample2Subsheet,
//     };

//     // testing modified code
//     alphaMergeSortSubsheet(&sampleSheet.masterlistCollection, 0, subsheetBasicSize-1);
//     for (int i = 0; i<subsheetBasicSize; i++)
//     {
//         printf("%-30s\t%d\n", sampleSheet.masterlistCollection.container[i].indexName, sampleSheet.masterlistCollection.container[i].value);
//     }

//     return 0;
// }

// void alphaMerge(struct strec studentList[MAX], int i1, int j1, int i2, int j2) {
//     int i, j, k;
//     struct strec temp[MAX];
//     i = i1;
//     j = i2;
//     k = 0;
    
//     // compare elements
//     while (i<=j1 && j<=j2) {
//         if (strcmp(studentList[i].name, studentList[j].name) < 0) {
//             temp[k++] = studentList[i++];
//         }
//         else {
//             temp[k++] = studentList[j++];
//         }
//     }
    
//     // copy remaining elements
//     while (i<=j1) {
//         temp[k++] = studentList[i++];
//     }
//     while (j<=j2) {
//         temp[k++] = studentList[j++];
//     }
    
//     // copy temp to original array
//     for (i=i1, j=0; i<=j2; i++, j++) {
//         studentList[i] = temp[j];
//     }
    
// }

void alphaMerge(SUBSHEET *subsheet, int i1, int j1, int i2, int j2) {
    int i, j, k;
    INDEX temp[MAX];
    i = i1;
    j = i2;
    k = 0;
    
    // compare elements
    while (i<=j1 && j<=j2) {
        if (strcmp(subsheet->container[i].indexName, subsheet->container[j].indexName) < 0) {
            temp[k++] = subsheet->container[i++];
        }
        else {
            temp[k++] = subsheet->container[j++];
        }
    }
    
    // copy remaining elements
    while (i<=j1) {
        temp[k++] = subsheet->container[i++];
    }
    while (j<=j2) {
        temp[k++] = subsheet->container[j++];
    }
    
    // copy temp to original array
    for (i=i1, j=0; i<=j2; i++, j++) {
        subsheet->container[i] = temp[j];
    }
    
}



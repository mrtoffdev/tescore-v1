/*========================================
      MASTERLIST : MERGE SORT
      Author: Jerome Loria
  ========================================*/

#include <string.h>
#include <stdio.h>

#include "../proc.h"

#define MAX 999

// void alphaMerge(struct strec studentList[MAX], int i1, int j1, int i2, int j2);
void alphaMerge(Sheetctx* in_sctx, size_t i1, size_t j1, size_t i2, size_t j2);

// void alphaMergeSort(struct strec studentList[MAX], int start, int end) {
    
//     int middle;
//     if (start < end) {
//         middle = (start+end)/2;
//         alphaMergeSort(studentList, start, middle);
//         alphaMergeSort(studentList, middle+1, end);
//         alphaMerge(studentList, start, middle, middle+1, end);
//     }
// }

void module_alphasort(Sheetctx* in_sctx, size_t start, size_t end) {
    
    size_t middle;

    if (start < end) {
        middle = (start+end)/2;

        module_alphasort(in_sctx, start, middle); // L Split
        module_alphasort(in_sctx, middle+1, end); // R Split

        alphaMerge(in_sctx, start, middle, middle+1, end);
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

void alphaMerge(Sheetctx* in_sctx, size_t i1, size_t j1, size_t i2, size_t j2) {
    size_t i, j, k;
    Index temp[MAX];
    i = i1;
    j = i2;
    k = 0;
    
    // compare elements
    while (i<=j1 && j<=j2) {
        if (strcmp(in_sctx->masterlist[i].indexName, in_sctx->masterlist[j].indexName) < 0) {
            temp[k++] = in_sctx->masterlist[i++];
        }
        else {
            temp[k++] = in_sctx->masterlist[j++];
        }
    }
    
    // copy remaining elements
    while (i<=j1) {
        temp[k++] = in_sctx->masterlist[i++];
    }
    while (j<=j2) {
        temp[k++] = in_sctx->masterlist[j++];
    }
    
    // copy temp to original array
    for (i=i1, j=0; i<=j2; i++, j++) {
        in_sctx->masterlist[i] = temp[j];
    }
    
}



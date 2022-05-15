/*========================================
      MASTERLIST : MERGE SORT
      Author: Jerome Loria
  ========================================*/

#include <string.h>

#include "alphaMergeSort.h"

#define MAX 999

void alphaMerge(struct strec studentList[MAX], int i1, int j1, int i2, int j2);

void alphaMergeSort(struct strec studentList[MAX], int start, int end) {
    
    int middle;
    if (start < end) {
        middle = (start+end)/2;
        alphaMergeSort(studentList, start, middle);
        alphaMergeSort(studentList, middle+1, end);
        alphaMerge(studentList, start, middle, middle+1, end);
    }
}

void alphaMerge(struct strec studentList[MAX], int i1, int j1, int i2, int j2) {
    int i, j, k;
    struct strec temp[MAX];
    i = i1;
    j = i2;
    k = 0;
    
    // compare elements
    while (i<=j1 && j<=j2) {
        if (strcmp(studentList[i].name, studentList[j].name) < 0) {
            temp[k++] = studentList[i++];
        }
        else {
            temp[k++] = studentList[j++];
        }
    }
    
    // copy remaining elements
    while (i<=j1) {
        temp[k++] = studentList[i++];
    }
    while (j<=j2) {
        temp[k++] = studentList[j++];
    }
    
    // copy temp to original array
    for (i=i1, j=0; i<=j2; i++, j++) {
        studentList[i] = temp[j];
    }
    
}

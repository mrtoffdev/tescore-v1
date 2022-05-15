#include <string.h>

#include "alphabeticallySort.h"

/** function: alphabetically sort list of students
 takes an array of unsorted strecs (student records)
**/

// this will rearrange the struct array,
// make a backup if needed

//TODO: change that ^ and make that v return
// and accept a SUBSHEET

void alphabeticallySort(struct strec studentList[MAX], int size) {
    // modified insertion sort,
    // might switch to merge sort if needed
    
    int i, j;
    struct strec key;
    
    for (i=1; i<size; i++) {
        key = studentList[i];
        j = i - 1;
        
        while (j>=0 && strcmp(studentList[j].name, key.name) > 0) {
            studentList[j+1] = studentList[j];
            j = j-1;
        }
        
        studentList[j+1] = key;
    }
    
    return;
}

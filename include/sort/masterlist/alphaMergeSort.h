/*========================================
      MASTERLIST : MERGE SORT HEADER
      Author: Jerome Loria
  ========================================*/

#ifndef TESCORE_ALPHAMERGESORT_H
#define TESCORE_ALPHAMERGESORT_H

#include "../../model/datamodel.h"

#define MAX 999

void alphaMergeSort(SUBSHEET *subsheet, const int start, int end);

// Jovic's Notes:
// I need to replace the index arrays with subsheet.container[]

// what i did?
// AS OF 5:52PM I changed the function slightly so that it accepts subsheets instead fo struct strec

// did i finish it?
// AS OF 5:52PM Maybe. I just cannot call the function at tests_alphasortmodule2

// what can you do?
// AS OF 5:52PM Try to call the function at tests_alphasortmodule2 or maybe make it work. if it works there, it might be integratable.
// AS OF 5:52PM: TO JEROME: You can check this code when you are trying to implement your module to render.c in your branch

// AS OF 5:52PM: Sorry for the mess tho... Imma try to clean it up after dishwashing
// void alphaMergeSort(struct strec studentList[MAX], int start, int end);

#endif
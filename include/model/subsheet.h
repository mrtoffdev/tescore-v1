/*========================================
      SUBSHEET MODEL
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_SUBSHEET_H
#define TESCORE_SUBSHEET_H

#include "../model/index.h"

// DATA MODEL PARAMETERS
#define MAXSTUDENTCOUNT 100

typedef struct  SUBSHEET {
    int         size;
    int         id;
    INDEX       container[MAXSTUDENTCOUNT];
} SUBSHEET;
#endif

/*  ID Reference
    1 - Top 10 Ranking
    2 - Master List
    3 - Unsorted
*/
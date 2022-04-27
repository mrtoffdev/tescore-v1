#ifndef TESCORE_SUBSHEET_H
#define TESCORE_SUBSHEET_H

#include "../model/index.h"

typedef struct  SUBSHEET {
    int         id;
    INDEX       container[];
} SUBSHEET;
#endif

/*  ID Reference
    1 - Top 10 Ranking
    2 - Master List
    3 - Unsorted
*/
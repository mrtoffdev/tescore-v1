#ifndef TESCORE_SHEET_H
#define TESCORE_SHEET_H

#include "subsheet.h"

typedef struct  DATASHEET {
    char*       name,
                author;
    SUBSHEET    rankedCollection,
                masterlistCollection;
} DATASHEET;
#endif

/*  Reference Model
    Datasheet
       |
       |--- Sheet Name
       |--- Sheet Author
       |--- RankedSheet/
       |     |
       |     |--- Index Collection/
       |           |
       |           |--- Index 1 (Student 1)
       |           |--- Index 2 (Student 2)
       |           |--- Etc...
       |
       |--- MasterSheet/
             |
             |--- Index Collection
                   |
                   |--- Index 1 (Student 1)
                   |--- Index 2 (Student 2)
                   |--- Etc...
*/
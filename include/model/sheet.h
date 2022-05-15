/*========================================
      SHEET/DATASHEET (DIB) MODEL
      Author: Christopher Abadillos Jr.
  ========================================*/

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

#ifndef TESCORE_SHEET_H
#define TESCORE_SHEET_H

#include "subsheet.h"

typedef struct  DATASHEET {
    SUBSHEET    rankedCollection;
    SUBSHEET    masterlistCollection;
} DATASHEET;
#endif


/*========================================
      DATA MODELS INTERFACE
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_DATAMODEL_H
#define TESCORE_DATAMODEL_H

#include "../model/index.h"
#include "../model/sheet.h"
#include "../model/subsheet.h"

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
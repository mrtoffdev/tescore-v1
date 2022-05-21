/*========================================
      DATA MODELS INTERFACE
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_MODELS_H
#define TESCORE_MODELS_H

#include "../model/index.h"
#include "../model/Sheetctx.h"
#include "../model/renderctx.h"

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
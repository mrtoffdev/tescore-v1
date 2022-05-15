/*========================================
      TOP 10 RANKING SORT MODULE
      Author: Jovic Francis Rayco
  ========================================*/
#ifndef TESCORE_RANKERMODULE_H
#define TESCORE_RANKERMODULE_H

#include "../../model/datamodel.h"

// Module Parameters
#define SIZE 100
#define LIMIT 509 // Standard limit for char ANSI Compatibility

// Method Calls
SUBSHEET ranker(SUBSHEET unsortedSubsheet, int size);

#endif

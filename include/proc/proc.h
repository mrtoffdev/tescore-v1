/*========================================
      INTERNAL PROCESSING HEADER
      Authors: Jovic Francis Rayco
               Jerome Loria
  ========================================*/
#ifndef TESCORE_PROC_H
#define TESCORE_PROC_H

#include <stdint.h>
#include "../model/Sheetctx.h"
#include "../model/index.h"

#define LIMIT_STUDENTS 100
#define LIMIT_STRLEN 509

// INTERFACE
void module_ranksort(Sheetctx in_sctx, Index out_ranked[10]);
void module_alphasort(Sheetctx* in_sctx, size_t start, size_t end);

#endif

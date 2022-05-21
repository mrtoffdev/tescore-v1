/*========================================
      DATASHEET CONTEXT
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_SHEETCTX_H
#define TESCORE_SHEETCTX_H

#include "index.h"

#define LIMIT_INDEX 100

typedef struct Sheetctx {
    char* name;
    char* passphrase;
    Index masterlist[LIMIT_INDEX];
    size_t size;
} Sheetctx;

#endif //TESCORE_SHEETCTX_H

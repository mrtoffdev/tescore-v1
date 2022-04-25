#ifndef TESCORE_DATASHEET_H
#define TESCORE_DATASHEET_H

#include "index.h"

typedef struct DATASHEET {
    char*   name,
            author;
    INDEX   collection[];

} DATASHEET;
#endif

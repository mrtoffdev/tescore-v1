/*========================================
      NAVIGATION SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

#include "../../model/models.h"
#include "../../model/renderctx.h"

/*
    FUNCTION CALLS
        VOID
        - parseNavigationKey(key, panelID)      : Checks passed in key & performs corresponding action

*/

// VOID
void navigationKeyHandler(Renderctx ctx, Sheetctx in_sctx, char commandLog[][509]);

#endif

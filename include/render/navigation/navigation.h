/*========================================
      NAVIGATION SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

#include "../../model/datamodel.h"
#include "../../model/renderctx.h"

/*
    FUNCTION CALLS
        VOID
        - parseNavigationKey(key, panelID)      : Checks passed in key & performs corresponding action

*/

// VOID
void navigationKeyHandler(Renderctx ctx, char commandLog[][509]);

#endif

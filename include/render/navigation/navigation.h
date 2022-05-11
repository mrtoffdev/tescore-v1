/*========================================
      NAVIGATION SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

#include "../../model/datamodel.h"

/*
    FUNCTION CALLS
        VOID
        - parseNavigationKey(key, panelID)      : Checks passed in key & performs corresponding action

        RETURN
        - <short> fetchPanelID()                : Returns the globalPanelID (short)
*/

// VOID
void navigationKeyHandler(DATASHEET sessionSheet, int key, int maxIndexes, char* commandLog);

// RETURN
short fetchPanelID();
#endif

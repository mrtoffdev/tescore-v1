/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

/*
    FUNCTION CALLS
        VOID
        - parseNavigationKey(key, panelID)      : Checks passed in key & performs corresponding action

        RETURN
        - <short> fetchPanelID()                : Returns the globalPanelID (short)
*/

// VOID
void navigationKeyHandler(int key, int maxIndexes);

// RETURN
short fetchPanelID();
#endif

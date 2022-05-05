#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

/* RENDERING SYSTEM

    FUNCTION CALLS
        VOID
        - parseNavigationKey(key, panelID)      : Checks passed in key & performs corresponding action

        RETURN
        - <short> fetchPanelID()                : Returns the panelID (short)

*/

// PUBLIC FUNCTIONS

// VOID
void parseNavigationKey(int key, short panelID);

void safeRemoveCell(int key, short panelID);
void safeEditCell(int key, short panelID);

// RETURN
short fetchPanelID();

#endif

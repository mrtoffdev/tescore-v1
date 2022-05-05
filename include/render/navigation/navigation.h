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
void parseNavigationKey(char key, short panelID);
short fetchPanelID();
#endif

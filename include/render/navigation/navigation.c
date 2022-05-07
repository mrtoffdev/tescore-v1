/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>

#include "navigation.h"
#include "../render.h"

/* NAVIGATION SYSTEM

    GLOBAL VARIABLES
    - cellIndex         position of navigation cursor in table, from top to bottom
    - cellSelection     position of navigation cursor within cell
        - <A>           left (L)
        - <D>           right (R)

    GLOBAL NAVIGATION
    - <1><2><3>         switching between panels
    - <W><A><S><D>      panel / table navigation
    - <Q>               program termination prompt

    MASTERLIST NAVIGATION
    - <E>               editing highlighted cell
    - <R>               removing highlighted cell

    RANKER LIST NAVIGATION
    - <E>               expand ranking list
    - <Q>               close expanded tab

    OPERATION MODES
    - 1                 view / read only
    - 2                 edit permissions
    - 3                 write permissions
    - 4                 delete permissions

    CELL SELECTION POSITIONS
    - X                 default (all highlighted, no edits can be made)
    - L                 editing index name
    - R                 editing index value

*/

// PRIVATE
void switchNavPanel(short);

void parseNavigationKey(char key, short panelID){
    char NAVKEY = key;

    switch (NAVKEY) {
        case 'Q':
        case 'q':
            terminatePrompt();
            break;

        case 'E':
        case 'e':
            puts("Hello");
            break;

        case 'R':
        case 'r':
            break;

    }

}

void switchNavPanel(short id){

}



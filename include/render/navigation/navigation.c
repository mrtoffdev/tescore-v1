#include <stdio.h>

#include "navigation.h"
#include "../render.h"

/* NAVIGATION SYSTEM

    GLOBAL NAVIGATION
    - <1><2><3>     switching between panels
    - <W><A><S><D>  panel / table navigation
    - <Q>           program termination prompt

    MASTERLIST NAVIGATION
    - <E>           editing highlighted cell
    - <R>           removing highlighted cell

    RANKER LIST NAVIGATION
    - <E>           expand ranking list
    - <Q>           close expanded tab

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



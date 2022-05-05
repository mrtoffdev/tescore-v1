#include <stdio.h>
#include <conio.h>

#include "navigation.h"
#include "../render.h"

/* NAVIGATION SYSTEM

    GLOBAL VARIABLES
    - cellIndex         position of the selection cursor, from top to bottom
    - cellSelection     position of the selection cursor within the same cell
        <L>             left (index name)
        <R>             right (value)

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


*/

// ============ PRIVATE PROTOTYPES ============
void switchNavPanel(short);

// ============ GLOBAL VARIABLES ============
int cellIndex;
char cellSelection;

void parseNavigationKey(int key, short panelID){

    // PARSE KEYS & SET GLOBAL VARIABLE VALUES
    switch (key) {
        //#region OPERATION KEYS
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
            safeRemoveCell(key, panelID);
            break;
        //#endregion

        //#region NAVIGATION KEYS
        case 'W':
        case 'w':
            cellIndex++;
            break;

        case 'S':
        case 's':
            cellIndex--;
            break;

        case 'A':
        case 'a':
            cellSelection = 'L';
            break;

        case 'D':
        case 'd':
            cellSelection = 'R';
            break;
        //#endregion

        //#region PANEL KEYS
        case 1:
            panelID = 1;
            break;

        case 2:
            panelID = 2;
            break;

        case 3:
            panelID = 3;
            break;
        //#endregion

        default:
            break;

    }

    // RENDER PANEL EVERY parseNavigationKey() CALL
    switchNavPanel(panelID);


}

// ============ PANEL RENDER METHODS ============
void switchNavPanel(short id){

}

// ============ OPERATION METHODS ============
void safeRemoveCell(int key, short panelID){

}

void safeEditCell(int key, short panelID){

}



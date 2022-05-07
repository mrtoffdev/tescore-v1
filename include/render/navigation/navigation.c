/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <malloc.h>

#include "navigation.h"
#include "../view/render.h"

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
void safeRemoveCell();
void safeEditCell();
void switchNavPanel(short);

// GLOBAL VARIABLES
short   cellIndex,
        globalPanelID,
        operationMode = 1;
char    cellSelection = 'X';

// PANELS
void switchNavPanel(short id){
    printf("Rendering Panel No: %d\n", id);
}

// OPERATIONS
void navigationKeyHandler(int key, int maxIndexes){
    // store current panelID
    short prevPanelID = globalPanelID;

    switch (key) {

        //#region OPERATION KEYS
        case 'Q':
        case 'q':
            /*
                Q OPERATION
                    - Checks if the cell selection is not default & currently in edit mode
                        - If true, gets out of edit mode & resets cursor position
                        - If not true (everything is on default i.e. at home screen
                            - Show terminate program prompt
            */
            if((cellSelection != 'X') && (operationMode == 2)){
                // reset global navigation values
                puts("Resetted all global nav values");
                cellSelection = 'X';
                operationMode = 1;
                break;
            } else {
                terminatePrompt();
                break;
            }

        case 'E':
        case 'e':
            /*
                E OPERATION
                    - Checks if the global nav variables are at default
                        - If true, starts edit mode & repositions cursor to left value
                        - If false, starts write mode for the selected cell position

                MODES
                    - Edit Mode
                        - Highlights either the index name or the index value

                    - Write Mode
                        - The highlighted element can now be changed
            */
            if((operationMode == 1) && (cellSelection == 'X')){
                puts("Operation Mode: 2");
                operationMode = 2;
                cellSelection = 'L';
                break;
            } else
            if((operationMode == 2) && (cellSelection != 'X')){
                puts("Operation Mode: 3");
                operationMode = 3;
                safeEditCell(cellSelection);
                break;
            } else break;

        case 'R':
        case 'r':
            if((operationMode == 1) && (cellSelection == 'X')){
                safeRemoveCell();
                break;
            } else break;
            //#endregion

        //#region NAVIGATION KEYS
        case 'W':
        case 'w':
            if(cellIndex > 0) cellIndex--;
            // Testing
            printf("Decremented cellIndex: %d\n", cellIndex);
            break;

        case 'S':
        case 's':
            if(cellIndex < maxIndexes) cellIndex++;
            // Testing
            printf("Incremented cellIndex: %d\n", cellIndex);
            break;

        case 'A':
        case 'a':
            if(operationMode == 2) {
                cellSelection = 'L';
                printf("Cell Selection: %c", cellSelection);
                break;
            } else break;

        case 'D':
        case 'd':
            if(operationMode == 2) {
                cellSelection = 'R';
                printf("Cell Selection: %c", cellSelection);
                break;
            } else break;
        //#endregion

        //#region PANEL KEYS
        case '1':
            globalPanelID = 1;
            break;

        case '2':
            globalPanelID = 2;
            break;

        case '3':
            globalPanelID = 3;
            break;

        default:
            break;
        //#endregion

    }

    // check if panelID values have changed and render frame ID
    // prevents re-rendering the frame if panelID hasn't changed
    printf("Cell Selection: %c ", cellSelection);
    printf("Operation Mode: %d ", operationMode);

    if (globalPanelID != prevPanelID){
        switchNavPanel(globalPanelID);
    }

}

void safeEditCell(){
    char prevCellSelection = cellSelection;
    puts("Editing Cell:");

    switch (cellSelection) {
        case 'L':
            puts("Editing Left of Cell:");
            break;

        case 'R':
            puts("Editing Right of Cell:");
            break;

        default:
            puts("Not Editing a Cell Right Now:");
            break;
    }

    // END
    operationMode = 2;
}

void safeRemoveCell(){
    puts("Removing Cell");
}

// RETURNS
short fetchPanelID(){
    return globalPanelID;
}



/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "navigation.h"
#include "../view/render.h"

/* NAVIGATION SYSTEM

    GLOBAL VARIABLES
    - renderCellIndex         position of navigation cursor in table, from top to bottom
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

//#region PRIVATE FUNC PROTS
void safeRemoveCell(char* []);
void safeEditCell(char, char* []);
void switchNavPanel(short, char* []);
//#endregion

//#region GLOBAL VARIABLES
short   renderCellIndex,
        globalCellIndex,
        globalPanelID,
        operationMode = 1,
        debugMode = 0;
int     NAVKEY = '1';
char    cellSelection = 'X';
char**  localCommandLog;
//#endregion

// OPERATIONS
void navigationKeyHandler(DATASHEET sessionSheet, int maxIndexes, char* commandLog[]){
    // SAVE CURRENT PANELID
    short prevPanelID = globalPanelID;

    while (NAVKEY != EOF){
        NAVKEY = _getch();

        switch (NAVKEY) {

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
                    commandLog[0] = "Resetted all global nav values\n";
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
                    commandLog[0] = "Operation Mode: 2";
                    operationMode = 2;
                    cellSelection = 'L';
                    break;
                } else
                if((operationMode == 2) && (cellSelection != 'X')){
                    commandLog[0] = "Operation Mode: 3";
                    operationMode = 3;
                    safeEditCell(cellSelection, commandLog);
                    break;
                } else break;

            case 'R':
            case 'r':
                if((operationMode == 1) && (cellSelection == 'X')){
                    safeRemoveCell(commandLog);
                    break;
                } else break;
                //#endregion

            //#region NAVIGATION KEYS
        case 'W':
        case 'w':
            if(renderCellIndex > 0) {
                renderCellIndex--;

                // Testing
                commandLog[0] = "Decremented renderCellIndex:";

            }
            break;

        case 'S':
        case 's':
            if(renderCellIndex < maxIndexes) {
                renderCellIndex++;

                // Testing
                commandLog[0] = "Incremented renderCellIndex:";
                printf("Incremented renderCellIndex: %d ", renderCellIndex);
            }
            break;

        case 'A':
        case 'a':
            if(operationMode == 2) {
                cellSelection = 'L';
                printf("\tCell Selection: %c ", cellSelection);
                break;
            } else break;

        case 'D':
        case 'd':
            if(operationMode == 2) {
                cellSelection = 'R';
                printf("\tCell Selection: %c ", cellSelection);
                break;
            } else break;
            //#endregion

            //#region PANEL KEYS
        case '1':
            globalPanelID = 1;
            commandLog[0] = "Rendering Panel No: 1";
            break;

        case '2':
            globalPanelID = 2;
            commandLog[0] = "Rendering Panel No: 2";
            break;

        case '3':
            globalPanelID = 3;
            commandLog[0] = "Rendering Panel No: 3";
            break;

        default:
            break;
            //#endregion

        }

        indentCursor(1);

        if(renderCellIndex){

        }

        printf("Cell Selection: %c ", cellSelection);
        printf("Operation Mode: %d \n", operationMode);

        // check if panelID values have changed and render frame ID
        // prevents re-rendering the frame if panelID hasn't changed
        if (globalPanelID != prevPanelID){

            switchNavPanel(globalPanelID, commandLog);
        }

        refreshFrame(sessionSheet, commandLog, globalPanelID);
    }
}

void safeEditCell(char selection, char* commandLog[]){
    char prevCellSelection = cellSelection;
    puts("Editing Cell:");

    switch (cellSelection) {
        case 'L':
            commandLog[0] = "Editing Left of Cell";
            break;

        case 'R':
            commandLog[0] = "Editing Right of Cell";
            break;

        default:
            commandLog[0] = "Not Editing a Cell Right Now";
            break;
    }

    // END
    operationMode = 2;
}

void safeRemoveCell(char* commandLog[]){
    commandLog[0] = "Removing Cell";
}

void switchNavPanel(short id, char* commandLog[]){
    printf("%d", id);
}

void appendCommandLogEntry(commandLog){

}

// RETURNS
short fetchPanelID(){
    return globalPanelID;
}



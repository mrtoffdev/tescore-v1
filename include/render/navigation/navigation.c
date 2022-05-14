/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <stdio.h>
//#include <conio.h>
#include <termios.h>
#include <malloc.h>
#include <string.h>

// temporary (maybe not anymore)
#include<unistd.h>

#include "navigation.h"
#include "../view/render.h"

//#region =========== DOCS ===========
/*  NAVIGATION SYSTEM

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
//#endregion

//#region PRIVATE FUNC PROTS
void safeRemoveCell(char* []);
void safeEditCell(char* []);
void switchNavPanel(short, char* []);
void clearStdinCache();
//#endregion

//#region GLOBAL VARIABLES
DATASHEET localSessionSheet;
short   renderCellIndex,
        globalPanelID,
        operationMode = 1,
        pauseHandler = 0;
int     NAVKEY = '1';
char    cellSelection = 'X';
char**  localCommandLog;
//#endregion

char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo. 
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}

// OPERATIONS
void navigationKeyHandler(DATASHEET sessionSheet, int maxIndexes, char* commandLog[]){
    // SAVE CURRENT PANELID
    short prevPanelID = globalPanelID;
    localSessionSheet = sessionSheet;

    while (NAVKEY != EOF || pauseHandler != 1){
        NAVKEY = getch();
        //sleep(5); //temporary

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
                if((cellSelection != 'X') && (operationMode != 1)){
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
                        - View Mode: 1
                            - Only highlights the tab
                        - Edit Mode: 2
                            - Highlights either the index name or the index value

                        - Write Mode: 3
                            - The highlighted element can now be changed
                */
                // If on View Mode & No Selection
                if((operationMode == 1) && (cellSelection == 'X')){
                    commandLog[0] = "Operation Mode: 2";
                    operationMode = 2;
                    cellSelection = 'L';
                    break;
                } else
                // If on Edit Mode & Selection
                if((operationMode == 2) && (cellSelection != 'X')){
                    commandLog[0] = "Operation Mode: 3";
                    operationMode = 3;
                    safeEditCell(commandLog);
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
            if(renderCellIndex < maxIndexes-1) {
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
            cellSelection = 'X';
            renderCellIndex = 0;
            operationMode = 1;
            globalPanelID = 1;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 1";
            break;

        case '2':
            cellSelection = 'X';
            renderCellIndex = 0;
            operationMode = 1;
            globalPanelID = 2;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 2";
            break;

        case '3':
            cellSelection = 'X';
            renderCellIndex = 0;
            operationMode = 1;
            globalPanelID = 3;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 3";
            break;

        default:
            break;
            //#endregion

        }

        indentCursor(1);

        printf("Cell Selection: %c ", cellSelection);
        printf("Operation Mode: %d \n", operationMode);

        // check if panelID values have changed and render frame ID
        // prevents re-rendering the frame if panelID hasn't changed
        if (globalPanelID != prevPanelID){

            switchNavPanel(globalPanelID, commandLog);

        }

        refreshFrame(localSessionSheet, globalPanelID, renderCellIndex, cellSelection, commandLog);

    }
}

void safeEditCell(char* commandLog[]){

    clearStdinCache();
    char* entry = calloc(1,(sizeof commandLog[0]));
    char* value = malloc(40);

    switch (cellSelection) {
        case 'L':
            commandLog[0] = "Editing Left of Cell. Please Enter Value: ";
            refreshFrame(localSessionSheet, globalPanelID, renderCellIndex, cellSelection,commandLog);

            // commit note: softbug fixed through stdin fflush();

            fgets(value, 40, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            commandLog[0] = entry;
            operationMode = 2;
            pauseHandler = 0;

            break;

        case 'R':
            commandLog[0] = "Editing Right of Cell. Please Enter Value: ";
            refreshFrame(localSessionSheet, globalPanelID, renderCellIndex, cellSelection, commandLog);

            fgets(value, 30, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            commandLog[0] = entry;
            operationMode = 2;
            pauseHandler = 0;

            break;

        default:
            commandLog[0] = "Not Editing a Cell Right Now";
            operationMode = 2;
            pauseHandler = 0;

            break;

    }
}

void safeRemoveCell(char* commandLog[]){
    commandLog[0] = "Removing Cell";
}

void switchNavPanel(short id, char* commandLog[]){
    printf("%d", id);
}

void clearStdinCache(){
    fflush(stdin);
}

// RETURNS
short fetchPanelID(){
    return globalPanelID;
}



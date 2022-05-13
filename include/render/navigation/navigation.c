/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>

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
void safeRemoveCell(Renderctx ctx, char* commandLog[]);
void safeEditCell(Renderctx ctx, char* commandLog[]);
void switchNavPanel(short, char* []);
void clearStdinCache();
//#endregion

//#region GLOBAL VARIABLES
int     NAVKEY = '1';
//#endregion

// OPERATIONS
void navigationKeyHandler(Renderctx ctx, char* commandLog[]){
    // SAVE CURRENT PANELID
    short prevPanelID = ctx.sessionPanelID;
    uint8_t deleteConfirm = 0; // 1 - Confirming, 2 - Confirmed

    while (NAVKEY != EOF || ctx.handlerMode != 1){
        NAVKEY = _getch();
        ctx.NAVKEY = NAVKEY;

        switch (ctx.NAVKEY) {

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
                if(
                    // ON EDIT MODE
                    ((ctx.renderCellX != 'X') && (ctx.operationMode != 1) && deleteConfirm == 0) ||
                    // CONFIRMING CELL DELETE
                    ((ctx.renderCellX == 'X') && (ctx.operationMode == 1) && deleteConfirm == 1)
                ){
                    commandLog[0] = "Resetted all global nav values\n";
                    ctx.renderCellX = 'X';
                    ctx.operationMode = 1;
                    deleteConfirm = 0;
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
                if((ctx.operationMode == 1) && (ctx.renderCellX == 'X')){
                    commandLog[0] = "Operation Mode: 2";
                    ctx.operationMode = 2;
                    ctx.renderCellX = 'L';
                    break;
                } else
                // If on Edit Mode & Selection
                if((ctx.operationMode == 2) && (ctx.renderCellX != 'X')){
                    commandLog[0] = "Operation Mode: 3";
                    ctx.operationMode = 3;
                    safeEditCell(ctx, commandLog);
                    ctx.operationMode = 1;
                    ctx.renderCellX = 'X';
                    break;
                } else break;

            case 'R':
            case 'r':
                if((ctx.operationMode == 1) && (ctx.renderCellX == 'X')){
                    deleteConfirm++;
                    commandLog[0] = "Removing Cell. Press <R> to confirm: ";
                    if (deleteConfirm == 2){
                        deleteConfirm = 0;
                        safeRemoveCell(ctx, commandLog);
                    }
                    break;
                } else break;
                //#endregion

            //#region NAVIGATION KEYS
        case 'W':
        case 'w':
            if(ctx.renderCellIndex > 0) {
                ctx.renderCellIndex--;

                // Testing
                commandLog[0] = "Decremented renderCellIndex:";

            }
            break;

        case 'S':
        case 's':
            if(ctx.renderCellIndex < 9) {
                ctx.renderCellIndex++;

                // Testing
                commandLog[0] = "Incremented renderCellIndex:";
//                printf("Incremented renderCellIndex: %d ", ctx.renderCellIndex);
            }
            break;

        case 'A':
        case 'a':
            if(ctx.operationMode == 2) {
                ctx.renderCellX = 'L';
//                printf("\tCell Selection: %c ", ctx.renderCellX);
                break;
            } else break;

        case 'D':
        case 'd':
            if(ctx.operationMode == 2) {
                ctx.renderCellX = 'R';
//                printf("\tCell Selection: %c ", ctx.renderCellX);
                break;
            } else break;
            //#endregion

            //#region PANEL KEYS

        case '1':
            ctx.renderCellX = 'X';
            ctx.renderCellIndex = 0;
            ctx.operationMode = 1;
            ctx.sessionPanelID = 1;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 1";
            break;

        case '2':
            ctx.renderCellX = 'X';
            ctx.renderCellIndex = 0;
            ctx.operationMode = 1;
            ctx.sessionPanelID = 2;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 2";
            break;

        case '3':
            ctx.renderCellX = 'X';
            ctx.renderCellIndex = 0;
            ctx.operationMode = 1;
            ctx.sessionPanelID = 3;
            commandLog[0] = "Resetted all global nav values. Rendering Panel No: 3";
            break;

        default:
            break;
            //#endregion

        }

        indentCursor(1);

        // check if panelID values have changed and render frame ID
        // prevents re-rendering the frame if panelID hasn't changed
        if (ctx.sessionPanelID != prevPanelID){
            switchNavPanel(ctx.sessionPanelID, commandLog);
        }

        refreshFrame(ctx, commandLog);
    }
}

void safeEditCell(Renderctx ctx, char* commandLog[]){

    clearStdinCache();
    char* entry = calloc(1,(sizeof commandLog[0]));
    char* value = malloc(40);

    switch (ctx.renderCellX) {
        case 'L':
            commandLog[0] = "Editing Left of Cell. Please Enter Value: ";
            refreshFrame(ctx, commandLog);

            // commit note: softbug fixed through stdin fflush();

            fgets(value, 40, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            commandLog[0] = entry;
            break;

        case 'R':
            commandLog[0] = "Editing Right of Cell. Please Enter Value: ";
            refreshFrame(ctx, commandLog);

            fgets(value, 30, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            commandLog[0] = entry;
            break;

        default:
            commandLog[0] = "Not Editing a Cell Right Now";
            break;

    }
}

void safeRemoveCell(Renderctx ctx, char* commandLog[]){
    commandLog[0] = "Removing Cell";
}

void switchNavPanel(short id, char* commandLog[]){
    printf("%d", id);
}

void clearStdinCache(){
    fflush(stdin);
}

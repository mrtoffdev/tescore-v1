/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "navigation.h"
#include "../view/render.h"

//#region PRIVATE FUNC PROTS
void safeRemoveCell(Renderctx ctx, char commandLog[][509]);
void safeEditCell(Renderctx ctx, char commandLog[][509]);
void switchNavPanel(short, char commandLog[][509]);
//#endregion

int NAVKEY = '1';

// HANDLERS
void navigationKeyHandler(Renderctx ctx, char commandLog[][509]){
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
                    strcpy((char *) commandLog[0], "Resetted all global nav values\n");
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
                    strcpy((char *) commandLog[0], "Operation Mode: 2");
                    ctx.operationMode = 2;
                    ctx.renderCellX = 'L';
                    break;
                } else
                // If on Edit Mode & Selection
                if((ctx.operationMode == 2) && (ctx.renderCellX != 'X')){
                    strcpy((char *) commandLog[0], "Operation Mode: 3");
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
                    strcpy((char *) commandLog[0], "Removing Cell. Press <R> to confirm: ");
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
                strcpy((char *) commandLog[0], "Decremented renderCellIndex:");

            }
            break;

        case 'S':
        case 's':
            if(ctx.renderCellIndex < 9) {
                ctx.renderCellIndex++;

                // Testing
                strcpy((char *) commandLog[0], "Incremented renderCellIndex:");
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
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 1");
            break;

        case '2':
            ctx.renderCellX = 'X';
            ctx.renderCellIndex = 0;
            ctx.operationMode = 1;
            ctx.sessionPanelID = 2;
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 2");
            break;

        case '3':
            ctx.renderCellX = 'X';
            ctx.renderCellIndex = 0;
            ctx.operationMode = 1;
            ctx.sessionPanelID = 3;
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 3");
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

// OPERATIONS
void safeEditCell(Renderctx ctx, char commandLog[][509]){

    fflush(stdin);
    char* entry = calloc(1,(sizeof commandLog[0]));
    char* value = malloc(40);

    switch (ctx.renderCellX) {
        case 'L':
            strcpy((char *) commandLog[0], "Editing Left of Cell. Please Enter Value: ");
            refreshFrame(ctx, commandLog);

            // commit note: softbug fixed through stdin fflush();

            fgets(value, 40, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            strcpy((char *) commandLog[0], entry);
            break;

        case 'R':
            strcpy((char *) commandLog[0], "Editing Right of Cell. Please Enter Value: ");
            refreshFrame(ctx, commandLog);

            fgets(value, 30, stdin);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            strcpy((char *) commandLog[0], entry);
            break;

        default:
            strcpy((char *) commandLog[0], "Not Editing a Cell Right Now");
            break;

    }
}
void safeRemoveCell(Renderctx ctx, char commandLog[][509]){
    strcpy((char *) commandLog[0], "Removing Cell");
}
void switchNavPanel(short id, char commandLog[][509]){
    printf("%d", id);
}

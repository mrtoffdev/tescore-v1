<<<<<<< HEAD
#include "navigation.h"

=======
/*========================================
      NAVIGATION SYSTEM
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Interface
#include "navigation.h"

// Render System
#include "../view/render.h"

// File Operations & Utils
#include "../../io/io.h"

// Merge Sort Call
#include "../../proc/proc.h"

//#region PRIVATE FUNC PROTS
void op_editcell(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]);
void op_rmcell(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]);
//#endregion

int NAVKEY = '1';

// HANDLERS
void navigationKeyHandler(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]){
    // Local Variables
    uint8_t deleteConfirm = 0, // 1 - Confirming, 2 - Confirmed
            quitConfirm = 0,
            haltSort = 0,
            rd_frameID = 0;

    // Start key handler
    indentCursor(1);
    while (NAVKEY != EOF || ctx->handlerMode != 1){
        NAVKEY = _getch();
        ctx->NAVKEY = NAVKEY;

        size_t size_chk = util_fetchmastersize(*in_sctx);

        // ALPHAMERGE SORT ---------------------------------------------------------
        ((size_chk > 0) && (haltSort == 0)) ? module_alphasort(in_sctx, 0, size_chk - 1): 0;

        if (ctx->NAVKEY != 'H' && ctx->NAVKEY != 'h'){rd_frameID = 0;} else {rd_frameID = 1;}

        switch (ctx->NAVKEY) {
            //#region OPERATION KEYS
            case 'Q': case 'q':
                /*
                    Q OPERATION
                        - Checks if the cell selection is not default & currently in edit mode
                            - If true, gets out of edit mode & resets cursor position
                            - If not true (everything is on default i.e. at home screen
                                - Show terminate program prompt
                */
                if(
                    // ON EDIT MODE OR
                    ((ctx->renderCellX != 'X') && (ctx->operationMode != 1) && deleteConfirm == 0) ||
                    // CONFIRMING CELL DELETE
                    ((ctx->renderCellX == 'X') && (ctx->operationMode == 1) && deleteConfirm == 1)
                ){
                    strcpy((char *) commandLog[0], "Resetted all global nav values\n");
                    ctx->renderCellX = 'X';
                    ctx->operationMode = 1;
                    deleteConfirm = 0;
                    break;
                }

                if ((ctx->renderCellX == 'X') && (ctx->operationMode == 1) && (deleteConfirm == 0)){
                    strcpy((char *) commandLog[0], "Terminating Program. Press [Q] to save data & confirm | [E] to cancel");
                    quitConfirm++;

                    if (quitConfirm == 2){
                        // IF NOT ON EDIT MODE / DELETE MODE
                        char* command = calloc(1, strlen(in_sctx->address) + 49);
                        snprintf(command, strlen(in_sctx->address) + 49, "Closing program. Saving & Encrypting all data to %s", in_sctx->address);
                        strcpy((char *) commandLog[0], command);
                        refreshFrame(ctx, in_sctx, commandLog, 0);
                        save_writesheetctx(*in_sctx, in_sctx->address);
                        exit(EXIT_SUCCESS);
                    } else break;
                } else break;
            case 'E': case 'e':
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
                // If on Program Terminate Prompt
                if ((ctx->renderCellX == 'X') && (ctx->operationMode == 1) && quitConfirm != 0){
                    strcpy((char *) commandLog[0], "Cancelled Program Termination");
                    quitConfirm--;
                } else
                // If on View Mode & No Selection
                if((ctx->operationMode == 1) && (ctx->renderCellX == 'X') && ctx->sessionPanelID == 3){
                    strcpy((char *) commandLog[0], "Operation Mode: 2");
                    ctx->operationMode = 2;
                    ctx->renderCellX = 'L';
                    break;
                } else
                // If on Edit Mode & Selection
                if((ctx->operationMode == 2) && (ctx->renderCellX != 'X')){
                    strcpy((char *) commandLog[0], "Operation Mode: 3");
                    ctx->operationMode = 3;
                    op_editcell(ctx, in_sctx, commandLog);
                    ctx->operationMode = 1;
                    ctx->renderCellX = 'X';
                    break;
                } else break;
            case 't': case 'T':
                if ((ctx->NAVKEY == 't' || ctx->NAVKEY == 'T') && ctx->operationMode < 2){
                    strcpy((char *) commandLog[0], "Operation Mode: 2. Adding new Entry: ");
                    // Instantly go to Edit Mode
                    ctx->sessionPanelID = 3;
                    ctx->operationMode = 3;
                    ctx->renderCellIndex = (size_t)util_fetchmastersize(*in_sctx);

                    haltSort = 1;
                    ctx->renderCellX = 'L';
                    op_editcell(ctx, in_sctx, commandLog);
                    ctx->renderCellX = 'R';
                    op_editcell(ctx, in_sctx, commandLog);
                    haltSort = 0;
                    ctx->operationMode = 1;
                    ctx->renderCellX = 'X';
                    break;
                } else break;
            case 'R': case 'r':
                if((ctx->operationMode == 1) && (ctx->renderCellX == 'X')){
                    deleteConfirm++;
                    strcpy((char *) commandLog[0], "Removing Cell. Press <R> to confirm: ");
                    if (deleteConfirm == 2){
                        deleteConfirm = 0;
                        op_rmcell(ctx, in_sctx,commandLog);
                    }
                    break;
                } else break;
                //#endregion
            //#region NAVIGATION KEYS
        case 'W':
        case 'w':
            if(ctx->renderCellIndex > 0) {
                ctx->renderCellIndex--;
                if (ctx->renderCellIndex < ctx->buffer_start){
                    ctx->buffer_start--;
                    ctx->buffer_end--;
                }
                // Testing
                strcpy((char *) commandLog[0], "Decremented renderCellIndex:");

            }
            break;

        case 'S':
        case 's':
            // Check if on Ranker Panel
            if (ctx->sessionPanelID != 2){
                if((ctx->renderCellIndex+1 < util_fetchmastersize(*in_sctx)) && util_fetchmastersize(*in_sctx) != 0) {
                    ctx->renderCellIndex++;
                    if (ctx->renderCellIndex >= ctx->buffer_end){
                        ctx->buffer_end++;
                        ctx->buffer_start++;
                    }
                    // Testing
                    strcpy((char *) commandLog[0], "Incremented renderCellIndex:");
                } else break;
            } else {
                if (ctx->renderCellIndex < 9){
                    ctx->renderCellIndex++;
                }
            }

            break;

        case 'A':
        case 'a':
            if(ctx->operationMode == 2) {
                ctx->renderCellX = 'L';
                break;
            } else break;

        case 'D':
        case 'd':
            if(ctx->operationMode == 2) {
                ctx->renderCellX = 'R';
                break;
            } else break;
            //#endregion
            //#region PANEL KEYS
        case '1':
            ctx->renderCellX = 'X';
            ctx->renderCellIndex = 0;
            ctx->operationMode = 1;
            ctx->sessionPanelID = 1;
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 1");
            break;

        case '2':
            ctx->renderCellX = 'X';
            ctx->renderCellIndex = 0;
            ctx->operationMode = 1;
            ctx->sessionPanelID = 2;
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 2");
            break;

        case '3':
            ctx->renderCellX = 'X';
            ctx->renderCellIndex = 0;
            ctx->operationMode = 1;
            ctx->sessionPanelID = 3;
            strcpy((char *) commandLog[0], "Resetted all global nav values. Rendering Panel No: 3");
            break;

        default:
            break;
            //#endregion
        }

        indentCursor(1);

        // check if panelID values have changed and render frame ID
        // prevents re-rendering the frame if panelID hasn't changed

        // Update references
        refreshFrame(ctx, in_sctx, commandLog, rd_frameID);
    }
}

// CRUD OPERATIONS
void op_editcell(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]){

    fflush(stdin);
    char* entry = calloc(1,(sizeof commandLog[0]));
    char* value = malloc(40);

    switch (ctx->renderCellX) {
        case 'L':
            strcpy((char *) commandLog[0], "Editing Name of Cell. Please Enter Name: ");
            refreshFrame(ctx, in_sctx, commandLog, 0);

            // commit note: softbug fixed through stdin fflush();

            fgets(value, 40, stdin);
            size_t valuelen = strlen(value);
            value[valuelen-1] = '\0';
            strcpy(in_sctx->masterlist[ctx->renderCellIndex].indexName, value);
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            strcpy((char *) commandLog[0], entry);
            break;

        case 'R':
            strcpy((char *) commandLog[0], "Editing Value of Cell. Please Enter Value: ");
            refreshFrame(ctx, in_sctx, commandLog, 0);

            fgets(value, 30, stdin);
            int ctr_gradeval = strtol(value, NULL, 10);
            in_sctx->masterlist[ctx->renderCellIndex].value = (short)ctr_gradeval;
            strncat(entry, "Entered Value: ", 16);
            strncat(entry, value, strlen(value));
            strcpy((char *) commandLog[0], entry);
            break;

        default:
            strcpy((char *) commandLog[0], "Not Editing a Cell Right Now");
            break;

    }
}
void op_rmcell(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]){
    // Print Dialogue
    strcpy((char *) commandLog[0], "Removing Cell");

    // Fetch Ctx
    const size_t deletedindex = ctx->renderCellIndex;
    const size_t sctx_mstrct = util_fetchmastersize(*in_sctx);

    // Move index above to current deleted index
    for (size_t i = deletedindex; i < sctx_mstrct; ++i) {
        strcpy(in_sctx->masterlist[i].indexName, in_sctx->masterlist[i+1].indexName);
        in_sctx->masterlist[i].value = in_sctx->masterlist[i+1].value;
    }

    // Reset Viewbuffer
    ctx->buffer_start = 0;
    ctx->buffer_end = 10;
    ctx->renderCellIndex = 0;
}
>>>>>>> main

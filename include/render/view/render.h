/*========================================
      FRAME RENDERING SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/

#ifndef TESCORE_RENDER_H
#define TESCORE_RENDER_H

#include "../../model/models.h"
#include "../../model/renderctx.h"

#define MAX_PASS_CHAR 30

// =========== UI UTILS ===========
void refreshFrame(Renderctx in_rctx, Sheetctx in_sctx,char commandLog[][509]);
void clearScreen();
void indentCursor(short spaces);
void generateGraph(Sheetctx in_sctxmasterlist);
void defaultMasterListRow(char* indexName, int indexVal);

// =========== PROMPTS ===========
void terminatePrompt();
void authFrame();

// =========== UI ELEMENTS ===========
void renderWhiteSpace(int);
void renderSeparator(short id);

// =========== UI PANELS ===========
void renderHeader(Renderctx ctx);
void renderSubHeader();
void renderMatrixRankerRow(char* indexNameContainer[10], short* indexValContainer, Renderctx in_rctx);
void renderMasterListHeader(short panelID);
void renderMasterListRow(Index sctx_masterlist[], short selectionID, char selectionX, short panelID);

#endif
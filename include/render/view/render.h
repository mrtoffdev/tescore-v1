<<<<<<< HEAD
#ifndef TESCORE_RENDER_H
#define TESCORE_RENDER_H

// rendering interfaces
void refreshFrame();
void renderAuth();
void renderSeparatorH();

// typeface modifications
char* typefaceBold(int, char*);
char* typefaceItalic(int, char*);
char* typefaceUnderline(int, char*);

char* typefaceReset(char*);
char* typefaceColor(int, char*);

#endif
=======
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
void refreshFrame(Renderctx* in_rctx, Sheetctx* in_sctx,char commandLog[][509], uint8_t rd_frameID);
void clearScreen();
void indentCursor(short spaces);
void generateGraph(Sheetctx in_sctxmasterlist);
void defaultMasterListRow(char* indexName, int indexVal);

// =========== UI ELEMENTS ===========
void renderWhiteSpace(int);
void renderSeparator(short id);

// =========== UI PANELS ===========
void frame_helperpanel();
void renderHeader(Renderctx ctx, Sheetctx in_sctx);
void renderSubHeader();
void renderMatrixRankerRow(char rg_collection[][2][MAXNAMECHARLIMIT], Renderctx in_rctx);
void renderMasterListHeader(short panelID);
void renderMasterListRow(Index sctx_masterlist[], Renderctx in_rctx);

#endif
>>>>>>> main

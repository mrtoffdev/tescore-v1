/*========================================
      RENDER SYSTEM CONTEXT MODEL
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_RENDERCTX_H
#define TESCORE_RENDERCTX_H

#include <stdint.h>
#include "models.h"

#define MAXCOMMANDENTRIES 10
typedef struct Renderctx {
    Sheetctx    SessionSheet;                       // Main Datasheet
    char        renderCellX;                        // Selection for Operation
    uint8_t     NAVKEY,                             // Navigation Key
                handlerMode,                        // Navigation Handler Mode
                operationMode,                      // Program Operation Mode
                sessionPanelID,                     // Frame Panel to Render
                renderCellIndex;                    // Frame Index to Render
    char*       sheetName,                          // Embedded Sheet Name
                commandLog[MAXCOMMANDENTRIES];      // Command Log Entries Container

// Legacy props
//                graphLayout[10][11],                // Bar Graph Layout Container
//    int         distributionTable[11][2];           // Student Distribution Reference for Graph Gen
} Renderctx;

#endif

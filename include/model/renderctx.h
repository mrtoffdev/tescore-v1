/*========================================
      RENDER SYSTEM CONTEXT MODEL
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_RENDERCTX_H
#define TESCORE_RENDERCTX_H

#include <stdint.h>
#include "models.h"

typedef struct Renderctx {
    char        renderCellX;                        // Selection for Operation
    uint8_t     NAVKEY,                             // Navigation Key
                handlerMode,                        // Navigation Handler Mode
                operationMode,                      // Program Operation Mode
                sessionPanelID,                     // Frame Panel to Render
                renderCellIndex,                    // Frame Index to Render
                buffer_start,
                buffer_end;
} Renderctx;

#endif

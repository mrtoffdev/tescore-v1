<<<<<<< HEAD
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

void navigate(int);
void resetNav();
=======
/*========================================
      NAVIGATION SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_NAVIGATION_H
#define TESCORE_NAVIGATION_H

#include "../../model/models.h"
#include "../../model/renderctx.h"

// VOID
void navigationKeyHandler(Renderctx* ctx, Sheetctx* in_sctx, char commandLog[][509]);
>>>>>>> main

#endif

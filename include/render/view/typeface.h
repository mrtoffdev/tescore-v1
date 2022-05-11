/*========================================
      TYPEFACE OPERATIONS
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_TYPEFACE_H
#define TESCORE_TYPEFACE_H

#define MAXADDRLENGTH 509
//#region =========== DEFAULT COLOR PALETTE DEFS ===========
#define DEFAULTFOREGROUND "x1B[38;5;15m"
#define DEFAULTBACKGROUND "x1B[48;5;0m"

#define SELECTIONFOREGROUND "x1B[38;5;16m"
#define SELECTIONBACKGROUND "x1B[48;5;7m"
//#endregion

// PANEL UTILS
char* charHighlightBG(char* inputsrc, short bgID, char* commandLog[]);

// TYPEFACE UTILS
char* charForeground(char* inputsrc, short fgID, char* commandLog[]);

#endif //TESCORE_TYPEFACE_H

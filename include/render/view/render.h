/*========================================
      FRAME RENDERING SYSTEM HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/

/* RENDERING SYSTEM

    FUNCTION CALLS
        - refreshFrame()    : Rendering the main interactive GUI for the first time
        -

    BAR GRAPH - 2D Char Matrix System
        - Divide the number of students into 10
            - If divisible by 10, set all notches with $Quotient increments
            - If not divisible by 10, divide by 9, set all notches with $Quotient increments, and set the last / highest notch to remainder
                - e.g. 81 =

    REFRESHING FRAMES
        - Refresh call will re-render all three panels
        - refreshFrame() will also be the primary call when rendering the panels for the first time

*/

#ifndef TESCORE_RENDER_H
#define TESCORE_RENDER_H

#include "../../model/datamodel.h"

#define MAX_PASS_CHAR 30

// =========== UI UTILS ===========
void refreshFrame(DATASHEET sessionSheet, short panelID, short selectionID, char selectionX, char* commandLog[]);
void clearScreen();
void indentCursor(short spaces);
void generateGraph();
void defaultMasterListRow(char* indexName, int indexVal);

// =========== PROMPTS ===========
void terminatePrompt();
void authFrame();

// =========== UI ELEMENTS ===========
void renderWhiteSpace(int);
void renderSeparator(short id);

// =========== UI PANELS ===========
void renderHeader(int sessionStudentCount, short panelID, char* commandLog[]);
void renderSubHeader();
void renderMatrixRankerRow(char* indexNameContainer[10], int* indexValContainer, short selectionID, char selectionX, short panelID);
void renderMasterListHeader(short panelID);
void renderMasterListRow(char* indexName, int indexVal, short selectionID, char selectionX, short panelID, int i);

// =========== TYPEFACE MODIFICATIONS ===========
char* typefaceBold(int, char*);
char* typefaceItalic(int, char*);
char* typefaceUnderline(int, char*);

char* typefaceReset(char*);
char* typefaceColor(int, char*);
#endif

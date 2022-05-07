/*========================================
      FRAME RENDERING
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

// FRAMES
void refreshFrame(DATASHEET);
void authFrame();

// PROMPTS
void terminatePrompt();

// UI ELEMENTS
void clearScreen();
void indentCursor();
void renderWhiteSpace(int);
void renderSeparator();

void renderHeader(int sessionStudentCount);
void renderSubHeader();
void renderUpperRow();
void renderMasterListHeader();
void renderMasterListRow();

// typeface modifications
char* typefaceBold(int, char*);
char* typefaceItalic(int, char*);
char* typefaceUnderline(int, char*);

char* typefaceReset(char*);
char* typefaceColor(int, char*);
#endif

/*========================================
      FRAME RENDERING
      Author: Christopher Abadillos Jr.
  ========================================*/

/* RENDERING SYSTEM

    FUNCTION CALLS
        - refreshFrame()    : Renders the main interactive GUI for the first time
        - terminatePrompt() : Renders the program termination prompt

    BAR GRAPH - 2D Char Matrix System
        - Divide the number of students into 10
            - If divisible by 10, set all notches with $Quotient increments
            - If not divisible by 10, divide by 9, set all notches with $Quotient increments, and set the last / highest notch to remainder
                - e.g. 81 =

    REFRESHING FRAMES
        - Refresh call will re-render all three panels
        - refreshFrame() will also be the primary call when rendering the panels for the first time

*/

#include <stdio.h>
#include <conio.h>

#include "render.h"

#define MAX_PASS_CHAR 30

// GLOBAL VARS
short panelID = 1;

void refreshFrame(){

    printf("\tTesting Render Frame\n");

    int navIndex = 1;
    int maxBackSpace = 0;
    int passChar = 0;

    printf("----  Renderer Debug: ----\n");
    printf("-----------------------------------\n"
                  "|                                 |\n");
    printf("-----------------------------------");
    printf("\x1b[1A");
    printf("\x1b[33D");

    while (navIndex != EOF){
        navIndex = _getch();

        maxBackSpace = maxBackSpace < 0 ? 0 : maxBackSpace;

        if (navIndex != 8 && passChar <= MAX_PASS_CHAR){
            maxBackSpace++;
            passChar++;
            printf("%c",navIndex);
        }

        if (navIndex == 8 && maxBackSpace > 0){
            maxBackSpace--;
            printf("\x1b[1D");
            printf(" ");
            printf("\x1b[1D");
        }
    }

}

void terminatePrompt(){

}

// Notes:
// #include <windows.h>
// SetConsoleOutputCP(CP_UTF8);

/* ANSI REFERENCES


 */
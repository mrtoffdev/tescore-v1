/*========================================
    AUTHENTICATION FRAME
    Author: Christopher Abadillos Jr
  ========================================*/
#include <stdio.h>
//#include <conio.h>

#include "render.h"

// =========== AUTHENTICATION ===========
void authFrame(){
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

    while ((navIndex != EOF) && (navIndex != '\n')){
        //navIndex = _getch();

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
    puts("Exited Prompt");
}
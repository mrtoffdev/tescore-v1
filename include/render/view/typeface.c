/*========================================
      TYPEFACE OPERATIONS
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <string.h>
#include <malloc.h>

#include "render.h"
#include "typeface.h"

/*

    ANSI TYPEFACE REFERENCE TABLE:

    #define STYLE_UNDERLINE     "\033[4m"
    #define STYLE_NO_UNDERLINE  "\033[24m"
    #define STYLE_BOLD          "\033[1m"
    #define STYLE_NO_BOLD       "\033[22m"

    #define TYPEFACE_BLACK      "\033[0;30m"
    #define TYPEFACE_RED        "\033[0;31m"
    #define TYPEFACE_GREEN      "\033[0;32m"
    #define TYPEFACE_YELLOW     "\033[0;33m"
    #define TYPEFACE_BLUE       "\033[0;34m"
    #define TYPEFACE_PURPLE     "\033[0;35m"
    #define TYPEFACE_CYAN       "\033[0;36m"
    #define TYPEFACE_WHITE      "\033[0;37m"

*/


char* charHighlightBG(char* inputsrc, short bgID, char* commandLog[]){
    char* returnChar = malloc(MAXADDRLENGTH);

    switch (bgID) {
        case 1:
            strcat(returnChar, DEFAULTBACKGROUND);
            strcat(returnChar, inputsrc);
            strcat(returnChar, DEFAULTBACKGROUND);
            commandLog[0] = "Switched BG to ID:1";
            return returnChar;

        case 2:
            strcat(returnChar, SELECTIONBACKGROUND);
            strcat(returnChar, inputsrc);
            strcat(returnChar, DEFAULTBACKGROUND);
            commandLog[0] = "Switched BG to ID:2";
            return returnChar;

        default:
            break;
    }
    return returnChar;
}

char* charForeground(char* inputsrc, short fgID, char* commandLog[]){
    char* returnChar = malloc(MAXADDRLENGTH);

    switch (fgID) {
        case 1:
            strcat(returnChar, DEFAULTFOREGROUND);
            strcat(returnChar, inputsrc);
            strcat(returnChar, DEFAULTFOREGROUND);
            commandLog[0] = "Switched FG to ID:1";
            return returnChar;

        case 2:
            strcat(returnChar, SELECTIONFOREGROUND);
            strcat(returnChar, inputsrc);
            strcat(returnChar, DEFAULTFOREGROUND);
            commandLog[0] = "Switched FG to ID:2";
            return returnChar;

        default:
            break;
    }
    return returnChar;
}


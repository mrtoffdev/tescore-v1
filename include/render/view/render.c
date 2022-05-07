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

// =========== UI ELEMENTS ===========
void clearScreen(){
    printf("\x1b[2J\x1b[H");
}

void renderWhiteSpace(int spaceSize){
    for (int i = 0; i < spaceSize; ++i) {
        printf("\n");
    }
}

void renderSeparator(){
    puts("\t-------------------------------------------------------------------------------------------------------------");

}

void indentCursor(){
    printf("\t");
}


void renderHeader(int sessionStudentCount){
    printf("\t|\t\t\t- Data Sheet -\t\t\t    |\t - Top 10 Students / %4d - \t|   Score   |\n",
           sessionStudentCount);
}

void renderSubHeader(int gradeScaling[11], char *sheetName){
    int bottom[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("\t|    |%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d| Sheet Name: %-18s \t|\t    |\n",
           gradeScaling[0],
           gradeScaling[1],
           gradeScaling[2],
           gradeScaling[3],
           gradeScaling[4],
           gradeScaling[5],
           gradeScaling[6],
           gradeScaling[7],
           gradeScaling[8],
           gradeScaling[9],
           gradeScaling[10],
           sheetName);
}

void renderUpperRow(int studentScaling[], int gradeScaling[], char matrixGraph[][11], int rowScale){

    int tableValY[] = {10};
    int bottom[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    char *barMatrix[10][10];

    for (int i = 0; i < rowScale; ++i) {
        printf("\t|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|%4d|  • Barack Obama \t\t\t|    100    |\n",
               tableValY[0],
               bottom[0],
               bottom[1],
               bottom[2],
               bottom[3],
               bottom[4],
               bottom[5],
               bottom[6],
               bottom[7],
               bottom[8],
               bottom[9],
               bottom[10]);
    }

}


void renderMasterListHeader(){
    printf("\t|\t\t\t\t- Student Submission List -\t\t\t\t\t|           |\n");
}

void renderMasterListRow(){
    printf("\t| • %-90s  |    %4d   |\n", "Michael Reeves", 23);
}

// =========== TESTS ===========

/* ENABLING UTF8 SUPPORT FOR MICROSOFT WINDOWS CONSOLES

    #include <windows.h>
    SetConsoleOutputCP(CP_UTF8);

*/

/* ANSI REFERENCES


 */
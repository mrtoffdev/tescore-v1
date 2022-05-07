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

#include "render.h"

// GLOBAL VARS

// =========== MAIN PANELS ===========
void refreshFrame(DATASHEET sessionSheet){

    /* ORDER OF UI ELEMENTS
        - Separator
        - Header (Number of Students)
        - Separator
        - Upper Rows
            - x10 formatted lines
        - Separator
        - Sub Header
        - Separator
            - x10 formatted lines
    */

    int indexCount = sizeof (sessionSheet.masterlistCollection.container) / sizeof (sessionSheet.masterlistCollection.container[0]);

    // TESTING RENDER MODULES
        renderWhiteSpace(3);

        // UPPER PANEL
            renderSeparator();
            renderHeader(indexCount);
            renderSeparator();

            int     studentScaling[10] = {
                    5, 10, 15, 20, 25, 30, 35, 40, 45, 50},
                    gradeScaling[11] = {
                    0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
                    };
            int     rowCount = 10,
                    sheetMaxScore,
                    sheetMaxStudents;
            char    matrixGraph[10][11];

            renderUpperRow(studentScaling, gradeScaling, matrixGraph, rowCount);

            renderSeparator();
            renderSubHeader(gradeScaling, "ShortLigmaBols");
            renderSeparator();

        // LOWER PANEL
            renderMasterListHeader();
            for(int i = 0; i < 10; i++){
                renderMasterListRow();
            }
            renderSeparator();

}

// =========== PROMPTS ===========
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
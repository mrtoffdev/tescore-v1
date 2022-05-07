/*========================================
    MAIN EXECUTABLE
    Author: Christopher Abadillos Jr
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "include/io/io.h"
#include "include/render/render.h"
#include "include/render/navigation/navigation.h"

/*

    PROCESS TREE

        1. Open file Through IO.h | Decrypt with corresponding passkey
        2. Disassemble Sheet for Ranker & Masterlist Modules
        3. Send Subsheet to Modules (Ranker & Masterlist)
        4. Get Sorted Subsheets
        5. Send Sorted Subsheets to Render.h
        6. Render Graph, Table, and Masterlist
        7. Open navigation buffer


    ACCESS TREE

        - Only [Navigation.c/h] & [Main.c] has access to [Render.c/h]
            - Only Main.c & Navigation.c/h will be rendering frames / causing frame re-renders

        - Only [Navigation.c/h] & [Main.c] has access to [IO.h]
            - Only Main.c & Navigation.c/h will be using FileOps

        - Only [Main.c] has access to [/sort] modules

        - Only [IO.h] has access to [Decrypt.c], [Encrypt.c], & [CRUD.c]
            - IO.h serves as a collective interface to multiple CRUD / FileOps modules

*/

// GLOBAL VARIABLES
int         testVal = 100,
            sessionStudentCount;
short       panelID;

FILE        *SessionDIB;
SUBSHEET    RankerSheet,
            MasterListSheet;

//#region CONSOLE SETUP: WINDOW RESIZE FUNCTION
//HANDLE      wHnd;    // Handle to write to the console.
//HANDLE      rHnd;    // Handle to read from the console.

//    // Set up the handles for reading/writing:
//    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
//    rHnd = GetStdHandle(STD_INPUT_HANDLE);
//    // Change the window title:
//    // Set up the required window size:
//    SMALL_RECT windowSize = {1000, 0, 2000, 100};
//    SetConsoleWindowInfo(wHnd, 1, &windowSize);
//    // Change the console window size:
//    // Create a COORD to hold the buffer size:
//    COORD bufferSize = {10, 10};
//    SetConsoleScreenBufferSize(wHnd, bufferSize);
//#endregion

int main() {
    // =========== CONSOLE SETUP: WIN32 ===========
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(WINDOWTITLE);

    //#region =========== OPEN FILE ===========

    // FILE CHECK
    while (SessionSheetFile == NULL){
        printf("Enter Datasheet Name: (Default: demo.txt) ");
        char* FileAddress = malloc(MAXADDRLENGTH);
        if(scanf("%s", FileAddress) != EOF){

        SessionDIB = openFile(FileAddress);
        char *temp = malloc(MAXADDRLENGTH);

            //#region FILE READ TEST
//            char *temp = malloc(MAXADDRLENGTH);
//
//            fscanf(SessionSheetFile, "%s", temp);
//
//            puts("\n---------- Read File Contents ----------\n");
//            printf("%s\n", temp);
//
//            free(FileAddress);
//            free(temp);
//#endregion
        }
    }

    // =========== DISASSEMBLE ===========
    // =========== SEND SUBSHEETS ===========
    // =========== FETCH SHEETS ===========
    // =========== RENDER SHEETS ===========
    refreshFrame();

    // =========== NAVIGATION ===========
    int NAVKEY = '1';

    while (NAVKEY != EOF){
        NAVKEY = _getch();
        parseNavigationKey(NAVKEY, panelID);
    }

    // =========== TERMINATE PROGRAM ===========
    puts("Program Exit");
    system("pause");
    return 0;
}

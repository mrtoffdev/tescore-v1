/*========================================
      MAIN EXECUTABLE
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>

#include "include/io/io.h"
#include "include/render/view/render.h"
#include "include/model/renderctx.h"
#include "include/render/navigation/navigation.h"
#include "include/sort/masterlist/alphaMergeSort.h"

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

#define WINDOWTITLE "TESCORE: Grading Sheet Inspector"
#define COMMANDLOGMAXENTRY 10

// DEVOPS
#define SANDBOX 1
#define SANDBOXID 2
void sandbox_scriptTesting();

// GLOBALS
FILE*       SessionSheetFile;

//#region CONSOLE WINDOW RESIZE FUNCTION
HWND WINAPI GetConsoleWindowNT(void)
{
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
            ,TEXT("GetConsoleWindow"));
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    return GetConsoleWindow();
}
//#endregion

int main() {

    //#region =========== CONSOLE SETUP: WIN32 ===========
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle(WINDOWTITLE);
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,450,200,1020,650,TRUE);
    //#endregion

    //#region =========== MAIN PROCESS ===========

    //#region INIT CONTEXTS
    char            commandLog[COMMANDLOGMAXENTRY][509];
    DATASHEET       sessionSheet;
    Renderctx       tescore_render_ctx;

    sheet_fetch_ctx(SessionSheetFile);
    tescore_render_ctx = render_init_ctx(sessionSheet);
    //#endregion

    // CHECKS RENDER SYSTEM MODE (TESTING / RELEASE)
    switch (SANDBOX) {
        case 0:
            refreshFrame(tescore_render_ctx, commandLog);
            break;

        case 1:
            sandbox_scriptTesting();
            break;

        default:
            break;
    }

    indentCursor(1);

    // START NAVIGATION HANDLER AFTER INIT RENDER
    navigationKeyHandler(tescore_render_ctx,  commandLog);

    puts("PROGRAM INTERRUPTED");
    system("pause");
    return 0;
    //#endregion
}

void sandbox_scriptTesting(){

    // Generator Init Data
    char *studentData[10][2] = {
            {"Fridge Grills", "85"},
            {"Window Tab Post", "92"},
            {"Roof Leaf", "96"},
            {"Coconut Rock", "79"},
            {"Shirt Switch Root", "86"},
            {"Screen Fruit", "88"},
            {"White Fan", "94"},
            {"Light Wall", "82"},
            {"Cloud Plane", "77"},
            {"Escaped Post", "97"}
    };

    //#region =========== ALPHAMERGESORT.H ===========
    if(SANDBOXID == 1){

        // Generate Extended List of 10 units
        struct strec extendedList[10];
        for (int i=0; i<10; i++) {
            strcpy(extendedList[i].name, studentData[i][0]);
            extendedList[i].score = atoi(studentData[i][1]);
        }
        printf("Generated Unsorted List:\n");
        for (int i=0; i<10; i++) {
            printf("%s : %d\n", extendedList[i].name, extendedList[i].score);
        }

        printf("\nSorting List...\n");
        alphaMergeSort(extendedList, 0, 9);

        printf("Generated Sorted List:\n");
        for (int i=0; i<10; i++) {
            printf("%s : %d\n", extendedList[i].name, extendedList[i].score);
        }

    } else
    if(SANDBOXID == 2){
        // TESTING FILE ENCRYPTION
        char* plain_strSrcBuffer = calloc(1024, 509);
        plain_strSrcBuffer = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.000";
//        plain_strSrcBuffer = "Tescore is a terminal-based grading sheet inspector that supports a dynamic, interactive user interface\nThere is no spoon.";

        testing(plain_strSrcBuffer);
    } else
    if(SANDBOXID == 3){


    }
    //#endregion
}
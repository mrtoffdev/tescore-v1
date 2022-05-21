/*========================================
      MAIN EXECUTABLE
      Author: Christopher Abadillos Jr.
  ========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>

// Models
#include "include/model/models.h"

// File Operations / CRUD
#include "include/io/io.h"

// Render System
#include "include/render/view/render.h"

// Navigation System
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

        - Only [Main.c] has access to [/proc] modules

        - Only [IO.h] has access to [Decrypt.c], [Encrypt.c], & [CRUD.c]
            - IO.h serves as a collective interface to multiple CRUD / FileOps modules

*/

#define WINDOWTITLE "TESCORE: Grading Sheet Inspector"
#define COMMANDLOGMAXENTRY 10

// DEVOPS
#define SANDBOX 1
#define SANDBOXID 1
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
    if (SANDBOX == 1){
        MoveWindow(hWnd,500,0,1100,1140,TRUE);
    } else {
        MoveWindow(hWnd,450,200,1020,650,TRUE);
    }
    //#endregion

    char        commandLog[COMMANDLOGMAXENTRY][509];
    Renderctx   global_renderctx;
    Sheetctx    global_Sheetctx;

    global_Sheetctx = save_readsheetctx();
    global_renderctx = init_renderctx(global_Sheetctx);

    // CHECKS RENDER SYSTEM MODE (TESTING / RELEASE)
    SANDBOX == 1 ? sandbox_scriptTesting() : 0;

    // START NAVIGATION HANDLER AFTER INIT RENDER
    refreshFrame(global_renderctx, global_Sheetctx, commandLog);
    navigationKeyHandler(global_renderctx,  global_Sheetctx, commandLog);

    // PROGRAM INTERRUPTION
    puts("PROGRAM INTERRUPTED");
    system("pause");
    return EXIT_SUCCESS;
}

void sandbox_scriptTesting(){

    //#region =========== SANDBOX SCRIPTS ===========
    if(SANDBOXID == 1){
//        script_fileopsTesting();
        CRUD_TEST();
    } else
    if(SANDBOXID == 2){
        exit(0);
    }
    //#endregion
}
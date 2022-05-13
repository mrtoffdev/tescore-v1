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
#define SANDBOX 0

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
    char*       commandLog[COMMANDLOGMAXENTRY];
    FILE*       SessionSheetFile;
    DATASHEET   sessionSheet;
    Renderctx   tescore_render_ctx;

    sheet_fetch_ctx(SessionSheetFile);
    tescore_render_ctx = render_init_ctx(sessionSheet);

    // CHECKS RENDER SYSTEM MODE (TESTING / RELEASE)
    switch (SANDBOX) {
        case 1:
//            testing();
            break;

        case 0:
            refreshFrame(tescore_render_ctx, commandLog);
            break;

        default:
            testing();
            break;
    }

    indentCursor(1);

    // START NAVIGATION HANDLER AFTER INIT RENDER
    navigationKeyHandler(tescore_render_ctx, commandLog);

    puts("PROGRAM INTERRUPTED");
    system("pause");
    return 0;
    //#endregion
}

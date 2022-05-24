/*========================================
      MAIN EXECUTABLE
      Author: Christopher Abadillos Jr.
  ========================================*/
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <stdint.h>

// Models
#include "include/model/models.h"

// File Operations / CRUD
#include "include/io/io.h"

// Render System
#include "include/render/view/render.h"

// Navigation System
#include "include/render/navigation/navigation.h"

#define WINDOWTITLE "TESCORE: Grading Sheet Inspector"
#define COMMANDLOGMAXENTRY 10

// DEVOPS
#define DEBUGMODE 0
#define SANDBOX 0
#define SANDBOXID 1
void sandbox_scriptTesting();

//#region CONSOLE WINDOW RESIZE FUNCTION
//HWND WINAPI GetConsoleWindowNT(void)
//{
//    typedef HWND WINAPI(*GetConsoleWindowT)(void);
//    GetConsoleWindowT GetConsoleWindow;
//    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
//    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
//            ,TEXT("GetConsoleWindow"));
//    if(GetConsoleWindow == NULL){
//        return NULL;
//    }
//    return GetConsoleWindow();
//}
//#endregion

int main() {

    //#region =========== CONSOLE SETUP: WIN32 ===========
//    SetConsoleOutputCP(CP_UTF8);
//    SetConsoleTitle(WINDOWTITLE);
//    HWND hWnd=GetConsoleWindowNT();
//    if (SANDBOX == 1){
//        MoveWindow(hWnd,500,0,1100,1140,TRUE);
//    } else {
//        MoveWindow(hWnd,450,200,1020,650,TRUE);
//    }
    //#endregion

    // INIT CONTAINERS & CONTEXTS
    char        commandLog[COMMANDLOGMAXENTRY][509];
    Renderctx   global_renderctx;
    Sheetctx    global_Sheetctx;

    // Initialize Default Render Context
    global_Sheetctx = save_readsheetctx();
    sprintf(commandLog[0], "Finished Loading Data From: %s | Press [H] to show controls / keybindings", global_Sheetctx.address);

    // Deconstruct sheet
    global_renderctx = init_renderctx(global_Sheetctx);

    DEBUGMODE == 1 ? printf("received address: %s\n", global_Sheetctx.address): 0;
    DEBUGMODE == 1 ? system("pause"): 0;

    // Check for testing / release mode
    SANDBOX == 1 ? CRUD_TEST(global_Sheetctx): 0;

    // Refresh frame & start handler
    refreshFrame(&global_renderctx, &global_Sheetctx, commandLog, 0);
    navigationKeyHandler(&global_renderctx,  &global_Sheetctx, commandLog);


    puts("PROGRAM INTERRUPTED");
    //system("pause");
    return EXIT_SUCCESS;
}

void sandbox_scriptTesting(){

    //#region =========== SANDBOX SCRIPTS ===========
    if(SANDBOXID == 1){

    } else
    if(SANDBOXID == 2){
        exit(0);
    }
    //#endregion
}

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

int main() {
    // =========== OPEN FILE ===========
    printf("Debugging: IO %d\n", testVal);
    printf("Enter Datasheet Name: (Default: demo.txt) ");

    char* FileAddress = malloc(MAXADDRLENGTH);
    if(scanf("%s", FileAddress) != EOF){

        SessionDIB = openFile(FileAddress);
        char *temp = malloc(MAXADDRLENGTH);

        fscanf(SessionDIB, "%s", temp);
        puts("\n\n---------- Read File Contents ----------\n");
        printf("%s\n", temp);

        free(FileAddress);
        free(temp);
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

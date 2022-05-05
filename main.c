/*========================================
    MAIN EXECUTABLE
    Author: Christopher Abadillos Jr
  ========================================*/
#include <stdio.h>
#include <stdlib.h>

#include "include/io/io.h"
#include "include/render/render.h"

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

        - Only [Main.c] has access to [IO.h]
            - Only Main.c will be using FileOps

        - Only [Main.c] has access to [/sort] modules

        - Only [IO.h] has access to [Decrypt.c], [Encrypt.c], & [CRUD.c]
            - IO.h serves as a collective interface to multiple CRUD / FileOps modules

*/

// GLOBAL VARIABLES
int testVal = 100,
    panelID,
    sessionStudentCount;

int main() {

    // =========== OPEN FILE ===========
    printf("Debugging: IO %d\n", testVal);
    FILE *LocalDIB;

    printf("Enter Datasheet Name: (Default: demo.txt) ");

    char* FileAddress = malloc(MAXADDRLENGTH);
    if(scanf("%s", FileAddress) != EOF){

        LocalDIB = openFile(FileAddress);
        char *temp = malloc(MAXADDRLENGTH);

        fscanf(LocalDIB, "%s", temp);
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
    // =========== TERMINATE PROGRAM ===========
    puts("Program Exit");
    system("pause");
    return 0;
}

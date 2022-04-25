#include <stdio.h>
#include <stdlib.h>

#include "io.h"

FILE* openFile(char*);

void testing(char* FileAddress){
    FILE *DIB = openFile(FileAddress);

    char *temp = malloc(MAXSTRLEN);
    fscanf(DIB, "%s", temp);
    puts("\n\n---------- Read File Contents ----------\n");
    printf("%s\n", temp);
    free(temp);
}

FILE* openFile(char* FileAddress){
    FILE *DIB;

    if ((DIB = fopen(FileAddress,"r")) == NULL){

        // default file prompt
        printf("Invalid Filename. Use default file? (y/n): ");

        char temp;
        scanf("%s", &temp);

        if(temp == 'y'){
            DIB = fopen(DEFAULTFILEADDRESS, "r");
            puts("Loaded default input file.");
            system("pause");
            return DIB;
        } else {
            system("pause");
            exit(1);
        }
    }
    return DIB;
}
#include <stdio.h>
#include <stdlib.h>

#include "io.h"

void testing(){
    FILE *DIB;
    if ((DIB = fopen(FILEADDRESS,"r")) == NULL){
        printf("Invalid Filename\n");
        system("pause");
        exit(1);
    }

    char *temp = malloc(MAXSTRLEN);
    fscanf(DIB, "%s", temp);

    printf("%s\n", temp);
}

void append(){


}


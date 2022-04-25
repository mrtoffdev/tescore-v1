// main exec: Toff
#include <stdio.h>
#include <stdlib.h>

#include "include/io/io.h"

int main() {
    puts("Debugging: IO");

    char* FileAddress = malloc(MAXSTRLEN);
    printf("Enter Datasheet Name: (Default: demo.txt) ");
    if(scanf("%s", FileAddress) != EOF){
        testing(FileAddress);
        free(FileAddress);
    }

    puts("Program Exit");
    system("pause");
    return 0;
}

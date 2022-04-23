// main exec: Toff
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "include/lemao.h"

int main() {
    printf("Hello, World!\n");
//    printf("Current typed text: %c", getchar());
    char vard;
    while (vard != EOF){
        vard = _getch();
        switch (vard) {
            case '1':
                printf("Typed 1\n");
                break;
            case '2':
                printf("Typed 2\n");
                break;
            default:
                printf("Invalid\n");
                break;
        }
    }

    system("pause");
    return 0;
}

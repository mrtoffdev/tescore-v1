// main exec: Toff
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "include/render/view/render.h"

void red();
void yellow();
void reset();

int main() {
    puts("--- Renderer Debug ---\n");

    int navIndex = 1;
    while (navIndex != EOF){
        navIndex = _getch();
        switch (navIndex) {
            case '1':
                printf("focused panel 1\n");
                refreshFrame();
                break;
            case '2':
                printf("focused panel 2\n");
                break;
            case 'e':
                puts("Testing E char on int navigation");
                break;
            default:
                break;
        }
    }


//    red();
//    printf("Hello ");
//    yellow();
//    printf("world\n");
//    reset();

    system("pause");
    return 0;
}

//void red () {
//    printf("\033[1;31m");
//}
//
//void yellow() {
//        printf("\033[1;33m");
//}
//void reset () {
//    printf("\033[0m");
//}
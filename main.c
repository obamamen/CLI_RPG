#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "units.h"
#include "ansi.h"


int main () {
    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'q') {
                break;
            }
            //system("cls");
            printf("%c ", input);
            printPlus(1, 1, 1, "hello");
        }
    }
    return 0;
}


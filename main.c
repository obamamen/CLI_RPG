#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"

#include "units.h"
#include "ansi.h"

#define EntityListSize 1024
#define EntitysMapWidth 32
#define EntitysMapHeight 32
typedef struct {
    Entity EntityList[EntityListSize];
    Entity* EntitysMap[EntitysMapWidth][EntitysMapHeight];
    Entity* Player;
    int width;
    int height;
}worldMap;

void makeEmptyEntity(Entity* Entity) {
    Entity->type = EMPTY;
    Entity->xPos = 0;
}

void setupWorld(worldMap* map) {
    for (int i = 0; i < EntityListSize; i++) {
        
    }
}

int main () {
    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'q') {
                break;
            }
            //system("cls");
            printf("%c ", input);
            printPlus(RESET, 0, GREEN, "Hello world!");
        }
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#ifdef _WIN32
    #include <windows.h>
    #endif

    void enable_virtual_terminal_processing() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) {
            printf("Error getting console handle.\n");
            return;
        }

        DWORD dwMode = 0;
        if (!GetConsoleMode(hConsole, &dwMode)) {
            printf("Error getting console mode.\n");
            return;
        }

        // Enable virtual terminal processing
        dwMode |= 0x0004;
        if (!SetConsoleMode(hConsole, dwMode)) {
            printf("Error setting console mode.\n");
        }
    #endif
}

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
    Entity->type = ENTITYTYPE_EMPTY;
    Entity->xPos = 0;
    Entity->yPos = 0;
    Entity->icon = '.'; 
    Entity->health = 0;
    Entity->mana = 0; 
    for (int i = 0; i < inventoryMaxSize; i++) {
        Entity->inventory[i].type = ITEMTYPE_EMPTY;
        Entity->inventory[i].type = 0;
    }
}

void setupWorld(worldMap* map) {
    for (int i = 0; i < EntityListSize; i++) {
        
    }
}

int main () {
    enable_virtual_terminal_processing(); //otherwise no color in normal cmd

    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'q') {
                break;
            }
            //system("cls");
            printf("%c ", input);
            printPlus(RESET, 0, GREEN, "Hello world!\n");
        }
    }
    return 0;
}


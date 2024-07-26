#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "units.h"
#include "ansi.h"
#include "world.h"

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
        dwMode |= 0x0004;
        if (!SetConsoleMode(hConsole, dwMode)) {
            printf("Error setting console mode.\n");
        }
    #endif
}



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

void setupPlayer(Entity* Player) {
    Player->type = ENTITYTYPE_PLAYER;
    Player->xPos = 0;
    Player->yPos = 0;
    Player->icon = '@'; 
    Player->health = 100;
    Player->mana = 100; 
}

void setupWorld(worldMap* map) {
    int i,j;
    for (i = 0; i < EntityListSize; i++) {
        makeEmptyEntity(&map->EntityList[i]);
    }
    setupPlayer(&map->EntityList[0]);

    map->width = EntitysMapWidth;
    map->height = EntitysMapHeight;
    for (i = 0; i < EntitysMapWidth; ++i) {
        for (j = 0; j < EntitysMapHeight; ++j) {
            map->EntitysMap[i][j] = NULL;
        }
    }
    map->EntitysMap[EntitysMapWidth/2][EntitysMapHeight/2] = &map->EntityList[0];
}

void printWorld(const worldMap* map) {
    printf("World Map:\n");
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            if (map->EntitysMap[x][y] != NULL) {
                printf("%c ", map->EntitysMap[x][y]->icon);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main () {
    enable_virtual_terminal_processing(); //otherwise no color in normal cmd
    worldMap* world = (worldMap*)malloc(sizeof(worldMap));
    if (world == NULL) {
        printf("allocating memory for worldMap failed womp womp.\n");
        return 1;
    }

    setupWorld(world);
    printWorld(world);
    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'q') {
                break;
            }
            //system("cls");
            printf("%c ", input);
            printPlus(RESET, 0, GREEN, "Hello World!");
        }
    }

    free(world);
    return 0;
}


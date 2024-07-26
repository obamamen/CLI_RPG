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

void moveEntity(Entity* entity, int dx, int dy, worldMap* map) {
    int newX = entity->xPos + dx;
    int newY = entity->yPos + dy;
    if (newX < 0 || newX >= map->width || newY < 0 || newY >= map->height) {
        return;
    }
    if (map->EntitysMap[newX][newY] != NULL) {
        return;
    }
    map->EntitysMap[entity->xPos][entity->yPos] = NULL;
    entity->xPos = newX;
    entity->yPos = newY;
    map->EntitysMap[newX][newY] = entity;
}

void handleInput(char input, worldMap* world) {
    switch (input) {
        case 'w':
            moveEntity(world->Player, 0, -1, world);
            break;
        case 's':
            moveEntity(world->Player, 0, 1, world);
            break;
        case 'a':
            moveEntity(world->Player, -1, 0, world);
            break;
        case 'd':
            moveEntity(world->Player, 1, 0, world);
            break;
        default:
            break;
    }
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
            system("cls");
            handleInput(input, world);
  
            printWorld(world);

            //printf("%c ", input);
            //printPlus(RESET, 0, GREEN, "Hello World!");
        }
    }

    free(world);
    return 0;
}


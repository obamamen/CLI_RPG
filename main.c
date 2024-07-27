#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "units.h"
#include "ansi.h"
#include "world.h"
#include "entity.h"

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

void set_code_page_utf8() {
#ifdef _WIN32
    system("chcp 65001 >nul"); // urf-8
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

void handleMovementInput(char input, worldMap* world) {
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

void handleCursorMovement(char input, int* cx, int* cy) {
        switch (input) {
        case 'w':
            *cy-=1;
            break;
        case 's':
            *cy+=1;
            break;
        case 'a':
            *cx-=1;
            break;
        case 'd':
            *cx+=1;
            break;
        default:
            break;
    }
}

void printEntity(Entity* entity) {
    if (entity == NULL) {
        return;
    }
    printf("━");
    printf("type: %s\n",entity->name);
}

typedef enum {
    UI_PLAY_STATE,
    UI_CURSOR_STATE
} UIstate;



int main () {
    enable_virtual_terminal_processing(); //otherwise no color in normal cmd
    set_code_page_utf8();  // utf-8 for special chars
    worldMap* world = (worldMap*)malloc(sizeof(worldMap));
    if (world == NULL) {
        printf("allocating memory for worldMap failed womp womp.\n");
        return 1;
    }
    setupWorld(world);
    setupSkeleton(addEntityToWorld(world, 5, 5));
    printWorld(world,-1,-1);

    UIstate ui = UI_PLAY_STATE;
    int cursorX = -1;
    int cursorY = -1;

    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'v') {
                printf("state = %d",ui);
                printf("x = %d",cursorX);
                printf("y = %d",cursorY);
                continue;
            }
            if (input == 'q') {
                break;
            }
            if (ui==UI_CURSOR_STATE) {
                system("cls");
                handleCursorMovement(input, &cursorX, &cursorY);
                printWorld(world, cursorX, cursorY);
                Entity* onCursor = world->EntitysMap[cursorX][cursorY];
                printEntity(onCursor);
            }
            if ((input == 'e') && (ui==UI_PLAY_STATE)) {
                ui = UI_CURSOR_STATE;
                system("cls");
                cursorX = world->Player->xPos;
                cursorY = world->Player->yPos;
                printWorld(world, world->Player->xPos,world->Player->yPos);
                printEntity(*world->EntitysMap[cursorX,cursorY]);
                continue;
            }
            if ((input == 'e') && (ui==UI_CURSOR_STATE)) {
                ui = UI_PLAY_STATE;
                cursorX = -1;
                cursorY = -1;
                system("cls");
                printWorld(world, -1, -1);
                continue;
            }
            if (ui==UI_PLAY_STATE) {
                system("cls");
                handleMovementInput(input, world);
                printWorld(world,-1,-1);
            }
            //printf("b: Enemies @  #  X  O  M  &   ☠  ☻  ▒ Cursor >  <  ^  v  *  +  o  .  ←  →  ↑  ↓ UI Elements *  +  -  |  =  .  :  ;  #  √  × +  -  |  ┼  ─  │  ┌  ┐  └  ┘  ╭  ╮  ╰  ╯  ╲  ╱  ╳  ╋  ┃  ━\n"); 
        }
    }

    free(world);
    return 0;
}


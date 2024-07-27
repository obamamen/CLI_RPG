#include "world.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "entity.h"

void setupWorld(worldMap* map) {
    int i, j;
    for (i = 0; i < EntityListSize; i++) {
        makeEmptyEntity(&map->EntityList[i]);
    }
    setupPlayer(&map->EntityList[0]);
    map->Player = &map->EntityList[0];

    map->width = EntitysMapWidth;
    map->height = EntitysMapHeight;
    for (i = 0; i < EntitysMapWidth; ++i) {
        for (j = 0; j < EntitysMapHeight; ++j) {
            map->EntitysMap[i][j] = NULL;
        }
    }
    map->EntitysMap[0][0] = &map->EntityList[0];
}

void printWorld(worldMap* map, int cursorX, int cursorY) {
    for (int line = 0; line < map->width+2; ++line) {
        if (line == 0) {
            printPlus(BOLD, BLACK_BG, WHITE, "╔═");
            continue;
        }
        if (line == map->width+1) {
            printPlus(BOLD, BLACK_BG, WHITE, "╗");
            continue;
        }
        printPlus(BOLD, BLACK_BG, WHITE, "══");
    }
    printf("\n");
    for (int y = 0; y < map->height; ++y) {
        printPlus(BOLD, BLACK_BG, WHITE, "║ ");
        for (int x = 0; x < map->width; ++x) {
            int newX = x;
            int newY = y;
            if (x == cursorX && y == cursorY) {
                printPlus(BOLD, MAGENTA_BG, YELLOW, "X ");
            } else if (map->EntitysMap[newX][newY] != NULL) {
                char ch[3] = { map->EntitysMap[newX][newY]->icon ,' ', '\0'};
                printPlus(RESET, 0, map->EntitysMap[newX][newY]->color, ch);
            } else {
                printPlus(RESET, BLACK_BG, WHITE, "· ");
            }
            if (x == (map->width-1)) {
                printPlus(BOLD, BLACK_BG, WHITE, "║");
            }
        }
        printf("\n");
    }
    for (int line = 0; line < map->width+2; ++line) {
        if (line == 0) {
            printPlus(BOLD, BLACK_BG, WHITE, "╚═");
            continue;
        }
        if (line == map->width+1) {
            printPlus(BOLD, BLACK_BG, WHITE, "╝");
            continue;
        }
        printPlus(BOLD, BLACK_BG, WHITE, "══");
    }
    printf("\n");
}

Entity* addEntityToWorld(worldMap* map, int x, int y) {
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        printf("Error: Position out of bounds.\n");
        return NULL;
    }

    if (map->EntitysMap[x][y] != NULL) {
        printf("Error: Position already occupied.\n");
        return NULL;
    }

    for (int i = 0; i < EntityListSize; ++i) {
        if (map->EntityList[i].type == ENTITYTYPE_EMPTY) {
            Entity* entity = &map->EntityList[i];
            makeEmptyEntity(entity);
            map->EntitysMap[x][y] = entity;
            return entity;
        }
    }

    printf("Error: No space in entityList.\n");
}

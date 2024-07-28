#include "world.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "entity.h"

void clampCamera(worldMap* map) {
    if (map->cameraX < 0) {
        map->cameraX = 0;
    }
    if (map->cameraY < 0) {
        map->cameraY = 0;
    }
    if (map->cameraX > (map->width - map->cameraWidth)) {
        map->cameraX = map->width - map->cameraWidth;
    }
    if (map->cameraY > (map->height - map->cameraHeight)) {
        map->cameraY = map->height - map->cameraHeight;
    }
    
}

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
    map->cameraX = 0;
    map->cameraY = 0;
    map->cameraWidth = 11;
    map->cameraHeight = 11;
}

void updateMap(worldMap* map) {
    int cameraIsEvenW = 0;
    int cameraIsEvenH = 0;
    if (map->cameraWidth % 2 == 1) {
        cameraIsEvenW = 1;
    }
    if (map->cameraHeight % 2 == 1) {
        cameraIsEvenH = 1;
    }
    if (cameraIsEvenW == 1) {
        map->cameraX = map->Player->xPos - (map->cameraWidth/2);
    }
    if (cameraIsEvenH == 1) {
        map->cameraY = map->Player->yPos - (map->cameraHeight/2);
    }
    clampCamera(map);
}

void printWorld(worldMap* map, int cursorX, int cursorY) {
    for (int line = 0; line < map->cameraWidth+2; ++line) {
        if (line == 0) {
            printPlus(BOLD, BLACK_BG, WHITE, "╔═");
            continue;
        }
        if (line == map->cameraWidth+1) {
            printPlus(BOLD, BLACK_BG, WHITE, "╗");
            continue;
        }
        printPlus(BOLD, BLACK_BG, WHITE, "══");
    }
    printf("\n");
    for (int y = 0; y < map->cameraHeight; ++y) {
        printPlus(BOLD, BLACK_BG, WHITE, "║ ");
        for (int x = 0; x < map->cameraWidth; ++x) {
            int newX = x+map->cameraX;
            int newY = y+map->cameraY;
            if (newX == cursorX && newY == cursorY) {
                printPlus(BOLD, MAGENTA_BG, YELLOW, "X ");
            } else if (map->EntitysMap[newX][newY] != NULL) {
                char ch[3] = { map->EntitysMap[newX][newY]->icon ,' ', '\0'};
                printPlus(RESET, 0, map->EntitysMap[newX][newY]->color, ch);
            } else {
                printPlus(RESET, BLACK_BG, WHITE, "· ");
            }
            if (x == (map->cameraWidth-1)) {
                printPlus(BOLD, BLACK_BG, WHITE, "║");
            }
        }
        printf("\n");
    }
    for (int line = 0; line < map->cameraWidth+2; ++line) {
        if (line == 0) {
            printPlus(BOLD, BLACK_BG, WHITE, "╚═");
            continue;
        }
        if (line == map->cameraWidth+1) {
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

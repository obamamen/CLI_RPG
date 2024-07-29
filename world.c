#include "world.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "entity.h"

void createEmptyItem(Item* item){
    
}

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
    map->cameraWidth = 45;
    map->cameraHeight = 25;
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
    char buffer[40000];
    int bufferPos = 0;

    // Top border
    for (int line = 0; line < map->cameraWidth + 2; ++line) {
        if (line == 0) {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "╔═", buffer, &bufferPos);
        } else if (line == map->cameraWidth + 1) {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "╗", buffer, &bufferPos);
        } else {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "══", buffer, &bufferPos);
        }
    }
    appendToBuffer(buffer, &bufferPos, "\n");

    // Map content
    for (int y = 0; y < map->cameraHeight; ++y) {
        printPlusAppendToBuffer(BOLD, BLACK, WHITE, "║ ", buffer, &bufferPos);
        for (int x = 0; x < map->cameraWidth; ++x) {
            int newX = x + map->cameraX;
            int newY = y + map->cameraY;
            if (newX == cursorX && newY == cursorY) {
                printPlusAppendToBuffer(BOLD, MAGENTA_BG, YELLOW, "X ", buffer, &bufferPos);
            } else if (map->EntitysMap[newX][newY] != NULL) {
                char ch[4];
                snprintf(ch, sizeof(ch), "%c ", map->EntitysMap[newX][newY]->icon);
                printPlusAppendToBuffer(RESET, BLACK, map->EntitysMap[newX][newY]->color, ch, buffer, &bufferPos);
            } else {
                int random = (int)((sin(newX * (0.5 + (newY / 5 % 5))) * cos(newY * 0.5 + (newX / 5 % 5))) * 10);
                if (!random) {
                    printPlusAppendToBuffer(RESET, BLACK, WHITE, "• ", buffer, &bufferPos);
                } else {
                    printPlusAppendToBuffer(RESET, BLACK, WHITE, "· ", buffer, &bufferPos);
                }
            }
            if (x == (map->cameraWidth - 1)) {
                printPlusAppendToBuffer(BOLD, BLACK, WHITE, "║", buffer, &bufferPos);
            }
        }
        appendToBuffer(buffer, &bufferPos, "\n");
    }

    // Bottom border
    for (int line = 0; line < map->cameraWidth + 2; ++line) {
        if (line == 0) {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "╚═", buffer, &bufferPos);
        } else if (line == map->cameraWidth + 1) {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "╝", buffer, &bufferPos);
        } else {
            printPlusAppendToBuffer(BOLD, BLACK, WHITE, "══", buffer, &bufferPos);
        }
    }
    appendToBuffer(buffer, &bufferPos, "\n");


    printf("%s", buffer);
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

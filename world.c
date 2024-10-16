#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "entity.h"


void waitMs(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000; 
    nanosleep(&ts, NULL);
}

void createEmptyItem(Item* item){
    
}

void addEntityToList(EntityList* list, Entity entity) {
    if (list == NULL) { return; } // if list

    list->entityCount ++; 
    list->entities = realloc(list->entities, sizeof(Entity)*list->entityCount+1);
    

    list->entities[list->entityCount-1] = entity;
}

void setupWorld(worldMap* map) {
    int i, j;
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

    map->entityList.entities = malloc(sizeof(Entity));
    map->entityList.entityCount = 1;
    makeEmptyEntity(&map->entityList.entities[0]);
    setupPlayer(&map->entityList.entities[0]);
    map->Player = &map->entityList.entities[0];
    for (i = 0; i < EntitysMapWidth; ++i) {
        for (j = 0; j < EntitysMapHeight; ++j) {
            map->entityMap[i][j] = NONE;
        }
    }


    map->entityMap[0][0] = 0;
    map->cameraX = 0;
    map->cameraY = 0;
    map->cameraWidth = 31;
    map->cameraHeight = 31;
}

void freeWorld(worldMap* map) {
    free(map->entityList.entities);
    free(map->Player);
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
    char buffer[map->cameraWidth*map->cameraHeight*80];
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
                printPlusAppendToBuffer(RESET, RESET, RESET, "", buffer, &bufferPos);
            } else if (map->entityMap[newX][newY] != NONE) {
                char ch[4];
                if ((map->entityMap[newX][newY] >= 0) && (map->entityMap[newX][newY] < map->entityList.entityCount)) {
                    int index = map->entityMap[newX][newY];
                    snprintf(ch, sizeof(ch), "%c ", map->entityList.entities[index].icon);
                    printPlusAppendToBuffer(RESET, BLACK, map->entityList.entities[index].color, ch, buffer, &bufferPos);
                }
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
            //addEntityToList(map->entityList, x, y);
            map->EntitysMap[x][y] = entity;
            return entity;
        }
    }


}

#include "world.h"
#include <stdio.h>
#include <string.h>

void makeEmptyEntity(Entity* entity) {
    if (entity == NULL) {
        return;
    }
    entity->type = ENTITYTYPE_EMPTY;
    entity->xPos = 0;
    entity->yPos = 0;
    entity->icon = '.'; 
    entity->health = 0;
    entity->mana = 0; 
    for (int i = 0; i < inventoryMaxSize; i++) {
        entity->inventory[i].type = ITEMTYPE_EMPTY;
        entity->inventory[i].type = 0;
    }
}

void setupPlayer(Entity* player) {
    if (player == NULL) {
        return;
    }
    player->type = ENTITYTYPE_PLAYER;
    player->xPos = 0;
    player->yPos = 0;
    player->icon = '@'; 
    player->health = 100;
    player->mana = 100; 
}

void setupSkeleton(Entity* skeleton) {
    if (skeleton == NULL) {
        return;
    }
    skeleton->type = ENTITYTYPE_SKELETON;
    skeleton->icon = 's'; 
    skeleton->health = 50;
    skeleton->mana = 0; 
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
}

void printWorld(const worldMap* map) {
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            if (map->EntitysMap[x][y] != NULL) {
                //printf("%c ", map->EntitysMap[x][y]->icon);
                char ch[2] = { map->EntitysMap[x][y]->icon , '\0' };
                printPlus(RESET, 0, GREEN, ch);
                printf(" ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
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

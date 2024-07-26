#include "world.h"
#include <stdio.h>

void makeEmptyEntity(Entity* entity) {
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
    player->type = ENTITYTYPE_PLAYER;
    player->xPos = 0;
    player->yPos = 0;
    player->icon = '@'; 
    player->health = 100;
    player->mana = 100; 
}

void setupSkeleton(Entity* skeleton) {
    skeleton->type = ENTITYTYPE_SKELETON;
    skeleton->xPos = 5;
    skeleton->yPos = 5;
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
                printf("%c ", map->EntitysMap[x][y]->icon);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void addEntityToWorld(Entity* Entity, worldMap* map) {
    int x = Entity->xPos;
    int y = Entity->yPos;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        printf("Error: Position out of bounds.\n");
        return;
    }

    if (map->EntitysMap[x][y] != NULL) {
        printf("Error: Position already occupied.\n");
        return;
    }

    for (int i = 0; i < EntityListSize; ++i) {
        if (map->EntityList[i] != NULL) {
            memcpy(&map->EntityList[i], entity, sizeof(Entity));
            map->EntitysMap[x][y] = &map->EntityList[i];
            return;
        }
    }

    printf("Error: No space in entityList.\n");
}

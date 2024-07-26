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
    map->EntitysMap[EntitysMapWidth / 2][EntitysMapHeight / 2] = &map->EntityList[0];
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

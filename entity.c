#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "units.h"

void setEntityName(Entity* entity, const char* name) {
    if (entity == NULL) {
        return;
    }
    if (entity->name != NULL) {
        free(entity->name);
    }
    if (entity->name != NULL) {
        strcpy(entity->name, name); 
    }
}

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
    entity->maxHealth = 0;
    entity->maxMana = 0;
    setEntityName(entity,"Empty Entity");
    for (int i = 0; i < inventoryMaxSize; i++) {
        entity->inventory[i].type = ITEMTYPE_EMPTY;
        entity->inventory[i].type = 0;
    }
}

void setupPlayer(Entity* player) {
    if (player == NULL) {
        return;
    }
    setEntityName(player,"Player");
    player->type = ENTITYTYPE_PLAYER;
    player->icon = '@'; 
    player->health = 100;
    player->maxHealth = 100;
    player->mana = 100; 
    player->maxMana= 100; 
}

void setupSkeleton(Entity* skeleton) {
    if (skeleton == NULL) {
        return;
    }
    setEntityName(skeleton,"Skeleton");
    skeleton->type = ENTITYTYPE_SKELETON;
    skeleton->icon = 'S'; 
    skeleton->health = 20;
    skeleton->maxHealth = 20;
    skeleton->mana = 0; 
    skeleton->maxMana= 0; 
}
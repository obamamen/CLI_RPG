#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "units.h"

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
    entity->level = 0;
    entity->color = WHITE;
    setEntityName(entity,"");
    for (int i = 0; i < InventoryMaxSize; i++) {
        entity->inventory[i].type = ITEMTYPE_EMPTY;
        entity->inventory[i].name = ITEMNAME_EMPTY;
        entity->inventory[i].collection = ITEMCOLLECTION_EMPTY;
        for (int j = 0; j < EnchantmentsMaxSize; j++) {
            entity->inventory[i].enchantments[j] = ENCHANTMENT_EMPTY;
        }
        entity->inventory[i].spell = SPELL_EMPTY;
        entity->inventory[i].manaCost = 0;
        entity->inventory[i].stack = 0;
        entity->inventory[i].maxStack = 0;
        entity->inventory[i].weight = 0;
    }
}

void setupPlayer(Entity* player) {
    if (player == NULL) {
        return;
    }
    setEntityName(player,"Player");
    player->type = ENTITYTYPE_PLAYER;
    player->icon = '@'; 
    player->health = 50;
    player->maxHealth = 50;
    player->mana = 100; 
    player->maxMana= 100; 
    player->level = 1;
    player->color = GREEN;
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
    skeleton->level = 1;
    skeleton->color = RED;
}
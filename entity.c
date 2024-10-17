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
    if (map->entityMap[newX][newY] != NONE) {
        return; // if space isnt empty
    }
    
    map->entityMap[newX][newY] = map->entityMap[entity->xPos][entity->yPos];
    map->entityMap[entity->xPos][entity->yPos] = NONE;
    entity->xPos = newX;
    entity->yPos = newY;

}

void setEntityName(Entity* entity, const char* name) {
    if (entity == NULL || name == NULL) {
        return;
    }

    if (entity->name != NULL) {
        free(entity->name);
    }

    entity->name = malloc(strlen(name) + 1);
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
    entity->spells.spellCount = 0;
    entity->inventory.itemCount = 0;
    setEntityName(entity,"Empty Entity");
    for (int i = 0; i < InventoryMaxSize; i++) {
        entity->spells.spells = NULL;
        entity->inventory.items = NULL;
    }
}

void addItemToList(ItemList* list, Item item) {
    if (list->itemCount >= InventoryMaxSize) {
       return;
    }
    list->items = realloc(list->items, sizeof(Item) * ++list->itemCount);
    //reallocating to ensure memory is efficienttly removed

    for (int i = list->itemCount - 1; i > 0; --i) {
        list->items[i] = list->items[i - 1];
    }

    list->items[0] = item;
}

void removeItemFromList(ItemList* list, int index) {
    if (index < 0 || index >= list->itemCount) {
        return;  
    }

    for (int i = index; i < list->itemCount - 1; ++i) {
        list->items[i] = list->items[i + 1];
        // when you remove from the middle,
        // the right side needs to be shifted to the left
    }
    
    list->items = realloc(list->items, sizeof(Spell) * --list->itemCount);
}

void addSpellToList(SpellList *spells, Spell spell) {
    if (spells->spellCount >= InventoryMaxSize) {
        return;
    }
    spells->spells = realloc(spells->spells, sizeof(Spell) * ++spells->spellCount);
    // reallocating to ensure memory is efficienttly removed


    for (int i = spells->spellCount - 1; i > 0; --i) {
        spells->spells[i] = spells->spells[i - 1];
    }
    spells->spells[0] = spell;
}

void removeSpellFromList(SpellList *spells, int index) {
    if (index < 0 || index >= spells->spellCount) {
        return;  
    }
    
    for (int i = index; i < spells->spellCount - 1; ++i) {
        spells->spells[i] = spells->spells[i + 1];
        // when you remove from the middle,
        // the right side needs to be shifted to the left

    }
    
    spells->spells = realloc(spells->spells, sizeof(Spell) * --spells->spellCount);
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

void freeItem(Item* item) {
    free(item->name);
    item->name = NULL;
}

void freeSpell(Spell* spell) {
    return;
}

void freeEntity(Entity* entity) {
    if (entity == NULL) {
        return;
    }

    free(entity->name);
    free(entity->spells.spells);
    free(entity->inventory.items);

    for (int i = 0; i < entity->inventory.itemCount; i++) {
        freeItem(&entity->inventory.items[i]);
    }
    entity->inventory.items = NULL;
    entity->spells.spells = NULL;
}
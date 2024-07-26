#ifndef WORLD_H
#define WORLD_H

#include "units.h"
#include "ansi.h"

#define EntityListSize 1024
#define EntitysMapWidth 32
#define EntitysMapHeight 32

typedef struct {
    Entity EntityList[EntityListSize];
    Entity* EntitysMap[EntitysMapWidth][EntitysMapHeight];
    Entity* Player;
    int width;
    int height;
} worldMap;

void makeEmptyEntity(Entity* entity);

void setupPlayer(Entity* player);
void setupSkeleton(Entity* skeleton);

void setupWorld(worldMap* map);
void printWorld(const worldMap* map);
Entity* addEntityToWorld(worldMap* map, int x, int y);

#endif // WORLD_H

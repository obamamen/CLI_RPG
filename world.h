#ifndef WORLD_H
#define WORLD_H

#include "units.h"
#include "ansi.h"

#define EntityListSize 256
#define EntitysMapWidth 64
#define EntitysMapHeight 64

void waitMs(int milliseconds);

typedef struct {
    Entity EntityList[EntityListSize];
    Entity* EntitysMap[EntitysMapWidth][EntitysMapHeight];
    Entity* Player;
    int width : 16;
    int height : 16;
    int cameraX : 16;
    int cameraY : 16;
    int cameraWidth : 8;
    int cameraHeight : 8;
} worldMap;

void createEmptyItem(Item* item);
void updateMap(worldMap* map);
void clampCamera(worldMap* map);
void makeEmptyEntity(Entity* entity);

void setupPlayer(Entity* player);
void setupSkeleton(Entity* skeleton);

void setupWorld(worldMap* map);
void printWorld(worldMap* map, int cursorX, int cursorY);
Entity* addEntityToWorld(worldMap* map, int x, int y);

#endif // WORLD_H

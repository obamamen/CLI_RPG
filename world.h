#ifndef WORLD_H
#define WORLD_H

#include "units.h"
#include "ansi.h"

#define EntityListSize 1024
#define EntitysMapWidth 16
#define EntitysMapHeight 16

typedef struct {
    Entity EntityList[EntityListSize];
    Entity* EntitysMap[EntitysMapWidth][EntitysMapHeight];
    Entity* Player;
    int width;
    int height;
    int cameraX;
    int cameraY;
    int cameraWidth;
    int cameraHeight;
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

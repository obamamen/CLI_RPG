#ifndef ENTITY_H
#define ENTITY_H

#include "units.h"
#include "world.h"
#include "ansi.h"

void moveEntity(Entity* entity, int dx, int dy, worldMap* map);
void setEntityName(Entity* entity, const char* name);
void makeEmptyEntity(Entity* entity);
void setupPlayer(Entity* player);
void setupSkeleton(Entity* skeleton);

#endif // ENTITY_H


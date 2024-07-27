#ifndef ENTITY_H
#define ENTITY_H

#include "units.h"
#include "ansi.h"

void setEntityName(Entity* entity, const char* name);
void makeEmptyEntity(Entity* entity);
void setupPlayer(Entity* player);
void setupSkeleton(Entity* skeleton);

#endif // ENTITY_H


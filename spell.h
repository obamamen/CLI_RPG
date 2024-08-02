#include "units.h"
#include "world.h"

#ifndef SPELL_H
#define SPELL_H


SpellTargetType getSpellTargetType(Spell spell);

void castSpell(worldMap* world, Spell* spell, Entity* caster, void* target);


#endif // SPELL_H
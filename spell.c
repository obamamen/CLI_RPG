#include <stdlib.h>
#include "spell.h"
#include "units.h"
#include "world.h"

SpellTargetType getSpellTargetType(Spell spell) {
    switch (spell.spellID) {
            case SPELLID_EMPTY:
                return SPELLTARGETTYPE_NONE;
            break;
            case SPELLID_FIREBALL:
                return SPELLTARGETTYPE_POS;
            break;
            case SPELLID_SELFHEAL:
                return SPELLTARGETTYPE_SELF;
            break;
    }
}

void castSpell(worldMap* world, Spell* spell, Entity* caster, void* target) {
    switch (spell->spellID) {
        case 0:
            return;
        break;
            case SPELLID_FIREBALL:
            {
                if (caster->mana >= spell->manaCost) {
                    caster->mana -= spell->manaCost;
            
                Entity* targetEntity = (Entity*)target;
                if (targetEntity != NULL) {
                    targetEntity->health -= 10;
                    if (targetEntity->health < 0) {
                        targetEntity->health = 0;
                    }
                }

                }
            }
            return;

        break;
            case SPELLID_SELFHEAL:
                if (caster->mana >= spell->manaCost) {
                    caster->mana -= spell->manaCost;

                    caster->health += 10;
                    caster->health = (caster->health < caster->maxHealth) ? caster->health : caster->maxHealth;
                }
            return;
        break;
    }
}
#ifndef UNITS_H
#define UNITS_H
#include "color.h"
//#include "spell.h"

#define InventoryMaxSize 64
#define EnchantmentsMaxSize 4
#define MaxStackSize
#define MaxSpellNameLength 20

typedef struct {
    int x;
    int y;
} Pos;





// items

typedef enum {
    ENCHANTMENT_EMPTY,
    ENCHANTMENT_MOREDAMAGE
} Enchantment;

typedef enum {
    ITEMTYPE_EMPTY,
    ITEMTYPE_SWORD
} ItemType;

typedef struct {
    char *name;
    ItemType type;
} Item;

typedef struct {
    Item *items;
    int itemCount;
} ItemList;



// spells

typedef enum {
    SPELLID_EMPTY,
    SPELLID_FIREBALL,
    SPELLID_SELFHEAL
} SpellID;

typedef enum {
    SPELLTARGETTYPE_NONE,
    SPELLTARGETTYPE_SELF,
    SPELLTARGETTYPE_POS,
    SPELLTARGETTYPE_AREA_3X3,
    SPELLTARGETTYPE_AREA_CROSS,
} SpellTargetType;

typedef struct {
    SpellID spellID;
    int manaCost;
    SpellTargetType targetType;
} Spell;

typedef struct {
    Spell *spells;
    int spellCount;
} SpellList;



// entities

typedef enum {
    ENTITYTYPE_EMPTY,
    ENTITYTYPE_PLAYER,
    ENTITYTYPE_SKELETON
} EntityType;

typedef struct {
    EntityType type;
    int level : 8;
    char icon; 
    char *name;
    Color color: 8;
    int health;  
    int maxHealth; 
    int mana; 
    int maxMana; 

    ItemList inventory;
    SpellList spells;

    int xPos;
    int yPos;
} Entity;


#endif // UNITS_H

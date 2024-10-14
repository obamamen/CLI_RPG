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

typedef enum {
    ENCHANTMENT_EMPTY,
    ENCHANTMENT_MOREDAMAGE
} Enchantment;

typedef enum {
    ITEMID_EMPTY,
    ITEMID_SWORD
} ItemID;

typedef struct {
    //ItemType type;
    //ItemName name;
    //ItemCollection collection : 8;
    Enchantment enchantments[EnchantmentsMaxSize];
    //Spell spell;
    //int manaCost : 16;
    //int stack : 16;
    //int maxStack : 16;
    //int weight : 16;
} Item;

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
    Item *inventory;
    int inventoryCount;

    Spell *spells;
    int spellCount;

    int xPos;
    int yPos;
} Entity;


#endif // UNITS_H

#ifndef UNITS_H
#define UNITS_H
#include "color.h"

#define InventoryMaxSize 64
#define EnchantmentsMaxSize 12
#define MaxStackSize


typedef enum {
    ITEMNAME_EMPTY
} ItemName;


typedef enum {
    ITEMTYPE_EMPTY,
    ITEMTYPE_SPELL,
    ITEMTYPE_ARMOUR,
    ITEMTYPE_WEAPON,
    ITEMTYPE_AMMUTITION
} ItemType;


typedef enum {
    ITEMCOLLECTION_EMPTY,
    ITEMCOLLENTION_SPELL
} ItemCollection;

typedef enum {
    SPELL_EMPTY,
    SPELL_FIREBALL
} Spell;

typedef enum {
    ENCHANTMENT_EMPTY,
    ENCHANTMENT_MOREDAMAGE
} Enchantment;

typedef struct {
    ItemType type;
    ItemName name;
    ItemCollection collection;
    Enchantment enchantments[EnchantmentsMaxSize];
    Spell spell;
    int manaCost : 16;
    int stack : 16;
    int maxStack : 16;
    int weight : 16;
} Item;


typedef enum {
    ENTITYTYPE_EMPTY,
    ENTITYTYPE_PLAYER,
    ENTITYTYPE_SKELETON
} EntityType;

typedef struct {
    int type;
    int level : 8;
    char icon; 
    char name[32];
    Color color;
    int health; 
    int maxHealth; 
    int mana; 
    int maxMana; 
    Item inventory[InventoryMaxSize];

    int xPos;
    int yPos;
} Entity;


#endif // UNITS_H

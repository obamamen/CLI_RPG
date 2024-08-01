#ifndef UNITS_H
#define UNITS_H
#include "color.h"

#define InventoryMaxSize 64
#define EnchantmentsMaxSize 4
#define MaxStackSize

typedef struct {
    int x;
    int y;
} Pos;

typedef enum {
    SPELLID_EMPTY,
    SPELLID_FIREBALL
} SpellID;

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

typedef struct {
    SpellID spellID;

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
    char name[32];
    Color color: 8;
    int health : 16;  
    int maxHealth : 16; 
    int mana: 16; 
    int maxMana: 16; 
    Item inventory[InventoryMaxSize];
    Spell spells[InventoryMaxSize];

    int xPos : 16;
    int yPos : 16;
} Entity;


#endif // UNITS_H

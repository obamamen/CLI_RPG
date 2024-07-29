#ifndef UNITS_H
#define UNITS_H
#include "color.h"

#define InventoryMaxSize 128
#define EnchantmentsMaxSize 4
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

typedef enum {
    ITEMID_EMPTY,
    ITEMID_SWORD
} ItemID;

typedef struct {
    ItemType type;
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

    int xPos : 16;
    int yPos : 16;
} Entity;


#endif // UNITS_H

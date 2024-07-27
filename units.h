#ifndef UNITS_H
#define UNITS_H


#define inventoryMaxSize 256

typedef enum {
    ITEMTYPE_EMPTY,
    ITEMTYPE_SWORD_BASIC_METAL,
    ITEMTYPE_BOW_BASIC_WOODEN,
    ITEMTYPE_ARROW_BASIC
} ItemType;

typedef enum {
    ITEMCOLLECTION_EMPTY,
    ITEMCOLLECTION_WEAPON,
    ITEMCOLLECTION_ARMORPIECE,
} ItemCollection;

typedef struct {
    ItemType type;
    ItemCollection collection;
    int weight;
} Item;

typedef enum {
    ENTITYTYPE_EMPTY,
    ENTITYTYPE_PLAYER,
    ENTITYTYPE_SKELETON
} EntityType;

typedef struct {
    int type;
    int xPos;
    int yPos;
    char icon; 
    int health; 
    int mana; 
    Item inventory[inventoryMaxSize];
} Entity;

#endif // UNITS_H

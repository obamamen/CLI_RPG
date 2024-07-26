#ifndef UNITS_H
#define UNITS_H


#define inventoryMaxSize 256

typedef enum {
    SWORD_BASIC_METAL,
    BOW_BASIC_WOODEN,
    ARROW_BASIC
} ItemType;

typedef struct {
    ItemType type;
    int weight;
} Item;

typedef enum {
    EMPTY,
    PLAYER
} EntityType;

typedef struct {
    int type;
    int xPos;
    int yPos;
    char icon; 
    int health; 
    int mana; 
    Item inventory[inventoryMaxSize];
    int inventorySize; 
} Entity;

#endif // UNITS_H

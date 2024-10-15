#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "units.h"
#include "ansi.h"

typedef enum {
    UI_PLAY_STATE,
    UI_CURSOR_STATE,
    UI_ABILITIE_STATE,
    UI_SELECTPOS_STATE,
    UI_INVENTORY_STATE,
    UI_SHOP_STATE
} UIstate;

void handleMovementInput(char input, worldMap* world);
void handleCursorMovement(char input, int* cx, int* cy);
void clampCursorInCamera(worldMap* world, int* cx, int* cy);
void printEntity(Entity* entity);

void printSpellName(Spell* spell);
Spell* selectPlayerSpell(worldMap* world);
Item* selectPlayerItem(worldMap* world);
Pos SelectXY(worldMap* world);



#endif // UI_H
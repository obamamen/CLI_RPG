#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "units.h"
#include "ansi.h"
#include "world.h"
#include "entity.h"


void handleMovementInput(char input, worldMap* world) {
    switch (input) {
        case 'w':
            moveEntity(world->Player, 0, -1, world);
            break;
        case 's':
            moveEntity(world->Player, 0, 1, world);
            break;
        case 'a':
            moveEntity(world->Player, -1, 0, world);
            break;
        case 'd':
            moveEntity(world->Player, 1, 0, world);
            break;
        default:
            break;
    }
}

void handleCursorMovement(char input, int* cx, int* cy) {
        switch (input) {
        case 'w':
            *cy-=1;
            break;
        case 's':
            *cy+=1;
            break;
        case 'a':
            *cx-=1;
            break;
        case 'd':
            *cx+=1;
            break;
        default:
            break;
    }
}

void printEntity(Entity* entity) {
    if (entity == NULL) {
        return;
    }
    printPlus(RESET, BLACK_BG, WHITE, " ╭━━━━━━━━═[ STATS ]═━━━━━━━━ \n");
    printPlus(BOLD, BLACK_BG, WHITE, " ┃  > Type    :  ");
    printPlus(RESET, BLACK_BG, WHITE,entity->name);
    printPlus(RESET, BLACK_BG, WHITE,"\n");
    printPlus(RESET, BLACK_BG, WHITE, " ┃  > Health  :  ");
        char str[64];
        snprintf(str, sizeof(str), "%d", entity->health);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE," / ");
        snprintf(str, sizeof(str), "%d", entity->maxHealth);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
    printPlus(RESET, BLACK_BG, WHITE, " ┃  > Mana    :  ");
        snprintf(str, sizeof(str), "%d", entity->mana);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE," / ");
        snprintf(str, sizeof(str), "%d", entity->maxMana);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
    printPlus(RESET, BLACK_BG, WHITE, " ┃  > level   :  ");
        snprintf(str, sizeof(str), "%d", entity->level);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
}
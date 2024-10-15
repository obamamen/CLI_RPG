#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "units.h"
#include "ansi.h"
#include "world.h"
#include "entity.h"
#include "ui.h"


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

void clampCursorInCamera(worldMap* world, int* cx, int* cy) {
    if (*cx < world->cameraX) {
        *cx = world->cameraX;
    }
    if (*cy < world->cameraY) {
        *cy = world->cameraY;
    }

    if (*cx > world->cameraX + world->cameraWidth-1) {
        *cx = world->cameraX + world->cameraWidth-1;
    }

    if (*cy > world->cameraY + world->cameraHeight-1) {
        *cy = world->cameraY + world->cameraHeight-1;
    }
}

void printEntity(Entity* entity) {
    if (entity == NULL) {
        return;
    }
    printPlus(RESET, BLACK_BG, WHITE, " ╭───────═[ STATS ]═─────── \n");
    printPlus(RESET, BLACK_BG, WHITE, " |\n");
    printPlus(RESET, BLACK_BG, WHITE, " |  + Type    :  ");
    printPlus(RESET, BLACK_BG, WHITE,entity->name);
    printPlus(RESET, BLACK_BG, WHITE,"\n");
    printPlus(RESET, BLACK_BG, WHITE, " |  + Health  :  ");
        char str[64];
        snprintf(str, sizeof(str), "%d", entity->health);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE," / ");
        snprintf(str, sizeof(str), "%d", entity->maxHealth);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
    if (entity->maxMana != 0) { 
    printPlus(RESET, BLACK_BG, WHITE, " |  + Mana    :  ");
        snprintf(str, sizeof(str), "%d", entity->mana);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE," / ");
        snprintf(str, sizeof(str), "%d", entity->maxMana);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
    }
    if (entity->level != 0) {
    printPlus(RESET, BLACK_BG, WHITE, " |  + level   :  ");
        snprintf(str, sizeof(str), "%d", entity->level);
        printPlus(RESET, BLACK_BG, WHITE,str);
        printPlus(RESET, BLACK_BG, WHITE,"\n");
    }
    printPlus(RESET, BLACK_BG, WHITE, " |\n");
    printPlus(RESET, BLACK_BG, WHITE, " ╰────────────── \n");
}

void printSpellName(Spell* spell) {
    //char print[20];
    printf("%s", get_attribute_code(RESET));
    switch (spell->spellID) {
        case SPELLID_FIREBALL:
            printf("%-*s", MaxSpellNameLength, "Fireball");
        break;
        case SPELLID_SELFHEAL:
            //printf("Self-healing");
            printf("%-*s", MaxSpellNameLength, "Self-healing");
        break;
    }
    //printPlus(RESET, WHITE, BLACK_BG, &print);
}

Item* selectPlayerItem(worldMap *world)
{
    int selectedItem = 0;

    void printTopBar()
    {
        printPlus(RESET, WHITE_HI, BLACK_BG, "  Select a item:");
        printPlus(RESET, WHITE, BLACK_BG, "\n\n");
    }
    void printItems()
    {
        for (int i = 0; i < world->Player->inventory.itemCount; i++) {
            if (i == selectedItem) {
                printf(">  ");
            } else {
                printf("   ");
            }
            printf("%s \n", world->Player->inventory.items[i].name);
        }
    }
    system("cls");
    printTopBar();
    printItems();
    while (1) {
        char input = _getch();
        if (input == 27) {
            return NULL;
        }
        if (input == ' ') {
            return &world->Player->inventory.items[selectedItem];
        }
        if (input == 's') {
            selectedItem += 1;
            if (selectedItem >= world->Player->inventory.itemCount) {
                selectedItem = world->Player->inventory.itemCount - 1;
            }
        }
        if (input == 'w') {
            selectedItem -= 1;
            if (selectedItem < 0) {
                selectedItem = 0;
            }
        }

        system("cls");
        printTopBar();
        printItems();
    }
}

Pos SelectXY(worldMap *world)
{
    Pos selectedPos;
    selectedPos.x = world->Player->xPos;
    selectedPos.y = world->Player->yPos;

    system("cls");
    printWorld(world, selectedPos.x, selectedPos.y);
    printf("\n");
    printf("(");
    printf("%d", selectedPos.x);
    printf(",");
    printf("%d", selectedPos.y);
    printf(")");

    while (1) {
        if (_kbhit()) {  
            char input = _getch();

            if (input == ' ') {
                return selectedPos;
            }

            if (input == 'q') {
                Pos defaultPos = {-1,-1};
                return defaultPos;
            }

            handleCursorMovement(input, &selectedPos.x, &selectedPos.y);
            clampCursorInCamera(world, &selectedPos.x, &selectedPos.y);
            system("cls");
            printWorld(world, selectedPos.x, selectedPos.y);
            printf("\n");
            printf("(");
            printf("%d", selectedPos.x);
            printf(",");
            printf("%d", selectedPos.y);
            printf(")");

            waitMs(25);
        }
    }
}

Spell* selectPlayerSpell(worldMap* world) {
    void printTopBar() {
        printPlus(RESET, WHITE_HI, BLACK_BG, "  Select a spell:");
        printPlus(RESET, WHITE, BLACK_BG, "\n\n");
        printPlus(RESET, WHITE, BLACK_BG,"  current mana: ");
        char buffer[20];
        sprintf(buffer, "%d", world->Player->mana);
        printPlus(RESET, CYAN, BLACK_BG, buffer);
        printPlus(RESET, WHITE, BLACK_BG, " / ");
        sprintf(buffer, "%d", world->Player->maxMana);
        printPlus(RESET, CYAN, BLACK_BG, buffer);
        printPlus(RESET, WHITE, BLACK_BG, "\n\n\n");

    }
    void printSpell(Spell* spell) {
        char buffer[20];
        sprintf(buffer, "%d", spell->manaCost);
        printSpellName(spell);
        printPlus(RESET, CYAN, BLACK_BG,"    mana: ");
        printPlus(RESET, WHITE, BLACK_BG, buffer);
        printPlus(RESET, WHITE, BLACK_BG, "\n");
    }
    system("cls");

    printTopBar();
    printPlus(RESET, WHITE, BLACK_BG, ">  ");
    Spell* noEmptySpells[world->Player->spells.spellCount];
    int noEmptySpellCount = 0;
    for (int i = 0; i < world->Player->spells.spellCount; i++) {
        if (world->Player->spells.spells[i].spellID == SPELLID_EMPTY) {
            continue;
        }
        if (i > 0) {
            printf("   ");
        }
        printSpell(&world->Player->spells.spells[i]);
        noEmptySpells[noEmptySpellCount] = &world->Player->spells.spells[i];
        noEmptySpellCount ++;
    }
    int selectedSpell = 0;
    while (1) {
        if (_kbhit()) {  
            char input = _getch();
            if (input == 'q') {
                return NULL;
            }
            if (input == ' ') {
                return noEmptySpells[selectedSpell];
            }
            if (input == 's') {
                selectedSpell += 1;
                if (selectedSpell >= noEmptySpellCount) {
                    selectedSpell = noEmptySpellCount - 1;
                }
            }
            if (input == 'w') {
                selectedSpell -= 1;
                if (selectedSpell < 0) {
                    selectedSpell = 0;
                }
            }
            system("cls");
            //printWorld(world, -1, -1);
            printTopBar();
            for (int i = 0; i < noEmptySpellCount; i++) {
                if (noEmptySpells[i]->spellID == SPELLID_EMPTY) {
                    continue;
                }
                if (i == selectedSpell) {
                    printf(">  ");
                } else {
                    printf("   ");
                }
                printSpell(noEmptySpells[i]);
            }
            waitMs(25);
        }
    }   
}
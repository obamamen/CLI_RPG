#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "units.h"
#include "ansi.h"
#include "world.h"
#include "entity.h"
#include "ui.h"
#include "spell.h"
#include <time.h>


void waitMs(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000; 
    nanosleep(&ts, NULL);
}

#ifdef _WIN32
    #include <windows.h>
    #endif

    void enable_virtual_terminal_processing() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) {
            printf("Error getting console handle.\n");
            return;
        }

        DWORD dwMode = 0;
        if (!GetConsoleMode(hConsole, &dwMode)) {
            printf("Error getting console mode.\n");
            return;
        }
        dwMode |= 0x0004;
        if (!SetConsoleMode(hConsole, dwMode)) {
            printf("Error setting console mode.\n");
        }
    #endif
}

void set_code_page_utf8() {
#ifdef _WIN32
    system("chcp 65001 >nul"); // urf-8
#endif
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

Pos SelectXY(worldMap* world) {
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
    Spell* noEmptySpells[world->Player->spellCount];
    int noEmptySpellCount = 0;
    for (int i = 0; i < world->Player->spellCount; i++) {
        if (world->Player->spells[i].spellID == SPELLID_EMPTY) {
            continue;
        }
        if (i > 0) {
            printf("   ");
        }
        printSpell(&world->Player->spells[i]);
        noEmptySpells[noEmptySpellCount] = &world->Player->spells[i];
        noEmptySpellCount ++;
    }
    int selectedSpell = 0;
    while (1) {
        if (_kbhit()) {  
            char input = _getch();
            if (input == 'e') {
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


int main () {
    enable_virtual_terminal_processing(); //otherwise no color in normal cmd
    set_code_page_utf8();  // utf-8 for special chars
    worldMap* world = (worldMap*)malloc(sizeof(worldMap));
    if (world == NULL) {
        printf("allocating memory for worldMap failed womp womp.\n");
        return 1;
    }
    setupWorld(world);
    setupSkeleton(addEntityToWorld(world, 5, 5));
    printWorld(world,-1,-1);

    UIstate ui = UI_PLAY_STATE;
    int cursorX = -1;
    int cursorY = -1;

    Spell fire = {SPELLID_FIREBALL, 10, SPELLTARGETTYPE_POS};
    Spell heal = {SPELLID_SELFHEAL, 15,  SPELLTARGETTYPE_SELF};
    addSpellToEntity(world->Player, fire);
    addSpellToEntity(world->Player, fire);
    addSpellToEntity(world->Player, fire);
    addSpellToEntity(world->Player, fire);
    addSpellToEntity(world->Player, fire);
    addSpellToEntity(world->Player, heal);

    removeSpellFromEntity(world->Player, 1);
    

    while (1) {
        if (_kbhit()) {  
            char input = _getch();  
            if (input == 'v') {
                printf("Size of: %zu\n", sizeof(int*));
                FILE* file = fopen("map.bin", "wb"); 
                if (file == NULL) {
                    exit(1);
                }
                fwrite(world, sizeof(worldMap), 1, file);
                fclose(file);
                continue;
            }
            if (input == 'q') {
                break;
            }
            if (ui==UI_CURSOR_STATE) {
                system("cls");
                handleCursorMovement(input, &cursorX, &cursorY);
                printWorld(world, cursorX, cursorY);
                waitMs(25);
                Entity* onCursor = world->EntitysMap[cursorX][cursorY];
                printEntity(onCursor);
            }
            if ((input == 'c') && (ui==UI_PLAY_STATE)) {
                ui = UI_CURSOR_STATE;
                system("cls");
                cursorX = world->Player->xPos;
                cursorY = world->Player->yPos;
                printWorld(world, world->Player->xPos,world->Player->yPos);
                waitMs(25);
                Entity* onCursor = world->EntitysMap[cursorX][cursorY];
                printEntity(onCursor);
                continue;
            }
            if ((input == 'e') && (ui==UI_PLAY_STATE)) {
                Spell* selectedSpell = selectPlayerSpell(world);
                if (selectedSpell != NULL) {
                    Pos XY;
                    switch (selectedSpell->targetType) {
                        case SPELLTARGETTYPE_POS:
                            XY = SelectXY(world);
                            castSpell(world, selectedSpell, world->Player, world->EntitysMap[XY.x][XY.y]);
                            break;
                        
                        case SPELLTARGETTYPE_SELF:
                            castSpell(world, selectedSpell, world->Player, NULL);
                            break;

                    }
                }
            }
            if ((input == 'c') && (ui==UI_CURSOR_STATE)) {
                ui = UI_PLAY_STATE;
                cursorX = -1;
                cursorY = -1;
                system("cls");
                printWorld(world, -1, -1);
                waitMs(25);
                continue;
            }
            if (ui==UI_PLAY_STATE) {
                system("cls");
                handleMovementInput(input, world);
                updateMap(world); 
                printWorld(world,-1,-1);
                waitMs(25);
            }
            //printf("b: Enemies @  #  X  O  M  &   ☠  ☻  ▒ Cursor >  <  ^  v  *  +  o  .  ←  →  ↑  ↓ UI Elements *  +  -  |  =  .  :  ;  #  √  × +  -  |  ┼  ─  │  ┌  ┐  └  ┘  ╭  ╮  ╰  ╯  ╲  ╱  ╳  ╋  ┃  ━\n"); 
        }
    }

    free(world);
    return 0;
}


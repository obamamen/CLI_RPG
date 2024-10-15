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

    addSpellToList(&world->Player->spells, heal);
    addSpellToList(&world->Player->spells, fire);
    addSpellToList(&world->Player->spells, fire);
    addSpellToList(&world->Player->spells, heal);
    addSpellToList(&world->Player->spells, fire);
    addSpellToList(&world->Player->spells, fire);

    Item item = {"Baller", ITEMTYPE_SWORD};
    addItemToList(&world->Player->inventory, item);
    addItemToList(&world->Player->inventory, item);
    Item item2 = {"Baller2", ITEMTYPE_SWORD};
    addItemToList(&world->Player->inventory, item2);
    addItemToList(&world->Player->inventory, item2);
    printf("%s", world->Player->inventory.items[0].name);

 
    

    while (1) {
        waitMs(5);
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
                clampCursorInCamera(world, &cursorX, &cursorY);
                printWorld(world, cursorX, cursorY);
                waitMs(50);
                Entity* onCursor = world->EntitysMap[cursorX][cursorY];
                printEntity(onCursor);
            }
            if ((input == 'c') && (ui==UI_PLAY_STATE)) {
                ui = UI_CURSOR_STATE;
                system("cls");
                cursorX = world->Player->xPos;
                cursorY = world->Player->yPos;
                printWorld(world, world->Player->xPos,world->Player->yPos);
                waitMs(50);
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
            if ((input == 'f') && (ui==UI_PLAY_STATE)) {
                Item* selectedItem = selectPlayerItem(world);

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


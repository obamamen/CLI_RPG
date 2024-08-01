#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "units.h"
#include "ansi.h"
#include "world.h"
#include "entity.h"
#include "ui.h"
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
    switch (spell->spellID) {
        case SPELLID_FIREBALL:
            printPlus(RESET, WHITE, BLACK_BG, "Fireball");
        break;
    }
}


Spell* selectPlayerSpell(worldMap* world) {
    printPlus(RESET, WHITE, BLACK_BG, "Select a spell:");
    printf("\n");
    printf("\n");
    printPlus(RESET, WHITE, BLACK_BG, "> ");
    Spell* noEmptySpells[InventoryMaxSize];
    int noEmptySpellCount = 0;
    for (int i = 0; i < InventoryMaxSize; i++) {
        if (world->Player->spells[i].spellID == SPELLID_EMPTY) {
            continue;
        }
        printSpellName(&world->Player->spells[i]);
        noEmptySpells[noEmptySpellCount] = &world->Player->spells[i];
        printf("\n");
        noEmptySpellCount ++;
    }
    int selectedSpell = 0;
    while (1) {
        if (_kbhit()) {  
            char input = _getch();


            if (input == 'd') { 
                return noEmptySpells[selectedSpell];
            }
            if (input == 'q') { 
                return NULL;
            }
            if (input == 's') {
                selectedSpell += 1;
            }
            if (input == 'w') {
                selectedSpell -= 1;
                if (selectedSpell < 0) {
                    selectedSpell = 0;
                }
            }
            system("cls");
            printWorld(world, -1, -1);
            printPlus(RESET, WHITE, BLACK_BG, "Select a spell:");
            printf("\n");
            printf("\n");
            for (int i = 0; i < noEmptySpellCount; i++) {
                if (noEmptySpells[i]->spellID == SPELLID_EMPTY) {
                    continue;
                }
                if (i == selectedSpell) {
                    printf("> ");
                }
                printSpellName(noEmptySpells[i]);
                printf("\n");
            }

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
    printPlus(RESET, GREEN_BOLD, BLACK_BG, "a");
    printf("bbb");
    UIstate ui = UI_PLAY_STATE;
    int cursorX = -1;
    int cursorY = -1;
    world->Player->spells[0].spellID = SPELLID_FIREBALL;
    world->Player->spells[1].spellID = SPELLID_FIREBALL;
    //world->Player->spells[2].spellID = SPELLID_FIREBALL;
    world->Player->spells[3].spellID = SPELLID_FIREBALL;
    world->Player->spells[4].spellID = SPELLID_FIREBALL;
    world->Player->spells[5].spellID = SPELLID_FIREBALL;

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
                    printSpellName(selectedSpell);
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


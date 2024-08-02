#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ansi.h"


static const char* attribute_codes[] = {
    "\033[0m",  // RESET
    "\033[1m",  // BOLD
    "\033[4m",  // UNDERLINE
    "\033[7m",  // REVERSE
};

static const char* color_codes[] = {
    "\033[30m", // BLACK
    "\033[31m", // RED
    "\033[32m", // GREEN
    "\033[33m", // YELLOW
    "\033[34m", // BLUE
    "\033[35m", // MAGENTA
    "\033[36m", // CYAN
    "\033[37m", // WHITE
    "\033[40m", // BLACK_BG
    "\033[41m", // RED_BG
    "\033[42m", // GREEN_BG
    "\033[43m", // YELLOW_BG
    "\033[44m", // BLUE_BG
    "\033[45m", // MAGENTA_BG
    "\033[46m", // CYAN_BG
    "\033[47m",  // WHITE_BG
    "\033[1;30m", // BLACK_BOLD
    "\033[1;31m", // RED_BOLD
    "\033[1;32m", // GREEN_BOLD
    "\033[1;33m", // YELLOW_BOLD
    "\033[1;34m", // BLUE_BOLD
    "\033[1;35m", // MAGENTA_BOLD
    "\033[1;36m", // CYAN_BOLD
    "\033[1;37m", // WHITE_BOLD
    "\033[4;30m", // BLACK_UNDERLINE
    "\033[4;31m", // RED_UNDERLINE
    "\033[4;32m", // GREEN_UNDERLINE
    "\033[4;33m", // YELLOW_UNDERLINE
    "\033[4;34m", // BLUE_UNDERLINE
    "\033[4;35m", // MAGENTA_UNDERLINE
    "\033[4;36m", // CYAN_UNDERLINE
    "\033[4;37m", // WHITE_UNDERLINE
    "\033[0;90m", // BLACK_HI
    "\033[0;91m", // RED_HI
    "\033[0;92m", // GREEN_HI
    "\033[0;93m", // YELLOW_HI
    "\033[0;94m", // BLUE_HI
    "\033[0;95m", // MAGENTA_HI
    "\033[0;96m", // CYAN_HI
    "\033[0;97m", // WHITE_HI
    "\033[0;100m",// BLACK_HI_BG
    "\033[0;101m",// RED_HI_BG
    "\033[0;102m",// GREEN_HI_BG
    "\033[0;103m",// YELLOW_HI_BG
    "\033[0;104m",// BLUE_HI_BG
    "\033[0;105m",// MAGENTA_HI_BG
    "\033[0;106m",// CYAN_HI_BG
    "\033[0;107m" // WHITE_HI_BG
};

const char* get_attribute_code(TextAttribute attr) {
    if (attr < 0 || attr >= sizeof(attribute_codes) / sizeof(attribute_codes[0])) {
        return "";
    }
    return attribute_codes[attr];
}

const char* get_color_code(Color color) {
    if (color < 0 || color >= sizeof(color_codes) / sizeof(color_codes[0])) {
        return "";
    }
    return color_codes[color];
}

void appendToBuffer(char* buffer, int* bufferPos, const char* text) {
    int len = strlen(text);
    if (*bufferPos + len < 40000) {
        strcpy(buffer + *bufferPos, text);
        *bufferPos += len;
    } else {
        fprintf(stderr, "Buffer overflow detected\n");
    }
}


void printPlusAppendToBuffer(TextAttribute attr, Color fg, Color bg, const char *text, char* buffer, int* bufferPos) {
    appendToBuffer(buffer, bufferPos, get_attribute_code(attr));    // Text attribute code
    appendToBuffer(buffer, bufferPos, get_color_code(fg));          // Foreground color code
    appendToBuffer(buffer, bufferPos, get_color_code(bg));          // Background color code
    appendToBuffer(buffer, bufferPos, text);     
    appendToBuffer(buffer, bufferPos, get_color_code(RESET));       // The text to print
}

void printPlus(TextAttribute attr, Color fg, Color bg, const char *text) {
    printf("%s%s%s%s", 
        get_attribute_code(attr),   
        get_color_code(fg),         
        get_color_code(bg),         
        text                      
    );
}

void printAlignedSpellMana(const char *name, int mana, int nameWidth, int manaWidth, TextAttribute attr, Color fg, Color bg) {
    char nameBuffer[nameWidth + 1];
    char manaBuffer[manaWidth + 1];

    snprintf(nameBuffer, sizeof(nameBuffer), "%-*s", nameWidth, name);
    snprintf(manaBuffer, sizeof(manaBuffer), "%*d", manaWidth, mana);

    printPlus(attr, fg, bg, nameBuffer);
    printf(" ");
    printPlus(attr, fg, bg, manaBuffer);
}




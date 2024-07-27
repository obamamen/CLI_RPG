#include <stdio.h>
#include "ansi.h"

static const char* attribute_codes[] = {
    "\033[0m",  // RESET
    "\033[1m",  // BOLD
    "\033[4m",  // UNDERLINE
    "\033[7m"   // REVERSE
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
    "\033[47m"  // WHITE_BG
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

void printPlus(TextAttribute attr, Color fg, Color bg, const char *text) {
    printf("%s%s%s%s%s", 
        get_attribute_code(attr), // Text attribute
        get_color_code(fg),       // Foreground color
        get_color_code(bg),       // Background color
        text,                     // Text to print
        get_attribute_code(RESET), // Reset to default
        '\0'
    );
}

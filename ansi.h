#ifndef ANSI_H
#define ANSI_H

typedef enum {
    RESET,
    BOLD,
    UNDERLINE,
    REVERSE
} TextAttribute;

typedef enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BLACK_BG,
    RED_BG,
    GREEN_BG,
    YELLOW_BG,
    BLUE_BG,
    MAGENTA_BG,
    CYAN_BG,
    WHITE_BG
} Color;

const char* get_attribute_code(TextAttribute attr);
const char* get_color_code(Color color);
void printPlus(TextAttribute attr, Color fg, Color bg, const char *text);

#endif // ANSI_H

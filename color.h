#ifndef COLOR_H
#define COLOR_H

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

#endif // COLOR_H
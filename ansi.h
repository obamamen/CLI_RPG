#ifndef ANSI_H
#define ANSI_H

#include "units.h"
#include <stdarg.h>

const char* get_attribute_code(TextAttribute attr);
const char* get_color_code(Color color);
void appendToBuffer(char* buffer, int* bufferPos, const char* text);
void printPlusAppendToBuffer(TextAttribute attr, Color fg, Color bg, const char *text, char* buffer, int* bufferPos);
void printPlus(TextAttribute attr, Color fg, Color bg, const char *text);
void printAlignedSpellMana(const char *name, int mana, int nameWidth, int manaWidth, TextAttribute attr, Color fg, Color bg);
#endif // ANSI_H

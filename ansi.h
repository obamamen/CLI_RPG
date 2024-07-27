#ifndef ANSI_H
#define ANSI_H

#include "units.h"

const char* get_attribute_code(TextAttribute attr);
const char* get_color_code(Color color);
void printPlus(TextAttribute attr, Color fg, Color bg, const char *text);

#endif // ANSI_H

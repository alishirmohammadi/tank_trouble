

#include "colors.h"

Color new_Color(int r, int g, int b, int a) {
    Color c;
    c.red = r;
    c.green = g;
    c.blue = b;
    c.alpha = a;
    return c;
}
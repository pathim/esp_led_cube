#ifndef CHARS_H
#define CHARS_H

#include "led_strip.h"

#include "../led_cube.h"

void show_char(const LedCube &led_cube,int c, int fg, int bg, int side);

#endif
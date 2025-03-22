
#include "gfx.h"
#include "SSD1306.h"

unsigned int _buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT/8];
DisplayBuffer buffer = (DisplayBuffer) {DISPLAY_WIDTH, DISPLAY_HEIGHT, _buffer};

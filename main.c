
#include "f28002x_device.h"
#include "init.h"
#include "SSD1306.h"
#include <stdlib.h>

void main(void)
{
    InitDSP();
    InitI2C();
    InitDisplay();

    unsigned long int n = 1024;//DISPLAY_WIDTH * DISPLAY_HEIGHT/8; 
    Uint16* buffer = malloc(n);

    for (unsigned long int i = 0; i<n; i++) {
        buffer[i] = 0x00;
    }
    
    SendDisplayBuffer(buffer, n);
    // free(buffer);
}

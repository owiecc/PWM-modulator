
#include "f28002x_device.h"
#include "init.h"
#include "SSD1306.h"
#include <stdlib.h>

void main(void)
{
    InitSysCtrl(); 
    InitEpwm();
    InitI2C();
    InitDisplay();

    unsigned int n = DISPLAY_WIDTH * DISPLAY_HEIGHT/8;
    unsigned int *buffer = malloc(n);

    for (unsigned int i = 0; i<n; i++) {
        buffer[i] = 0x00;
    }
    
    SendDisplayBuffer(buffer, n);
    // free(buffer);
}

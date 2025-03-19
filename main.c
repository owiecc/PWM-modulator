
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

    for (unsigned int i = 0; i < DISPLAY_BUFFER_SIZE; i++) {
        buffer[i] = 0x00;
    }
    
    UpdateDisplay(buffer);
}

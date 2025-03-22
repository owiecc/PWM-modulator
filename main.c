
#include "f28002x_device.h"
#include "init.h"
#include "SSD1306.h"
#include "gfx.h"

void main(void)
{
    InitSysCtrl(); 
    InitEpwm();
    InitI2C();
    InitDisplay();

    for (unsigned int i = 0; i < buffer.xSize * buffer.ySize / 8; i++) {
        buffer.data[i] = 0xFF;
    }

    UpdateDisplay(data);
}

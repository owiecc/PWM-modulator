
#include "init.h"
#include "oled.h"

void main(void)
{
    InitDSP();
    InitI2C();
    SendI2C2(0xA8, 0x3F); // Set MUX ratio
    SendI2C2(0xD3, 0x00); // Set display offset
    SendI2C(0x40); // Set display start line
    SendI2C(0xA0); // Set segment re-map
    SendI2C(0xC0); // Set COM output scan direction
    SendI2C2(0xDA, 0x02); // Set COM pins hardware configuration
    SendI2C2(0x81, 0x7F); // Set contrast
    SendI2C(0xA4); // Entire display on
    SendI2C(0xA6); // Set normal display
    SendI2C2(0xD5, 0x80); // Set oscillator frequency
    SendI2C2(0x8D, 0x14); // Enable charge pump regulator
    SendI2C(0xAF); // Display on
}

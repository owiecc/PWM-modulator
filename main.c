
#include "f28002x_device.h"
#include "init.h"
#include "SSD1306.h"
#include <stdlib.h>

void main(void)
{
    InitDSP();
    InitI2C();
    SendI2C(0xAE); // Display off
    SendI2C2(0xD5, 0x80); // Set oscillator frequency
    SendI2C2(0xA8, OLED_HEIGHT - 1); // Set MUX ratio
    SendI2C2(0xD3, 0x00); // Set no offset 
    SendI2C(0x40); // Set display start line
    SendI2C2(0x8D, 0x14); // Enable charge pump regulator
    SendI2C2(0x20, 0x00); // Set memory mode KS0108
    SendI2C(0xA1); // Set segment re-map 0xA0 | 0x01
    SendI2C(0xC8); // Set COM output scan direction
    SendI2C2(0xDA, 0x12); // Set COM pins hardware configuration
    SendI2C2(0x81, 0xCF); // Set contrast
    SendI2C2(0xD9, 0xF1); // Set precharge

    SendI2C2(0xDB, 0x40); // Set VCOM detect
    SendI2C(0xA4); // Entire display on
    SendI2C(0xA6); // Set normal display
    SendI2C(0x2E); // Deactivate scroll
    SendI2C(0xAF); // Display on

    SendI2C2(0x22, 0x00); // Set page address
    SendI2C(0xFF); // Set page end
    SendI2C2(0x21, 0x00); // Set column address
    SendI2C(DISPLAY_WIDTH - 1); // Set column end

    unsigned long int n = DISPLAY_WIDTH * DISPLAY_HEIGHT/8; 
    Uint16* buffer = malloc(n);

    for (unsigned long int i = 0; i<n; i++) {
        buffer[i] = 0x00;
    }
    
    SendDisplayBuffer(buffer, n);
    // free(buffer);
}

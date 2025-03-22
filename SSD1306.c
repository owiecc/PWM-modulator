
#include "SSD1306.h"
#include "f28002x_device.h"
#include "f28002x_i2c.h"

int SendI2C(unsigned int);
int SendI2C2(unsigned int, unsigned int);

//unsigned int buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT/8];

void InitDisplay()
{
    SendI2C(0xAE); // Display off
    SendI2C2(0xD5, 0x80); // Set oscillator frequency
    SendI2C2(0xA8, DISPLAY_HEIGHT - 1); // Set MUX ratio
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
}

int SendI2C(unsigned int data)
{
    while (I2caRegs.I2CSTR.bit.BB != 0); // wait for bus free
    I2caRegs.I2CSAR.all = DISPLAY_I2C_ADDR; // display address
    I2caRegs.I2CMDR.bit.MST = 1; // master mode
    I2caRegs.I2CMDR.all = 0x66A0;
    I2caRegs.I2CMDR.bit.STT = 1; // generate START condition
    I2caRegs.I2CMDR.bit.RM = 1; // repeat mode
    I2caRegs.I2CMDR.bit.TRX = 1; // transmit mode
    I2caRegs.I2CDXR.all = 0x00; // load command/data byte; Co = 0, D/C = 0
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CDXR.all = data; // load data into the transmit register
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CMDR.bit.STP = 1; // generate STOP condition
    while(I2caRegs.I2CMDR.bit.STP != 0x0); // wait for STOP condition
    return 0;
}

int SendI2C2(unsigned int data1, unsigned int data2)
{
    while (I2caRegs.I2CSTR.bit.BB != 0); // wait for bus free
    I2caRegs.I2CSAR.all = DISPLAY_I2C_ADDR; // display address
    I2caRegs.I2CMDR.bit.MST = 1; // master mode
    I2caRegs.I2CMDR.all = 0x66A0;
    I2caRegs.I2CMDR.bit.STT = 1; // generate START condition
    I2caRegs.I2CMDR.bit.RM = 1; // repeat mode
    I2caRegs.I2CMDR.bit.TRX = 1; // transmit mode
    I2caRegs.I2CDXR.all = 0x00; // command byte; Co = 0, D/C = 0
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CDXR.all = data1; // load data into the transmit register
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CDXR.all = data2; // load data into the transmit register
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CMDR.bit.STP = 1; // generate STOP condition
    while(I2caRegs.I2CMDR.bit.STP != 0x0); // wait for STOP condition
    return 0;
}

int UpdateDisplay(unsigned int *buffer) 
{
    unsigned int sizeBuffer = DISPLAY_BUFFER_SIZE; // (OLED_WIDTH*OLED_HEIGHT)/2;
    unsigned int *ptr = buffer;
    while (I2caRegs.I2CSTR.bit.BB != 0); // wait for bus free
    I2caRegs.I2CSAR.all = DISPLAY_I2C_ADDR; // display address
    I2caRegs.I2CMDR.bit.MST = 1; // master mode
    I2caRegs.I2CMDR.all = 0x66A0;
    I2caRegs.I2CMDR.bit.STT = 1; // generate START condition
    I2caRegs.I2CMDR.bit.RM = 1; // repeat mode
    I2caRegs.I2CMDR.bit.TRX = 1; // transmit mode
    I2caRegs.I2CDXR.all = 0x40; // data byte; Co = 0, D/C = 1
    while (sizeBuffer--) {
        unsigned int data = *ptr++; // get data (two bytes)
        while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
        I2caRegs.I2CDXR.all = data; // load data into the transmit register
    }
    while (I2caRegs.I2CSTR.bit.XRDY != 1); // wait for end of transmission
    I2caRegs.I2CMDR.bit.STP = 1; // generate STOP condition
    while(I2caRegs.I2CMDR.bit.STP != 0x0); // wait for STOP condition
    return 0;
}

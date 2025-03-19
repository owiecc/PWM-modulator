
#include "SSD1306.h"
#include "f28002x_device.h"
#include "f28002x_i2c.h"

void InitI2C(void)
{
    // Configure GPIO port
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1; // Disable pull-up
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Async input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 1; // SCL
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2; // SCL
    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 1; // SDA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2; // SDL
    EDIS;

    // Set I2C module in reset state
    I2caRegs.I2CMDR.bit.IRS = 0;

    // I2C module frequency should be between 7 and 12MHz per 6.14.2.1.1 I2C Timing Requirements
    I2caRegs.I2CPSC.all = 9; // SYSCLK/(I2CPSC+1) = 10MHz

    // I2C clock set at 50kHz (100kHz max)
    // d = 5 for I2CPSC = 9 per Table 23-1
    I2caRegs.I2CCLKH = 195;
    I2caRegs.I2CCLKL = 195;
    // TODO Test timings

    // load slave address
    I2caRegs.I2CSAR.all = I2C_SLAVE_ADDR;

    // Take I2C module out of reset state
    I2caRegs.I2CMDR.bit.IRS = 1;
}

int SendI2C(unsigned int data)
{
    while (I2caRegs.I2CSTR.bit.BB != 0); // wait for bus free
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

int SendDisplayBuffer(unsigned int *buffer, unsigned int sizeBuffer) 
{
    //unsigned int sizeBuffer = 128; // (OLED_WIDTH*OLED_HEIGHT)/2;
    unsigned int *ptr = buffer;
    while (I2caRegs.I2CSTR.bit.BB != 0); // wait for bus free
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

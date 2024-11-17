
#include "oled.h"
#include "f28002x_device.h"

void InitI2C(void)
{
    // Configure GPIO port
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1; // Disable pull-up
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Async input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2; // SCL
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 1; // SCL
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2; // SDL
    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 1; // SDA
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

    // Take I2C module out of reset state
    I2caRegs.I2CMDR.bit.IRS = 1;

    // load slave address
    I2caRegs.I2CSAR.all = I2C_SLAVE_ADDR;
}

int SendI2C(unsigned int data)
{
    // wait for STOP condition
    while (I2caRegs.I2CMDR.bit.STP != 0);

    // master mode
    I2caRegs.I2CMDR.bit.MST = 1;

    // generate START condition
    I2caRegs.I2CMDR.bit.STT = 1;

    // repeat mode
    I2caRegs.I2CMDR.bit.RM = 1;

    // transmit mode
    I2caRegs.I2CMDR.bit.TRX = 1;

    // wait for XRDY flag to transmit data
    while (I2caRegs.I2CSTR.bit.XRDY != 1);

    // load data into the transmit register
    I2caRegs.I2CDXR.all = data;

    // wait for XRDY flag to transmit data or ARDY if we get NACKed
    //while (I2caRegs.I2CSTR.bit.XRDY != 1 || I2caRegs.I2CSTR.bit.ARDY != 1);
    while (I2caRegs.I2CSTR.bit.XRDY != 1);

    I2caRegs.I2CMDR.bit.STP = 1;

    for (unsigned long int i = 0; i < 10000; i++) {}

    return 0;
}

int SendI2C2(unsigned int data1, unsigned int data2)
{
    SendI2C(data1);
    SendI2C(data2);
    /*
    // wait for STOP condition
    while (I2caRegs.I2CMDR.bit.STP != 0);

    // master mode
    I2caRegs.I2CMDR.bit.MST = 1;

    // generate START condition
    I2caRegs.I2CMDR.bit.STT = 1;

    // repeat mode
    I2caRegs.I2CMDR.bit.RM = 1;

    // transmit mode
    I2caRegs.I2CMDR.bit.TRX = 1;

    // wait for XRDY flag to transmit data
    while (I2caRegs.I2CSTR.bit.XRDY != 1);

    // load data into the transmit register
    I2caRegs.I2CDXR.all = data1;

    // wait for XRDY flag to transmit data
    while (I2caRegs.I2CSTR.bit.XRDY != 1);

    // load data into the transmit register
    I2caRegs.I2CDXR.all = data2;

    // wait for XRDY flag to transmit data or ARDY if we get NACKed
    //while (I2caRegs.I2CSTR.bit.XRDY != 1 || I2caRegs.I2CSTR.bit.ARDY != 1);
    while (I2caRegs.I2CSTR.bit.XRDY != 1);

    I2caRegs.I2CMDR.bit.STP = 1;

    asm(" RPT #120 || NOP");
*/
    return 0;
}

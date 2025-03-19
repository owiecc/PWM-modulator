
#include "init.h"
#include "f28002x_device.h"

void InitEpwm(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.all &= 0x00FF;   // Disable pull-up on GPIO0-7 (EPWM1-4)
    GpioCtrlRegs.GPAMUX1.all &= 0x00FF;  // Configure GPIO0-7 as EPWM
    EDIS;
}

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

    // Take I2C module out of reset state
    I2caRegs.I2CMDR.bit.IRS = 1;
}

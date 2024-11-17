
#include "init.h"
#include "f28002x_device.h"

void initDSP(void)
{
    InitSysCtrl(); // Init device clock and peripherals

    EALLOW;
    GpioCtrlRegs.GPAPUD.all &= 0x00FF;   // Disable pull-up on GPIO0-7 (EPWM1-4)
    GpioCtrlRegs.GPAMUX1.all &= 0x00FF;  // Configure GPIO0-7 as EPWM
    EDIS;
}

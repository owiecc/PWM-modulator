
 #include "f28002x_device.h"

void main(void)
{
    EALLOW;
    GpioCtrlRegs.GPADIR.all = 0x00FF;  // GPIO0..7 output
    EDIS;
}

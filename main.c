
 #include "f28002x_device.h"

void main(void)
{
    EALLOW;
    GpioCtrlRegs.GPADIR.all = 0x00FF;  // GPIO0..7 output

    EDIS;

    long unsigned int i = 0;

    for(;;)
    {
        short unsigned int m = i >> 16;
        GpioDataRegs.GPASET.all = m;
        GpioDataRegs.GPACLEAR.all = ~m;
        i++;
    }
}

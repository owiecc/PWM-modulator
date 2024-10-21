
 #include "f28002x_device.h"

void main(void)
{
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0 = output
    EDIS;

    for(;;)
    {
        GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;
        for(unsigned int i=0; i<65000; i++){}
    }
}

#include "system_sam3x.h"
#include "at91sam3x8.h"
void main(void)
{
    SystemInit();          //Disables the Watchdog and setup the MCK
    SysTick_Config(83999); //SysTick Set to 1ms
                           //    init_keypad();
                           //    init_display();
                           //    setup_display();
    init_temp();
    //    init_sensor();
    //    init_pwm();
    //    clear_display();

    //    command_display(0x24);
    while (1)
    {
        //if(nTick > 5000)
        //{
        //    nTick = 0;
        //}
        measure_temp();
        //            double temperature = (((temp_pulse * (1/42.0)) / 5 ) - 273.15);
        //            temperature = temperature;
    }
}

#include "common.h"
#include "led_display.h"

#if ENABLE_LED_MOUDLE

enum{
    LED_DEMO_0,
    LED_DEMO_1,
};

void led_init(unsigned char status)
{
	LED = status;
}

void turn_one_led()
{
    led_init(0xf0);
    while(1)
    {
        LED_0 =~LED_0;
        delay_ms(1000*1);
        LED_1 =~LED_1;
        delay_ms(1000*1);
        LED_2 =~LED_2;
        delay_ms(1000*1);
        LED_3 =~LED_3;
        delay_ms(1000*1);
    }
}

void run_led_demo(unsigned index)
{
    switch (index)
    {
    case LED_DEMO_0:
		turn_one_led();
        break;
    case LED_DEMO_1:
        break;
    default:
        break;
    }
}
#endif
#ifndef __LED_DISPLAY_H__
#define __LED_DISPLAY_H__

void led_init(unsigned char status);
void turn_one_led();
void run_led_demo(unsigned index);
void enableLED(unsigned index);
void disableLED(unsigned index);
void turnLED(unsigned num);
#endif // __LED_DISPLAY_H__
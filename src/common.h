#ifndef __COMMON_H__
#define __COMMON_H__
#include <intrins.h>
#include "gpio.h"
#include "config.h"
#include "display.h"
#include "uart.h"
#include "interrupt.h"
#include "nv_flash.h"
#include "led_display.h"
#include "temperature.h"
#include "RTX51TNY.h"
#include "dht11.h"
#include "st7735s.h"

#define OK       0
#define ERROR   -1

#define LED_ON   0
#define LED_OFF  1

//#define OSC_FREQUENCY 11059200UL    // Hz
//#define OS_TICK 1*1000*5            // us 5ms
//#define OS_TIMER0_INIT_VALUE  (65536-(OS_TICK*OSC_FREQUENCY/12)/(1000*1000)) // timer init value

#define OSC_CLK_FREQUENCY       11059200UL                  // Hz
#define OSC_MC_FREQUENCY        (OSC_CLK_FREQUENCY/12)
#define OS_TICK                 5*1000E-6L                  // s
#define OSC_MC_TCOUNT     		(OS_TICK*OSC_MC_FREQUENCY)
#define OS_TIMER0_INIT_VALUE    (65536-OSC_MC_TCOUNT)

enum{
    LED_DEMO_TASK = 1,
    TEMP_DEMO_TASK,
    UART_DEMO_TASK,
};


void delay_10us();
void delay_us(unsigned us);
void delay_ms(unsigned ms);
void delay_sec(unsigned sec);
#endif // __COMMON_H__
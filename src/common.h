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

enum{
    LED_DEMO_TASK = 1,
    TEMP_DEMO_TASK,
    UART_DEMO_TASK,
};

/*ÑÓÊ±º¯Êý*/ 
void delay_10us();
void delay_us(unsigned us);
void delay_ms(unsigned ms);
void delay_sec(unsigned sec);
#endif // __COMMON_H__
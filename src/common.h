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

/*ÑÓÊ±º¯Êý*/ 
void delay_us(unsigned us);
void delay_ms(unsigned ms);

#endif // __COMMON_H__
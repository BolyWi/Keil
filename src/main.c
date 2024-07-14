#include "gpio.h"
#include "common.h"
#include "display.h"
#include "nv_flash.h"

#define DEMO_ADDR 0x2200

// 主程序入口
void main()
{
	lcd_init();
	run_display_time();
}
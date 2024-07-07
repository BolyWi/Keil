#include "gpio.h"
#include "stdio.h"
#include "stdlib.h"
#include "intrins.h"
#include "string.h"
#include "stdio.h"
#include "uart.h"
#include "common.h"
#include "display.h"

xdata char content[32] = {0};
xdata char hello_info[] ={
	"Hello, C51!",
};

// 主程序入口
void main()
{	
	S_TIME *now_time = NULL;
	int i = 0;
	lcd_init();
	initTime(0, 0, 0);
    now_time = get_sys_time();
	
	while (1)
	{
		sprintf(content, "Time : %02d:%02d:%02d", (int)now_time->hour, (int)now_time->min, (int)now_time->sec);
		lcd_show_string(hello_info, 2);
		lcd_show_string(content, 16);
		updateTime();
		delay_s(1);
	}
}
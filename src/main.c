#include "common.h"

#if ENABLE_RTXOS_MOUDLE

void uart_task() _task_ 1
{
    while(1)
    {
        run_display_uart_info();
        delay_ms(10);
    }
}

void Main_task() _task_ 0
{
    lcd_init();
    uart_config();
    os_create_task(1);
    os_delete_task(0);
}
#else
// 主程序入口
void main()
{
    while(1)
    {
        delay_ms(500);
    }
}
#endif
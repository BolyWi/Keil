#ifndef __UART_H__
#define __UART_H__
#include "gpio.h"

// 初始化串口
void uart_config();
// 串口发送数据
void uart_send(unsigned char buf);
/*重定向putchar() 用于串口log输出*/
char putchar(char c);
#endif // __UART_H__
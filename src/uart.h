#ifndef __UART_H__
#define __UART_H__
#include "gpio.h"

// ��ʼ������
void uart_config();
// ���ڷ�������
void uart_send(unsigned char buf);
/*�ض���putchar() ���ڴ���log���*/
char putchar(char c);
#endif // __UART_H__
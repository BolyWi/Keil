#ifndef __UART_H__
#define __UART_H__
#include <string.h>
#include <stdlib.h>

// ��ʼ������
void uart_config();
// ���ڷ�������
void uart_send(unsigned char buf);
/*�ض���putchar() ���ڴ���log���*/
char putchar(char c);

int get_uart_info(char* buf, int buf_len);
#endif // __UART_H__
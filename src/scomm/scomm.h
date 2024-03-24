#ifndef __SCOMM_H__
#define __SCOMM_H__

#include "REG52.H"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void uart_config();
void sendStr(char* str);

#endif//__SCOMM_H__
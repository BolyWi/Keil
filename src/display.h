#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <string.h>
#include "gpio.h"
#include "common.h"

#define MAX_CHAR_ROW 2
#define MAX_CHAR_COL 16
#define MAX_CHAR_NUM MAX_CHAR_ROW * MAX_CHAR_COL

typedef unsigned char U8;


void lcd_init();
void lcd_write_commond(U8 commond);
void lcd_write_data(U8 dat);

void lcd_show_char(U8 content, U8 x, U8 y);
void lcd_show_string(U8 *content, U8 start_pos);

void run_display_time();
#endif //_DISPLAY_H_
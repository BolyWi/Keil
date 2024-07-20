#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <string.h>

#define MAX_CHAR_ROW 2
#define MAX_CHAR_COL 16
#define MAX_CHAR_NUM MAX_CHAR_ROW * MAX_CHAR_COL

typedef unsigned char U8;

void lcd_init();
static void lcd_write_commond(U8 commond);
static void lcd_write_data(U8 dat);
static void lcd_set_pos(U8 x, U8 y);

void lcd_show_char(U8 content, U8 x, U8 y);
void lcd_show_string(U8 *content, U8 start_pos);

void run_display_time();
void run_display_temp();
#endif //_DISPLAY_H_
#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "gpio.h"
#include "common.h"
#include "string.h"
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;
sfr  LCD_DATA = 0x80;

#define MAX_CHAR_ROW 2
#define MAX_CHAR_COL 16
#define MAX_CHAR_NUM MAX_CHAR_ROW * MAX_CHAR_COL

typedef unsigned char U8;


void lcd_init();
void lcd_write_commond(U8 commond);
void lcd_write_data(U8 dat);

void lcd_show_char(U8 content, U8 x, U8 y);
void lcd_show_string(U8 *content, U8 start_pos);
#endif //_DISPLAY_H_
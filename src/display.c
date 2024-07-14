#include "display.h"

xdata char s_date[32] = {0};
xdata char s_time[32] = {0};
xdata char hello_info[] ={
	"Hello, C51!",
};

void lcd_init()
{
    lcd_write_commond(0x01);
    lcd_write_commond(0x06);
    lcd_write_commond(0x0c);
    lcd_write_commond(0x38);
}

void lcd_write_commond(U8 commond)
{
    LCD_EN = 1;
    LCD_RS = 0;
    LCD_RW = 0;

    LCD_DATA = commond;
	delay_us(100);
    LCD_EN = 0;
}

void lcd_write_data(U8 dat)
{
    LCD_EN = 1;
    LCD_RS = 1;
    LCD_RW = 0;

    LCD_DATA = dat;
	delay_us(100);
    LCD_EN = 0;
    LCD_RS = 0;
}

void lcd_set_pos(U8 x, U8 y)
{
	U8 pos_x = 0, pos_y = 0;
	U8 pos_addr = 0;
	if( 0 <= x && x < 16)
		pos_x = x;
	if( 0 <= y && y < 2)
		pos_y = y;

	if(pos_y == 0)
		pos_addr = 0x80 + pos_x;
	else
		pos_addr = 0x80 + 0x40 + pos_x;

	lcd_write_commond(pos_addr);
}

void lcd_show_char(U8 Char, U8 x, U8 y)
{
	lcd_set_pos(x, y);
	lcd_write_data(Char);
}

void lcd_show_string(U8 *content, U8 start_pos)
{
	unsigned i = 0;
	unsigned len = 0;
	U8 x = 0, y = 0;
	len = strlen(content);
	if(len == 0)
		return;
	if( 0 < start_pos && start_pos < MAX_CHAR_NUM - 1)
	{
		x = start_pos % 16;
		y = start_pos / 16;
	}
	while(i < len)
	{
		lcd_show_char(*content, x, y);
		content++;
		i++;
		// change line ?
		if(x < MAX_CHAR_COL - 1)
			x++;
		else
		{
			x = 0;
			// change page ?
			if( y < MAX_CHAR_ROW - 1)
				y++;
			else
			{
				y = 0;
				lcd_write_commond(0x01);
			}
		}
	}
}


void run_display_time()
{
	S_TIME *now_time = NULL;
	unsigned char old_date = 0;
	lcd_init();
	Ds1302Init();

	while (1)
	{
		Ds1302ReadTime();
		now_time = get_sys_time();
		sprintf(s_date, "Date:20%02d-%02d-%02d", (int)now_time->year, (int)now_time->month, (int)now_time->day);
		sprintf(s_time, "Time:%02d:%02d:%02d %d", (int)now_time->hour, (int)now_time->min, (int)now_time->sec, (int)now_time->week);

		if(old_date != now_time->day)
		{
			lcd_show_string(s_date, 0);
			old_date = now_time->day;
		}

		lcd_show_string(s_time, 16);
		delay_s(1);
	}
}
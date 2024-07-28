#include "display.h"
#include "common.h"
#include "clock.h"
#include "uart.h"

#if ENABLE_LCD_MOUDLE

void lcd_init()
{
    lcd_write_commond(0x01);
    lcd_write_commond(0x06);
    lcd_write_commond(0x0c);
    lcd_write_commond(0x38);
}

static void lcd_write_commond(U8 commond)
{
    LCD_EN = 1;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DATA = commond;
    delay_us(80);
    LCD_EN = 0;
}

static void lcd_write_data(U8 dat)
{
    LCD_EN = 1;
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DATA = dat;
    delay_us(80);
    LCD_EN = 0;
    LCD_RS = 0;
}

static void lcd_set_pos(U8 x, U8 y)
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
    U8 i = 0;
    U8 len = 0;
    U8 pos = 0;
    len = strlen(content);
    if(len == 0)
        return;
    if( 0 < start_pos && start_pos < MAX_CHAR_NUM - 1)
    {
        pos = start_pos;
    }

    while(*content != '\0')
    {
        lcd_show_char(*content, pos % 16, pos / 16);
        pos++;
        if(pos > MAX_CHAR_NUM)
        {
            pos = 0;
            lcd_write_commond(0x01);
        }
        content++;
    }
}

#if ENABLE_UART_MOUDLE
void run_display_uart_info()
{
    char display_buf[128] = { 0 };
    int len = sizeof(display_buf);
    memset(display_buf, 0, len);
    get_uart_info(display_buf, len);
    if(strlen(display_buf) > 0)
    {
        lcd_write_commond(0x01);
        lcd_show_string(display_buf, 0);
    }
}
#endif

#if ENABLE_TEMPERATURE_MOUDLE
void run_display_temp()
{
    char buf[16] = { 0 };
    sprintf(buf, "temp: %0.3f %cC", get_temperature(), 0xdf);
    lcd_show_string(buf, 0);
}
#endif

#if ENABLE_CLOCK_MOUDLE
void run_display_time()
{
    char s_date[16] = {0};
    char s_time[16] = {0};

    lcd_init();
    clock_init();

    while (1)
    {
        get_time_string(s_date, s_time);
        lcd_show_string(s_date, 0);
        lcd_show_string(s_time, 16);
        delay_ms(100);
    }
}
#endif


#endif
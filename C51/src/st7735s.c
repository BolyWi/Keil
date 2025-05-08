#include "common.h"
#include "st7735s.h"
#include <math.h>

#if ENABLE_TFT_MOUDLE

#define USE_LANDSCAPE

#define RED    0xF800
#define GREEN  0x07E0
#define BLUE   0x001F
#define WHITE  0xFFFF
#define BLACK  0x0000
#define YELLOW 0xFFE0
#define PINK   0xFDF9
#define CYAN   0x07FF
#define AQUA   0xD79C
#define TEAL   0x0410
#define LIME   0x07E0
#define WHEAT  0xF6F6

void spi_write_data(unsigned char dat)
{
    unsigned char i = 0;
    for(i = 8; i > 0; i--)
    {
        if(dat & 0x80)
            TFT_SDA = 1;
        else
            TFT_SDA = 0;
        TFT_SCL = 0;
        TFT_SCL = 1;
        dat <<= 1;
    }
}

void TFT_write_com(unsigned char com)
{
    TFT_CS = 0;
    TFT_DC = 0;
    spi_write_data(com);
    TFT_CS = 1;
}

void TFT_write_data(unsigned char dat)
{
    TFT_CS = 0;
    TFT_DC = 1;
    spi_write_data(dat);
    TFT_CS = 1;
}

void TFT_write_word(unsigned dat)
{
    unsigned char i=0;
    TFT_CS=0;
    TFT_DC=1;
    spi_write_data(dat >> 8);                     //写入高8位数据
    spi_write_data(dat);                         //写入低8位数据
    TFT_CS=1;
}

void TFT_reset()
{
    TFT_RST = 0;
    delay_ms(100);
    TFT_RST = 1;
    delay_ms(100);
}

void TFT_init()
{
    TFT_reset();
    //LCD Init For 1.44Inch LCD Panel with ST7735R.
    TFT_write_com(0x11);//Sleep exit
    delay_ms(120);

    //ST7735R Frame Rate
    TFT_write_com(0xB1);
    TFT_write_data(0x01);
    TFT_write_data(0x2C);
    TFT_write_data(0x2D);

    TFT_write_com(0xB2);
    TFT_write_data(0x01);
    TFT_write_data(0x2C);
    TFT_write_data(0x2D);

    TFT_write_com(0xB3);
    TFT_write_data(0x01);
    TFT_write_data(0x2C);
    TFT_write_data(0x2D);
    TFT_write_data(0x01);
    TFT_write_data(0x2C);
    TFT_write_data(0x2D);
    
    TFT_write_com(0xB4); //Column inversion
    TFT_write_data(0x07);
    
    //ST7735R Power Sequence
    TFT_write_com(0xC0);
    TFT_write_data(0xA2);
    TFT_write_data(0x02);
    TFT_write_data(0x84);
    TFT_write_com(0xC1);
    TFT_write_data(0xC5);

    TFT_write_com(0xC2);
    TFT_write_data(0x0A);
    TFT_write_data(0x00);

    TFT_write_com(0xC3);
    TFT_write_data(0x8A);
    TFT_write_data(0x2A);
    TFT_write_com(0xC4);
    TFT_write_data(0x8A);
    TFT_write_data(0xEE);
    
    TFT_write_com(0xC5); //VCOM
    TFT_write_data(0x0E);
    
    TFT_write_com(0x36); //MX, MY, RGB mode
    TFT_write_data(0xc0);
    
    
#ifdef USE_LANDSCAPE
    TFT_write_data(0xA8); //竖屏C8 横屏08 A8
#else
    TFT_write_data(0xc8); //竖屏C8 横屏08 A8
#endif               
    //ST7735R Gamma Sequence
    TFT_write_com(0xe0);
    TFT_write_data(0x0f);
    TFT_write_data(0x1a);
    TFT_write_data(0x0f);
    TFT_write_data(0x18);
    TFT_write_data(0x2f);
    TFT_write_data(0x28);
    TFT_write_data(0x20);
    TFT_write_data(0x22);
    TFT_write_data(0x1f);
    TFT_write_data(0x1b);
    TFT_write_data(0x23);
    TFT_write_data(0x37);
    TFT_write_data(0x00);         
    TFT_write_data(0x07);
    TFT_write_data(0x02);
    TFT_write_data(0x10);

    TFT_write_com(0xe1);
    TFT_write_data(0x0f);
    TFT_write_data(0x1b);
    TFT_write_data(0x0f);
    TFT_write_data(0x17);
    TFT_write_data(0x33);
    TFT_write_data(0x2c);
    TFT_write_data(0x29);
    TFT_write_data(0x2e);
    TFT_write_data(0x30);
    TFT_write_data(0x30);
    TFT_write_data(0x39);
    TFT_write_data(0x3f);
    TFT_write_data(0x00);
    TFT_write_data(0x07);
    TFT_write_data(0x03);
    TFT_write_data(0x10);  
    
    TFT_write_com(0x2a);
    TFT_write_data(0x00);
    TFT_write_data(0x00+2);
    TFT_write_data(0x00);
    TFT_write_data(0x80+2);

    TFT_write_com(0x2b);
    TFT_write_data(0x00);
    TFT_write_data(0x00+3);
    TFT_write_data(0x00);
    TFT_write_data(0x80+3);
    
    TFT_write_com(0xF0); //Enable test command  
    TFT_write_data(0x01);
    TFT_write_com(0xF6); //Disable ram power save mode
    TFT_write_data(0x00);

    TFT_write_com(0x3A); //65k mode
    TFT_write_data(0x05);

    TFT_write_com(0x29);//Display on
}

void TFT_set_region(unsigned x_start,unsigned y_start,unsigned x_end,unsigned y_end)
{        
#ifdef USE_LANDSCAPE//使用横屏模式
    TFT_write_com(0x2a);
    TFT_write_data(0x02);
    TFT_write_data(x_start);
    TFT_write_data(0x02);
    TFT_write_data(x_end);

    TFT_write_com(0x2b);
    TFT_write_data(0x01);
    TFT_write_data(y_start);
    TFT_write_data(0x01);
    TFT_write_data(y_end);

#else//竖屏模式        
    TFT_write_com(0x2a);
    TFT_write_data(0x02);
    TFT_write_data(x_start);
    TFT_write_data(0x02);
    TFT_write_data(x_end);

    TFT_write_com(0x2b);
    TFT_write_data(0x01);
    TFT_write_data(y_start);
    TFT_write_data(0x01);
    TFT_write_data(y_end);        
#endif
    TFT_write_com(0x2c);
}

void TFT_clear(unsigned color)
{
    unsigned char i,j;
    TFT_set_region(0,0,128,160);
    for (i=0;i<160;i++)
        for (j=0;j<128;j++)
            TFT_write_word(color);
}

void TFT_put_pixel(unsigned x_start,unsigned y_start, unsigned color)
{
    TFT_set_region(x_start, y_start, x_start+1, y_start+1);
    TFT_write_word(color);
}

void TFT_draw_line(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned color)
{
    unsigned i;
    unsigned x_cur,y_cur;
    int err_x=0,err_y=0,delta_x,delta_y,distance; 
    int inc_x, inc_y;

    //设置坐标增量
    delta_x = x1 - x0; delta_y = y1 - y0;
    x_cur = x0; y_cur = y0;

    //算法，直接拿来用
    if(delta_x > 0){
        /* 设置单步方向 */
        inc_x=1; 
    }
    else if(delta_x == 0){
        /* 垂直线 */
        inc_x = 0;
    }
    else{ 
        inc_x = -1;
        delta_x    = -delta_x;
    }

    if(delta_y > 0){
        inc_y = 1;
    }
    else if(delta_y==0){
        /* 水平线  */
        inc_y = 0;
    }
    else{
        inc_y = -1;
        delta_y    = -delta_y;
    }

    if(delta_x > delta_y){
        /* 选取基本增量坐标轴 */
        distance = delta_x;  
    }
    else{
        distance = delta_y; 
    }

    //画线输出
    for(i=0;i<=distance+1;i++){
        //画点
        TFT_put_pixel(x_cur,y_cur,color); 
        err_x += delta_x; 
        err_y += delta_y;
        if(err_x > distance){ 
            err_x    -= distance; 
            x_cur += inc_x; 
        }
        if(err_y > distance){
            err_y    -= distance; 
            y_cur += inc_y; 
        }
    }
}

void TFT_draw_rectangle(unsigned x0,unsigned y0, unsigned width, unsigned height, unsigned color, unsigned char bFilled)
{
    unsigned char i = 0;
    //如果是填充矩形
    if(1 == bFilled){
        for(i = 0; i <= height; i++)
        {
            TFT_draw_line(x0, y0+i, x0+width, y0+i, color);
        }
    }
    //不填充矩形
    else{
        //画四条线
        TFT_draw_line(x0, y0, x0 + width - 1, y0, color);
        TFT_draw_line(x0 + width - 1, y0, x0 + width - 1, y0 + height - 1, color);
        TFT_draw_line(x0 + width - 1, y0 + height - 1, x0, y0 + height - 1, color);
        TFT_draw_line(x0, y0 + height - 1, x0, y0, color);
    }
}

void TFT_draw_circle(unsigned center_x, unsigned center_y, unsigned radius, unsigned color, unsigned char bFilled)
{
    int cur_x, cur_y;
    int count;
    int err;

    cur_x = 0;
    cur_y = radius;
    err   = 3 - ( radius << 1 );   //判断下个点位置的标志

    while(cur_x <= cur_y){
        if(bFilled){
            for(count=cur_x;count<=cur_y;count++){
                TFT_put_pixel(center_x + cur_x, center_y + count, color);
                TFT_put_pixel(center_x - cur_x, center_y + count, color);
                TFT_put_pixel(center_x - count,   center_y + cur_x, color);
                TFT_put_pixel(center_x - count,   center_y - cur_x, color);
                TFT_put_pixel(center_x - cur_x, center_y - count, color);
                TFT_put_pixel(center_x + cur_x, center_y - count, color);
                TFT_put_pixel(center_x + count,   center_y - cur_x, color);
                TFT_put_pixel(center_x + count,   center_y + cur_x, color);
            }
        }
        else{
            TFT_put_pixel(center_x + cur_x, center_y + cur_y, color);
            TFT_put_pixel(center_x - cur_x, center_y + cur_y, color);
            TFT_put_pixel(center_x - cur_y, center_y + cur_x, color);
            TFT_put_pixel(center_x - cur_y, center_y - cur_x, color);
            TFT_put_pixel(center_x - cur_x, center_y - cur_y, color);
            TFT_put_pixel(center_x + cur_x, center_y - cur_y, color);
            TFT_put_pixel(center_x + cur_y, center_y - cur_x, color);
            TFT_put_pixel(center_x + cur_y, center_y + cur_x, color);
        }
        cur_x++;
        if(err < 0){
            err += (4*cur_x + 6);
        }
        else{
            err += (10 + 4*(cur_x - cur_y));   
            cur_y--;
        }
    }
}

void TFT_draw_heart(unsigned x0, unsigned y0, unsigned num, unsigned color)
{
    double x = 0.00, y = 0.00;
    double angle = 0.00;
    double t = 0.00;
    unsigned i;
    for (i = 0; i < num; i++)
    {
        angle++;
        t = angle * 3.14 / 180.0;
        x = 16 * pow(sin(t), 3);
        y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
        TFT_put_pixel(x0+x, y0+y, color);
    }
}

void open_flower(unsigned x, unsigned y, unsigned char r, unsigned color)
{
    unsigned char j;
    for(j = 0; j < r; j++)
    {
        TFT_draw_circle(x, y, j, color, 0);
    }
    delay_ms(20);
    for(j = 0; j < r; j++)
    {
        TFT_draw_circle(x, y, j, BLACK, 0);
    }
}

#endif //ENABLE_TFT_MOUDLE
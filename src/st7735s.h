#ifndef __ST7735S_H__
#define __ST7735S_H__

void spi_write_data(unsigned char dat);
void TFT_write_com(unsigned char com);
void TFT_write_data(unsigned char dat);
void TFT_write_word(unsigned dat);
void TFT_reset();
void TFT_init();

void TFT_set_region(unsigned x_start,unsigned y_start,unsigned x_end,unsigned y_end);
void TFT_put_pixel(unsigned x_start, unsigned y_start, unsigned color);
void TFT_clear(unsigned color);

void TFT_draw_line(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned color);
void TFT_draw_rectangle(unsigned x0,unsigned y0, unsigned width, unsigned heigth, unsigned color, unsigned char bFilled);
void TFT_draw_circle(unsigned center_x, unsigned center_y, unsigned radius, unsigned color, unsigned char bFilled);
void TFT_draw_heart(unsigned x0, unsigned y0, unsigned num, unsigned color);
#endif
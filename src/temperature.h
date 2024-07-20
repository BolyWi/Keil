#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

typedef unsigned char uchar;
uchar Ds18b20Init();
void  Ds18b20WriteByte(uchar com);
uchar Ds18b20ReadByte();
void  Ds18b20ChangTemp();
void  Ds18b20ReadTempCom();
int   Ds18b20ReadTemp();
float get_temperature();
#endif //__TEMPERATURE_H__
#include "common.h"

//---DS1302 д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b,
                               0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a,
                                0x8c};
//---DS1302 ʱ�ӳ�ʼ�� 2016 �� 5 �� 7 �������� 12 �� 00 �� 00 �롣---//
//---�洢˳�������ʱ��������,�洢��ʽ���� BCD ��---//
xdata uchar TIME[7] = {0, 0, 0x12, 0x13, 0x07, 0x06, 0x24};

unsigned char BCD_to_uchar(uchar dat)
{
    return (dat >> 4) * 10 + (dat & 0x0f);
}

S_TIME *get_sys_time()
{
    return &colock;
}

unsigned long initTime(unsigned h, unsigned m, unsigned s)
{
    colock.hour = h;
    colock.min = m;
    colock.sec = s;
    colock.total = h * 60 + m * 60 + s;
    return colock.total;
}

unsigned long updateTime()
{
    xdata unsigned long time = 0;
    time = ++colock.total;
    colock.hour = time / (60 * 60);
    colock.min = (time / 60) % 60;
    colock.sec = time % 60;
    return time;
}

void delay_us(unsigned us)
{
    xdata unsigned i = 0;
    while (i < us)
    {
        i++;
        _nop_();
    }
}

void delay_ms(unsigned ms)
{
    xdata unsigned i = 0;
    while (i < ms)
    {
        i++;
        delay_us(65);
    }
}

void delay_s(unsigned s)
{
    xdata unsigned i = 0;
    while (i < s)
    {
        i++;
        delay_ms(1000);
    }
}

void Ds1302Write(uchar addr, uchar dat)
{
    uchar n;
    RST = 0;
    _nop_();
    SCLK = 0; // �Ƚ� SCLK �õ͵�ƽ

    _nop_();
    RST = 1; // Ȼ�� RST(CE)�øߵ�ƽ��
    _nop_();
    for (n = 0; n < 8; n++) // ��ʼ���Ͱ�λ��ַ����
    {
        DSIO = addr & 0x01; // ���ݴӵ�λ��ʼ����
        addr >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0;
        _nop_();
    }
    for (n = 0; n < 8; n++) // д�� 8 λ����
    {
        DSIO = dat & 0x01;
        dat >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0;
        _nop_();
    }
    RST = 0; // �������ݽ���
    _nop_();
}

uchar Ds1302Read(uchar addr)
{
    uchar n, dat, dat1;
    RST = 0;
    _nop_();
    SCLK = 0; // �Ƚ� SCLK �õ͵�ƽ��
    _nop_();
    RST = 1; // Ȼ�� RST(CE)�øߵ�ƽ��
    _nop_();
    for (n = 0; n < 8; n++) // ��ʼ���Ͱ�λ��ַ����
    {
        DSIO = addr & 0x01; // ���ݴӵ�λ��ʼ����
        addr >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0; // DS1302 �½���ʱ����������
        _nop_();
    }
    _nop_();
    for (n = 0; n < 8; n++) // ��ȡ 8 λ����
    {
        dat1 = DSIO; // �����λ��ʼ����
        dat = (dat >> 1) | (dat1 << 7);
        SCLK = 1;
        _nop_();
        SCLK = 0; // DS1302 �½���ʱ����������
        _nop_();
    }
    RST = 0;
    _nop_(); // ����Ϊ DS1302 ��λ���ȶ�ʱ��,����ġ�
    SCLK = 1;
    _nop_();
    DSIO = 0;
    _nop_();
    DSIO = 1;
    _nop_();
    return dat;
}

void Ds1302Init()
{
    uchar n;
    Ds1302Write(0x8E, 0X00); // ��ֹд���������ǹر�д��������
    for (n = 0; n < 7; n++)  // д�� 7 ���ֽڵ�ʱ���źţ�����ʱ��������
    {
        Ds1302Write(WRITE_RTC_ADDR[n], TIME[n]);
    }
    Ds1302Write(0x8E, 0x80); // ��д��������
}

void Ds1302ReadTime()
{
    uchar n;
    for (n = 0; n < 7; n++) // ��ȡ 7 ���ֽڵ�ʱ���źţ�����ʱ��������
    {
        TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
    }
    colock.year  = BCD_to_uchar(TIME[6]);
    colock.week  = BCD_to_uchar(TIME[5]);
    colock.month = BCD_to_uchar(TIME[4]);
    colock.day   = BCD_to_uchar(TIME[3]);
    colock.hour  = BCD_to_uchar(TIME[2]);
    colock.min   = BCD_to_uchar(TIME[1]);
    colock.sec   = BCD_to_uchar(TIME[0]);
}
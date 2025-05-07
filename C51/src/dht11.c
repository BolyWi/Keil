#include "common.h"
#include "dht11.h"
#if ENABLE_DHT11_MOUDLE

static char s_dht_buf[32] = { 0 };  //������ʾ�Ľ�����������

void DHT11_delay_us(uchar n)
{
    while(--n);
}

void DHT11_delay_ms(uchar z)
{
   uchar i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

void DHT11_start()
{
   DHT11=1;
   DHT11_delay_us(2);
   DHT11=0;
   DHT11_delay_ms(30);   //��ʱ18ms����
   DHT11=1;
   DHT11_delay_us(30);
}

uchar DHT11_rec_byte()      //����һ���ֽ�
{
    uchar i,dat=0;
    for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
    {          
      while(!DHT11);   ////�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(8);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(DHT11==1)    //����Ϊ1ʱ��ʹdat��1����������1
         dat+=1;
      while(DHT11);  //�ȴ�����������    
    }  
    return dat;
}

void DHT11_receive()      //����40λ������
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(DHT11==0)
    {
        while(DHT11==0);   //�ȴ�����     
        DHT11_delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����
        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        }
        //��ȡ�¶�ʪ��
        sprintf(s_dht_buf, "%bd.%bd C,%bd.%bd", TH, TL, RH, RL);
    }
}

char* get_DHT11_data()
{
    DHT11_receive();
    return s_dht_buf;
}
#endif
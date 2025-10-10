# C51 学习记录

## IO控制
- P0(addr: 0x80)
- P1(addr: 0x90)
- P2(addr: 0xA0)
- P3(addr: 0xB0)

## 定时器
- TCON(可位寻址)
![TCON寄存器](./res/img/TCON寄存器.png "TCON寄存器")  
- TMOD(不可位寻址)
![TCON寄存器](./res/img/TCON寄存器.png "TCON寄存器")  

![定时器示意图](./res/img/定时器示意图.png "定时器示意图")  
定时器初值计算公式：晶振频率(OSC)、时钟周期(Tc)、机器周期(Tm)、 定时时间(t)、定时器初值(y)  
`Tc = (1/OSC)`
`Tm = 12*(1/OSC)`;  
`x*12*(1/OSC) = t`;  
`y = maxVal - x`;  
<sub>可位寻址/不可位寻址：能否单独对寄存器的某一位进行赋值操作</sub>

## 中断

<sub>中断函数中不要做耗时操作</sub>

## 通信协议

- UART
- SPI
- IIC

## 按键

## LED流水灯

## LED点阵

## LED数码管

## LCD液晶显示

## 蜂鸣器模块

## 时钟模块

## 光敏模块

## 红外模块

## 温度检测模块

## EEPROM

## 电机控制

## 数模转换模块
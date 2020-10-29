/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef		_LCD_H_
#define		_LCD_H_

#include "stm8l15x.h"
#include "stm8l15x_gpio.h"
#include	"display.h"
#include	"function.h"

/**********************HT1621命令宏定义*************************/

#define SYSDIS 0X00 //0b1000 0000 0000 关振系统荡器和LCD偏压发生器
#define SYSEN 0X02 //0b1000 0000 0010 打开系统振荡器
#define LCDOFF 0X04 //0b1000 0000 0100 关LCD偏压
#define LCDON 0X06 //0b1000 0000 0110 打开LCD偏压
#define RC256 0X30 //0b1000 0011 0000 内部时钟
#define TIMER_DIS	0x08
#define WDT_DIS		0x0A
#define TIMER_EN	0x0C
#define WDT_EN		0x07
#define TONE_OFF	0x10
#define TONE_ON		0x12
#define CLR_TIMER	0x18
#define CLR_WDT		0x1C
#define XTAL_32K		0x28
#define RC_256K		0x30
#define EXT_256K		0x38
#define BIAS_12_2C	0x40	// 1/2 偏压，2个com口
#define BIAS_12_3C	0x48// 1/2 偏压，3个com口
#define BIAS_12_4C	0x50// 1/2 偏压，4个com口

#define BIAS_13_2C	0x42// 1/3 偏压，2个com口
#define BIAS_13_3C	0x4A// 1/3 偏压，3个com口
#define BIAS_13_4C	0x52// 1/3 偏压，4个com口

#define TONE_4K		0x80
#define TONE_2K		0xC0
//#define IRQ_DIS
//#define IRQ_EN
//#define F1_CMD
//#define F2_CMD
//#define F4_CMD

/**********************数码管段码宏定义*************************/

#define BLANK_SEG      0x00
#define ALLON_SEG      0xff

#define	Ht1621_POWER_Port		GPIOE
#define	Ht1621_POWER_Pin			GPIO_Pin_2
#define Ht1621_POWER_Low()		GPIO_ResetBits(Ht1621_POWER_Port,Ht1621_POWER_Pin)
#define Ht1621_POWER_High()	GPIO_SetBits(Ht1621_POWER_Port,Ht1621_POWER_Pin)


#define	Ht1621_MODE_Port		GPIOB
#define	Ht1621_MODE_Pin			GPIO_Pin_1
#define Ht1621_MODE_Low()		GPIO_ResetBits(Ht1621_MODE_Port,Ht1621_MODE_Pin)
#define Ht1621_MODE_High()	GPIO_SetBits(Ht1621_MODE_Port,Ht1621_MODE_Pin)


#define	Ht1621_CS1_Port		GPIOB
#define	Ht1621_CS1_Pin			GPIO_Pin_4
#define Ht1621_CS1_Low()		GPIO_ResetBits(Ht1621_CS1_Port,Ht1621_CS1_Pin)
#define Ht1621_CS1_High()	GPIO_SetBits(Ht1621_CS1_Port,Ht1621_CS1_Pin)

#define	Ht1621_CS2_Port		GPIOG
#define	Ht1621_CS2_Pin			GPIO_Pin_4
#define Ht1621_CS2_Low()		GPIO_ResetBits(Ht1621_CS2_Port,Ht1621_CS2_Pin)
#define Ht1621_CS2_High()	GPIO_SetBits(Ht1621_CS2_Port,Ht1621_CS2_Pin)

#define	Ht1621_WR_Port			GPIOB
#define	Ht1621_WR_Pin			GPIO_Pin_3
#define Ht1621_WR_Low()		GPIO_ResetBits(Ht1621_WR_Port,Ht1621_WR_Pin)
#define Ht1621_WR_High()		GPIO_SetBits(Ht1621_WR_Port,Ht1621_WR_Pin)

#define	Ht1621_DATA_Port		GPIOB
#define	Ht1621_DATA_Pin		GPIO_Pin_2
#define Ht1621_DATA_Low()	GPIO_ResetBits(Ht1621_DATA_Port,Ht1621_DATA_Pin)
#define Ht1621_DATA_High()	GPIO_SetBits(Ht1621_DATA_Port,Ht1621_DATA_Pin)


typedef	enum
{
	Select_Chip_1=0,
	Select_Chip_2,
}_HT1621_Chip_Select_;


volatile void Ht1621_Delay(u8 us);
volatile void Ht1621_DelayMS(u16 iMs);
extern void Ht1621_Port_Init(void);
extern void	Ht1621_Select_A_Chip(void);
extern void	Ht1621_Select_B_Chip(void);
extern void	Ht1621_DeSelect_Chip(void);
extern void Ht1621_Write_Data(u8 Data,u8 cnt);
extern void Ht1621_WrCmd_A(u8 Cmd);
extern void Ht1621_WrCmd_B(u8 Cmd);
extern void Ht1621_SendByteToA(u8 Addr,u8 Data);
extern void Ht1621_SendByteToB(u8 Addr,u8 Data);
extern void Ht1621_Send_4BitToA(u8 Addr,u8 Data);
extern void Ht1621_Send_4BitToB(u8 Addr,u8 Data);
extern void Ht1621WrAllData_A(u8 Addr,u8 *p,u8 cnt);
extern void Ht1621WrAllData_B(u8 Addr,u8 *p,u8 cnt);
extern void Ht1621_Init_A(void);
extern void Ht1621_Init_B(void);
extern void HT1621B_Init(void);



#endif
/*-----------------------------------------------
  项目：鱼缸控制器程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2014.7.1
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef		_DS1302_H_
#define		_DS1302_H_

#include "stm8l15x.h"
#include "stm8l15x_gpio.h"
#include "stdio.h"


//DS1302寄存器宏定义
#define	WRITE_SECOND            0x80		    //秒
#define	WRITE_MINUTE            0x82			//分
#define	WRITE_HOUR              0x84			//时
#define	WRITE_DAY               0x86			//日
#define	WRITE_MONTH             0x88			//月
#define	WRITE_YEAR              0x8C			//年

#define	WRITE_PROTECT           0x8E		    //写保护寄存器
#define	Supply_Power			  		0x90			//充电寄存器

#define   READ_SECOND             0x81
#define   READ_MINUTE             0x83
#define   READ_HOUR               0x85
#define   READ_DAY                0x87
#define   READ_MONTH              0x89
#define   READ_YEAR               0x8D

#define   WRITE_PARITY_RAM0     0xC0
#define   READ_PARITY_RAM0     0xC1

#define   WRITE_PARITY_RAM1     0xC2
#define   READ_PARITY_RAM1     0xC3

#define   WRITE_PARITY_RAM2     0xC4
#define   READ_PARITY_RAM2     0xC5

#define   WRITE_PARITY_RAM3     0xC6
#define   READ_PARITY_RAM3     0xC7

#define	DS_RST_Port			GPIOC
#define	DS_RST_Pin			GPIO_Pin_3
#define 	DS_RST_Low()		(DS_RST_Port->ODR &= (uint8_t)(~(DS_RST_Pin)))
#define 	DS_RST_High()	(DS_RST_Port->ODR |= (uint8_t)DS_RST_Pin)

#define	DS_SCLK_Port		GPIOB
#define	DS_SCLK_Pin			GPIO_Pin_5
#define 	DS_SCLK_Low()		(DS_SCLK_Port->ODR &= (uint8_t)(~(DS_SCLK_Pin)))
#define 	DS_SCLK_High()		(DS_SCLK_Port->ODR |= (uint8_t)DS_SCLK_Pin)

#define	DS_DATA_Port		GPIOB
#define	DS_DATA_Pin			GPIO_Pin_4
#define	DS_DATA_Val			((BitStatus)(DS_DATA_Port->IDR & (uint8_t)DS_DATA_Pin))
#define 	DS_DATA_Low()		(DS_DATA_Port->ODR &= (uint8_t)(~(DS_DATA_Pin)))
#define 	DS_DATA_High()		(DS_DATA_Port->ODR |= (uint8_t)DS_DATA_Pin)

typedef struct
{
    u8 time_cnt;
    u8 now_time[7];
    u8 second_flg:1;
    u8 flash_cnt;
    u8 year;
    u8 month;
    u8 date;
    u8 hour;
    u8 minute;
    u8 second;
}_DS1302_CTRL_DEF_;




extern u8 const init_time[];
extern _DS1302_CTRL_DEF_ ds1302;

extern void Delay_NOP(void);
extern void DS1302_Init_Port(void);
extern void DS1302_Init(void);
extern u8 DS1302_ReadByte(void);
extern void DS1302_WriteByte(u8 dat);
extern void DS_DATA_Input(void);
extern void DS_DATA_Output(void);
extern void DS1302_SetTime(u8 *p);
extern void DS1302_GetTime(u8 *p);
extern void DS1302_WriteData(u8 addr, u8 dat);
extern u8 DS1302_ReadData(u8 addr);
extern void Ds1302_Serv_Handler(void);
extern u8 DS1302_GetRST_Flag(void);
extern void DS1302_SetRST_Flag(void);
extern void Ds1302_Time_Handler(void);










#endif






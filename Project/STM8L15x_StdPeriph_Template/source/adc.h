/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef	_ADC_H_
#define _ADC_H_


#include    "stm8l15x_adc.h"
#include    "stdio.h"
#include	"function.h"

#define SAMP_MAX		10
#define CHARG_TIME	 1500
#define RELEASE_TIME 500

typedef struct
{

    u16 bat1_voltbuff[SAMP_MAX];	//BAT1 VOLTAGE
    u16 bat1_volt;
    u16 bat1_currbuff[SAMP_MAX];	//BAT1 CURRENT
    u16 bat1_curr;
    u16 bat2_voltbuff[SAMP_MAX];	//BAT2 VOLTAGE
    u16 bat2_volt;
    u16 bat2_currbuff[SAMP_MAX];	//BAT2 CURRENT
    u16 bat2_curr;
    u8 bat_lev;
    u8 index;
    u8 init;
    u8 time_cnt;        //测量计时
    u8 step;	// 0: 判断  1： 充电   2：休息
    u16 bat_time;
    u8 charge_flg:1;	//
    u8 full_flg:1;		//充满标志
}_ADC_CTRL_DEF_;

extern _ADC_CTRL_DEF_ adc;

#define BAT1_VOLTAGE_PORT GPIOD
#define BAT1_VOLTAGE_PIN	GPIO_Pin_4
#define BAT1_VOLTAGE_CHANNEL	ADC_Channel_10

#define BAT1_CURRENT_PORT GPIOF
#define BAT1_CURRENT_PIN	GPIO_Pin_0
#define BAT1_CURRENT_CHANNEL	ADC_Channel_24

#define BAT1_CHARGE_PORT	GPIOB
#define BAT1_CHARGE_PIN GPIO_Pin_7	
#define BAT1_CHARGE_ON()	GPIO_ResetBits(BAT1_CHARGE_PORT,BAT1_CHARGE_PIN)
#define BAT1_CHARGE_OFF()	GPIO_SetBits(BAT1_CHARGE_PORT,BAT1_CHARGE_PIN)

#define BAT2_VOLTAGE_PORT GPIOD
#define BAT2_VOLTAGE_PIN	GPIO_Pin_3
#define BAT2_VOLTAGE_CHANNEL	ADC_Channel_19

#define BAT2_CURRENT_PORT GPIOB
#define BAT2_CURRENT_PIN	GPIO_Pin_0
#define BAT2_CURRENT_CHANNEL	ADC_Channel_18

#define BAT2_CHARGE_PORT	GPIOD
#define BAT2_CHARGE_PIN GPIO_Pin_5	
#define BAT2_CHARGE_ON()	GPIO_ResetBits(BAT2_CHARGE_PORT,BAT2_CHARGE_PIN)
#define BAT2_CHARGE_OFF()	GPIO_SetBits(BAT2_CHARGE_PORT,BAT2_CHARGE_PIN)






extern void ADC_Config(void);
extern void ADC_ClearChannel(void);
extern void ADC_Timeticket(void);
extern void ADC_Serv_Handler(void);
extern u16 ADC_Get_Average(u16 *pt, u8 len);





#endif

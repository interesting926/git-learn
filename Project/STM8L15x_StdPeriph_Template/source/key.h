/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/


#ifndef		_KEY_H_
#define		_KEY_H_

#include "stm8l15x.h"
#include	"uart.h"
#include	"main.h"
#include	"function.h"
#include	"timer.h"
#include    "stdio.h"


/*
#define	KEY_1_Port	GPIOA
#define	KEY_2_Port	GPIOA
#define	KEY_3_Port	GPIOA
#define	KEY_4_Port	GPIOA



#define 	KEY_1_Pin		GPIO_Pin_4
#define 	KEY_2_Pin		GPIO_Pin_5
#define 	KEY_3_Pin		GPIO_Pin_6
#define 	KEY_4_Pin		GPIO_Pin_7


#define	Key_1_Val		GPIO_ReadInputDataBit(KEY_1_Port,KEY_1_Pin)
#define	Key_2_Val		GPIO_ReadInputDataBit(KEY_2_Port,KEY_2_Pin)
#define	Key_3_Val		GPIO_ReadInputDataBit(KEY_3_Port,KEY_3_Pin)
#define	Key_4_Val		GPIO_ReadInputDataBit(KEY_4_Port,KEY_4_Pin)*/


//-------------KEY VALUE DEFINE------------------
#define	KEY_VALUE_NONE    		0
#define	KEY_VALUE_RST   		1
#define	KEY_VALUE_DOWN    		2
#define	KEY_VALUE_UP    		3
#define	KEY_VALUE_TEST    		4
#define KEY_VALUE_EXE           5
#define KEY_VALUE_CMP           6



#define KEY_INT_Port GPIOG
#define KEY_int_Pin     GPIO_Pin_5



typedef enum
{
    Init_Step=0,        //初始扫描
    Filter_Step,        //防抖动扫描
    Continue_Step,      //连续按键扫描
    ReFilter_Step,			//释放防抖动扫描
    Wait_Nokey_Step,	//等待无按键
    Release_Step,       //按键释放
    GetValue_Step,
}_SCANKEY_STEP_DEF;


typedef struct
{
	u8 value;
	u8 bk_value;
	u8 step;	//扫描步骤
	u16 contime;	//扫描时间
	u8 b_cont_flg:1;	//连续按键
	
}_SCANKEY_CTRL_DEF;

extern _SCANKEY_CTRL_DEF key;


extern void Key_Init_Port(void);
extern void Key_Init_Param(void);
extern 	 u8 Key_Read_Port(void);
extern void Key_Scan_Handler(void);
extern void Key_Print_Value(u8 keyval , u8 contkey);
extern void Key_Function(void);
extern void Key_Time_Handler(void);




#endif


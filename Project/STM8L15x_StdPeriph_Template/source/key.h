/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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
    Init_Step=0,        //��ʼɨ��
    Filter_Step,        //������ɨ��
    Continue_Step,      //��������ɨ��
    ReFilter_Step,			//�ͷŷ�����ɨ��
    Wait_Nokey_Step,	//�ȴ��ް���
    Release_Step,       //�����ͷ�
    GetValue_Step,
}_SCANKEY_STEP_DEF;


typedef struct
{
	u8 value;
	u8 bk_value;
	u8 step;	//ɨ�貽��
	u16 contime;	//ɨ��ʱ��
	u8 b_cont_flg:1;	//��������
	
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


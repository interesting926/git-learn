/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/

#ifndef _KILL_H_
#define _KILL_H_


#include "stm8l15x.h"
#include "adc.h"



#define KILL_Mode 	0

#define KILL_Run_MaxTime ((u16)30*24*6)	//������ת30���ʱ��

#define KILL_PARITY_A		0x77
#define KILL_PARITY_B		0x88

typedef struct
{
	u32 run_time;//ÿ����Ϊ��λ
	u16 micros;	//�Ʒ���
	u8 update_flg:1;	//���±�־

}_KILL_STRUCT_DEF;

extern _KILL_STRUCT_DEF kill;


extern void Kill_Init(void);
extern void Kill_Update_Param(void);
extern void Kill_Check_Time(void);
extern void Kill_SysTime_Tick(void);












#endif

/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef _KILL_H_
#define _KILL_H_


#include "stm8l15x.h"
#include "adc.h"



#define KILL_Mode 	0

#define KILL_Run_MaxTime ((u16)30*24*6)	//连续运转30天的时间

#define KILL_PARITY_A		0x77
#define KILL_PARITY_B		0x88

typedef struct
{
	u32 run_time;//每分钟为单位
	u16 micros;	//计分钟
	u8 update_flg:1;	//更新标志

}_KILL_STRUCT_DEF;

extern _KILL_STRUCT_DEF kill;


extern void Kill_Init(void);
extern void Kill_Update_Param(void);
extern void Kill_Check_Time(void);
extern void Kill_SysTime_Tick(void);












#endif

/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef _MAIN_H_
#define _MAIN_H_

#define Software_Ver "V1.01"


#define	LoByte(w)	((u8)(w))
#define	HiByte(w)	((u8)(((u16)(w) >> 8) & 0xFF))

#define	Abs(a,b)		(((a) > (b)) ? (a-b) : (b-a))
#define	Max(a,b)		(((a) > (b)) ? (a) : (b))
#define	Min(a,b)		(((a) < (b)) ? (a) : (b))


#define Disable()	disableInterrupts();
#define Enable()	(if(INT_FLG==1) enableInterrupts())


extern char const Product_Info[];


void SysClock_Init(void);
void Hard_Init(void);
void Exti_Init(void);
void Soft_Init(void);

/*
IAR优化选项 #pragma optimize 指令使用
 
要注意的是：设置优化等级要小于初始options默认设置的优化等级
 
#pragma optimize= none  //one of none, low,medium, high, size, or speed放在被优化函数前
#pragma optimize 指令格式：


 #pragma optimize=token1 token2  token3


where token isone or more of the following:

token1、
speed Optimizes forspeed。
size   Optimizes for size。


token2  、

2|3|6|9   Specifies level of optimization。


token3、
no_cse   Turns off common sub-expression elimination。
no_inline  Turns offfunction inlining。
no_unroll   Turns offloop unrolling。
no_code_motion   Turns off code motion.




Example
#pragma optimize=speed  9 
int small_and_used_often()
{
...
}
#pragma optimize= size 9
int big_and_seldom_used()
{
...
}
======================================================================================
使用好处：
1、 可以使用这个方便优化或者不优化部分程序。
2、 可用于查找优化等级过高导致的程序错误，查找优化错误的函数。
*/






#endif


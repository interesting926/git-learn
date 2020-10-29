/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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
IAR�Ż�ѡ�� #pragma optimize ָ��ʹ��
 
Ҫע����ǣ������Ż��ȼ�ҪС�ڳ�ʼoptionsĬ�����õ��Ż��ȼ�
 
#pragma optimize= none  //one of none, low,medium, high, size, or speed���ڱ��Ż�����ǰ
#pragma optimize ָ���ʽ��


 #pragma optimize=token1 token2  token3


where token isone or more of the following:

token1��
speed Optimizes forspeed��
size   Optimizes for size��


token2  ��

2|3|6|9   Specifies level of optimization��


token3��
no_cse   Turns off common sub-expression elimination��
no_inline  Turns offfunction inlining��
no_unroll   Turns offloop unrolling��
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
ʹ�úô���
1�� ����ʹ����������Ż����߲��Ż����ֳ���
2�� �����ڲ����Ż��ȼ����ߵ��µĳ�����󣬲����Ż�����ĺ�����
*/






#endif


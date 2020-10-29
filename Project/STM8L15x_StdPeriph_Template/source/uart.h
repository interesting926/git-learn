/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/

#ifndef		_UART_H_
#define		_UART_H_

#include	"main.h"
#include	"function.h"
#include	"stm8l15x_usart.h"
#include	"stdio.h"


#define c_dbg_print     printf

//����ʹ��
#define USING_UART1
#define USING_UART2
#define USING_UART3
#define USING_DUART	//ģ�⴮��


//��Ϣ��ӡ���ĸ�����
//#define UART1_DBG_PRINT
//#define UART2_DBG_PRINT
//#define UART3_DBG_PRINT
#define DUART_DBG_PRINT

#define RS485_DR_PORT	GPIOE
#define RS485_DR_PIN	GPIO_Pin_5
#define RS485_REV() GPIO_ResetBits(RS485_DR_PORT,RS485_DR_PIN)
#define RS485_SEND() GPIO_SetBits(RS485_DR_PORT,RS485_DR_PIN)


//���ڲ������趨
#define UART1_BAUDRATE	9600
#define UART2_BAUDRATE	4800
#define UART3_BAUDRATE	9600



//���ô������������ֽ����ʱ��
#define UART1_BYTE_MAX_TIME	2	//���ٲ�С��2
#define UART2_BYTE_MAX_TIME	2
#define UART3_BYTE_MAX_TIME	2


//���ý��ջ�����󳤶�
#define UART1_MAX_RECV_LEN	110
#define UART1_MAX_SEND_LEN	110
#define UART2_MAX_RECV_LEN	32
#define UART2_MAX_SEND_LEN	32
#define UART3_MAX_RECV_LEN	32
#define UART3_MAX_SEND_LEN	32





typedef struct
{
	u8 rev_flg:1;	//�������ݵı�־
	u8 length;		//���յ����ݵĳ���
	u8 time_cnt;	//��ʱ����
	u8 rbuf[UART1_MAX_RECV_LEN];
	u8 sbuf[UART1_MAX_SEND_LEN];
}_UART1_CTRL_DEF;

typedef struct
{
	u8 rev_flg:1;	//�������ݵı�־
	u8 length;		//���յ����ݵĳ���
	u8 time_cnt;	//��ʱ����
	u8 rbuf[UART2_MAX_RECV_LEN];
	u8 sbuf[UART2_MAX_SEND_LEN];
}_UART2_CTRL_DEF;

typedef struct
{
	u8 rev_flg:1;	//�������ݵı�־
	u8 length;		//���յ����ݵĳ���
	u8 time_cnt;	//��ʱ����
	u8 rbuf[UART3_MAX_RECV_LEN];
	u8 sbuf[UART3_MAX_SEND_LEN];
}_UART3_CTRL_DEF;



extern u8 debug_flg;
extern _UART1_CTRL_DEF uart1;
extern _UART2_CTRL_DEF uart2;
extern _UART3_CTRL_DEF uart3;




extern void Uart_Init(void);
extern void Uart_Timeticket(void);
extern void Print_System_Info(void);

#ifdef	USING_UART1
extern void Uart1_Init(void);
extern void Uart1_SendByte(u8 c);
extern void Uart1_Send_N_bytes(u8 *buf,u8 len);
extern void Uart1_Send_Hex(u8 Byte_HEX);
extern void Uart1_Send_Dec(u8 Byte_Dec);
extern void Uart1_Send_IntDec(u16 Int_dec);
extern void Uart1_dbg_print(char *str);
extern void Uart1_Timeticket(void);
extern void Uart1_Receive_Data(u8 rdata);

#endif
#ifdef	USING_UART2
extern void Uart2_Init(void);
extern void Uart2_SendByte(u8 c);
extern void Uart2_Send_N_bytes(u8 *buf,u8 len);
extern void Uart2_Send_Hex(u8 Byte_HEX);
extern void Uart2_Send_Dec(u8 Byte_Dec);
extern void Uart2_Send_IntDec(u16 Int_dec);
extern void Uart2_dbg_print(char *str);
extern void Uart2_Timeticket(void);
extern void Uart2_Receive_Data(u8 rdata);

#endif
#ifdef	USING_UART3
extern void Uart3_Init(void);
extern void Uart3_SendByte(u8 c);
extern void Uart3_Send_N_bytes(u8 *buf,u8 len);
extern void Uart3_Send_Hex(u8 Byte_HEX);
extern void Uart3_Send_Dec(u8 Byte_Dec);
extern void Uart3_Send_IntDec(u16 Int_dec);
extern void Uart3_dbg_print(char *str);
extern void Uart3_Timeticket(void);
extern void Uart3_Receive_Data(u8 rdata);

#endif










#endif



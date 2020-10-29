/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_



#include "stm8l15x.h"

#define PowerBike 	0			//������
#define KeepFitBike 1			//����

#define Device_Unknow 0xFF	//δ֪�豸

#define     Device_ID   0xAF    //�ķγ�
//#define	Device_ID		0xB0	//����
//#define	Device_ID	0xB3	//��ʽ��ҡ��
//#define	Device_ID		0xB1	//�ܲ���
//#define	Device_ID	0xB2	//������
//#define	Device_ID	0x11		//���ƾ�ѵ����/����
//#define	Device_ID	0x12		//���ػ���
//#define	Device_ID	0x13		//������
//#define	Device_ID	0x14		//���
//#define	Device_ID	0x21		//Ť��
//#define	Device_ID	0x22		//��������
//#define	Device_ID	0x31		//�Ŷ�ͷ��



#if Device_ID == 0xB0		//����
	#define Machine_Type			KeepFitBike
#elif  Device_ID == 0xAF
    #define Machine_Type			KeepFitBike
#elif Device_ID == 0xB3		//��ʽ��ҡ��
	#define Machine_Type			KeepFitBike
#elif Device_ID == 0xA1		//˫�˾�������
    #define Machine_Type			KeepFitBike
#else						//����������
	#define Machine_Type			PowerBike
#endif


#define DB_POWER_PORT	GPIOE
#define DB_POWER_PIN		GPIO_Pin_2
#define DB_POWER_LOW() GPIO_ResetBits(DB_POWER_PORT,DB_POWER_PIN)
#define DB_POWER_HIG() GPIO_SetBits(DB_POWER_PORT,DB_POWER_PIN)


#define	LED_ON		0
#define	LED_OFF		1

//#define BLE_WAKUP_PORT	GPIOC
//#define BLE_WAKUP_PIN		GPIO_Pin_5
//#define BLE_WAKUP_LOW() GPIO_ResetBits(BLE_WAKUP_PORT,BLE_WAKUP_PIN)
//#define BLE_WAKUP_HIG() GPIO_SetBits(BLE_WAKUP_PORT,BLE_WAKUP_PIN)

#define BLE_CONNECT_PORT	GPIOD
#define BLE_CONNECT_PIN		GPIO_Pin_7
#define BLE_CONNECT_VAL()		GPIO_ReadInputDataBit(BLE_CONNECT_PORT,BLE_CONNECT_PIN)

//#define BLE_INT_PORT	GPIOC
//#define BLE_INT_PIN		GPIO_Pin_7
//#define BLE_INT_VAL()		GPIO_ReadInputDataBit(BLE_INT_PORT,BLE_INT_PIN)

#define BLE_RST_PORT	GPIOC
#define BLE_RST_PIN		GPIO_Pin_6
#define BLE_RST_LOW() GPIO_ResetBits(BLE_RST_PORT,BLE_RST_PIN)
#define BLE_RST_HIG() GPIO_SetBits(BLE_RST_PORT,BLE_RST_PIN)

#define BLE_TXD_PORT	GPIOE
#define BLE_TXD_PIN		GPIO_Pin_6

#define BLE_RXD_PORT	GPIOE
#define BLE_RXD_PIN		GPIO_Pin_7

#define	HR_Port	GPIOE               //HR
#define	HR_Pin	GPIO_Pin_0

#define	RPM_Port	GPIOD               //RPM
#define	RPM_Pin	GPIO_Pin_2

#define	RPM2_Port	GPIOD               //RPM
#define	RPM2_Pin	GPIO_Pin_1


#define PERIMETER	2500	//�ܳ��� mm

#define	Led1_Port	GPIOF               //LED
#define	Led1_Pin	GPIO_Pin_7
#define	Set_Led1_Off()	GPIO_SetBits(Led1_Port,Led1_Pin)
#define	Set_Led1_On()		GPIO_ResetBits(Led1_Port,Led1_Pin)

#define	Beep_Port	GPIOG
#define	Beep_Pin	GPIO_Pin_4
#define	Set_Beep_OFF()		GPIO_SetBits(Beep_Port,Beep_Pin)
#define	Set_Beep_ON()		GPIO_ResetBits(Beep_Port,Beep_Pin)

#define TIMER2_PER_TIME		2	// ms
#define	RPM_DATA_MAX	    8
#define RPM_COUNT_MIN   100     //����ת����С����Чʱ��
#define RPM_COUNT_MAX   2500     //����ת����С����Чʱ��
#define RPM_RATE_Max    300    //���ת��

#define	HR_DATA_MAX	    5       //���ݻ������
#define HR_COUNT_MIN   350     //����ת����С����Чʱ��
#define HR_COUNT_MAX   2500     //����ת����С����Чʱ��
#define HR_RATE_Max    200    //���ת��


#define DR_HEAD_BYTE 0x01
#define DR_FUNC_BYTE 0xC0
//--------------------------
#define DR_PWM_MODE	0
#define DR_AD_MODE	(1<<6)
#define DR_LEV_MODE (2<<6)
//--------------------------
#define DR_LEV_MAX	8
#define DR_SEL_LEV (0<<7)
#define DR_SEL_WAT (1<<7)
#define DR_PER_PULSE 0x05


#define PWM_LEV_MAX	99

//#define TIMEOUT_MAX	60000	// 10����
#define TIMEOUT_MAX	15000	// 1����
//#define TIMEOUT_MAX	6000	// 1����
//#define TIMEOUT_MAX	1000	// 10��
//#define TIMEOUT_MAX	500	// 5��


typedef struct
{
	u8 int_flg:1;	// 2ms
	u8 micros;	// 2ms
	u8 second_flg;	// 
	u8 second;	//s
	u8 minute;	//minute
	u16  total_time;		//���ڲ��Կ�ʼ��ʱ,����Ϊ��λ
}_TIME_CTRL_DEF_;

typedef struct
{
	u8 nbits;        //��������ƽ��ֵ�Ĵ���
  u16 count;			//������ʱ,ÿ��hr�ж�֮���ж��ٸ� 1ms ��ʱ�ж�
  u16 cnt_bak;
	u16 array[HR_DATA_MAX];	//�洢ÿ��hr�жϵ�ʱ����
	u16 rate;			//hrת������
	u8 int_flg:1;    //�жϱ�־
	u8 init_flg:1;  //��ʼ����־
	u8 display_flg:1;		//��ʾ��־
	u8 time;						//��ʾ��ʱ��
}_HR_STRUCT_DEF;

typedef struct
{
	//------��������Ӳ����������ʱ��---------------------
	u8 year;     //��
	u8 month;    //��
	u8 days;     //��
	u8 hour;		//Сʱ
	u8 minute;	//����
	u8 second;	//��
	u8 microsec; //50ms
	u8 flash:1;  //��ӡʱ����Ϣ�ı�־λ
    //--------------------------------------------------
}_SYSTEM_TIME_DEF_;

typedef	struct
{
	//-------------------------------
	u8 start:1;	//��ʼ���Ա�־λ
	u8 resume:1;	//��ͣ,����
	u8 time_count;	//��ʱ,���ڳ��޶�������
	u8 time_out:1;	//ϵͳ��ʱ�޶���
	u8 send_cnt;		//�������ݼ�ʱ,ÿ��1s�������ݵ�ƽ�����
	u8 send_cnt2;		//�ڶ������ݶ�ʱ
	u8 send_cnt2_flg;	//
	u8 loader:1;			//
	//-------------------------------
	char level;			//�����ȼ�
	u16 watt;			//����W
	u32 calorie;		//��·��ƽ��ֵ
	u32 cal_sum;		//��·������
	u8 oxygen;		//����Ũ��
	//-------------------------------
}_SYSTEM_TEST_DEF_;

typedef struct
{
	u8 sex:1;	//�Ա�
	u8 age;		//���
	u8 height;	//���
	u8 weight;	//����
	u16 BMI_Val;		//BMI
	u16 FAT_Val;		//FAT

}_USER_PARAM_DEF_;


//30s
#define Timeout_Max 30000   

typedef struct
{
    u8 nbits;        //��������ƽ��ֵ�Ĵ���
    u16 count;			//������ʱ,ÿ��hr�ж�֮���ж��ٸ� 1ms ��ʱ�ж�
    u16 cnt_bak;
    u16 array[RPM_DATA_MAX];	//�洢ÿ��hr�жϵ�ʱ����
    u16 rate;			//rpm����(ת/����)
    u16 speed;		//�ٶ� (KM/H)*10  ���͹�ȥ��ʮ����
    u16 distance;		//����,
    u16 cycle;			//Ȧ��
    u32 total_cnt;	//�ܴ���
    u32 Back_cnts;	//����ֵ
    u32 total_miles;	//�ܳ���
    u8 int_flg:1;    //�жϱ�־
    u8 send_flg:1;	//�������ݵı�־λ
    u8 init_flg:1;
    u8 en_count:1;	//�Ƿ������������
    u8 second_flg:1;	//ÿһ����
    u8 cal_cnt;			//������ÿ������һ��,��ף���������ҡ����ÿ�ζ���
    u16 timeOut;
}_RPM_TEST_CTRL_;		//RPM���Կ��Ʋ���

typedef struct
{
	u8 b_enable:1;     //�Ƿ�������ʾ
	u8 blink:1;	//�Ƿ���Ҫ��˸
	u8 blink_val:1;    //��ǰ��˸��״̬
	u8 blink_cnt;	//��˸�Ĵ���
	u8 blink_time;	//��˸��ʱ��
	u16 update_time;		// �Թ̶���Ƶ�ʽ�����ʾ

	u8 mode;			//��ʾ��ģʽ
	u16 sw_time;		//��˸ʱ�����
	u16 swtime_out;	//��ʱ�Զ��л�Ϊ��˸״̬
	u8 buff[6];
}_DISPLAY_CTRL_DEF_;

typedef struct
{
	u8 time;
}BEEP_CTRL_DEF;

typedef struct
{
	u8 rst_time;
	u8 state:1;	//״̬
}BLE_CTRL_DEF;

typedef struct
{
	u8 time;
}LED_CTRL_DEF;

typedef struct
{
	u16 H_Voltage;	//�����ѹ
	u16 R_Current;	//����������
	u16 R_PWMAD;			//����ADֵ
	u8 loader;				//�¿ص�loader����
}BATTERY_CTRL_DEF;

typedef struct
{
	u16 time_cnt;
	u8 flag:1;



}POWER_CTRL_DEF;


typedef struct
{
	u8 bit0:1;
	u8 bit1:1;
	u8 bit2:1;
	u8 bit3:1;
	u8 bit4:1;
	u8 bit5:1;
	u8 bit6:1;
	u8 bit7:1;
}_UNION_8_BIT;


typedef union
{
	u8 value;
	_UNION_8_BIT bits;
}_UNION_8_TYPE;


typedef union
{
	u32 u32_val;
	u8 u8_val[4];
}U32_STRUCT_DEF;










typedef enum
{
    INIT_STEP=0,
    SELECT_MODE_STEP,
    SPORTING_STEP,
    REPORT_STEP,
    DISPLAY_STEP,
    ERROR_STEP
}FACE_STEP;


typedef enum
{
    MODE_TRAIN=0,
    MODE_TEST
}FACE_SPORT_MODE;

//���չʾ��ʱ����30S
#define RESOULT_DISP_TIME 3000
//1000ms����ط�����
#define reSendTime 200
#define RESEND_COUNT 3
#define ERR_DISPLAY_TIME    1000
#define SPORTING_TIME 5900     //���Թ��̳���ʱ��


typedef struct 
{
    u8 qrLength;
    u8 QRCODE[100];
}QRCODE_STRUCT;

typedef struct
{
    u16 date;
    u8 score;
    u8 evalue;
    u16 ReOxygen; 
    u16 MaxOxygen;
}RESOULT_STRUCT;

//Ĭ�ϵĳ�ʼ��������60KG
#define DEFAULT_INPUT_WEIGHT  60
//�������ʱ����120S �����Զ��˳�
#define INPUT_TIME  60
//����ID�ĳ���
#define FACE_ID_LENGTH  32

typedef struct
{
    FACE_STEP step;
    u8 detail;
    FACE_SPORT_MODE mode;
	u8 start;
    u8 faceId[FACE_ID_LENGTH];          //����ID
    u8 facePower[3];        //�������õĴ�С
    u16 timeDelay;
    u16 resDispTime;
    QRCODE_STRUCT qrcode;
    RESOULT_STRUCT res;
    u8 firstHeart;
    u8 secondHeart;
    //u8 testCount;
    u8 inputTime;
    u16 timeRemain;        //����ʱ
    u8 inputWeightFlag;       //��������û��������Ϣ����Ҫ�Լ�����
    u8 inputWeight;     //�û��Լ����������
    u8 inputSexFlag;    //�����Ա���Ϣ   
    u8 inputSex;        //�����Ա�   0  �� 1 Ů
    u8 noUserFlag;          //��������û������û��ķ���,��ʾ�û���ȥ���

    u8 hand_flag;
    u8 start_flag;
    u8 power_flag;
    u8 date_flag;
    u8 timeOut_flag;
    u8 status_flag;
    u8 setQR_flag;
    u8 cleanQR_flag;
    u8 err_count;       //���������û�յ��������������ݵĴ���
    u8 error;           //�˶�����
}FACE_SPORT;

extern FACE_SPORT face_sport;



typedef struct 
{
    u8 dataChange;  //����LCDһֱ�ظ�ˢ��
    u8 refresh;
    u8 step;        //lcd��ʾ����
    u16 DispTime;

} LCD_STRUCT;

extern LCD_STRUCT lcd;


extern U32_STRUCT_DEF u32_data;

extern _UNION_8_TYPE LED_CTRL;
extern _DISPLAY_CTRL_DEF_ display;		//��ʾ����
extern _SYSTEM_TEST_DEF_ sport;		//�˶�����
extern _TIME_CTRL_DEF_ timer;
extern _RPM_TEST_CTRL_ rpm;
extern _HR_STRUCT_DEF hr;
extern BEEP_CTRL_DEF beep;
extern BLE_CTRL_DEF ble;
extern LED_CTRL_DEF led;
extern BATTERY_CTRL_DEF bat;
extern POWER_CTRL_DEF power;

extern u16 ModbusCRC(u8 * pData, u8 len);
extern u16 Convert_Wat_Data(u16 rpms,u8 lev);
extern void Driver_Ctrl_Handler(void);

extern void Beep_Ring(u8 time);
extern void BLE_Reset(u8 time);
extern void LED_Display(u8 time);
extern void HR_Display(u8 time);

extern void Uart_BLE_Serv_Handler(void);
extern void Flash_Display_RAM(void);
extern u8 Get_Buffer_Checksum(u8 *buff,u8 len);
extern void Display_Timeticket(void);
extern void Function(void);
extern void System_Timeticket(void);

extern void HR_INT_Init(void);
extern void HR_INT_Routine(void);
extern void HR_TimeTicket(void);
extern void HR_Handler(void);
extern void HR_GPIO_Sleep(void);


extern void RPM_INT_Init(void);
extern void RPM_INT_Routine(void);
extern void RPM_TimeTicket(void);
extern void RPM_Handler(void);


extern void Watt_Lev_Print(void);
extern void Ultra_Power_Init(void);
extern void Standby_Serv_Handler(void);






extern void lcd_Init(void);
void face_sport_handler(void);
void Uart_Face_Serv_Handler(void);
void Step_Display(void);
void face_sport_timer_handler(void);
void clean_face_sport(void);
void face_sport_test(void);




void test(void);



#endif

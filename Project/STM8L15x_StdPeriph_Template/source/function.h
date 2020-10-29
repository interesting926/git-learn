/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef _FUNCTION_H_
#define _FUNCTION_H_



#include "stm8l15x.h"

#define PowerBike 	0			//力量型
#define KeepFitBike 1			//健身车

#define Device_Unknow 0xFF	//未知设备

#define     Device_ID   0xAF    //心肺车
//#define	Device_ID		0xB0	//健身车
//#define	Device_ID	0xB3	//立式手摇车
//#define	Device_ID		0xB1	//跑步机
//#define	Device_ID	0xB2	//划船器
//#define	Device_ID	0x11		//高推举训练器/高拉
//#define	Device_ID	0x12		//推胸划船
//#define	Device_ID	0x13		//腹背肌
//#define	Device_ID	0x14		//深蹲
//#define	Device_ID	0x21		//扭腰
//#define	Device_ID	0x22		//踢腿曲腿
//#define	Device_ID	0x31		//肱二头肌



#if Device_ID == 0xB0		//健身车
	#define Machine_Type			KeepFitBike
#elif  Device_ID == 0xAF
    #define Machine_Type			KeepFitBike
#elif Device_ID == 0xB3		//立式手摇车
	#define Machine_Type			KeepFitBike
#elif Device_ID == 0xA1		//双人竞赛健身车
    #define Machine_Type			KeepFitBike
#else						//其它力量型
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


#define PERIMETER	2500	//周长： mm

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
#define RPM_COUNT_MIN   100     //计算转速最小的有效时间
#define RPM_COUNT_MAX   2500     //计算转速最小的有效时间
#define RPM_RATE_Max    300    //最大转速

#define	HR_DATA_MAX	    5       //数据缓冲深度
#define HR_COUNT_MIN   350     //计算转速最小的有效时间
#define HR_COUNT_MAX   2500     //计算转速最小的有效时间
#define HR_RATE_Max    200    //最大转速


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

//#define TIMEOUT_MAX	60000	// 10分钟
#define TIMEOUT_MAX	15000	// 1分钟
//#define TIMEOUT_MAX	6000	// 1分钟
//#define TIMEOUT_MAX	1000	// 10秒
//#define TIMEOUT_MAX	500	// 5秒


typedef struct
{
	u8 int_flg:1;	// 2ms
	u8 micros;	// 2ms
	u8 second_flg;	// 
	u8 second;	//s
	u8 minute;	//minute
	u16  total_time;		//用于测试开始计时,以秒为单位
}_TIME_CTRL_DEF_;

typedef struct
{
	u8 nbits;        //用来计算平均值的次数
  u16 count;			//用来计时,每次hr中断之间有多少个 1ms 定时中断
  u16 cnt_bak;
	u16 array[HR_DATA_MAX];	//存储每次hr中断的时间间隔
	u16 rate;			//hr转速速率
	u8 int_flg:1;    //中断标志
	u8 init_flg:1;  //初始化标志
	u8 display_flg:1;		//显示标志
	u8 time;						//显示的时间
}_HR_STRUCT_DEF;

typedef struct
{
	//------用来计算硬件的总运行时间---------------------
	u8 year;     //年
	u8 month;    //月
	u8 days;     //日
	u8 hour;		//小时
	u8 minute;	//分钟
	u8 second;	//秒
	u8 microsec; //50ms
	u8 flash:1;  //打印时长消息的标志位
    //--------------------------------------------------
}_SYSTEM_TIME_DEF_;

typedef	struct
{
	//-------------------------------
	u8 start:1;	//开始测试标志位
	u8 resume:1;	//暂停,继续
	u8 time_count;	//计时,用于超无动作计数
	u8 time_out:1;	//系统超时无动作
	u8 send_cnt;		//发送数据计时,每隔1s发送数据到平板电脑
	u8 send_cnt2;		//第二包数据定时
	u8 send_cnt2_flg;	//
	u8 loader:1;			//
	//-------------------------------
	char level;			//阻力等级
	u16 watt;			//功率W
	u32 calorie;		//卡路里平均值
	u32 cal_sum;		//卡路里计算和
	u8 oxygen;		//制氧浓度
	//-------------------------------
}_SYSTEM_TEST_DEF_;

typedef struct
{
	u8 sex:1;	//性别
	u8 age;		//年纪
	u8 height;	//身高
	u8 weight;	//体重
	u16 BMI_Val;		//BMI
	u16 FAT_Val;		//FAT

}_USER_PARAM_DEF_;


//30s
#define Timeout_Max 30000   

typedef struct
{
    u8 nbits;        //用来计算平均值的次数
    u16 count;			//用来计时,每次hr中断之间有多少个 1ms 定时中断
    u16 cnt_bak;
    u16 array[RPM_DATA_MAX];	//存储每次hr中断的时间间隔
    u16 rate;			//rpm速率(转/分钟)
    u16 speed;		//速度 (KM/H)*10  发送过去是十倍速
    u16 distance;		//距离,
    u16 cycle;			//圈数
    u32 total_cnt;	//总次数
    u32 Back_cnts;	//备份值
    u32 total_miles;	//总长度
    u8 int_flg:1;    //中断标志
    u8 send_flg:1;	//发送数据的标志位
    u8 init_flg:1;
    u8 en_count:1;	//是否允许继续计数
    u8 second_flg:1;	//每一秒钟
    u8 cal_cnt;			//力量型每两次算一次,深蹲，健身车，手摇车则每次都算
    u16 timeOut;
}_RPM_TEST_CTRL_;		//RPM测试控制参数

typedef struct
{
	u8 b_enable:1;     //是否允许显示
	u8 blink:1;	//是否需要闪烁
	u8 blink_val:1;    //当前闪烁的状态
	u8 blink_cnt;	//闪烁的次数
	u8 blink_time;	//闪烁的时延
	u16 update_time;		// 以固定的频率进行显示

	u8 mode;			//显示的模式
	u16 sw_time;		//闪烁时间控制
	u16 swtime_out;	//超时自动切换为闪烁状态
	u8 buff[6];
}_DISPLAY_CTRL_DEF_;

typedef struct
{
	u8 time;
}BEEP_CTRL_DEF;

typedef struct
{
	u8 rst_time;
	u8 state:1;	//状态
}BLE_CTRL_DEF;

typedef struct
{
	u8 time;
}LED_CTRL_DEF;

typedef struct
{
	u16 H_Voltage;	//发电电压
	u16 R_Current;	//磁阻器电流
	u16 R_PWMAD;			//阻力AD值
	u8 loader;				//下控的loader开关
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

//结果展示的时间是30S
#define RESOULT_DISP_TIME 3000
//1000ms后会重发数据
#define reSendTime 200
#define RESEND_COUNT 3
#define ERR_DISPLAY_TIME    1000
#define SPORTING_TIME 5900     //测试过程持续时间


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

//默认的初始化体重是60KG
#define DEFAULT_INPUT_WEIGHT  60
//输入最大时间是120S 否则自动退出
#define INPUT_TIME  60
//人脸ID的长度
#define FACE_ID_LENGTH  32

typedef struct
{
    FACE_STEP step;
    u8 detail;
    FACE_SPORT_MODE mode;
	u8 start;
    u8 faceId[FACE_ID_LENGTH];          //人脸ID
    u8 facePower[3];        //阻力设置的大小
    u16 timeDelay;
    u16 resDispTime;
    QRCODE_STRUCT qrcode;
    RESOULT_STRUCT res;
    u8 firstHeart;
    u8 secondHeart;
    //u8 testCount;
    u8 inputTime;
    u16 timeRemain;        //倒计时
    u8 inputWeightFlag;       //服务器端没有阻力信息，需要自己输入
    u8 inputWeight;     //用户自己输入的体重
    u8 inputSexFlag;    //输入性别信息   
    u8 inputSex;        //输入性别   0  男 1 女
    u8 noUserFlag;          //服务器中没有这个用户的方案,提示用户先去体测

    u8 hand_flag;
    u8 start_flag;
    u8 power_flag;
    u8 date_flag;
    u8 timeOut_flag;
    u8 status_flag;
    u8 setQR_flag;
    u8 cleanQR_flag;
    u8 err_count;       //发送请求后没收到服务器返回数据的次数
    u8 error;           //运动错误
}FACE_SPORT;

extern FACE_SPORT face_sport;



typedef struct 
{
    u8 dataChange;  //避免LCD一直重复刷新
    u8 refresh;
    u8 step;        //lcd显示步骤
    u16 DispTime;

} LCD_STRUCT;

extern LCD_STRUCT lcd;


extern U32_STRUCT_DEF u32_data;

extern _UNION_8_TYPE LED_CTRL;
extern _DISPLAY_CTRL_DEF_ display;		//显示控制
extern _SYSTEM_TEST_DEF_ sport;		//运动控制
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

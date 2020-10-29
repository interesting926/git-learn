/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#include "function.h"
#include "adc.h"
#include	"timer.h"
#include	"ds1302.h"
#include "JLX256160G.h"
#include "SC09A.h"

//******************************************************************************
_SYSTEM_TEST_DEF_ sport;		//运动控制
_RPM_TEST_CTRL_ rpm;				//rpm转速测试
_UNION_8_TYPE LED;
_TIME_CTRL_DEF_ timer;
_HR_STRUCT_DEF hr;
U32_STRUCT_DEF u32_data;
BEEP_CTRL_DEF beep;
BLE_CTRL_DEF ble;
LED_CTRL_DEF led;
BATTERY_CTRL_DEF bat;
POWER_CTRL_DEF power;
FACE_SPORT face_sport;
LCD_STRUCT lcd;


//******************************************************************************

//const u16 PWM_LEV_ARRY[]={0,0,50,150,250,350,450,550,700,800,1020};
const u8 face_res_evaluate[10][20]={
    {"不及格  "},
    {"不及格  "},
    {"不及格  "},
    {"不及格  "},
    {"不及格  "},
    {"及格    "},
    {"一般    "},
    {"良好    "},
    {"优秀    "},
    {"非常优秀"}          
};





//修改成100档位
const u16 PWM_LEV_ARRY[]=
{
    0,10,20,30,40,50,60,70,80,90,
    100,110,120,130,140,150,160,170,180,190,
    200,210,220,230,240,250,260,270,280,290,
    300,310,320,330,340,350,360,370,380,390,
    400,410,420,430,440,450,460,470,480,490,
    500,510,520,530,540,550,560,570,580,590,
    600,610,620,630,640,650,660,670,680,690,
    700,710,720,730,740,750,760,770,780,790,
    800,810,820,830,840,850,860,870,880,890,
    900,910,920,930,940,950,960,970,980,990,
    1000,
};




const u8 Corrdard[]={30,40,60,80,100,120,150,180};

const u16 Watt_Tbl[][8]=
{							//功率表
0, 		0, 		0, 		0, 		0, 		0, 		0, 		0,
13,		18,		27,		36,		45,		54,		60,		78,
27,		36,		54,		72,		89,		98,		124,	144,
47,		63,		94,		126,	159,	179,	216,	236,
72,		96,		143,	180,	213,	233,	263,	280,
102,	136,	203,	225,	248,	268,	311,	331,
133,	178,	261,	267,	284,	304,	340,	370,
157,	202,	268,	281,	301,	321,	370,	390,
172,	217,	300,	306,	329,	349,	371,	401,
192,	232,	332,	331,	357,	377,	390,	410,
212,	247,	364,	356,	386,	399,	420,	430,


};
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 const gabyCRCHi[] =
{
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
    0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,
    0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,
    0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,
    0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
    0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,
    0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,
    0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
    0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
    0x80,0x41,0x00,0xc1,0x81,0x40
};
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 const gabyCRCLo[] =
{
    0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,
    0x07,0xc7,0x05,0xc5,0xc4,0x04,0xcc,0x0c,0x0d,0xcd,
    0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,
    0x08,0xc8,0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,
    0x1e,0xde,0xdf,0x1f,0xdd,0x1d,0x1c,0xdc,0x14,0xd4,
    0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,
    0x11,0xd1,0xd0,0x10,0xf0,0x30,0x31,0xf1,0x33,0xf3,
    0xf2,0x32,0x36,0xf6,0xf7,0x37,0xf5,0x35,0x34,0xf4,
    0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,
    0x3b,0xfb,0x39,0xf9,0xf8,0x38,0x28,0xe8,0xe9,0x29,
    0xeb,0x2b,0x2a,0xea,0xee,0x2e,0x2f,0xef,0x2d,0xed,
    0xec,0x2c,0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,
    0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,0xa0,0x60,
    0x61,0xa1,0x63,0xa3,0xa2,0x62,0x66,0xa6,0xa7,0x67,
    0xa5,0x65,0x64,0xa4,0x6c,0xac,0xad,0x6d,0xaf,0x6f,
    0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,
    0x78,0xb8,0xb9,0x79,0xbb,0x7b,0x7a,0xba,0xbe,0x7e,
    0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,0xb4,0x74,0x75,0xb5,
    0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,
    0x70,0xb0,0x50,0x90,0x91,0x51,0x93,0x53,0x52,0x92,
    0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9c,0x5c,
    0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,
    0x99,0x59,0x58,0x98,0x88,0x48,0x49,0x89,0x4b,0x8b,
    0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
    0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,
    0x43,0x83,0x41,0x81,0x80,0x40
};
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
u16 ModbusCRC(u8 * pData, u8 len)
{
    u8 byCRCHi = 0xff;
    u8 byCRCLo = 0xff;
    u8 byIdx;
    u16 crc;

    while(len--)
    {
       byIdx = byCRCHi ^* pData++;
       byCRCHi = byCRCLo ^ gabyCRCHi[byIdx];
       byCRCLo = gabyCRCLo[byIdx];
    }
	crc = byCRCHi;
	crc <<= 8;
	crc += byCRCLo;
	return crc;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
u16 Convert_Wat_Data(u16 rpms,u8 lev)
{
	u16 rets;
    //要修改成100个档位的版本所以功率等级要先降下来
    if(lev>=90) lev=10;
    else if((lev>10)&&(lev<90))lev= lev/10;
    else lev=lev;
	if(rpms<Corrdard[0])
	{
		rets = (rpms * Watt_Tbl[lev][0])/Corrdard[0];
	}
	else if(rpms==Corrdard[0])
	{
		rets=Watt_Tbl[lev][0];
	}
	else if(rpms<Corrdard[1])
	{
		rets=Watt_Tbl[lev][0] + ((rpms-Corrdard[0])*(Watt_Tbl[lev][1]-Watt_Tbl[lev][0]))/(Corrdard[1]-Corrdard[0]);
	}
	else if(rpms==Corrdard[1])
	{
		rets=Watt_Tbl[lev][1];
	}
	else if(rpms<Corrdard[2])
	{
		rets=Watt_Tbl[lev][1] + ((rpms-Corrdard[1])*(Watt_Tbl[lev][2]-Watt_Tbl[lev][1]))/(Corrdard[2]-Corrdard[1]);
	}
	else if(rpms==Corrdard[2])
	{
		rets=Watt_Tbl[lev][2];
	}
	else if(rpms<Corrdard[3])
	{
		rets=Watt_Tbl[lev][2] + ((rpms-Corrdard[2])*(Watt_Tbl[lev][3]-Watt_Tbl[lev][2]))/(Corrdard[3]-Corrdard[2]);
	}
	else if(rpms==Corrdard[3])
	{
		rets=Watt_Tbl[lev][3];
	}
	else if(rpms<Corrdard[4])
	{
		rets=Watt_Tbl[lev][3] + ((rpms-Corrdard[3])*(Watt_Tbl[lev][4]-Watt_Tbl[lev][3]))/(Corrdard[4]-Corrdard[3]);
	}
	else if(rpms==Corrdard[4])
	{
		rets=Watt_Tbl[lev][4];
	}
	else if(rpms<Corrdard[5])
	{
		rets=Watt_Tbl[lev][4] + ((rpms-Corrdard[4])*(Watt_Tbl[lev][5]-Watt_Tbl[lev][4]))/(Corrdard[5]-Corrdard[4]);
	}
	else if(rpms==Corrdard[5])
	{
		rets=Watt_Tbl[lev][5];
	}

	else if(rpms<Corrdard[6])
	{
		rets=Watt_Tbl[lev][5] + ((rpms-Corrdard[5])*(Watt_Tbl[lev][6]-Watt_Tbl[lev][5]))/(Corrdard[6]-Corrdard[5]);
	}
	else if(rpms==Corrdard[6])
	{
		rets=Watt_Tbl[lev][6];
	}

	else if(rpms<Corrdard[7])
	{
		rets=Watt_Tbl[lev][6] + ((rpms-Corrdard[6])*(Watt_Tbl[lev][7]-Watt_Tbl[lev][6]))/(Corrdard[7]-Corrdard[6]);
	}
	else if(rpms==Corrdard[7])
	{
		rets=Watt_Tbl[lev][7];
	}
	else if(rpms>Corrdard[7])
	{
		rets =  Watt_Tbl[lev][7] + ((rpms-Corrdard[7]) * Watt_Tbl[lev][7])/Corrdard[7];
	}
	return rets;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void Driver_Ctrl_Handler(void)
{
	/*
	if(timer.second_flg==1)	//控制器需要每秒钟进行更新数据
	{
		timer.second_flg=0;
		RS485_SEND();
		uart2.sbuf[0]=DR_HEAD_BYTE;
		uart2.sbuf[1]=DR_FUNC_BYTE;
		if(sport.start==0)	//待机
		{
			uart2.sbuf[2]=(DR_AD_MODE);
		}
		else
		{
			if(sport.resume==0)
			{
				uart2.sbuf[2]=(0x02|DR_AD_MODE);//暂停
			}
			else
			{
				uart2.sbuf[2]=(0x01|DR_AD_MODE);	//继续计数
			}
		}
		uart2.sbuf[3]=0;
		uart2.sbuf[4]=DR_SEL_LEV;
		uart2.sbuf[5]=PWM_LEV_ARRY[sport.level];
		uart2.sbuf[6]=DR_PER_PULSE;
		uart2.sbuf[7]=ModbusCRC(uart2.sbuf,7)>>8;
		uart2.sbuf[8]=ModbusCRC(uart2.sbuf,7);
		Uart2_Send_N_bytes(uart2.sbuf,9);
		RS485_REV();
	}
	if(uart2.rev_flg==1)	//接收到控制器的反馈消息
	{
		if((uart2.rbuf[1]==0x01)&&(uart2.rbuf[2]==0xC0))
		{
			for(i=0;i<uart2.length;i++)
			{
				uart2.rbuf[i]=uart2.rbuf[i+1];
			}
			uart2.length--;
		}
		if(ModbusCRC(uart2.rbuf,9)==(((u16)uart2.rbuf[9]<<8)+uart2.rbuf[10]))
		{
			if(sport.start==1)	//开始
			{
				rpm.rate=((u16)uart2.rbuf[4]<<8)+uart2.rbuf[5];		//转速
				c_dbg_print("<<Rate:%d\t",rpm.rate);
				u32_data.u8_val[0]=0;
				u32_data.u8_val[1]=uart2.rbuf[6];
				u32_data.u8_val[2]=uart2.rbuf[7];
				u32_data.u8_val[3]=uart2.rbuf[8];
				rpm.total_cnt=u32_data.u32_val;	//圈数
				c_dbg_print("RPM Count:%ld\t",(u32)rpm.total_cnt);
				if(rpm.Back_cnts!=rpm.total_cnt)
				{
					rpm.Back_cnts=rpm.total_cnt;
					rpm.send_flg=1;
				}
				rpm.total_miles=(rpm.total_cnt*PERIMETER)/1000;	//总距离：m
				rpm.distance=(u16)(rpm.total_miles/10);	//距离:0.01km
				c_dbg_print("Distance:%d-%.1fKm\t",(u16)rpm.distance,((float)rpm.distance)/10);

				rpm.speed=(u16)(((u32)rpm.rate*PERIMETER*6)/10000);//速度(0.1km/h)
				c_dbg_print("[RPM]: Speed:%.1fKM\r\n",((float)rpm.speed/10));

				c_dbg_print("Lev:%d\t",(u8)sport.level);

				sport.watt=Convert_Wat_Data((u16)rpm.rate,(u8)sport.level);	//功率
				c_dbg_print("Watt:%dW\t",(u16)sport.watt);

				sport.cal_sum=sport.cal_sum+sport.watt;
				sport.calorie=sport.cal_sum/100;	//卡路里
				c_dbg_print("Cal:%d-%.1fKcal\r\n",(u16)sport.calorie,(float)sport.calorie/10);

				//c_dbg_print("----------------------------------\r\n");
			}
			else
			{
				c_dbg_print("Standby\r\n");
			}
		}

		uart2.length=0;
		uart2.rev_flg=0;

	}
	if((rpm.second_flg==1)&&(sport.start==1))
	{
		rpm.second_flg=0;
		sport.cal_sum=sport.cal_sum+sport.watt;
		sport.calorie=(u32)(sport.cal_sum/418.6); //卡路里(0.1KCAL)
		c_dbg_print("Cal:%d - %.1fKcal\r\n",(u16)sport.calorie,(float)sport.calorie/10);
	}
	*/

	if(timer.second_flg==0) //控制器需要每秒钟进行更新数据
	{
		timer.second_flg=50;
		RS485_SEND();
		uart2.sbuf[0]=DR_HEAD_BYTE;
		uart2.sbuf[1]=DR_FUNC_BYTE;
		uart2.sbuf[2]=PWM_LEV_ARRY[sport.level]>>8;
		uart2.sbuf[3]=PWM_LEV_ARRY[sport.level];
		uart2.sbuf[4]=sport.loader;
		uart2.sbuf[5]=ModbusCRC(uart2.sbuf,5)>>8;
		uart2.sbuf[6]=ModbusCRC(uart2.sbuf,5);
		Uart2_Send_N_bytes(uart2.sbuf,7);
		RS485_REV();
	}
	if(uart2.rev_flg==1)	//接收到控制器的反馈消息
	{
		if(ModbusCRC(uart2.rbuf,9)==(((u16)uart2.rbuf[9]<<8)+uart2.rbuf[10]))
		{
			bat.H_Voltage=((u16)uart2.rbuf[2]<<8)+uart2.rbuf[3];
			bat.R_Current=((u16)uart2.rbuf[4]<<8)+uart2.rbuf[5];
			bat.R_PWMAD=((u16)uart2.rbuf[6]<<8)+uart2.rbuf[7];
			bat.loader=uart2.rbuf[8];
#if 0
			c_dbg_print("------------------------------------------------\r\n");
			c_dbg_print("H_Voltage: %d-%ldV\t",bat.H_Voltage,(((u32)bat.H_Voltage*5*101)/1024));
			c_dbg_print("R_Current: %d-%ldmA\t",bat.R_Current,((u32)bat.R_Current*303)/39);
			c_dbg_print("R_PWMAD: %d\t",bat.R_PWMAD);
			c_dbg_print("loader: %d\r\n",bat.loader);
			c_dbg_print("------------------------------------------------\r\n");
#endif
		}
		uart2.length=0;
		uart2.rev_flg=0;
	}

}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void Key_Function(void)
{
    if(key.value>KEY_VALUE_NONE)
    {
    	Beep_Ring(5);
    	if(key.value==KEY_VALUE_UP)	//阻力+
    	{

            if((face_sport.inputSexFlag ==1)||(face_sport.inputWeightFlag==1))
            {   
                if(face_sport.inputSexFlag ==1)
                {
                    face_sport.inputSex =0;            
                }

                if(face_sport.inputWeightFlag ==1)
                {
                    if(face_sport.inputWeight <100) face_sport.inputWeight++;
                }
            }
            else
            {
                if(key.b_cont_flg)
                {
                    sport.level += 10;
                }
                else
                {
                    sport.level ++;

                }
                if(sport.level>=PWM_LEV_MAX) sport.level=PWM_LEV_MAX;
                c_dbg_print("[KEY]: Lev++: %d \r\n",sport.level);
            }
    	}
    	else if(key.value==KEY_VALUE_DOWN)	//阻力-
    	{

            if((face_sport.inputSexFlag ==1)||(face_sport.inputWeightFlag==1))
            {
                 if(face_sport.inputSexFlag ==1)
                {
                    face_sport.inputSex =1;            
                }

                if(face_sport.inputWeightFlag ==1)
                {
                    if(face_sport.inputWeight >5) --face_sport.inputWeight;
                }
            
            }else
            {
                if(key.b_cont_flg)
                {
                    if(sport.level >10)
                    sport.level -= 10;
                }
                else
                {
                    if(sport.level >1)
                    sport.level --;

                }
                if(sport.level<=1) sport.level =1;
                c_dbg_print("[KEY]: Lev--: %d \r\n",sport.level);        
            }
    	}
    	else if(key.value==KEY_VALUE_TEST)	//测试模式
    	{
            clean_face_sport();           
            lcd.refresh=1;
            face_sport.step = SELECT_MODE_STEP;
            face_sport.mode=MODE_TEST;
    	}
        else if(key.value==KEY_VALUE_EXE)	//训练模式
    	{            
            clean_face_sport();
            lcd.refresh=1;
            face_sport.step = SELECT_MODE_STEP;
            face_sport.mode=MODE_TRAIN;

    	}
    	else if(key.value==KEY_VALUE_RST)	//蓝牙复位
    	{

            if((face_sport.inputSexFlag ==1)||(face_sport.inputWeightFlag==1))
            {
			  
			     if(face_sport.inputWeightFlag ==1)
                {
                    face_sport.inputWeightFlag=0;
                    //clear_screen();
                    Beep_Ring(50);
                    lcd.refresh =1;
                    rpm.total_cnt=0;
                }
                if(face_sport.inputSexFlag ==1)
                {
                    face_sport.inputSexFlag=0;
                    //clear_screen();
                    lcd.refresh =1;
                    face_sport.inputWeightFlag=1;
                }


            }
            else if(face_sport.step ==SELECT_MODE_STEP)
            {
                face_sport.start=1;
                //if(face_sport.step != SELECT_MODE_STEP) face_sport.mode = MODE_TRAIN;
                if(face_sport.resDispTime == 0)//在显示结果的完成之后才能开始下次运动
                {
                    rpm.timeOut = TIMEOUT_MAX; 
                    face_sport.err_count=0;
                    face_sport.step=SPORTING_STEP;
                    lcd.refresh=1;
                    rpm.total_cnt=0;
                    face_sport.detail=0;
                }
                if(face_sport.mode == MODE_TEST) 
                {
                    face_sport.timeRemain = SPORTING_TIME;
                }
            }
            else
            {
                c_dbg_print("[KEY]: BLE Reset!\r\n");
                //BLE_Reset(50);
                clean_face_sport();
            }
    	}
    	power.time_cnt=TIMEOUT_MAX;
    	key.b_cont_flg=0;
    	key.value=KEY_VALUE_NONE;
    }

}


/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void HR_INT_Init(void)	//心跳初始化
{
	u8 i;
	hr.init_flg=0;
	hr.int_flg=0;
	hr.count= 0;
	hr.rate=0;
	hr.nbits =0;
	for(i=0;i<HR_DATA_MAX;i++)
	{
	    hr.array[i]=0;
	}
	GPIO_Init(HR_Port,HR_Pin,GPIO_Mode_In_PU_IT);		//中断输入
}

void HR_GPIO_Sleep(void)
{
    GPIO_Init(HR_Port,HR_Pin,GPIO_Mode_Out_PP_Low_Slow);		//中断输入
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void HR_INT_Routine(void)
{
	if((hr.count>HR_COUNT_MIN)&&(hr.count<HR_COUNT_MAX))//最大不超过
	{
		HR_Display(30);
		hr.int_flg=1;  //中断
		hr.cnt_bak=hr.count;
		hr.count = 0; //得到有效计数时，清除计数，如果发现中断间隔远低于有效计数时，认为是干扰，不清零
	}
	else if(hr.count>=HR_COUNT_MAX)
	{
		hr.count = 0;
	}
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void HR_Handler(void)
{
	u8 i;
	u16 temp;
	u32 sum;
	if(hr.int_flg==1)
	{
		hr.int_flg=0;
		temp = (u16)(60000/hr.cnt_bak);
		hr.array[hr.nbits]=temp;
		hr.nbits++;
		if(hr.nbits>=HR_DATA_MAX)
		{
			hr.init_flg=1;
			hr.nbits =0;
		}
		if(hr.init_flg==1)
		{
			sum =0;
			for(i=0;i<HR_DATA_MAX;i++)
			{
				sum +=hr.array[i];
			}
			sum = sum/HR_DATA_MAX;	//求平均值
			if(sum>HR_RATE_Max) sum = HR_RATE_Max;	//最大不超过240转
			hr.rate=(u16)sum;
			c_dbg_print("[HR]: heart is :%d\r\n",hr.rate);
		}
	}
	if(hr.count>=5000)          //超时5秒视为无效数据
	{
	    hr.rate=0;
	    for(i=0;i<HR_DATA_MAX;i++)
	    {
	    	hr.array[i]=0;
	    }
	    hr.init_flg=0;
	}
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void HR_TimeTicket(void)
{
	  if(hr.count<5003) 	hr.count++;    //设定低于5001时可以累计时间,持续超过5001时不用继续计时和触发
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void RPM_INT_Init(void)
{
	rpm.count=0;
	rpm.cnt_bak=0;
	rpm.total_cnt=0;
	rpm.Back_cnts=0;
	rpm.total_miles=0;
	rpm.distance=0;

	rpm.int_flg=0;
	rpm.init_flg=0;
	rpm.nbits=0;
	rpm.rate=0;
	rpm.cal_cnt=0;
	//GPIO_Init(RPM_Port,RPM_Pin,GPIO_Mode_In_FL_IT);		//中断输入
	GPIO_Init(RPM_Port,RPM_Pin,GPIO_Mode_In_PU_IT);		//中断输入
	
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void RPM_INT_Routine(void)
{
	#if Machine_Type==KeepFitBike
	//健身车
	if((rpm.count>RPM_COUNT_MIN)&&(rpm.count<RPM_COUNT_MAX))//最大不超过
	{
		rpm.int_flg=1;  //中断
		rpm.cnt_bak=rpm.count;
		rpm.count = 0; //得到有效计数时，清除计数，如果发现中断间隔远低于有效计数时，认为是干扰，不清零
	}
	else if(rpm.count>=RPM_COUNT_MAX)
	{
		rpm.count = 0;
	}
	#endif
	#if Machine_Type==PowerBike		//力量型
	if(rpm.count>RPM_COUNT_MIN)//最大不超过
	{
		rpm.int_flg=1;  //中断
		rpm.cnt_bak=rpm.count;
		rpm.count = 0; //得到有效计数时，清除计数，如果发现中断间隔远低于有效计数时，认为是干扰，不清零
	}
	#endif
	power.time_cnt=TIMEOUT_MAX;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void RPM_TimeTicket(void)
{
	if(rpm.count<5003) 	rpm.count++;
    if(rpm.timeOut ) rpm.timeOut--;                         //设备无人操作超时
}

/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void RPM_Handler(void)
{
	u8 i;
	u16 temp;
	u32 sum;
	if(rpm.int_flg==1)
	{
		rpm.int_flg=0;rpm.send_flg=1;
		temp = (u16)(60000/rpm.cnt_bak);
		rpm.array[rpm.nbits]=temp;
		rpm.nbits++;
		if(rpm.nbits>=RPM_DATA_MAX)
		{
			rpm.init_flg=1;
			rpm.nbits =0;
		}
		if(ble.state==0) sport.resume=1;	//无蓝牙时，通过运动自动恢复计数计时
		#if (Device_ID == 0x14)||(Device_ID == 0xB0)||(Device_ID == 0xB3)||(Device_ID == 0x22)	//深蹲，车类每次计一次，其它项目计两次算一次
		rpm.total_cnt++;	//中断次数
		#else
    		rpm.cal_cnt++;
    		if(rpm.cal_cnt>1)
    		{
    			rpm.cal_cnt=0;
    			rpm.total_cnt++;	//中断次数
    		}
		#endif

        if(face_sport.start == 0)
        {
            face_sport.start=1;
            if(face_sport.step != SELECT_MODE_STEP) face_sport.mode = MODE_TRAIN;
            if(face_sport.resDispTime == 0)//在显示结果的完成之后才能开始下次运动
            {
                face_sport.err_count=0;
                face_sport.step=SPORTING_STEP;
                lcd.refresh=1;
                rpm.total_cnt=0;
                face_sport.detail=0;
            }
            if(face_sport.mode == MODE_TEST) 
            {
                face_sport.timeRemain = SPORTING_TIME;
            }
        }
        rpm.timeOut = TIMEOUT_MAX;        
		//	c_dbg_print("[RPM]: total_cnt:%ld\r\n",rpm.total_cnt);
		if(rpm.init_flg==1)
		{
			sum =0;
			for(i=0;i<RPM_DATA_MAX;i++)
			{
				sum +=rpm.array[i];
			}
			sum = sum/RPM_DATA_MAX;	//求平均值
			if(sum>RPM_RATE_Max) sum = RPM_RATE_Max;	//最大不超过240转
			rpm.rate=(u16)sum;
		//	c_dbg_print("[RPM]: rate is :%d\r\n",rpm.rate);

			if((sport.start==1)&&(sport.resume==1))	//开始
			{
				rpm.speed=(u16)(((u32)rpm.rate*PERIMETER*6)/10000);//速度(0.1km/h)
				sport.watt=Convert_Wat_Data(rpm.rate,sport.level);	//功率
				rpm.total_miles=((u32)rpm.total_cnt*PERIMETER)/1000;	//总距离(米)
				rpm.distance=(u16)(rpm.total_miles/100);	//距离(0.1KM)
				rpm.cycle=(u16)(rpm.total_miles/400);		//圈数
			}
		}
	}
	if((rpm.second_flg==1)&&(sport.start==1)&&(sport.resume==1))
	{
		rpm.second_flg=0;
		sport.cal_sum=sport.cal_sum+sport.watt;
		sport.calorie=(u32)(sport.cal_sum/418.6); //卡路里(0.1KCAL)
//		c_dbg_print("Cal:%d - %.1fKcal\r\n",(u16)sport.calorie,(float)sport.calorie/10);
	}
	if(rpm.count>=5000)          //超时5秒视为无效数据
	{
	    rpm.rate=0;
	    for(i=0;i<RPM_DATA_MAX;i++)
	    {
	    	rpm.array[i]=0;
	    }
	    rpm.init_flg=0;
	    rpm.speed=0;  
	}

    if(rpm.timeOut == 0)        //30S没运动是运动结束
    {
        if(face_sport.start ==1)
        {
            if(face_sport.mode ==MODE_TRAIN)
            {
                face_sport.start=0;
                if(face_sport.step == SPORTING_STEP)
                {
                    face_sport.err_count =0;
                    face_sport.resDispTime = RESOULT_DISP_TIME;
                    face_sport.step=REPORT_STEP;
                    lcd.refresh=1;
                }
                if(ble.state==0)	sport.resume=0;	//无蓝牙连接时
            }
        }
    }    
}

/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void Watt_Lev_Print(void)
{
	u8 i;
	u16 j;

	for(i=1;i<8;i++)
	{
			c_dbg_print("[LEV]: LEV:%d\r\n",i);
			for(j=40;j<180;j+=1)
			{
				sport.watt=Convert_Wat_Data(j,i); //功率
				c_dbg_print("[RPM]:%d, Watt:%dW\r\n",j,sport.watt);
			}
			c_dbg_print("*************************************\r\n");
	}
	delay_ms(50000);
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/


void Standby_Serv_Handler(void)
{
	if(power.time_cnt==0)
	{
		sim();	//暂时禁止中断

		sport.level=1;
		RS485_SEND();	//取消阻力
		uart2.sbuf[0]=DR_HEAD_BYTE;
		uart2.sbuf[1]=DR_FUNC_BYTE;
		uart2.sbuf[2]=PWM_LEV_ARRY[sport.level]>>8;
		uart2.sbuf[3]=PWM_LEV_ARRY[sport.level];
		uart2.sbuf[4]=sport.loader;
		uart2.sbuf[5]=ModbusCRC(uart2.sbuf,5)>>8;
		uart2.sbuf[6]=ModbusCRC(uart2.sbuf,5);
		Uart2_Send_N_bytes(uart2.sbuf,7);
		RS485_REV();
	
		GPIO_Init(BLE_CONNECT_PORT,BLE_CONNECT_PIN,GPIO_Mode_In_PU_IT);//ble
		EXTI_SetPinSensitivity(EXTI_Pin_4,EXTI_Trigger_Falling);//key
		//
		EXTI_SetPinSensitivity(EXTI_Pin_6,EXTI_Trigger_Falling);//key
		EXTI_SetPinSensitivity(EXTI_Pin_7,EXTI_Trigger_Rising_Falling);//key  ,ble

		//GPIO_Init(RPM2_Port,RPM2_Pin,GPIO_Mode_In_PU_IT);		//rpm2中断输入
		//EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Falling);	//rpm2

		GPIO_Init(RPM_Port,RPM_Pin,GPIO_Mode_In_PU_IT);		//rpm中断输入
		EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling);//rpm
		
        GPIO_Init(KEY_INT_PORT, KEY_INT_PIN, GPIO_Mode_In_PU_IT);
        EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Rising_Falling);//key
        LCD_GPIO_Sleep();//关闭LCDSPI管脚,降低功耗               
        
        HR_GPIO_Sleep();
        clean_face_sport();
        
		delay_ms(1000);
		DB_POWER_LOW();       //电源控制
		LCD_BACKLIGHT_OFF;     //关闭背光
    	c_dbg_print("[WFE]: Goto Sleep!\r\n");
    	delay_ms(100);
    	rim();	//允许中断

		halt();

		sim();	//暂时禁止中断
		LCD_BACKLIGHT_ON;     //打开背光
		DB_POWER_HIG();
		SysClock_Init();
		Hard_Init();
		delay_ms(100);
		ADC_Config();
		HR_INT_Init();
		RPM_INT_Init();
		Uart_Init();
		Timer_Init();
		Exti_Init();	//中断初始化
		lcd_Init();
        KEY_GPIO_INIT();

		Ultra_Power_Init();
		Soft_Init();
        memset(&lcd,0x00,sizeof(lcd));
        lcd.refresh=1;
        
		GPIO_Init(BLE_CONNECT_PORT,BLE_CONNECT_PIN,GPIO_Mode_In_PU_No_IT);
		power.time_cnt=TIMEOUT_MAX;
		c_dbg_print("[WFE]: Start up!\r\n");
		Beep_Ring(100);
		rim();	//允许中断
	}
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void Ultra_Power_Init(void)
{
	PWR_DeInit();
	PWR_FastWakeUpCmd(ENABLE);
	PWR_UltraLowPowerCmd(ENABLE);
}


//对液晶模块进行初始化设置
void lcd_Init(void)
{
    LCD_GPIO_Init();
    initial_lcd();
    Font_Ic_GPIO_Init();
    clear_screen(); 
    LCD_BACKLIGHT_ON;
}


/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/
void Function(void)
{
	Key_Function();
	ADC_Serv_Handler();
	HR_Handler();
	RPM_Handler();
	Driver_Ctrl_Handler();
	//Uart_BLE_Serv_Handler();
	Standby_Serv_Handler();
    face_sport_handler();
    Step_Display();
    Uart_Face_Serv_Handler();
    face_sport_test();
}

/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void Beep_Ring(u8 time)
{
	Set_Beep_ON();
	beep.time=time;
}

void BLE_Reset(u8 time)
{
	BLE_RST_LOW();
	ble.rst_time=time;
}
void LED_Display(u8 time)
{
	Set_Led1_On();
	led.time=time;
}

void HR_Display(u8 time)
{
	hr.display_flg=1;
	hr.time=time;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void System_Timeticket(void)
{
	timer.micros++;				//计数
	if(timer.micros>100)
	{
		timer.micros=0;//计算秒数
		rpm.second_flg=1;

		if(sport.resume==1)
		{
			timer.total_time++;
		}      
	}
	if(timer.second_flg)
	timer.second_flg--;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void Uart_BLE_Serv_Handler(void)
{
	u8 Ble_Connect=0;
	if(BLE_CONNECT_VAL()==RESET)
	{
		Ble_Connect=1;
		power.time_cnt=TIMEOUT_MAX;	//只要蓝牙连接上，永不待机
	}
	else
	{
		Ble_Connect=0;
	}
	if(ble.state!=Ble_Connect)
	{
		ble.state=Ble_Connect;
		timer.second_flg=1;
		if(Ble_Connect==1)	//连接上蓝牙
		{
			//BLE_WAKUP_LOW();
			sport.start=0;sport.resume=0;
			c_dbg_print("[ble]: Connect ok!\r\n");
		}
		else
		{
			//BLE_WAKUP_HIG();
			sport.start=1;sport.resume=0;
			c_dbg_print("[ble]: Release ok!\r\n");
		}
		//蓝牙通断都将清除以下数据
		timer.total_time=0;
		rpm.total_cnt=0;
		rpm.Back_cnts=0;
		rpm.total_miles=0;
		rpm.distance=0;
		rpm.speed=0;
		rpm.rate=0;
		sport.calorie=0;
		sport.cal_sum=0;
		sport.watt=0;
		sport.level=1;
	}

	if(uart3.rev_flg==1)
	{
		//if(Get_Buffer_Checksum(&uart3.rbuf[2],uart3.length-3)==uart3.rbuf[uart3.length-1])
		{
			switch(uart3.rbuf[6])	//命令字节
			{
				case 0xD0:	//握手指令
				{
					uart3.sbuf[0]=0xAA;
					uart3.sbuf[1]=0x06;
					uart3.sbuf[2]=0x00;
					uart3.sbuf[3]=0x02;
					uart3.sbuf[4]=0x00;
					uart3.sbuf[5]=Device_ID;
					uart3.sbuf[6]=0xD0;
					uart3.sbuf[7]=Get_Buffer_Checksum(&uart3.sbuf[2],5);
					Uart3_Send_N_bytes((u8 *)uart3.sbuf,8);
					c_dbg_print("[BLE]: ***********ACK*********\r\n");
				}break;
				case 0xD1:
				{
					if(uart3.rbuf[7]==0x00) //停止健身车
					{
						Beep_Ring(5);
						sport.start=0;
						sport.resume=0;
						sport.level=1;
						sport.send_cnt=20;
						timer.second_flg=1;
						rpm.total_cnt=0;
						uart3.sbuf[0]=0xAA;
						uart3.sbuf[1]=0x07;
						uart3.sbuf[2]=0x00;
						uart3.sbuf[3]=0x02;
						uart3.sbuf[4]=0x00;
						uart3.sbuf[5]=Device_ID;
						uart3.sbuf[6]=0xD1;
						uart3.sbuf[7]=0x01;	//OK
						uart3.sbuf[8]=Get_Buffer_Checksum(&uart3.sbuf[2],6);
						Uart3_Send_N_bytes((u8 *)uart3.sbuf,9);
						c_dbg_print("[BLE]: ***********Stop*********\r\n");
					}
					else if(uart3.rbuf[7]==0x01) //开始健身车
					{
						Beep_Ring(5);
						sport.cal_sum=0;
						sport.watt=0;
						sport.calorie=0;
						sport.level=1;
						sport.send_cnt=20;
						sport.start=1;sport.resume=1;
						timer.total_time=0;
						timer.second_flg=1;
						rpm.total_cnt=0;
						rpm.rate=0;
						rpm.cycle=0;
						rpm.distance=0;
						rpm.rate=0;
						rpm.speed=0;
						rpm.total_miles=0;
						rpm.Back_cnts=0;

						uart3.sbuf[0]=0xAA;
						uart3.sbuf[1]=0x07;
						uart3.sbuf[2]=0x00;
						uart3.sbuf[3]=0x02;
						uart3.sbuf[4]=0x00;
						uart3.sbuf[5]=Device_ID;
						uart3.sbuf[6]=0xD1;
						uart3.sbuf[7]=0x01;	//OK
						uart3.sbuf[8]=Get_Buffer_Checksum(&uart3.sbuf[2],6);
						Uart3_Send_N_bytes((u8 *)uart3.sbuf,9);
						c_dbg_print("[BLE]: ***********Start*********\r\n");
					}
				}break;
				case 0xD4:	//设置阻力
				{
					if(uart3.rbuf[7]<=PWM_LEV_MAX)
					{
						Beep_Ring(5);
						sport.level=uart3.rbuf[7];
						sport.send_cnt=20;
						uart3.sbuf[0]=0xAA;
						uart3.sbuf[1]=0x07;
						uart3.sbuf[2]=0x00;
						uart3.sbuf[3]=0x02;
						uart3.sbuf[4]=0x00;
						uart3.sbuf[5]=Device_ID;
						uart3.sbuf[6]=0xD4;
						uart3.sbuf[7]=0x01;	//OK
						uart3.sbuf[8]=Get_Buffer_Checksum(&uart3.sbuf[2],6);
						Uart3_Send_N_bytes((u8 *)uart3.sbuf,9);
						c_dbg_print("[BLE]: ***********Set Lev:%d*********\r\n",sport.level);
					}
					else
					{
						Beep_Ring(5);
						sport.send_cnt=20;
						uart3.sbuf[0]=0xAA;
						uart3.sbuf[1]=0x07;
						uart3.sbuf[2]=0x00;
						uart3.sbuf[3]=0x02;
						uart3.sbuf[4]=0x00;
						uart3.sbuf[5]=Device_ID;
						uart3.sbuf[6]=0xD4;
						uart3.sbuf[7]=0x00; //NG
						uart3.sbuf[8]=Get_Buffer_Checksum(&uart3.sbuf[2],6);
						Uart3_Send_N_bytes((u8 *)uart3.sbuf,9);
						c_dbg_print("[BLE]: ***********Set Lev Error:%d*********\r\n",uart3.rbuf[7]);
					}
				}break;
				case 0xD7:	//暂停与继续计数
				{
						Beep_Ring(5);
						sport.resume=uart3.rbuf[7];
						uart3.sbuf[0]=0xAA;
						uart3.sbuf[1]=0x07;
						uart3.sbuf[2]=0xff;
						uart3.sbuf[3]=0x02;
						uart3.sbuf[4]=0x00;
						uart3.sbuf[5]=Device_ID;
						uart3.sbuf[6]=0xD7;
						uart3.sbuf[7]=sport.resume; //OK
						uart3.sbuf[8]=Get_Buffer_Checksum(&uart3.sbuf[2],6);
						Uart3_Send_N_bytes((u8 *)uart3.sbuf,9);
						if(sport.resume==0)
						{
							c_dbg_print("[BLE]: ***********Pause Count!*********\r\n");
						}
						else
						{
							c_dbg_print("[BLE]: ***********Continue Count!*********\r\n");
						}

				}break;
			    default:break;
			}
		}
		uart3.length=0;
		uart3.rev_flg=0;

	}

	if(sport.start==1)
	{
		#if Machine_Type==KeepFitBike
		//健身车
		if(sport.send_cnt==0)
		{
			sport.send_cnt=100;
			sport.send_cnt2=20;	//200ms以后再发下一包

			uart3.sbuf[0]=0xAA;
			uart3.sbuf[1]=13;
			uart3.sbuf[2]=0x00;
			uart3.sbuf[3]=0x02;
			uart3.sbuf[4]=0x00;
			uart3.sbuf[5]=Device_ID;	//推胸划船
			uart3.sbuf[6]=0xD2;
			uart3.sbuf[6+1]=rpm.rate>>8;
			uart3.sbuf[6+2]=rpm.rate;
			uart3.sbuf[6+3]=rpm.speed>>8;
			uart3.sbuf[6+4]=rpm.speed;
			uart3.sbuf[6+5]=sport.watt>>8;
			uart3.sbuf[6+6]=sport.watt;
			uart3.sbuf[6+7]=sport.level;
			uart3.sbuf[6+8]=Get_Buffer_Checksum(&uart3.sbuf[2],12);
			Uart3_Send_N_bytes(uart3.sbuf,15);
		}
		if(sport.send_cnt2_flg==1)
		{
			sport.send_cnt2_flg=0;
			uart3.sbuf[0]=0xAA;
			uart3.sbuf[1]=13;
			uart3.sbuf[2]=0xFF;
			uart3.sbuf[3]=0x02;
			uart3.sbuf[4]=0x00;
			uart3.sbuf[5]=Device_ID;
			uart3.sbuf[6]=0xD2;
			uart3.sbuf[6+1]=rpm.distance>>8;
			uart3.sbuf[6+2]=rpm.distance;
			uart3.sbuf[6+3]=timer.total_time>>8;
			uart3.sbuf[6+4]=timer.total_time;
			uart3.sbuf[6+5]=sport.calorie>>8;
			uart3.sbuf[6+6]=sport.calorie;
			uart3.sbuf[6+7]=hr.rate;
			uart3.sbuf[6+8]=Get_Buffer_Checksum(&uart3.sbuf[2],12);
			Uart3_Send_N_bytes(uart3.sbuf,15);
		}
		#endif
		#if Machine_Type==PowerBike
		//力量型
		if((sport.send_cnt==0)&&(rpm.send_flg==1))
		{
			rpm.send_flg=0;
			sport.send_cnt=100;
			uart3.sbuf[0]=0xAA;
			uart3.sbuf[1]=13;
			uart3.sbuf[2]=0xFF;
			uart3.sbuf[3]=0x02;
			uart3.sbuf[4]=0x00;
			uart3.sbuf[5]=Device_ID;
			uart3.sbuf[6]=0xD2;
			uart3.sbuf[6+1]=rpm.total_cnt>>8;
			uart3.sbuf[6+2]=rpm.total_cnt;
			uart3.sbuf[6+3]=sport.watt>>8;
			uart3.sbuf[6+4]=sport.watt;
			uart3.sbuf[6+5]=sport.calorie>>8;
			uart3.sbuf[6+6]=sport.calorie;
			uart3.sbuf[6+7]=sport.level;
			uart3.sbuf[6+8]=hr.rate;
			uart3.sbuf[6+9]=Get_Buffer_Checksum(&uart3.sbuf[2],13);
			Uart3_Send_N_bytes(uart3.sbuf,16);
			c_dbg_print(">>[BLE]: Send Count:%d\r\n",(u16)rpm.total_cnt);
		}
	#endif
	}
}




/*
    人脸识别接口


*/
void Uart_Face_Serv_Handler(void)
{


	if(uart1.rev_flg==1)
	{
        face_sport.err_count =0;

		switch(uart1.rbuf[5])	//命令字节
		{
				case 0xD0:	//握手指令
				{
                    face_sport.hand_flag=1;
                     
				}break;
				case 0xD1:      //启动指令收到应答
				{
                    face_sport.start_flag=1;
                    memcpy(face_sport.faceId,&uart1.rbuf[6],FACE_ID_LENGTH);                        
				}break;
				case 0xD2:	//发送运动数据应答
				{
                    face_sport.date_flag=1;	

                    if(face_sport.mode ==MODE_TEST)
                    {
                        #if (Device_ID == 0x12)
                            face_sport.res.date=uart1.rbuf[6]*256+uart1.rbuf[7];
                            face_sport.res.score = uart1.rbuf[8];
                            face_sport.res.evalue = uart1.rbuf[9];
                        #endif
                        #if(Device_ID == 0xAF)
                            face_sport.res.MaxOxygen = uart1.rbuf[6]*256+uart1.rbuf[7];
                            face_sport.res.ReOxygen = uart1.rbuf[8]*256+uart1.rbuf[9];
                            face_sport.res.evalue = uart1.rbuf[10];
                        #endif
                    }
				}break;

                case 0xD3:	//设备超时应答
				{
                    face_sport.timeOut_flag=1;						
				}break;

                case 0xD7:	//服务器请求当前运动状态
				{                        
                    face_sport.status_flag=1;					
				}break;
				case 0xD8:	//设置二维码
				{
                    face_sport.setQR_flag=1;
                    face_sport.qrcode.qrLength = uart1.rbuf[1]-5;
                    memset(face_sport.qrcode.QRCODE,0x00,sizeof(face_sport.qrcode.QRCODE));
                    memcpy(face_sport.qrcode.QRCODE,&uart1.rbuf[6],face_sport.qrcode.qrLength);

                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x06;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xD8;  
                    uart1.sbuf[6]=0x01; 
                    uart1.sbuf[7]=Get_Buffer_Checksum(&uart1.sbuf[2],5);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,8);
				}break;

                case 0xD9:	//清除二维码
				{
                    face_sport.cleanQR_flag=1;
                    memset(face_sport.qrcode.QRCODE,0x00,sizeof(face_sport.qrcode.QRCODE));
                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x06;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xD9;  
                    uart1.sbuf[6]=0x01; 
                    uart1.sbuf[7]=Get_Buffer_Checksum(&uart1.sbuf[2],5);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,8);

				}break;
                case 0xDD:	//请求阻力
				{
                    delay_us(5);
                    face_sport.power_flag=1;
                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x25;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xDD;
                    memcpy(&uart1.sbuf[6],face_sport.faceId,FACE_ID_LENGTH);
                    uart1.sbuf[38]=Get_Buffer_Checksum(&uart1.sbuf[2],36);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,39);
                    
                    if((uart1.rbuf[6]==0)&&(uart1.rbuf[7]==0)&&(uart1.rbuf[8]==0))  //如果返回的阻力都是0 
                    {
                        /*face_sport.inputSexFlag=1;      //进入输入模式了
                        face_sport.inputWeight = DEFAULT_INPUT_WEIGHT;
                        face_sport.inputSex=0;          //0 男  1女 
                        face_sport.inputTime = INPUT_TIME;  //输入时长限制
                        //clear_screen();*/          
                        //播报请去体测，不输入
                        memset(&lcd,0x00,sizeof(lcd));
                        memset(&face_sport,0x00,sizeof(face_sport));
                        lcd.refresh=1;
                        rpm.total_cnt=0;
                        sport.watt=0;
                        sport.calorie=0;
                        sport.cal_sum=0;
                        timer.total_time=0;
                        face_sport.noUserFlag=1;
                        face_sport.resDispTime = ERR_DISPLAY_TIME;
                        face_sport.step =ERROR_STEP;
                    }else
                    {
                        //开始测试  
                        face_sport.timeRemain = SPORTING_TIME;                        
                        rpm.total_cnt=0;
                        sport.watt=0;
                        sport.calorie=0;
                        timer.total_time=0;                
                        face_sport.detail=1;                           
                        lcd.refresh=1;
                        memset(face_sport.facePower,0x00,sizeof(face_sport.facePower));
                        memcpy(face_sport.facePower,&uart1.rbuf[6],3);
                        sport.level = face_sport.facePower[0];
                    }
				}break;
				default:break;
		}
		uart1.length=0;
		uart1.rev_flg=0;

	}

}



void Idle_display()
{
#if Device_ID == 0x12		//健身车
    show_char("推胸划船训练器",1,1,ASCII_16_A);
    show_char("训练肌肉:胸部、背部",1,3,ASCII_16_A);

    show_char("使用说明:",1,5,ASCII_16_A);
    show_char("自由模式，自由使用设备进行训练",1,7,ASCII_16_A);
    show_char("测试模式,力量测试，请按测试按键",1,9,ASCII_16_A);
    show_char("根据提示进行测试",1,11,ASCII_16_A);
#endif

#if Device_ID == 0XAF
    show_char("体测中心",1,1,ASCII_16_A);
    show_char("项目:心肺功能",1,3,ASCII_16_A);

    show_char("使用说明:",1,5,ASCII_16_A);
    show_char("电机对应按键,选择使用模式",1,7,ASCII_16_A);
#endif

show_char("心率",80,11,ASCII_16_A);
show_char("    ",80,15,ASCII_16_A);
show_Num(hr.rate,0,80,15, ASCII_8X16); 


}




void test(void)
{
    
    show_char("体测中心",1,1,ASCII_16_A);
    show_char("体测结果-心肺功能",64,3,ASCII_16_A);                    
    show_char("最大摄氧量(绝对):",1,5,ASCII_16_A);
    show_char("最大摄氧量(相对)",1,7,ASCII_16_A);
    show_char("评价等级",1,9,ASCII_16_A);
    show_char("[确定键: 开始]",72,18,ASCII_16_A);  
    lcd.refresh=1;


    


}


//页面显示
void Step_Display(void)
{
    if(lcd.refresh)
    {
        lcd.refresh =0;
        clear_screen();
        lcd.dataChange =1;
    }

    if(face_sport.inputSexFlag ==1)
    {
        if(lcd.dataChange)
        {
            lcd.dataChange=0;
            show_char("测试模式",1,2,ASCII_16_A);    
            show_char("输入性别:",38,10,ASCII_16_A);
            show_char("按+ 男性 按- 女性 确定键提交",20,18,ASCII_16_A); 
        }
        if(face_sport.inputSex ==0)
        {
            show_char("√ 男性  女性",110,10,ASCII_16_A);
        }else{
            show_char("男性  √ 女性",110,10,ASCII_16_A);
        }    
           
    }


    if(face_sport.inputWeightFlag==1)
    {
        if(lcd.dataChange)
        {
            lcd.dataChange=0;
            show_char("测试模式",1,2,ASCII_16_A);        
            show_char("请输入体重:",62,10,ASCII_16_A);
            show_char("按+/-调整体重,按确定提交",28,18,ASCII_16_A);
        }
        show_Num(face_sport.inputWeight,0,150,10,ASCII_8X16);        
        
    }

    if(face_sport.step == INIT_STEP)
    {
            Idle_display();        
    }
    if((face_sport.inputWeightFlag ==0)&&(face_sport.inputSexFlag == 0))        //输入模式下不能显示下面的界面
    {
    
        if(face_sport.step  == SELECT_MODE_STEP)
        {
            if(lcd.dataChange)
            {
                lcd.dataChange=0;
                if(face_sport.mode == MODE_TRAIN)
                {
                    show_char("体测中心",1,1,ASCII_16_A);
                    show_char("项目:心肺功能-训练模式",1,3,ASCII_16_A);                    
                    show_char("说明:",1,5,ASCII_16_A);
                    show_char("本测试可以进行心肺功能训练,请根",1,7,ASCII_16_A);
                    show_char("据提示进行操作",1,9,ASCII_16_A);
                    show_char("[确定键: 开始]",72,18,ASCII_16_A);                      
                }
                else
                {                    
                    show_char("体测中心",1,1,ASCII_16_A);
                    show_char("项目:心肺功能",1,3,ASCII_16_A);                    
                    show_char("测试模式:",1,5,ASCII_16_A);
                    show_char("测试需要进行两次一分钟骑行,中间",1,7,ASCII_16_A);
                    show_char("休息一分钟,根据提示操作",1,9,ASCII_16_A);
                    show_char("[确定键: 开始]",72,18,ASCII_16_A);            
                }
            }
        }

        if(face_sport.step  == SPORTING_STEP)
        {
            if(face_sport.mode == MODE_TRAIN)
            {
                if(lcd.dataChange)
                {
                    lcd.dataChange =0;
                    show_char("自由模式",1,2,ASCII_16_A);
                    show_char("时长",42,8,ASCII_16_A);
                    show_char("距离",112,8,ASCII_16_A);
                    show_char("消耗",170,8,ASCII_16_A);
                    show_char("强度",80,15,ASCII_16_A);
                    show_char("[+-:阻力 确定键: 开始]",36,18,ASCII_16_A);
               }
                show_Time(timer.total_time, 26,11, ASCII_8X16);                                
                show_Num(rpm.distance/10,rpm.distance%10,112,11,ASCII_8X16);
                show_Num(sport.calorie/10,sport.calorie%10,170,11,ASCII_8X16);
                show_char("    ",150,15,ASCII_16_A);
                show_Num(sport.level,0,150,15,ASCII_8X16);                
            }
            else
            {
                if(lcd.dataChange)
                {
                    lcd.dataChange=0;                    
                    if(face_sport.detail == 0)
                    {
                        show_char("请等待",96,7,ASCII_24_A);
                        show_char("测试数据获取中...",64,13,ASCII_16_A);
                    }
                    else
                    {   
                        if((face_sport.detail == 1)||(face_sport.detail == 3))
                        {
                            show_char("体测中心",1,1,ASCII_16_A);
                            show_char("测试模式-心肺功能",1,4,ASCII_16_A);
                            if(face_sport.detail == 1)
                            {
                                show_char("阶段1:请保持健身车45-55转/分钟",1,7,ASCII_16_A);
                            }else
                            {
                                show_char("阶段2:请保持健身车45-55转/分钟",1,7,ASCII_16_A);
                            }
                            show_char("阻力",16,11,ASCII_16_A);
                            show_char("心率",80,11,ASCII_16_A);
                            show_char("倒计时",128,11,ASCII_16_A);
                            show_char("转速",200,11,ASCII_16_A);
                        }
                        if(face_sport.detail ==2)
                        {
                            show_char("体测中心",1,1,ASCII_16_A);
                            show_char("测试模式-心肺功能",1,4,ASCII_16_A);
                            show_char("休息:请休息一分钟,休息完毕后将进",1,7,ASCII_16_A);
                            show_char("行第2阶段测试",1,9,ASCII_16_A);
                            show_char("倒计时",104,12,ASCII_16_A);
                            show_char("[删除键: 返回]",72,18,ASCII_16_A);
                        }

                    } 
                }  
                if((face_sport.detail == 1)||(face_sport.detail == 3))
                {
                    show_char("    ",16,15,ASCII_16_A);
                    show_Num(sport.level,0,16,15, ASCII_8X16); 
                    show_char("    ",80,15,ASCII_16_A);
                    show_Num(hr.rate,0,80,15, ASCII_8X16);                                
                    show_char("     ",128,15,ASCII_8X16); 
                    show_Num(face_sport.timeRemain/100,0,128,15,ASCII_8X16);
                    show_char("     ",200,15,ASCII_8X16); 
                    show_Num(rpm.rate,0,200,15,ASCII_8X16);                
                }
                else if(face_sport.detail == 2)
                {
                    show_char("     ",120,15,ASCII_8X16); 
                    show_Num(face_sport.timeRemain/100,0,120,15,ASCII_8X16); 
                }
            }
        }
    
        if(face_sport.step  == REPORT_STEP)
        {
            if(lcd.dataChange)
            {
                lcd.dataChange=0;
                if(face_sport.mode == MODE_TRAIN)
                {
                    show_char("自由模式",1,2,ASCII_16_A);
                    show_char("运动小结",96,8,ASCII_16_A);
                    
                    show_char("时长",20,12,ASCII_16_A);
                    show_Time(timer.total_time, 4,15, ASCII_8X16);
                    
                    show_char("里程",86,12,ASCII_16_A);
                    show_Num(rpm.distance/10,rpm.distance%10,86,15,ASCII_8X16);
                    
                    show_char("消耗",146,12,ASCII_16_A);
                    show_Num(sport.calorie/10,sport.calorie%10,146,15,ASCII_8X16);

                    if(strlen((char *)face_sport.qrcode.QRCODE))
                    {
                        LED_QRcode_Disp(194,12,(char *)face_sport.qrcode.QRCODE);
                        show_char("微信扫码",194,18,ASCII_16_A);
                    }
                }
                else
                {
                    
                    show_char("体测中心",1,1,ASCII_16_A);
                    show_char("体测结果-心肺功能",64,3,ASCII_16_A);                    
                    show_char("最大摄氧量(绝对):",1,5,ASCII_16_A);
                    show_char("最大摄氧量(相对):",1,7,ASCII_16_A);
                    show_char("评价等级",1,9,ASCII_16_A);
                    show_char("[复位键: 返回]",72,18,ASCII_16_A);  

                    
                    if(strlen((char *)face_sport.qrcode.QRCODE))
                    {
                        LED_QRcode_Disp(168,14,(char *)face_sport.qrcode.QRCODE);
                        show_char("微信扫码",192,14,ASCII_16_A);
                        show_char("查看详情",192,16,ASCII_16_A);
                    }                
                } 
            }  
            if(face_sport.mode == MODE_TEST)
            {
                //这里需要显示2个最大摄氧量
                show_Num(face_sport.res.MaxOxygen/10,face_sport.res.MaxOxygen%10,152,5,ASCII_8X16);
                show_Num(face_sport.res.ReOxygen/10,face_sport.res.ReOxygen%10,152,7,ASCII_8X16);
                show_char((u8 *)face_res_evaluate[face_sport.res.evalue],152,9,ASCII_16_A);
            }
        }
        if(face_sport.step == ERROR_STEP)
        {
            if(lcd.dataChange)
            {
                lcd.dataChange=0;
                if(face_sport.noUserFlag)
                {                    
                    show_char("缺少体重数据",56,6,ASCII_24_A);
                    show_char("请先进行[身高体重体成分]测试",16,11,ASCII_16_A);
                    show_char("[删除键: 返回]",72,18,ASCII_16_A);
                }
                else
                {
                    show_char("网络错误",80,6,ASCII_24_A);
                    show_char("请按测试键重新启动功能",40,11,ASCII_16_A);
                    show_char("或直接使用设备自由训练",40,13,ASCII_16_A);
                    show_char("[删除键: 返回]",72,18,ASCII_16_A);
                }
            }
        }
    }   
}


void clean_face_sport(void)
{
    memset(&lcd,0x00,sizeof(lcd));
    memset(&face_sport,0x00,sizeof(face_sport));
    lcd.refresh=1;
    rpm.total_cnt=0;
    rpm.Back_cnts=0;
    rpm.rate=0;
    rpm.speed=0;
    rpm.total_miles=0;
    rpm.distance=0;
    sport.start=1;sport.resume=0;
    sport.calorie=0;
    sport.cal_sum=0;
    sport.watt=0;

    timer.second_flg=1;
    timer.total_time=0;
    sport.level=1;
    
}


void face_sport_timer_handler(void)
{

    if(face_sport.timeDelay)   face_sport.timeDelay--;      //重发
    if(face_sport.resDispTime)  face_sport.resDispTime--;   //展示结果
    if((face_sport.resDispTime == 0)&&(face_sport.step ==ERROR_STEP))
    {
        clean_face_sport();
    }
    if((face_sport.resDispTime== 0)&&(face_sport.step == REPORT_STEP))
    {
        clean_face_sport();
    }

    if((face_sport.inputSexFlag==0)&&(face_sport.inputWeightFlag==0))
    {
        if(face_sport.timeRemain) face_sport.timeRemain--;          //自由运动模式下 运动超时时间减少
    }

    if(face_sport.inputTime)
    {
        face_sport.inputTime--;
        if((face_sport.inputTime==0)&&((face_sport.inputSexFlag!=0)||(face_sport.inputWeightFlag!=0)))
        {
            face_sport.inputSexFlag=0;
            face_sport.inputWeightFlag=0;
            rpm.total_cnt=0;
            lcd.refresh=1;
        }
    }  
}




void face_sport_test(void)
{
    if((face_sport.step == SPORTING_STEP)&&(face_sport.mode == MODE_TEST))
    {
        if((face_sport.inputSexFlag==0)&&(face_sport.inputWeightFlag==0))
        {
            if(face_sport.timeRemain == 0) 
            {
                if(face_sport.detail ==1)
                {
                    lcd.refresh=1;
                    face_sport.detail=2;
					sport.level = face_sport.facePower[1];   
                    face_sport.firstHeart=hr.rate;
                    face_sport.timeRemain =SPORTING_TIME;
                    return;
                }
                if(face_sport.detail ==2)
                {
                    lcd.refresh=1;
                    face_sport.detail=3;
					sport.level = face_sport.facePower[2];
                    face_sport.timeRemain =SPORTING_TIME;
                    return;
                }
                if(face_sport.detail ==3)
                {
                    lcd.refresh=1;
                    face_sport.secondHeart=hr.rate;
                    face_sport.detail=0;
                    face_sport.err_count=0;
                    face_sport.resDispTime = RESOULT_DISP_TIME;
                    face_sport.step = REPORT_STEP;
                    return;
                }              
            }
              
        }
    }
}


void face_sport_handler(void)
{  
    if(face_sport.mode == MODE_TRAIN)   //自由运动模式
    {
        switch(face_sport.step)
        {

            case SPORTING_STEP:
            {
                if(face_sport.start_flag)
                {
                    break;
                }
                if((face_sport.err_count <RESEND_COUNT)&&(face_sport.timeDelay ==0)&&(face_sport.start_flag==0))
                {
                	uart1.sbuf[0]=0xAA;
        			uart1.sbuf[1]=0x06;
        			uart1.sbuf[2]=0x00;
        			uart1.sbuf[3]=0x02;
        			uart1.sbuf[4]=Device_ID;
        			uart1.sbuf[5]=0xD1;  
                    uart1.sbuf[6]=0x00; 
        			uart1.sbuf[7]=Get_Buffer_Checksum(&uart1.sbuf[2],5);
        			Uart1_Send_N_bytes((u8 *)uart1.sbuf,8);
                    face_sport.err_count++;
                    face_sport.timeDelay = reSendTime;      //如果发送失败 500ms后重发

                    if(face_sport.err_count >=RESEND_COUNT)
                    {

                    }                                                        
                }
            }break;

            case REPORT_STEP:
            {
                if(face_sport.date_flag)
                {               
                    break;
                }
                if((face_sport.err_count <RESEND_COUNT)&&(face_sport.timeDelay ==0)&&(!face_sport.date_flag))
                {
            		#if Machine_Type==KeepFitBike
                        uart1.sbuf[0]=0xAA;
                        uart1.sbuf[1]=0x33;
                        uart1.sbuf[2]=0x00;
                        uart1.sbuf[3]=0x02;
                        uart1.sbuf[4]=Device_ID;
                        uart1.sbuf[5]=0xD2;
                        memcpy(&uart1.sbuf[6],face_sport.faceId,FACE_ID_LENGTH);
                        //uart1.sbuf[4]=0x00;
                        uart1.sbuf[38]=rpm.rate>>8;;
                        uart1.sbuf[39]=rpm.rate;
                        uart1.sbuf[40]=rpm.speed>>8;
                        uart1.sbuf[41]=rpm.speed;
                        uart1.sbuf[42]=sport.watt>>8;
                        uart1.sbuf[43]=sport.watt;
                        uart1.sbuf[44]=sport.level;
                        uart1.sbuf[45]=rpm.distance>>8;
                        uart1.sbuf[46]=rpm.distance;
                        uart1.sbuf[47]=timer.total_time>>8;
                        uart1.sbuf[48]=timer.total_time;
                        uart1.sbuf[49]=sport.calorie>>8;
                        uart1.sbuf[50]=sport.calorie;
                        uart1.sbuf[51]=hr.rate;
                        uart1.sbuf[52]=Get_Buffer_Checksum(&uart1.sbuf[2],50);
                        Uart1_Send_N_bytes((u8 *)uart1.sbuf,53);

                    #endif
                    #if Machine_Type==PowerBike                        
                        uart1.sbuf[0]=0xAA;
                        uart1.sbuf[1]=0x2D;
                        uart1.sbuf[2]=0x00;
                        uart1.sbuf[3]=0x02;
                        uart1.sbuf[4]=Device_ID;
                        uart1.sbuf[5]=0xD2;
                        memcpy(&uart1.sbuf[6],face_sport.faceId,FACE_ID_LENGTH);
                        //uart1.sbuf[4]=0x00;
                        uart1.sbuf[38]=rpm.total_cnt>>8;
                        uart1.sbuf[39]=rpm.total_cnt;
                        uart1.sbuf[40]=sport.watt>>8;
                        uart1.sbuf[41]=sport.watt;
                        uart1.sbuf[42]=sport.calorie>>8;
                        uart1.sbuf[43]=sport.calorie;
                        uart1.sbuf[44]=sport.level;
                        uart1.sbuf[45]=hr.rate;
                        uart1.sbuf[46]=Get_Buffer_Checksum(&uart1.sbuf[2],44);
                        Uart1_Send_N_bytes((u8 *)uart1.sbuf,47);
                    #endif
                    face_sport.err_count++;
                    face_sport.timeDelay = reSendTime;      //如果发送失败 500ms后重发
                     if(face_sport.err_count >=RESEND_COUNT)
                    {
                    }
                }
           }break;
            default:break;

        }
    }
    else if(face_sport.mode == MODE_TEST)  //测试模式
    {
        switch(face_sport.step)
        {
            case SPORTING_STEP:
            {
                if((face_sport.err_count <RESEND_COUNT)&&(face_sport.timeDelay ==0)&&(face_sport.start_flag==0))
                {
                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x06;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xD1;
                    uart1.sbuf[6]=0x01;
                    uart1.sbuf[7]=Get_Buffer_Checksum(&uart1.sbuf[2],5);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,8);
                    face_sport.err_count++;
                    face_sport.timeDelay = reSendTime;      //如果发送失败 500ms后重发
                    if(face_sport.err_count >=RESEND_COUNT)
                    {
                        lcd.refresh=1;
                        face_sport.error =1;
                        face_sport.resDispTime= ERR_DISPLAY_TIME;
                        face_sport.step = ERROR_STEP;
                    }
                }
            }break;         

            case REPORT_STEP:
            if(face_sport.date_flag)
            {
                //face_sport.step = DISPLAY_STEP;
                //lcd.refresh=1;
                //lcd.step = DISPLAY_STEP;               
                break;
            }
            if((face_sport.err_count <RESEND_COUNT)&&(face_sport.timeDelay ==0)&&(face_sport.date_flag==0))
            {
                #if Machine_Type==KeepFitBike
                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x34;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xD2;
                    memcpy(&uart1.sbuf[6],face_sport.faceId,FACE_ID_LENGTH);
                    //uart1.sbuf[4]=0x00;
                    uart1.sbuf[38]=rpm.rate>>8;;
                    uart1.sbuf[39]=rpm.rate;
                    uart1.sbuf[40]=rpm.speed>>8;
                    uart1.sbuf[41]=rpm.speed;
                    uart1.sbuf[42]=sport.watt>>8;
                    uart1.sbuf[43]=sport.watt;
                    uart1.sbuf[44]=sport.level;
                    uart1.sbuf[45]=rpm.distance>>8;
                    uart1.sbuf[46]=rpm.distance;
                    uart1.sbuf[47]=timer.total_time>>8;
                    uart1.sbuf[48]=timer.total_time;
                    uart1.sbuf[49]=sport.calorie>>8;
                    uart1.sbuf[50]=sport.calorie;
                    //uart1.sbuf[51]=hr.rate;
                    uart1.sbuf[51]=face_sport.firstHeart;
                    uart1.sbuf[52]=face_sport.secondHeart;
                    uart1.sbuf[53]=Get_Buffer_Checksum(&uart1.sbuf[2],51);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,54);
                #endif
                #if Machine_Type==PowerBike                        
                    uart1.sbuf[0]=0xAA;
                    uart1.sbuf[1]=0x2D;
                    uart1.sbuf[2]=0x00;
                    uart1.sbuf[3]=0x02;
                    uart1.sbuf[4]=Device_ID;
                    uart1.sbuf[5]=0xD2;
                    memcpy(&uart1.sbuf[6],face_sport.faceId,FACE_ID_LENGTH);
                    uart1.sbuf[38]=rpm.total_cnt>>8;
                    uart1.sbuf[39]=rpm.total_cnt;
                    uart1.sbuf[40]=sport.watt>>8;
                    uart1.sbuf[41]=sport.watt;
                    uart1.sbuf[42]=sport.calorie>>8;
                    uart1.sbuf[43]=sport.calorie;
                    uart1.sbuf[44]=sport.level;
                    uart1.sbuf[45]=hr.rate;
                    uart1.sbuf[46]=Get_Buffer_Checksum(&uart1.sbuf[2],44);
                    Uart1_Send_N_bytes((u8 *)uart1.sbuf,47);                     
                #endif
                face_sport.err_count++;
                face_sport.timeDelay = reSendTime;      //如果发送失败 500ms后重发

                if(face_sport.err_count >=RESEND_COUNT)
                {
                    /*
                    lcd.refresh=1;
                    face_sport.error =1;
                    face_sport.step = ERROR_STEP;
                    face_sport.resDispTime= ERR_DISPLAY_TIME;*/
                }
            }break;
            default:break;
        }
    }   
}




/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

u8 Get_Buffer_Checksum(u8 *buff,u8 len)
{
	u8 i,sum;
	sum = 0;
	for(i=0;i<len;i++)
	{
		sum = sum + buff[i];
	}
	return sum;
}
/******************************************************************************
* Function Name  : None
* Description    : None
* Input           : None
* Output         : None
* Return         : None
*******************************************************************************/

void Flash_Display_RAM(void)
{

}



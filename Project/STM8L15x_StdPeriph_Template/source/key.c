/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/


#include	"key.h"
#include "function.h"
#include "SC09A.h"


_SCANKEY_CTRL_DEF key;




void Key_Init_Param(void)
{
	key.value=KEY_VALUE_NONE;
	key.bk_value=KEY_VALUE_NONE;
	key.step=GetValue_Step;
	key.contime=0;
	key.b_cont_flg=0;

}

void Key_Time_Handler(void)
{
	if(key.contime) key.contime--;
}
/******************************************************************************
* Function Name  : ReadKeyPort
* Description    : 读取端口状态
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 Key_Read_Port(void)
{
    unsigned int SC09_TOUCH_DATA;
	u8	key_value;
	key_value = KEY_VALUE_NONE;

	/*if(Key_1_Val==RESET)
	{
		key_value = 1;
	}
	else if(Key_2_Val==RESET)
	{
		key_value = 2;
	}
	else if(Key_3_Val==RESET)
	{
		key_value = 3;
	}
	else if(Key_4_Val==RESET)
	{
		key_value = 4;
	}
	//if(key_value!=0x00)
	//c_dbg_print("touch key: 0x%2x\r\n",key_value);	
	return key_value;*/
    I2C_ReadDeviceDataTo(CON_ADDR,&SC09_TOUCH_DATA,1);
    if(!(SC09_TOUCH_DATA & 0x0400))
    {
        key_value = KEY_VALUE_TEST;
    }
    if(!(SC09_TOUCH_DATA & 0x0200))
    {
        key_value = KEY_VALUE_EXE;
    }
    if(!(SC09_TOUCH_DATA & 0x0100))
    {
        key_value = KEY_VALUE_CMP;
    }
    if(!(SC09_TOUCH_DATA & 0x0080))
    {       
        key_value = KEY_VALUE_RST;
    }
    if(!(SC09_TOUCH_DATA & 0x0040))
    {
        key_value = KEY_VALUE_DOWN;
    }
     if(!(SC09_TOUCH_DATA & 0x0020))
    {
        key_value = KEY_VALUE_UP;
    }


    
    return key_value;
}
/**********************************************************************************************
* Function Name  : Scankey
* Description    : 按键扫描主程序，使用状态机的方式扫描，注意必须要开启定时并自减:  ScanContime
* Input          : None
* Output         : None
* Return         : None
************************************************************************************************/
void  Key_Scan_Handler(void)
{
	u8 temp;
	switch(key.step)
	{
		case Init_Step:		//开始扫描
		{
			temp=Key_Read_Port();
			if(temp>KEY_VALUE_NONE)
			{
				key.bk_value=temp;
				key.step=Filter_Step;
				key.contime=1;		//用于消抖动
			}
		}break;
		case Filter_Step:		//防抖动扫描
		{
			if(key.contime==0)
			{
				key.step=Init_Step;
				temp=Key_Read_Port();
				if(temp==key.bk_value)
				{
					key.b_cont_flg =0;
					key.value=key.bk_value;		//确认有键按下
					Key_Print_Value(key.value,key.b_cont_flg);	//打印按键值
					key.contime=50;			// 500ms用于扫描判断长按多久触发连续按键。
					key.step=Continue_Step;
				}
			}
		}break;
		case Continue_Step:		//连续按键扫描
		{
			temp=Key_Read_Port();
			if(temp!=key.bk_value)			//连续按键中断则重新扫描
			{
                key.contime=1;
				key.step=ReFilter_Step;
				//key.step=Init_Step;
			}
			else if(key.contime==0)			//连续按键相同，且按的时间到
			{
				key.value=temp;
				key.b_cont_flg = 1;
				Key_Print_Value(key.value,key.b_cont_flg); //打印输出按键
			  key.contime=125;			//用于连续按键之间的触发间隔
            }
		}break;
		case ReFilter_Step:
		{
			if(key.contime==0)	//释放防抖动时间为10ms
			{
				temp=Key_Read_Port();
				if(temp==key.bk_value)	//重新扫描到按键，说明是抖动导致的
				{
					key.step=Continue_Step;
					key.contime=125;
				}
				else	if(temp==KEY_VALUE_NONE)	//按键释放
				{
					key.step=Release_Step;
					key.contime=5;	
				}
				else		//其它按键,需要重新扫描
				{
					key.step=Init_Step;
					key.bk_value = KEY_VALUE_NONE;
				}
			}
		}break;
		case Release_Step:
		{
			if(key.contime==0)
			{
				key.step=Init_Step;
				key.bk_value = KEY_VALUE_NONE;
			}
		}break;


     /*   case GetValue_Step:
        {
            if(key.contime ==0)
            {
                key.contime=10;		//100ms读取一次按键的值
                temp=Key_Read_Port();
    			if(temp>KEY_VALUE_NONE)
    			{
                    key.value=temp;
                    if(key.bk_value != key.value)
                    {
                        key.bk_value = key.value;
                        key.b_cont_flg = 0;
                    }
                    else
                    {
                        key.b_cont_flg = 1;
                    }
    			}
                else
                {
				  key.value=KEY_VALUE_NONE;
				  key.bk_value=KEY_VALUE_NONE;
				  key.b_cont_flg = 0;
                }
            }
        }break;*/
	}
}
/******************************************************************************************************
* Function Name  : Print_Key_Value
* Description    : 通过串口打印按键消息
* Input          : None
* Output         : None
* Return         : None
******************************************************************************************************/
void Key_Print_Value(u8 keyval , u8 contkey)		//按键值打印
{
    if (contkey) c_dbg_print("cont key--");
		switch(keyval)
    {
			case KEY_VALUE_UP:	c_dbg_print("[KEY]: Press UP key\r\n");break;
			case KEY_VALUE_DOWN:		c_dbg_print("[KEY]: Press DOWN key\r\n");break;
			case KEY_VALUE_TEST:		c_dbg_print("[KEY]: Press MODE key\r\n");break; 			
			case KEY_VALUE_RST: 	c_dbg_print("[KEY]: Press RST key\r\n");break;
			default: c_dbg_print("[KEY]: Press %d key\r\n",keyval);break;

    }
}


















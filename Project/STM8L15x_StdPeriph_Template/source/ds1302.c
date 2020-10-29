/*-----------------------------------------------
  项目：鱼缸控制器程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2014.7.1
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include	"ds1302.h"

                  		//秒   分    时   日     月   星期    年
u8 const init_time[] = {0x00, 0x00, 0x12, 0x01, 0x01, 0x05, 0x16};


_DS1302_CTRL_DEF_ ds1302;


/**************************************
延时X微秒
不同的工作环境,需要调整此函数
**************************************/
void Delay_NOP(void)
{
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
}
/**************************************
初始化DS1302的端口输入输出
**************************************/
void DS_DATA_Input(void)
{
	DS_DATA_Port->DDR &= (uint8_t)(~(DS_DATA_Pin));
	DS_DATA_Port->CR1 &= (uint8_t)(~(DS_DATA_Pin));
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin));
}
/**************************************
初始化DS1302的端口输入输出
**************************************/
void DS_DATA_Output(void)
{
	DS_DATA_Port->DDR |= (uint8_t)DS_DATA_Pin;	//输出模式
	DS_DATA_Port->CR1 |= (uint8_t)DS_DATA_Pin;	//推挽输出
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin)); //推挽输出
	DS_DATA_Port->ODR &= (uint8_t)(~(DS_DATA_Pin)); //输出低电平
}
/**************************************
初始化DS1302的端口
**************************************/
void DS1302_Init_Port(void)
{
	DS_RST_Port->DDR |= (uint8_t)DS_RST_Pin;	//输出模式
	DS_RST_Port->CR1 |= (uint8_t)DS_RST_Pin;	//推挽输出
	DS_RST_Port->CR2 &= (uint8_t)(~(DS_RST_Pin)); //推挽输出
	DS_RST_Port->ODR &= (uint8_t)(~(DS_RST_Pin)); //输出低电平

	DS_SCLK_Port->DDR |= (uint8_t)DS_SCLK_Pin;	//输出模式
	DS_SCLK_Port->CR1 |= (uint8_t)DS_SCLK_Pin;	//推挽输出
	DS_SCLK_Port->CR2 &= (uint8_t)(~(DS_SCLK_Pin)); //推挽输出
	DS_SCLK_Port->ODR &= (uint8_t)(~(DS_SCLK_Pin)); //输出低电平

	DS_DATA_Port->DDR |= (uint8_t)DS_DATA_Pin;	//输出模式
	DS_DATA_Port->CR1 |= (uint8_t)DS_DATA_Pin;	//推挽输出
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin)); //推挽输出
	DS_DATA_Port->ODR &= (uint8_t)(~(DS_DATA_Pin)); //输出低电平

	DS_RST_Low();
	DS_SCLK_Low();

}

void Ds1302_Time_Handler(void)
{
	if(ds1302.time_cnt) ds1302.time_cnt--;
}


void Ds1302_Serv_Handler(void)
{
	if(ds1302.time_cnt==0)
	{
		ds1302.time_cnt=100;    //250ms取一次时间
		DS1302_GetTime((u8 *)ds1302.now_time);

		//c_dbg_print("[DS1302] 20%2x.%2x.%2x ",ds1302.now_time[6],ds1302.now_time[4],ds1302.now_time[3]);
		//c_dbg_print("%2x:%2x:%2x ",ds1302.now_time[2],ds1302.now_time[1],ds1302.now_time[0]);
		//c_dbg_print("Week: %1x\r\n",ds1302.now_time[5]);
	}
 }
/**************************************
初始化DS1302
**************************************/

void DS1302_Init(void)
{
  u8 i;u8 flag;
  for(i=0;i<7;i++) ds1302.now_time[i]=0;
  ds1302.time_cnt=0;
  DS1302_Init_Port();
	DS1302_WriteData(WRITE_PROTECT,0x00);   //允许写操作
	DS1302_WriteData(Supply_Power, 0xa6);   //一个二极管＋4K电阻充电
	DS1302_WriteData(WRITE_PROTECT,0x80);   //写保护
  flag = DS1302_GetRST_Flag();
	if(flag)		//停止状态,或者数据出错时，需要重新复位
	{
		DS1302_SetTime((u8 *)init_time);      //设置初始时间
    DS1302_SetRST_Flag();   //写入复位标志
	}
  DS1302_GetTime((u8 *)ds1302.now_time);       //读取当前时间
}

/**************************************
从DS1302读1字节数据
**************************************/
u8 DS1302_ReadByte(void)
{
	u8 i;
	u8 dat = 0;
	DS_DATA_Input();
	for (i=0; i<8; i++)             //8位计数器
	{
		DS_SCLK_Low();                   //时钟线拉低
		Delay_NOP();                //延时等待
		dat >>= 1;	                //数据右移一位
		if (DS_DATA_Val) dat |= 0x80;        //读取数据
		DS_SCLK_High();                   //时钟线拉高
		Delay_NOP();                //延时等待
	}
	DS_DATA_Output();
	return dat;
}
/**************************************
向DS1302写1字节数据
**************************************/
void DS1302_WriteByte(u8 dat)
{
	char i;
	DS_DATA_Output();
	for (i=0; i<8; i++)             //8位计数器
	{
		DS_SCLK_Low();                   //时钟线拉低
		Delay_NOP();                //延时等待
		if(dat&0x01)
			DS_DATA_High();				//送出到端口
		else
			DS_DATA_Low();
		dat >>= 1;                 //移出数据
		DS_SCLK_High();                   //时钟线拉高
		Delay_NOP();                //延时等待
	}
}
/**************************************
读DS1302某地址的的数据
**************************************/
u8 DS1302_ReadData(u8 addr)
{
    u8 dat;

    DS_RST_Low();
    Delay_NOP();
    DS_SCLK_Low();
    Delay_NOP();
    DS_RST_High();
    Delay_NOP();
    DS1302_WriteByte(addr);         //写地址
    dat = DS1302_ReadByte();        //读数据
    DS_SCLK_High();
    DS_RST_Low();
    return dat;
}

/**************************************
往DS1302的某个地址写入数据
**************************************/
void DS1302_WriteData(u8 addr, u8 dat)
{
    DS_RST_Low();
    Delay_NOP();
    DS_SCLK_Low();
    Delay_NOP();
    DS_RST_High();
    Delay_NOP();
    DS1302_WriteByte(addr);         //写地址
    DS1302_WriteByte(dat);          //写数据
    DS_SCLK_High();
    DS_RST_Low();
    Delay_NOP();
}
/**************************************
往DS1302的RAM里面获取复位标志
**************************************/
u8 DS1302_GetRST_Flag(void)     //通过对内存进行写操作，判断是否复位过
{
    u8 volatile temp,Reset_flg;
	Reset_flg=0;
	temp = DS1302_ReadData(READ_PARITY_RAM0);
	if(temp!=0xAA) Reset_flg=1;
	temp = DS1302_ReadData(READ_PARITY_RAM1);
	if(temp!=0x55) Reset_flg=1;
	temp = DS1302_ReadData(READ_PARITY_RAM2);
	if(temp!=0x77) Reset_flg=1;
	temp = DS1302_ReadData(READ_PARITY_RAM3);
	if(temp!=0x88) Reset_flg=1;

  temp = DS1302_ReadData(READ_YEAR);  //99年
  if((((temp>>4)&0x0f)>9)||((temp&0x0f)>9))   //如果年出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_MONTH); //12月
  if((((temp>>4)&0x0f)>1)||((temp&0x0f)>9))   //如果月出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_DAY);   //30号
  if((((temp>>4)&0x0f)>3)||((temp&0x0f)>9))   //如果日出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_HOUR);  //24小时
  if((((temp>>4)&0x0f)>2)||((temp&0x0f)>9))   //如果时出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_MINUTE);    //60分钟
  if((((temp>>4)&0x0f)>5)||((temp&0x0f)>9))   //如果分出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_SECOND);    //60秒钟
  if((((temp>>4)&0x07)>5)||((temp&0x0f)>9)||(temp&0x80))   //如果秒出错，需要重新复位计时
  {
      Reset_flg=1;
  }
  return Reset_flg;
}

/**************************************
往DS1302的RAM里面设置复位标志
**************************************/
void DS1302_SetRST_Flag(void)
{
  DS1302_WriteData(WRITE_PROTECT, 0x00);   //允许写操作
	DS1302_WriteData(WRITE_PARITY_RAM0,0xAA);
	DS1302_WriteData(WRITE_PARITY_RAM1,0x55);
	DS1302_WriteData(WRITE_PARITY_RAM2,0x77);
	DS1302_WriteData(WRITE_PARITY_RAM3,0x88);
	DS1302_WriteData(WRITE_PROTECT, 0x80);   //写保护
}
/**************************************
写入初始时间
**************************************/
void DS1302_SetTime(u8 *p)
{
    u8 addr = 0x80;
    u8 n = 7;
    DS1302_WriteData(WRITE_PROTECT, 0x00);   //允许写操作
    while (n--)
    {
        DS1302_WriteData(addr, *p++);
        addr += 2;
    }
    DS1302_WriteData(WRITE_PROTECT, 0x80);   //写保护
}

/**************************************
读取当前时间
**************************************/
void DS1302_GetTime(u8 *p)
{
    u8 addr = 0x81;
    u8 n = 7;
    while (n--)
    {
        *p++ = DS1302_ReadData(addr);
        addr += 2;
    }
}

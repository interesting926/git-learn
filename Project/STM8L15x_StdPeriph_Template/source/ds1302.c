/*-----------------------------------------------
  ��Ŀ����׿���������
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2014.7.1
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
------------------------------------------------*/
#include	"ds1302.h"

                  		//��   ��    ʱ   ��     ��   ����    ��
u8 const init_time[] = {0x00, 0x00, 0x12, 0x01, 0x01, 0x05, 0x16};


_DS1302_CTRL_DEF_ ds1302;


/**************************************
��ʱX΢��
��ͬ�Ĺ�������,��Ҫ�����˺���
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
��ʼ��DS1302�Ķ˿��������
**************************************/
void DS_DATA_Input(void)
{
	DS_DATA_Port->DDR &= (uint8_t)(~(DS_DATA_Pin));
	DS_DATA_Port->CR1 &= (uint8_t)(~(DS_DATA_Pin));
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin));
}
/**************************************
��ʼ��DS1302�Ķ˿��������
**************************************/
void DS_DATA_Output(void)
{
	DS_DATA_Port->DDR |= (uint8_t)DS_DATA_Pin;	//���ģʽ
	DS_DATA_Port->CR1 |= (uint8_t)DS_DATA_Pin;	//�������
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin)); //�������
	DS_DATA_Port->ODR &= (uint8_t)(~(DS_DATA_Pin)); //����͵�ƽ
}
/**************************************
��ʼ��DS1302�Ķ˿�
**************************************/
void DS1302_Init_Port(void)
{
	DS_RST_Port->DDR |= (uint8_t)DS_RST_Pin;	//���ģʽ
	DS_RST_Port->CR1 |= (uint8_t)DS_RST_Pin;	//�������
	DS_RST_Port->CR2 &= (uint8_t)(~(DS_RST_Pin)); //�������
	DS_RST_Port->ODR &= (uint8_t)(~(DS_RST_Pin)); //����͵�ƽ

	DS_SCLK_Port->DDR |= (uint8_t)DS_SCLK_Pin;	//���ģʽ
	DS_SCLK_Port->CR1 |= (uint8_t)DS_SCLK_Pin;	//�������
	DS_SCLK_Port->CR2 &= (uint8_t)(~(DS_SCLK_Pin)); //�������
	DS_SCLK_Port->ODR &= (uint8_t)(~(DS_SCLK_Pin)); //����͵�ƽ

	DS_DATA_Port->DDR |= (uint8_t)DS_DATA_Pin;	//���ģʽ
	DS_DATA_Port->CR1 |= (uint8_t)DS_DATA_Pin;	//�������
	DS_DATA_Port->CR2 &= (uint8_t)(~(DS_DATA_Pin)); //�������
	DS_DATA_Port->ODR &= (uint8_t)(~(DS_DATA_Pin)); //����͵�ƽ

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
		ds1302.time_cnt=100;    //250msȡһ��ʱ��
		DS1302_GetTime((u8 *)ds1302.now_time);

		//c_dbg_print("[DS1302] 20%2x.%2x.%2x ",ds1302.now_time[6],ds1302.now_time[4],ds1302.now_time[3]);
		//c_dbg_print("%2x:%2x:%2x ",ds1302.now_time[2],ds1302.now_time[1],ds1302.now_time[0]);
		//c_dbg_print("Week: %1x\r\n",ds1302.now_time[5]);
	}
 }
/**************************************
��ʼ��DS1302
**************************************/

void DS1302_Init(void)
{
  u8 i;u8 flag;
  for(i=0;i<7;i++) ds1302.now_time[i]=0;
  ds1302.time_cnt=0;
  DS1302_Init_Port();
	DS1302_WriteData(WRITE_PROTECT,0x00);   //����д����
	DS1302_WriteData(Supply_Power, 0xa6);   //һ�������ܣ�4K������
	DS1302_WriteData(WRITE_PROTECT,0x80);   //д����
  flag = DS1302_GetRST_Flag();
	if(flag)		//ֹͣ״̬,�������ݳ���ʱ����Ҫ���¸�λ
	{
		DS1302_SetTime((u8 *)init_time);      //���ó�ʼʱ��
    DS1302_SetRST_Flag();   //д�븴λ��־
	}
  DS1302_GetTime((u8 *)ds1302.now_time);       //��ȡ��ǰʱ��
}

/**************************************
��DS1302��1�ֽ�����
**************************************/
u8 DS1302_ReadByte(void)
{
	u8 i;
	u8 dat = 0;
	DS_DATA_Input();
	for (i=0; i<8; i++)             //8λ������
	{
		DS_SCLK_Low();                   //ʱ��������
		Delay_NOP();                //��ʱ�ȴ�
		dat >>= 1;	                //��������һλ
		if (DS_DATA_Val) dat |= 0x80;        //��ȡ����
		DS_SCLK_High();                   //ʱ��������
		Delay_NOP();                //��ʱ�ȴ�
	}
	DS_DATA_Output();
	return dat;
}
/**************************************
��DS1302д1�ֽ�����
**************************************/
void DS1302_WriteByte(u8 dat)
{
	char i;
	DS_DATA_Output();
	for (i=0; i<8; i++)             //8λ������
	{
		DS_SCLK_Low();                   //ʱ��������
		Delay_NOP();                //��ʱ�ȴ�
		if(dat&0x01)
			DS_DATA_High();				//�ͳ����˿�
		else
			DS_DATA_Low();
		dat >>= 1;                 //�Ƴ�����
		DS_SCLK_High();                   //ʱ��������
		Delay_NOP();                //��ʱ�ȴ�
	}
}
/**************************************
��DS1302ĳ��ַ�ĵ�����
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
    DS1302_WriteByte(addr);         //д��ַ
    dat = DS1302_ReadByte();        //������
    DS_SCLK_High();
    DS_RST_Low();
    return dat;
}

/**************************************
��DS1302��ĳ����ַд������
**************************************/
void DS1302_WriteData(u8 addr, u8 dat)
{
    DS_RST_Low();
    Delay_NOP();
    DS_SCLK_Low();
    Delay_NOP();
    DS_RST_High();
    Delay_NOP();
    DS1302_WriteByte(addr);         //д��ַ
    DS1302_WriteByte(dat);          //д����
    DS_SCLK_High();
    DS_RST_Low();
    Delay_NOP();
}
/**************************************
��DS1302��RAM�����ȡ��λ��־
**************************************/
u8 DS1302_GetRST_Flag(void)     //ͨ�����ڴ����д�������ж��Ƿ�λ��
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

  temp = DS1302_ReadData(READ_YEAR);  //99��
  if((((temp>>4)&0x0f)>9)||((temp&0x0f)>9))   //����������Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_MONTH); //12��
  if((((temp>>4)&0x0f)>1)||((temp&0x0f)>9))   //����³�����Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_DAY);   //30��
  if((((temp>>4)&0x0f)>3)||((temp&0x0f)>9))   //����ճ�����Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_HOUR);  //24Сʱ
  if((((temp>>4)&0x0f)>2)||((temp&0x0f)>9))   //���ʱ������Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_MINUTE);    //60����
  if((((temp>>4)&0x0f)>5)||((temp&0x0f)>9))   //����ֳ�����Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  temp = DS1302_ReadData(READ_SECOND);    //60����
  if((((temp>>4)&0x07)>5)||((temp&0x0f)>9)||(temp&0x80))   //����������Ҫ���¸�λ��ʱ
  {
      Reset_flg=1;
  }
  return Reset_flg;
}

/**************************************
��DS1302��RAM�������ø�λ��־
**************************************/
void DS1302_SetRST_Flag(void)
{
  DS1302_WriteData(WRITE_PROTECT, 0x00);   //����д����
	DS1302_WriteData(WRITE_PARITY_RAM0,0xAA);
	DS1302_WriteData(WRITE_PARITY_RAM1,0x55);
	DS1302_WriteData(WRITE_PARITY_RAM2,0x77);
	DS1302_WriteData(WRITE_PARITY_RAM3,0x88);
	DS1302_WriteData(WRITE_PROTECT, 0x80);   //д����
}
/**************************************
д���ʼʱ��
**************************************/
void DS1302_SetTime(u8 *p)
{
    u8 addr = 0x80;
    u8 n = 7;
    DS1302_WriteData(WRITE_PROTECT, 0x00);   //����д����
    while (n--)
    {
        DS1302_WriteData(addr, *p++);
        addr += 2;
    }
    DS1302_WriteData(WRITE_PROTECT, 0x80);   //д����
}

/**************************************
��ȡ��ǰʱ��
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

#include <stdlib.h>
#include "stm8l15x.h"
#include "timer.h"
#include "JLX256160G.h"
#include "chinese_code.h"
#include "QR_Encode.h"
#include "uart.h"
#include "GT30L24T3Y.h"


/*延时：1 毫秒的 i 倍*/
void delay(int i)
{
    delay_ms(i);
}


void LCD_GPIO_Init(void)
{
	GPIO_Init(LCD_CS_PORT, LCD_PIN_CS, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(LCD_SDA_PORT, LCD_PIN_SDA, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(LCD_GPIO_PORT, LCD_PIN_SCLK, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(LCD_GPIO_PORT, LCD_PIN_RS, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(LCD_GPIO_PORT, LCD_PIN_RST, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(LCD_BACK_LIGHT_PORT,LCD_BACK_LIGHT_pin, GPIO_Mode_Out_PP_Low_Slow);
	
}


void LCD_GPIO_Sleep(void)
{
	GPIO_Init(LCD_CS_PORT, LCD_PIN_CS, GPIO_Mode_Out_OD_Low_Slow);
	GPIO_Init(LCD_SDA_PORT, LCD_PIN_SDA, GPIO_Mode_Out_OD_Low_Slow);
	GPIO_Init(LCD_GPIO_PORT, LCD_PIN_SCLK, GPIO_Mode_Out_OD_Low_Slow);
	GPIO_Init(LCD_GPIO_PORT, LCD_PIN_RS, GPIO_Mode_Out_OD_Low_Slow);
    GPIO_Init(LCD_GPIO_PORT, LCD_PIN_RST, GPIO_Mode_Out_OD_Low_Slow);
    GPIO_Init(LCD_BACK_LIGHT_PORT,LCD_BACK_LIGHT_pin, GPIO_Mode_Out_OD_Low_Slow);

}

//写指令到 LCD 模块
void transfer_command_lcd(int data1)
{
    char i;

    GPIO_ResetBits(LCD_CS_PORT,LCD_PIN_CS);
    GPIO_ResetBits(LCD_GPIO_PORT,LCD_PIN_RS);
    for(i=0;i<8;i++)
    {
        GPIO_ResetBits(LCD_GPIO_PORT,LCD_PIN_SCLK);
        if(data1&0x80) 
        {
            GPIO_SetBits(LCD_SDA_PORT, LCD_PIN_SDA);

        }
        else
        {
            GPIO_ResetBits(LCD_SDA_PORT, LCD_PIN_SDA);
            
        }
         GPIO_SetBits(LCD_GPIO_PORT, LCD_PIN_SCLK);
        data1<<=1;
    }
    GPIO_SetBits(LCD_CS_PORT,LCD_PIN_CS);
    
}


//写数据到 LCD 模块
void transfer_data_lcd(int data1)
{
    char i;

    GPIO_ResetBits(LCD_CS_PORT,LCD_PIN_CS);
    GPIO_SetBits(LCD_GPIO_PORT,LCD_PIN_RS);
    for(i=0;i<8;i++)
    {
        GPIO_ResetBits(LCD_GPIO_PORT,LCD_PIN_SCLK);
        if(data1&0x80) 
        {
            GPIO_SetBits(LCD_SDA_PORT, LCD_PIN_SDA);

        }
        else
        {
            GPIO_ResetBits(LCD_SDA_PORT, LCD_PIN_SDA);           
        }
         GPIO_SetBits(LCD_GPIO_PORT, LCD_PIN_SCLK);
        data1<<=1;
    }
     GPIO_SetBits(LCD_CS_PORT,LCD_PIN_CS);
    
}





void initial_lcd()
{

    GPIO_ResetBits(LCD_GPIO_PORT, LCD_PIN_RST);
    delay(100);
    GPIO_SetBits(LCD_GPIO_PORT,LCD_PIN_RST);
    delay(100);
    transfer_command_lcd(0x30); //EXT=0
    transfer_command_lcd(0x94); //Sleep out
    transfer_command_lcd(0x31); //EXT=1
    transfer_command_lcd(0xD7); //Autoread disable
    transfer_data_lcd(0X9F); //
    transfer_command_lcd(0x32); //Analog SET
    transfer_data_lcd(0x00); //OSC Frequency adjustment
    transfer_data_lcd(0x01); //Frequency on booster capacitors->6KHz
    transfer_data_lcd(0x03); //Bias=1/11
    transfer_command_lcd(0x20); // Gray Level
    transfer_data_lcd(0x01);
    transfer_data_lcd(0x03);
    transfer_data_lcd(0x05);
    transfer_data_lcd(0x07);
    transfer_data_lcd(0x09);
    transfer_data_lcd(0x0b);
    transfer_data_lcd(0x0d);
    transfer_data_lcd(0x10);
    transfer_data_lcd(0x11);
    transfer_data_lcd(0x13);
    transfer_data_lcd(0x15);
    transfer_data_lcd(0x17);
    transfer_data_lcd(0x19);
    transfer_data_lcd(0x1b);
    transfer_data_lcd(0x1d);
    transfer_data_lcd(0x1f);
    transfer_command_lcd(0x30); //EXT=0
    transfer_command_lcd(0x75); //Page Address setting
    transfer_data_lcd(0X00); // XS=0
    transfer_data_lcd(0X28); // XE=159 0x28
    transfer_command_lcd(0x15); //Clumn Address setting
    transfer_data_lcd(0X00); // XS=0
    transfer_data_lcd(0Xff); // XE=256
    transfer_command_lcd(0xBC); //Data scan direction
    transfer_data_lcd(0x00); //MX.MY=Normal
    transfer_data_lcd(0xA6);
    transfer_command_lcd(0xCA); //Display Control
    transfer_data_lcd(0X00); //
    transfer_data_lcd(0X9F); //Duty=160
    transfer_data_lcd(0X20); //Nline=off
    transfer_command_lcd(0xF0); //Display Mode
    transfer_data_lcd(0X10); //10=Monochrome Mode,11=4Gray
    transfer_command_lcd(0x81); //EV control
    transfer_data_lcd(0x38); //VPR[5-0] //0x38
    transfer_data_lcd(0x04); //VPR[8-6]
    transfer_command_lcd(0x20); //Power control
    transfer_data_lcd(0x0B); //D0=regulator ; D1=follower ; D3=booste, on:1 off:0
    delay_us(100);
    transfer_command_lcd(0xAF); //Display on
}


/*写 LCD 行列地址：X 为起始的列地址，Y 为起始的行地址，x_total,y_total 分别为列地址及行地址的起点到终点的差值 */
void lcd_address(int x,int y,int x_total, int y_total)
{
    x=x-1;
    y=y-1;
    transfer_command_lcd(0x15); //Set Column Address
    transfer_data_lcd(x);
    transfer_data_lcd(x+x_total-1);
    transfer_command_lcd(0x75); //Set Page Address
    transfer_data_lcd(y);
    transfer_data_lcd(y+y_total-1);
    transfer_command_lcd(0x30);
    transfer_command_lcd(0x5c);
}



/*清屏*/
void clear_screen(void)
{
    int i,j;
    lcd_address(1,1,256,21);
    for(i=0;i<21;i++)
    {
        for(j=0;j<256;j++)
        {
            transfer_data_lcd(0x00);
        }
    }
}




/*清除指定区域*/
void clear_erea(int x,int y,int end_x,int end_y)
{
    int i,j;
    lcd_address(x,y,end_x,end_y);
    for(i=0;i<end_y;i++)
    {
        for(j=0;j<end_x;j++)
        {
            transfer_data_lcd(0x00);
        }
    }
}


/*
void test(uchar data1,uchar data2)
{
    int i,j;
    lcd_address(1,1,256,21);
    for(i=0;i<20;i++)
    {
        for(j=0;j<255;j++)
        {
            transfer_data_lcd(data1);
            transfer_data_lcd(data2);
        }
    }
}
*/


/*显示 8*16 点阵的汉字或等同于 32*32 点阵的图像*/
void disp_16x8(int x,int y,uchar *dp)
{
    int i,j;
    lcd_address(x,y,16,2);
    for(i=0;i<2;i++)
    {
        for(j=0;j<8;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}



/*显示 32*32 点阵的汉字或等同于 32*32 点阵的图像*/
void disp_16x16(int x,int y,uchar *dp)
{
    int i,j;
    lcd_address(x,y,16,2);
    for(i=0;i<2;i++)
    {
        for(j=0;j<16;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}




/*显示 32*32 点阵的汉字或等同于 32*32 点阵的图像*/
void disp_32x32(int x,int y,uchar *dp)
{
    int i,j;
    lcd_address(x,y,32,4);
    for(i=0;i<4;i++)
    {
        for(j=0;j<32;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}


/*显示 256*160 点阵的图像*/
void disp_256x160(int x,int y,char *dp)
{
    int i,j;
    lcd_address(x,y,256,20);
    for(i=0;i<20;i++)
    {
        for(j=0;j<256;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}




/*显示 256*160 点阵的图像*/
void disp_128x64(int x,int y,char *dp)
{
    int i,j;
    lcd_address(x,y,128,8);
    for(i=0;i<8;i++)
    {
        for(j=0;j<128;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}




void disp_any(int x,int y,int w,int h,unsigned char *dp)
{
    int i,j;
    int height=h/8;
    height=(h%8)? ++height:height;
    lcd_address(x,y,w,height);
    for(i=0;i<height;i++)
    {
        for(j=0;j<w;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }




}


void disp_4gray_256x160(int x,int y,uchar *dp)
{
    int i,j;
    lcd_address(x,y,256,40);
    for(i=0;i<40;i++)
    {
        for(j=0;j<256;j++)
        {
            transfer_data_lcd(*dp);
            dp++;
        }
    }
}



#define QRCODE_COLUMN m_nSymbleSize      //二维码列数
#define QRCODE_ROW   ((m_nSymbleSize/8)+1) //二维码行数  8个像素点为一行 因为都不是8的倍数 所以行数+1 
unsigned char g_qrbuffer[MAX_MODULESIZE * ((MAX_MODULESIZE/8)+1)]={0};


void ledDrawPoint(int pos,unsigned char * databuf)
{

    
    unsigned char temp=0 ,i;
    
    for(i=0;i<8;i++)
   {
        if(databuf[i]==1)
        {
            temp |=(1 << (7-i));
        }
        else
        {
            temp &= ~(1 << (7-i));
        }
        g_qrbuffer[pos]=temp;

    }

}





void qrcodeToChar(){


    int x,y,z,pos=0,bit=0;
    unsigned char charBuff[8]={0};
    int line = m_nSymbleSize/8;
    if(m_nSymbleSize%8) line++;


    for(z=0;z<line;z++)
    {
        for(y=0;y<m_nSymbleSize;y++)
        {
            for(x=z*8;x<(z+1)*8;x++){

               charBuff[bit] = m_byModuleData[x][y];
			   bit++;
            }
            ledDrawPoint(pos,charBuff);
            memset(charBuff,0x00,8);
			bit=0;
            pos++;
           
        }
    }    
      
    
}



/*把Dis_ram的数据刷新到12864中，即可完成显示。*/
void disp_QRCODE(int x,int y,unsigned char * dp)
{
    int i,j;
    lcd_address(x,y,QRCODE_COLUMN,QRCODE_ROW);
    for(i=0;i<QRCODE_ROW;i++)
    {
        
        for(j=0;j<QRCODE_COLUMN;j++)
        {
            transfer_data_lcd(*dp);
			dp++;
        }
    }
}




s32 LED_QRcode_Disp(int x,int y,char *str)
{
	if(EncodeData(str))
	{
        qrcodeToChar();
		disp_QRCODE(x,y,g_qrbuffer);
		return 0;
	}
	else
	{
		printf("转换二维码失败\r\n");
		return -1;
	}
}





unsigned long BitReverse8( unsigned char aNum)
{
    unsigned char Num = 0;
    char i;


    for( i = 0; i < 8; i++ )
    {
       Num |= (aNum&1)<<(7-i);
       aNum >>= 1;
    }
    return Num;
};




void string_BitReverser8(u8 * pDate,unsigned long ascii_kind)
{
  
    int i;
    int length;


    switch(ascii_kind){

        case ASCII_5X7:
        {
            length=8;

        }break;

        case ASCII_7X8:
        {
            length=8;

        }break;

        case ASCII_6X12:
        {
            length=12;

        }break;

        case ASCII_12_A:
        {
            length=26;

        }break;

         case ASCII_16_A:
        {
            length=32;

        }break;

        case ASCII_24_A:
        {
            length=74;

        }break;

        case ASCII_8X16:
        {
            length=16;

        }break;

    }
    for(i=0;i<length;i++)
    {        
        pDate[i] = BitReverse8(pDate[i]);
    }
 
}





void show_char(unsigned char *text,unsigned int x,unsigned int y,unsigned long ascii_kind)
{
    int width;
    int height;
    unsigned char pBits[512];


    switch(ascii_kind)
    {

        case ASCII_5X7:
        {
            width=5;
            height=7;        
        }break;
        
        case ASCII_7X8:
        {
            width=7;
            height=8;        
        }break;
        
        case ASCII_6X12:
        {
            width=6;
            height=12;        
        }break;
        
        case ASCII_12_A:
        {
            width=12;
            height=12;        
        }break;
        
         case ASCII_16_A:
        {
            width=16;
            height=16;        
        }break;
        
        case ASCII_24_A:
        {
            width=24;
            height=24;        
        }break;
        
        case ASCII_8X16:
        {
            width=8;
            height=16;        
        }break;
        default:return;

    }
    

	while(*text!='\0')//判断是否是结尾
	{
		if(*text<0x80){  //ASCII 码 *text是ASCII码

            if((ascii_kind == ASCII_12_A)||(ascii_kind == ASCII_16_A)||(ascii_kind == ASCII_24_A))
            {
                ASCII_GetData(*text, ASCII_8X16, pBits);    //示例, 按实际函数名进行修改
                //DisZK_DZ_W(x,y,8,16, BLACK, WHITE,pBits,1);  //显示8X16点ASCII函数
                string_BitReverser8(pBits,ASCII_8X16);
                disp_any(x,y,8,16,pBits);
                x=x+8;
            }else
            {
    			ASCII_GetData(*text, ascii_kind, pBits);	//示例, 按实际函数名进行修改
    			//DisZK_DZ_W(x,y,8,16, BLACK, WHITE,pBits,1);  //显示8X16点ASCII函数
                string_BitReverser8(pBits,ascii_kind);
                disp_any(x,y,width,height,pBits);
    			x=x+width;
            }
		}else{  //汉字编码*text是汉字编码的高位，*(text+1)是汉字编码的低位
		    if((ascii_kind !=ASCII_12_A)&&(ascii_kind !=ASCII_16_A)&&(ascii_kind !=ASCII_24_A)) return; //如果有汉字并不属于这三种 就退出
		    if(ascii_kind ==ASCII_12_A )
		    {
			    gt_12_GetData(*text, *(text+1),pBits);	//示例, 按实际函数名进行修改
		    }
            else if(ascii_kind ==ASCII_16_A )
            {
                gt_16_GetData(*text, *(text+1),pBits);    //示例, 按实际函数名进行修改
            }
            else if(ascii_kind ==ASCII_24_A )
            {
                gt_24_GetData(*text, *(text+1),pBits);    //示例, 按实际函数名进行修改
            }
			//DisZK_DZ_W(x,y,16,16, BLACK, WHITE,pBits,1);  //显示汉字
			string_BitReverser8(pBits,ascii_kind);
			disp_any(x,y,width,height,pBits);
			x=x+width;
			text++;
		}
		text++;
	}
}



void show_Num(unsigned int num,unsigned int unmFloat,unsigned int x,unsigned int y,unsigned long ascii_kind)
{

    unsigned char str1[20]={0};
	unsigned char str2[20]={0};
    if(unmFloat!=0)
    {
        sprintf((char *)str1,"%d.",num); //将整数转换成str
        sprintf((char *)str2,"%d",unmFloat); //将整数转换成str
        strcat((char *)str1,(char *)str2);
    }else
    {
        sprintf((char *)str1,"%d",num); //将整数转换成str
    }

    show_char(str1,x,y,ascii_kind);
}




void show_Time(unsigned int sec,unsigned int x,unsigned int y,unsigned long ascii_kind)
{
    u8 timeBuf[10]={0};
    u8 houre = sec/3600;
    u8 min = sec/60;
    u8 sec1 = sec%60;
    
    sprintf((char *)timeBuf,"%02d:%02d:%02d",houre,min,sec1); //将整数转换成str 
    show_char(timeBuf,x,y,ascii_kind);
}




void display_test1(void)
{
    show_char("竞赛车-竞赛模式",0,1,ASCII_16_A);
    show_char("连接成功，开始竞赛",60,6,ASCII_16_A);
    show_char("3",110,10,ASCII_24_A);  

    //show_char("深圳市研天科技",1,15,ASCII_16_A);   

}


void display_test2(void)
{
    unsigned long num=135;
	unsigned long numFloat=20;
    show_char("体测中心      27岁 男性",1,1,ASCII_16_A);
    show_char("您的体测结果:",1,3,ASCII_16_A);
    show_char("身高",0,5,ASCII_16_A);
    show_char("172.6cm",40,5,ASCII_8X16);
    show_char("心率",128,5,ASCII_16_A);
    show_char("8",160,5,ASCII_8X16);
    
    show_char("体重",0,7,ASCII_16_A);
    show_char("73.5kg",40,7,ASCII_8X16);
    show_char("骨重量",128,7,ASCII_16_A);
    show_char("8",184,7,ASCII_8X16);


    show_char("BMI",0,9,ASCII_8X16);
    show_char("24.5",40,9,ASCII_8X16);
    show_char("基础代谢",128,9,ASCII_16_A);
    show_char("182l",200,9,ASCII_8X16);

    show_Num(num,numFloat,0,11,ASCII_8X16);

    LED_QRcode_Disp(230,17,"QRCODE TEST");

}


void testMain(void)
{




        
        while(1)
        {

            display_test1();           
            delay_ms(3000);
            clear_screen();
            display_test2();            
            delay_ms(3000);
            clear_screen();
        }

}





































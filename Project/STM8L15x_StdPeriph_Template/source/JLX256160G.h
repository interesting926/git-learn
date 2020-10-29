#ifndef __JLX256160G_H_
#define __JLX256160G_H_


#include "GT30L24T3Y.h"


#define uchar unsigned char
#define uint unsigned int



#define LCD_GPIO_PORT GPIOB
#define LCD_CS_PORT GPIOE
#define LCD_SDA_PORT GPIOC

#define LCD_PIN_CS GPIO_Pin_1       //拉低即可
#define LCD_PIN_SDA GPIO_Pin_4      //串行数据

#define LCD_PIN_SCLK GPIO_Pin_3     //串行时钟
#define LCD_PIN_RS GPIO_Pin_2       //拉低即可
#define LCD_PIN_RST GPIO_Pin_1      //LCD复位

#define LCD_BACK_LIGHT_PORT GPIOD
#define LCD_BACK_LIGHT_pin GPIO_Pin_3
#define LCD_BACKLIGHT_ON GPIO_SetBits(LCD_BACK_LIGHT_PORT,LCD_BACK_LIGHT_pin)
#define LCD_BACKLIGHT_OFF GPIO_ResetBits(LCD_BACK_LIGHT_PORT,LCD_BACK_LIGHT_pin)



void LCD_GPIO_Init(void);
void LCD_GPIO_Sleep(void);


void initial_lcd(void);
void clear_screen(void);
void clear_erea(int x,int y,int end_x,int end_y);
s32 LED_QRcode_Disp(int x,int y,char *str);
void show_char(unsigned char *text,unsigned int x,unsigned int y,unsigned long ascii_kind);
void show_Num(unsigned int num,unsigned int unmFloat,unsigned int x,unsigned int y,unsigned long ascii_kind);
void show_Time(unsigned int sec,unsigned int x,unsigned int y,unsigned long ascii_kind);


void testMain(void);

#endif

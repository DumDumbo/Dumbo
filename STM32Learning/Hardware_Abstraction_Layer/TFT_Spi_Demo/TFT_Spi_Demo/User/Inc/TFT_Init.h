#ifndef __TFT_Init_H
#define __TFT_Init_H


/******************************************************************************
	@Breif：头文件
******************************************************************************/
#include "stdint.h"
#include "USART_Redirect.h"


/******************************************************************************
	@Breif：TFT屏幕相关宏定义
******************************************************************************/
#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0竖屏 1为横屏
#define TFT_W 240
#define TFT_H 240


/******************************************************************************
	@Breif：TFT端口宏定义
******************************************************************************/
//SCL（SCK）端口
#define TFT_SCL_GPIO_PORT GPIOA
#define TFT_SCL_PIN GPIO_PIN_5
//SDA(MOSI)端口
#define TFT_SDA_GPIO_PORT GPIOA
#define TFT_SDA_PIN GPIO_PIN_7
//DC（Dada and Command）端口
#define TFT_DC_GPIO_PORT GPIOB
#define TFT_DC_PIN GPIO_PIN_0
//CS（Chip Select）端口
#define TFT_CS_GPIO_PORT GPIOA
#define TFT_CS_PIN GPIO_PIN_4
//RST端口
#define TFT_RST_GPIO_PORT GPIOB
#define TFT_RST_PIN GPIO_PIN_1


/******************************************************************************
	@Breif：TFT屏幕初始化状态结构体定义
******************************************************************************/
typedef struct __TFT_INIT_STATE_
{
	uint8_t TFT_Init_Flag; //1为初始化成功
}TFT_INIT_STATE;


/******************************************************************************
	@breif：TFT屏幕参数
******************************************************************************/
typedef struct __TFT_PARAMETERS_
{
	uint8_t TFT_Direction;	//0:横屏； 1:竖屏；
	uint16_t TFT_Width;
	uint16_t TFT_Height;
}TFT_PARAMETERS;


/******************************************************************************
	@breif：函数声明
******************************************************************************/
void TFT_Write_Bus(uint8_t dat,uint8_t type);//SPI数据发送函数
void TFT_WR_DATA8(uint8_t dat);//写单字节数据模式
void TFT_WR_DATA(uint16_t dat);//写多字节数据模式
void TFT_WR_REG(uint8_t dat); //写命令模式
void TFT_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void TFT_Display_Direction(uint8_t direction);//TFT显示方向选择函数
void TFT_Clear(void);  	//清屏函数
void TFT_Init(void);//TFT初始化


/******************************************************************************
	@breif：声明全局结构体变量
******************************************************************************/
extern TFT_INIT_STATE TFT_Init_State;
extern TFT_PARAMETERS TFT_Parameters;
	

#endif





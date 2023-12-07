/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    oled.h
  * @brief   This file contains all the function prototypes for
  *          the oled.c file
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#ifndef __OLED_H__
#define __OLED_H__


/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "string.h"
/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */
extern unsigned char heart_shape[];
extern const unsigned char F6x8[][6]; 
extern const unsigned char F8x16[];
extern const unsigned char robot[][8];
extern unsigned char YDLogo50x50[];
extern unsigned char YDLogo25x25[];
/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */
	
void WriteCmd(void);											//被调用的初始化控制命令
void OLED_WR_CMD(uint8_t cmd);						//向设备写控制命令
void OLED_WR_DATA(uint8_t data);					//向设备写数据
void OLED_Init(void);											//初始化oled屏幕
void OLED_Clear(void);										//清屏
void OLED_Clearrow(uint8_t i);						//清行
void OLED_Display_On(void);								//开启OLED显示
void OLED_Display_Off(void);							//关闭OLED显示
void OLED_Set_Pos(uint8_t x, uint8_t y);	//设置光标
void OLED_On(void);												//开启OLED
//在指定位置显示一个字符,包括部分字符
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
//显示数字
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2);
//显示一个字符串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
//显示汉字
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no);
//显示图片
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[]);
//屏幕缓存清屏
void OLED_Clear_GRAM(void);
//屏幕刷新
void OLED_Refresh(void);
void OLED_ver_scroll(void);

void YuanDianLogo(void);									//开机显示源点机器人Logo





/* USER CODE END Prototypes */

#endif /* __OLED_H__ */



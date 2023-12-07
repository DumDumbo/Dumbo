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
	
void WriteCmd(void);											//�����õĳ�ʼ����������
void OLED_WR_CMD(uint8_t cmd);						//���豸д��������
void OLED_WR_DATA(uint8_t data);					//���豸д����
void OLED_Init(void);											//��ʼ��oled��Ļ
void OLED_Clear(void);										//����
void OLED_Clearrow(uint8_t i);						//����
void OLED_Display_On(void);								//����OLED��ʾ
void OLED_Display_Off(void);							//�ر�OLED��ʾ
void OLED_Set_Pos(uint8_t x, uint8_t y);	//���ù��
void OLED_On(void);												//����OLED
//��ָ��λ����ʾһ���ַ�,���������ַ�
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
//��ʾ����
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2);
//��ʾһ���ַ���
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
//��ʾ����
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no);
//��ʾͼƬ
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[]);
//��Ļ��������
void OLED_Clear_GRAM(void);
//��Ļˢ��
void OLED_Refresh(void);
void OLED_ver_scroll(void);

void YuanDianLogo(void);									//������ʾԴ�������Logo





/* USER CODE END Prototypes */

#endif /* __OLED_H__ */



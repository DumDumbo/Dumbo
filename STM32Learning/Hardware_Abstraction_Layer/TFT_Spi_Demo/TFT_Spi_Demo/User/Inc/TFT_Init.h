#ifndef __TFT_Init_H
#define __TFT_Init_H


/******************************************************************************
	@Breif��ͷ�ļ�
******************************************************************************/
#include "stdint.h"
#include "USART_Redirect.h"


/******************************************************************************
	@Breif��TFT��Ļ��غ궨��
******************************************************************************/
#define USE_HORIZONTAL 0  //���ú�������������ʾ 0���� 1Ϊ����
#define TFT_W 240
#define TFT_H 240


/******************************************************************************
	@Breif��TFT�˿ں궨��
******************************************************************************/
//SCL��SCK���˿�
#define TFT_SCL_GPIO_PORT GPIOA
#define TFT_SCL_PIN GPIO_PIN_5
//SDA(MOSI)�˿�
#define TFT_SDA_GPIO_PORT GPIOA
#define TFT_SDA_PIN GPIO_PIN_7
//DC��Dada and Command���˿�
#define TFT_DC_GPIO_PORT GPIOB
#define TFT_DC_PIN GPIO_PIN_0
//CS��Chip Select���˿�
#define TFT_CS_GPIO_PORT GPIOA
#define TFT_CS_PIN GPIO_PIN_4
//RST�˿�
#define TFT_RST_GPIO_PORT GPIOB
#define TFT_RST_PIN GPIO_PIN_1


/******************************************************************************
	@Breif��TFT��Ļ��ʼ��״̬�ṹ�嶨��
******************************************************************************/
typedef struct __TFT_INIT_STATE_
{
	uint8_t TFT_Init_Flag; //1Ϊ��ʼ���ɹ�
}TFT_INIT_STATE;


/******************************************************************************
	@breif��TFT��Ļ����
******************************************************************************/
typedef struct __TFT_PARAMETERS_
{
	uint8_t TFT_Direction;	//0:������ 1:������
	uint16_t TFT_Width;
	uint16_t TFT_Height;
}TFT_PARAMETERS;


/******************************************************************************
	@breif����������
******************************************************************************/
void TFT_Write_Bus(uint8_t dat,uint8_t type);//SPI���ݷ��ͺ���
void TFT_WR_DATA8(uint8_t dat);//д���ֽ�����ģʽ
void TFT_WR_DATA(uint16_t dat);//д���ֽ�����ģʽ
void TFT_WR_REG(uint8_t dat); //д����ģʽ
void TFT_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void TFT_Display_Direction(uint8_t direction);//TFT��ʾ����ѡ����
void TFT_Clear(void);  	//��������
void TFT_Init(void);//TFT��ʼ��


/******************************************************************************
	@breif������ȫ�ֽṹ�����
******************************************************************************/
extern TFT_INIT_STATE TFT_Init_State;
extern TFT_PARAMETERS TFT_Parameters;
	

#endif





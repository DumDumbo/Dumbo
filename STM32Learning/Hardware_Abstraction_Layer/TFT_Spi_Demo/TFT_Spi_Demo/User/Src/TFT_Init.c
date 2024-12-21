#include "TFT_Init.h"
#include "gpio.h"
#include "spi.h"
#include <string.h>  // memset


/******************************************************************************
	@breif:�ṹ��ʵ����
******************************************************************************/
TFT_INIT_STATE TFT_Init_State;
TFT_PARAMETERS TFT_Parameters;


/******************************************************************************
*@brief��SPI�������ݺ���
*@Parameters��dat ��Ҫ���͵���Ϣ��type: 0:��ϢΪ���� 1����ϢΪ����
*@return����			
******************************************************************************/
void TFT_Write_Bus(uint8_t dat,uint8_t type)
{
	// ���SPI״̬�Ƿ����
	if (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		// ����CS����ʼ���ݴ���
		HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_PIN, GPIO_PIN_RESET); 	
		
		// ����DC���ţ�����typeѡ��д�����д���ݣ�������Ԫ�������
    HAL_GPIO_WritePin(TFT_DC_GPIO_PORT, TFT_DC_PIN, (type == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
		
    //����SPI���ͺ�����������
//		HAL_SPI_Transmit(&hspi1, &dat, 1, 100); // ����ʽ����
			HAL_SPI_Transmit_IT(&hspi1, &dat, 1); //�жϷ���
		
																						//DMA���ͣ���δд��
		
		// ����CS�����Խ�������	   
    HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_PIN, GPIO_PIN_SET);
	}		
	
}


/******************************************************************************
*@brief��TFTд�������WR_REG: Write register��
*@Parameters��dat д�������
*@return���� 			
******************************************************************************/
void TFT_WR_REG(uint8_t dat)
{
		TFT_Write_Bus(dat,0);   
}


/******************************************************************************
*@brief��TFTд�����ݺ�����8λ���ݣ�
*@Parameters��dat д������ݣ�8λ��
*@return����  
******************************************************************************/
void TFT_WR_DATA8(uint8_t dat)
{  
	TFT_Write_Bus(dat,1);
}


/******************************************************************************
*@brief��TFTд�����ݺ�����16λ���ݣ�
*@Parameters��dat д������ݣ�16λ��
*@return����    
******************************************************************************/
void TFT_WR_DATA(uint16_t dat)
{
  TFT_WR_DATA8(dat >> 8); 		// ��8λ
  TFT_WR_DATA8(dat & 0xFF);   // ��8λ
}


/******************************************************************************
*@brief��������ʼ�ͽ�����ַ
*@Parameters��x1,x2 �����е���ʼ�ͽ�����ַ
							y1,y2 �����е���ʼ�ͽ�����ַ
*@return����      
******************************************************************************/
void TFT_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	TFT_WR_REG(0x2A);//�е�ַ����
	TFT_WR_DATA8(x1 >> 8);
	TFT_WR_DATA8(x1 & 0xFF);
	TFT_WR_DATA8(x2>>8);
	TFT_WR_DATA8(x2 & 0xFF);
	
	TFT_WR_REG(0x2B);//�е�ַ����
	TFT_WR_DATA8(y1 >> 8);	
	TFT_WR_DATA8(y1 & 0xFF);
	TFT_WR_DATA8(y2 >> 8);	
	TFT_WR_DATA8(y2 & 0xFF);
	
	TFT_WR_REG(0x2C);//������д
}


/******************************************************************************
*@brief��TFT��Ļ����ѡ����
*@Parameters������ѡ��0������ 1��������
*@return����
******************************************************************************/
void TFT_Display_Direction(uint8_t direction)
{
	switch(direction){
		case 0:
			TFT_Parameters.TFT_Width = TFT_W;
			TFT_Parameters.TFT_Height = TFT_H;
			TFT_WR_REG(0x36);
			TFT_WR_DATA8(1<<3);
		break;
		case 1:
			TFT_Parameters.TFT_Width = TFT_H;
			TFT_Parameters.TFT_Height = TFT_W;
			TFT_WR_REG(0x36);
			TFT_WR_DATA8((1<<5)|(1<<6)|(1<<3));
		break;
		case 2:
			TFT_Parameters.TFT_Width = TFT_W;
			TFT_Parameters.TFT_Height = TFT_H;
			TFT_WR_REG(0x36);
			TFT_WR_DATA8((1<<6)|(1<<7)|(1<<3));
		break;
		case 3:
			TFT_Parameters.TFT_Width = TFT_H;
			TFT_Parameters.TFT_Height = TFT_W;
			TFT_WR_REG(0x36);
			TFT_WR_DATA8((1<<7)|(1<<5)|(1<<3));
		break;
		default:break;}
}


/******************************************************************************
*@brief��TFT��Ļ��պ���
*@Parameters����
*@return����
******************************************************************************/
void TFT_Clear(void)
{
  uint16_t i,m;  
	TFT_Address_Set(0,0,TFT_Parameters.TFT_Width-1,TFT_Parameters.TFT_Height-1);
	for(i=0;i<TFT_Parameters.TFT_Width;i++)
	{
    for(m=0;m<TFT_Parameters.TFT_Height;m++)
    {	
			TFT_WR_DATA8(0x00);	//����Ϊ��ɫ
			TFT_WR_DATA8(0x00);
		}
	}
} 


/******************************************************************************
*@brief��TFT��Ļ��ʼ��
*@Parameters����
*@return����
******************************************************************************/
void TFT_Init(void)
{
	// ����¼��ʼ��״̬�Ľṹ��������ֽ�����
	memset(&TFT_Init_State, 0, sizeof(TFT_Init_State));
	
	HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_PIN, GPIO_PIN_RESET); // �͵�ƽ��������λ
  HAL_Delay(10);
	HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_PIN, GPIO_PIN_SET);   // �ߵ�ƽ����λ����
	HAL_Delay(120);

	
	//TFT��ĻGC9A01��ʼ������
 	TFT_WR_REG(0xEF);
	TFT_WR_REG(0xEB);
	TFT_WR_DATA8(0x14); 
	
  TFT_WR_REG(0xFE);			 
	TFT_WR_REG(0xEF); 

	TFT_WR_REG(0xEB);	
	TFT_WR_DATA8(0x14); 

	TFT_WR_REG(0x84);			
	TFT_WR_DATA8(0x40); 

	TFT_WR_REG(0x85);			
	TFT_WR_DATA8(0xFF); 

	TFT_WR_REG(0x86);			
	TFT_WR_DATA8(0xFF); 

	TFT_WR_REG(0x87);			
	TFT_WR_DATA8(0xFF);

	TFT_WR_REG(0x88);			
	TFT_WR_DATA8(0x0A);

	TFT_WR_REG(0x89);			
	TFT_WR_DATA8(0x21); 

	TFT_WR_REG(0x8A);			
	TFT_WR_DATA8(0x00); 

	TFT_WR_REG(0x8B);			
	TFT_WR_DATA8(0x80); 

	TFT_WR_REG(0x8C);			
	TFT_WR_DATA8(0x01); 

	TFT_WR_REG(0x8D);			
	TFT_WR_DATA8(0x01); 

	TFT_WR_REG(0x8E);			
	TFT_WR_DATA8(0xFF); 

	TFT_WR_REG(0x8F);			
	TFT_WR_DATA8(0xFF); 


	TFT_WR_REG(0xB6);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x20);

	TFT_WR_REG(0x36);
	TFT_WR_DATA8(0x08);
	
	TFT_WR_REG(0x3A);			
	TFT_WR_DATA8(0x05); 


	TFT_WR_REG(0x90);			
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x08); 

	TFT_WR_REG(0xBD);			
	TFT_WR_DATA8(0x06);
	
	TFT_WR_REG(0xBC);			
	TFT_WR_DATA8(0x00);	

	TFT_WR_REG(0xFF);			
	TFT_WR_DATA8(0x60);
	TFT_WR_DATA8(0x01);
	TFT_WR_DATA8(0x04);

	TFT_WR_REG(0xC3);			
	TFT_WR_DATA8(0x13);
	
	TFT_WR_REG(0xC4);			
	TFT_WR_DATA8(0x13);

	TFT_WR_REG(0xC9);			
	TFT_WR_DATA8(0x22);

	TFT_WR_REG(0xBE);			
	TFT_WR_DATA8(0x11); 

	TFT_WR_REG(0xE1);			
	TFT_WR_DATA8(0x10);
	TFT_WR_DATA8(0x0E);

	TFT_WR_REG(0xDF);			
	TFT_WR_DATA8(0x21);
	TFT_WR_DATA8(0x0c);
	TFT_WR_DATA8(0x02);

	TFT_WR_REG(0xF0);   
	TFT_WR_DATA8(0x45);
	TFT_WR_DATA8(0x09);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x26);
 	TFT_WR_DATA8(0x2A);

 	TFT_WR_REG(0xF1);    
 	TFT_WR_DATA8(0x43);
 	TFT_WR_DATA8(0x70);
 	TFT_WR_DATA8(0x72);
 	TFT_WR_DATA8(0x36);
 	TFT_WR_DATA8(0x37);  
 	TFT_WR_DATA8(0x6F);


 	TFT_WR_REG(0xF2);   
 	TFT_WR_DATA8(0x45);
 	TFT_WR_DATA8(0x09);
 	TFT_WR_DATA8(0x08);
 	TFT_WR_DATA8(0x08);
 	TFT_WR_DATA8(0x26);
 	TFT_WR_DATA8(0x2A);

 	TFT_WR_REG(0xF3);   
 	TFT_WR_DATA8(0x43);
 	TFT_WR_DATA8(0x70);
 	TFT_WR_DATA8(0x72);
 	TFT_WR_DATA8(0x36);
 	TFT_WR_DATA8(0x37); 
 	TFT_WR_DATA8(0x6F);

	TFT_WR_REG(0xED);	
	TFT_WR_DATA8(0x1B); 
	TFT_WR_DATA8(0x0B); 

	TFT_WR_REG(0xAE);			
	TFT_WR_DATA8(0x77);
	
	TFT_WR_REG(0xCD);			
	TFT_WR_DATA8(0x63);		


	TFT_WR_REG(0x70);			
	TFT_WR_DATA8(0x07);
	TFT_WR_DATA8(0x07);
	TFT_WR_DATA8(0x04);
	TFT_WR_DATA8(0x0E); 
	TFT_WR_DATA8(0x0F); 
	TFT_WR_DATA8(0x09);
	TFT_WR_DATA8(0x07);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x03);

	TFT_WR_REG(0xE8);			
	TFT_WR_DATA8(0x34);

	TFT_WR_REG(0x62);			
	TFT_WR_DATA8(0x18);
	TFT_WR_DATA8(0x0D);
	TFT_WR_DATA8(0x71);
	TFT_WR_DATA8(0xED);
	TFT_WR_DATA8(0x70); 
	TFT_WR_DATA8(0x70);
	TFT_WR_DATA8(0x18);
	TFT_WR_DATA8(0x0F);
	TFT_WR_DATA8(0x71);
	TFT_WR_DATA8(0xEF);
	TFT_WR_DATA8(0x70); 
	TFT_WR_DATA8(0x70);

	TFT_WR_REG(0x63);			
	TFT_WR_DATA8(0x18);
	TFT_WR_DATA8(0x11);
	TFT_WR_DATA8(0x71);
	TFT_WR_DATA8(0xF1);
	TFT_WR_DATA8(0x70); 
	TFT_WR_DATA8(0x70);
	TFT_WR_DATA8(0x18);
	TFT_WR_DATA8(0x13);
	TFT_WR_DATA8(0x71);
	TFT_WR_DATA8(0xF3);
	TFT_WR_DATA8(0x70); 
	TFT_WR_DATA8(0x70);

	TFT_WR_REG(0x64);			
	TFT_WR_DATA8(0x28);
	TFT_WR_DATA8(0x29);
	TFT_WR_DATA8(0xF1);
	TFT_WR_DATA8(0x01);
	TFT_WR_DATA8(0xF1);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x07);

	TFT_WR_REG(0x66);			
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0xCD);
	TFT_WR_DATA8(0x67);
	TFT_WR_DATA8(0x45);
	TFT_WR_DATA8(0x45);
	TFT_WR_DATA8(0x10);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x00);

	TFT_WR_REG(0x67);			
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x01);
	TFT_WR_DATA8(0x54);
	TFT_WR_DATA8(0x10);
	TFT_WR_DATA8(0x32);
	TFT_WR_DATA8(0x98);

	TFT_WR_REG(0x74);			
	TFT_WR_DATA8(0x10);	
	TFT_WR_DATA8(0x85);	
	TFT_WR_DATA8(0x80);
	TFT_WR_DATA8(0x00); 
	TFT_WR_DATA8(0x00); 
	TFT_WR_DATA8(0x4E);
	TFT_WR_DATA8(0x00);					
	
  TFT_WR_REG(0x98);			
	TFT_WR_DATA8(0x3e);
	TFT_WR_DATA8(0x07);

	TFT_WR_REG(0x34);//Tearing Effect Line Off
	TFT_WR_REG(0x21);

	TFT_WR_REG(0x11); 
	HAL_Delay(120); 
	
	TFT_Display_Direction(USE_HORIZONTAL);//������Ļ����
	TFT_Clear();//�������ú�������ڡ�TFT_Display_Direction()��������ʹ�ã�
										//��Ϊ���������Ļ�������ߴ�ȣ�������"Clear()"�����޷���֪��Ļ�ߴ�Ӷ��޷�������

	TFT_WR_REG(0x29); //����ʾ
	HAL_Delay(20);
	
	TFT_Init_State.TFT_Init_Flag = 1;//��־λ
}


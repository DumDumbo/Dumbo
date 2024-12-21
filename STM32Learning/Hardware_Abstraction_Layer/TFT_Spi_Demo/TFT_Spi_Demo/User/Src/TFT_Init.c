#include "TFT_Init.h"
#include "gpio.h"
#include "spi.h"
#include <string.h>  // memset


/******************************************************************************
	@breif:结构体实例化
******************************************************************************/
TFT_INIT_STATE TFT_Init_State;
TFT_PARAMETERS TFT_Parameters;


/******************************************************************************
*@brief：SPI发送数据函数
*@Parameters：dat 需要发送的信息；type: 0:信息为命令 1：信息为数据
*@return：无			
******************************************************************************/
void TFT_Write_Bus(uint8_t dat,uint8_t type)
{
	// 检查SPI状态是否空闲
	if (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		// 拉低CS，开始数据传输
		HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_PIN, GPIO_PIN_RESET); 	
		
		// 设置DC引脚，根据type选择写命令或写数据（采用三元运算符）
    HAL_GPIO_WritePin(TFT_DC_GPIO_PORT, TFT_DC_PIN, (type == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
		
    //调用SPI发送函数发送数据
//		HAL_SPI_Transmit(&hspi1, &dat, 1, 100); // 阻塞式发送
			HAL_SPI_Transmit_IT(&hspi1, &dat, 1); //中断发送
		
																						//DMA发送（暂未写）
		
		// 拉高CS引脚以结束传输	   
    HAL_GPIO_WritePin(TFT_CS_GPIO_PORT, TFT_CS_PIN, GPIO_PIN_SET);
	}		
	
}


/******************************************************************************
*@brief：TFT写命令函数（WR_REG: Write register）
*@Parameters：dat 写入的命令
*@return：无 			
******************************************************************************/
void TFT_WR_REG(uint8_t dat)
{
		TFT_Write_Bus(dat,0);   
}


/******************************************************************************
*@brief：TFT写入数据函数（8位数据）
*@Parameters：dat 写入的数据（8位）
*@return：无  
******************************************************************************/
void TFT_WR_DATA8(uint8_t dat)
{  
	TFT_Write_Bus(dat,1);
}


/******************************************************************************
*@brief：TFT写入数据函数（16位数据）
*@Parameters：dat 写入的数据（16位）
*@return：无    
******************************************************************************/
void TFT_WR_DATA(uint16_t dat)
{
  TFT_WR_DATA8(dat >> 8); 		// 高8位
  TFT_WR_DATA8(dat & 0xFF);   // 低8位
}


/******************************************************************************
*@brief：设置起始和结束地址
*@Parameters：x1,x2 设置列的起始和结束地址
							y1,y2 设置行的起始和结束地址
*@return：无      
******************************************************************************/
void TFT_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	TFT_WR_REG(0x2A);//列地址设置
	TFT_WR_DATA8(x1 >> 8);
	TFT_WR_DATA8(x1 & 0xFF);
	TFT_WR_DATA8(x2>>8);
	TFT_WR_DATA8(x2 & 0xFF);
	
	TFT_WR_REG(0x2B);//行地址设置
	TFT_WR_DATA8(y1 >> 8);	
	TFT_WR_DATA8(y1 & 0xFF);
	TFT_WR_DATA8(y2 >> 8);	
	TFT_WR_DATA8(y2 & 0xFF);
	
	TFT_WR_REG(0x2C);//储存器写
}


/******************************************************************************
*@brief：TFT屏幕方向选择函数
*@Parameters：参数选择（0：横批 1：竖屏）
*@return：无
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
*@brief：TFT屏幕清空函数
*@Parameters：无
*@return：无
******************************************************************************/
void TFT_Clear(void)
{
  uint16_t i,m;  
	TFT_Address_Set(0,0,TFT_Parameters.TFT_Width-1,TFT_Parameters.TFT_Height-1);
	for(i=0;i<TFT_Parameters.TFT_Width;i++)
	{
    for(m=0;m<TFT_Parameters.TFT_Height;m++)
    {	
			TFT_WR_DATA8(0x00);	//清屏为黑色
			TFT_WR_DATA8(0x00);
		}
	}
} 


/******************************************************************************
*@brief：TFT屏幕初始化
*@Parameters：无
*@return：无
******************************************************************************/
void TFT_Init(void)
{
	// 将记录初始化状态的结构体的所有字节清零
	memset(&TFT_Init_State, 0, sizeof(TFT_Init_State));
	
	HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_PIN, GPIO_PIN_RESET); // 低电平，触发复位
  HAL_Delay(10);
	HAL_GPIO_WritePin(TFT_RST_GPIO_PORT, TFT_RST_PIN, GPIO_PIN_SET);   // 高电平，复位结束
	HAL_Delay(120);

	
	//TFT屏幕GC9A01初始化命令
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
	
	TFT_Display_Direction(USE_HORIZONTAL);//设置屏幕方向
	TFT_Clear();//清屏（该函数务必在“TFT_Display_Direction()”函数后使用）
										//因为其包含了屏幕参数（尺寸等），否则"Clear()"函数无法得知屏幕尺寸从而无法清屏）

	TFT_WR_REG(0x29); //打开显示
	HAL_Delay(20);
	
	TFT_Init_State.TFT_Init_Flag = 1;//标志位
}


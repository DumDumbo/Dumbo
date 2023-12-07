/**************************************************************
* @FileName: Clock_selcet.c
* @Author: Ye
* @Version: 1.0
* @Date: 2023/6/17
* @Description: Output clock frequency 72MHz 
***************************************************************/

/*-------------------Headfile Define--------------------*/
#include "Clock_select.h"



/*-------------------Clock control register setting--------------------*/

void Clock_Select(unsigned char PLL)
{
	unsigned int Clock_OK;
	
	// HSE oscillator clock open
	RCC->CR |= 1<<16;  
	// Check HSE oscillator clock ready or not
	while(!(RCC->CR & (1<<17))); 
	
	
	//0x00000400 AHB不分频;APB2不分频;APB1二分频
	RCC->CFGR|=4<<8;			
	//FLASH缓冲
	FLASH_ACR|=0x2;		
	
	
	//HSE输出作为PLL输入时钟
	RCC->CFGR|=1<<16;			
	//选择PLL倍频2--9
	PLL=PLL-2;					
	//PLL九倍频输出
	RCC->CFGR|=PLL<<18;		
	//PLL使能
	RCC->CR|=1<<24;				
	//等待PLL使能成功
	while(!(RCC->CR&(1<<25)));	
	
	
	//选择PLL为系统时钟
	RCC->CFGR|=2<<0;
	//等待系统时钟设置成功
	do							
	{
		Clock_OK=RCC->CFGR&0x0c;
	}
	while(Clock_OK!=0x08);
}
 

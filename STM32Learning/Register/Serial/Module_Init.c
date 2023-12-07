/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: Store main function modules
*************************************************/
#include "main.h"



/***************************************************************************
* @ModuleName: Clock_Select(unsigned char PLL)
* @Description：To Selcet The Frequency Of The System Clock
****************************************************************************/
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


/***************************************************************************
* @ModuleName: SystemInit(void)
* @Description：To Prevent Error
****************************************************************************/
void SystemInit(void)
{
	//do nothing
}


/***************************************************************************
* @ModuleName: Delay_ms
* @Description：To Realize The Delay
****************************************************************************/

void Delay_ms(unsigned int time)
{
	unsigned int num;
	SysTick->VAL = 0;						//计数器清零
	SysTick->LOAD = 1000*time;	//重装载计数值
	SysTick->CTRL |= 1<<0;			//打开定时器使能
	do
	{
		num = SysTick->CTRL;
	}
	while((num & 0x01)&&!(num&(1<<16)));  //等待计数器到0
	SysTick->CTRL &= ~(1<<0);							//关闭计数器
	SysTick->VAL = 0;											//计数器清零
}


/***************************************************************************
* @ModuleName: Delay_ms
* @Description：To Realize The Delay
****************************************************************************/


/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: Store main function modules
*************************************************/

#include "main.h"

//-----------------Prevent error-------------

void SystemInit(void)
{
	//do nothing
}

//-----------------SysTick Delay ms------------------------

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

//-----------------Light Init-----------------------------

void Light_Init(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRH &= ~(15<<(2*10));
	GPIOC->CRH |= 3<<(2*10);
}

//-----------------Light setting-----------------------------

void LED_Output(int LevelMode)
{
	if (LevelMode==1)
	{
		GPIOC->ODR |= 1<<13; // high level
	}
	else if(LevelMode==0)
	{
		GPIOC->ODR &= 0<<13; // low level
	}
	else
	{
	}
}
	

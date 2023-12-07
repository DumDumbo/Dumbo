/****************************************************************
* @FileName: module_init.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/27
* @Description: Store main function modules
*************************************************/

#include "main.h"

/*---------------------------------------------*/

void SystemInit(void)
{
	//do nothing
}

/*-------------------------------------------*/

void delay(void)
{
	long int i,j,y;
	for(i=0;i<1000;++i)
	{
		for (j=0;j<1000;++j)
		{
			y+=y;
		}
	}
	i=0,j=0,y=0;
}

/*-------------------------------------------*/

void Beep_Initialization(void)
{
	//Turn on peripheral clock enable register
	RCC_APB2ENR |= 1<<2;
	
	//Setting portA 
	GPIOA_CRL &= ~(15<<(2*6)); //Reset
	GPIOA_CRL |= 3<<(2*6); // Turn on PortA
}

/*-------------------------------------------*/

void Beep_Output(int LevelMode)
{
	if (LevelMode==1)
	{
		GPIOA_ODR |= 1<<3; // high level
	}
	else if(LevelMode==0)
	{
			GPIOA_ODR &= 0<<3; // low level
	}
	else
	{
	}
}

/*-------------------------------------------*/

void LED_Initialization(void)
{
	//设置reset and clock control 为输出模式
	RCC_APB2ENR |= 1<<4;
	
	//设置GPIOC为输出模式
	GPIOC_CRH &= ~(15<<(2*10));  // 清零
	GPIOC_CRH |= 3<<(2*10);
}

/*-------------------------------------------*/

void LED_Output(int LevelMode)
{
	if (LevelMode==1)
	{
		GPIOC_ODR |= 1<<13; // high level
	}
	else if(LevelMode==0)
	{
		GPIOC_ODR &= 0<<13; // low level
	}
	else
	{
	}
}


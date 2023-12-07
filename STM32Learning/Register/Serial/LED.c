/***********************************************************
* @FileName: LED.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: To Configurate PC13 Port
* @LedWorkingStatusExplanation: SET 0:ligth up 
*																		1：ligth off 
************************************************************/


#include "main.h"

void LED_Init(void)
{
	// GPIOC Clock Enabled
	RCC->APB2ENR |= 1<<4;
	
	//Configured GPIOC 13 
	GPIOC->CRH &= ~(15<<(2*10)); //Reset
	GPIOC->CRH |= 	3<<(2*10);
	
	//Make the LED lights stay off after initialization
//	GPIOC->ODR |= 1<<13;
}

void GPIOCWritePin(const int PortNum, const int State)
{
	if(State==1)
	{
		GPIOC->ODR |= State<<PortNum;
	}
	
	if(State==0)
	{
		GPIOC->ODR &= State<<PortNum;
	}
	
}
	
	

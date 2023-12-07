/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/13
* @Description: Light up the LED through 
								the register strcture packing
*************************************************/


#include "main.h"

//-------------------------------------------------------

void SystemInit()
{
	// do nothing
}

//-------------------------------------------------------

int main(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRH &= ~(15<<(2*10));
	GPIOC->CRH |= 3<<(2*10);
	while(1)
	{
		GPIOC->ODR &= 0<<13; //低电平亮
	}
	
}


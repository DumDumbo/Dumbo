/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Light up a LED 
*************************************************/

/*--------------------------Headfile Define---------------------------------*/
#include "main.h"


/*--------------------------Function List---------------------------------*/


/*****************************************************************************
* @FunctionName： SystemInit
* @Function： To avoid system warning
* @Parameter： None
* @ReturnType：Void
* @Return： None
* @Remark：  
*****************************************************************************/
void SystemInit()
{
	// do nothing
}


/*****************************************************************************
* @FunctionName： main
* @Function： main function(light up a light)
* @Parameter： None
* @ReturnType：Void
* @Return： None
* @Remark：  
*****************************************************************************/
int main(void)
{
  //设置reset and clock control 为输出模式
	RCC_APB2ENR |= 1<<4;
	
	//设置GPIOC为输出模式
	GPIOC_CRH &= ~(15<<(2*10));  // 清零
	GPIOC_CRH |= 3<<(2*10);
	
	//设置PC13输出低电平
	while(1)
	{
		GPIOC_ODR &= 0<<13;
	}
	
}


















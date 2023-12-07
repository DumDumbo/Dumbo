/***************************************************************************
* @ModuleName: Delay_ms
* @Description：To Realize The Delay
****************************************************************************/
#include "Register.h"

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

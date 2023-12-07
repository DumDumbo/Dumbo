/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Select the system clock 
*************************************************/

#include "main.h"


int main()
{
	Clock_Select(9);//九倍频
	Light_Init();
	while(1)
	{
		LED_Output(0);
		Delay_ms(9000);
		LED_Output(1);
		Delay_ms(9000);
	}
}


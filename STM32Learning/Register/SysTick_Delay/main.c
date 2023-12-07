/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: Use systick timer to 
*								achieve precise delay
*************************************************/

#include "main.h"


int main()
{
	Light_Init();
	while(1)
	{
		LED_Output(0);
		Delay_ms(1000); //复位后默认hsi为时钟源，频率为8Hz，分频后为1HZ
		LED_Output(1);
		Delay_ms(1000);
	}
}



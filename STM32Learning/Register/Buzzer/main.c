/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Buzzer use
* @BuzzerPort: PA3
*************************************************/

#include "main.h"

int main(void)
{
	// Beep_init
	Beep_Initialization();
	// LED_init
	LED_Initialization();
	
	while(1)
	{
		Beep_Output(1);
		LED_Output(0);
		delay();
		Beep_Output(0);
		LED_Output(1);
		delay();
		delay();
	}
}





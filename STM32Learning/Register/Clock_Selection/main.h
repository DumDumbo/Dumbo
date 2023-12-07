/************************************************
* @FileName: main.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Define All headfile and function 
*************************************************/


#include "Clock_select.h"
#include "GPIO.h"
#include "SysTick.h"

void Clock_Select(unsigned char PLL);
void SystemInit(void);
void Delay_ms(unsigned int time);
void Light_Init(void);
void LED_Output(int LevelMode);



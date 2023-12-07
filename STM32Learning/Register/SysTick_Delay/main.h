/************************************************
* @FileName: main.h
* @Author: ye 
* @Version: 1.0
* @Date: 2023/5/14
* @Description: Define all header files	
*************************************************/

#include "GPIOx.h"
#include "RCC.h"
#include "SysTick.h"

void SystemInit(void);
void Delay_ms(unsigned int time);
void Light_Init(void);
void LED_Output(int LevelMode);


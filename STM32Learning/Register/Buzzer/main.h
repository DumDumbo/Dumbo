/****************************************************************
* @FileName: main.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: It is used to declare functions,
*								include system header files, 
*								and define constants.
*****************************************************************/

#include "buzzer.h"
#include "led.h"

void SystemInit(void);
void delay(void);
void Beep_Initialization(void);
void Beep_Output(int LevelMode);
void LED_Initialization(void);
void LED_Output(int LevelMode);


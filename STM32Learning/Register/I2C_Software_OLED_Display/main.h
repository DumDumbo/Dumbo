/*****************************************************************************************
* @FileName: main.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @brief: Define All headfile and function 
******************************************************************************************/


#include <stdint.h>
#include "Register.h"


void Clock_Select(unsigned char PLL);
void SystemInit(void);
void Delay_ms(unsigned int time);


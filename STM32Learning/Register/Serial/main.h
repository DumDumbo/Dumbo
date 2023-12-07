/*****************************************************************************************
* @FileName: main.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Define All headfile and function 
******************************************************************************************/


#include <stdint.h>
#include "Register.h"


extern uint8_t data;

void Clock_Select(unsigned char PLL);
void SystemInit(void);
void Delay_ms(unsigned int time);
//
char USART1_ReceiveMsg(void);
void USART1_SendCharacter(char ch);
void USART1_SendString(const char* str);
void USART1_Init(void);
void USART1_IRQHandle(void);
uint32_t USART1_ReceiveData(uint8_t *buffer, uint32_t length);
void SentReceivedMsg(void);
//
void LED_Init(void);
void GPIOCWritePin(const int PortNum,const int State);


/****************************************************************
* @FileName: Buzzer.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Buzzer Initialization
* @BuzzerPort: PA3
*************************************************/

//--------APB2 peripheral clock enable register-----------------
#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018 ) 
	
//--------PortA configuration register
#define GPIOA_CRL (*(volatile unsigned int*)0x40010800)
#define GPIOA_ODR (*(volatile unsigned int*)0x4001080C)

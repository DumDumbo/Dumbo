/************************************************
* @FileName: light.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: LED initialization
* @LEDport: PC13
*************************************************/

//-----AHB peripheral clock enable register -----
#define RCC_APB2ENR	(*(volatile unsigned int*)0x40021018)
	
////-----PortC configuration register -----
#define	GPIOC_CRH	(*(volatile unsigned int*)0x40011004)
#define	GPIOC_ODR	(*(volatile unsigned int*)0x4001100C)



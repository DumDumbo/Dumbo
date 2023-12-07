/************************************************
* @FileName: Clock_select.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/4/26
* @Description: Select the system clock 
*************************************************/


/*----------------Registes define------------------*/
typedef struct
{
	volatile unsigned int CR;
	volatile unsigned int CFGR;
	volatile unsigned int CIR;
	volatile unsigned int APB2RSTR;
	volatile unsigned int APB1RSTR;
	volatile unsigned int AHBENR;
	volatile unsigned int APB2ENR;
	volatile unsigned int APB1ENR;
	volatile unsigned int BDCR;
	volatile unsigned int CSR;
	volatile unsigned int AHBSTR;
	volatile unsigned int CFGR2;
}RCC_TypeDef;

#define RCC ((RCC_TypeDef*)0x40021000)
#define FLASH_ACR	(*(volatile unsigned int*)0x40022000)
/*--------Clock control register(RCC_CR)-----------*/

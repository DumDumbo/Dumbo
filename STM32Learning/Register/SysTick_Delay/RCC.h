/************************************************
* @FileName: GPIOx.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: Reset and Clock Control(RCC) Registers packing
*************************************************/


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


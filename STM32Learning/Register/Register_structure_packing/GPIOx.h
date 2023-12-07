/************************************************
* @FileName: GPIOx.h
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: GPIO Registers packing
*************************************************/


typedef struct
{
	volatile unsigned int CRL;
	volatile unsigned int CRH;
	volatile unsigned int IDR;
	volatile unsigned int ODR;
	volatile unsigned int BSRR;
	volatile unsigned int BRR;
	volatile unsigned int LCKR;
}GPIO_TypeDef;


#define GPIOA ((GPIO_TypeDef*)0x40010800)
#define GPIOB ((GPIO_TypeDef*)0x40010C00)
#define GPIOC ((GPIO_TypeDef*)0x40011000)
#define GPIOD ((GPIO_TypeDef*)0x40011400)
#define GPIOE ((GPIO_TypeDef*)0x40011800)
#define GPIOF ((GPIO_TypeDef*)0x40011C00)
#define GPIOG ((GPIO_TypeDef*)0x40012000)

/*****************************************************************************************
* @Function:
* @Author:
* @Date：
* @Description：Define All Registers
******************************************************************************************/


/***************************************************************************
* @RegisterName: RCC Register
* @Description：To Packing RCC Register 
****************************************************************************/

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
	

/***************************************************************************
* @RegisterName: GPIO Register
* @Description：To Packing GPIO Register 
****************************************************************************/

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

/***************************************************************************
* @RegisterName: SysTick
* @Description：To Packing SysTick's Register 
****************************************************************************/
typedef struct
{
	volatile unsigned int CTRL;  	//控制和状态寄存器
	volatile unsigned int LOAD;  	//重装载寄存器
	volatile unsigned int VAL;  	//当前值寄存器
	volatile unsigned int CALIB;	//校准值寄存器
}SysTick_TypeDef;

//结构体首地址
#define SysTick ((SysTick_TypeDef*)0xE000E010)


/***************************************************************************
* @RegisterName: USART1 registers
* @Description：To Setting USART 
****************************************************************************/

typedef struct
{
	volatile unsigned int SR;
	volatile unsigned int DR;
	volatile unsigned int BRR;
	volatile unsigned int CR1;
	volatile unsigned int CR2;
	volatile unsigned int CR3;
	volatile unsigned int GTPR;
}USART_TypeDef;

#define USART1 ((USART_TypeDef*)0x40013800)
#define USART2 ((USART_TypeDef*)0x40004400)
#define USART3 ((USART_TypeDef*)0x40004800)
#define UART4 ((USART_TypeDef*)0x40004C00)
#define UART5 ((USART_TypeDef*)0x40005000)


/***************************************************************************
* @RegisterName: Alternate Function I/O" (AFIO) register
* @Description：To Configure The Alternate Functions Of Certain I/O Pins.  
****************************************************************************/

typedef struct
{
	volatile unsigned int EVCR;
	volatile unsigned int MAPR;
	volatile unsigned int EXTICR1;
	volatile unsigned int EXTICR2;
	volatile unsigned int EXTICR3;
	volatile unsigned int EXTICR4;
	volatile unsigned int MAPR2;
}AFIO_TypeDef;

#define AFIO ((AFIO_TypeDef*)0x40010000)
	
	

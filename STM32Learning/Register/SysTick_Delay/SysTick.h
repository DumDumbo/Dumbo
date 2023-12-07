/************************************************
* @FileName: main.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: SysTick's Register packing 
*								
*************************************************/


typedef struct
{
	volatile unsigned int CTRL;  	//控制和状态寄存器
	volatile unsigned int LOAD;  	//重装载寄存器
	volatile unsigned int VAL;  	//当前值寄存器
	volatile unsigned int CALIB;	//校准值寄存器
}SysTick_TypeDef;

//结构体首地址
#define SysTick ((SysTick_TypeDef*)0xE000E010)


/***************************************************************************
* @ModuleName: void I2C_Oled_Init(void)
* @Description：To Init I2C_Oled
*
* @Parameters: Fpclk1(APB1总线的时钟频率)=36MHZ
*						   I2C_Speed(希望设置的I2C通信速度)=100kHz
*              设置为标准模式
*
* @Note: I2C模式分类：SM（标准模式）、FM（快速模式）
				 The CCR register must be configured only when the I2C is disabled (PE = 0)
PB6 SCL
PB7 SDA
****************************************************************************/
#include "Register.h"
 
//宏定义OLED的I2C地址
#define OLED_I2C_Address 0x78
// 设置I2C_Speed
unsigned int Fpclk1 = 36000000; // APB1总线的时钟频率
unsigned int I2C_Speed = 100000; // 100kHz


void I2C_Oled_Init(void)
{
	unsigned int prescaler = (Fpclk1 / (I2C_Speed * 2)) - 1;
	
	//打开I2C1使能
	RCC->APB1ENR |= 1<<21;
	//打开GPIOB使能
	RCC->APB2ENR |= 1<<3;
	//将PB6/7端口清零
	GPIOB->CRL &= ~(15<<(2*12));
	GPIOB->CRL &= ~(15<<(2*14));
	//将PB6/7均配置为复用推挽输出
	GPIOB->CRL |= 11<<(2*12);
	GPIOB->CRL |= 11<<(2*14);
	
	/*寄存器I2C->CCR文档中有这一句
	The CCR register must be configured only when the I2C is disabled (PE = 0)
	所以要将CR寄存器的外设使能关掉（即PE）*/
	
	//将I2C1控制寄存器CR1的所有位设置为零，从而禁用I2C1
	I2C1->CR1 = 0; 
	
	// 清除CR2寄存器
	I2C1->CR2 = 0;
	// 设置时钟预分频值
	I2C1->CR2 |= prescaler << 0;
	// 设置I2C模式为SM标准模式
	I2C1->CCR &= ~(1 << 15);
	
	
	
	//使能ACK位，以允许I2C从设备发送应答信号
	I2C1->CR1 |= (1 << 10); 
	//配置寻址模式：
	I2C1->OAR1 = OLED_I2C_Address;
	// 使能I2C1，开始通信
	I2C1->CR1 |= (1 << 0); 
	// 生成起始条件
	I2C1->CR1 |= (1 << 8); 
	// 等待起始条件完成
	while (!(I2C1->SR1 & (1 << 0))); 
	// 将数据发送到I2C数据寄存器
	I2C1->DR = 0x11; 
	// 等待传输完成
	while (!(I2C1->SR1 & (1 << 7))); 
	// 传输完成后，生成停止条件
	I2C1->CR1 |= (1 << 9); 
	

}

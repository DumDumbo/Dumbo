/************************************************
* @FileName: USART1_Init.c
* @Author: ye
* @Version: 1.0
* @Date: 2023/5/14
* @Description: To Configurate USART1 Port
*								Tx：PA9 ；Rx：PA10 
*************************************************/

#include "main.h"


/***************************************************************************
* @FunctionName: void USART1_Init(void)
* @Description：To Init USART1
****************************************************************************/
void USART1_Init(void)
{
	//IO port A clock enabled
	RCC->APB2ENR |= 1<<2;
	
	/* USART1引脚默认为PA9/10，若需更改，到AFIO寄存器进行映射
	** 配置PA9为复用推挽输出(配置成1011)
	** Configure PA9 as: Alternate function output Push-pull
	** Output Frequency： 50MHz
	********************************************************/
  GPIOA->CRH &= ~(15<<(2*2)); //清零
  GPIOA->CRH |= 11<<(2*2); 
	
	/* 配置PA10为浮空输入(配置成：0100)
	** Configure PA10 as: : Floating input (reset state)
	********************************************************/
	GPIOA->CRH &= ~(15<<(2*4));//清零
	GPIOA->CRH |= 4<<(2*4);
	 
	//USART1 Clock Enable(使能USART1的时钟)
	RCC->APB2ENR |= 1<<14;
	
	/*对于STM32F103C8T6，它的时钟频率为72 MHz。
	要设置波特率为9600，我们可以使用以下计算方法(手册里也给出了一部分！)：
	USARTDIV = USART_CLK / (16 * BaudRate) = 72,000,000 / (16 * 9600) ≈ 468.75
	*/
	
	USART1->BRR = 0x271;  //设置波特率为115200
	
	USART1->CR1 &= 0<<12; //  0: "1 Start bit, 8 Data bits, n Stop bit"
	USART1->CR2 &= ~(3<<12);// 00: "1 stop bit"
	
	// Parity control disabled(关闭校验位)
	USART1->CR1 &= 0<<10;
	
	// Transmitter/Receiver enable(使能发送和接收)
	USART1->CR1 |= 1<<3;
	USART1->CR1 |= 1<<2;
	
	// RXNE interrupt enable(使能接收中断)
	USART1->CR1 |= 1<<5;
	
	// 使能USART1
  USART1->CR1 |= 1<<13;
	
}


/***************************************************************************
* @FunctionName: void USART1_SendCharacter(char ch)
* @Description：To Send Character Messages
****************************************************************************/
void USART1_SendCharacter(char ch)
{
	// 等待发送缓冲区为空
   while (!(USART1->SR & 1<<7));
   // 将字符写入发送寄存器
	USART1->DR = ch;
}


/***************************************************************************
* @FunctionName: void USART1_SendString(const char* str)
* @Description：To Send String Messages
* @Tips: The const char* str means it will not modify the data
****************************************************************************/
void USART1_SendString(const char* str) 
{
		int i;
    // 等待发送缓冲区为空
    while (!(USART1->SR & (1 << 7)));

    // 将字符串写入发送寄存器
    for (i = 0; str[i] != '\0'; i++)
    {
        USART1->DR = str[i]; // 将字符写入数据寄存器，自动发送
        while (!(USART1->SR & (1 << 6)));// 等待发送完成		
		}
}

//--------------接收还需要解决-----------
/***************************************************************************
* @FunctionName: void USART1_IRQHandle(void)    IRQ means: Interrupt Request
* @Description：It is a interrupt handling function
****************************************************************************/
// 定义接收缓冲区大小
#define RX_BUFFER_SIZE 128
// 接收缓冲区和索引
volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint32_t rx_buffer_index = 0;

void USART1_IRQHandle(void) {
    if (USART1->SR & (1 << 5)) // 接收到数据
    {
        // 读取接收到的数据
        uint8_t data = USART1->DR;

        // 检查缓冲区是否未满
        if (rx_buffer_index < RX_BUFFER_SIZE - 1) // 预留一个位置来存放字符串的终止符
        {
            // 存储接收到的数据
            rx_buffer[rx_buffer_index++] = data;

            // 检查是否接收到回车和换行符（字符串结束标志）
					if (data == '\r' || data == '\n' || data == '0' )
            {
                // 在字符串末尾添加终止符
                rx_buffer[rx_buffer_index] = '\0';

                // 发送接收到的字符串
                USART1_SendString((const char*)rx_buffer);

                // 重置缓冲区索引
                rx_buffer_index = 0;
            }
        }
    }
}

	
//	if(USART1->SR & 1<<5)		//Received data is ready to be read.
//		{
//			
//			//读取接收寄存器中的数据
//			//uint8_t 
//			data = USART1->DR;	
//		
//			// 将数据放入接收缓冲区
//			if(rx_buffer_index < RX_BUFFER_SIZE)
//			{
//				/*后缀自增运算符
//				**先读取 rx_buffer_index 索引位置的值，
//				**然后将 rx_buffer_index 的值增加 1。*/
//				rx_buffer[rx_buffer_index++] = data;
//				/*这意味着：
//				当 rx_buffer_index 为 0 时，接收到的第一个数据会存储在 rx_buffer[0] 中。
//				当 rx_buffer_index 为 1 时，接收到的第二个数据会存储在 rx_buffer[1] 中。
//				当 rx_buffer_index 为 2 时，接收到的第三个数据会存储在 rx_buffer[2] 中，依此类推。*/
//			}
//			
//			rx = rx_buffer[0];
//			// 将接收到的字符/字符串发送回去
//			USART1_SendString((const char *)rx);     //(const char *)rx_buffer
//			
//			// 数据前移
//			for(x; x<rx_buffer_index; x++)
//			{
//				rx_buffer[x] = rx_buffer[x+1];
//			}
//			
//		}
//}


/***************************************************************************
* @FunctionName: void USART1_IRQHandle(void)    IRQ means: Interrupt Request
* @Description：It is a interrupt handling function
****************************************************************************/ 
uint32_t i;

uint32_t USART1_ReceiveData(uint8_t *buffer, uint32_t length)
{
	// 禁用接收中断以保证数据读取的一致性
    USART1->CR1 &= 0<<5;
    
    // 复制接收缓冲区的数据到目标缓冲区
   
    for (i = 0; i < length && i < rx_buffer_index; i++) {
        buffer[i] = rx_buffer[i];
    }
		
    
    // 已读取的数据出队，其他数据前移
    for (i = 0; i < rx_buffer_index - length; i++) {
        rx_buffer[i] = rx_buffer[i + length];
    }
    rx_buffer_index -= length;
    
    // 重新使能接收中断
    USART1->CR1 |= 1<<5;
    
    return i; // 返回实际读取的数据字节数
}





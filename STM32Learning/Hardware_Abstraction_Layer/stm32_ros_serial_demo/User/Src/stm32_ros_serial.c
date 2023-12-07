/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_ros_serial.c
  * @brief   This file provides code for the communication of the ros 2 stm32
  *          
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */


/* USER CODE BEGIN Includes */
#include "usart.h"
#include "stm32_ros_serial.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */

//声明结构体对象
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;

//全局变量声明
uint8_t Interrupt_Buffer[1];

/* USER CODE END PV */


/* USER CODE BEGIN 0 */



/**************************************************************************
Function: The data sent by the serial port is assigned
Input   : none
Output  : none
函数功能：串口发送的数据进行赋值
入口参数：无
返回  值：无
**************************************************************************/
void data_transition(void)
{
	//获取需要发送的数据的值
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER; 		//Frame_header //帧头
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL;     		//Frame_tail //帧尾
	Send_Data.Sensor_Str.Flag = 2;												//标志位
	Send_Data.Sensor_Str.Status = 2;
	Send_Data.Sensor_Str.X_speed = 1000;
	Send_Data.Sensor_Str.Y_speed = 530;
	Send_Data.Sensor_Str.Z_speed = 590;
	Send_Data.Sensor_Str.U_speed = 3000;
		
	//为需要发送的数据赋值
	Send_Data.buffer[0] = Send_Data.Sensor_Str.Frame_Header; 			//第一位帧头
	Send_Data.buffer[1] = Send_Data.Sensor_Str.Flag;				
	Send_Data.buffer[2] = Send_Data.Sensor_Str.Status;
	//The three-axis speed of / / car is split into two eight digit Numbers
	//小车三轴速度,各轴都拆分为两个8位数据再发送
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed >> 8;  			//X轴高八位
	Send_Data.buffer[4]=Send_Data.Sensor_Str.X_speed & 0xFF;     	//X轴低八位
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed >> 8;  
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Y_speed & 0xFF;   
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed >> 8;   
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Z_speed & 0xFF;  
  Send_Data.buffer[9]=Send_Data.Sensor_Str.U_speed >> 8;   
	Send_Data.buffer[10]=Send_Data.Sensor_Str.U_speed & 0xFF; 
	

  //Data check digit calculation, Pattern 1 is a data check
  //数据校验位计算，模式1是发送数据校验
	Send_Data.buffer[11]=Check_Sum(11,1);      //Check_Sum(8,1); 
	
	Send_Data.buffer[12]=Send_Data.Sensor_Str.Frame_Tail; //Frame_tail //帧尾
}

/**************************************************************************
Function: Send data to host computer
Input   : none
Output  : none
函数功能：串口发送函数
入口参数：无
返 回 值：无
**************************************************************************/
void stm32_2_ros(void)
{
	//数据赋值
	data_transition();
	//数据向上发送
	for(unsigned char i = 0; i<13;i++)
	{
		
		/*第一种发送函数：HAL_UART_Transmit：是一种阻塞函数，它会等待所有数据被发送完成后才返回。
																				 它适用于短期、低频率的发送操作。
				参数：huart：		UART句柄。
							pData：		指向发送数据缓冲区的指针。
							Size：		要发送的数据字节数。
							Timeout：	发送超时时间。
			 返回值：
							return：	返回该函数执行状态。*/
		
//			HAL_UART_Transmit(&huart1,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]),1);
//			HAL_Delay(1);	
	
		/*第二种发送函数：HAL_UART_Transmit_IT：是一个非阻塞的函数，它会立即返回并在后台通过中断来完成数据的发送。
																						适用于大量或高频率的数据传输，因为它不会阻塞主程序的执行。
				参数：huart：		UART句柄。
							pData：		指向发送数据缓冲区的指针。
							Size：		要发送的数据字节数。
			返回值：
							return：	返回该函数执行状态。*/	

			HAL_UART_Transmit_IT(&huart1,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]));
			HAL_Delay(1);
			
		/*第三种发送函数：HAL_UART_Transmit_DMA：是非阻塞的，因为数据传输是通过DMA进行的，不需要CPU的直接参与。
																						 函数返回一个 HAL_StatusTypeDef 枚举，表示操作的执行状态。
				参数：huart：		UART句柄。
							pData：		指向发送数据缓冲区的指针。
							Size：		要发送的数据字节数。
			返回值：
							return：	返回该函数执行状态。*/

//			HAL_UART_Transmit_DMA(&huart1,(uint8_t*)&Send_Data.buffer[i],sizeof(Send_Data.buffer[i]));
//			HAL_Delay(1);
			
		}

}

/**************************************************************************
Function: Calculates the check bits of data to be sent/received
Input   : Count_Number: The first few digits of a check; Mode: 0-Verify the received data, 1-Validate the sent data
Output  : Check result
函数功能：计算要发送/接收的数据校验结果
入口参数：Count_Number：校验的前几位数；Mode：0-对接收数据进行校验，1-对发送数据进行校验
返回  值：校验结果
**************************************************************************/
unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	//Validate the data to be sent
	//对要发送的数据进行校验
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_Data.buffer[k];
	}
	
	//Verify the data received
	//对接收到的数据进行校验
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}

/**************************************************************************
Function: Receive data from host computer
Input   : none
Output  : none
函数功能：串口接收函数
入口参数：无
返 回 值：无
注	  意：选用的数据接收函数放在main.c的函数UserCodeBegin2中，数据在中断回调函数中处理
**************************************************************************/
void receive_data_from_ros()
{
	
	/*第一种接收函数：HAL_UART_Receive()： 通过轮询方式实现，即函数会一直等待直到接收到指定数量的数据或超时。
																			 适用于简单的串口接收操作，但可能会导致CPU的空闲时间浪费在等待接收数据上。
				参数：huart：		UART句柄。
							pData：		指向存储接收数据的缓冲区的指针。。
							Size：		要接收的数据字节数。
							Timeout：	接收超时时间。
			 返回值：
							return：	返回该函数执行状态。*/
		
//			HAL_UART_Receive(&huart1,(uint8_t*)Receive_Data.buffer[i],sizeof(Receive_Data.buffer[i]),1);
//			HAL_Delay(1);	
	
		/*第二种接收函数：HAL_UART_Receive_IT：是一个非阻塞的函数，通过中断方式实现，函数启动后会立即返回，
																						接收完成时会触发中断回调函数。它不会阻塞主程序的执行。
				参数：huart：		UART句柄。
							pData：		指向存储接收数据的缓冲区的指针。
							Size：		要接收的数据字节数。
			返回值：
							return：	返回该函数执行状态。*/	

			HAL_UART_Receive_IT(&huart1,(uint8_t*)Receive_Data.buffer,sizeof(Receive_Data.buffer));
			HAL_Delay(1);
			
		/*第三种接收函数：HAL_UART_Receive_DMA：非阻塞的，通过DMA方式实现，函数启动后会立即返回，接收完成时会触发DMA传输完成中断。
																						 函数返回一个 HAL_StatusTypeDef 枚举，表示操作的执行状态。
				参数：huart：		UART句柄。
							pData：		指向存储接收数据的缓冲区的指针。
							Size：		要接收的数据字节数。
			返回值：
							return：	返回该函数执行状态。*/

//			HAL_UART_Receive_DMA(&huart1,Receive_Data.buffer,100)；
//			HAL_Delay(1);
				 
}

/**************************************************************************
Function: Receive data transformation
Input   : uint8_t Data_High, uint8_t Data_Low
Output  : short transition_16
函数功能：将两个8位数据拼接为16位
入口参数：高八位数据，低八位数据
返 回 值：16位数据 transition——16
**************************************************************************/
short received_data_trans(uint8_t Data_High, uint8_t Data_Low)
{
	short transition_16;   // 中间变量
  transition_16 = 0;
  transition_16 |=  Data_High << 8; //Get the high 8 bits of data   // 将高8位数据左移8位，与高八位数据做或运算
  transition_16 |=  Data_Low;      //Get the lowest 8 bits of data //获取数据的低8位，与低8位数据做或运算
  return transition_16;
}


/**************************************************************************
Function: UART1_Callback_Function
Input   : none
Output  : none
函数功能：HAL_UART_Receive_IT的中断回调函数，缓存为1字节，
					对串口接收的数据进行整合赋值
入口参数：无
返 回 值：无
**************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
	{
		
		if(huart == &huart1) // 如果是串口1
		{
		
			uint8_t check=0,error=1;	//Temporary variable to save the data of the lower machine //临时变量，保存下位机数据
			static int count; 				//Static variable for counting //静态变量，用于计数，静态变量的生命周期在整个程序运行期间
	
	
			// 固定值数据赋值
			Receive_Data.buffer[count] = Interrupt_Buffer[0]; //Fill the array with serial data //串口数据填入数组
			Receive_Data.Control_Str.Frame_Header = Receive_Data.buffer[0]; 	//The first part of the data is the frame header 0X7B //数据的第一位是帧头0X7B
			Receive_Data.Control_Str.Frame_Tail = Receive_Data.buffer[10];  	//The last bit of data is frame tail 0X7D //数据的最后一位是帧尾0X7D
			
			//数据匹配
			//Ensure that the first data in the array is FRAME_HEADER //确保数组第一个数据为FRAME_HEADER
			if(Interrupt_Buffer[0] == FRAME_HEADER || count>0)
				count++;
			else
				count = 0;
	
			if(count == 11) //Verify the length of the packet //验证数据包的长度
				{
					//复位count
					count=0;  //Prepare for the serial port data to be refill into the array //为串口数据重新填入数组做准备
			
				if(Receive_Data.Control_Str.Frame_Tail == FRAME_TAIL) //Verify the frame tail of the packet //验证数据包的帧尾
					{
						check=Check_Sum(9,READ_DATA_CHECK);  //BCC check passes or two packets are interlaced //BCC校验通过或者两组数据包交错
					}
				 
				if(check == Receive_Data.buffer[9])   	// 匹配校验位
					{
						error=0;  //XOR bit check successful //异或位校验成功
					}
				
				if(error == 0)			//无错即开始数据赋值拼接
					{
						Receive_Data.Control_Str.Flag = Receive_Data.buffer[1];    //预留位Flag
						Receive_Data.Control_Str.Status = Receive_Data.buffer[2];	 //预留位Status
						Receive_Data.Control_Str.X_speed = received_data_trans(Receive_Data.buffer[3],Receive_Data.buffer[4]);
						Receive_Data.Control_Str.Y_speed = received_data_trans(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Receive_Data.Control_Str.Z_speed = received_data_trans(Receive_Data.buffer[7],Receive_Data.buffer[8]);
					}			
				}
			// 重新启动串口1的接收中断，准备下一次接收
      HAL_UART_Receive_IT(&huart1, Interrupt_Buffer, sizeof(Interrupt_Buffer));
			}
	}


/* USER CODE END 0 */
	
	
	
	

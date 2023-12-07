/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_ros_serial.h
  * @brief   This file contains all the function prototypes for
  *          the stm32_ros_serial.c file
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#ifndef __STM32_ROS_SERIAL_H__
#define	__STM32_ROS_SERIAL_H__


/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */


/* USER CODE BEGIN PV */
extern uint8_t Interrupt_Buffer[1];  //接收中断缓存大小
/* USER CODE END PV */


/* USER CODE BEGIN Private defines */
#define SEND_DATA_CHECK   1        //Send data check flag bits //发送数据校验标志位
#define READ_DATA_CHECK   0        //Receive data to check flag bits //接收数据校验标志位
#define FRAME_HEADER      0X7B 		 //Frame_header //帧头
#define FRAME_TAIL        0X7D 		 //Frame_tail   //帧尾
#define SEND_DATA_SIZE    13	 		 //发送数据的总字节
#define RECEIVE_DATA_SIZE 11	 		 //接收数据的总字节
	

/*******The structure of the serial port sending data************/
/*******串口发送数据的结构体*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //帧头			//1个字节
		unsigned char Flag; 				//预留标志位//1个字节
		unsigned char Status;				//预留状态位//1个字节
		short X_speed;	            //2 bytes //2个字节
		short Y_speed;              //2 bytes //2个字节
		short Z_speed;              //2 bytes //2个字节
		short U_speed;							//2 bytes //2个字节
		unsigned char Frame_Tail;   //帧尾 //1个字节
	}Sensor_Str;
}SEND_DATA;	

/*******The structure of the serial port receiving data************/
/*******串口接收数据的结构体*************************************/
typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //1 bytes //1个字节 // 帧头
		unsigned char Flag;					//1 bytes //1个字节 // 预留位
		unsigned char Status;				//1 bytes //1个字节 // 预留位
		short X_speed;	            //2 bytes //2个字节 // X轴速度
		short Y_speed;              //2 bytes //2个字节 // Y轴速度
		short Z_speed;              //2 bytes //2个字节 // Z轴速度
		unsigned char Frame_Tail;   //1 bytes //1个字节 // 帧尾
	}Control_Str;
}RECEIVE_DATA;


/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/**************************Function declaration******************************/
/*******************************函数声明*************************************/

unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode);		//声明校验函数

//stm32发送数据至上位机
void data_transition(void);					//数据赋值函数
void stm32_2_ros(void);							//数据向上发送函数

//stm32接收上位机数据
short received_data_trans(uint8_t Data_High, uint8_t Data_Low);		// 数据转换函数
void receive_data_from_ros(void);


/* USER CODE END Prototypes */


#endif



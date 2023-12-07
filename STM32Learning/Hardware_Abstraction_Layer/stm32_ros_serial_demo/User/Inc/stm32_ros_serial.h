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
extern uint8_t Interrupt_Buffer[1];  //�����жϻ����С
/* USER CODE END PV */


/* USER CODE BEGIN Private defines */
#define SEND_DATA_CHECK   1        //Send data check flag bits //��������У���־λ
#define READ_DATA_CHECK   0        //Receive data to check flag bits //��������У���־λ
#define FRAME_HEADER      0X7B 		 //Frame_header //֡ͷ
#define FRAME_TAIL        0X7D 		 //Frame_tail   //֡β
#define SEND_DATA_SIZE    13	 		 //�������ݵ����ֽ�
#define RECEIVE_DATA_SIZE 11	 		 //�������ݵ����ֽ�
	

/*******The structure of the serial port sending data************/
/*******���ڷ������ݵĽṹ��*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //֡ͷ			//1���ֽ�
		unsigned char Flag; 				//Ԥ����־λ//1���ֽ�
		unsigned char Status;				//Ԥ��״̬λ//1���ֽ�
		short X_speed;	            //2 bytes //2���ֽ�
		short Y_speed;              //2 bytes //2���ֽ�
		short Z_speed;              //2 bytes //2���ֽ�
		short U_speed;							//2 bytes //2���ֽ�
		unsigned char Frame_Tail;   //֡β //1���ֽ�
	}Sensor_Str;
}SEND_DATA;	

/*******The structure of the serial port receiving data************/
/*******���ڽ������ݵĽṹ��*************************************/
typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //1 bytes //1���ֽ� // ֡ͷ
		unsigned char Flag;					//1 bytes //1���ֽ� // Ԥ��λ
		unsigned char Status;				//1 bytes //1���ֽ� // Ԥ��λ
		short X_speed;	            //2 bytes //2���ֽ� // X���ٶ�
		short Y_speed;              //2 bytes //2���ֽ� // Y���ٶ�
		short Z_speed;              //2 bytes //2���ֽ� // Z���ٶ�
		unsigned char Frame_Tail;   //1 bytes //1���ֽ� // ֡β
	}Control_Str;
}RECEIVE_DATA;


/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/**************************Function declaration******************************/
/*******************************��������*************************************/

unsigned char Check_Sum(unsigned char Count_Number,unsigned char Mode);		//����У�麯��

//stm32������������λ��
void data_transition(void);					//���ݸ�ֵ����
void stm32_2_ros(void);							//�������Ϸ��ͺ���

//stm32������λ������
short received_data_trans(uint8_t Data_High, uint8_t Data_Low);		// ����ת������
void receive_data_from_ros(void);


/* USER CODE END Prototypes */


#endif



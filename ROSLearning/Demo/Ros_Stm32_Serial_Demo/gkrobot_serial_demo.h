#ifndef __GKROBOT_SERIAL_H_
#define __GKROBOT_SERIAL_H_

/*******
 * @brief:	头文件
 * 			Header file
*********/
#include "ros/ros.h"
#include <iostream>
#include <string.h>
#include <string> 
#include <iostream>
#include <math.h>
#include <stdlib.h>    
#include <unistd.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <serial/serial.h>
#include <fcntl.h>          
#include <stdbool.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/Imu.h>
#include <qrcode_msg/qrcode_msg.h>
#include <thread>
using namespace std;

/*******
 * @brief:	宏定义
 * 			Macro definition
*********/
#define SEND_DATA_CHECK   1          //Send data check flag bits //发送数据校验标志位
#define READ_DATA_CHECK   0          //Receive data to check flag bits //接收数据校验标志位
#define FRAME_HEADER      0X7B       //Frame head //帧头
#define FRAME_TAIL        0X7D       //Frame tail //帧尾
#define RECEIVE_DATA_SIZE 11         //The length of the data sent by the lower computer //下位机发送过来的数据的长度
#define SEND_DATA_SIZE    11         //The length of data sent by ROS to the lower machine //ROS向下位机发送的数据的长度
#define PI 				  3.1415926f //PI //圆周率


/*******
 * @brief:	变量声明
 * 			Variable declaration
*********/


/*******
 * @brief:	协方差矩阵，用于里程计话题数据，用于robt_pose_ekf功能包
 * 			Covariance matrix for speedometer topic data for robt_pose_ekf feature pack
*********/
const double odom_pose_covariance[36]   = {1e-3,    0,    0,   0,   0,    0, 
										      0, 1e-3,    0,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0,  1e3 };

const double odom_pose_covariance2[36]  = {1e-9,    0,    0,   0,   0,    0, 
										      0, 1e-3, 1e-9,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0, 1e-9 };

const double odom_twist_covariance[36]  = {1e-3,    0,    0,   0,   0,    0, 
										      0, 1e-3,    0,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0,  1e3 };
										      
const double odom_twist_covariance2[36] = {1e-9,    0,    0,   0,   0,    0, 
										      0, 1e-3, 1e-9,   0,   0,    0,
										      0,    0,  1e6,   0,   0,    0,
										      0,    0,    0, 1e6,   0,    0,
										      0,    0,    0,   0, 1e6,    0,
										      0,    0,    0,   0,   0, 1e-9} ;


/*******
 * @brief:	速度、位置数据结构体
 * 			Data structure for speed and position
*********/
typedef struct __Vel_Pos_Data_
{
	float X;
	float Y;
	float Z;
}Vel_Pos_Data;


/*******
 * @brief:	IMU数据结构体
 * 			IMU data structure
*********/
// typedef struct __MPU6600_DATA_
// {
// 	short accele_x_data; 
// 	short accele_y_data; 	
// 	short accele_z_data; 
//     short gyros_x_data; 
// 	short gyros_y_data; 	
// 	short gyros_z_data; 

// }MPU6600_DATA;


/*******
 * @brief:	ROS向Stm32发送数据的结构体
 * 			The structure of the ROS to send data to the down machine
*********/
typedef struct _SEND_DATA_  
{
	unsigned char tx[SEND_DATA_SIZE];	//接收缓存数组
	struct _Control_Str_
	{
		unsigned char Frame_Header;		//帧头		//1字节
		unsigned char Flag;				//预留位	//1字节
		unsigned char Status;			//预留位	//1字节
		short X_speed;	       			//小车X轴线速度（ROS坐标系）	//2字节
		short Y_speed;           		//小车Y轴线速度（ROS坐标系）	//2字节
		short Z_speed;         			//小车Z轴角速度（ROS坐标系）	//2字节
		unsigned char Frame_Tail;		//帧尾		//1字节
	}Control_Str;
}SEND_DATA;


/*******
 * @brief:	ROS从Stm32接收数据的结构体
 * 			The structure of ROS receiving data from Stm32
*********/
typedef struct _RECEIVE_DATA_     
{
	unsigned char rx[RECEIVE_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header;		//帧头		//1字节
		unsigned char Flag;				//预留位	//1字节
		unsigned char Status;			//预留位	//1字节
		short X_speed;	       			//小车X轴线速度（ROS坐标系）	//2字节
		short Y_speed;           		//小车Y轴线速度（ROS坐标系）	//2字节
		short Z_speed;         			//小车Z轴角速度（ROS坐标系）	//2字节
		unsigned char Frame_Tail;		//帧尾		//1字节
	}Sensor_Str;
}RECEIVE_DATA;


/*******
 * @brief:	机器人底盘类，使用构造函数初始化数据和发布话题等
 * 			The robot chassis class uses constructors to initialize data, publish topics, etc
*********/
class turn_on_robot
{
	public:
		void gkrobot_Init();  			//Constructor //构造函数 //初始化相关参数
		serial::Serial Stm32_Serial; 	//Declare a serial object //声明串口对象 
		void serial_ros2stm32();		//Sending data //ROS向Stm32发送数据函数
		void serial_data_pub();			//Receiving data and pub //将接收到的数据按要求发布话题
	private:
		ros::NodeHandle n; //Create a ROS node handle //创建ROS节点句柄

		ros::Subscriber Cmd_Vel_Sub , Qr_Code_Sub; //Initialize the topic subscriber //初始化话题订阅者
		ros::Time _Now, _Last_Time;  //Time dependent, used for integration to find displacement (mileage) //时间相关，用于积分求位移(里程)
		float Sampling_Time;         //Sampling time, used for integration to find displacement (mileage) //采样时间，用于积分求位移(里程)
        
		

		ros::Publisher odom_publisher;
		void Publish_Odom();//里程计数据发布函数

		bool serial_data_from_stm32();	//Receiving data //ROS从Stm32接收数据函数
		void Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux);	//速度话题订阅回调函数
		void Qr_Code_Callback(const qrcode_msg::qrcode_msg &qrmsg);		//二维码数据话题订阅回调函数

		//接收速度数据转化函数，用于里程计信息发布
		float Odom_Trans(uint8_t Data_High,uint8_t Data_Low);

        unsigned char Check_Sum(unsigned char Count_Number,unsigned char mode); //BBC check function //BBC校验函数 

           
        //Initialize the topic publisher //初始化话题发布者
		// ros::Publisher odom_publisher, imu_publisher, voltage_publisher;

		//Define the related variables //定义相关变量
        string usart_port_name, robot_frame_id, gyro_frame_id, odom_frame_id;
        int serial_baud_rate;      //Serial communication baud rate //串口通信波特率

		//实例化对象
        RECEIVE_DATA Receive_Data; //The serial port receives the data structure //串口接收数据结构体
        SEND_DATA Send_Data;       //The serial port sends the data structure //串口发送数据结构体
        Vel_Pos_Data Robot_Vel;    //The speed of the robot //机器人基于ROS坐标系的线速度
		Vel_Pos_Data Robot_Pos;	   //The position of the robot //机器人的位置
};
#endif
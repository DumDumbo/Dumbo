/****************************************************************************************
 * @brief:  本文件为ROS系统与下位机STM32全双工异步串行通信例程
 * 
 * @version: 1.3（1.2, 1.1 , 1.0）
 * 
 * @date：2023/12/9
 * 
 * @author: YYY (From GZIST)
 *                     
 * @details:  本文件通过UART串口通信方式，实现ROS系统与下位机STM32F407IIH6的
 *                       全双工异步串行通信。其中ROS向Stm32发送速度消息以及被解析的二维码消息。
 *                       Stm32向ROS发送小车基于电机转速合成后的XYZ方向速度（单位mm/s），
 *                       并发布里程计话题（速度单位m/s）
 *
 * @note: 1.1修改：修改了serial_data_pub()函数中关于ros_pos.X(Y)(Z)的算法公式
 *                 1.2修改：开启了publish_odom()函数中的协方差矩阵判断，用于使用robot_pose_ekf包
 *                                     进行机器人姿态判断，并其会发布odom->base_footprint的tf变换
 *                 1.3修改：将下位机传输的轮式里程计信息发布至/odom_wheel话题，代替了原来直接发布
 *                                      至/odom话题。方便用户后续对/odom信息的优化（譬如想融合IMU消息与轮式
 *                                      里程计消息，再将优化后的位姿消息通过另一节点发布至/odom中）
 *                                      已将/odom的“frame_id、话题名称”修改为/odom_wheel
 ****************************************************************************************/

#include "gkrobot_serial_demo.h"
#include "Quaternion_Solution.h"


/*******
 * @brief:	实例化对象
 * 			    Instantiate Objects
*********/


/*******
 * @brief:	全局变量声明
 * 			    Global Variable Declaration
*********/
static uint8_t target_Point1, target_Point2, door_num1, door_num2;
static short  linearX, linearY, angularZ;  


/*******
 * @brief:	主函数，ROS初始化，通过turn_on_robot类创建Robot_control对象并自动调用构造函数初始化
 * 			    The main function, ROS initialization, creates the Robot_control object through the Turn_on_robot class and automatically calls the constructor initialization
*********/
int main(int argc, char** argv)
{
  ros::init(argc, argv, "gkrobot_serial_demo"); //ROS initializes and sets the node name //ROS初始化 并设置节点名称 
  turn_on_robot Robot_Control; //Instantiate an object //实例化一个对象
  Robot_Control.gkrobot_Init(); //进行机器人相关参数初始化

  // 为两个函数创建线程  
  std::thread data_pub_thread(&turn_on_robot::serial_data_pub, &Robot_Control);
  std::thread ros2stm32_thread(&turn_on_robot::serial_ros2stm32, &Robot_Control);

  // 等待两个线程完成  
  data_pub_thread.join();
  ros2stm32_thread.join();

  
  return 0;  
} 


/*******
 * @name:   void turn_on_robot::gkrobot_Init()
 * 
 * @brief:  构造函数, 只执行一次，用于初始化
 * 			    Constructor, executed only once, for initialization
*********/
void turn_on_robot::gkrobot_Init()
{
  //Clear the data
  //清空数据
  memset(&Robot_Vel, 0, sizeof(Robot_Vel));
  memset(&Send_Data, 0, sizeof(Send_Data));

  ros::NodeHandle private_nh("~"); //Create a node handle //创建节点句柄
  //The private_nh.param() entry parameter corresponds to the initial value of the name of the parameter variable on the parameter server
  //private_nh.param()入口参数分别对应：参数服务器上的名称  参数变量名  初始值
  private_nh.param<std::string>("usart_port_name",  usart_port_name,  "/dev/ttyUSB0"); //Fixed serial port number //固定串口号
  private_nh.param<int>        ("serial_baud_rate", serial_baud_rate, 115200); //Communicate baud rate 115200 to the lower machine //和下位机通信波特率115200
  private_nh.param<std::string>("odom_frame_id",    odom_frame_id,    "odom_wheel");      //The odometer topic corresponds to the parent TF coordinate //里程计话题对应父TF坐标
  private_nh.param<std::string>("robot_frame_id",   robot_frame_id,   "base_footprint"); //The odometer topic corresponds to sub-TF coordinates //里程计话题对应子TF坐标
  
  odom_publisher = n.advertise<nav_msgs::Odometry>("odom_wheel", 50); //Create the odometer topic publisher //创建里程计话题发布者
  
  //Set the velocity control command callback function
  //速度控制命令订阅回调函数设置
  Cmd_Vel_Sub  = n.subscribe("cmd_vel", 1, &turn_on_robot::Cmd_Vel_Callback, this);  //缓存：说明了缓存几条消息，1条消息有多少字节看用户自定义
  Qr_Code_Sub = n.subscribe("QrCodeTopic", 0, &turn_on_robot::Qr_Code_Callback, this);

  ROS_INFO_STREAM("Data ready"); //Prompt message //提示信息
  
  try
  { 
    //Attempts to initialize and open the serial port //尝试初始化与开启串口
    Stm32_Serial.setPort(usart_port_name); //Select the serial port number to enable //选择要开启的串口号
    Stm32_Serial.setBaudrate(serial_baud_rate); //Set the baud rate //设置波特率
    serial::Timeout _time = serial::Timeout::simpleTimeout(20); //Timeout //超时等待 //单位:ms
    Stm32_Serial.setTimeout(_time);
    Stm32_Serial.open(); //Open the serial port //开启串口
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR_STREAM("gkrobot can not open serial port,Please check the serial port cable! "); //If opening the serial port fails, an error message is printed //如果开启串口失败，打印错误信息
  }
  if(Stm32_Serial.isOpen())
  {
    ROS_INFO_STREAM("gkrobot serial port opened"); //Serial port opened successfully //串口开启成功提示
  }
}


/*******
 * @name:   unsigned char turn_on_robot::Check_Sum(unsigned char Count_Number,unsigned char mode)
 * 
 * @brief:	串口通讯校验函数（BCC校验）
 *          数据包n有个字节，第n-1个字节为校验位，第n个字节位帧尾。
 *          第1个字节到第n-2个字节数据按位异或的结果与第n-1个字节对比，即为BCC校验
 * 
 * @param:  Count_Number：数据包前几个字节加入校验          
 *          mode：对发送数据还是接收数据进行校验
 * 
 * @retval: check_sum
*********/
unsigned char turn_on_robot::Check_Sum(unsigned char Count_Number,unsigned char mode)
{
  unsigned char check_sum=0,k;
  
  if(mode==0) //Receive data mode //接收数据模式
  {
   for(k=0;k<Count_Number;k++)
    {
     check_sum=check_sum^Receive_Data.rx[k]; //By bit or by bit //按位异或
     }
  }
  if(mode==1) //Send data mode //发送数据模式
  {
   for(k=0;k<Count_Number;k++)
    {
     check_sum=check_sum^Send_Data.tx[k]; //By bit or by bit //按位异或
     }
  }
  return check_sum; //Returns the bitwise XOR result //返回按位异或结果
}


/*******************************************发送数据部分******************************************/
/************************************************************************************************/

/*******
 * @name:   void turn_on_robot::serial_ros2stm32()
 * 
 * @brief:	数据发送函数。将指令通过UART串口通信方式发送至Stm32进行控制
 * 
*********/
void turn_on_robot::serial_ros2stm32()
{
  short  transition;  //intermediate variable //中间变量
  while(ros::ok())
  {  
    Send_Data.tx[0] = FRAME_HEADER;   //frame head 0x7B //帧头0X7B
    Send_Data.tx[1] = 100; //target_Point1; //set aside //预留位
    Send_Data.tx[2] = door_num1;    //set aside //预留位

    //The target velocity of the X-axis of the robot
    //机器人x轴的目标线速度
    transition = 0;
    transition = linearX;        //因速度单位为m/s，已将浮点数放大一千倍，变成mm/s，简化传输
    Send_Data.tx[3] = transition>>8;  //取数据的高8位
    Send_Data.tx[4] = transition;     //取数据的低8位
    //The target velocity of the Y-axis of the robot
    //机器人y轴的目标线速度
    transition = 0;
    transition = linearY;    
    Send_Data.tx[5] = transition>>8;
    Send_Data.tx[6] = transition;
    //The target velocity of the Y-axis of the robot
    //机器人绕自身z轴旋转的目标角速度
    transition = 0;
    transition = angularZ;
    Send_Data.tx[7] = transition>>8;
    Send_Data.tx[8] = transition;


    Send_Data.tx[9] = Check_Sum(9,SEND_DATA_CHECK); //For the BCC check bits, see the Check_Sum function //BCC校验位，规则参见Check_Sum函数
    Send_Data.tx[10] = FRAME_TAIL; //frame tail 0x7D //帧尾0X7D
    try
    {
      for (int i = 0; i < 11; i++)
      {
        /* code */
        Stm32_Serial.write(&Send_Data.tx[i], 1);

      }
    
      // Stm32_Serial.write(Send_Data.tx, 11); //Sends data to the downloader via serial port //通过串口向下位机发送数据 
      /* code */
    }
    catch (serial::IOException& e)   
    {
      ROS_ERROR_STREAM("Unable to send data through serial port(From function serial_ros2stm32())"); //If sending data fails, an error message is printed //如果发送数据失败，打印错误信息
    }
  }
}


/*******
 * @name:   void turn_on_robot::Qr_Code_Callback(const qrcode_msg::qrcode_msg &qrmsg)
 * 
 * @brief:	二维码数据话题订阅回调函数Callback
 *          The QrCode topic subscription Callback function
 * 
*********/
void turn_on_robot::Qr_Code_Callback(const qrcode_msg::qrcode_msg &qrmsg)
{
    target_Point1 = qrmsg.target_point1;
    target_Point2 = qrmsg.target_point2;
    door_num1 = qrmsg.door_num1;
    door_num2 = qrmsg.door_num2;
}


/*******
 * @name:   void turn_on_robot::Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux)
 * 
 * @brief:	速度话题订阅回调函数Callback
 *          The speed topic subscription Callback function
 * 
*********/
void turn_on_robot::Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux)
{
  //必须在这放大倍数，因为twist_aux.linear.x为float，单位为m/s，放大1000倍数后mm/s,且小数部分都为0，
  //相当于整数，此时赋值给short类型的linearX不会出现数据丢失的情况。

  //The target velocity of the X-axis of the robot
  //机器人x轴的目标线速度
  linearX = twist_aux.linear.x *1000; //将浮点数放大一千倍，简化传输

  //The target velocity of the Y-axis of the robot
  //机器人y轴的目标线速度
  linearY = twist_aux.linear.y*1000;

  //The target angular velocity of the robot's Z axis
  //机器人z轴的目标角速度
  angularZ = twist_aux.angular.z*1000;
}


/*******************************************接收数据部分******************************************/
/************************************************************************************************/

/*******
 * @name:   float turn_on_robot::Odom_Trans(uint8_t Data_High,uint8_t Data_Low)
 * 
 * @brief:	速度转换函数，用于发布里程计数据
 * 
 * @param： uint8_t Data_High：高八位数据
 *          uint8_t Data_Low： 低八位数据
 * 
 * @retval: data_return
*********/
float turn_on_robot::Odom_Trans(uint8_t Data_High,uint8_t Data_Low)
{
  float data_return;
  short transition_16;
  transition_16 = 0;
  transition_16 |=  Data_High<<8;  //Get the high 8 bits of data   //获取数据的高8位
  transition_16 |=  Data_Low;      //Get the lowest 8 bits of data //获取数据的低8位
  data_return   =  (transition_16 / 1000)+(transition_16 % 1000)*0.001; // The speed unit is changed from mm/s to m/s //速度单位从mm/s转换为m/s
  return data_return;
}


/*******
 * @name:   void turn_on_robot::Publish_Odom()
 * 
 * @brief:	里程计数据发布函数
 *                  发布里程计话题，包含位置、姿态、三轴速度、绕三轴角速度、TF父子坐标、协方差矩阵
 * 
*********/
void turn_on_robot::Publish_Odom()
{
  //Convert the Z-axis rotation Angle into a quaternion for expression 
  //把Z轴转角转换为四元数进行表达
  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(Robot_Pos.Z);

  //里程计消息赋值
  nav_msgs::Odometry odom; //Instance the odometer topic data //实例化里程计话题数据
  odom.header.stamp = ros::Time::now(); 
  odom.header.frame_id = odom_frame_id; // Odometer TF parent coordinates //里程计TF父坐标
  odom.pose.pose.position.x = Robot_Pos.X; //Position //位置
  odom.pose.pose.position.y = Robot_Pos.Y;
  odom.pose.pose.position.z = Robot_Pos.Z;
  odom.pose.pose.orientation = odom_quat; //Posture, Quaternion converted by Z-axis rotation //姿态，通过Z轴转角转换的四元数
  
  odom.child_frame_id = robot_frame_id; // Odometer TF subcoordinates //里程计TF子坐标
  odom.twist.twist.linear.x =  Robot_Vel.X; //Speed in the X direction //X方向速度
  odom.twist.twist.linear.y =  Robot_Vel.Y; //Speed in the Y direction //Y方向速度
  odom.twist.twist.angular.z = Robot_Vel.Z; //Angular velocity around the Z axis //绕Z轴角速度 

  //There are two types of this matrix, which are used when the robot is at rest and when it is moving.Extended Kalman Filtering officially provides 2 matrices for the robot_pose_ekf feature pack
  //这个矩阵有两种，分别在机器人静止和运动的时候使用。扩展卡尔曼滤波官方提供的2个矩阵，用于robot_pose_ekf功能包
  if(Robot_Vel.X== 0 && Robot_Vel.Y== 0 && Robot_Vel.Z== 0)
  {
    // If the velocity is zero, it means that the error of the encoder will be relatively small, and the data of the encoder will be considered more reliable
    // 如果velocity是零，说明编码器的误差会比较小，认为编码器数据更可靠
    memcpy(&odom.pose.covariance, odom_pose_covariance2, sizeof(odom_pose_covariance2)),
    memcpy(&odom.twist.covariance, odom_twist_covariance2, sizeof(odom_twist_covariance2));
   } 
  else
  {
    //If the velocity of the trolley is non-zero, considering the sliding error that may be brought by the encoder in motion, the data of IMU is considered to be more reliable
     //如果小车velocity非零，考虑到运动中编码器可能带来的滑动误差，认为imu的数据更可靠
     memcpy(&odom.pose.covariance, odom_pose_covariance, sizeof(odom_pose_covariance)),
    memcpy(&odom.twist.covariance, odom_twist_covariance, sizeof(odom_twist_covariance));       
  
  }

  odom_publisher.publish(odom); //Pub odometer topic //发布里程计话题
  
}


/*******
 * @name:   bool turn_on_robot::serial_data_from_stm32()
 * 
 * @brief:	ROS从Stm32接收数据函数
 *          Receiving data from Stm32
 * 
*********/
bool turn_on_robot::serial_data_from_stm32()
{
  
  short transition_16=0; //Intermediate variable //中间变量
  uint8_t check=0, error=1,Receive_Data_Pr[1]; //Temporary variable to save the data of the lower machine //临时变量，保存下位机数据
  static int count; //Static variable for counting //静态变量，用于计数


  Stm32_Serial.read(Receive_Data_Pr,sizeof(Receive_Data_Pr)); //Read the data sent by the lower computer through the serial port //通过串口读取下位机发送过来的数据

  Receive_Data.rx[count] = Receive_Data_Pr[0]; //Fill the array with serial data //串口数据填入数组

  //固定数据赋值
  Receive_Data.Sensor_Str.Frame_Header = Receive_Data.rx[0]; //The first part of the data is the frame header 0X7B //数据的第一位是帧头0X7B
  Receive_Data.Sensor_Str.Frame_Tail = Receive_Data.rx[10];  //The last bit of data is frame tail 0X7D //数据的最后一位是帧尾0X7D

  if(Receive_Data_Pr[0] == FRAME_HEADER || count>0)//Ensure that the first data in the array is FRAME_HEADER //确保数组第一个数据为FRAME_HEADER
  {
    
    count++;
  } 
    
  else 
  	count=0;

  if(count == 11) //Verify the length of the packet //验证数据包的长度
  {
    
    count=0;  //Prepare for the serial port data to be refill into the array //为串口数据重新填入数组做准备
    
    if(Receive_Data.Sensor_Str.Frame_Tail == FRAME_TAIL) //Verify the frame tail of the packet //验证数据包的帧尾
    {
      check=Check_Sum(9,READ_DATA_CHECK);  //BCC check passes or two packets are interlaced //BCC校验通过或者两组数据包交错
      
      if(check == Receive_Data.rx[9])  
      {
        error=0;  //XOR bit check successful //异或位校验成功
      }

      if(error == 0)
      {
        Receive_Data.Sensor_Str.Flag = Receive_Data.rx[1]; //set aside //预留位
        Receive_Data.Sensor_Str.Status = Receive_Data.rx[2]; //set aside //预留位
        
        Robot_Vel.X = Odom_Trans(Receive_Data.rx[3],Receive_Data.rx[4]); //Get the speed of the moving chassis in the X direction //获取运动底盘X方向速度
        // std::cout << Robot_Vel.X << std::endl;  输出信息
        Robot_Vel.Y = Odom_Trans(Receive_Data.rx[5],Receive_Data.rx[6]); //Get the speed of the moving chassis in the Y direction, The Y speed is only valid in the omnidirectional mobile robot chassis
                                                                          //获取运动底盘Y方向速度，Y速度仅在全向移动机器人底盘有效
        Robot_Vel.Z = Odom_Trans(Receive_Data.rx[7],Receive_Data.rx[8]); //Get the speed of the moving chassis in the Z direction //获取运动底盘Z方向速度   
          
        return true;

      }
      
    }

  }
  return false;
}


/*******
 * @name:   void turn_on_robot::serial_data_pub()
 * 
 * @brief:	循环获取下位机数据与发布话题
 * 
*********/
void turn_on_robot::serial_data_pub()
{
  _Last_Time = ros::Time::now();
  while(ros::ok())
  {
    Sampling_Time = (_Now - _Last_Time).toSec(); //Retrieves time interval, which is used to integrate velocity to obtain displacement (mileage) 
                                                 //获取时间间隔，用于积分速度获得位移(里程)
    _Now = ros::Time::now();
    if (true == serial_data_from_stm32()) //The serial port reads and verifies the data sent by the lower computer, and then the data is converted to international units
                                   //通过串口读取并校验下位机发送过来的数据，然后数据转换为国际单位
    {
      //根据速度积分计算位移
      // Robot_Pos.X+=(Robot_Vel.X * cos(Robot_Pos.Z) - Robot_Vel.Y * sin(Robot_Pos.Z)) * Sampling_Time; //Calculate the displacement in the X direction, unit: m //计算X方向的位移，单位：m
      // Robot_Pos.Y+=(Robot_Vel.X * sin(Robot_Pos.Z) + Robot_Vel.Y * cos(Robot_Pos.Z)) * Sampling_Time; //Calculate the displacement in the Y direction, unit: m //计算Y方向的位移，单位：m
      // Robot_Pos.Z+=Robot_Vel.Z * Sampling_Time; //The angular displacement about the Z axis, in rad //绕Z轴的角位移，单位：rad 
      Robot_Pos.X+= Robot_Vel.X *Sampling_Time;
      Robot_Pos.Y+= Robot_Vel.Y *Sampling_Time;
      Robot_Pos.Z+=Robot_Vel.Z *Sampling_Time;
      Publish_Odom();      //Pub the speedometer topic //发布里程计话题

      _Last_Time = _Now; //Record the time and use it to calculate the time interval //记录时间，用于计算时间间隔
      
    }
    
    ros::spinOnce();   //The loop waits for the callback function //循环等待回调函数
    }
}


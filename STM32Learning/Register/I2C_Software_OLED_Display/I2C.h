/*****************************************************************************************
* @FunctionName: I2C.h
* @Author:
* @Date：
* @brief：To realize software simulation I2C
******************************************************************************************/

#include "Register.h"


#define SDA_IN() {GPIOB->CRL&=~(15<<28);GPIOB->CRL|= 8<<28;}//清零；配置上拉/下拉输入模式
//PB7 输入模式
#define SDA_OUT() {GPIOB->CRL&=~(15<<28);GPIOB->CRL|=3<<28;}//通用推挽输出模式 输出模式，最大速度50MHz
//PB7 输出模式

//IO 操作
#define I2C_SCL GPIO_SetBits(GPIOB, GPIO_PIN_6) //SCL
#define I2C_SDA PBout(7) //输出 SDA
#define READ_SDA PBin(7) //输入 SDA

void iic_init(void);




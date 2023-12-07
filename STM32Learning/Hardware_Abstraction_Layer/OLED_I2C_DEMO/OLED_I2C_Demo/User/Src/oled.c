/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    oled.c
  * @brief   These files are the implementation of oled screen function
  *          .
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* USER CODE END Header */


/* USER CODE BEGIN Includes 用户头文件定义*/
#include "oled.h"
#include "I2C.h"
#include "oled_font.h"
/* USER CODE END Includes */


/* USER CODE BEGIN PV 私有变量定义*/

unsigned char GRAM[8][128]; //显示缓存

/* USER CODE END Private variables  */


/* USER CODE BEGIN 0 */

/*********************************************************************************
****************************功能函数Start****************************************/
void WriteCmd()
{
	//--turn off oled panel 
  OLED_WR_CMD(0xAE);	//关闭显示,进入睡眠模式，准备配置
	
	//开始配置
	
	//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_CMD(0x20);	//设置页寻址模式
	OLED_WR_CMD(0x02);	//00水平地址模式，01垂直地址模式，02页地址模式
	
	OLED_WR_CMD(0x00);	//设置列的低位起始地址	//---set low column address 
	OLED_WR_CMD(0x10);	//设置列的高位起始地址	//---set high column address
	
	//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_CMD(0x40); //设置起始行，显存中的第几行作为屏幕的第一行
	
	//--set contrast control register
	OLED_WR_CMD(0x81);	//设置对比度
	OLED_WR_CMD(0xCF);	//对比度值：（0x00-0xFF）共计256个
	
	//--Set SEG/Column Mapping  
	OLED_WR_CMD(0xA1);	//是否设置左右镜像显示：0xA0左右反置 0xA1正常
	
	//Set COM/Row Scan Direction   
	OLED_WR_CMD(0xC8);	//是否设置上下镜像显示：0xc0上下反置 0xc8正常
	
	//--set normal display
	OLED_WR_CMD(0xA6);	//设置显示模式，A6h正常显示，A7h反色显示
	
	//--set multiplex ratio(1 to 64)
	OLED_WR_CMD(0xA8);	//设置复用率
	OLED_WR_CMD(0x3f);	//--1/64 duty // 00h--3Fh
	
	//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_CMD(0xD3);	//设置屏幕的上下偏移
	OLED_WR_CMD(0x00);	//值（00h-FFh）； 00h即为无偏移
	
	//--set display clock divide ratio/oscillator frequency//设置显示时钟分频值/震荡频率（刷新率）
	OLED_WR_CMD(0xD5);	//设置刷新率
	OLED_WR_CMD(0x80);	//--set divide ratio, Set Clock as 100 Frames/Sec
	
	//--set pre-charge period
	OLED_WR_CMD(0xD9);	//设置预充电周期
	OLED_WR_CMD(0xF1);	//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	
	//--set com pins hardware configuration
	OLED_WR_CMD(0xDA);	//设置列引脚硬件配置
	OLED_WR_CMD(0x12);	//--12846->0x12; 12832->0x02
	
	//--set vcomh
	OLED_WR_CMD(0xDB);	//设置vcomh反压值
	OLED_WR_CMD(0x40);	//Set VCOM Deselect Level

	//--set Charge Pump enable/disable
	OLED_WR_CMD(0x8D);	//设置电荷泵开关
	OLED_WR_CMD(0x14);	//--set(0x10) disable
	
	// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_CMD(0xA4);	//A4h显示显存内容；A5h无视显存内容点亮全屏
	
	OLED_Clear();
	 
	//--turn on oled panel 
	OLED_WR_CMD(0xAF);	//开启显示（进入工作模式）
}


//水平滚动
void OLED_ver_scroll()
{
  OLED_WR_CMD(0x2e);//关滚动
  OLED_WR_CMD(0x27);//29向右，2a向左
  OLED_WR_CMD(0x00);//A:空字节
  OLED_WR_CMD(0x02);//B:水平起始页
  OLED_WR_CMD(0x07);//C:水平滚动速度
  OLED_WR_CMD(0x03);//D:水平结束页
  OLED_WR_CMD(0x00);//E:每次垂直滚动位移
  OLED_WR_CMD(0xFF);//E:每次垂直滚动位移
  OLED_WR_CMD(0x2f);//开滚动
 
}
//向设备写控制命令
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c2 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
	//HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  //分别代表硬件IIC的通道号，设备地址，设备寄存器地址，写入数据的字节类型 8位还是16位，传输数据，传输数据大小，超时时间
}
//向设备写数据
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c2 ,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,0x100);
}



//初始化oled屏幕
void OLED_Init(void)
{
	HAL_Delay(500);
	WriteCmd();
}

//清屏size12 size16要清两行，其他函数有类似情况
void OLED_Clear()
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_CMD(0xb0+i);	//设置页（行）地址和（0-7）
		OLED_WR_CMD (0x00);		//设置显示位置一列低地址
		OLED_WR_CMD (0x10);		//设置显示位置一列高地址
		for(n=0;n<128;n++)		//遍历每一行的每一列的8位地址
			OLED_WR_DATA(0x00);
	}
}
//清行
void OLED_Clearrow(uint8_t i)
{
	uint8_t n;
	OLED_WR_CMD(0xb0+i);
	OLED_WR_CMD (0x20);
	OLED_WR_CMD (0x00);
	for(n=0;n<128;n++)
		OLED_WR_DATA(0x00);
}
//开启OLED显示
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}

/**************************************************************************
Function: Set OLED display cursor position
Input   : none
Output  : none
函数功能：设置 OLED（Organic Light-Emitting Diode）显示屏上光标的位置
入口参数：uint8_t x, uint8_t y （分别代表列(0-127)、行（0-7））
返 回 值：无
**************************************************************************/

void OLED_Set_Pos(uint8_t x, uint8_t y)
{
	OLED_WR_CMD(0xb0+y);							//设置显示的起始行
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);	//设置列地址的高四位
	OLED_WR_CMD(x&0x0f);							//设置列地址的低四位
}


/**************************************************************************
Function: light up the whole screen
Input   : none
Output  : none
函数功能：点亮整个OLED显示屏
入口参数：无
返 回 值：无
**************************************************************************/

void OLED_On(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		
		OLED_WR_CMD(0xb0+i);    //设置页地址（0~7）
		OLED_WR_CMD(0x00);      //设置显示位置—列低地址
		OLED_WR_CMD(0x10);      //设置显示位置—列高地址
		for(n=0;n<128;n++)
			OLED_WR_DATA(0xFF);
	} //更新显示
}


/**************************************************************************
Function: get Power Function
Input   : uint8_t m,uint8_t n
Output  : the result of m^n
函数功能：求幂函数，使用循环实现。
入口参数：uint8_t m,uint8_t n
返 回 值：返回m^n次幂结果
**************************************************************************/

unsigned int oled_pow(uint8_t m,uint8_t n)
{
	unsigned int result=1;
	while(n--)result*=m;
	return result;
}
 

/**************************************************************************
Function: Display a character at the specified position
Input   : none
Output  : none
函数功能：在指定位置显示一个字符,包括部分字符
入口参数：uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size
					列坐标（x:0~127），行坐标（y:0~7），需显示字符，字体大小（16/12）
返 回 值：无
注    意：字符来字预先定义好的F6x8/F8x16数组,编写根据ASCII码
**************************************************************************/

//mode:0,反白显示;1,正常显示
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{
	unsigned char c=0,i=0;
		c=chr - ' ';							//字符减去空格得到偏移后的ASCII值
		if(x>128-1){x=0;y=y+2;}		//若起点坐标超过屏幕最右侧，列坐标x清零（光标回到最左侧），行坐标下移两行
		if(Char_Size <=16)				//判断字号大小，size=16时读取F8X16字库
			{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i+8]);
			}
			else {									//判断字号大小，size不等于16时，读取F6X8字库
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_DATA(F6x8[c][i]);
 
			}
}

/**************************************************************************
Function: Display numbers at the specified position
Input   : none
Output  : none
函数功能：在指定位置显示数字
入口参数：uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2
					列坐标（x:0~127），行坐标（y:0~7），数值(0~65535)，len（数字的位数<=5），字体大小（16/12）
返 回 值：无
注    意：数字来字预先定义好的F6x8/F8x16数组,编写根据ASCII码
**************************************************************************/
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2)
{
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;			//取第t位数字
		if(enshow==0&&t<(len-1))								//如果数串长度小于指定长度
		{
			if(temp==0)														//多出来的位用空客补齐
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;														//继续循环判断
			}else enshow=1;												//直到有数字为止
 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); //从高到低逐位显示数字
	}
}

/**************************************************************************
Function: Display string at the specified position
Input   : none
Output  : none
函数功能：在指定位置显示字符串
入口参数：uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size
					列坐标（x:0~127），行坐标（y:0~7）,字体大小（16/12）
返 回 值：无
注    意：字符串来字预先定义好的F6x8/F8x16数组,编写根据ASCII码
**************************************************************************/
//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')											//若未读到字符串结束符，一直循环
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);		//从第一字符开始显示
		x+=8;																		//显示完第一个字符，起点x坐标右移8格，准备显示下一个字符
		if(x>120)																//若起点x位置大于120，为保证字符显示完成
		{																				//换行，在下一行最左侧位置显示
			x=0;
			y+=2;
		}										
		j++;																		//指针移动到下一个字符								
	}
}
 

/**************************************************************************
Function: Display Chinese at the specified position
Input   : none
Output  : none
函数功能：在指定位置显示汉字
入口参数：uint8_t x,uint8_t y,uint8_t no
					列坐标（x:0~127），行坐标（y:0~7），数值(0~4294967295)，len（数字的位数），字体大小（16/12）
返 回 值：无
注    意：数字来字预先定义好的F6x8/F8x16数组,编写根据ASCII码
**************************************************************************/
//hzk 用取模软件得出的数组
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no)
{
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
		{
				OLED_WR_DATA(Hzk[2*no][t]);
				adder+=1;
     }
		OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
			{
				OLED_WR_DATA(Hzk[2*no+1][t]);
				adder+=1;
      }
}


/**************************************************************************
Function: Display Image at the specified position
Input   : uint8_t x0, uint8_t y0, uint8_t width, uint8_t height, uint8_t BMP[]
Output  : none
函数功能：在指定位置显示图片
入口参数：uint8_t x0, uint8_t y0, uint8_t width, uint8_t height, uint8_t BMP[]
					x0:图像起始列坐标,范围（0-127）
					y0:图像起始行坐标,范围（0-7）
					x1:输入图像的宽（width），范围:0<=width<=128
					y1:输入图像的高（height)，范围:0<=height<=64
					例如：例图片尺寸为128x64，则width=128，height=64
返 回 值：无
**************************************************************************/
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height, uint8_t BMP[])
{
	unsigned int j =0;
	uint8_t x,y,quotient;
	quotient = height / 8; 								//图像高度除以8的商 (直接抛弃小数部分)
	
	for(y = y0; y < (y0+quotient);++y)    //设定行的起点、终点坐标（两者之间的区域为显示区域）
	{
		OLED_Set_Pos(x0,y);
		for(x = x0; x < (x0+width); ++x)		//设定列的起点、终点坐标（两者之间的区域为显示区域）
		{
			OLED_WR_DATA(BMP[j++]);
		}
	}
}





void OLED_Clear_GRAM()
{
	/****************方法一：嵌套循环
	代码示例：
		unsigned int t,j;
		for(t=0;t<8;++t)
		{
			for(j=0;j<128;++j)
			{
				GRAM[t][j]=0xFF;
			}
		}
		OLED_Refresh();
	*******************************/
	
	/****************方法二：使用memset函数(memset用于设置一段内存的内容为指定的值)
	函数原型：
		void *memset(void *ptr, int value, size_t num);
	参数：
		ptr：指向要设置的内存块的指针。
		value：要设置的值。int 类型是为了容纳任意字节的值。
		num：要设置的字节数。
	返回值：
		void
	代码示例:
	*******************************/
	memset(GRAM, 0x00, sizeof(GRAM));
	OLED_Refresh();
	
	
	/*****************方法三：使用循环和指针
	代码示例：
		unsigned char *ptr = &GRAM[0][0];
		unsigned char *end = ptr + sizeof(GRAM);

		while (ptr < end) {
			*ptr++ = 0;}
		OLED_Refresh();
		*******************************/
}


/**************************************************************************
Function: Refresh the GRAM
Input   : none
Output  : none
函数功能：屏幕刷新函数
入口参数：无
返 回 值：无
**************************************************************************/
void OLED_Refresh()
{
	unsigned char x,y;
	unsigned int j =0;
	for(y=0;y<8;++y)
	{
		OLED_Set_Pos(0,y);
		for(x=0;x<128;++x)
		{
			OLED_WR_DATA(GRAM[y][j++]);
		}
	}
}


/**************************************************************************
Function: Display YDLogo at the specified position
Input   : None
Output  : None
函数功能：在指定位置显示源点机器人的Logo
入口参数：无
返 回 值：无
**************************************************************************/
void YuanDianLogo()
{
	uint8_t x=24;
	OLED_Display_On();
	OLED_Clear();
	OLED_ShowBMP(39,0,50,50,YDLogo50x50);
	for(unsigned char i = 4;i<=8;i++)
	{
		OLED_ShowChinese(x,6,i);
		x+=16;
		if(i==8)
			x=24;	
	}
	HAL_Delay(1000);
	OLED_Clear();
	OLED_ShowBMP(52,0,25,25,YDLogo25x25);
}
/* USER CODE END 0 */



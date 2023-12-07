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


/* USER CODE BEGIN Includes �û�ͷ�ļ�����*/
#include "oled.h"
#include "I2C.h"
#include "oled_font.h"
/* USER CODE END Includes */


/* USER CODE BEGIN PV ˽�б�������*/

unsigned char GRAM[8][128]; //��ʾ����

/* USER CODE END Private variables  */


/* USER CODE BEGIN 0 */

/*********************************************************************************
****************************���ܺ���Start****************************************/
void WriteCmd()
{
	//--turn off oled panel 
  OLED_WR_CMD(0xAE);	//�ر���ʾ,����˯��ģʽ��׼������
	
	//��ʼ����
	
	//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_CMD(0x20);	//����ҳѰַģʽ
	OLED_WR_CMD(0x02);	//00ˮƽ��ַģʽ��01��ֱ��ַģʽ��02ҳ��ַģʽ
	
	OLED_WR_CMD(0x00);	//�����еĵ�λ��ʼ��ַ	//---set low column address 
	OLED_WR_CMD(0x10);	//�����еĸ�λ��ʼ��ַ	//---set high column address
	
	//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_CMD(0x40); //������ʼ�У��Դ��еĵڼ�����Ϊ��Ļ�ĵ�һ��
	
	//--set contrast control register
	OLED_WR_CMD(0x81);	//���öԱȶ�
	OLED_WR_CMD(0xCF);	//�Աȶ�ֵ����0x00-0xFF������256��
	
	//--Set SEG/Column Mapping  
	OLED_WR_CMD(0xA1);	//�Ƿ��������Ҿ�����ʾ��0xA0���ҷ��� 0xA1����
	
	//Set COM/Row Scan Direction   
	OLED_WR_CMD(0xC8);	//�Ƿ��������¾�����ʾ��0xc0���·��� 0xc8����
	
	//--set normal display
	OLED_WR_CMD(0xA6);	//������ʾģʽ��A6h������ʾ��A7h��ɫ��ʾ
	
	//--set multiplex ratio(1 to 64)
	OLED_WR_CMD(0xA8);	//���ø�����
	OLED_WR_CMD(0x3f);	//--1/64 duty // 00h--3Fh
	
	//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_CMD(0xD3);	//������Ļ������ƫ��
	OLED_WR_CMD(0x00);	//ֵ��00h-FFh���� 00h��Ϊ��ƫ��
	
	//--set display clock divide ratio/oscillator frequency//������ʾʱ�ӷ�Ƶֵ/��Ƶ�ʣ�ˢ���ʣ�
	OLED_WR_CMD(0xD5);	//����ˢ����
	OLED_WR_CMD(0x80);	//--set divide ratio, Set Clock as 100 Frames/Sec
	
	//--set pre-charge period
	OLED_WR_CMD(0xD9);	//����Ԥ�������
	OLED_WR_CMD(0xF1);	//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	
	//--set com pins hardware configuration
	OLED_WR_CMD(0xDA);	//����������Ӳ������
	OLED_WR_CMD(0x12);	//--12846->0x12; 12832->0x02
	
	//--set vcomh
	OLED_WR_CMD(0xDB);	//����vcomh��ѹֵ
	OLED_WR_CMD(0x40);	//Set VCOM Deselect Level

	//--set Charge Pump enable/disable
	OLED_WR_CMD(0x8D);	//���õ�ɱÿ���
	OLED_WR_CMD(0x14);	//--set(0x10) disable
	
	// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_CMD(0xA4);	//A4h��ʾ�Դ����ݣ�A5h�����Դ����ݵ���ȫ��
	
	OLED_Clear();
	 
	//--turn on oled panel 
	OLED_WR_CMD(0xAF);	//������ʾ�����빤��ģʽ��
}


//ˮƽ����
void OLED_ver_scroll()
{
  OLED_WR_CMD(0x2e);//�ع���
  OLED_WR_CMD(0x27);//29���ң�2a����
  OLED_WR_CMD(0x00);//A:���ֽ�
  OLED_WR_CMD(0x02);//B:ˮƽ��ʼҳ
  OLED_WR_CMD(0x07);//C:ˮƽ�����ٶ�
  OLED_WR_CMD(0x03);//D:ˮƽ����ҳ
  OLED_WR_CMD(0x00);//E:ÿ�δ�ֱ����λ��
  OLED_WR_CMD(0xFF);//E:ÿ�δ�ֱ����λ��
  OLED_WR_CMD(0x2f);//������
 
}
//���豸д��������
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c2 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
	//HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  //�ֱ����Ӳ��IIC��ͨ���ţ��豸��ַ���豸�Ĵ�����ַ��д�����ݵ��ֽ����� 8λ����16λ���������ݣ��������ݴ�С����ʱʱ��
}
//���豸д����
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c2 ,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,0x100);
}



//��ʼ��oled��Ļ
void OLED_Init(void)
{
	HAL_Delay(500);
	WriteCmd();
}

//����size12 size16Ҫ�����У������������������
void OLED_Clear()
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_CMD(0xb0+i);	//����ҳ���У���ַ�ͣ�0-7��
		OLED_WR_CMD (0x00);		//������ʾλ��һ�е͵�ַ
		OLED_WR_CMD (0x10);		//������ʾλ��һ�иߵ�ַ
		for(n=0;n<128;n++)		//����ÿһ�е�ÿһ�е�8λ��ַ
			OLED_WR_DATA(0x00);
	}
}
//����
void OLED_Clearrow(uint8_t i)
{
	uint8_t n;
	OLED_WR_CMD(0xb0+i);
	OLED_WR_CMD (0x20);
	OLED_WR_CMD (0x00);
	for(n=0;n<128;n++)
		OLED_WR_DATA(0x00);
}
//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}

/**************************************************************************
Function: Set OLED display cursor position
Input   : none
Output  : none
�������ܣ����� OLED��Organic Light-Emitting Diode����ʾ���Ϲ���λ��
��ڲ�����uint8_t x, uint8_t y ���ֱ������(0-127)���У�0-7����
�� �� ֵ����
**************************************************************************/

void OLED_Set_Pos(uint8_t x, uint8_t y)
{
	OLED_WR_CMD(0xb0+y);							//������ʾ����ʼ��
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);	//�����е�ַ�ĸ���λ
	OLED_WR_CMD(x&0x0f);							//�����е�ַ�ĵ���λ
}


/**************************************************************************
Function: light up the whole screen
Input   : none
Output  : none
�������ܣ���������OLED��ʾ��
��ڲ�������
�� �� ֵ����
**************************************************************************/

void OLED_On(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		
		OLED_WR_CMD(0xb0+i);    //����ҳ��ַ��0~7��
		OLED_WR_CMD(0x00);      //������ʾλ�á��е͵�ַ
		OLED_WR_CMD(0x10);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)
			OLED_WR_DATA(0xFF);
	} //������ʾ
}


/**************************************************************************
Function: get Power Function
Input   : uint8_t m,uint8_t n
Output  : the result of m^n
�������ܣ����ݺ�����ʹ��ѭ��ʵ�֡�
��ڲ�����uint8_t m,uint8_t n
�� �� ֵ������m^n���ݽ��
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
�������ܣ���ָ��λ����ʾһ���ַ�,���������ַ�
��ڲ�����uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size
					�����꣨x:0~127���������꣨y:0~7��������ʾ�ַ��������С��16/12��
�� �� ֵ����
ע    �⣺�ַ�����Ԥ�ȶ���õ�F6x8/F8x16����,��д����ASCII��
**************************************************************************/

//mode:0,������ʾ;1,������ʾ
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{
	unsigned char c=0,i=0;
		c=chr - ' ';							//�ַ���ȥ�ո�õ�ƫ�ƺ��ASCIIֵ
		if(x>128-1){x=0;y=y+2;}		//��������곬����Ļ���Ҳ࣬������x���㣨���ص�����ࣩ����������������
		if(Char_Size <=16)				//�ж��ֺŴ�С��size=16ʱ��ȡF8X16�ֿ�
			{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i+8]);
			}
			else {									//�ж��ֺŴ�С��size������16ʱ����ȡF6X8�ֿ�
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_DATA(F6x8[c][i]);
 
			}
}

/**************************************************************************
Function: Display numbers at the specified position
Input   : none
Output  : none
�������ܣ���ָ��λ����ʾ����
��ڲ�����uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2
					�����꣨x:0~127���������꣨y:0~7������ֵ(0~65535)��len�����ֵ�λ��<=5���������С��16/12��
�� �� ֵ����
ע    �⣺��������Ԥ�ȶ���õ�F6x8/F8x16����,��д����ASCII��
**************************************************************************/
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2)
{
	uint8_t t,temp;
	uint8_t enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;			//ȡ��tλ����
		if(enshow==0&&t<(len-1))								//�����������С��ָ������
		{
			if(temp==0)														//�������λ�ÿտͲ���
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;														//����ѭ���ж�
			}else enshow=1;												//ֱ��������Ϊֹ
 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); //�Ӹߵ�����λ��ʾ����
	}
}

/**************************************************************************
Function: Display string at the specified position
Input   : none
Output  : none
�������ܣ���ָ��λ����ʾ�ַ���
��ڲ�����uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size
					�����꣨x:0~127���������꣨y:0~7��,�����С��16/12��
�� �� ֵ����
ע    �⣺�ַ�������Ԥ�ȶ���õ�F6x8/F8x16����,��д����ASCII��
**************************************************************************/
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')											//��δ�����ַ�����������һֱѭ��
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);		//�ӵ�һ�ַ���ʼ��ʾ
		x+=8;																		//��ʾ���һ���ַ������x��������8��׼����ʾ��һ���ַ�
		if(x>120)																//�����xλ�ô���120��Ϊ��֤�ַ���ʾ���
		{																				//���У�����һ�������λ����ʾ
			x=0;
			y+=2;
		}										
		j++;																		//ָ���ƶ�����һ���ַ�								
	}
}
 

/**************************************************************************
Function: Display Chinese at the specified position
Input   : none
Output  : none
�������ܣ���ָ��λ����ʾ����
��ڲ�����uint8_t x,uint8_t y,uint8_t no
					�����꣨x:0~127���������꣨y:0~7������ֵ(0~4294967295)��len�����ֵ�λ�����������С��16/12��
�� �� ֵ����
ע    �⣺��������Ԥ�ȶ���õ�F6x8/F8x16����,��д����ASCII��
**************************************************************************/
//hzk ��ȡģ����ó�������
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
�������ܣ���ָ��λ����ʾͼƬ
��ڲ�����uint8_t x0, uint8_t y0, uint8_t width, uint8_t height, uint8_t BMP[]
					x0:ͼ����ʼ������,��Χ��0-127��
					y0:ͼ����ʼ������,��Χ��0-7��
					x1:����ͼ��Ŀ�width������Χ:0<=width<=128
					y1:����ͼ��ĸߣ�height)����Χ:0<=height<=64
					���磺��ͼƬ�ߴ�Ϊ128x64����width=128��height=64
�� �� ֵ����
**************************************************************************/
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height, uint8_t BMP[])
{
	unsigned int j =0;
	uint8_t x,y,quotient;
	quotient = height / 8; 								//ͼ��߶ȳ���8���� (ֱ������С������)
	
	for(y = y0; y < (y0+quotient);++y)    //�趨�е���㡢�յ����꣨����֮�������Ϊ��ʾ����
	{
		OLED_Set_Pos(x0,y);
		for(x = x0; x < (x0+width); ++x)		//�趨�е���㡢�յ����꣨����֮�������Ϊ��ʾ����
		{
			OLED_WR_DATA(BMP[j++]);
		}
	}
}





void OLED_Clear_GRAM()
{
	/****************����һ��Ƕ��ѭ��
	����ʾ����
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
	
	/****************��������ʹ��memset����(memset��������һ���ڴ������Ϊָ����ֵ)
	����ԭ�ͣ�
		void *memset(void *ptr, int value, size_t num);
	������
		ptr��ָ��Ҫ���õ��ڴ���ָ�롣
		value��Ҫ���õ�ֵ��int ������Ϊ�����������ֽڵ�ֵ��
		num��Ҫ���õ��ֽ�����
	����ֵ��
		void
	����ʾ��:
	*******************************/
	memset(GRAM, 0x00, sizeof(GRAM));
	OLED_Refresh();
	
	
	/*****************��������ʹ��ѭ����ָ��
	����ʾ����
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
�������ܣ���Ļˢ�º���
��ڲ�������
�� �� ֵ����
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
�������ܣ���ָ��λ����ʾԴ������˵�Logo
��ڲ�������
�� �� ֵ����
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



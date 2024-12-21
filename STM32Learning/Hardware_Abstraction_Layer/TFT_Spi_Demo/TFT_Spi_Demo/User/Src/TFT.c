#include "TFT.h"
#include "TFT_Font.h"


/******************************************************************************
*@breif:��ָ�����������ɫ��һ��һ��ˢ�£�
*@paremeters:	x1,y1����ʼ���꣩
							x2,y2����ֹ���꣩
							color��������ɫ��
*@return:��  
******************************************************************************/
void TFT_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	TFT_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			TFT_WR_DATA(color);
		}
	}
}


/******************************************************************************
*@breif:����
*@paremeters:	x,y���������꣩	
							color�������ɫ��
*@return:�� 
******************************************************************************/
void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	TFT_Address_Set(x,y,x,y);//���ù��λ�� 
	TFT_WR_DATA(color);
} 


/******************************************************************************
*@breif:����
*@paremeters:	x1,y1����ʼ���꣩
							x2,y2����ֹ���꣩
							color�����ε���ɫ��
*@return:��   
******************************************************************************/
void TFT_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		TFT_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
*@breif:������
*@paremeters:	x1,y1����ʼ���꣩
							x2,y2����ֹ���꣩
							color�����ε���ɫ��
*@return:��   
******************************************************************************/
void TFT_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	TFT_DrawLine(x1,y1,x2,y1,color);
	TFT_DrawLine(x1,y1,x1,y2,color);
	TFT_DrawLine(x1,y2,x2,y2,color);
	TFT_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
*@breif:��Բ
*@paremeters:	x0,y0��Բ�����꣩
							r���뾶��
							color��Բ����ɫ��
*@return:��    
******************************************************************************/
void TFT_DrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		TFT_DrawPoint(x0-b,y0-a,color);             //3           
		TFT_DrawPoint(x0+b,y0-a,color);             //0           
		TFT_DrawPoint(x0-a,y0+b,color);             //1                
		TFT_DrawPoint(x0-a,y0-b,color);             //2             
		TFT_DrawPoint(x0+b,y0+a,color);             //4               
		TFT_DrawPoint(x0+a,y0-b,color);             //5
		TFT_DrawPoint(x0+a,y0+b,color);             //6 
		TFT_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

/******************************************************************************
*@breif:��ʾ���ִ�
*@paremeters:	x,y��ʾ����
							*s Ҫ��ʾ�ĺ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey ��(��ѡ12��16��24��32)
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:��       
******************************************************************************/
void TFT_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	while(*s!=0)
	{
		if(sizey==12) TFT_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
		else if(sizey==16) TFT_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
		else if(sizey==24) TFT_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
		else if(sizey==32) TFT_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
		else return;
		s+=2;
		x+=sizey;
	}
}

/******************************************************************************
*@breif:��ʾ����12x12����
*@paremeters:	x,y��ʾ����
							*s Ҫ��ʾ�ĺ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:�� 
******************************************************************************/
void TFT_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//������Ŀ
	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	                         
	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
		{ 	
			TFT_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
					{
						if(tfont12[k].Msk[i]&(0x01<<j))TFT_WR_DATA(fc);
						else TFT_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//���ӷ�ʽ
					{
						if(tfont12[k].Msk[i]&(0x01<<j))	TFT_DrawPoint(x,y,fc);//��һ����
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 

/******************************************************************************
*@breif:��ʾ����16x16����
*@paremeters:	x,y��ʾ����
							*s Ҫ��ʾ�ĺ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:�� 
******************************************************************************/
void TFT_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//������Ŀ
	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
		{ 	
			TFT_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
					{
						if(tfont16[k].Msk[i]&(0x01<<j))TFT_WR_DATA(fc);
						else TFT_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//���ӷ�ʽ
					{
						if(tfont16[k].Msk[i]&(0x01<<j))	TFT_DrawPoint(x,y,fc);//��һ����
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 


/******************************************************************************
*@breif:��ʾ����24x24����
*@paremeters:	x,y��ʾ����
							*s Ҫ��ʾ�ĺ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:�� 
******************************************************************************/
void TFT_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//������Ŀ
	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{ 	
			TFT_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
					{
						if(tfont24[k].Msk[i]&(0x01<<j))TFT_WR_DATA(fc);
						else TFT_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//���ӷ�ʽ
					{
						if(tfont24[k].Msk[i]&(0x01<<j))	TFT_DrawPoint(x,y,fc);//��һ����
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 

/******************************************************************************
*@breif:��ʾ����32x32����
*@paremeters:	x,y��ʾ����
							*s Ҫ��ʾ�ĺ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:��
******************************************************************************/
void TFT_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//������Ŀ
	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
		{ 	
			TFT_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
					{
						if(tfont32[k].Msk[i]&(0x01<<j))TFT_WR_DATA(fc);
						else TFT_WR_DATA(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//���ӷ�ʽ
					{
						if(tfont32[k].Msk[i]&(0x01<<j))	TFT_DrawPoint(x,y,fc);//��һ����
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
}


/******************************************************************************
*@breif:��ʾ�����ַ�
*@paremeters:	x,y��ʾ����
							*p Ҫ��ʾ���ַ�
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:��
******************************************************************************/
void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	TFT_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ�� 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //����6x12����
		else if(sizey==16)temp=ascii_1608[num][i];		 //����8x16����
		else if(sizey==24)temp=ascii_2412[num][i];		 //����12x24����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//�ǵ���ģʽ
			{
				if(temp&(0x01<<t))TFT_WR_DATA(fc);
				else TFT_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//����ģʽ
			{
				if(temp&(0x01<<t))TFT_DrawPoint(x,y,fc);//��һ����
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
*@breif:��ʾ�ַ���
*@paremeters:	x,y��ʾ����
							*p Ҫ��ʾ���ַ���
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
							mode:  0�ǵ���ģʽ  1����ģʽ
*@return:��
******************************************************************************/
void TFT_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		TFT_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
*@breif:��ʾ����
*@paremeters:	m����
							nָ��
*@return:��      
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
*@breif:��ʾ��������
*@paremeters:	x,y��ʾ����
							num Ҫ��ʾ��������
							len Ҫ��ʾ��λ��
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
*@return:��
******************************************************************************/
void TFT_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				TFT_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	TFT_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
*@breif:��ʾ��λС������
*@paremeters:	x,y��ʾ����
							num Ҫ��ʾС������
							len Ҫ��ʾ��λ��
							fc �ֵ���ɫ
							bc �ֵı���ɫ
							sizey �ֺ� 
*@return:��
******************************************************************************/
void TFT_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			TFT_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	TFT_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


/******************************************************************************
*@breif:��ʾͼƬ
*@paremeters:	x,y�������  
							length ͼƬ����
							width  ͼƬ���
							pic[]  ͼƬ����    
*@return:��
******************************************************************************/
void TFT_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	TFT_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			TFT_WR_DATA8(pic[k*2]);
			TFT_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}


/******************************************************************************
*@breif:TFT��ĻDemoչʾ
*@paremeters:��  
*@return:��
******************************************************************************/
void TFT_Demo_Show(void)
{	
	if(TFT_Init_State.TFT_Init_Flag == 1)
	{
		TFT_ShowPicture(60,60,120,120,Eyes_Photo);
//		TFT_Fill(0,0,240,240,GREEN);
//		HAL_Delay(1000);
//		TFT_Fill(0,0,240,240,RED);
//		HAL_Delay(1000);
//		TFT_Fill(0,0,240,240,BLUE);
//		HAL_Delay(1000);
	}
}



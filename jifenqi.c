#include<reg51.h>

#define LEDData P0

unsigned char code LEDCode[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

unsigned char minit,second,count,count1;        	//�֣��룬������

sbit add1=P1^0;						//�׶Լӷ֣�ÿ��һ�μ�1��   /��δ��ʼ����ʱΪ��ʱ���
sbit dec1=P1^1;						//�׶Լ��֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ���
sbit exchange=P1^2;					//��������
sbit add2=P1^3;						//�ҶԼӷ֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ����
sbit dec2=P1^4;						//�ҶԼ��֣�ÿ��һ�μ�1��	/��δ��ʼ����ʱΪ��ʱ����
sbit secondpoint=P0^7;				//��������
//----���ε�������ܵ�λ------
sbit led1=P2^7;
sbit led2=P2^6;
sbit led3=P2^5;
sbit led4=P2^4;
sbit led5=P2^3;
sbit led6=P2^2;
sbit led7=P2^1;
sbit led8=P2^0;
sbit led9=P3^7;
sbit led10=P3^6;
sbit led11=P3^5;

sbit alam=P1^7;						//����

bit  playon=0;						//�������б�־λ��Ϊ1ʱ��ʾ������ʼ����ʱ����
bit  timeover=0;					//����������־λ��Ϊ1ʱ��ʾʱ���Ѿ���
bit  AorB=0;						//���ҶԽ���λ�ñ�־λ
bit  halfsecond=0;					//�����־λ

unsigned int scoreA;				//�׶ӵ÷�
unsigned int scoreB;				//�Ҷӵ÷�
		

void Delay5ms(void)
{
	unsigned int i;
	for(i=100;i>0;i--);
}


void display(void)
{
//-----------��ʾʱ���--------------
	LEDData=LEDCode[minit/10];
	led1=0;
	Delay5ms();
	led1=1;
	LEDData=LEDCode[minit%10];
	led2=0;
	Delay5ms();
	led2=1;
//-------------�������------------
	if(halfsecond==1)
		LEDData=0x80;
	else
		LEDData=0x00;
	led2=0;
	Delay5ms();
	led2=1;
	secondpoint=0;
//-----------��ʾʱ����------------
	LEDData=LEDCode[second/10];
	led3=0;
	Delay5ms();
	led3=1;
	LEDData=LEDCode[second%10];
	led4=0;
	Delay5ms();
	led4=1;
//-----------��ʾ1��ķ�����λ-------
	if(AorB==0)
		LEDData=LEDCode[scoreA/100];
	else
		LEDData=LEDCode[scoreB/100];
	led5=0;
	Delay5ms();
	led5=1;
//---------------��ʾ1�������ʮλ-----------
	if(AorB==0)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led6=0;
	Delay5ms();
	led6=1;

//---------------��ʾ1������ĸ�λ-----------
	if(AorB==0)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led7=0;
	Delay5ms();
	led7=1;

//-----------��ʾ2������İ�λ-------
	if(AorB==1)
		LEDData=LEDCode[scoreA/100];
	else
		LEDData=LEDCode[scoreB/100];
	led8=0;
	Delay5ms();
	led8=1;
//-----------��ʾ2�������ʮλ-----------
	if(AorB==1)
		LEDData=LEDCode[(scoreA%100)/10];
	else
		LEDData=LEDCode[(scoreB%100)/10];
	led9=0;
	Delay5ms();
	led9=1;

//-----------��ʾ2������ĸ�λ-----------
	if(AorB==1)
		LEDData=LEDCode[scoreA%10];
	else
		LEDData=LEDCode[scoreB%10];
	led10=0;
	Delay5ms();
	led10=1;
}


//=========================����������================================================
void keyscan(void)
{
	if(playon==0)
	{
		if(add1==0)
		{
			display();
			if(add1==0);
			{
				if(minit<99)
					minit++;
				else
					minit=99;
			}
			do
				display();
			while(add1==0);
		}

		if(dec1==0)
		{
			display();
			if(dec1==0);
			{
				if(minit>0)
					minit--;
				else
					minit=0;
			}
			do
				display();
			while(dec1==0);
		}

		if(add2==0)
		{
			display();
			if(add2==0);
			{
				if(second<59)
					second++;
				else
					second=59;
			}
			do
				display();
			while(add2==0);
		}

		if(dec2==0)
		{
			display();
			if(dec2==0);
			{
				if(second>0)
					second--;
				else
					second=0;
			}
			do
				display();
			while(dec2==0);
		}

		if(exchange==0)
		{
			display();
			if(exchange==0);
			{
				TR1=0;					//�ر�T1������
				alam=1;					//�ر���
   				AorB=~AorB;				//��������	
				minit=15;				//����ʱ��Ԥ��Ϊ15��00
				second=0;
			}
			do
				display();
			while(exchange==0);
		}	
	}
	else
	{
		if(add1==0)
		{
			display();
			if(add1==0);
			{
				if(AorB==0)
				{
					if(scoreA<999)
						scoreA++;
					else
						scoreA=999;
				}
				else
				{
					if(scoreB<999)
						scoreB++;
					else
						scoreB=999;
				}
			}
			do
				display();
			while(add1==0);
		}

		if(dec1==0)
		{
			display();
			if(dec1==0);
			{
				if(AorB==0)
				{
					if(scoreA>0)
						scoreA--;
					else
						scoreA=0;
				}
				else
				{
					if(scoreB>0)
						scoreB--;
					else
						scoreB=0;
				}
			}
			do
				display();
			while(dec1==0);
		}

		if(add2==0)
		{
			display();
			if(add2==0);
			{
				if(AorB==1)
				{
					if(scoreA<999)
						scoreA++;
					else
						scoreA=999;
				}
				else
				{
					if(scoreB<999)
						scoreB++;
					else
						scoreB=999;
				}
			}
			do
				display();
			while(add2==0);
		}

		if(dec2==0)
		{
			display();
			if(dec2==0);
			{
				if(AorB==1)
				{
					if(scoreA>0)
						scoreA--;
					else
						scoreA=0;
				}
				else
				{
					if(scoreB>0)
						scoreB--;
					else
						scoreB=0;
				}
			}
			do
				display();
			while(dec2==0);
		}
	}
}
	


//******************************������*************************************************
void main(void)
{
	TMOD=0x11;
 	TL0=0xb0;
 	TH0=0x3c;
 	TL1=0xb0;
 	TH1=0x3c;
	minit=15;				//��ʼֵΪ15��00
	second=0;
 	EA=1;
	ET0=1;
	ET1=1;
 	TR0=0;
	TR1=0;
	EX0=1;
	IT0=1;
	IT1=1;
//	EX1=1;
	PX0=1;
//	PX1=1;
	PT0=0;
	P1=0xFF;
	P3=0xFF;
 	while(1)
 	{
		keyscan();
		display();			
    }
}


void PxInt0(void) interrupt 0
{
	Delay5ms();
	EX0=0;
	alam=1;
	TR1=0;
	if(timeover==1)
	{
		timeover=0;
	}

	if(playon==0)
	{
		playon=1;				//��ʼ��־λ
		TR0=1;					//������ʱ
	}
	else
	{
		playon=0;				//��ʼ��־λ���㣬��ʾ��ͣ
		TR0=0;					//��ʱ��ʱ
	}	
	EX0=1;						//���ж�	
}

/*
void PxInt1(void) interrupt 2
{
	Delay5ms();
	EX1=0;						//���ж�
	if(timeover==1)				//����������־������һ�ڽ�����ſ��Խ�������;���ܽ�������
	{
		TR1=0;					//�ر�T1������
		alam=1;					//�ر���
   		AorB=~AorB;				//��������	
		minit=15;				//����ʱ��Ԥ��Ϊ15��00
		second=0;
	}
	EX1=1;						//���ж�
}
*/


//*********************************�жϷ�����**************************************
void  time0_int(void) interrupt 1 
{
 	TL0=0xb0;
 	TH0=0x3c;
 	TR0=1;
  	count++;
	if(count==10)
	{
		halfsecond=0;
	}

   	if(count==20)
   	{
		count=0;
		halfsecond=1;
	
    	if(second==0)
	 	{
			if(minit>0)
			{
				second=59;
				minit--;
			}
			else
			{
				timeover=1;
				playon=0;
				TR0=0;
				TR1=1;
			}
		}
		else
			second--;
   	}
}


//*********************************�жϷ�����**************************************
void  time1_int(void) interrupt 3
{
	TL1=0xb0;
 	TH1=0x3c;
 	TR1=1;
  	count1++;
	if(count1==10)
	{
		alam=0;
	}

   	if(count1==20)
   	{
		count1=0;
		alam=1;
	}
} 

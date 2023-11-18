#include <REGX52.H>
#include "Key.h"
#include "Timer0.h"
#include "Nixie.h"
#include "AT24C02.H"
#include "Delay.h"

unsigned char KeyNum,TimeFlag;
unsigned char Min,Sec,Msec;

void main()
{
	Timer0Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			TimeFlag=KeyNum;
		}
		if(KeyNum==2)
		{
			Min=0;
			Sec=0;
			Msec=0;
		}
		if(KeyNum==3)
		{
			AT24C02_WriteByte(0,Min);
			Delay(5);
			AT24C02_WriteByte(1,Sec);
			Delay(5);
			AT24C02_WriteByte(2,Msec);
			Delay(5);
			
		}
		if(KeyNum==4)
		{
			Min=AT24C02_ReadByte(0);
			Sec=AT24C02_ReadByte(1);
			Msec=AT24C02_ReadByte(2);
			
		}		
		    Nixie_Buf_(3,11);
	        Nixie_Buf_(6,11);
		    Nixie_Buf_(1,Min/10);
			Nixie_Buf_(2,Min%10);
			Nixie_Buf_(4,Sec/10);
			Nixie_Buf_(5,Sec%10);
			Nixie_Buf_(7,Msec/10);
			Nixie_Buf_(8,Msec%10);
	}
}
void TimeCount()
{
	Msec++;
	if(Msec>99)
	{
		Msec=0;
		Sec++;
		if(Sec>59)
		{
			Sec=0;
			Min++;
			if(Min>59)
			{
				Min=0;
			}
		}
	}
	
}


void Timer0_Rountine() interrupt 1
{    //中断函数模板
	static unsigned int Count0,Count1,Count3;
	TL0 = 0x66;		 
	TH0 = 0xFC;
	Count0++;
    Count1++;
	if(TimeFlag==1)
	{
	    Count3++;
	}
	if(Count0>=20)
	{
		Count0=0;
		Key_Loop();
	}
	if(Count1>=2)
	{
		Count1=0;
		Nixie_Loop();
	}
	if(Count3>=10)
	{
		Count3=0;
		TimeCount();
	}
 }
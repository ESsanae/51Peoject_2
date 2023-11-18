#include <REGX52.H>
//#include "Delay.h"
/**
  * @brief  获取独立按键的键码
  * @param  无
  * @retval 按下按键的键码 K1--K4 无按键按下放回值为0
  */
  
unsigned char Key_Number;

unsigned char Key()
{
	unsigned char Temp;
	Temp=Key_Number;
	Key_Number=0;
	return Temp;
}


unsigned char Key_GetState()
{
	unsigned char Keynum = 0;
	if(P3_1==0){Keynum=1;}
	if(P3_0==0){Keynum=2;}
	if(P3_2==0){Keynum=3;}
	if(P3_3==0){Keynum=4;}
	return Keynum;
}

void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	if(LastState==1&&NowState==0)
	{
		Key_Number=1;
	}
	if(LastState==2&&NowState==0)
	{
		Key_Number=2;
	}
	if(LastState==3&&NowState==0)
	{
		Key_Number=3;
	}
	if(LastState==4&&NowState==0)
	{
		Key_Number=4;
	}	
}
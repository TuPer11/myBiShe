#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "CountSensor.h"
#include "AD.h"
#include "Servo.h"

uint8_t KeyNum;
int8_t Speed;
uint16_t AD0;

int main(void)
{
	CountSensor_Init();
	OLED_Init();
	//Motor_Init();
	Key_Init();
    AD_Init();
    Servo_Init();
    	Motor_Init();
	
	OLED_ShowString(1, 1, "Speed:");
	OLED_ShowString(2, 1, "Count:");
	OLED_ShowString(3, 1, "AD0:");
	while (1)
	{
        AD0 = AD_GetValue();
		KeyNum = Key_GetNum();
        
		if (KeyNum == 1)
		{

            Speed=15;
		}
		if (KeyNum == 2)
		{
			Speed =-15;
		}
        if (KeyNum == 3)
		{
			Speed =0;
		}
		Motor_SetSpeed(Speed);
        Delay_ms(100);
        Servo_SetAngle(90);
        
		OLED_ShowSignedNum(1, 7, Speed, 3);
		OLED_ShowNum(2, 7, CountSensor_Get(), 5);
        OLED_ShowNum(3, 5, AD0, 4);
        
	}
}

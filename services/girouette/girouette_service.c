#include "girouette_service.h"

int angle;
int first_capture;

int abs(int a){
    return a > 0 ? a : -a;
}

void On_Capture(uint16_t val)
{
	int angle_servo;
	if (first_capture == 1)
	{
		int index = Port_IO_Read(GPIOA, 5);
		if (index == 1) 
		{
			angle = 0;
			first_capture = 0;                                                                                                                                                                                                                                                                                                              
		}
	}
	else 
	{
		int inc = Port_IO_Read(GPIOA, 7);
		if (inc == 0)
		{
			angle++;
		} 
		else 
		{
			angle--;
		}

		angle %= 360;
		angle_servo = abs(angle);
		
		if (angle_servo > 180) 
		{
			angle_servo =360-angle_servo;
		}
		Service_Servo_Set_Angle(angle_servo);
	}
}



void Service_Girouette_Init(void) {
	first_capture = 1;
	Service_Servo_Init();
	Service_Servo_Set_Angle(0);
	Port_IO_Init_Input(GPIOA, 6);
	Port_IO_Init_Input(GPIOA, 7);
	Port_IO_Init_Input(GPIOA, 5);
	Port_IO_Init_Input(GPIOA, 5);
	Port_IO_Init_Input(GPIOA, 5);
	Timer_1234_Init(TIM3, 10);
	Timer_Capture_Configure(TIM3, 1, 0);
	Timer_Capture_Enable_IT(TIM3, 1, On_Capture);	
}

int Service_Girouette_GetAngle(void) {
	return angle;
}
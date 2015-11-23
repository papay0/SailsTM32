#include "servo_voile_service.h"

void Service_Servo_Init () 
{
	Pwm_Configure(TIM4, 3, 20000);
	Port_IO_Init_Output_Alt(GPIOB, 8);
}

void Service_Servo_Set_Angle(int AngleServo)
{
	float rate = 0.95;
	
	if (AngleServo <= 45.0)  {		
		rate = 0.90;
	} else {
		rate = ((0.05/135.0)*AngleServo)+0.883333333;
	}
	rate =(1 - rate);
	Pwm_Cyclic_RateF(TIM4, 3, rate);
}
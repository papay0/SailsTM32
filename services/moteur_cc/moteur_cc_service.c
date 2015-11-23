#include "moteur_cc_service.h"


void Service_Moteur_CC_Init()
{
	/* PA 1 : PWM (TIM2 port A channel 2), PA 2 : Sens  (TIM2 port A channel 3)*/
	float period_us = 50; // 20Khz
	Pwm_Configure(TIM2, 2, period_us);
	Port_IO_Init_Output(GPIOA, 2);
}

void Service_Moteur_CC_Commande(int Commande)
{
	if(Commande < 0)
	{

		Port_IO_Set(GPIOA, 2);
		Pwm_Cyclic_RateF(TIM2, 2, - Commande / 100.0f);
	}
	else
	{
		Port_IO_Reset(GPIOA, 2);
		Pwm_Cyclic_RateF(TIM2, 2, Commande / 100.0f);
	}
}
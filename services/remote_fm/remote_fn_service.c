#include "remote_fn_service.h"

uint16_t _lastRecord;
void (*_captureFunction) (uint16_t);

/* Transforme la valeur val (comprise entre 1000 et 2000 usecondes) en un pourcentage 
 * (valeur de -100 à 100)
 */
int _toPercent(int val)
{
	return 14 * (val - 1500) / (5*10) ;
}

/* TODO DELETE */
void _onCapture2(uint16_t val) 
{ 

}

/* Function callback appelée lors d'une capture.
   NE MARCHE PAS EN SIMU !!*/
void _onCapture(uint16_t val)
{
	// Enregistre la dernière valeur
	_lastRecord = _toPercent(val);
	// Appelle la fonction callback si elle est définie.
	if(_captureFunction != 0)
		_captureFunction(_lastRecord);
}

void Service_FM_Init()
{
	Port_IO_Init_Input(GPIOB, 6);
	// Timer_1234_Init(TIM4, 100000);  
	Timer_1234_Init(TIM4, 20000);
	Timer_Capture_Configure_PWM(TIM4, 1);
	Timer_Capture_Enable_IT(TIM4, 1, _onCapture2);
	Timer_Capture_Enable_IT(TIM4, 2, _onCapture);
	
	/*Port_IO_Init_Input(GPIOA, 6);
	Timer_1234_Init(TIM3, 1000000);
	Timer_Capture_Configure_PWM(TIM3, 1);
	Timer_Capture_Enable_IT(TIM3, 2, _onCapture);*/
	_captureFunction = 0;
	_lastRecord = 0;
}

void Service_FM_Enable_IT(void (*Callback) (uint16_t))
{
	_captureFunction = Callback;
}

int Service_FM_GetValue()
{
	return _lastRecord;
}
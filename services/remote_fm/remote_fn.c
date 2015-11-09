#include "remote_fn.h"

uint16_t _lastRecord;
void (*_captureFunction) (uint16_t);

/* Transforme la valeur val (comprise entre 1000 et 2000 usecondes) en un pourcentage 
 * (valeur de -100 à 100)
 */
int _toPercent(int val)
{
	return (val - 1500) / 5;
}

/* Function callback appelée lors d'une capture. */
void _onCapture(uint16_t val)
{
	// Enregistre la dernière valeur
	_lastRecord = _toPercent(val);
	// Appelle la fonction callback si elle est définie.
	if(_captureFunction != 0)
		_captureFunction(_lastRecord);
}

void FM_Service_Init()
{
	Port_IO_Init_Input(GPIOB, 6);
	Timer_1234_Init(TIM4, 100000);
	Timer_Capture_Configure_PWM(TIM4, 1);
	Timer_Capture_Enable_IT(TIM4, 2, _onCapture);
	_captureFunction = 0;
	_lastRecord = 0;
}

void FM_Service_Enable_IT(void (*Callback) (uint16_t))
{
	_captureFunction = Callback;
}

int FM_Service_GetValue()
{
	return _lastRecord;
}
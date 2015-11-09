#include "girouette.h"

int angle;
int first_capture;

void On_Capture(uint16_t val)
{
	if (first_capture == 1){
		int index = Port_IO_Read(GPIOA, 5);
		if (index == 1) {
			angle = 0;
			first_capture = 0;
		}
	} else {
		int inc = Port_IO_Read(GPIOA, 7);
		if (inc == 0){
			angle++;
		} else {
			angle--;
		}
		angle += 360;
		angle %= 360;
	}
}

void Init_Girouette(void) {
	first_capture = 1;
	Port_IO_Init_Input(GPIOA, 6);
	Port_IO_Init_Input(GPIOA, 7);
	Port_IO_Init_Input(GPIOA, 5);
	Timer_1234_Init(TIM3, 10);
	Timer_Capture_Configure(TIM3, 1, 0);
	Timer_Capture_Enable_IT(TIM3, 1, On_Capture);	
}

int getGirouetteAngle(void) {
	return angle;
}
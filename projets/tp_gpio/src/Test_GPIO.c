/*#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document" pour ouvrir le fichier
#include "gpio.h"
#include "clock.h"
#include "timer_1234.h"
#include "adc.h"
*/
/*int a = 0;
int first_capture = 1;
void On_Capture(uint16_t val)
{
	if (first_capture == 1){
		int index = Port_IO_Read(GPIOA, 5);
		if (index == 1) {
			a = 0;
			first_capture = 0;
		}
	} else {
		int inc = Port_IO_Read(GPIOA, 7);
		if (inc == 0){
			a++;
		} else {
			a--;
		}
		a += 360;
		a %= 360;
	}
}
int TEST_Capture(void)
{
	Port_IO_Init_Input(GPIOA, 6);
	Port_IO_Init_Input(GPIOA, 7);
	Port_IO_Init_Input(GPIOA, 5);
	Timer_1234_Init(TIM3, 10);
	Timer_Capture_Configure(TIM3, 1, 0);
	Timer_Capture_Enable_IT(TIM3, 1, On_Capture);
while(1) { }
}
*/

#include "girouette.h"

int main (void)
{
	CLOCK_Configure();
	Init_Girouette();
	while (1){}
	return 0;
}
#include "gpio.h"
#include "adc.h"
#include "usart.h"
#include "usart_service.h"

void Service_Usart_Init()
{
	Usart_Configure(USART1);
	Port_IO_Init_Output_Alt (GPIOA,9);	
	Init_ADC_Single_Conv(ADC2, 12);
	//PA9 en output push pull alternate fn 
}

int Service_Usart_Is_Low_Battery()
{
	float batterie;
	Port_IO_Init_Input(GPIOC,2);
	batterie = ADC_Single_Conv(ADC2);
	batterie = batterie*3.3000/4095.0000; 
	return batterie < 0.80*12.0/13.0;
}

/*
La valeur initiale de la batterie est 12V. 
Pour 3.3V , j'obtiens une valeur convertie de 4095.
*/ 
void Service_Usart_Start_Transmission(void) //ouvrir X-CTU
{
	char BUFFERUART [15] = "BATTERIE_FAIBLE";
	Usart_Send_Message(USART1,BUFFERUART);
	while (1) {}
}



//****************
//test de la transmission sans s'occuper de la batterie
/*
int main(void)
{
	start_transmission();
	//float b = niv_batterie();
	return 1;
}

//test niveau batterie Résultat correct à 10^-3 près.

int main(void) 
{
	while(1){
	float a = niv_batterie();
	
	}
	return 1;
}
*/










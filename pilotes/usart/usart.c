#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "clock.h"

void Usart_Configure(USART_TypeDef * Usart)
{
	CLOCK_Configure();
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	Usart->CR1 |= USART_CR1_UE; //enable usart
	Usart->CR1 &= ~USART_CR1_M; //transmission de 8 bit
	Usart-> BRR = 0b1100 ; //fraction
	Usart->BRR &= ~((0xFFF)<<4);//mantisse 
	Usart-> BRR |= 468 <<4 ;
}

int Is_Usart_Transmission_Ended(USART_TypeDef * Usart)
{
	//la transmission de la frame est terminée lorsque TXE et TC sont égaux à 1
	if (((Usart->SR & USART_SR_TXE) == USART_SR_TXE ) && ((Usart->SR & USART_SR_TC)) == (USART_SR_TC))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void Usart_Send_Message(USART_TypeDef * Usart , char BUFFERUART[]) 
{
	int ind = 0;
		while (BUFFERUART[ind] != '\0')
		{
			Usart->CR1 |= USART_CR1_TE;
			do {
					// Attente ... 
			} while ((Usart->SR & USART_SR_TXE) == 0);
			Usart->DR = BUFFERUART[ind];
			ind++;
			do {
					// Attente ... 
			} while (Is_Usart_Transmission_Ended(Usart)==0);
			Usart->CR1 &= ~USART_CR1_TE;
		}
}

/*
int main(void)
{
	
	char BUFFERUART [15] = "BATTERIE_FAIBLE";
	configure_usart(USART1);
	Port_IO_Init_Output_Alt (GPIOA,9);
	send_mess(USART1 , BUFFERUART);
	while (1) {}
	return 1;
}
*/
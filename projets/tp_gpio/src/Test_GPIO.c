//__________________________________________________________
// projet/TP_GPIO/      MAIN.C
// Tentative de faire clignoter une diode
// BINOME :
// ETAT : compilé et testé
// MODIFICATIONS :
// 14/09     : suppression des options de compilation et nettoyage des TODO
// 1/09/2013 : 0xACC0 => Nettoyage des chemins pour windows 7 + question sur le .h
//__________________________________________________________

//____ registres de périphériques du stm_32
#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier
#include "gpio.h"
#include "clock.h"
#include "timer_1234.h"
#include "adc.h"

//TODO :
// appréciez la déclaration de GPIOB ligne 1409 :-) la valeur numérique GPIOB_BASE (ligne 1316)
// est castée en pointeur sur une structure de type GPIO_Typedef.
// A quelle adresse pointe ce pointeur (complétez la ligne suivante) ?
// GPIOB_BASE  = APB2PERIPH_BASE + ???? = ????
// APB2PERIPH_BASE = PERIPH_BASE + ????
// PERIPH_BASE = ????
// GPIOB <=> ( ( GPIO_Typedef *) 0x??????? ) 
// On construit ainsi un pointeur à l'adresse désirée. Vérifiez cette adresse
// avec la doc du Reference Manual page 167 et la Table 1 de la page 41. 
// 
// Observez la déclaration de la structure GPIO_Typedef ligne 1000 à 1010
// Sachant que GPIOB->CRH est unbe notation simplifiée de (*GPIOB).CRH, le terme GPIOB->CRH est-il
// 	a) un registre natif
//  b) un pointeur natif
//  c) une macro donnant un registre
//  d) une macro donnant un pointeur
// A quelle adresse agit GPIOB->CRH ? 0x??????

int TEST_ADC(void)
{
	Port_IO_Init_Input(GPIOA, 1);
	Init_ADC_Single_Conv(ADC1, 1);
	u16 res;
	while (1)
	{
		
		res = ADC_Single_Conv(ADC1);
		
	}
	
	return 0;
}

void On_IT_Test_PWM(void)
{
	
}

int TEST_PWM(void)
{
	int b = Timer_1234_Init(TIM3, 10);
	Timer_Active_IT(TIM3, 10, On_IT_Test_PWM);
	Pwm_Configure(TIM2, 3, 100);
	Pwm_Cyclic_RateF(TIM2, 3, 0.30);
	while(1)
	{
		int a = 55;
		a++;
	}
}

void On_Capture(uint16_t val)
{
	int a = val;
	int b = val * (TIM3->PSC+1) / 72;
	int c = TIM3->ARR;
	int d = TIM3->CCR1;
	int e = TIM3->CCR2;
}

int TEST_Capture(void)
{
	int testCapture1 = 0;
	if(testCapture1)
	{
		Port_IO_Init_Input(GPIOA, 6);
		int b = Timer_1234_Init(TIM3, 1000000);
		Timer_Capture_Configure(TIM3, 1, 0);
		Timer_Capture_Enable_IT(TIM3, 1, On_Capture);
		int a = 4;
	}
	else
	{
		Port_IO_Init_Input(GPIOA, 6);
		int b = Timer_1234_Init(TIM3, 1000000);
		Timer_Capture_Configure_PWM(TIM3, 1);
		Timer_Capture_Enable_IT(TIM3, 1, On_Capture);
		int a = 4;
	}
	while(1) { }
}
	

void On_IT(void)
{
	Port_IO_Blink(GPIOB, 9);
}

int TEST_TIMER(void)
{
 	// Cette ligne valide les horloges de quelques périphériques, pour le moment ignorez-la 
	// mais CONSERVEZ CETTE LIGNE EN DEBUT DE PROGRAMME !
 	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	RCC->APB1ENR|=  RCC_APB1ENR_TIM2EN;
	CLOCK_Configure();
	Port_IO_Init_Output(GPIOB, 9);
	Timer_1234_Init(TIM2, 500000);
	Timer_Active_IT(TIM2, 1, On_IT);
	while(1) 
	{
		
	}
	
	return 0;
}


int TEST_GPIO(void)
{	
 	// Cette ligne valide les horloges de quelques périphériques, pour le moment ignorez-la 
	// mais CONSERVEZ CETTE LIGNE EN DEBUT DE PROGRAMME !
 	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	Port_IO_Init_Output(GPIOB, 10);
	Port_IO_Init_Output(GPIOB, 9);
	while(1)
	{		
		// Allume la LED 10 si le bouton sur PA0 est appuyé.
		uint32_t bitIDR = Port_IO_Read(GPIOA, 0);
		Port_IO_SetValue(GPIOB, 10, !bitIDR);
		Port_IO_Blink(GPIOB, 9);
	}

	return 0;
}

int main (void)

{
	CLOCK_Configure();
	TEST_Capture();
	return 0;
}

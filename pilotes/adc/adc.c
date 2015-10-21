#include "adc.h"


void Init_ADC_Single_Conv(ADC_TypeDef * ADC, u8 channel)
{
	// SMPR1 et 2 : on laisse les sample time de tous les channels � 0. (1.5 cycles).
	// Quand on fait l'acquisition, la charge du condensateur d�pend de l'imp�dance de charge
	// (du truc qu'on a connect� � la broche GPIO / channel correspondant � l'ADC).
	// Si l'imp�dence d'entr�e est grande, on est oblig� d'augmenter le temps d'acquisition afin
	// que le condensateur se charge.
	// Dans notre cas, l'imp�dance d'entr�e des p�riph est faible, on laisse tout � 0.
	
	
	// ADC_SQR3 bits 0:3 -> channel sur lequel on va �chantilloner.
	
	// On active l'horloge de l'ADC correspondant.
	if(ADC == ADC1)
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	else
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	
	// Sur ADC_SQR1 les bits 23:20 d�terminent la longueur de la s�quence.
	// On force le z�ro sur ces bits.
	ADC->SQR1 = ADC->SQR1 &~ ADC_SQR1_L;
	
	ADC->SQR3 =  ADC->SQR3 &~ ADC_SQR3_SQ1; // reset des 4 bits
	ADC->SQR3 |= (channel & ADC_SQR3_SQ1);
	
	// On allume l'ADC
	ADC->CR2 |= ADC_CR2_ADON;
}

int EOC(ADC_TypeDef * ADC)
{
	return ADC->SR & ADC_SR_EOC;
}

uint16_t DR(ADC_TypeDef * ADC)
{
	// La lecture de ce registre remet � 0 EOC.
	return ADC->DR;
}

uint16_t ADC_Single_Conv(ADC_TypeDef * ADC)
{
	// On lance la conversion 
	ADC->CR2 |= ADC_CR2_ADON;
	
	while (!EOC(ADC)) { }
	
	return DR(ADC);
}
#include "pwm.h"


/* -------------------------------------------------------
 * 1. Configuration des E/S timer (Ocy) en sortie.
 * -> Dans CCMRx bits CCyS pour conf en output
 * 2. Contrôle de la polarité de la sortie y (output control)
 * -> Dans CCER -> CCxP : output polarity
 * 3. Validation de la sortie
 * -> Dans CCER -> CCxE : output enable
 * 4. mettre la pwm en mode 1 
 * Dans CCMR1 -> OCxM mode PWM mode 1
 * -----------------------------------------------------*/
int Configure_Gpio(TIM_TypeDef* Tim)
{
    if (Tim == TIM1)
        return -1;
    
	if (Tim == TIM2)
		Port_IO_Init_Output_Alt(GPIOA, 0);
	else if (Tim == TIM3)
		Port_IO_Init_Output_Alt(GPIOA, 6);
	else if (Tim == TIM4)
		Port_IO_Init_Output_Alt(GPIOB, 6);
    
    return 0;
}

uint16_t Pwm_Configure(TIM_TypeDef* Tim, int channel, float period_us)
{
    if(channel <= 0 || channel > 4)
        return -1;
    
	// Configuration des GPÏO en alternate function.
    if(Configure_Gpio(Tim))
        return -1;
	    
    // Initialise le timer.
	Timer_1234_Init(Tim, period_us);
    
    if(channel == 1)
    {
        // configuration de la sortie du CC1 du timer donné en output sur le channel numéro 1  
        Tim->CCMR1 &= ~TIM_CCMR1_CC1S;
        // mise de la polarité à 0 (logique normale) tjrs sur le numéro 1 
        Tim->CCER &= ~TIM_CCER_CC1P;
        // enable la sortie du channel 1 du timer 
        Tim->CCER |= TIM_CCER_CC1E;
        // mettre la pwm en mode 1 
        Tim->CCMR1 &= ~TIM_CCMR1_OC1M;
        Tim->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;  
    }
    else if(channel == 2)
    {
        Tim->CCMR1 &= ~TIM_CCMR1_CC2S;
        Tim->CCER &= ~TIM_CCER_CC2P;
        Tim->CCER |= TIM_CCER_CC2E;
        Tim->CCMR1 &= ~TIM_CCMR1_OC2M;
        Tim->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;  
    }
    else if(channel == 3)
    {
        Tim->CCMR2 &= ~TIM_CCMR2_CC3S;
        Tim->CCER &= ~TIM_CCER_CC3P;
        Tim->CCER |= TIM_CCER_CC3E;
        Tim->CCMR2 &= ~TIM_CCMR2_OC3M;
        Tim->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;  
    }
    else if(channel == 4)
    {
        Tim->CCMR2 &= ~TIM_CCMR2_CC4S;
        Tim->CCER &= ~TIM_CCER_CC4P;
        Tim->CCER |= TIM_CCER_CC4E;
        Tim->CCMR2 &= ~TIM_CCMR2_OC4M;
        Tim->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;  
    }
    
	
	return Tim->ARR;
}

int Pwm_Cyclic_Rate(TIM_TypeDef* Tim, int channel, uint16_t rate)
{
	if(rate < 0 || rate > Tim->ARR || channel <= 0 || channel > 4)
		return -1;
	
	uint16_t arr = Tim->ARR;
	uint16_t ccr = rate;
    
    if(channel == 1)
        Tim->CCR1 = ccr;
    else if(channel == 2)
        Tim->CCR2 = ccr;
    else if(channel == 3)
        Tim->CCR3 = ccr;
    else if(channel == 4)
        Tim->CCR4 = ccr;
        
    
    return 0;
}

int Pwm_Cyclic_RateF(TIM_TypeDef* Tim, int channel, float rate)
{
	if(rate < 0 || rate > 1 || channel <= 0 || channel > 4)
		return -1;
	
	uint16_t arr = Tim->ARR;
	uint16_t ccr = (uint16_t)(arr * rate);
    
    if(channel == 1)
        Tim->CCR1 = ccr;
    else if(channel == 2)
        Tim->CCR2 = ccr;
    else if(channel == 3)
        Tim->CCR3 = ccr;
    else if(channel == 4)
        Tim->CCR4 = ccr;
	
	return 0;
}
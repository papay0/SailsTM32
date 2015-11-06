#include "timer_1234.h"

#define EXEC(fun) if(fun != 0) { fun(); }
#define EXECA(fun, arg) if (fun != 0) { fun(arg); }
/**
 * Active l'horloge du timer donné.
 */ 
void _timer_1234_enable(TIM_TypeDef* Tim)
{
	if (Tim == TIM1)
		RCC->APB2ENR |=  RCC_APB2ENR_TIM1EN;
	else if (Tim == TIM2)
		RCC->APB1ENR |=  RCC_APB1ENR_TIM2EN;
	else if (Tim == TIM3)
		RCC->APB1ENR |=  RCC_APB1ENR_TIM3EN;
	else if (Tim == TIM4)
		RCC->APB1ENR |=  RCC_APB1ENR_TIM4EN;
}

/**
 * Retourne l'id du timer Tim dans le registre IP.
 */
u8 _timer_1234_id(TIM_TypeDef * Tim)
{
	if (Tim == TIM2)
		return 28;
	else if (Tim == TIM3)
		return 29;
	else if (Tim == TIM4)
		return 30;
	
	return -1;
}
/**
 * Retourne l'id du timer TIM dans le tableau de pointeurs de fonctions.
 */
u8 _timer_1234_id_base0(TIM_TypeDef * Tim)
{
	return _timer_1234_id(Tim) - _timer_1234_id(TIM2);
}


/** 
* @brief Configure les Timers 1, 2, 3 et 4
* @param Tim Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer considéré
* @param Period_us Intervalle de temps exprimé en µs entre
* deux débordements successifs
* @return Le durée véritable qui a été configurée (en microsecondes)
**/
float Timer_1234_Init(TIM_TypeDef* Tim, float Period_us)
{
	float PSC, ARR;
	
	_timer_1234_enable(Tim);
	// Met le bit CEN à 1 (autorise le comptage de l'horloge) 
	Tim->CR1 |= 1; 
	
	// Période de l'entrée de l'horloge.
	float tin = 1.0 / 72.0;
	float rap = Period_us / tin;
	
	// On divise par la valeur max de arr pour avoir la valeur min de psc
	PSC = (rap / 65536.0f); 
	PSC = (uint16_t)PSC + 1;
	ARR = (rap / (float)PSC);
	
	// On affecte PSC et ARR
	Tim->PSC = (uint16_t)PSC - 1;
	Tim->ARR = (uint16_t)ARR - 1;
	
	// On calcule la période réelle à laquelle est lancé le timer (en usec).
	float real_period = tin * (Tim->PSC+1) * (Tim->ARR+1);
	return real_period;
}

/**
 * @brief Retourne vrai si le timer a récemment subi un débordement.
 * Si c'est le cas, les prochains appels retourneront false jusqu'au prochain débordement.
 * @param Tim Pointeur vers le jeu de registres (TIM_TypeDef*) du timer considéré.
 */
int Timer_1234_Poll(TIM_TypeDef* Tim)
{
	if ((Tim->SR & 1) == 1) //verfifie le flag uif (bit d'interruption -> la periode est écoulée)
	{
		Tim->SR = Tim->SR & ~ 1;
		return 1;
	}
	return 0;
}




/* -------------------------------------------------------
 * 
 * 					PARTIE PWM
 * 
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

/* ----------------------------------------------------------------------------
 * Helpers
 * --------------------------------------------------------------------------*/

/**
 * Définit la valeur du flag CCXS du registre CCMR pour le channel X donné.
 */
int _cc_set_ccmr_ccxs(TIM_TypeDef* Tim, int channel, int bit1, int bit0)
{
	switch(channel)
	{
		case 1:
			Tim->CCMR1 &= ~TIM_CCMR1_CC1S;
			Tim->CCMR1 |= (TIM_CCMR1_CC1S_0 * bit0) | (TIM_CCMR1_CC1S_1 * bit1); 
			return 0;
		case 2:
			Tim->CCMR1 &= ~TIM_CCMR1_CC2S;
			Tim->CCMR1 |= (TIM_CCMR1_CC2S_0 * bit0) | (TIM_CCMR1_CC2S_1 * bit1); 
			return 0;
		case 3:
			Tim->CCMR2 &= ~TIM_CCMR2_CC3S;
			Tim->CCMR2 |= (TIM_CCMR2_CC3S_0 * bit0) | (TIM_CCMR2_CC3S_1 * bit1); 
			return 0;
		case 4:
			Tim->CCMR2 &= ~TIM_CCMR2_CC4S;
			Tim->CCMR2 |= (TIM_CCMR2_CC4S_0 * bit0) | (TIM_CCMR2_CC4S_1 * bit1); 
			return 0;
		default:
			return -1;
	}
}
/**
 * Définit la valeur de polarité du channel pour le channel X donné.
 */
int _cc_select_active_polarity(TIM_TypeDef * Tim, int channel, int polarity)
{
	switch(channel)
	{
		case 1:
			if(polarity)
				Tim->CCER &= ~TIM_CCER_CC1P;
			else
				Tim->CCER |= TIM_CCER_CC1P;
			return 0;
		case 2:
			if(polarity)
				Tim->CCER &= ~TIM_CCER_CC2P;
			else
				Tim->CCER |= TIM_CCER_CC2P;
			return 0;
		case 3:
			if(polarity)
				Tim->CCER &= ~TIM_CCER_CC3P;
			else
				Tim->CCER |= TIM_CCER_CC3P;
			return 0;
		case 4:
			if(polarity)
				Tim->CCER &= ~TIM_CCER_CC4P;
			else
				Tim->CCER |= TIM_CCER_CC4P;
			return 0;
		default:
			return -1;
	}
}


/**
 * Définit la valeur du flag TS du registre SMCR pour le channel X donné.
 */
int _cc_set_smcr_ts(TIM_TypeDef* Tim, int bit2, int bit1, int bit0)
{
	Tim->SMCR &= ~TIM_SMCR_TS;
	Tim->SMCR |= (TIM_SMCR_TS_0 * bit0) | (TIM_SMCR_TS_1 * bit1) | (TIM_SMCR_TS_2 * bit2);
	return 0;
}


/**
 * Définit la valeur du flag SMS du registre SMCR pour le channel X donné.
 */
int _cc_set_smcr_sms(TIM_TypeDef* Tim, int bit2, int bit1, int bit0)
{
	Tim->SMCR &= ~TIM_SMCR_SMS;
	Tim->SMCR |= (TIM_SMCR_SMS_0 * bit0) | (TIM_SMCR_SMS_1 * bit1) | (TIM_SMCR_SMS_2 * bit2);
	return 0;
}

/**
 * Active la capture pour le channel donné.
 */
int _cc_channel_enable(TIM_TypeDef* Tim, int channel)
{
	switch(channel)
	{
		case 1:
			Tim->CCER |= TIM_CCER_CC1E;
			return 0;
		case 2:
			Tim->CCER |= TIM_CCER_CC2E;
			return 0;
		case 3:
			Tim->CCER |= TIM_CCER_CC3E;
			return 0;
		case 4:
			Tim->CCER |= TIM_CCER_CC4E;
			return 0;
		default:
			return -1;
	}
}



/**
 * Active les IT de capture.
 */
int _cc_it_enable(TIM_TypeDef * Tim, int channel)
{
	switch(channel)
	{
		case 1:
			Tim->DIER |= TIM_DIER_CC1IE;
			return 0;
		case 2:
			Tim->DIER |= TIM_DIER_CC2IE;
			return 0;
		case 3:
			Tim->DIER |= ~TIM_DIER_CC3IE;
			return 0;
		case 4:
			Tim->DIER |= TIM_DIER_CC4IE;
			return 0;
		default:
			return -1;
	}
}
/**
 * Nettoie le flag de 
 */
int _cc_clear_if(TIM_TypeDef * Tim, int channel)
{
	switch(channel)
	{
		case 1:
			Tim->SR &= ~TIM_SR_CC1IF;
			return 0;
		case 2:
			Tim->SR &= ~TIM_SR_CC2IF;
			return 0;
		case 3:
			Tim->SR &= ~TIM_SR_CC3IF;
			return 0;
		case 4:
			Tim->SR &= ~TIM_SR_CC4IF;
			return 0;
		default:
			return -1;
	}
}


// Capture : sur un event (front montant / descendant : configurer la polarité) on écrit la
// valeur du compteur dans CCR1.
// Sur un front montant on doit reset.
int Timer_Capture_Configure_PWM(TIM_TypeDef* Tim, int channel)
{
	if(channel > 2)
		return -1;
	
	// Mode input : mappé sur le channel.
	_cc_set_ccmr_ccxs(Tim, channel, 0, 1);
	
	// front descendant
	_cc_select_active_polarity(Tim, channel, 1);
	
	// Trigger selection TI1FP1 / 2.
	if(channel == 1)
		_cc_set_smcr_ts(Tim, 1, 0, 1);
	else if(channel == 2)
		_cc_set_smcr_ts(Tim, 1, 1, 0);
		
	// Sur front montant du trigger sélectionné -> reset de CNT
	_cc_set_smcr_sms(Tim, 1, 0, 0);
	
	// Active les channel de CC
	_cc_channel_enable(Tim, channel);
	
	return 0;
}

int Timer_Capture_Configure(TIM_TypeDef* Tim, int channel, int polarity)
{	
	// Front descendant / front montant
	_cc_select_active_polarity(Tim, channel, polarity);
	
	// Configuration en input.
	_cc_set_ccmr_ccxs(Tim, channel, 0, 1);
	
	// Active les channel de CC
	_cc_channel_enable(Tim, channel);
	
	return 0;
}



/* -------------------------------------------------------
 * 
 * 					IT Handlers
 * 
 * -----------------------------------------------------*/
/**
 * Fonctions callback des timers.
 */
void (* Timer_Function[4])(void);
void (* Capture_Function[4][4])(uint16_t);

/**
 * Gère les intéruptions des timers.
 */
void _timer_handle_it(TIM_TypeDef * Tim)
{
	if(Tim->SR & TIM_SR_UIF)
	{
		Tim->SR &= ~(TIM_SR_UIF);
		EXEC(Timer_Function[_timer_1234_id_base0(Tim)]);
	}
}

// Fonction gérant les it de capture compare.
void _cc_handle_it(TIM_TypeDef * Tim)
{
	#define ToMicrosec(t) (t * (Tim->PSC+1) * (Tim->ARR+1) / 72);
	if(Tim->SR & TIM_SR_CC1IF)
	{
		EXECA(Capture_Function[_timer_1234_id_base0(Tim)][0], ToMicrosec(Tim->CCR1) );
		Tim->SR &= ~TIM_SR_CC1IF;
	}
	
	if(Tim->SR & TIM_SR_CC2IF)
	{
		EXECA(Capture_Function[_timer_1234_id_base0(Tim)][1], ToMicrosec(Tim->CCR2));
		Tim->SR &= ~TIM_SR_CC2IF;
	}
	
	if(Tim->SR & TIM_SR_CC3IF)
	{
		EXECA(Capture_Function[_timer_1234_id_base0(Tim)][2], Tim->CCR3);
		Tim->SR &= ~TIM_SR_CC2IF;
	}
	
	if(Tim->SR & TIM_SR_CC4IF)
	{
		EXECA(Capture_Function[_timer_1234_id_base0(Tim)][3], Tim->CCR4);
		Tim->SR &= ~TIM_SR_CC3IF;
	}
	
}

void _timer_enable_it(TIM_TypeDef * timer, u8 priority)
{
	u8 idTimer = _timer_1234_id(timer);
	NVIC->IP[idTimer] = priority << 4;
	NVIC->ISER[0] = 0x01 << idTimer;
}

/** 
* Configure la routine d'interruption d'un Timer
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer considéré
* @param Priority Niveau de priorité de l'interruption
* @param IT_function Pointeur sur la fonction qui sera exécutée dans le routine
d'interruption
**/
void Timer_Active_IT(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void))
{
	_timer_1234_enable(Timer);
	u8 idTimer = _timer_1234_id(Timer);
	u8 idTimerBase0 = _timer_1234_id_base0(Timer);
	
	// On donne la fonction d'interruption.
	Timer_Function[idTimerBase0] = IT_function;
	
	// On active les interruptions
	Timer->DIER |= 1;
	
	// On set la priorité.
	NVIC->IP[idTimer] = Priority << 4;
	NVIC->ISER[0] = 0x01 << idTimer;
}

/**
 * @brief Active les interruptions pour la capture pour un channel et un timer donné.
 * @param Tim timer sur lequel configurer l'interruption.
 * @param channel canal de capture sur lequel configurer l'interruption.
 * @param it_function fonction à appeler lors de l'interruption.
 */
int Timer_Capture_Enable_IT(TIM_TypeDef * Tim, int channel, void (*it_function) (uint16_t))
{
	Capture_Function[_timer_1234_id_base0(Tim)][channel - 1] = it_function;
	_cc_it_enable(Tim, channel);
	_timer_enable_it(Tim, 30);
	return 0;
}

void TIM2_IRQHandler(void)
{
	_timer_handle_it(TIM2);
	_cc_handle_it(TIM2);
}

void TIM3_IRQHandler(void)
{
	_timer_handle_it(TIM3);
	_cc_handle_it(TIM3);
}

void TIM4_IRQHandler(void)
{
	_timer_handle_it(TIM4);
	_cc_handle_it(TIM4);
}


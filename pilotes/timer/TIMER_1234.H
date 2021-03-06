#ifndef __TIMER_1234_H
#define __TIMER_1234_H

#include "stm32f10x.h"
#include "gpio.h"

/**
 * @brief Configure la PWM sur le timer Tim, avec la p�riode donn�e.
 * @param Tim timer sur lequel configurer la PWM.
 * Broches GPIO correspondantes : 
 * - TIM2 -> GPIOA channel 0
 * - TIM3 -> GPIOA channel 6
 * - TIM4 -> GPIOB channel 6 
 * @param R�solution de la PWM.
 * @returns -1 si �chec de l'op�ration. la r�solution de la PWM sinon.
 */
uint16_t Pwm_Configure(TIM_TypeDef* Tim, int channel, float period_us);

/**
 * @brief Configure le rapport cyclique d'une PWM.
 * Exemple d'utilisation :
 * Configuration d'une PWM avec T=100us et rapport cyclique = 1/2.
 *      int reso = Pwm_Configure(TIM1, 100);
 *      Pwm_Cyclic_Rate(TIM1, reso/2)
 * @param Tim timer sur lequel est reli� la PWM
 * @param Rapport cyclique � utiliser.
 * @returns -1 si �chec de l'op�ration. 0 sinon.
 */
int Pwm_Cyclic_Rate(TIM_TypeDef* Tim, int channel, uint16_t rate);

/**
 * @brief Configure le rapport cyclique d'une PWM.
 * /!\ Pour plus de pr�cision, utiliser Pwm_Cyclic_Rate
 * @param Tim timer sur lequel est reli� la PWM.
 * @param percent rapport cyclique � utiliser (valeur comprise entre 0 et 1)
 * @returns -1 si �chec de l'op�ration. 0 sinon.
 */
int Pwm_Cyclic_RateF(TIM_TypeDef* Tim, int channel, float rate);


/**
 * @brief Configure un channel un timer en capture.
 * Le timer doit pr�alablement �tre initialis� � la fr�quence souhait�e.
 * /!\ Le port GPIO d'entr�e doit �tre pr�alablement configur� en InputFloating.
 * @param Tim timer sur lequel configurer la pwm capture.
 * @param channel channel sur lequel "brancher" la capture.
		  /!\ channel_in doit valoir 1 ou 2 pour pouvoir utiliser un capture en PWM !!
 */
int Timer_Capture_Configure_PWM(TIM_TypeDef* Tim, int channel);
/**
 * @brief Configure deux channels d'un timer en capture.
 * Le timer doit pr�alablement �tre initialis� � la fr�quence souhait�e.
 * /!\ Le port GPIO d'entr�e doit �tre pr�alablement configur� en InputFloating.
 * @param Tim timer sur lequel configurer la pwm capture.
 * @param channel channel sur lequel "brancher" la capture.
 * @param polarity si 1 : capture sur front descendant. 0 : capture sur front montant.
 */
int Timer_Capture_Configure(TIM_TypeDef* Tim, int channel, int polarity);

/**
 * @brief Active les interruptions pour la capture pour un channel et un timer donn�.
 * @param Tim timer sur lequel configurer l'interruption.
 * @param channel canal de capture sur lequel configurer l'interruption.
 * @param it_function fonction � appeler lors de l'interruption. Le param�tre de cette 
 * fonction correspond � la p�riode en microsecondes.
 */
int Timer_Capture_Enable_IT(TIM_TypeDef * Tim, int channel, void (*it_function) (uint16_t));

/** 
* Configure les Timers 1, 2, 3 et 4
* @param Tim Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer consid�r�
* @param Period_us Intervalle de temps exprim� en �s entre
* deux d�bordements successifs
* @return Le dur�e v�ritable qui a �t� configur�e (en microsecondes)
**/
float Timer_1234_Init(TIM_TypeDef* Tim, float Period_us);

/**
 * Retourne vrai si le timer a r�cemment subi un d�bordement.
 * Si c'est le cas, les prochains appels retourneront false jusqu'au prochain d�bordement.
 * @param Tim Pointeur vers le jeu de registres (TIM_TypeDef*) du timer consid�r�.
 */
int Timer_1234_Poll(TIM_TypeDef* Tim);

/** 
* Configure la routine d'interruption d'un Timer
* @param Timer Pointeur vers le jeu de registres (de type TIM_TypeDef) du 
* timer consid�r�
* @param Priority Niveau de priorit� de l'interruption
* @param IT_function Pointeur sur la fonction qui sera ex�cut�e dans le routine
d'interruption
**/
void Timer_Active_IT(TIM_TypeDef * Timer, u8 Priority, void (*IT_function) (void));

#endif /*__TIMER_1234_H */ 
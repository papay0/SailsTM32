#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "timer_1234.h"
#include "gpio.h"

/**
 * @brief Configure la PWM sur le timer Tim, avec la période donnée.
 * @param Tim timer sur lequel configurer la PWM.
 * Broches GPIO correspondantes : 
 * - TIM2 -> GPIOA channel 0
 * - TIM3 -> GPIOA channel 6
 * - TIM4 -> GPIOB channel 6 
 * @param Résolution de la PWM.
 * @returns -1 si échec de l'opération. la résolution de la PWM sinon.
 */
uint16_t Pwm_Configure(TIM_TypeDef* Tim, int channel, float period_us);

/**
 * @brief Configure le rapport cyclique d'une PWM.
 * Exemple d'utilisation :
 * Configuration d'une PWM avec T=100us et rapport cyclique = 1/2.
 *      int reso = Pwm_Configure(TIM1, 100);
 *      Pwm_Cyclic_Rate(TIM1, reso/2)
 * @param Tim timer sur lequel est relié la PWM
 * @param Rapport cyclique à utiliser.
 * @returns -1 si échec de l'opération. 0 sinon.
 */
int Pwm_Cyclic_Rate(TIM_TypeDef* Tim, int channel, uint16_t rate);

/**
 * @brief Configure le rapport cyclique d'une PWM.
 * /!\ Pour plus de précision, utiliser Pwm_Cyclic_Rate
 * @param Tim timer sur lequel est relié la PWM.
 * @param percent rapport cyclique à utiliser (valeur comprise entre 0 et 1)
 * @returns -1 si échec de l'opération. 0 sinon.
 */
int Pwm_Cyclic_RateF(TIM_TypeDef* Tim, int channel, float rate);


int Pwm_Capture_Configure(TIM_TypeDef* Tim, int channel);
#endif
#ifndef __REMOTE_FN_H
#define __REMOTE_FN_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer_1234.h"


/**
 * @brief Initialise le système de réception FM.
 */
void Service_FM_Init();
/**
 * @brief Active le système d'interuptions du service FM.
 * La fonction donnée en paramètre sera exécutée à chaque capture, avec en argument
 * une valeur de -100 à 100 indiquant la position de la télécommande.
 */
void Service_FM_Enable_IT(void (*Callback) (uint16_t));

/**
 * @brief Retourne une valeur allant de -100 à 100 correspondant à la position de la télécommande
 * FM.
 * 0 		: centre
 * 100 	: à babord toute !
 * -100 : à tribord toute !
 */
int Service_FM_GetValue();

#endif /* __REMOTE_FN_H */
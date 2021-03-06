#ifndef __REMOTE_FN_H
#define __REMOTE_FN_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer_1234.h"


/**
 * @brief Initialise le syst�me de r�ception FM.
 */
void Service_FM_Init();
/**
 * @brief Active le syst�me d'interuptions du service FM.
 * La fonction donn�e en param�tre sera ex�cut�e � chaque capture, avec en argument
 * une valeur de -100 � 100 indiquant la position de la t�l�commande.
 */
void Service_FM_Enable_IT(void (*Callback) (uint16_t));

/**
 * @brief Retourne une valeur allant de -100 � 100 correspondant � la position de la t�l�commande
 * FM.
 * 0 		: centre
 * 100 	: � babord toute !
 * -100 : � tribord toute !
 */
int Service_FM_GetValue();

#endif /* __REMOTE_FN_H */
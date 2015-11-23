#ifndef __MOTEUR_CC_H
#define __MOTEUR_CC_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer_1234.h"

/**
 * @brief Initialise le service du moteur plateau.
 */
void Service_Moteur_CC_Init();

/**
 * @brief Envoie une commande au moteur plateau.
 * @param Commande Valeur allant de -100 à 100 indiquant
 * 	      le sens de rotation et la puissance à envoyer au moteur.
 */ 
void Service_Moteur_CC_Commande(int Commande);



#endif /* __MOTEUR_CC_H */
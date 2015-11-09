#ifndef __GIROUETTE_H
#define __GIROUETTE_H

#include "gpio.h"
#include "clock.h"
#include "timer_1234.h"

/**
 * @brief Initialisation de la girouette
 */
void Init_Girouette(void);

/**
 * @brief Récupérer la valeur de l'angle
 */
int getGirouetteAngle(void);

#endif /* __GIROUETTE_H */
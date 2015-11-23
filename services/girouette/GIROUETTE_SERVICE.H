#ifndef __GIROUETTE_H
#define __GIROUETTE_H

#include "gpio.h"
#include "clock.h"
#include "timer_1234.h"
#include "servo_voile_service.h"

/**
 * @brief Initialisation de la girouette
 */
void Service_Girouette_Init(void);

/**
 * @brief Récupérer la valeur de l'angle
 */
int Service_Girouette_GetAngle(void);

#endif /* __GIROUETTE_H */
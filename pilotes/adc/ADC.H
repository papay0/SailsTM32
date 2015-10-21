#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"

/**
 * @brief Initialise l'ADC donné sur le channel donné en mode Single Conversion.
 * Le GPIO correspondant au channel donné doit être configuré en Output Push Pull
 * que cela fonctionne.
 * @example 	Port_IO_Init_Input(GPIOA, 1);
* 				Init_ADC_Single_Conv(ADC1, 1);
 */
void Init_ADC_Single_Conv(ADC_TypeDef * ADC,  u8 channel);

/**
 * @brief Lance la conversion sur un channel de l'ADC préalablement configuré.
 */
uint16_t ADC_Single_Conv(ADC_TypeDef * ADC);

#endif
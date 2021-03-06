#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

// TODO : mettre des exemples.

/**
 * @brief Configure la broche du port donn� en mode Output push-pull.
 */
char Port_IO_Init_Output( GPIO_TypeDef * Port, u8 Broche);
/**
 * @brief Configure la broche du port donn� en mode Output push-pull (alternate function).
 */
char Port_IO_Init_Output_Alt( GPIO_TypeDef * Port, u8 Broche);
/**
 * @brief Configure la broche du port donn� en mode floating input.
 */
char Port_IO_Init_Input( GPIO_TypeDef * Port, u8 Broche);

/**
 * @brief Met � 1 la valeur d'une proche pr�alablement configur�e en mode output.
 */
void Port_IO_Set(GPIO_TypeDef * Port, u8 Broche);

/**
 * @brief Met � 0 la valeur d'une proche pr�alablement configur�e en mode output.
 */
void Port_IO_Reset(GPIO_TypeDef * Port, u8 Broche);

/**
 * @brief Inverse la valeur d'une proche pr�alablement configur�e en mode output.
 */
void Port_IO_Blink(GPIO_TypeDef * Port, u8 Broche);

/**
 * @brief D�finit la valeur d'une proche pr�alablement configur�e en mode output.
 */
void Port_IO_SetValue(GPIO_TypeDef * Port, u8 Broche, u8 Value);
/**
 * @brief Lis la valeur d'une broche pr�abalement configur�e en mode input.
 */
unsigned int Port_IO_Read(GPIO_TypeDef * Port, u8 Broche);

#endif /* __GPIO_H */

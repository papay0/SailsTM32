#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"

void Usart_Configure(USART_TypeDef * Usart);

void Usart_Send_Message(USART_TypeDef * Usart , char BUFFERUART[]);

#endif
#ifndef __USART_SERVICE_H
#define __USART_SERVICE_H
#include "stm32f10x.h"

void Service_Usart_Init();
int Service_Usart_Is_Low_Battery();
void Service_Usart_Start_Transmission();
#endif
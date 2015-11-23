#include "usart_service.h"
#include "usart.h"
#include "stm32f10x.h" 
#include "clock.h"

/*Il y a un pont diviseur afin que la tension captée par l'adc soit acceptable. 
d'ou valeur init capté par l'adc = R1/(R1+R2)*12 = 12/13 V . 
la valeur à laquelle il faut envoyer le signal est donc 80% de 12/13.
*/
void transmission()
{
	
	config_transmission();
	//if (niv_batterie() < (12/13)*0.8 ) 
	//{
	start_transmission();
	//}
}


int main(void)
{
	transmission();
	return 0;
	
}
 
/*
RESULTAT

On obtient bien le signal batterie_faible, avec des charactères apres, qui je pense représentent le bruit.
*/
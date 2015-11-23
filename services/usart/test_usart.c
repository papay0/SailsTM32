#include "usart_service.h"
#include "usart.h"
#include "stm32f10x.h" 
#include "clock.h"

/*Il y a un pont diviseur afin que la tension capt�e par l'adc soit acceptable. 
d'ou valeur init capt� par l'adc = R1/(R1+R2)*12 = 12/13 V . 
la valeur � laquelle il faut envoyer le signal est donc 80% de 12/13.
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

On obtient bien le signal batterie_faible, avec des charact�res apres, qui je pense repr�sentent le bruit.
*/
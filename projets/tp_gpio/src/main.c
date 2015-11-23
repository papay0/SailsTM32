#include "girouette_service.h"
#include "remote_fn_service.h"
#include "moteur_cc_service.h"
#include "usart_service.h"

void callback(uint16_t percent)
{
	int16_t c = percent;
	Service_Moteur_CC_Commande(c);
}

int main (void)
{
	CLOCK_Configure();
	Service_Girouette_Init();
	//Config_Transmission();

	Service_Moteur_CC_Init();
	Service_FM_Init();
	Service_FM_Enable_IT(callback);
	/*while (1) 
	{ 
		if(Is_Low_Battery())
		{
			Start_Transmission();
		}
	}*/
	while(1) { }
	return 0;
}
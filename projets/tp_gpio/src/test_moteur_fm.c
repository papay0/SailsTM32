#include "moteur_cc.h"
#include "remote_fn.h"
#include "clock.h"
/* Fichier de test EN REEL du moteur + télécommande FM.
   Ce test n'est pas simulable !!! */
void callback(uint16_t percent)
{
	int16_t c = percent;
	Service_Moteur_CC_Commande(c);
}

int main()
{
	CLOCK_Configure();
	Service_Moteur_CC_Init();
	Service_FM_Init();
	Service_FM_Enable_IT(callback);
  
	/*Moteur_CC_Commande(-50);*/
	while(1) { }
	return 0;
}
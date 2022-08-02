/* ***********************
 * 		 	 ETS
 * ***********************
 *   Equipe Proto-Pulmo
 * ***********************
 *	Dans le cadre du cours
 *			ELE400
 * ***********************
 *	Client: Martin Leduc
 *	(Projet Refelexions)
 * ***********************
 *  Travail presente a:
 *  Vincent Lacasse
 *  Bilal Alchalbi
 */


#include </usr/include/stdio.h>

#include "sendosc.h"
#include "slmx4_vcom.h"

#define RUN_TIME 10

#define DEBUG


#define FULL
#ifdef FULL
int main()
{
	/*CLASS: slmx4
	* isOpen
	* numSamplers
	* iterations*/
	slmx4 sensor;


	/* Begin():
	*  init_serial() : Connection vers le port serie virtuel du capteur
	*  OpenRadar()	 : Envoie la commande d'initialisation au capteur*/
	sensor.Begin();

	/* Iterations() :
	 * 	Demande au capteur d'envoyer la valeur du registre 'iterations'
	 * 	->Affiche un message du succes suivi de la valeur*/
	sensor.Iterations();


	/* TryUpdateChip() :
		 * 	Demande au capteur de recevoir une valeur et de la placer dans un registre
		 * 	->Affiche un message du succes suivi de la valeur 'Number of samplers'
		 * 		  (mise a jour lors d'un changement dans les registres de configuration)*/
	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);
	
#ifdef DEBUG
	timeOut run_time;
	run_time.initTimer();

while(run_time.elapsedTime_ms() < 1000 * RUN_TIME)
	sensor.GetFrameNormalized();
#else
while(1)	//TODO: Catch and break this loop
	sensor.GetFrameNormalized();
#endif

	/* End():
	 *  ClsoeRadar() : Envoie la commande de fermeture au capteur*/
	sensor.End();

	return 0;
}











#else
int main()
{
	slmx4 sensor;
	//sensor.init_serial();

	sensor.Begin();
	sensor.End();
}
#endif


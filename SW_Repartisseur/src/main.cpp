#include <stdio.h> 
#include <stdlib.h> 

#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "filters.h"
#include "respiration.h"

#include "testData.h"

#define BREATH_SIZE 6

#define PERIOD 50

int main()
{
	slmx4 sensor;

	sensor.Begin();
	sensor.Iterations();

	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);
	sensor.TryUpdateChip(slmx4::PPS);

	respiration_data_t* resp_data = respiration_init(sensor.numSamplers, BREATH_SIZE);


	_Float32* tablo = (_Float32*)malloc(sizeof(_Float32)*sensor.numSamplers);

	timeOut timer;

	while(1){
		timer.initTimer();

		sensor.GetFrameNormalized(tablo);

		respiration_update(tablo, sensor.numSamplers, resp_data);

		FILE* fichier = fopen("./FILE", "w+");
		for(int i = 0; i < sensor.numSamplers-1; i++){
			fprintf(fichier,"%f,",tablo[i]);
		}

		fprintf(fichier,"%f",tablo[sensor.numSamplers-1]);

		fflush(fichier);
		fclose(fichier);

		if(timer.elapsedTime_ms() > PERIOD){
			fprintf(stderr, "CAUTION : CANNOT RESPECT DEFINED PERIOD || Elapsed : %ims, Period : %ims\r\n",(int)timer.elapsedTime_ms(), PERIOD);
		}
		else{
			while(timer.elapsedTime_ms() < PERIOD);
		}
	}
	
	sensor.End();


	return 0;
}




#include <stdio.h> 
#include <stdlib.h> 

#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "filters.h"

#include "testData.h"



int main()
{
	/*
	filter_data_t filter1_data;

	filter1_data.gain = 0.1;
	filter1_data.output = 0;
	filter1_data.input[0] = 0;
	filter1_data.type = HIGHPASS;

	float outputarr[50];

	filter_data_2d_t* filt2d_dat = init_2d_filter(50);

	set2dFilterParam(HIGHPASS, 0.1, filt2d_dat);

	for(int i = 0; i < 50; i++){
		update2dFilter(test_data[i], outputarr, filt2d_dat);
		for(int j = 0; j < 50; j++){
			printf("%f,",outputarr[j]);
		}
		printf("%f,", test_data[i][39]);
		float output = updateFilter(test_data[i][39], &filter1_data);
		printf("\r\n");
	}
	//float output = updateFilter(0.5, &filter1_data);
	*/
	

	slmx4 sensor;
	//sensor.init_serial();

	sensor.Begin();



	sensor.Iterations();

	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);
	sensor.TryUpdateChip(slmx4::PPS);


	_Float32* tablo = (_Float32*)malloc(sizeof(_Float32)*sensor.numSamplers);

	sensor.GetFrameNormalized(tablo);

	for(int i = 0; i < sensor.numSamplers-1; i++){
		printf("%f,",tablo[i]);
	}

	printf("%f",tablo[sensor.numSamplers-1]);

	sensor.End();


	return 0;
}




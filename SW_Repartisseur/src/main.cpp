#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "filters.h"

#include "testData.h"



int main()
{
	filter_data_t filter1_data;

	filter1_data.gain = 0.1;
	filter1_data.output = 0;
	filter1_data.input[0] = 0;
	filter1_data.type = HIGHPASS;

	filter_data_2d_t* filt2d_dat = init_2d_filter(50);

	set2dFilterParam(LOWPASS, 0.1, filt2d_dat);

	for(int i = 0; i < 50; i++){
		printf("%f,", test_data[i][39]);
		float output = updateFilter(test_data[i][39], &filter1_data);
		printf("%f\r\n", output);
	}
	//float output = updateFilter(0.5, &filter1_data);

	/*

	slmx4 sensor;
	//sensor.init_serial();

	sensor.Begin();



	sensor.Iterations();

	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);

	sensor.GetFrameRaw();


	//sensor.GetFrameNormalized();

	//sendosc();	//Test sine

	sensor.End();

*/
	return 0;
}




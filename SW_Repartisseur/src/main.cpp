#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "filters.h"

#include "testData.h"



int main()
{
	filter_data_t filter1_data;

	filter1_data.gain = 0.01;
	filter1_data.output = 0.02;
	filter1_data.input[0] = 0.02;

	float output = updateFilter(0.5, &filter1_data);

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




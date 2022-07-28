#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
//#include "matlab_XEP.h"

#define FULL


#ifdef FULL
int main()
{

	slmx4 sensor;
	//sensor.init_serial();

	sensor.Begin();



	sensor.Iterations();

	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);

	//sensor.GetFrameRaw();


	//sensor.GetFrameNormalized();

	//sendosc();	//Test sine

	sensor.End();


	return 0;
}
#else
int main()
{
	Serial test;

	test.Connect("/dev/serial/by-id/usb-NXP_SEMICONDUCTORS_MCU_VIRTUAL_COM_DEMO-if00", 115200);
	sleep(2);
	test.Disconnect();
}
#endif


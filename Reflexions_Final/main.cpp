#include "sendosc.h"
#include "slmx4_vcom.h"
//#include "matlab_XEP.h"

#define DEBUG


int main()
{

	slmx4 sensor;

	sensor.Begin();
	sensor.GetFrameNormalized();

	//sendosc();	//Test sine


	return 0;
}





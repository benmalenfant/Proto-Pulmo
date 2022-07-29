#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "serialib.h"
#include <stdio.h>

	// Initialise circular buffer.
	charBuffer myBuffer;

	charBuffer* myBuffer_ptr;


#define FULL
#ifdef FULL
int main()
{



	bufferInit(myBuffer,1024,char);
	myBuffer_ptr = &myBuffer;
	set_buff_ptr(myBuffer_ptr);	//Make buffer ptr available to thread

	slmx4 sensor(myBuffer_ptr);

	sensor.Begin();



	//sensor.Iterations();

	sensor.TryUpdateChip(slmx4::rx_wait);
	sensor.TryUpdateChip(slmx4::frame_start);
	sensor.TryUpdateChip(slmx4::frame_end);
	sensor.TryUpdateChip(slmx4::ddc_en);







	//sensor.GetFrameRaw();


	//sensor.GetFrameNormalized();

	//sendosc();	//Test sine

	//sleep(1);

	sensor.End();

	sleep(1);

	sensor.serial.threadRunning=0;
	close(sensor.serial.fd);

	for(int i = 5; i; --i)
	{
		char _read;
		bufferRead(myBuffer_ptr,_read);
		printf("READ:   %c\n", _read);
	}

	bufferDestroy(myBuffer_ptr);

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


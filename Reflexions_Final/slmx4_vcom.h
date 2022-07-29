#ifndef SENSOR_DEF
#define SENSOR_DEF

#include <iostream>
#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <stdint.h>

#include "serialib.h"
//#include "async_serial.h"
#include "Proto_Pulmo.h"

//#define SERIAL_PORT "/dev/ttyACM0"

//#define ASYNC

#define SERIAL_PORT "/dev/serial/by-id/usb-NXP_SEMICONDUCTORS_MCU_VIRTUAL_COM_DEMO-if00"

class slmx4
{

public:
	slmx4();

#ifndef ASYNC
	serialib serial;
#else
	Serial serial;
#endif

	void Begin();
	void End();
	void GetFrameNormalized();
	void GetFrameRaw();

	int isOpen;

	void OpenRadar();
	void CloseRadar();

	int check_ACK();

#ifndef DEBUG
private:
#endif

	enum cmds{rx_wait,frame_start,frame_end,ddc_en};

	void init_device();
	void init_serial();
	void updateNumberOfSamplers();
	void Iterations();

	void TryUpdateChip(int);

	int status;
	int numSamplers;



};


#endif

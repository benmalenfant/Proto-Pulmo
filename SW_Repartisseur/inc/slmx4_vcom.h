#ifndef SENSOR_DEF
#define SENSOR_DEF

#include <iostream>
#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#include <stdint.h>

#include "serialib.h"

//#define DEBUG

#define SERIAL_PORT "/dev/serial/by-id/usb-NXP_SEMICONDUCTORS_MCU_VIRTUAL_COM_DEMO-if00"
#define TIMEOUT_MS 1000

class slmx4
{
	serialib serial;
	int status;
	int numSamplers;
	int isOpen;

	void init_device();
	void init_serial();
	void OpenRadar();
	void CloseRadar();

	int check_ACK();

public:
	slmx4();
	enum cmds{rx_wait,frame_start,frame_end,ddc_en, PPS};

	void Begin();
	void End();
	void GetFrameNormalized();
	void GetFrameRaw();
	void updateNumberOfSamplers();
	void Iterations();
	void TryUpdateChip(int);
};


#endif

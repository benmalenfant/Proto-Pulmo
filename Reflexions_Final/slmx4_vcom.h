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

#define SERIAL_PORT "/dev/ttyACM0"

class slmx4
{

public:
	slmx4();

	serialib serial;

	void Begin();
	void GetFrameNormalized();



	void OpenRadar();
	void CloseRadar();

	int check_ACK();


private:

	void init_device();
	void init_serial();
	void updateNumberOfSamplers();

	int status;
	int numSamplers;
	int isOpen;


};


#endif

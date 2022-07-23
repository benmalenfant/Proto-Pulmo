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

class slmx4
{

public:
	slmx4();

	void Begin();
	void init_device();
	void init_serial();
	void termios_config();
	void updateNumberOfSamplers();

	void OpenRadar();
	void CloseRadar();
	void getData(void*, int);
	void* Item(int CMD);
	int device_id;
	struct termios tty;

	int status;
	int numSamplers;
	int isOpen;

private:
	enum type{INT, CHAR, STRING};

};


#endif

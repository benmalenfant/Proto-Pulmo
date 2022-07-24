#include "serialib.h"
#include "matlab_XEP.h"


serialib serial;


void init_serial()
{


	// Connection to serial port
	char errorOpening = serial.openDevice(SERIAL_PORT, 115200);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening!=1)
    	printf ("ERROR connection to serial port: %i\n", (int)errorOpening);
    else
    {
    	printf ("Successful connection to %s\n",SERIAL_PORT);
    	serial.setDTR();
    	serial.setRTS();
    }

}

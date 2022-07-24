// C library headers

#include "slmx4_vcom.h"





#define BUFF_SIZE 32

#define SLEEP_US 1000

#define DEBUG



slmx4::slmx4()
{
	isOpen = 0;
	numSamplers = 0;
	status = -1;
}

void slmx4::Begin()
{
	init_serial();

	init_device();

	OpenRadar();
	//CloseRadar();

	printf("numSamplers: %i", numSamplers);

	//cout << "bins = " << numSamplers << endl;
}

void slmx4::init_device()
{
	serial.writeString("NVA_CreateHandle()");

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'init_device'\n"); }
    else { printf("ERROR: Reading ACK in 'init_serial'\n"); }
#endif
}


int slmx4::check_ACK()
{
	char buffer[BUFF_SIZE];

	serial.readString(buffer, '0', BUFF_SIZE, SLEEP_US);

	if(!strcmp(buffer, "<ACK>")) { return 0; }
	else
	{
		//TODO stderr <<
		return -1;
	}
}


void slmx4::OpenRadar()
{
	serial.writeString("OpenRadar(X4)");

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'OpenRadar'\n"); }
    else { printf("ERROR from 'OpenRadar() \n"); }
#endif

	isOpen = 1;

	updateNumberOfSamplers();
}

void slmx4::CloseRadar()
{
	serial.writeString("Close()");

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'CloseRadar'\n"); }
    else { printf("ERROR: Reading ACK in 'CloseRadar'\n"); }
#endif
}


void slmx4::updateNumberOfSamplers()
{
	char buffer[BUFF_SIZE];

	serial.writeString("VarGetValue_ByName(SamplersPerFrame)");

	serial.readString(buffer, '0', BUFF_SIZE, SLEEP_US);

	char* token = strtok(buffer, "<");
	numSamplers = atoi(token);
}

//void slmx4 TryUpdateChip(char* reg,)
//{
//
//}

void slmx4::init_serial()
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

void slmx4::GetFrameNormalized()
{
	int frameSize = (numSamplers * 4 + 5);

	char frame[frameSize];
	int i = 0;

	char buffer;

	while(buffer != '<')
	{
		printf("buffer: %c", buffer);
		frame[i] = serial.readChar(&buffer, SLEEP_US);
		if(++i > frameSize)
			printf("Frame size error");
	}

#ifdef DEBUG
	for(int j = 0; j < frameSize; ++j)
		printf("%c ", frame[j]);
#endif

}




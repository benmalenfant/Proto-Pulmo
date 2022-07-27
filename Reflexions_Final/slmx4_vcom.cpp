// C library headers

#include "slmx4_vcom.h"





#define BUFF_SIZE 32

#define SLEEP_US 500

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

	while(!isOpen);


	//cout << "bins = " << numSamplers << endl;
}

void slmx4::init_device()
{
	serial.writeString("NVA_CreateHandle()");

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'init_device'\n"); }
    else { printf("ERROR: Reading ACK in 'init_device'\n"); }
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

	updateNumberOfSamplers();

	isOpen = 1;
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

#ifdef DEBUG
	printf("Samplers: %i\n", numSamplers);
#endif
}

void slmx4::Iterations()
{
	char buffer[BUFF_SIZE];

	serial.writeString("VarGetValue_ByName(Iterations)");

	serial.readString(buffer, '0', BUFF_SIZE, SLEEP_US);

	char* token = strtok(buffer, "<");
	int iterations = atoi(token);

#ifdef DEBUG
	printf("Iterations: %i\n", iterations);
#endif
}

void slmx4::TryUpdateChip(int cmd)
{

	switch(cmd)
	{
	case rx_wait:
		serial.writeString("VarSetValue_ByName(rx_wait,0)");
		break;
	case frame_start:
		serial.writeString("VarSetValue_ByName(frame_start,0)");
		break;
	case frame_end:
		serial.writeString("VarSetValue_ByName(frame_end,4.0)");
		break;
	case ddc_en:
			serial.writeString("VarSetValue_ByName(ddc_en,1)");
		break;
	}

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'TryUpdateChip'\n"); }
    else { printf("ERROR: Reading ACK in 'TryUpdateChip'\n"); }
#endif

    updateNumberOfSamplers();

}

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

void slmx4::GetFrameRaw()
{
	static int frameSize = (numSamplers * 8) + 5;

	//int i = frameSize;
	char* buffer = (char*)malloc(frameSize+32);

	serial.writeString("GetFrameRaw()");


	//while(--i)//buffer != '<')
	//	{
			serial.readBytes(&buffer, frameSize, 1, 10);
			//if(++i > frameSize)
			//	printf("Frame size error");
	//		if(!(i%30))
	//			printf("\n");
	//		else
	//			printf("%i ", buffer);
	//	}

	for(int i = 0; i < 100; ++i)
		printf("%i ", buffer[i]);

	free(buffer);

}

void slmx4::GetFrameNormalized()
{
	//int frameSize = (numSamplers * 4 + 5);
	//int frameSize = 11;

	//char frame[frameSize];
	int i = 10;

	printf("\n\nok\n");

	char buffer;//= 'P';

	while(--i)//buffer != '<')
	{
		serial.readBytes(&buffer, 1, 1, SLEEP_US);
		//if(++i > frameSize)
		//	printf("Frame size error");
		printf("%i . ", buffer);
	}

#ifdef DEBUG
//	for(int j = 0; j < frameSize; ++j)
//		printf("%c ", frame[j]);
#endif

}

void slmx4::End()
{
	CloseRadar();
}


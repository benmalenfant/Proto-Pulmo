// C library headers

#include "slmx4_vcom.h"
#include "sendosc.h"





#define BUFFER_SIZE 32

#define SLEEP_US 500

#define DEBUG

#ifndef ASYNC

slmx4::slmx4()
{
	isOpen = 0;
	numSamplers = 0;
	status = -1;
}

void slmx4::Begin()
{
	init_serial();

	//init_device();

	OpenRadar();
	//CloseRadar();

	while(!isOpen);


	//cout << "bins = " << numSamplers << endl;
}

void slmx4::init_device()
{
	serial.writeString("NVA_CreateHandle()");

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'init_device'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'init_device'");}
    else { printf("ERROR: Reading ACK in 'init_device'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'init_device'\n");}
#endif
}


int slmx4::check_ACK()
{
	char buffer[BUFFER_SIZE];

	//printf("Avail: %i\n", serial_rx.Available());

	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

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
    if(!check_ACK()) { printf("SUCCESS: ACK from 'OpenRadar'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'OpenRadar'");}
    else { printf("ERROR: Reading ACK in 'OpenRadar'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'OpenRadar'\n");}
#endif

	updateNumberOfSamplers();

	isOpen = 1;
}

void slmx4::CloseRadar()
{
	serial.writeString("Close()");


/*#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'CloseRadar'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'CloseRadar'");}
    else { printf("ERROR: Reading ACK in 'CloseRadar'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'CloseRadar'\n");}
#endif
*/
}


void slmx4::updateNumberOfSamplers()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(SamplersPerFrame)");



	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

	char* token = strtok(buffer, "<");
	numSamplers = atoi(token);

#ifdef DEBUG
	char text[32];
	sprintf(text, "Samplers: %i\n", numSamplers);
	printf("%s",text);
	sendosc(string_, (void*)text);
#endif
}

void slmx4::Iterations()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(Iterations)");

	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

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
    if(!check_ACK()) { printf("SUCCESS: ACK from 'TryUpdateChip'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'TryUpdateChip'");}
    else { printf("ERROR: Reading ACK in 'TryUpdateChip'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'TryUpdateChip'\n");}
#endif

    updateNumberOfSamplers();

}

void slmx4::init_serial()
{
	// Connection to serial port
	char errorOpening = serial.openDevice(SERIAL_PORT, 115200);
	//serial_rx.Connect(SERIAL_PORT, 115200);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1)
    {
    	printf ("ERROR connection to serial port: %i\n", errorOpening);
    	sendosc(string_, (void*)"ERROR connection to serial port");
    }

    else
    {
    	printf ("Successful connection to %s\n",SERIAL_PORT);
    	sendosc(string_, (void*)"Successful connection to serial port");
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


	while(int av = serial.available() < frameSize)
	{
		if(av>1)
			printf("Avail: %i\n", av);
	};// < frameSize){};

	//for(int i = 0; i <= frameSize; ++i)
	//{
		//buffer[i] = serial_rx.Get();
	//	printf("Available: %i \n", serial_rx.Available());
	//}

	//serial_rx.Disconnect();


/*
	for(int i = 0; i < 100; ++i)
		printf("%i ", buffer[i]);
		*/

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
		serial.readBytes(&buffer, 1, 1);
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
	//serial.threadRunning=0;
	//close(serial.fd);
}

#else


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
    if(!check_ACK()) { printf("SUCCESS: ACK from 'init_device'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'init_device'");}
    else { printf("ERROR: Reading ACK in 'init_device'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'init_device'\n");}
#endif
}


int slmx4::check_ACK()
{
	char buffer[BUFFER_SIZE];

	//printf("Avail: %i\n", serial_rx.Available());

	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

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
    if(!check_ACK()) { printf("SUCCESS: ACK from 'OpenRadar'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'OpenRadar'");}
    else { printf("ERROR: Reading ACK in 'OpenRadar'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'OpenRadar'\n");}
#endif

	updateNumberOfSamplers();

	isOpen = 1;
}

void slmx4::CloseRadar()
{
	serial.writeString("Close()");
	serial.Disconnect();

#ifdef DEBUG
    if(!check_ACK()) { printf("SUCCESS: ACK from 'CloseRadar'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'CloseRadar'");}
    else { printf("ERROR: Reading ACK in 'CloseRadar'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'CloseRadar'\n");}
#endif
}


void slmx4::updateNumberOfSamplers()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(SamplersPerFrame)");

	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

	char* token = strtok(buffer, "<");
	numSamplers = atoi(token);

#ifdef DEBUG
	char text[32];
	sprintf(text, "Samplers: %i\n", numSamplers);
	printf("%s",text);
	sendosc(string_, (void*)text);
#endif
}

void slmx4::Iterations()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(Iterations)");

	serial.readString(buffer, '0', BUFFER_SIZE, SLEEP_US);

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
    if(!check_ACK()) { printf("SUCCESS: ACK from 'TryUpdateChip'\n");
    sendosc(string_, (void*)"SUCCESS: ACK from 'TryUpdateChip'");}
    else { printf("ERROR: Reading ACK in 'TryUpdateChip'\n");
    sendosc(string_, (void*)"ERROR: Reading ACK in 'TryUpdateChip'\n");}
#endif

    updateNumberOfSamplers();

}

void slmx4::init_serial()
{
	// Connection to serial port
	char errorOpening = serial.Connect(SERIAL_PORT, 115200);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening)
    {
    	printf ("ERROR connection to serial port: %i\n", errorOpening);
    	sendosc(string_, (void*)"ERROR connection to serial port");
    }

    else
    {
    	printf ("Successful connection to %s\n",SERIAL_PORT);
    	sendosc(string_, (void*)"Successful connection to serial port");

    	serial.setDTR();
    	serial.setRTS();
    }
}

void slmx4::GetFrameRaw()
{

}

void slmx4::GetFrameNormalized()
{

}

#ifdef DEBUG
//	for(int j = 0; j < frameSize; ++j)
//		printf("%c ", frame[j]);
//}
#endif

void slmx4::End()
{
	CloseRadar();
}






















#endif


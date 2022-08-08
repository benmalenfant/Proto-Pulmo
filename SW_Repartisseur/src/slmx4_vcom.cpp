/*	Module slmx4_vcom :
 *
 * Auteur: Julian Davis
 *
 * Une traduction en C(++) du script matlab " vcom_xep_radar_connector.m "
 *
 * (github.com/SensorLogicInc/modules/blob/main/matlab/vcom_xep_radar_connector.m)
 *
 */

#include "slmx4_vcom.h"
#include "sendosc.h"
#include <string.h>

#define DEBUG

#define BUFFER_SIZE 32
#define ACK_SIZE 6


slmx4::slmx4()
{
	isOpen = 0;
	numSamplers = 0;
	status = -1;
}

void slmx4::setHost(const char* host) { strcpy(host_addr, host); }

int slmx4::Begin()
{
	unsigned char tmpdata;
	timeOut timer;
	timer.initTimer();
	init_serial();

	init_device();

	OpenRadar();
	

	if(isOpen)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;

}

void slmx4::init_device()
{
	serial.writeString("NVA_CreateHandle()");

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'init_device'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'init_device'", host_addr);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'init_device'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'init_device'\n", host_addr);
		#endif
	}
}


int slmx4::check_ACK()
{
	char ack_[32];
	
	serial.readBytes(ack_, 32-1, TIMEOUT_MS);

	ack_[5] = 0;

	if(!strcmp(ack_, "<ACK>")){ 
		return EXIT_SUCCESS; 
	}
	else{
		return EXIT_FAILURE;
	}
}


void slmx4::OpenRadar()
{
	serial.writeString("OpenRadar(X4)");

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'OpenRadar'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'OpenRadar'", host_addr);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'OpenRadar'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'OpenRadar'\n", host_addr);
		#endif
	}

	updateNumberOfSamplers();

	isOpen = 1;
}

void slmx4::CloseRadar()
{
	serial.writeString("Close()");

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'CloseRadar'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'CloseRadar'", host_addr);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'CloseRadar'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'CloseRadar'\n", host_addr);
		#endif
	}

}


void slmx4::updateNumberOfSamplers()
{
	char buffer[1024] = {0};

	serial.flushReceiver();
	serial.writeString("VarGetValue_ByName(SamplersPerFrame)");

	serial.readBytes(buffer, 1024, TIMEOUT_MS, SLEEP_US);

	//printf("%s\n", buffer);

	char* _errstr;
	char* token;
	token = strtok(buffer, "<"); //Find number within ACKs...
	if(token)
	{
		if(!strtol(token, &_errstr, 10))
			token = strtok(NULL, ">"); // if any.
		
		numSamplers = (int)strtol(token, &_errstr, 10);
	}
	


#ifdef DEBUG
	char text[32];
	sprintf(text, "Samplers: %i\n", numSamplers);
	printf("%s",text);
	//sendosc(string_, (void*)text);
#endif
}

int slmx4::Iterations()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(Iterations)");

	serial.readString(buffer, '0', BUFFER_SIZE, TIMEOUT_MS);

	char* token = strtok(buffer, "<");
	int iterations = atoi(token);

#ifdef DEBUG
	printf("Iterations: %i\n", iterations);
#endif
	return(iterations);
}

void slmx4::TryUpdateChip(int cmd, void* val)
{
	char _valstr[1024] = {0};
	char _cmd[1024] = {0};

	switch(cmd)
	{
	case rx_wait:
		sprintf(_valstr, "%i)", *(unsigned char*)val);
		strcpy(_cmd, "VarSetValue_ByName(rx_wait,");
		strcat(_cmd, _valstr);
		serial.writeString(_cmd);
		break;

	case frame_start:
		sprintf(_valstr, "%.1f)", *(float*)val);
		strcpy(_cmd, "VarSetValue_ByName(frame_start,");
		strcat(_cmd, _valstr);
		serial.writeString(_cmd);
		break;
	case frame_end:
		sprintf(_valstr, "%.1f)", *(float*)val);
		strcpy(_cmd, "VarSetValue_ByName(frame_end,");
		strcat(_cmd, _valstr);
		serial.writeString(_cmd);
		break;
	case ddc_en:
		sprintf(_valstr, "%i)", *(unsigned char*)val);
		strcpy(_cmd, "VarSetValue_ByName(ddc_en,");
		strcat(_cmd, _valstr);
		serial.writeString(_cmd);
		break;
	case pps:
		sprintf(_valstr, "%i)", *(int*)val);
		strcpy(_cmd, "VarSetValue_ByName(PPS,");
		strcat(_cmd, _valstr);
		serial.writeString(_cmd);
		break;
	}

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'TryUpdateChip'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'TryUpdateChip'", host_addr);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'TryUpdateChip'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'TryUpdateChip'\n", host_addr);
		#endif
	}

    updateNumberOfSamplers();

}

void slmx4::init_serial()
{
	// Connection to serial port
	char errorOpening = serial.openDevice(SERIAL_PORT, 115200);

	// Share buffer ptr to serial module
	//serial.set_buffer_ptr(buf_ptr);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1)
    {
    	printf ("ERROR connection to serial port: %i\n", errorOpening);
    	sendosc(string_, (void*)"ERROR connection to serial port", host_addr);
    }

    else
    {
		#ifdef DEBUG
    	printf ("Successful connection to %s\n",SERIAL_PORT);
    	sendosc(string_, (void*)"Successful connection to serial port", host_addr);
		#endif
    	serial.setDTR();
    	serial.setRTS();
    }
}


int slmx4::GetFrameRaw(_Float32* frame)
{
	int frameSize = (numSamplers);
	int av = 0;
	
	serial.writeString("GetFrameRaw()");
	
	timeOut timer;
	timer.initTimer();

	while(1)
	{
		av = serial.available();
		if(timer.elapsedTime_ms() > TIMEOUT_MS)
		{
			printf("Timeout\n");
			break;
		}
		if(av >= frameSize*4)
		{
			serial.readBytes(frame, frameSize * 4, 1);
			break;
		}
	}

	#ifdef DEBUG
	for(int j = 0; j < frameSize -1; ++j)
		printf("%f, ", frame[j]);
	#endif


	if(!check_ACK()){
		return(EXIT_SUCCESS);
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'getFrameRaw'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'getFrameRaw'", host_addr);
		#endif
	}
 	else{ 
		return(EXIT_FAILURE);
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'getFrameRaw'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'getFrameRaw'\n", host_addr);
		#endif
	}
}

int slmx4::GetFrameNormalized(_Float32* frame)
{
	int frameSize = (numSamplers);
	int av = 0;
	
	serial.writeString("GetFrameNormalized()");
	
	timeOut timer;
	timer.initTimer();

	while(1)
	{
		av = serial.available();
		if(timer.elapsedTime_ms() > TIMEOUT_MS)
		{
			printf("Timeout\n");
			break;
		}
		if(av >= frameSize*4)
		{
			serial.readBytes(frame, frameSize * 4, 0);
			break;
		}
	}

	#ifdef DEBUG
	for(int j = 0; j < frameSize -1; ++j)
		printf("%f, ", frame[j]);
	#endif

	if(!check_ACK()){
		return(EXIT_SUCCESS);
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'getframenormalized'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'getframenormalized'", host_addr);
		#endif
	}
 	else{ 
		return(EXIT_FAILURE);
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'getframenormalized'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'getframenormalized'\n", host_addr);
		#endif
	}

}

void slmx4::End()
{
	CloseRadar();
}


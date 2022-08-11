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

#define BUFFER_SIZE 32
#define ACK_SIZE 6

#define DEBUG


slmx4::slmx4()
{
	isOpen = 0;
	numSamplers = 0;
	status = -1;
}

int slmx4::Begin()
{
	timeOut timer;
	timer.initTimer();

	if(init_serial() == EXIT_FAILURE){
		return(EXIT_FAILURE);
	}
	OpenRadar();

	while(!isOpen)
	{
		if(timer.elapsedTime_ms() > TIMEOUT_MS)
		{
			fprintf(stderr,"Timeout: OpenRadar()");
		}
	};
	return(EXIT_SUCCESS);
}

void slmx4::init_device()
{
	serial.writeString("NVA_CreateHandle()");

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'init_device'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'init_device'", host_ip);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'init_device'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'init_device'\n", host_ip);
		#endif
	}
}


int slmx4::check_ACK()
{
	char ack_[ACK_SIZE];
	
	serial.readBytes(ack_, ACK_SIZE-1, TIMEOUT_MS);

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
		sendosc(string_, (void*)"SUCCESS: ACK from 'OpenRadar'", host_ip);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'OpenRadar'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'OpenRadar'\n", host_ip);
		#endif
	}

	updateNumberOfSamplers();

	isOpen = 1;
}

void slmx4::CloseRadar()
{
	serial.flushReceiver();
	serial.writeString("Close()");

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'CloseRadar'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'CloseRadar'", host_ip);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'CloseRadar'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'CloseRadar'\n", host_ip);
		#endif
	}

}


void slmx4::updateNumberOfSamplers()
{
	char buffer[BUFFER_SIZE];

	serial.writeString("VarGetValue_ByName(SamplersPerFrame)");

	usleep(10);

	serial.readString(buffer, '0', BUFFER_SIZE, TIMEOUT_MS);

	//printf("%s\n", buffer);

	char* token = strtok(buffer, "<");
	if(token != NULL){
		numSamplers = atoi(token);
	}
	else{
		fprintf(stderr,"ERROR reading number of samplers\n");
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
	int iterations = 0;
	if(token != NULL){
		iterations = atoi(token);
	}
	else{
		fprintf(stderr,"ERROR reading number of Iterations\n");
	}

#ifdef DEBUG
	printf("Iterations: %i\n", iterations);
#endif
	return(iterations);
}

void slmx4::TryUpdateChip(int cmd,void* test)
{

	switch(cmd)
	{
	case rx_wait:
		serial.writeString("VarSetValue_ByName(rx_wait,0)");
		break;
	case frame_start:
		serial.writeString("VarSetValue_ByName(frame_start,0.3)");
		break;
	case frame_end:
		serial.writeString("VarSetValue_ByName(frame_end,4)");
		break;
	case ddc_en:
		serial.writeString("VarSetValue_ByName(ddc_en,0)");
		break;
	case pps:
		serial.writeString("VarSetValue_ByName(PPS,30)");
		break;
	}

	if(!check_ACK()){
		#ifdef DEBUG
 		printf("SUCCESS: ACK from 'TryUpdateChip'\n");
		sendosc(string_, (void*)"SUCCESS: ACK from 'TryUpdateChip'", host_ip);
		#endif
	}
 	else{ 
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'TryUpdateChip'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'TryUpdateChip'\n", host_ip);
		#endif
	}

    updateNumberOfSamplers();

}

int slmx4::init_serial()
{
	// Connection to serial port
	char errorOpening = serial.openDevice(SERIAL_PORT, 115200);

	// Share buffer ptr to serial module
	//serial.set_buffer_ptr(buf_ptr);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1)
    {
    	printf ("ERROR connection to serial port: %i\n", errorOpening);
    	sendosc(string_, (void*)"ERROR connection to serial port", host_ip);
		  return(EXIT_FAILURE);
    }

    else
    {
		#ifdef DEBUG
    	printf ("Successful connection to %s\n",SERIAL_PORT);
    	sendosc(string_, (void*)"Successful connection to serial port", host_ip);
		#endif
    	serial.setDTR();
    	serial.setRTS();
		serial.flushReceiver();
		return(EXIT_SUCCESS);
    }
}


int slmx4::GetFrameRaw(_Float32* frame)
{
	serial.flushReceiver();
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
		sendosc(string_, (void*)"SUCCESS: ACK from 'getFrameRaw'", host_ip);
		#endif
	}
 	else{ 
		return(EXIT_FAILURE);
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'getFrameRaw'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'getFrameRaw'\n", host_ip);
		#endif
	}
}

int slmx4::GetFrameNormalized(_Float32* frame)
{
	serial.flushReceiver();
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
		sendosc(string_, (void*)"SUCCESS: ACK from 'getframenormalized'", host_ip);
		#endif
	}
 	else{ 
		return(EXIT_FAILURE);
		#ifdef DEBUG
		printf("ERROR: Reading ACK in 'getframenormalized'\n");
		sendosc(string_, (void*)"ERROR: Reading ACK in 'getframenormalized'\n", host_ip);
		#endif
	}

}

void slmx4::setHost(const char *addr)
{
	strcpy(host_ip, addr);
}

void slmx4::End()
{
	CloseRadar();
}


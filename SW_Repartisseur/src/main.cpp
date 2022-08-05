#include <stdio.h> 
#include <stdlib.h> 

#include "sendosc.h"
#include "slmx4_vcom.h"
#include "Proto_Pulmo.h"
#include "filters.h"
#include "respiration.h"

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include "tinyosc.h"

#include "testData.h"

#define BREATH_SIZE 6

#define PERIOD 5

void *osc_listener(void* vargp);
void UpdateSensorReg(int reg, float val);
#define RX_WAIT 1
#define FRAME_START 2
#define FRAME_END 3
#define DDC_EN 4
#define PPS 5

static char host_addr[32] = {0};
static volatile unsigned char go = 0;

static volatile unsigned char thread_running = 0;


typedef struct _args
{
	void* host_addr_str_ptr;
	volatile void* go_ptr;
} *thread_args;


static unsigned char rx_wait_arg = 0;
static float frame_start_arg = 0.2;
static float frame_end_arg = 4;
static unsigned char ddc_en_arg = 1;
static unsigned int PPS_arg = 10;




int main()
{
	/* Wait for '@host' message from MAX*/
	pthread_t listen_thread;
	thread_args args = (thread_args)malloc(sizeof(struct _args));
	args->host_addr_str_ptr = &host_addr;
	args->go_ptr = &go;
	thread_running = 1;
	pthread_create(&listen_thread, NULL, osc_listener,(void*)args);

	while(!go); // BLOCKING


	printf("%s\n", host_addr);	// This can now be used to communicate with MAX

/*
	slmx4 sensor;

	sensor.Begin();
	sensor.Iterations();


	UpdateSensorReg(sensor, RX_WAIT, 0);
	UpdateSensorReg(sensor, FRAME_START, 0.2);
	UpdateSensorReg(sensor, FRAME_END, 4);
	UpdateSensorReg(sensor, DDC_EN, 1);
	UpdateSensorReg(sensor, PPS, 10);


	respiration_data_t* resp_data = respiration_init(sensor.numSamplers, BREATH_SIZE);


	_Float32* tablo = (_Float32*)malloc(sizeof(_Float32)*sensor.numSamplers);

	timeOut timer;

	while(go){
		timer.initTimer();

		sensor.GetFrameNormalized(tablo);

		respiration_update(tablo, sensor.numSamplers, resp_data);

		FILE* fichier = fopen("./FILE", "w+");
		for(int i = 0; i < sensor.numSamplers-1; i++){
			fprintf(fichier,"%f,",tablo[i]);
		}

		fprintf(fichier,"%f",tablo[sensor.numSamplers-1]);

		fflush(fichier);
		fclose(fichier);

		if(timer.elapsedTime_ms() > PERIOD){
			fprintf(stderr, "CAUTION : CANNOT RESPECT DEFINED PERIOD || Elapsed : %ims, Period : %ims\r\n",(int)timer.elapsedTime_ms(), PERIOD);
		}
		else{
			while(timer.elapsedTime_ms() < PERIOD);
		}
	}
	
	sensor.End();
*/

	thread_running = 0;
	//pthread_join
	free(args);
	return 0;
}

void UpdateSensorReg(slmx4* sensor, int reg, float val)
{
	switch (reg)
	{
	case RX_WAIT:
		static unsigned char rx_wait_arg = val;
		sensor->TryUpdateChip(slmx4::rx_wait, &rx_wait_arg);
		break;
	case FRAME_START:
		static float frame_start_arg = val;
		sensor->TryUpdateChip(slmx4::frame_start, &frame_start_arg);
		break;
	case FRAME_END:
		static float frame_end_arg = val;
		sensor->TryUpdateChip(slmx4::frame_end, &frame_end_arg);
		break;
	case DDC_EN:
		static unsigned char ddc_en_arg = val;
		sensor->TryUpdateChip(slmx4::ddc_en, &ddc_en_arg);
		break;
	case PPS:
		static unsigned int PPS_arg = val;
		sensor->TryUpdateChip(slmx4::pps, &PPS_arg);
		break;
	}
}


/**
 * A basic program to listen to port 9000 and print received OSC packets.
 */
void *osc_listener(void* vargp)
{
	thread_args params = (thread_args) vargp;


	char buffer[2048]; // declare a 2Kb buffer to read packet data into

	// open a socket to listen for datagrams (i.e. UDP packets) on port 9000
	const int fd = socket(AF_INET, SOCK_DGRAM, 0);
	fcntl(fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(6969);
	sin.sin_addr.s_addr = INADDR_ANY;
	bind(fd, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));

	while (thread_running) {
		char buff[32];
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(fd, &readSet);
		struct timeval timeout = {1, 0}; // select times out after 1 second
		if (select(fd+1, &readSet, NULL, NULL, &timeout) > 0) {
			struct sockaddr sa; // can be safely cast to sockaddr_in
			socklen_t sa_len = sizeof(struct sockaddr_in);
			int len = 0;
			while ((len = (int) recvfrom(fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0) {
				if (tosc_isBundle(buffer)) {
					tosc_bundle bundle;
					tosc_parseBundle(&bundle, buffer, len);
					const uint64_t timetag = tosc_getTimetag(&bundle);
					tosc_message osc;
					while (tosc_getNextMessage(&bundle, &osc)) {
						tosc_printMessage(&osc, buff);
					}
				} else {
					tosc_message osc;
					tosc_parseMessage(&osc, buffer, len);
					switch(tosc_printMessage(&osc, buff))
					{
					case 1:
						strcpy((char*)params->host_addr_str_ptr, buff);
						*((volatile unsigned char*)params->go_ptr) = 1;
						break;
					case 2:
						//Parse cmd strings here
						break;
					default: break;
					}

				}
			}
		}
	}

	// close the UDP socket
	close(fd);

	return 0;
}




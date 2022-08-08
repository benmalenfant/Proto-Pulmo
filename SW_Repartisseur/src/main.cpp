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

/**************************************************************************************/

// Frame capture macros
#define BREATH_SIZE 6
#define PERIOD 5

// Sensor register macros
#define RX_WAIT 1
#define FRAME_START 2
#define FRAME_END 3
#define DDC_EN 4
#define PPS 5

// Global buffers
static char host_addr[32] = {0};
static char cmd_buf[32] = {0};

// Global flags
static volatile unsigned char go__ = 0;
static volatile unsigned char cmd__ = 0;
static volatile unsigned char stop__ = 0;
static volatile unsigned char thread_running = 0;

// Thread params
typedef struct _args
{
	void* host_addr_str_ptr;
	volatile void* go_ptr;
	volatile void* cmd_buf_ptr;
	volatile void* cmd_flag_ptr;
} *thread_args;

// Struct memory allocation
thread_args argsCons();
void argsDest(thread_args ptr);

// Global states
enum states{stopped, running, parsing, starting, stopping, standby};

// Local functions
void *osc_listener(void* vargp);
void UpdateSensorReg(slmx4* sensor, int reg, float val);


/**************************************************************************************/
/**************************		 		MAIN 				***************************/
/**************************************************************************************/
int main()
{

	/* Create OSC listener thread */
	/* {{ Waits for '@host' message from MAX }} */
	pthread_t listen_thread;
	thread_args args = argsCons();
	thread_running = 1;
	pthread_create(&listen_thread, NULL, osc_listener,(void*)args);
	fprintf(stdout, "Thread: En attente de '@hostadress' sur upd:6969\n");


	/* Sensor data init */
	slmx4 sensor;
	respiration_data_t* resp_data = respiration_init(sensor.numSamplers, BREATH_SIZE);
	_Float32* tablo = (_Float32*)malloc(sizeof(_Float32)*sensor.numSamplers);

	/* Parser values */
	double _val = 0;

	/* Timer for easy timeout implementation */
	timeOut timer;

	/* Init state */
	states pgm_state = standby;


	while(1)
	{
		switch(pgm_state)
		{
		/* Standby: Wait for go from listener thread */
		case standby:
			if(go__)
			{
				sensor.setHost(host_addr);
				fprintf(stdout, "%s\n", host_addr);	//This can now be used to communicate with MAX
				pgm_state = starting;
			}
			break;

		/* Starting: Go through init sequences and send default values to sensor*/
		case starting:
			if(sensor.Begin())
			{
				pgm_state = stopping;
				break;	//Stop if Begin() times out
			}

			sensor.Iterations();//Default values
			UpdateSensorReg(&sensor, RX_WAIT, 0);
			UpdateSensorReg(&sensor, FRAME_START, 0.2);
			UpdateSensorReg(&sensor, FRAME_END, 4);
			UpdateSensorReg(&sensor, DDC_EN, 1);
			UpdateSensorReg(&sensor, PPS, 10);

			pgm_state = running;
			break;

		/* Running: Capture, filter and send frame information to MAX*/
		case running:
			//Triggers every given PERIOD (ms)
			if(timer.elapsedTime_ms() > PERIOD)
			{
				timer.initTimer();

				//resp_data->format_filter->gain
				sensor.GetFrameNormalized(tablo);
				respiration_update(tablo, sensor.numSamplers, resp_data);
				FILE* fichier = fopen("./FILE", "w+");

				for(int i = 0; i < sensor.numSamplers-1; i++)
					fprintf(fichier,"%f,",tablo[i]);

				fprintf(fichier,"%f",tablo[sensor.numSamplers-1]);
				fflush(fichier);
				fclose(fichier);

				//Catch flags (set in listener thread)
				if(cmd__)
				{
					cmd__ = 0;
					pgm_state = parsing;
				}if(stop__)
				{
					stop__ = 0;
					pgm_state = stopping;
				}

				//Timer has exceeded period before looping back
				if(timer.elapsedTime_ms() > PERIOD)
					fprintf(stderr, "CAUTION : CANNOT RESPECT DEFINED PERIOD || Elapsed : %ims, Period : %ims\r\n",
							(int)timer.elapsedTime_ms(), PERIOD);
			}
			break;

		/* Parsing: Respond to command buffer input accordingly*/
		case parsing:
			char *_cmd, *_valstr;
			_val = 0;

			//Command format:: '/cmd=value'
			_cmd = strtok(cmd_buf, "=");

			//Frame start command
			if(!strcmp(_cmd, "fstart"))
			{
				_valstr = strtok(NULL, "\0");
				_val = atof((const char*)_valstr);
				UpdateSensorReg(&sensor, FRAME_START, _val);
			}

			//Frame end command
			if(!strcmp(_cmd, "fend"))
			{
				_valstr = strtok(NULL, "\0");
				_val = atof((const char*)_valstr);
				UpdateSensorReg(&sensor, FRAME_END, _val);
			}

			//Shutdown command (for testing)
			if(!strcmp(_cmd, "stop"))
				pgm_state = stopping;

			break;

		/* Stopping: Shutdown the sensor and close the program */
		case stopping:
			sensor.End();
			thread_running = 0;
			pthread_join(listen_thread, NULL);
			argsDest(args);
			return 0;

		default:
			break;
		}
	}
	return 0;
}
/**************************************************************************************/


/* UpdateSensorReg()
 *	- sensor: 	Pointer to sensor obj
 *	- reg: 		Register to be updated on sensor (see macros)
 *	- val: 		Value sent to register
 */
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
/**************************************************************************************/


/* osc_listener()
 *	- vargp: Pointeur vers thread params
 */
void *osc_listener(void* vargp)
{
	thread_args params = (thread_args) vargp;


	char buffer[2048]; //Buffer de 2kB pour lire le packet

	// Ouvrir le socket et ecouter sur le port 6969
	const int fd = socket(AF_INET, SOCK_DGRAM, 0);
	fcntl(fd, F_SETFL, O_NONBLOCK); // non-blockant
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
		struct timeval timeout = {1, 0};
		if (select(fd+1, &readSet, NULL, NULL, &timeout) > 0) {
			struct sockaddr sa;
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

					//Parse osc address string (MAX message string)
					switch(tosc_printMessage(&osc, buff))
					{
					case 1://string starts with '@' : parse as host address
						strcpy((char*)params->host_addr_str_ptr, buff); //store hostaddr string
						*((volatile unsigned char*)params->go_ptr) = 1; //break blocking loop for init
						break;
					case 2:
						strcpy((char*)params->cmd_buf_ptr, buff); //store cmd string
						*((volatile unsigned char*)params->cmd_flag_ptr) = 1;
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
/**************************************************************************************/


/* argsCons()
 *	Initialisation du struct passe au thread
 */
thread_args argsCons()
{
	thread_args _args= (thread_args)malloc(sizeof(struct _args));
	_args->host_addr_str_ptr = &host_addr;
	_args->go_ptr = &go__;
	_args->cmd_buf_ptr = &cmd_buf;
	_args->cmd_flag_ptr = &cmd__;
	return _args;
}

/* argsDest()
 *	Destruction du struct passe au thread
 */
void argsDest(thread_args ptr)
{
	free(ptr);
}
/**************************************************************************************/

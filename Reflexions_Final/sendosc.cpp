#include <iostream>

#include </usr/include/oscpack/osc/OscOutboundPacketStream.h>
#include </usr/include/oscpack/ip/UdpSocket.h>

#include "sendosc.h"

#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*------------------------------------------------------------------------------------*/

#define BUF_SIZE 1024
#define MESSAGE_MAX BUF_SIZE / 2

#define PORT 5555
char* host_addr = "10.0.2.2";

/*------------------------------------------------------------------------------------*/


int sendosc(type t, void* val)
{
	using namespace osc;

	int i = 0; //var for sine

	// setup udp socket
	UdpTransmitSocket transmitSocket(IpEndpointName(host_addr, PORT));

//	while(1)
//	{
//		usleep(5000);
//		++i;

		// setup packet
		char buf[BUF_SIZE];
		memset(buf, 0, BUF_SIZE);
		osc::OutboundPacketStream p(buf, BUF_SIZE);

		char path[MESSAGE_MAX] = {};


		switch(t)
		{
		case int_:
			strcat(path, "int");
			p << osc::BeginMessage(path);
			p << *((int*)val);
			p << osc::EndMessage;
			break;
		case string_:
			strcat(path, (const char*)val);
			p << osc::BeginMessage(path);
			p << osc::EndMessage;
			break;
		case sine_:
			strcat(path, "int");
			p << osc::BeginMessage(path);
			p << (int)(60*sin(((double)i/150))) + 60;
			p << osc::EndMessage;
			break;
		}


		transmitSocket.Send( p.Data(), p.Size() );
//	}

	//bundle?

	return 0;
}

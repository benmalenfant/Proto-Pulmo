#include <iostream>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "sendosc.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*------------------------------------------------------------------------------------*/

#define BUF_SIZE 1024

#define PORT 5557
char* host_addr = "10.0.2.2";

/*------------------------------------------------------------------------------------*/


int sendosc()
{
	using namespace osc;

	int i = 0; //var for sine

	// setup udp socket
	UdpTransmitSocket transmitSocket(IpEndpointName(host_addr, PORT));

	while(1)
	{
		usleep(5000);
		++i;

		// setup packet
		char buf[BUF_SIZE];
		memset(buf, 0, BUF_SIZE);
		OutboundPacketStream p(buf, BUF_SIZE);

		char *path = "int";
		p << osc::BeginMessage(path);
		p << (int)(60*sin(((double)i/150))) + 60;
		p << osc::EndMessage;

		transmitSocket.Send( p.Data(), p.Size() );
	}

	//bundle?

	//return 0;
}

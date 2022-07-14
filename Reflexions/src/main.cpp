#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hdr/slmx4_driver.h"


#define BUF_SIZE 1024

#define HOST_ADDR "127.0.0.1"
#define PORT 9999

char* host_addr = "127.0.0.1";

int main()
{
	int s_port = init_serial();


	//return 0;
}

void send_osc(char* host, unsigned short port)
{
	using namespace osc;

	// setup udp socket
	UdpTransmitSocket transmitSocket(IpEndpointName(host, port));

	// setup packet
	char buf[BUF_SIZE];
	memset(buf, 0, BUF_SIZE);
	OutboundPacketStream p(buf, BUF_SIZE);

	//p << osc::BeginBundleImmediate;

	char *path = "/test1";
	p << osc::BeginMessage(path);

	p << "STRING";

	p << (int) 69;

	p << (float)69.69;

	p << osc::EndMessage;
	//p << osc::EndBundle;

	transmitSocket.Send( p.Data(), p.Size() );
}


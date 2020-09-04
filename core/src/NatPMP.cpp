/*
 *  Author: Ivan Khodyrev
 */
#include "NatPMP.h"
#include "MainInterfaces.h"
#include "NetSocketWorker.h"
#include <cstring>
using namespace std;

void NatPMP::PortForwarding(int code, int internal_port, int external_port, int life_time){
	unsigned char ver = 0;
	unsigned char opcode = code;
	unsigned short reserved_val = 0;
	const unsigned short private_port = (unsigned short)internal_port;
	const unsigned short public_port = (unsigned short)external_port;
	unsigned int lifetime = (unsigned int)life_time;

	unsigned char *buffer = new unsigned char[12];
	buffer[0] = ver;
	buffer[1] = opcode;
	buffer[2] = reserved_val>>8;
	buffer[3] = reserved_val;
	buffer[4] = private_port>>8;
	buffer[5] = private_port;
	buffer[6] = public_port>>8;
	buffer[7] = public_port;
	buffer[8] = lifetime>>8*3;
	buffer[9] = lifetime>>8*2;
	buffer[10] = lifetime>>8;
	buffer[11] = lifetime;

	NetSocketWorker *sw = new NetSocketWorker();
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	sw->ConnectTo(sock, new ClientAddr("192.168.0.1", 5351));
	sw->Send(sock, (char*)buffer, 12);

	delete[] buffer;
	delete sw;
}


#pragma once
#include "C:\Users\1\Desktop\������\bootcamp\C++\MiniProject\CommunicationProject\Share\Server\Server_Socket.h"
class Amplifier
{
public:
	Server_Socket server;
	Amplifier(int port):server(port) {
	}
};


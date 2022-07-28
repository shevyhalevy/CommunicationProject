#pragma once
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Server\Server_Socket.h"
class Modem
{
public:
	Server_Socket server;
	Modem(int port) :server(port) {
	}
};



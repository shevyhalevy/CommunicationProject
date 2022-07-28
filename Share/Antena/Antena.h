#pragma once
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Server\Server_Socket.h"
class Antena
{
public:
	Server_Socket server;
	Antena(int port) :server(port){
	}
};





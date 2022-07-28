#pragma once
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Client\Client.h"
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Server\Server_Socket.h"
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\IDD\IDD.h" 
#include <thread>
class Message_Generator
{
public:
	int flag = 0;
	Client c = Client();
	vector<controlerType> Send_to;
	void Send_from_Message_Generator();
	void recived_to_Message_Generator();
	int send_DataMessage_counter = 0;
	int received_DataMessage_counter = 0;
	Message_Generator(vector<controlerType> Send_to1, int port) {
		Server_Socket Server = Server_Socket(port);
		Send_to = Send_to1;
		thread t1(&Message_Generator::Send_from_Message_Generator, this);
		thread t2(&Message_Generator::recived_to_Message_Generator, this);
		t1.detach();
		t2.detach();
	}
};


void Message_Generator::Send_from_Message_Generator() {
	while (true) {
		c.send_client(Send_to);
		send_DataMessage_counter++;
		flag = 1;
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Message_Generator::recived_to_Message_Generator() {
	while (true) {
		int check = 0;
		if (flag) {
			c.recivd_client(Send_to);
			//if(check==0)
			received_DataMessage_counter++;
		}
	}
}


#pragma once
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\IDD\IDD.h" 
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Client\Client.h"
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Server\Server_Socket.h"
#include<thread>
#include<vector>
#include <unordered_map>
#include<thread>
#include <iostream>
using namespace std;


class Manager
{
public:
	int flag = 0;
	Client c ;
	vector<controlerType> m;
	vector<controlerType> Send_to;
	Manager(vector<controlerType> Send_to1,int port) {
		Client c = Client();
		Server_Socket server = Server_Socket(port);
		Send_to = Send_to1;
		thread tget_Massag(&Manager::get_Massag,this);
		thread trec_get_Massag(&Manager::rec_get_Massag, this);
		thread tchech(&Manager::chech, this);
		tget_Massag.detach();
		trec_get_Massag.detach();
		tchech.detach();
		this_thread::sleep_for(std::chrono::seconds(1));
	}
	void get_Massag();
	void rec_get_Massag();
	void chech();
};


void Manager::get_Massag()
{
	while (true)
	{
		c.send_client(Send_to);
		for (int i = 0; i < Send_to.size(); i++)
		{
			Send_to[i].counter = c.Client_counter;
			m.push_back(Send_to[i]);
		}
		flag = 1;
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Manager::rec_get_Massag()
{
	while (true)
	{
		if (flag) {
		
				Header massage = c.recivd_client(Send_to);
				cout << "client recive massage" << massage.Opcode << endl;
				for (int i = 0; i < m.size(); i++)
				{
					if (m[i].counter == massage.msgCounter && m[i].to == massage.Opcode)
						m.erase(m.begin() + i);
				}
			}

		this_thread::sleep_for(std::chrono::seconds(1));
	}

}

void Manager::chech()
{
	while (true) {
		if (c.Client_counter % 5 == 0) {
			this_thread::sleep_for(std::chrono::seconds(5));
			for (int i = 0; i < m.size(); i++)
			{
				if (c.Client_counter - (m[i].counter) > 5)
				{
					cout << "error in " << m[i].counter << "sec in port" << m[i].port << endl;
					m.erase(m.begin() + i);
				}
			}
		}
	}
}


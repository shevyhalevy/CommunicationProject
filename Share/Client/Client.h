#pragma once
#include <vector>
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\IDD\IDD.h"
#include <winsock2.h>
#include<unordered_map>
#include <iostream>
#include<thread>
using namespace std;

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "192.168.56.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
//#define PORT 8888  // the port on which to listen for incoming data
#define MSG_SYNC 0xAA55
#define DATA_MSG_OPCODE 0xD001

class Client
{
public:
	/*vector<controlerType> Send_to;*/
	sockaddr_in server;
	int client_socket;
	/*int PORT;*/
	int Client_counter;
	int Create_Client();
	Client() {
		Client_counter = 0;
		client_socket = -1;
		Create_Client();
	}
	void send_client(vector<controlerType> Send_to);
	Header recivd_client(vector<controlerType> Send_to);
};


int Client::Create_Client()
{

    system("title UDP Client");

    // initialise winsock
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // create socket
    /*int client_socket;*/
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
   /* server.sin_port = htons(PORT);*/
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);
}


void Client::send_client(vector<controlerType> Send_to) {
    if (Send_to[0].to == DATA_MSG_OPCODE) {
        DataMessage message;
        message.header.msgSync = MSG_SYNC;
        message.header.msgCounter = Client_counter;
        for (int i = 0; i < Send_to.size(); i++)
        {
            message.header.Opcode = Send_to[i].to;
            server.sin_port = htons(Send_to[i].port);
            cout << Send_to[i].port;
            if (sendto(client_socket, (char*)&message, sizeof(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("send_client sendto() failed with error code: %d\n", WSAGetLastError());
            }
            else {
                printf("send_client sucsess\n");
            }
        }
    }
    else
    {
        ControlMessage message;
        message.Ack = 0;
        message.header.msgSync = MSG_SYNC;
        message.header.msgCounter = Client_counter;
        for (int i = 0; i < Send_to.size(); i++)
        {
            message.header.Opcode = Send_to[i].to;
            server.sin_port = htons(Send_to[i].port);
            cout << Send_to[i].port;

            if (sendto(client_socket, (char*)&message, sizeof(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("send_client sendto() failed with error code: %d\n", WSAGetLastError());

            }
            else {
                printf("send_client sucsess\n");
            }
        }
        Client_counter++;
    }
}

Header Client::recivd_client(vector<controlerType> Send_to)
{
   
      /*  for (int i = 0; i < Send_to.size(); i++)
        {*/
            //receive a reply and print it
           //clear the answer by filling null, it might have previously received data
            char message[BUFLEN] = {};
            //try to receive some data, this is a blocking call
            int slen = sizeof(sockaddr_in);
            int answer_length;
            if (answer_length = recvfrom(client_socket, message, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
            {
                printf(" recivd_client >>recvfrom() failed with error code: %d\n", WSAGetLastError());
              /*  exit(0);*/
            }
           /* else {
                cout << " recivd_client sucss" << Send_to[i].port << endl;
            }*/
            ControlMessage* h2 = (ControlMessage*)&message;
            Header* h = (Header*)&message;
            cout << " recivd_client sucss" << h->Opcode << endl;
//}
            if (h->Opcode != DATA_MSG_OPCODE) {
                ControlMessage* massage2 = (ControlMessage*)&message;
                return massage2->header;
            }
            else {
                
            }
        /*cout << answer << "\n";*/
   //chac which type is the massage
    
}



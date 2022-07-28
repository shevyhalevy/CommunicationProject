#pragma once
#include<thread>
#include <iostream>
#include <winsock2.h>
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\IDD\IDD.h"
#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 
#define BUFLEN 512
#include "Server_Socket.h"
#define GREEN   "\033[32m"      /* Green */
#define WHITE   "\033[37m"      /* White */
using namespace std;

class Server_Socket
{
public:
	int PORT;
	void server();
	Server_Socket(int port) {
		PORT = port;
		thread t5(&Server_Socket::server, this);
		t5.detach();
	}
};

void Server_Socket::server()
{

    system("title UDP Server");

    sockaddr_in server, client;

    // initialise winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
    }
    printf("Initialised.\n");

    // create a socket
    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 17)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    cout<<"Socket created.\n"<<endl;

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        //exit(EXIT_FAILURE);
    }
    cout<<"Bind done.";


    while (true)
    {
        cout<<"Waiting for data...";
        fflush(stdout);
        /* char message[BUFLEN] = {};*/
        char message[BUFLEN] = {};
        /* DataMessage message;*/
         // try to receive some data, this is a blocking call
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (struct sockaddr*) & client, &slen) == SOCKET_ERROR)
        {
            printf("server failed with error code: %d\n", WSAGetLastError());
        }

        Header* h = (Header*)&message;
        if (h->Opcode != DATA_MSG_OPCODE) {
            ControlMessage* massage2 = (ControlMessage*)&message;
            if (massage2->Ack != 0)
            {
                cout << "ack from " << massage2->header.Opcode << "is not 0" << endl;
            }
            else {
                massage2->Ack = 1;
            }
            if (massage2->header.Opcode == MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE)
                massage2->header.Opcode = ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE;
            else if (massage2->header.Opcode == MANAGER_TO_MODEM_CONTROL_MSG_OPCODE)
                massage2->header.Opcode = MODEM_TO_MANAGER_CONTROL_MSG_OPCODE;
            else if (massage2->header.Opcode == MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE)
                massage2->header.Opcode = AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE;
            // reply the client with 2the same data
            if (sendto(server_socket, (char*)&massage2, sizeof(massage2), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf(" server sendto() failed with error code: %d\n", WSAGetLastError());
            }
            else {
                cout << "server sendto() seccus " << PORT << endl;
            }
        }
        else {
            DataMessage* message3 = (DataMessage*)&message;
            cout << GREEN << PORT << "hello DataMessage from port " << PORT << endl;
            cout << WHITE;
            switch (PORT)
            {
            case(9004):client.sin_port = htons(9002);//modempc1
            case(9002):client.sin_port = htons(9009);//modempc2
            case(9009):client.sin_port = htons(9011);//menegerpc2
            case(9011):client.sin_port = htons(9008);//message generator
            case(9008):exit(0);
            }
            if (sendto(server_socket, (char*)&message3,sizeof(message3), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("server sendto() failed with error code: %d\n", WSAGetLastError());
            }
        }
    }

    closesocket(server_socket);
    WSACleanup();
}



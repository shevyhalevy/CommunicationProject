#include "Message_Generator.h"
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\IDD\IDD.h"
#include<vector>
#include<thread>
#include<iostream>
#define RED     "\033[31m"      /* Red */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
using namespace std;
int main() {
	int counter = 0;
	int seconds;
	cout << "enter seconds to run" << endl;
	cin >> seconds;
	cout << RED << "MESSAGE GENERATOR";
	cout << WHITE << endl;
	vector<controlerType> Send_to1;
	controlerType c1 = { DATA_MSG_OPCODE   ,9004 };
	Send_to1.push_back(c1);
	Message_Generator MassageGenerator1 = Message_Generator(Send_to1, 9008);
	//counter < seconds
	while (true)
	{
		this_thread::sleep_for(std::chrono::seconds(1));
		counter++;
	}
	cout << BOLDBLUE;
	cout << "THE NUMBER OF DATA MESSAGES THAT SEND IS:" << MassageGenerator1.send_DataMessage_counter << endl;
	cout << "THE MESSAGE GENERATOR RECEIVED:" << MassageGenerator1.received_DataMessage_counter << endl;
}
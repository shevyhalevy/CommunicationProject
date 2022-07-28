#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\Share\Antena\Antena.h"
#include"C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\share\Modem\Modem.h"
#include "C:\Users\1\Desktop\תיכנות\bootcamp\C++\MiniProject\CommunicationProject\share\Manager\Manager.h"
#define RED     "\033[31m"      /* Red */
#define WHITE   "\033[37m"      /* White */

using namespace std;
int main() {
    cout << RED << "CP2";
    cout << WHITE << endl;

    Modem modem = Modem(9009);
    Antena antena = Antena(10000);
    vector<controlerType> Send_to;
    controlerType c2 = { MANAGER_TO_MODEM_CONTROL_MSG_OPCODE  ,9009 };
    controlerType c3 = { MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE  ,10000 };
    Send_to.push_back(c2);
    Send_to.push_back(c3);
    Manager manager = Manager(Send_to, 9011);
    while (true)
    {
        this_thread::sleep_for(std::chrono::seconds(1));
    }
}



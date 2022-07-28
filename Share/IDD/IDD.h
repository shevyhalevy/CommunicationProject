#pragma once
//For Data messages
#define DATA_MSG_OPCODE 0xD001
//For Control Messages
#define MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE  0xA002
#define AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE  0xA003
#define MANAGER_TO_MODEM_CONTROL_MSG_OPCODE 0xA004
#define MODEM_TO_MANAGER_CONTROL_MSG_OPCODE 0xA005
#define MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE 0xA006
#define ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE 0xA007
#define MSG_SYNC 0xAA55
//For ports
#define  MANAGERpc1_PORT 9002
#define ANTENApc1_PORT 9000
#define AMPLIFIER_PORT 8889
#define MODEMpc1_PORT 9002

#define MANAGERpc2_PORT 9011
#define ANTENApc2_PORT 10000
#define MODEMpc2_PORT 9009

#define  MESSAGEGENE_PORT  unsigned short  9008

using namespace std;
typedef struct {
    unsigned short msgSync;
    unsigned short Opcode;
    unsigned int msgCounter;
} Header;
typedef struct {
    Header header;
    char Ack;
}ControlMessage;
typedef struct {
    Header header;
}DataMessage;
typedef struct {
    int to;
    int port;
    int counter=0;
}controlerType;


#ifndef CLIENT_H
#define CLIENT_H

#include "include.h"

class client
{
private:
    int CreateSocket = 0, n = 0;
    char dataReceived[1024];
    char dataSending[1024]; // Actually this is called packet in Network Communication, which contain data and send through.
    struct sockaddr_in ipOfServer;
    std::string ip="192.168.20.150";
    std::string message;
    controller motor;

public:
    client(/* args */);
    ~client();
    void connecting();
    void reader();
    void writing(std::string s);
    void message_Translation();
    void closing();
};
#endif
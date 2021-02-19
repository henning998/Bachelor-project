#ifndef SERVER_H
#define SERVER_H

#include "include.h"

class server
{
private:
    time_t clock;
    int n = 0;
    char dataReceived[1024];
    char dataSending[1024]; // Actually this is called packet in Network Communication, which contain data and send through.
    int clintListn = 0, clintConnt = 0;
    struct sockaddr_in ipOfServer;

public:
    server(/* args */);
    ~server();
    void connect();
    void writing(std::string s);
    void closing();
    void reader();
};
#endif
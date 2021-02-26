#ifndef SERVER_H
#define SERVER_H

#include "include.h"

class server
{
private:
    char dataReceived[1024];       //Char that can hold up to 1024 characters
    char dataSending[1024];        //Actually this is called packet in Network Communication, which contain data and send through.
    int clintListn = 0;            //Listen for client
    int clintConnt = 0;            //Connect to client
    struct sockaddr_in ipOfServer; //Ip handler

public:
    std::string message; //Message that is recieved
    server();
    ~server();
    //Setup connection to client
    void connect();
    //Write a message to client
    //@param s a string that gets send to client
    void writing(std::string s);
    //Close connection to client
    void closing();
    //Read data recieved from client
    void reader();
};
#endif
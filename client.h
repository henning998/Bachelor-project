#ifndef CLIENT_H
#define CLIENT_H

#include "include.h"
#include "Braitenberg.h"

class client
{
private:
    int CreateSocket = 0;              //Id for the socket
    char dataReceived[1024];           //Char that can hold 1024 characters
    char dataSending[1024];            // Actually this is called packet in Network Communication, which contain data and send through.
    struct sockaddr_in ipOfServer;     //Structure describing an Internet socket address
    std::string ip = "192.168.20.150"; //Ip of the server to connect to

public:
    std::string message; // String that holds the message received
    client();
    ~client();
    //Setup the connection to the server
    void connecting();
    //Read if there is a message recieved from server
    void reader();
    //Write a message to server
    //@param s a string that gets send to server
    void writing(std::string s);
    //Close connection to the server
    void closing();
};
#endif
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

server::server(/* args */)
{
    memset(&ipOfServer, '0', sizeof(ipOfServer));
    memset(dataSending, '0', sizeof(dataSending));
    clintListn = socket(AF_INET, SOCK_STREAM, 0); // creating socket
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(2017); // this is the port number of running server
    bind(clintListn, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
    listen(clintListn, 20);
     printf("\n\nHi,Iam running server.Some Client hit me\n"); // whenever a request from client came. It will be processed here.
   
    
}

server::~server()
{
    
}

void server::connect()
{
   clintConnt = accept(clintListn, (struct sockaddr *)NULL, NULL);
   std::cout << "clintConnt: " << clintConnt << std::endl;
}

void server::writing(std::string s)
{
    snprintf(dataSending, sizeof(dataSending), "%s\n", s.data()); // Printing successful message
    clock = time(NULL);
    write(clintConnt, dataSending, strlen(dataSending));
}

void server::closing()
{
    close(clintConnt);
    sleep(1);
}

void server::reader()
{
    while ((n = read(clintConnt, dataReceived, sizeof(dataReceived) - 1)) > 0)
    {
        dataReceived[n] = 0;
        if (fputs(dataReceived, stdout) == EOF)
        {
            printf("\nStandard output error");
        }

        printf("\n");
    }

    if (n < 0)
    {
        printf("Standard input error \n");
    }
}

#endif
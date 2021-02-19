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

public:
    client(/* args */);
    ~client();
    void connecting();
    void reader();
    void writing(std::string s);
};

client::client(/* args */)
{
    memset(dataReceived, '0', sizeof(dataReceived));
    if ((CreateSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket not created \n");
    }
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(2017);
    ipOfServer.sin_addr.s_addr = inet_addr("192.168.20.179");
}

client::~client()
{
}

void client::connecting()
{
    if (connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer)) < 0)
    {
        printf("Connection failed due to port and ip problems\n");
    }
}

void client::reader()
{
    while ((n = read(CreateSocket, dataReceived, sizeof(dataReceived) - 1)) > 0)
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

void client::writing(std::string s)
{
    snprintf(dataSending, sizeof(dataSending), "%s\n", s.data()); // Printing successful message
    write(CreateSocket, dataSending, strlen(dataSending));
}

#endif
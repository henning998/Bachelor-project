#include "client.h"

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
    read(CreateSocket, dataReceived, sizeof(dataReceived));
    std::string test;

    for (int i = 0; i < sizeof(dataReceived); i++)
    {
        if (dataReceived[i] != '0')
        {
            test.push_back(dataReceived[i]);
        }
        else
        {
            break;
        }
    }
    std::cout << test << std::endl;
}

void client::writing(std::string s)
{
    snprintf(dataSending, sizeof(dataSending), "%s\n", s.data()); // Printing successful message
    std::cout << "CreateSocket: " << CreateSocket << std::endl;
    write(CreateSocket, dataSending, strlen(dataSending));
}
#include "client.h"

client::client(/* args */)
{
    memset(dataReceived, '0', sizeof(dataReceived));
    if ((CreateSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) //Protocol = "0", compiler choose the protocol automatically
    {
        printf("Socket not created \n");
    }

    //Setup of ip
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(2017);
    ipOfServer.sin_addr.s_addr = inet_addr(ip.data());
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
    // Set up a timeout, so there is no busy waiting
    struct timeval timeout;
    timeout.tv_usec = 500;
    if (setsockopt(CreateSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        std::cout << "Recieve timeout does not work";
}

void client::reader()
{
    message.clear();
    read(CreateSocket, dataReceived, sizeof(dataReceived));

    for (int i = 0; i < sizeof(dataReceived); i++)
    {
        if (isalpha(dataReceived[i]) || dataReceived[i] == ' ') //isalpha checks if value in dataRecieved is alphabetic
        {
            message.push_back(dataReceived[i]);
            dataReceived[i] = '0';
        }
        else
        {
            break;
        }
    }
    std::cout << message << std::endl;
}

void client::writing(std::string s)
{
    snprintf(dataSending, sizeof(dataSending), "%s.", s.data()); // Printing successful message
    //std::cout << "CreateSocket: " << CreateSocket << std::endl;
    write(CreateSocket, dataSending, strlen(dataSending));
}

void client::closing()
{
    close(CreateSocket);
    sleep(1);
}
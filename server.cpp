#include "server.h"

server::server()
{
    memset(&ipOfServer, '0', sizeof(ipOfServer));
    memset(dataSending, '0', sizeof(dataSending));
    clintListn = socket(AF_INET, SOCK_STREAM, 0); // Creating socket
    //Setup of ip
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(2017); // This is the port number of running server

    bind(clintListn, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
    listen(clintListn, 20);
    printf("\n\nHi,I am running server.Some Client hit me\n"); // Whenever a request from client came. It will be processed here.
}

server::~server()
{
}

void server::connect()
{
    clintConnt = accept(clintListn, (struct sockaddr *)NULL, NULL);
    std::cout << "clintConnt: " << clintConnt << std::endl;

    // Set up a timeout, so there is no busy waiting
    struct timeval timeout;
    timeout.tv_usec = 500;
    if (setsockopt(clintConnt, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        std::cout << "det virker ikke";
}

void server::writing(std::string s)
{
    snprintf(dataSending, sizeof(dataSending), "%s.", s.data()); // Printing successful message
    write(clintConnt, dataSending, strlen(dataSending));
}

void server::closing()
{
    close(clintConnt);
    sleep(1);
}

void server::reader()
{
    message.clear();
    read(clintConnt, dataReceived, sizeof(dataReceived));

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
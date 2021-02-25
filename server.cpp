#include "server.h"

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
    snprintf(dataSending, sizeof(dataSending), "%s", s.data()); // Printing successful message
    //clock = time(NULL);
    write(clintConnt, dataSending, strlen(dataSending));
}

void server::closing()
{
    close(clintConnt);
    sleep(1);
}

void server::reader()
{
    data.clear();
    read(clintConnt, dataReceived, sizeof(dataReceived));

    for (int i = 0; i < sizeof(dataReceived); i++)
    {
        if (isalpha(dataReceived[i]))
        {
            data.push_back(dataReceived[i]);
            dataReceived[i] = '0';
        }
        else
        {
            break;
        }
    }
    std::cout << data << std::endl;
}
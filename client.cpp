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
    ipOfServer.sin_addr.s_addr = inet_addr(ip.data());
}

client::~client()
{
    motor.setLeftMotorSpeedDirection(0,1);
    motor.setRightMotorSpeedDirection(0,1);
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
    message.clear();

    for (int i = 0; i < sizeof(dataReceived); i++)
    {
        if (dataReceived[i] != '0')
        {
            message.push_back(dataReceived[i]);
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
    snprintf(dataSending, sizeof(dataSending), "%s\n", s.data()); // Printing successful message
    std::cout << "CreateSocket: " << CreateSocket << std::endl;
    write(CreateSocket, dataSending, strlen(dataSending));
}

void client::message_Translation()
{
   if (message == "w")
   {
       motor.setLeftMotorSpeedDirection(25,1);
       motor.setRightMotorSpeedDirection(25,1);
   }
   else if (message == "s")
   {
       motor.setLeftMotorSpeedDirection(25,0);
       motor.setRightMotorSpeedDirection(25,0);
   }
   else
   {
       motor.setLeftMotorSpeedDirection(0,1);
       motor.setRightMotorSpeedDirection(0,1);
   }
   
}
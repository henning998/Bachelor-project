#include "include.h"

int main(int argc, char **argv)
{
  client Client;
  Client.connecting();
 
  
  camera Camera;
  while (true)
  {
    Camera.getpicture();
  
    Client.reader();
    Client.message_Translation();
    //Client.closing();

    if (cv::waitKey(30) == 27)
    {
      // Release camera resources
      controller test;
      test.setLeftMotorSpeedDirection(0, 0);
      test.setRightMotorSpeedDirection(0, 0);
      break;
    }
  }

  return 0;
}

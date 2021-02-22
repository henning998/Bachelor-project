#include "include.h"

int main(int argc, char **argv)
{
  camera Camera;
  client Client;
  
  enum goal
  {
    blue,
    red
  };
  goal goal = red;
  Braitenberg braitenberg;

  while (true)
  {
    Camera.getpicture();

    Client.reader();
    Client.message_Translation();

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

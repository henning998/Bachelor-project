#include "include.h"
#include "Braitenberg.h"
#include "server.h"
#include "client.h"
#include "leader.h"
#include "camera.h"

int main(int argc, char **argv)
{
  leader leaderobj;
  leaderobj.run();
  controller test;
  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);

  return 0;
}

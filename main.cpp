#include "include.h"
#include "Braitenberg.h"
#include "server.h"
#include "client.h"
#include "leader.h"
#include "camera.h"
#include "follower.h"

int main(int argc, char **argv)
{
  controller test;

  test.setled(4, 100, 0, 0);
  test.setled(13, 100, 0, 0);

  // for (int i = 65; i < 80; i++)
  // {
  //   test.setLeftMotorSpeedDirection(i, backward);
  //   test.setRightMotorSpeedDirection(i, forward);
  //   std::cout << "i: " << i << std::endl;
  //   usleep(5000000);
  // }

  // test.setLeftMotorSpeedDirection(65, backward);
  // test.setRightMotorSpeedDirection(65, forward);
  // usleep(10000000);
    Braitenberg braitenbergobj;
    leader leaderobj;

  for (int i = 0; i < 1; i++)
  {
    //leaderobj.run();
    braitenbergobj.turn();
  }

  // follower followerobj;
  // followerobj.run();

  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);

  return 0;
}

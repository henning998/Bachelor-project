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
  
  leader leaderobj;
  leaderobj.run();

  // follower followerobj;
  // followerobj.run();

  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);

  return 0;
}

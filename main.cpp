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
  //usleep(10000000);
  Braitenberg braitenbergobj;
  // leader leaderobj;
  // leaderobj.run();
  

  // for (int i = 0; i < 6; i++)
  // {
  //    braitenbergobj.turn();
  //    usleep(1000000);
  //    //leaderobj.run();
  // }

  follower followerobj;
  followerobj.run();


  // camera Picam;
  // Picam.change2green();
  // int max_pic = 1000;
  // int detected = 0;
  // for (int i = 0; i < max_pic ; i++)
  // {
  //   cv::waitKey(27);
  //   //usleep(100000);
  //   Picam.getpicture();
  //   if (Picam.new_pic)
  //   {
  //     detected++;
  //   }
  // }
  // std::cout << " Number of detected " << detected << " out of " << max_pic << std::endl;




  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);

  return 0;
}

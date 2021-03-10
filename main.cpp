#include "include.h"
#include "Braitenberg.h"
#include "server.h"
#include "client.h"
#include "leader.h"
#include "camera.h"
#include "follower.h"

int main(int argc, char **argv)
{
 //leader leaderobj;
 //leaderobj.run();
  // // Braitenberg temp;
  // //temp.turn180();


//  camera temp;
//  while (true)
//  {
 
//  temp.getpicture(); 
//   cv::waitKey(27);
// }
   controller test;

  // test.setLeftMotorSpeedDirection(100, 0);
  // test.setRightMotorSpeedDirection(100, 1);
  // usleep(2540000);


  auto timer = std::chrono::steady_clock::now();

  test.setLeftMotorSpeedDirection(100, 1);
  test.setRightMotorSpeedDirection(100, 1);
  //usleep(1000000);
  int i = 0;
  while (i<10000)
  {
    test.get_encode_values();
    //usleep(60000);
    i++;
  }
    test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);
  auto end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end-timer).count();

  return 0;
}

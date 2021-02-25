#include "include.h"
#include "Braitenberg.h"
#include "server.h"
#include "client.h"
#include "leader.h"
#include "camera.h"
#include "follower.h"

int main(int argc, char **argv)
{
 follower followerobj;
 followerobj.run();
  // Braitenberg temp;
  // //temp.turn180();


//  camera temp;
//  while (true)
//  {
 
//  temp.getpicture(); 
//   cv::waitKey(27);
// }
   controller test;
  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);

  return 0;
}

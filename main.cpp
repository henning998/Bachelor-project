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

  test.setled(4, 2, 2, 2);
  test.setled(13, 2, 2, 2);

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

  // std::thread thread_logging(&controller::get_encode_values, &test);

  // // test.setLeftMotorSpeedDirection(100, 0);
  // // test.setRightMotorSpeedDirection(100, 1);
  // // usleep(2540000);
  // thread_logging.join();
  // std::cout << test.encode.size();

  // for (int i = 0; i < test.encode.at(0).size(); i++)
  // {
  //   std::cout << "test " <<test.encode.at(0).at(i) << std::endl;
  // }

  // auto timer = std::chrono::steady_clock::now();

  // test.setLeftMotorSpeedDirection(100, 1);
  // test.setRightMotorSpeedDirection(100, 1);
  // //usleep(1000000);

  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);
  // auto end = std::chrono::steady_clock::now();
  // std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end-timer).count();

  return 0;
}

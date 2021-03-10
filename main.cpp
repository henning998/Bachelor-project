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
  double temp;
 
  while (temp <= 270000)
  {
    test.get_encode_values();
    temp++;
  }
  int count = 0;
  for (int i = 1; i < test.encode.size(); i++)
  {
    if (test.encode.at(i).at(0) != test.encode.at(i-1).at(0) || test.encode.at(i).at(1) != test.encode.at(i-1).at(1))
    {
      count++;
    }
    
  }
  
  std::cout << "encoder på en hjul omgang: " << count << std::endl;



  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);
  // auto end = std::chrono::steady_clock::now();
  // std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end-timer).count();

  return 0;
}

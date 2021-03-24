#include "include.h"
#include "Braitenberg.h"
#include "server.h"
#include "client.h"
#include "leader.h"
#include "camera.h"
#include "follower.h"
#define forward 1
#define backward 0


int main(int argc, char **argv)
{

  controller test;

  test.setled(4, 100, 0, 0);
  test.setled(13, 100, 0, 0);
  
  
  leader leaderobj;
  leaderobj.run();
  // //leaderobj.find_Food();
  // Braitenberg temp;
  //  temp.turn180();

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


  // test.setLeftMotorSpeedDirection(100, 0);
  // test.setRightMotorSpeedDirection(100, 0);
  // for(int i = 0; i<10000;i++)
  // {
  //   test.get_encode_values();
  // }
// int tic = 3290;
//   int tics_r = 0, tics_l = 0;
//     std::vector<int> last_run = test.get_encode_values();
//     while (tics_r <= tic || tics_l <= tic) //4523
//     {
//         std::vector<int> temp = test.get_encode_values();
//         // for (int i = 0; i < temp.size(); i++)
//         // {
//         //     std::cout<<temp.at(i) << " " ;
//         // }
//         // std::cout << std::endl;
        
        
//         if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
//         {
//             tics_l++;
//         }
//         if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
//         {
//             tics_r++;
//         }
//         last_run = temp;
//         if (tics_r <= tic)
//         {
//           int kloklo = 0;
//           if(tics_r < tics_l)
//           {
//             kloklo = (tics_l - tics_r)*0.33;
//           }

//            test.setRightMotorSpeedDirection(65+kloklo, 1);
//         }
//         else
//         {
//             test.setRightMotorSpeedDirection(0, 1);
//         }

//         if (tics_l <= tic)
//         {
//           int qwer = 0;
//           if (tics_l < tics_r)
//           {
//             qwer = (tics_r-tics_l)*0.33;
//           }
          
//             test.setLeftMotorSpeedDirection(65 + qwer, 1);
//         }
//         else
//         {
//             test.setLeftMotorSpeedDirection(0, 1);
//         }
//          std::cout << "tics_l: " << tics_l << " & tics_r: " <<tics_r << std::endl;
//     }

  // int tic = 160000;
  // int  tics_r = 0, tics_l = 0;
  //  std::vector<int> last_run = test.get_encode_values();
  //   while (tics_r <= tic || tics_l <= tic) //4523
  //   {
  //       std::vector<int> temp = test.get_encode_values();

  //       if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
  //       {
  //           tics_l++;
  //       }
  //       if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
  //       {
  //           tics_r++;
  //       }
  //       last_run = temp;
  //       if (tics_r <= tic)
  //       {
  //           int difference = 0;
  //           if (tics_r > tics_l)
  //           {
  //               difference = (tics_r - tics_l);
  //             test.setRightMotorSpeedDirection(0, 0);  
  //           }
  //           else
  //           {

  //           test.setRightMotorSpeedDirection(65 - difference , 0);
  //           }
  //       }
  //       else
  //       {
  //           test.setRightMotorSpeedDirection(0, 0);
  //       }

  //       if (tics_l <= tic)
  //       {
  //           int difference = 0;
  //           if (tics_l > tics_r)
  //           {
  //               difference = (tics_l - tics_r);
  //               test.setLeftMotorSpeedDirection(0, 0);
  //           }
  //           else
  //           {
              
  //           test.setLeftMotorSpeedDirection(65 - difference, 0);
  //           }
            
  //       }
  //       else
  //       {
  //           test.setLeftMotorSpeedDirection(0, 0);
  //       }
  //        std::cout << "tics_l: " << tics_l << " & tics_r: " <<tics_r << std::endl;
  //   }
//   int tics_from_food_to_nest = 50000;

//  int tics_r = 0, tics_l = 0;
//     controller log_encode;
//     std::vector<int> last_run = log_encode.get_encode_values();
//     while (tics_r <= tics_from_food_to_nest || tics_l <= tics_from_food_to_nest) //4523
//     {
//         std::vector<int> temp = log_encode.get_encode_values();
//         // for (int i = 0; i < temp.size(); i++)
//         // {
//         //     std::cout<<temp.at(i) << " " ;
//         // }
//         // std::cout << std::endl;

//         if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
//         {
//             tics_l++;
//         }
//         if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
//         {
//             tics_r++;
//         }
//         last_run = temp;
//         if (tics_r <= tics_from_food_to_nest)
//         {
//             int diff_r = 0;
//             if (tics_r < tics_l)
//             {
//                 diff_r = (tics_l - tics_r) * 0.33;
//             }

//             log_encode.setRightMotorSpeedDirection(65 + diff_r, forward);
//         }
//         else
//         {
//             log_encode.setRightMotorSpeedDirection(0, forward);
//         }

//         if (tics_l <= tics_from_food_to_nest)
//         {
//             int diff_l = 0;
//             if (tics_l < tics_r)
//             {
//                 diff_l = (tics_r - tics_l) * 0.33;
//             }

//             log_encode.setLeftMotorSpeedDirection(65 + diff_l, forward);
//         }
//         else
//         {
//             log_encode.setLeftMotorSpeedDirection(0, forward);
//         }
//         std::cout << "tics_l: " << tics_l << " & tics_r: " << tics_r << std::endl;
//     }

  test.setLeftMotorSpeedDirection(0, 0);
  test.setRightMotorSpeedDirection(0, 0);
  // auto end = std::chrono::steady_clock::now();
  // std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end-timer).count();

  return 0;
}

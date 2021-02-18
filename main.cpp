//#include "controller.h"
#include "Braitenberg.h"

int main()
{
  //  controller::controller test;
/*controller test;
test.setRightMotorSpeedDirection(80, 1);
test.setLeftMotorSpeedDirection(80,0);
usleep(1000000);
test.setRightMotorSpeedDirection(0, 1);
test.setLeftMotorSpeedDirection(0,1);
*/
Braitenberg test;
test.love(0,0);
usleep(1000000);
test.love(1,1);
}
#include "include.h"

int main (int argc, char** argv)
{
  camera Camera;



  enum goal {blue, red};
  goal goal = red;
  Braitenberg braitenberg;
	

	while(true)
	{
    Camera.getpicture();


  
  if(Camera.size>0.85)
  {
    braitenberg.stop();
    usleep(100000);
    Camera.size = 0;
    if (goal == blue)
    {
      // iLowH = 160;
 	    // iHighH = 175;

	    // iLowS = 60;
 	    // iHighS = 230;

 	    // iLowV = 0;
 	    // iHighV = 255;

       goal = red;

       braitenberg.turn180();
       usleep(100000);
    }
    else if (goal == red)
    {
      // iLowH = 100;
 	    // iHighH = 110;

	    // iLowS = 90;
 	    // iHighS = 230;

 	    // iLowV = 0;
 	    // iHighV = 255;

       goal = blue;

       braitenberg.turn180();
       usleep(100000);
    }

    
  }
 float left,right;
  if (Camera.x <300)
  {
    left = (300-Camera.x )/300;
    right = 0;
  }
  if (Camera.x > 340)
  {
    left = 0;
    right = (Camera.x -340)/300;
  }
  
    braitenberg.love(left,right,Camera.size);

	if (cv::waitKey(30) == 27)
	{
		// Release camera resources
      controller test;
  test.setLeftMotorSpeedDirection(0,0);
  test.setRightMotorSpeedDirection(0,0);
		break;
	}
	}

	return 0;
}

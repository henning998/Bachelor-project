#include "leader.h"

leader::leader(/* args */)
{
}

leader::~leader()
{
}
void leader::find_Food()
{
    picam.change2red();
    while (true)
    {
        picam.getpicture();
        cv::waitKey(27);
        float left, right;
        if (picam.x < 300)
        {
            left = (300 - picam.x) / 300;
            right = 0;
        }
        if (picam.x > 340)
        {
            left = 0;
            right = (picam.x - 340) / 300;
        }
        motor.love(left, right, picam.size);
        if (picam.size > 0.85)
        {
            motor.stop();
            usleep(100000);
            motor.turn180();
            diff_state = BACK_TO_NEST;
            break;
        }
    }
}
void leader::back_To_Nest()
{
}
void leader::call_Follower()
{
}
void leader::guide_Follower()
{
}
void leader::make_room()
{
}

void leader::run()
{
    switch (diff_state)
    {
    case FIND_FOOD:
        find_Food();
        break;

    default:
        break;
    }
}
#include "follower.h"

follower::follower()
{
}

follower::~follower()
{
}

void follower::follow()
{
    picam.change2green();
    while (true)
    {
        picam.getpicture();
        cv::waitKey(27);
        float left = 0, right = 0;
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
        if (picam.size > 0.35)
        {
            motor.stop(true);
        }
    }
}

void follower::back_To_Nest()
{
}

void follower::back_To_Food()
{
}

void follower::back_To_Nest_Again()
{
}

void follower::run()
{
}

void follower::get_logging()
{
}

void follower::printlog()
{
}

void follower::reverse_Motor_values()
{
}
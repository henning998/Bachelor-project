#include "follower.h"

follower::follower()
{
    comm.connect();
}

follower::~follower()
{
}

void follower::getting_Ready()
{
    comm.reader();
    //std::cout << "Indholdet fra comm.data: " << comm.data << std::endl;
    if (comm.data == "Ready")
    {
        picam.change2green();
        picam.getpicture();
        cv::waitKey(27);
        if (picam.new_pic)
        {
            comm.writing("I am here");
            std::cout << "I wrote" << std::endl;
            diff_state = FOLLOW;
        }
    }
}

void follower::follow()
{

    picam.change2green();
    while (diff_state == FOLLOW)
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
        if (picam.new_pic)
        {
            motor.love(left, right, picam.size, true);
        }
        else
        {
            motor.stop();
        }
        if (picam.size > 0.35)
        {
            motor.stop(true);
            comm.reader();
            if (comm.data == "Goal found")
            {
                comm.writing("Okay move");
                comm.reader();
                if (comm.data == "I have moved")
                {
                    while (true)
                    {
                        picam.change2red();
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
                        if (picam.new_pic)
                        {
                            motor.love(left, right, picam.size, true);
                            if (picam.size > 0.35)
                            {
                                motor.stop(true);
                                diff_state = BACK_TO_NEST;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void follower::back_To_Nest()
{
    motor.turn180();
    picam.change2blue();
    reverse_Motor_values();
    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        motor.set_motor_speed(route_from_food_to_nest.at(i).at(0), route_from_food_to_nest.at(i).at(1));
        usleep(route_from_food_to_nest.at(i).back() * 1000000); // from sec to mikrosec.
    }
    diff_state = BACK_TO_FOOD;
}

void follower::back_To_Food()
{
    motor.turn180();
    picam.change2red();
    for (int i = 0; i < route_from_nest_to_food.size(); i++)
    {
        motor.set_motor_speed(route_from_nest_to_food.at(i).at(0), route_from_nest_to_food.at(i).at(1));
        usleep(route_from_nest_to_food.at(i).back() * 1000000); // from sec to mikrosec.
    }
    diff_state = BACK_TO_NEST_AGAIN;
}

void follower::back_To_Nest_Again()
{
    motor.turn180();
    picam.change2blue();
    reverse_Motor_values();
    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        motor.set_motor_speed(route_from_food_to_nest.at(i).at(0), route_from_food_to_nest.at(i).at(1));
        usleep(route_from_food_to_nest.at(i).back() * 1000000); // from sec to mikrosec.
    }
    diff_state = HOOKED_ON_A_FEELING;
}

void follower::run()
{
    while (true)
    {
        switch (diff_state)
        {
        case GETTING_READY:
            getting_Ready();
            break;
        case FOLLOW:
            follow();
            break;
        case BACK_TO_NEST:
            back_To_Nest();
            break;
        case BACK_TO_FOOD:
            back_To_Food();
            break;
        case BACK_TO_NEST_AGAIN:
            back_To_Nest_Again();
            break;
        case HOOKED_ON_A_FEELING:
            break;
        default:
            std::cout << "I failed my master" << std::endl;
            break;
        }
    }
}

void follower::get_logging()
{
}

void follower::printlog()
{
}

void follower::reverse_Motor_values()
{
    route_from_food_to_nest = route_from_nest_to_food;
    std::vector<double> temp = route_from_food_to_nest.back();
    route_from_food_to_nest.pop_back();
    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        // double temp;
        // temp = route_from_nest_to_food.at(i).at(0);
        // route_from_nest_to_food.at(i).at(0) = route_from_nest_to_food.at(i).at(1);
        // route_from_nest_to_food.at(i).at(1) = temp;
        std::swap(route_from_food_to_nest[i][0], route_from_food_to_nest[i][1]);
    }

    std::reverse(route_from_food_to_nest.begin(), route_from_food_to_nest.end());
    route_from_food_to_nest.push_back(temp);

    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        for (int j = 0; j < route_from_food_to_nest.at(i).size(); j++)
        {
            std::cout << route_from_food_to_nest.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

// void follower::message_Handler()
// {
//     comm.reader();
//     if (comm.data.data() == "Ready")
//     {
//        getting_Ready();

//     }
//     else if (/* condition */)
//     {
//         /* code */
//     }
//     else
//     {
//         /* code */
//     }

// }
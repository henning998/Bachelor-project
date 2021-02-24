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
        motor.love(left, right, picam.size,true);
        if (picam.size > 0.85)
        {
            motor.stop(true);
            usleep(100000);
            get_logging();
            printlog();
            motor.turn180();
            diff_state = BACK_TO_NEST;
            break;
        }
    }
}
void leader::back_To_Nest()
{   
    picam.change2blue();
    reverse_Motor_values();
    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        motor.set_motor_speed(route_from_food_to_nest.at(i).at(0),route_from_food_to_nest.at(i).at(1));
        usleep(route_from_food_to_nest.at(i).back()*1000000);// from sec to mikrosec.
    }
    motor.turn180();
    diff_state = CALL_FOLLOWER;
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

void leader::get_logging()
{
   route_from_nest_to_food = motor.get_logging();
}
void leader::printlog()
{
    for (int i = 0; i < route_from_nest_to_food.size(); i++)
    {
        for (int j = 0; j < route_from_nest_to_food.at(i).size(); j++)
        {
            std::cout << route_from_nest_to_food.at(i).at(j) << " "; 
        }
        std::cout << std::endl;
    }
}

void leader::run()
{
    while (1)
    {
    switch (diff_state)
    {
    case FIND_FOOD:
        find_Food();
        break;
    case BACK_TO_NEST:
        back_To_Nest();
        break;
    default:
        break;
    }
    }
}

void leader::reverse_Motor_values()
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
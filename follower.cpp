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
    if (comm.message == "Ready")
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
        // Calculate how much the blob is to the left/right of the center
        blob_left_right(left, right);
        // If the green blob is being detected drive else stop
        if (picam.new_pic)
        {
            motor.love(left, right, picam.size, true);
        }
        else
        {
            motor.stop();
        }
        // If the robot are to close
        if (picam.size > 0.35)
        {
            motor.stop(true);
            comm.reader();
            // Does the leader see the goal
            if (comm.message == "Goal found")
            {

                comm.writing("Okay move");
                while (diff_state == FOLLOW)
                {
                    comm.reader();

                    if (comm.message == "I have moved")
                    {
                        while (diff_state == FOLLOW)
                        {
                            picam.change2red();
                            picam.getpicture();
                            cv::waitKey(27);
                            float left = 0, right = 0;
                            // Calculate how much the blob is to the left/right of the center
                            blob_left_right(left, right);
                            if (picam.new_pic)
                            {
                                motor.love(left, right, picam.size, true);
                                // When the robot see the goal
                                if (picam.size > 0.35)
                                {
                                    motor.stop(true);
                                    diff_state = BACK_TO_NEST;
                                    get_logging();
                                }
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
    // Drive on the logged motor values
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
    // Drive on the logged motor values
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
    // Drive on the logged motor values
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
    route_from_nest_to_food = motor.get_logging();
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

void follower::blob_left_right(float &left, float &right)
{
    if (picam.x < 150)
    {
        left = (150 - picam.x) / 150;
        right = 0;
    }
    if (picam.x > 170)
    {
        left = 0;
        right = (picam.x - 170) / 150;
    }
}
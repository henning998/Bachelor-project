#include "leader.h"

void leader::log_encoder()
{
    std::cout << " I am here " << std::endl;
    controller log_data;
    while (diff_state == FIND_FOOD)
    {
        log_data.get_encode_values();
    }
    encoder_values = log_data.encode;
}


leader::leader()
{
    comm.connecting();
}

leader::~leader()
{
}
void leader::find_Food()
{
    picam.change2red();
    std::thread log_thread(&leader::log_encoder, this);
    while (true)
    {
        picam.getpicture();
        cv::waitKey(27);
        float left = 0, right = 0;
        // Calculate how much the blob is to the left/right of the center
        blob_left_right(left, right);
        motor.love(left, right, picam.size, true);
        if (picam.size > 0.85) // When the robot is close enough to the blob
        {
            motor.stop(true);
            get_logging();
            //printlog();
            diff_state = BACK_TO_NEST;
            usleep(100000);
            log_thread.join();
            for (int i = 0; i < encoder_values.size(); i++)
            {
                for (int j = 0; j < encoder_values.at(i).size(); j++)
                {
                    std::cout << encoder_values.at(i).at(j) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "Size of encoder values: " << encoder_values.size()  << std::endl;
            
            break;
        }
    }
}
void leader::back_To_Nest()
{
    motor.turn180();
    picam.change2blue();
    reverse_Motor_values();
    // Drive on the logged motor values
    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        motor.set_motor_speed(route_from_food_to_nest.at(i).at(0), route_from_food_to_nest.at(i).at(1));
        usleep(route_from_food_to_nest.at(i).back() * 1000000); // From sec to mikrosec.
    }
    motor.turn180();
    diff_state = CALL_FOLLOWER;
}
void leader::call_Follower()
{
    usleep(500000);        // Sleep so server don't get spammed
    comm.writing("Ready"); // Ready to start tandem running
    comm.reader();
    if (comm.message == "I am here") // Wait for response from client
    {
        diff_state = GUIDE_FOLLOWER;
    }
}
void leader::guide_Follower()
{
    picam.change2red();
    // Drive on the logged motor values
    for (int i = 0; i < route_from_nest_to_food.size(); i++)
    {
        motor.set_motor_speed(route_from_nest_to_food.at(i).at(0), route_from_nest_to_food.at(i).at(1));
        usleep(route_from_nest_to_food.at(i).back() * 1000000); // From sec to mikrosec.
    }
    while (true)
    {
        usleep(500000); // Sleep so server don't get spammed
        comm.writing("Goal found");
        comm.reader();
        if (comm.message == "Okay move")
        {
            diff_state = MAKE_ROOM;
            break;
        }
    }
}

void leader::make_room()
{
    picam.change2red();
    picam.getpicture();
    cv::waitKey(27);
    float left = 0, right = 0;
    // Calculate how much the blob is to the left/right of the center
    blob_left_right(left, right);
    motor.fear(left, right, picam.size, true);
    usleep(2000000);
    motor.stop();
    comm.writing("I have moved");
    usleep(5000000);
    diff_state = BACK_TO_NEST_AGAIN;
}

void leader::back_to_nest_again()
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
    while (true)
    {
        switch (diff_state)
        {
        case FIND_FOOD:
            find_Food();
            break;
        case BACK_TO_NEST:
            back_To_Nest();
            break;
        case CALL_FOLLOWER:
            call_Follower();
            break;
        case GUIDE_FOLLOWER:
            guide_Follower();
            break;
        case MAKE_ROOM:
            make_room();
            break;
        case BACK_TO_NEST_AGAIN:
            back_to_nest_again();
            break;
        case HOOKED_ON_A_FEELING:
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
        std::swap(route_from_food_to_nest[i][0], route_from_food_to_nest[i][1]);
    }

    std::reverse(route_from_food_to_nest.begin(), route_from_food_to_nest.end());
    route_from_food_to_nest.push_back(temp);

    for (int i = 0; i < route_from_food_to_nest.size(); i++)
    {
        for (int j = 0; j < route_from_food_to_nest.at(i).size(); j++)
        {
         //   std::cout << route_from_food_to_nest.at(i).at(j) << " ";
        }
       // std::cout << std::endl;
    }
}

void leader::blob_left_right(float &left, float &right)
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
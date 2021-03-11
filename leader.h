#ifndef LEADER_H
#define LEADER_H

#include "include.h"
#include "camera.h"
#include "Braitenberg.h"
#include "client.h"

class leader
{
private:
    camera picam;      // Camera object
    Braitenberg motor; // Braitenberg object
    client comm;       // Client object
    enum state         // Define all the states for the leader
    {
        FIND_FOOD,
        BACK_TO_NEST,
        CALL_FOLLOWER,
        GUIDE_FOLLOWER,
        MAKE_ROOM,
        BACK_TO_NEST_AGAIN,
        HOOKED_ON_A_FEELING
    };
    state diff_state = FIND_FOOD;                             // Set start state
    std::vector<std::vector<double>> route_from_nest_to_food; // Logged route from nest to food
    std::vector<std::vector<double>> route_from_food_to_nest; // Logged route from food to nest
    std::vector<std::vector<int>> encoder_values;

    std::vector<int> left_encoder_tics;
    std::vector<int> right_encoder_tics;
    std::vector<int> return_left_encoder_values;
    std::vector<int> return_right_encoder_values;

    bool FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = false;

    void log_encoder();
    std::vector<int> tic_count(int tail, int head);


public:
    leader();
    ~leader();
    //Robot go out and find food
    void find_Food();
    //Robot go back to nest
    void back_To_Nest();
    //Calling of follower to start the tandem running
    void call_Follower();
    //Guiding follower robot to the food
    void guide_Follower();
    //Goes into "fear" braitenberg to go away from food, so follower can see the food and find it for itself
    void make_room();
    //After follower robot found the food wait to it is out of the way and go back to nest
    void back_to_nest_again();
    //Main loop controlling all states leader robot can go into
    void run();
    //Getting the loggged data
    void get_logging();
    //Printing the logged data
    void printlog();
    //Takes the logged route to food and reverse it
    void reverse_Motor_values();
    // calculate left and right
    void blob_left_right(float &left, float &right);
    //Dance party
    void hooked_on_a_feeling();
};

#endif
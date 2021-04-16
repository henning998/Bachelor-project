#ifndef LEADER_H
#define LEADER_H

#include "include.h"
#include "camera.h"
#include "Braitenberg.h"
#include "client.h"

class leader
{
private:
    bool run_leader = true;
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
    state diff_state = FIND_FOOD; // Set start state
    // std::vector<std::vector<double>> route_from_nest_to_food; // Logged route from nest to food
    // std::vector<std::vector<double>> route_from_food_to_nest; // Logged route from food to nest
    std::vector<std::vector<int>> encoder_values;

    std::vector<int> left_encoder_tics;
    std::vector<int> right_encoder_tics;
    std::vector<double> timepoint;
    // std::vector<int> return_left_encoder_values;
    // std::vector<int> return_right_encoder_values;
    double theta_param = 0.0;
    
    int tics_from_food_to_nest = 0;

    double center_of_wheel_base = (6.4/20.4)*2800; // Cm to tics

    bool FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = false;

    void log_encoder();
    std::vector<int> tic_count(int tail, int head);

    gsl_vector *X_Y_Theta = gsl_vector_alloc(3);
    void set_rotation_matrix(gsl_matrix &rotationmatrix, int i);
    void set_translation(gsl_vector &translation, int i);
    void set_icc(gsl_vector &ICC, int i);

    void position_direction();
    double direction_vector();
    void go_straight(int tics_to_go);
    
    int time_to_fear = 3000000; // 3 seconds
    int time_to_wait = 10000000; // 10 seconds

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
    //  void get_logging();
    //Printing the logged data
    // void printlog();
    //Takes the logged route to food and reverse it
    // void reverse_Motor_values();
    // calculate left and right
    void blob_left_right(float &left, float &right);
    void file(std::string file_name);
    //Dance party
    void hooked_on_a_feeling();
};

#endif
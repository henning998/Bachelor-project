#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "include.h"
#include "camera.h"
#include "Braitenberg.h"
#include "server.h"

class follower
{
private:
    camera picam;      // Camera object
    Braitenberg motor; // Braitenberg object
    server comm;       // Client object
    enum state         // Define all the states for the leader
    {
        GETTING_READY,
        FOLLOW,
        BACK_TO_NEST,
        BACK_TO_FOOD,
        BACK_TO_NEST_AGAIN,
        HOOKED_ON_A_FEELING
    };
    state diff_state = GETTING_READY;                         // Set start state
    std::vector<std::vector<double>> route_from_nest_to_food; // Logged route from nest to food
    std::vector<std::vector<double>> route_from_food_to_nest; // Logged route from food to nest

    std::vector<int> tic_count(int tail, int head);
    void log_encoder();

    double theta_param = 0.0;

    int tics_from_food_to_nest = 0;

    std::vector<int> route_length;

    double center_of_wheel_base = (6.9 / 18.849) * 2800; // Cm to tics

    bool FLAG_FOR_PUSHING_BACK_ENCODE_VALUE = false;

    bool follower_run = true;

    std::vector<std::vector<int>> encoder_values;

    std::vector<std::vector<int>> encoder_tics;
    std::vector<std::vector<std::vector<int>>> encode_tics_file;

    std::vector<int> left_encoder_tics;
    std::vector<int> right_encoder_tics;

    std::vector<double> timepoint;
    std::vector<std::vector<double>> timepoint_file;

    gsl_vector *X_Y_Theta = gsl_vector_alloc(3); // Position and direction

    void set_rotation_matrix(gsl_matrix &rotationmatrix, int i);
    void set_translation(gsl_vector &translation, int i);
    void set_icc(gsl_vector &ICC, int i);
    void position_direction();
    double direction_vector();
    void go_straight(int tics_to_go);
    void file(std::string file_name); // Log parameters

public:
    follower();
    ~follower();
    //Initial state. Waiting for server to find food and get back
    void getting_Ready();
    //Follow leader to food and see it
    void follow();
    //Turn and go back to nest
    void back_To_Nest();
    //Use logged data from leader route to get back to the food
    void back_To_Food();
    //Use the back to nest data to get back again
    void back_To_Nest_Again();
    //Main loop that keep track of all states
    void run();
    //Get the logged data
    //void get_logging();
    //Print the logged data
    //void printlog();
    //Take the logged data and reverse it
    //void reverse_Motor_values();
    // calculate left and right
    void blob_left_right(float &left, float &right);
    //Dance party
    void hooked_On_A_Feeling();
};

#endif
#ifndef BRAITENBERG_H
#define BRAITENBERG_H

#include "controller.h"

class Braitenberg
{
private:
    controller Motor;         // Controller object
    int MaxSpeed = 90;        // Variable to adjust max speed
    int MinSpeed = 65;      // Variable to adjust min speed , 65
    float centerWeight = 0.3; // Weight for adjusting the importance of the blob being centered 0,45
    float distWeight = 0.3;   // Weight for adjusting the importance of the distance to the blob 0,2
    int turn_tic = 4000;
    int tic_moveback = 2193;
public:
    Braitenberg();
    ~Braitenberg();
    //Love left sensor -> (-) left motor , right sensor -> (-) right motor
    void love(float left, float right, float dist, bool log = false); // Input between 0-1
    //Fear left sensor -> (+) left motor , right sensor -> (+) right motor
    void fear(float left, float right, float dist, bool log = false); // Input between 0-1
    //Explorer left sensor -> (-) right motor , right sensor -> (-) left motor
    void explorer(float left, float right, float dist); // Input between 0-1
    //Agression left sensor -> (+) right motor , right sensor -> (+) left motor
    void agression(float left, float right, float dist); // Input between 0-1
    // Set the motor speed for forward
    void set_motor_speed(int left, int right); // Input between 0-1
    // Get the logged data from controller object
    std::vector<std::vector<double>> get_logging();
    // Turn the robot 180
    void turn(double theta = M_PI);
    // Stop the robot
    void stop(bool log = false); // Log the stop or not
    //@return MaxSpeed, MinSpeed, centerweight, distweight, turn_tic
    std::vector<float> parameters();
};

#endif
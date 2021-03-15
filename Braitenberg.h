#ifndef BRAITENBERG_H
#define BRAITENBERG_H

#include "controller.h"

class Braitenberg
{
private:
    controller Motor;         // Controller object
    int MaxSpeed = 100;        // Variable to adjust max speed
    int MinSpeed = 60;      // Variable to adjust min speed
    float centerWeight = 0.4; // Weight for adjusting the importance of the blob being centered
    float distWeight = 0.4;   // Weight for adjusting the importance of the distance to the blob
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
    void turn180();
    // Stop the robot
    void stop(bool log = false); // Log the stop or not
};

#endif
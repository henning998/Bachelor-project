#ifndef BRAITENBERG_H
#define BRAITENBERG_H

#include "controller.h"

class Braitenberg
{
private:
    controller Motor;
    int MaxSpeed = 50;
    float centerWeight= 0.4;
    float distWeight = 0.4;
public:
    Braitenberg(/* args */);
    ~Braitenberg();
    //love left sensor -> (-) left motor , right sensor -> (-) right motor
    void love(float left, float right, float dist, bool log = false);// input between 0-1
    //fear left sensor -> (+) left motor , right sensor -> (+) right motor
    void fear(float left, float right, float dist);// input between 0-1
    //love left sensor -> (-) right motor , right sensor -> (-) left motor
    void explorer(float left, float right, float dist);// input between 0-1
    //love left sensor -> (+) right motor , right sensor -> (+) left motor
    void agression(float left, float right, float dist);// input between 0-1
    void set_motor_speed(int left , int right);
    std::vector<std::vector<double>> get_logging();
    void turn180();
    void stop(bool log = false);
};





#endif
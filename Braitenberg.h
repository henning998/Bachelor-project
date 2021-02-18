#ifndef BRAITENBERG_H
#define BRAITENBERG_H

#include "controller.h"

class Braitenberg
{
private:
    controller Motor;
    int MaxSpeed = 30;
    float centerWeight= 0.4;
    float distWeight = 0.4;
public:
    Braitenberg(/* args */);
    ~Braitenberg();
    //love left sensor -> (-) left motor , right sensor -> (-) right motor
    void love(float left, float right, float dist);// input between 0-1
    //fear left sensor -> (+) left motor , right sensor -> (+) right motor
    void fear(float left, float right, float dist);// input between 0-1
    //love left sensor -> (-) right motor , right sensor -> (-) left motor
    void explorer(float left, float right, float dist);// input between 0-1
    //love left sensor -> (+) right motor , right sensor -> (+) left motor
    void agression(float left, float right, float dist);// input between 0-1
    
    void turn180();
    void stop();
};





#endif
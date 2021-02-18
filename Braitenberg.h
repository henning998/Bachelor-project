#ifndef BRAITENBERG_H
#define BRAITENBERG_H

#include "controller.h"

class Braitenberg
{
private:
    controller Motor;
    int MaxSpeed = 40;
public:
    Braitenberg(/* args */);
    ~Braitenberg();
    //love left sensor -> (-) left motor , right sensor -> (-) right motor
    void love(float left, float right);// input between 0-1
    //fear left sensor -> (+) left motor , right sensor -> (+) right motor
    void fear(float left, float right);// input between 0-1
    //love left sensor -> (-) right motor , right sensor -> (-) left motor
    void explorer(float left, float right);// input between 0-1
    //love left sensor -> (+) right motor , right sensor -> (+) left motor
    void agression(float left, float right);// input between 0-1
    
    void turn180();
};





#endif
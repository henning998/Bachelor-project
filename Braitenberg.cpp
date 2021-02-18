#include "Braitenberg.h"

#define forward 1
#define backward 0

Braitenberg::Braitenberg(/* args */)
{
}

Braitenberg::~Braitenberg()
{
}

 //love left sensor -> (-) left motor , right sensor -> (-) right motor
void Braitenberg::love(float left, float right, float dist)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed - (left * MaxSpeed)*centerWeight -(dist*MaxSpeed)*distWeight;
    SpeedR = MaxSpeed - (right * MaxSpeed)*centerWeight-(dist*MaxSpeed)*distWeight;
    if (SpeedR< 18)
    {
        SpeedR = 0;
    }
    if (SpeedL< 18)
    {
        SpeedL = 0;
    }
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//fear left sensor -> (+) left motor , right sensor -> (+) right motor
void Braitenberg::fear(float left, float right, float dist)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL =  (left * MaxSpeed)*centerWeight + (dist*MaxSpeed)*distWeight;
    SpeedR =  (right * MaxSpeed)*centerWeight + (dist*MaxSpeed)*distWeight;
    if (SpeedR< 18)
    {
        SpeedR = 18;
    }
    if (SpeedL< 18)
    {
        SpeedL = 18;
    }
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//love left sensor -> (-) right motor , right sensor -> (-) left motor
void Braitenberg::explorer(float left, float right, float dist)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed - (right * MaxSpeed) -(dist*MaxSpeed)*distWeight;
    SpeedR = MaxSpeed - (left * MaxSpeed) -(dist*MaxSpeed)*distWeight;
    if (SpeedR< 18)
    {
        SpeedR = 0;
    }
    if (SpeedL< 18)
    {
        SpeedL = 0;
    }
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//love left sensor -> (+) right motor , right sensor -> (+) left motor
void Braitenberg::agression(float left, float right, float dist)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL =  (right * MaxSpeed)*centerWeight + (dist*MaxSpeed)*distWeight;
    SpeedR =  (left * MaxSpeed)*centerWeight + (dist*MaxSpeed)*distWeight;
    if (SpeedR< 18)
    {
        SpeedR = 18;
    }
    if (SpeedL< 18)
    {
        SpeedL = 18;
    }
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

void Braitenberg::turn180()
{
    Motor.setLeftMotorSpeedDirection(20,forward);
    Motor.setRightMotorSpeedDirection(20,backward);
    usleep(2600000); // 2,6 sec calculated with trail and error battery 90%-100%
    Motor.setLeftMotorSpeedDirection(0,forward);
    Motor.setRightMotorSpeedDirection(0,backward);
}

void Braitenberg::stop()
{
    Motor.setLeftMotorSpeedDirection(0,forward);
    Motor.setRightMotorSpeedDirection(0,forward);
}
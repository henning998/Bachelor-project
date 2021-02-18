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
void Braitenberg::love(float left, float right)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed - (left * MaxSpeed);
    SpeedR = MaxSpeed - (right * MaxSpeed);
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//fear left sensor -> (+) left motor , right sensor -> (+) right motor
void Braitenberg::fear(float left, float right)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed + (left * MaxSpeed);
    SpeedR = MaxSpeed + (right * MaxSpeed);
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//love left sensor -> (-) right motor , right sensor -> (-) left motor
void Braitenberg::explorer(float left, float right)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed - (right * MaxSpeed);
    SpeedR = MaxSpeed - (left * MaxSpeed);
    Motor.setLeftMotorSpeedDirection(SpeedL,forward);
    Motor.setRightMotorSpeedDirection(SpeedR,forward);
}

//love left sensor -> (+) right motor , right sensor -> (+) left motor
void Braitenberg::agression(float left, float right)// input between 0-1
{
    float SpeedL , SpeedR;
    SpeedL = MaxSpeed + (right * MaxSpeed);
    SpeedR = MaxSpeed + (left * MaxSpeed);
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
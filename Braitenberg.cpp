#include "Braitenberg.h"

// #define forward 1
// #define backward 0

Braitenberg::Braitenberg()
{
}

Braitenberg::~Braitenberg()
{
}

//Love left sensor -> (-) left motor , right sensor -> (-) right motor
void Braitenberg::love(float left, float right, float dist, bool log) // Input between 0-1
{
    //std::cout << "left right dist " << left << " " << right << " " << dist <<std::endl;
    float SpeedL, SpeedR;
    SpeedL = MaxSpeed - (left * MaxSpeed) * centerWeight - (dist * MaxSpeed) * distWeight;
    SpeedR = MaxSpeed - (right * MaxSpeed) * centerWeight - (dist * MaxSpeed) * distWeight;
    // Make sure the robot's wheel can turn
    if (SpeedR < MinSpeed)
    {
        SpeedR = 0;
    }
    if (SpeedL < MinSpeed)
    {
        SpeedL = 0;
    }
    // Set the calcualate speed on the robot
   // std::cout << "speedL SpeedR " << SpeedL << " " << SpeedR << std::endl;
    Motor.setMotorSpeedDirection(SpeedL, SpeedR, forward, forward, log);
}

//Fear left sensor -> (+) left motor , right sensor -> (+) right motor
void Braitenberg::fear(float left, float right, float dist, bool log) // Input between 0-1
{
    float SpeedL, SpeedR;
    SpeedL = (left * MaxSpeed) * centerWeight + (dist * MaxSpeed) * distWeight;
    SpeedR = (right * MaxSpeed) * centerWeight + (dist * MaxSpeed) * distWeight;
    if (SpeedR < MinSpeed)
    {
        SpeedR = MinSpeed;
    }
    if (SpeedL < MinSpeed)
    {
        SpeedL = MinSpeed;
    }
    Motor.setMotorSpeedDirection(SpeedL, SpeedR, forward, forward, log);
}

//Explorer left sensor -> (-) right motor , right sensor -> (-) left motor
void Braitenberg::explorer(float left, float right, float dist) // Input between 0-1
{
    float SpeedL, SpeedR;
    SpeedL = MaxSpeed - (right * MaxSpeed) - (dist * MaxSpeed) * distWeight;
    SpeedR = MaxSpeed - (left * MaxSpeed) - (dist * MaxSpeed) * distWeight;
    if (SpeedR < MinSpeed)
    {
        SpeedR = 0;
    }
    if (SpeedL < MinSpeed)
    {
        SpeedL = 0;
    }
    Motor.setMotorSpeedDirection(SpeedL, SpeedR, forward, forward);
}

//Agression left sensor -> (+) right motor , right sensor -> (+) left motor
void Braitenberg::agression(float left, float right, float dist) // Input between 0-1
{
    float SpeedL, SpeedR;
    SpeedL = (right * MaxSpeed) * centerWeight + (dist * MaxSpeed) * distWeight;
    SpeedR = (left * MaxSpeed) * centerWeight + (dist * MaxSpeed) * distWeight;
    if (SpeedR < MinSpeed)
    {
        SpeedR = MinSpeed;
    }
    if (SpeedL < MinSpeed)
    {
        SpeedL = MinSpeed;
    }
    Motor.setMotorSpeedDirection(SpeedL, SpeedR, forward, forward);
}

void Braitenberg::turn(double theta) // NEED UPDATE TO TURN BOTH WAY
{

    int tic = (3015 / M_PI) * (abs(theta)) ; 
    //std::cout << " tic " << tic << std::endl;

    //Turn to the right
    int tics_r = 0, tics_l = 0;
    std::vector<int> last_run = Motor.get_encode_values();
    while (tics_r <= tic || tics_l <= tic) //4523
    {
        std::vector<int> temp = Motor.get_encode_values();
        // for (int i = 0; i < temp.size(); i++)
        // {
        //     std::cout<<temp.at(i) << " " ;
        // }
        // std::cout << std::endl;

        if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
        {
            tics_l++;
        }
        if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
        {
            tics_r++;
        }
        last_run = temp;
        if (theta < 0)
        {
            if (tics_r <= tic)
            {
                Motor.setRightMotorSpeedDirection(MinSpeed, forward);
            }
            else
            {
                Motor.setRightMotorSpeedDirection(0, backward);
            }

            if (tics_l <= tic)
            {
                Motor.setLeftMotorSpeedDirection(MinSpeed, backward);
            }
            else
            {
                Motor.setLeftMotorSpeedDirection(0, forward);
            }
        }
        else
        {
            if (tics_r <= tic)
            {
                Motor.setRightMotorSpeedDirection(MinSpeed, backward);
            }
            else
            {
                Motor.setRightMotorSpeedDirection(0, backward);
            }

            if (tics_l <= tic)
            {
                Motor.setLeftMotorSpeedDirection(MinSpeed, forward);
            }
            else
            {
                Motor.setLeftMotorSpeedDirection(0, forward);
            }
        }
        //std::cout << "tics_l: " << tics_l << " & tics_r: " << tics_r << std::endl;
    }

    if (theta > M_PI / 2 || theta < M_PI/2)
    {
        tic = 2193 * abs(cos(theta));
    }
    else
    {
        tic = 0;
    }
    tics_r = 0, tics_l = 0;
    last_run = Motor.get_encode_values();
    while (tics_r <= tic || tics_l <= tic) //4523
    {
        std::vector<int> temp = Motor.get_encode_values();

        if (temp.at(0) != last_run.at(0) || temp.at(1) != last_run.at(1))
        {
            tics_l++;
        }
        if (temp.at(2) != last_run.at(2) || temp.at(3) != last_run.at(3))
        {
            tics_r++;
        }
        last_run = temp;
        if (tics_r <= tic)
        {
            int difference = 0;
            if (tics_r < tics_l)
            {
                difference = (tics_l - tics_r) * 0.33;
            }

            Motor.setRightMotorSpeedDirection(65 + difference,backward);
        }
        else
        {
            Motor.setRightMotorSpeedDirection(0, backward);
        }

        if (tics_l <= tic)
        {
            int difference = 0;
            if (tics_l < tics_r)
            {
                difference = (tics_r - tics_l) * 0.33;
            }

            Motor.setLeftMotorSpeedDirection(65 + difference, backward);
        }
        else
        {
            Motor.setLeftMotorSpeedDirection(0, backward);
        }
        // std::cout << "tics_l: " << tics_l << " & tics_r: " <<tics_r << std::endl;
    }
}

void Braitenberg::stop(bool log)
{
    Motor.setMotorSpeedDirection(0, 0, forward, forward, log);
}
std::vector<std::vector<double>> Braitenberg::get_logging()
{
    return Motor.get_logging();
}
void Braitenberg::set_motor_speed(int left, int right)
{
    Motor.setMotorSpeedDirection(left, right, 1, 1);
}
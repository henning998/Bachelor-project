#include "controller.h"

controller::controller()
{
        // Initialize bus and exit program if error occurs
        if (!bus.Init())
                std::cout << "error matrix bus, check matrix and restart program" << std::endl;
        // Set gpio to use MatrixIOBus bus
        gpio.Setup(&bus);

        // Initialise Matrix Voice GPIO pins
        initGPIOPins(&gpio);
}

controller::~controller()
{
}

void controller::initGPIOPins(matrix_hal::GPIOControl *gpio)
{

        gpio->SetMode(TB6612_RIGHT_MOTOR_PWMA, 1);     //Pin mode as output
        gpio->SetFunction(TB6612_RIGHT_MOTOR_PWMA, 1); // Pin function as PWM
        gpio->SetMode(TB6612_RIGHT_MOTOR_AIN1, 1);
        gpio->SetMode(TB6612_RIGHT_MOTOR_AIN2, 1);

        gpio->SetMode(TB6612_LEFT_MOTOR_PWMB, 1);     //Pin mode as output
        gpio->SetFunction(TB6612_LEFT_MOTOR_PWMB, 1); // Pin function as PWM
        gpio->SetMode(TB6612_LEFT_MOTOR_BIN1, 1);
        gpio->SetMode(TB6612_LEFT_MOTOR_BIN2, 1);

        // setup encoder
        gpio->SetMode(MOTOR_ENCODER_LEFT_1, 0);
        gpio->SetMode(MOTOR_ENCODER_LEFT_2, 0);
        gpio->SetMode(MOTOR_ENCODER_RIGHT_1, 0);
        gpio->SetMode(MOTOR_ENCODER_RIGHT_2, 0);
}

void controller::setLeftMotorSpeedDirection(int speed, int dir)
{
        if (dir <= 0) // Reverse
        {
                gpio.SetGPIOValue(TB6612_LEFT_MOTOR_BIN1, 0); // Rotate left motor clockwise
                gpio.SetGPIOValue(TB6612_LEFT_MOTOR_BIN2, 1);
        }
        if ((dir > 0) || (dir >= 1)) // Forward
        {
                gpio.SetGPIOValue(TB6612_LEFT_MOTOR_BIN1, 1); // Rotate left motor clockwise
                gpio.SetGPIOValue(TB6612_LEFT_MOTOR_BIN2, 0);
        }

        // Set motor speed via PWM signal (min. = 0, max. = 100)
        if (speed > 100)
                speed = 100;
        if (speed < 0)
                speed = 0;

        gpio.SetPWM(1000, speed, TB6612_LEFT_MOTOR_PWMB);
}

void controller::setRightMotorSpeedDirection(int speed, int dir)
{
        if (dir <= 0) // Reverse
        {
                gpio.SetGPIOValue(TB6612_RIGHT_MOTOR_AIN1, 0); // Rotate left motor clockwise
                gpio.SetGPIOValue(TB6612_RIGHT_MOTOR_AIN2, 1);
        }
        if ((dir > 0) || (dir >= 1)) // Forward
        {
                gpio.SetGPIOValue(TB6612_RIGHT_MOTOR_AIN1, 1); // Rotate left motor clockwise
                gpio.SetGPIOValue(TB6612_RIGHT_MOTOR_AIN2, 0);
        }

        // Set motor speed via PWM signal (min. = 0, max. = 100)
        if (speed > 100)
                speed = 100;
        if (speed < 0)
                speed = 0;

        gpio.SetPWM(1000, speed, TB6612_RIGHT_MOTOR_PWMA);
}

void controller::setMotorSpeedDirection(int speedL, int speedR, int dirL, int dirR, bool log)
{
        setLeftMotorSpeedDirection(speedL, dirL);
        setRightMotorSpeedDirection(speedR, dirR);
        if (log)
        {
                logging(speedL, speedR, dirL, dirR);
        }
}

void controller::logging(int speedL, int speedR, int dirL, int dirR)
{
        double time_elapsed;
        std::vector<double> temp;
        temp.push_back(speedL);
        temp.push_back(speedR);
        temp.push_back(dirL);
        temp.push_back(dirR);
        if (datalog.size() < 1)
        {
                timer = std::chrono::steady_clock::now();
        }
        else
        {
                // calculate how long the motor values have been running on the robot
                std::chrono::_V2::steady_clock::time_point end = timer;
                timer = std::chrono::steady_clock::now();
                time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(timer - end).count();
                datalog.at(datalog.size() - 1).push_back(time_elapsed); // push it back to the previous motor values
        }
        datalog.push_back(temp);
}

std::vector<std::vector<double>> controller::get_logging()
{
        return datalog;
}

void controller::get_encode_values()
{
        int left_1 = gpio.GetGPIOValue(MOTOR_ENCODER_LEFT_1 );
        int left_2 = gpio.GetGPIOValue(MOTOR_ENCODER_LEFT_2 );
        int right_1 = gpio.GetGPIOValue(MOTOR_ENCODER_RIGHT_1);
        int right_2 = gpio.GetGPIOValue(MOTOR_ENCODER_RIGHT_2);

        std::vector<int> temp;
        temp.push_back(left_1);
        temp.push_back(left_2);
        temp.push_back(right_1);
        temp.push_back(right_2);
        encode.push_back(temp);
       // std::cout << "Left: " << left_1 << " " << left_2 << std::endl;
       // std::cout << "right: " << right_1 << " " << right_2 << std::endl;
}
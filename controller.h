#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <unistd.h>
#include <matrix_hal/gpio_control.h>
#include <matrix_hal/matrixio_bus.h>

#include <pigpio.h>
#include <cmath>

/*
#define TB6612_RIGHT_MOTOR_PWMA = 12 // (Orange)
#define TB6612_LEFT_MOTOR_PWMB          13 // (Green)
#define TB6612_RIGHT_MOTOR_AIN1         16 // (Blue)
#define TB6612_RIGHT_MOTOR_AIN2         26 // (Brown)
#define TB6612_LEFT_MOTOR_BIN1          5  // (Grey)
#define TB6612_LEFT_MOTOR_BIN2          6  // (Pink)



#define  TB6612_RIGHT_MOTOR_PWMA        13 // (Orange)
#define  TB6612_LEFT_MOTOR_PWMB         16 // (Green)
#define  TB6612_RIGHT_MOTOR_AIN1        19 // (Blue)
#define  TB6612_RIGHT_MOTOR_AIN2        26 // (Brown)
#define  TB6612_LEFT_MOTOR_BIN1         20 // (Grey)
#define  TB6612_LEFT_MOTOR_BIN2         21 // (Pink)
*/

#define TB6612_RIGHT_MOTOR_PWMA 14 // (Orange)
#define TB6612_LEFT_MOTOR_PWMB 8   // (Green)
#define TB6612_RIGHT_MOTOR_AIN1 12 // (Blue)
#define TB6612_RIGHT_MOTOR_AIN2 10 // (Brown)
#define TB6612_LEFT_MOTOR_BIN1 6   // (Grey)
#define TB6612_LEFT_MOTOR_BIN2 4   // (Pink)
#define MOTOR_ENCODER_LEFT_1 3 
#define MOTOR_ENCODER_LEFT_2 1
#define MOTOR_ENCODER_RIGHT_1 2
#define MOTOR_ENCODER_RIGHT_2 0


class controller
{
private:
    matrix_hal::MatrixIOBus bus;                      // Create MatrixIOBus object for hardware communication
    matrix_hal::GPIOControl gpio, old_gpio;           // Create GPIOControl object
    std::vector<std::vector<double>> datalog;         // Vector that's hold the logged information
    std::chrono::_V2::steady_clock::time_point timer; // Timer
    // Initialize the GPIO pins as input and output
    void initGPIOPins(matrix_hal::GPIOControl *gpio);

public:
    controller();
    ~controller();

    //Set speed and direction of LEFT motor
    //@param dir Directiom -> 1 = forward, 0 = reverse
    //@param speed Speed -> 0-100% in steps of 1%
    void setLeftMotorSpeedDirection(int speed, int dir);
    /*Set speed and direction of RIGHT motor
    @param dir Directiom -> 1 = forward, 0 = reverse
    @param speed Speed -> 0-100% in steps of 1%*/
    void setRightMotorSpeedDirection(int speed, int dir);
    // Set the motor speed and diretion for both motors
    void setMotorSpeedDirection(int speedL, int speedR, int dirL, int dirR, bool log = false);
    // Logging the different motor values
    void logging(int speedL, int speedR, int dirL, int dirR);
    // Return the logged information
    std::vector<std::vector<double>> get_logging();

    void get_encode_values();
    std::vector<std::vector<int>> encode;
};

#endif
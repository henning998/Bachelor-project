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

#define  TB6612_RIGHT_MOTOR_PWMA        14 // (Orange)
#define  TB6612_LEFT_MOTOR_PWMB         8  // (Green)
#define  TB6612_RIGHT_MOTOR_AIN1        12 // (Blue)
#define  TB6612_RIGHT_MOTOR_AIN2        10 // (Brown)
#define  TB6612_LEFT_MOTOR_BIN1         6  // (Grey)
#define  TB6612_LEFT_MOTOR_BIN2         4  // (Pink)

class controller
{
private:
    matrix_hal::MatrixIOBus bus;  // Create MatrixIOBus object for hardware communication
    matrix_hal::GPIOControl gpio, old_gpio; // Create GPIOControl object
    void initGPIOPins(matrix_hal::GPIOControl* gpio);
public:
    controller(/* args */);
    ~controller();

    /*  Set speed and direction of LEFT motor
    Directiom -> 1 = forward, 0 = reverse
    Speed -> 0-100% in steps of 1%*/
void setLeftMotorSpeedDirection(int speed, int dir);
// Set speed and direction of RIGHT motor
// Directiom -> 1 = forward, 0 = reverse
// Speed -> 0-100% in steps of 1%
void setRightMotorSpeedDirection(int speed, int dir);

};



#endif
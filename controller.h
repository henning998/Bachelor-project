#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "include.h"



// Matrix Voice LEDs
#define MATRIX_LED_R_1 0
#define MATRIX_LED_R_2 1
#define MATRIX_LED_R_3 2
#define MATRIX_LED_R_4 3
#define MATRIX_LED_R_5 4
#define MATRIX_LED_R_6 5
#define MATRIX_LED_R_7 6
#define MATRIX_LED_R_8 7
#define MATRIX_LED_R_9 8

#define MATRIX_LED_L_1 9
#define MATRIX_LED_L_2 10
#define MATRIX_LED_L_3 11
#define MATRIX_LED_L_4 12
#define MATRIX_LED_L_5 13
#define MATRIX_LED_L_6 14
#define MATRIX_LED_L_7 15
#define MATRIX_LED_L_8 16
#define MATRIX_LED_L_9 17

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
    // Create EverloopImage object, with size of ledCount
	matrix_hal::EverloopImage everloop_image;
	// Create Everloop object
	matrix_hal::Everloop everloop;

public:
    controller();
    ~controller();

    //Set speed and direction of LEFT motor
    //@param dir Direction -> 1 = forward, 0 = reverse
    //@param speed Speed -> 0-100% in steps of 1%
    void setLeftMotorSpeedDirection(int speed, int dir);
    /*Set speed and direction of RIGHT motor
    @param dir Direction -> 1 = forward, 0 = reverse
    @param speed Speed -> 0-100% in steps of 1%*/
    void setRightMotorSpeedDirection(int speed, int dir);
    // Set the motor speed and diretion for both motors
    void setMotorSpeedDirection(int speedL, int speedR, int dirL, int dirR, bool log = false);
    // Logging the different motor values
    void logging(int speedL, int speedR, int dirL, int dirR);
    // Return the logged information
    std::vector<std::vector<double>> get_logging();

    std::vector<int> get_encode_values();

    void setled(int led,int r, int g, int b);
};

#endif
#include <iostream>
#include <unistd.h>
#include <matrix_hal/gpio_control.h>
#include <matrix_hal/matrixio_bus.h>

#include <pigpio.h>
#include <cmath>

//#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////
//                  Define                                                 //
/////////////////////////////////////////////////////////////////////////////

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


#define  TB6612_RIGHT_MOTOR_PWMA        14 // (Orange)
#define  TB6612_LEFT_MOTOR_PWMB         8  // (Green)
#define  TB6612_RIGHT_MOTOR_AIN1        12 // (Blue)
#define  TB6612_RIGHT_MOTOR_AIN2        10 // (Brown)
#define  TB6612_LEFT_MOTOR_BIN1         6  // (Grey)
#define  TB6612_LEFT_MOTOR_BIN2         4  // (Pink)

/////////////////////////////////////////////////////////////////////////////
//                  Functions                                              //
/////////////////////////////////////////////////////////////////////////////
void initGPIOPins(matrix_hal::GPIOControl* gpio);
/*  Set speed and direction of LEFT motor
    Directiom -> 1 = forward, 0 = reverse
    Speed -> 0-100% in steps of 1%*/
void setLeftMotorSpeedDirection(matrix_hal::GPIOControl* gpio, int speed, int dir);
// Set speed and direction of RIGHT motor
// Directiom -> 1 = forward, 0 = reverse
// Speed -> 0-100% in steps of 1%
void setRightMotorSpeedDirection(matrix_hal::GPIOControl* gpio, int speed, int dir);
// setup Matrix-hal



int main()
{

    // Create MatrixIOBus object for hardware communication
    matrix_hal::MatrixIOBus bus;
    // Initialize bus and exit program if error occurs
    if (!bus.Init())
		return false;
	// Create GPIOControl object
	matrix_hal::GPIOControl gpio, old_gpio;
	// Set gpio to use MatrixIOBus bus
	gpio.Setup(&bus);

	// Initialise Matrix Voice GPIO pins
	initGPIOPins(&gpio);

    bool drive = true;
    int key;
    while (drive)
    {
       system ("/bin/stty raw");

        key = getchar();
        
        
        /* use system call to set terminal behaviour to more normal behaviour */
       system ("/bin/stty cooked");
        switch (key)
        {
        case 'w':
            // Turn forward
        	setRightMotorSpeedDirection(&gpio,25,1);
        	setLeftMotorSpeedDirection(&gpio,25,1);
            break;
        case 's':
            // Turn backward
        	setRightMotorSpeedDirection(&gpio,25,0);
        	setLeftMotorSpeedDirection(&gpio,25,0);
            break;
        case 'a':
            // Turn left
        	setRightMotorSpeedDirection(&gpio,25,1);
        	setLeftMotorSpeedDirection(&gpio,25,0);
            break;
        case 'd':
            // Turn right
        	setRightMotorSpeedDirection(&gpio,25,0);
        	setLeftMotorSpeedDirection(&gpio,25,1);
            break;
        case 27:
            drive = false;
            break;
        default:
            // Stop
           	setRightMotorSpeedDirection(&gpio,0,1);
           	setLeftMotorSpeedDirection(&gpio,0,1);
            break;
        }
        //usleep(1000000);
    }
    
   
	// Stop
	
	setRightMotorSpeedDirection(&gpio,0,1);
	setLeftMotorSpeedDirection(&gpio,0,1);

    return 0;
}

void initGPIOPins(matrix_hal::GPIOControl* gpio)
{

	gpio->SetMode(TB6612_RIGHT_MOTOR_PWMA,1); //Pin mode as output
        gpio->SetFunction(TB6612_RIGHT_MOTOR_PWMA,1); // Pin function as PWM
        gpio->SetMode(TB6612_RIGHT_MOTOR_AIN1,1);
        gpio->SetMode(TB6612_RIGHT_MOTOR_AIN2,1);

        gpio->SetMode(TB6612_LEFT_MOTOR_PWMB,1); //Pin mode as output
        gpio->SetFunction(TB6612_LEFT_MOTOR_PWMB,1); // Pin function as PWM
        gpio->SetMode(TB6612_LEFT_MOTOR_BIN1,1);
        gpio->SetMode(TB6612_LEFT_MOTOR_BIN2,1);
}

void setLeftMotorSpeedDirection(matrix_hal::GPIOControl* gpio, int speed, int dir)
{
	if (dir <= 0) // Reverse
        {
                gpio->SetGPIOValue(TB6612_LEFT_MOTOR_BIN1,0); // Rotate left motor clockwise
                gpio->SetGPIOValue(TB6612_LEFT_MOTOR_BIN2,1);
        }
    if ( (dir > 0)  || (dir >= 1) ) // Forward
        {
                gpio->SetGPIOValue(TB6612_LEFT_MOTOR_BIN1,1); // Rotate left motor clockwise
                gpio->SetGPIOValue(TB6612_LEFT_MOTOR_BIN2,0);
        }

	// Set motor speed via PWM signal (min. = 0, max. = 100)
        if (speed > 100)
                speed = 100;
        if (speed < 0)
                speed = 0;

	gpio->SetPWM(1000,speed,TB6612_LEFT_MOTOR_PWMB);
}


void setRightMotorSpeedDirection(matrix_hal::GPIOControl* gpio, int speed, int dir)
{
        if (dir <= 0) // Reverse
        {
                gpio->SetGPIOValue(TB6612_RIGHT_MOTOR_AIN1,0); // Rotate left motor clockwise
                gpio->SetGPIOValue (TB6612_RIGHT_MOTOR_AIN2,1);
        }
        if ( (dir > 0)  || (dir >= 1) ) // Forward
        {
                gpio->SetGPIOValue(TB6612_RIGHT_MOTOR_AIN1,1); // Rotate left motor clockwise
                gpio->SetGPIOValue(TB6612_RIGHT_MOTOR_AIN2,0);
        }

        // Set motor speed via PWM signal (min. = 0, max. = 100)
        if (speed > 100)
                speed = 100;
        if (speed < 0)
                speed = 0;

	gpio->SetPWM(1000,speed,TB6612_RIGHT_MOTOR_PWMA);
}


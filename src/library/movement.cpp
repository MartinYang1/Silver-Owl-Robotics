#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"

//returns the distance of the wheel inputted, this allows better PID and odometry
double distance(wheel){
    double distConst = 22.305; //tune this number
    return wheel.get_position()/distConst;
}

/** Moves the robot continuously based on voltage. A negative
 * value moves the robot backwards, while a positive
 * value moves the robot forwards. A higher left than right
 * value turns the robot right, and vice versa.
 * 
 * @param left the voltage of the motors on the left side
 * of the drive train, from -127 to 127 volts
 * @param right the voltage of the motors on the right side
 * of the drive train, from -127 to 127 volts
 */
void move(double left, double right){
    leftFrontMotor = left;
    leftBackMotor = left;
    rightFrontMotor = right;
    rightBackMotor = right;
}

//closed loop movement using PID
void move_closed_loop(double distanceLeft, double distanceRight){
    double lastErrorLeft = 0.1;
    double lastErrorRight = 0.1;
    double startLeft = distance(left_back);
    double startRight = distance(right_back);

    while (lastErrorLeft + lastErrorRight != 0){
        PID(distanceLeft, distance(left_back) - startLeft, &lastErrorLeft);
        PID(distanceRight, distance(right_back) - startRight, &lastErrorRight);
    }
}

/** Turns the robot using the gyro sensor
 * 
 * @param leftVoltage the voltage for the motors on the left side 
 * of the drive train in volts, from -127 to 127
 * @param rightVoltage the voltage for the motors on the right side 
 * of the drive train in volts, from -127 to 127
 * @param angle in degrees, to 2 decimal places. A negative angle turns the robot counter-clockwise
 * and a postive angle turns the robot clockwise
 */
void turn(double leftVoltage, double rightVoltage, float angle) {
    // if (abs(leftVoltage) > 127 || abs(rightVoltage) > 127)
    //     throw ;
    
    float currentAngle = get_heading();
    angle += currentAngle;

    if (angle > 0)
        while (currentAngle <= angle) {
            currentAngle = get_heading();
            move(leftVoltage, rightVoltage);
            pros::delay(30);
    else
        while (currentAngle >= angle) {
            currentAngle = get_heading();
            move(leftVoltage, rightVoltage);
            pros::delay(30);
    }
}

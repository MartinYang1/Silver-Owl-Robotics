#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include <math.h>
#include <vector>

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
 * @param leftVolt the voltage of the motors on the left side
 * of the drive train, from -127 to 127 volts
 * @param rightVolt the voltage of the motors on the right side
 * of the drive train, from -127 to 127 volts
 */
void move(double leftVolt, double rightVolt){
    leftFrontMotor = leftVolt;
    leftBackMotor = leftVolt;
    rightFrontMotor = rightVolt;
    rightBackMotor = rightVolt;
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

/** Turns the robot to a desired angle
 * 
 * @param leftVolt the voltage for the motors on the left side 
 * of the drive train in volts, from -127 to 127
 * @param rightVolt the voltage for the motors on the right side 
 * of the drive train in volts, from -127 to 127
 * @param angle in degrees, to 2 decimal places. A negative angle turns the robot counter-clockwise
 * and a postive angle turns the robot clockwise
 */
void turn(double leftVolt, double rightVolt, float desiredAngle) {
    // if (abs(leftVolt) > 127 || abs(rightVolt) > 127)
    //     throw ;
    
    float currentAngle = get_heading();
    desiredAngle += currentAngle;

    if (angle > 0)
        while (currentAngle <= desiredAngle) {
            currentAngle = get_heading();
            move(leftVolt, rightVolt);
            pros::delay(30);
    else
        while (currentAngle >= desiredAngle) {
            currentAngle = get_heading();
            move(leftVolt, rightVolt);
            pros::delay(30);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

/** Accelerates or decelerates the robot to a desired speed, then stops the robot
 * 
 * @param desiredSpeed the desired RPM for the robot to accelerate or decelerate to
 * @param scaleFactor the scale factor of the exponential function in acceleration.
 * A scale factor > 1 achieves acceleration. A scale factor < 1 achieves deceleration.
 */
void accelerate(double desiredSpeed, float scaleFactor) {
    unsigned numPeriods = 0;
    double initialSpeed = move_speed(), currentSpeed = initialSpeed;
    while (currentSpeed < desiredSpeed) {
        move(currentSpeed, currentSpeed);
        currentSpeed = initialSpeed * pow(scaleFactor, numPeriods);
        pros::delay(30);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

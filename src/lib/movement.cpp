#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <math.h>
#include <vector>

//returns the distance of the wheel inputted, this allows better PID and odometry
// double distance(wheel){
//     double distConst = 22.305; //tune this number
//     return wheel.get_position()/distConst;
// }

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
    double startLeft = distance(leftBackMotor);
    double startRight = distance(rightBackMotor);

    while (lastErrorLeft + lastErrorRight != 0){
        PID(distanceLeft, distance(leftBackMotor) - startLeft, &lastErrorLeft);
        PID(distanceRight, distance(rightBackMotor) - startRight, &lastErrorRight);
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

    while (abs(currentAngle) <= abs(desiredAngle)) {
        currentAngle = get_heading();
        move(leftVolt, rightVolt);
        pros::delay(30);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
 }

// need to test this out first. if it works, will add it for going backwards.
// rn it can only go straight
void move_straight(double desiredSpeed, double desiredDist) {
    double currDist = 0;
    while (currDist < desiredDist * 2/3) {
        double currSpeed = move_speed();
        double volt = PID(currSpeed, desiredSpeed, 1, 0, 0);
        move(volt, volt);

        currDist = distance();
        pros::delay(30);
    }
    while (currDist < desiredDist) {
        double currDist = distance();
        double volt = PID(currDist, desiredDist, 1, 0, 0);
        move(volt, volt);

        pros::delay(30);
    }
}
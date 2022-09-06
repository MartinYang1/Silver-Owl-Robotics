#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <math.h>
#include <vector>

/** Moves the robot continuously based on voltage. A negative
 * value moves the robot backwards, while a positive
 * value moves the robot forwards.
 * 
 * @param leftVolt the voltage of the motors on the left side
 * of the drive train, from -127 to 127 volts
 * @param rightVolt the voltage of the motors on the right side
 * of the drive train, from -127 to 127 volts
 */
void move(double leftVolt, double rightVolt){
    leftFrontMotor = leftVolt; leftMidMotor = leftVolt; leftBackMotor = leftVolt;
    rightFrontMotor = rightVolt; rightMidMotor = rightVolt; rightBackMotor = rightVolt;
}

// //closed loop movement using PID
// void move_closed_loop(double distanceLeft, double distanceRight){
//     double lastErrorLeft = 0.1;
//     double lastErrorRight = 0.1;
//     double startLeft = distance(leftBackMotor);
//     double startRight = distance(rightBackMotor);

//     while (lastErrorLeft + lastErrorRight != 0){
//         PID(distanceLeft, distance(leftBackMotor) - startLeft, &lastErrorLeft);
//         PID(distanceRight, distance(rightBackMotor) - startRight, &lastErrorRight);
//     }
// }

/** Turns the robot to a desired angle,
 * relative to its starting pos when the gyro sensor was calibrated
 * 
 * @param leftVolt the voltage for the motors on the left side 
 * of the drive train in volts, from -127 to 127
 * @param rightVolt the voltage for the motors on the right side 
 * of the drive train in volts, from -127 to 127
 * @param angle in degrees, to 2 decimal places. A negative angle turns the robot counter-clockwise
 * and a postive angle turns the robot clockwise
 */
void turn(const int leftVolt, const int rightVolt, float desiredAngle) {
    //  if (abs(leftVolt) > 127 || abs(rightVolt) > 127)
    //      throw std::out_of_range;
    
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
void move_straight(const int desiredVel, double desiredDist) {
    leftBackMotor.tare_position(); rightBackMotor.tare_position();
    leftMidMotor.tare_position(); rightMidMotor.tare_position();
    leftFrontMotor.tare_position(); rightFrontMotor.tare_position();
    double currDist = 0;

    while (currDist < desiredDist * 2/3) {
        double currSpeed = get_move_speed();
        double volt = PID(currSpeed, desiredVel, 0.5, 0, 0);
        move(volt, volt);

        currDist = get_dist_travelled();
        pros::delay(15);
    }

    while (currDist < desiredDist) {
        double currDist = abs(get_dist_travelled());
        double volt = static_cast<int>(get_move_voltage());
        volt *= 1.0 / PID(currDist, desiredDist, 0.00005, 0, 0, -1);
        volt = (desiredVel < 0) ? -volt : volt;
        move(volt, volt);

        pros::delay(15);
    }
    //move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

void move_straight(const unsigned time) {
    
}
#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"
#include "pros/motors.h"

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
void move(const int leftVolt, const int rightVolt){
    leftFrontMotor = leftVolt; leftBackMotor = leftVolt;
    rightFrontMotor = rightVolt; rightBackMotor = rightVolt;
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
 * @param baseLeftVolt the base voltage for the motors on the left side 
 * of the drive train in volts, from -127 to 127
 * @param baseRightVolt the voltage for the motors on the right side 
 * of the drive train in volts, from -127 to 127
 * @param desiredAngle in degrees, to 2 decimal places. A negative angle turns the robot counter-clockwise
 * and a postive angle turns the robot clockwise
 */
void turn(const int baseLeftVolt, const int baseRightVolt, int desiredAngle, vector *pCentre){
    int pos = 0;
    int R = desiredAngle / 360;
    int r = desiredAngle % 360;
    float p = imu_sensor.get_heading();
    int s = sgn(desiredAngle);
    float current_angle = imu_sensor.get_heading();
    float target_angleoof = current_angle + desiredAngle;
    float target_angle;
    if (target_angleoof > 360){
        float target_angle = target_angleoof - 360;
    }
    else{
        float target_angle = target_angleoof;
    }
   
    int revolutions = 0;
    while (revolutions < R){
        move(s*baseLeftVolt, -s*baseRightVolt);
        p = imu_sensor.get_heading();
        if (pos == 0) {
            if (current_angle - 9 < p && p < current_angle + 9){
                pos = 0;
            }
            else{
                pos = 1;
            }
        }
        if (pos == 1){
            if (current_angle - 9 < p && p < current_angle + 9){
                    revolutions ++;
                    pos = 0 ;
            }
            else{
                  pos = 1;
            }
        }
    }
    move(0, 0);
   
    while (target_angle - 8 < p && p < target_angle + 8){
        move(s*baseLeftVolt, -s*baseRightVolt);
        p = imu_sensor.get_heading();
           
    }
    move(0, 0);
}

/** Moves the robot a given distance forwards or backwards
 * 
 * @param desiredDist the distance to travel, in inches
 * @param stopType the type of brake mechanism the robot uses
 */
void move_straight(const double desiredDist, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    leftBackMotor.tare_position(); rightBackMotor.tare_position();
    //leftMidMotor.tare_position(); rightMidMotor.tare_position();
    leftFrontMotor.tare_position(); rightFrontMotor.tare_position();
    
    double currDist = 0; const unsigned baseVolt = 20;
    while (currDist < desiredDist) {
        const double volt = (desiredDist < 0) ? PID(currDist, desiredDist, 1, 0.1, 0.5) - baseVolt
                                            : PID(currDist, desiredDist, 1, 0.1, 0.5) + baseVolt;
        move(volt + PID(get_heading(), 0, 1, 0.02, 0.5), 
                volt - PID(get_heading(), 0, 1, 0.02, 0.5));
        currDist = get_dist_travelled();
        pros::delay(15);
    }
    move(stopType, stopType);
}

void move_straight(const float time, const int volt) {
    static unsigned timeElapsed = 0;    // in milliseconds
    while (timeElapsed < time * 1000) {
        move(volt, volt);
        ++timeElapsed;
        pros::delay(1);
    }
    move(MOTOR_BRAKE_HOLD, MOTOR_BRAKE_HOLD);
}

/** Moves the robot until the light sensor
 * detects the roller.
 * 
 * @param volt the voltage for the motors, from -127 to 127
 */
void move_straight(const int volt) {
    while (optical_sensor.get_proximity() < 255) {
        move(volt + PID(get_heading(), 0, 1, 0.02, 0.5), 
                volt - PID(get_heading(), 0, 1, 0.02, 0.5));
        pros::delay(15);
    }
    move(MOTOR_BRAKE_HOLD, MOTOR_BRAKE_HOLD);
}
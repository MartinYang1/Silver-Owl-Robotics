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
    leftFrontMotor = leftVolt; leftMidMotor = leftVolt; leftBackMotor = leftVolt;
    rightFrontMotor = rightVolt; rightMidMotor = rightVolt; rightBackMotor = rightVolt;
}

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
 void turn(const int baseLeftVolt, const int baseRightVolt, const int desiredAngle, vector *pCentre) {
    //  if (abs(leftVolt) > 127 || abs(rightVolt) > 127)
    //      throw std::out_of_range;
    int prevErrorHeading = 0, integralHeading = 0;
    float currentAngle = get_heading(); const int targetAngle = currentAngle + desiredAngle;
    if (desiredAngle > 0) {
        while (currentAngle < targetAngle) { 
            currentAngle = get_heading();
            move(baseLeftVolt + PID(currentAngle, targetAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                    baseRightVolt - PID(currentAngle, targetAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
            pros::delay(15);
        }
    }
    else {
        while (currentAngle > targetAngle) { 
            currentAngle = get_heading();
            move(baseLeftVolt + PID(currentAngle, targetAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                    baseRightVolt - PID(currentAngle, targetAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
            pros::delay(15);
        }
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
    pCentre->heading = get_heading(); pCentre->desiredHeading = get_heading();
}
// void turn(const int baseLeftVolt, const int baseRightVolt, int desiredAngle, vector *pCentre){
//     int pos = 0;
//     int R = abs(desiredAngle) / 360;
//     int r = desiredAngle % 360;
//     float p = imu_sensor.get_heading();
//         pros::delay(20);
//     int s = sgn(desiredAngle);
//     float current_angle = imu_sensor.get_heading();
//         pros::delay(40);
//     float desiredAngleoof = current_angle + desiredAngle;
//         pros::delay(20);
//     float desiredAngle;
//         pros::delay(20);
//     if (desiredAngleoof > 360){
//         desiredAngle = desiredAngleoof - 360;
//             pros::delay(50);
//     }
//     else if (desiredAngleoof < 0){
//         desiredAngle = desiredAngleoof + 360;
//             pros::delay(50);
//     }
//     else{
//         desiredAngle = desiredAngleoof;
//             pros::delay(50);
//     }
   
//     int revolutions = 0;
//     while (revolutions < R){
//             pros::delay(20);
//         move(s*baseLeftVolt, -s*baseRightVolt);
//         p = imu_sensor.get_heading();
//             pros::delay(20);
//         if (pos == 0) {
//                 pros::delay(50);
//             if (current_angle - 9 < p && p < current_angle + 9){
//                 pos = 0;
//                     pros::delay(20);
//             }
//             else{
//                 pos = 1;
//                     pros::delay(20);
//             }
//         }
//         if (pos == 1){
//             if (current_angle - 9 < p && p < current_angle + 9){
//                     revolutions ++;
//                     pos = 0 ;
//                         pros::delay(20);
//             }
//             else{
//                   pos = 1;
//                       pros::delay(20);
//             }
//         }
//     }
//         pros::delay(20);
//     move(0, 0);
//     p = imu_sensor.get_heading();
//     int prevErrorHeading = 0, integralHeading = 0;
//     while (p > desiredAngle+1 || p < desiredAngle-1) { 
//         //master.print(0, 0, "%f", desiredAngle);
//         p = imu_sensor.get_heading();
//         move(baseLeftVolt + PID(p, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
//                      baseRightVolt - PID(p, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
 
// }
//    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
//    pCentre -> heading = desiredAngle;
// }

/** Moves the robot a given distance forwards or backwards
 * 
 * @param desiredDist the distance to travel, in inches
 * @param stopType the type of brake mechanism the robot uses
 */
void move_straight(const double desiredDist, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double currDist = get_dist_travelled(); //const double targetDist = currDist + desiredDist;
    const unsigned baseVolt = 30;
    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;
    while (abs(currDist) < abs(desiredDist)) {
        const double volt = (desiredDist < 0) ? PID(currDist, desiredDist, 2.2, 0.1, 0.5, prevErrorDist, integralDist) - baseVolt
                                            : PID(currDist, desiredDist, 2.2, 0.1, 0.5, prevErrorDist, integralDist) + baseVolt;
        move(volt + PID(get_heading(), pCenter->desiredHeading, 1.1, 0.02, 0.7, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading, 1.1, 0.02, 0.7, prevErrorHeading, integralHeading));
        currDist = get_dist_travelled();
        pros::delay(15);
    }
    move(stopType, stopType);
    pCenter->heading = get_heading();
}

void move_straight(const double desiredDist, const int volt, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double currDist = get_dist_travelled(); //onst double targetDist = currDist + desiredDist;
    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;
    while (abs(currDist) < abs(desiredDist)) {
        move(volt + PID(get_heading(), pCenter->heading, 1.1, 0.02, 0.7, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->heading, 1.1, 0.02, 0.7, prevErrorHeading, integralHeading));
        currDist = get_dist_travelled();
        pros::delay(15);
    }
    move(stopType, stopType);
}

void move_straight(const float time, const int volt) {
    static unsigned timeElapsed = 0;    // in milliseconds
    pros::Task track_time(stopwatch, &timeElapsed);
    while (timeElapsed < time * 1000) {
        move(volt, volt);
        pros::delay(1);
    }
    track_time.remove();
    move(MOTOR_BRAKE_HOLD, MOTOR_BRAKE_HOLD);
}

/** Moves the robot until the light sensor
 * detects the roller.
 * 
 * @param volt the voltage for the motors, from -127 to 127
 */
void move_straight(const int volt) {
    int prevErrorDist = 0, integralDist = 0;
    while (optical_sensor.get_proximity() < 255) {
        move(volt + PID(get_heading(), 0, 1, 0.02, 0.5, prevErrorDist, integralDist), 
                volt - PID(get_heading(), 0, 1, 0.02, 0.5, prevErrorDist, integralDist));
        pros::delay(15);
    }
    move(MOTOR_BRAKE_HOLD, MOTOR_BRAKE_HOLD);
}
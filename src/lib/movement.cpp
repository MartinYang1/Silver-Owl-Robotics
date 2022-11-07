#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"
#include "pros/motors.h"

#include <cmath>
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
 * @param pCenter the pointer to the vector data structure for the robot
 */

void turn(const int baseLeftVolt, const int baseRightVolt, double desiredAngle, vector *pCentre) {
    int prevErrorHeading = 0, integralHeading = 0;
    double currAngle = imu_sensor.get_heading();
    
    if (baseLeftVolt > baseRightVolt) {
        if (currAngle < desiredAngle) {
            while (currAngle < desiredAngle) { 
                currAngle = imu_sensor.get_heading();         
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                pros::delay(15);
            }
        }
        else if (currAngle > desiredAngle) {
            desiredAngle = desiredAngle + (360 - currAngle);
            currAngle = 0; double prevAngle = imu_sensor.get_heading();
            
            while (currAngle + 2 < desiredAngle) {
                if (imu_sensor.get_heading() - prevAngle < -2) 
                    prevAngle = imu_sensor.get_heading();
                currAngle += imu_sensor.get_heading() - prevAngle;
                
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                prevAngle = imu_sensor.get_heading();  
                pros::delay(15);
            }
        }
    }
    else {
        if (0 <= currAngle && desiredAngle > currAngle) {
            desiredAngle = -(currAngle + (360 - desiredAngle));
            currAngle = 0; double prevAngle = imu_sensor.get_heading();
            
            while (currAngle - 2 > desiredAngle) {
                if (imu_sensor.get_heading() - prevAngle > 2) 
                    prevAngle = imu_sensor.get_heading();
                currAngle += imu_sensor.get_heading() - prevAngle;
                
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                prevAngle = imu_sensor.get_heading();
                pros::delay(15);
            }
        }
        else if (currAngle < 360 && currAngle > desiredAngle) {
            desiredAngle = desiredAngle - 360;
            currAngle -= 360;  
            
            while (currAngle > desiredAngle) {
                currAngle = imu_sensor.get_heading() - 360;
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                pros::delay(15);
            }
        }
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
    pros::delay(100);
    pCentre->heading = imu_sensor.get_heading(); pCentre->desiredHeading = desiredAngle;
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
 * @param pCenter the pointer to the vector data structure for the robot
 * @param stopType the type of brake mechanism the robot uses
 */
void move_straight(const double desiredDist, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double prevLeftPos, prevRightPos;
    double currDist = 0;
    
    const unsigned baseVolt = 30;
    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;
    while (abs(currDist) < abs(desiredDist)) {
        const double volt = (desiredDist < 0) ? PID(currDist, desiredDist, 2, 0, -0.2, prevErrorDist, integralDist) - baseVolt
                                            : PID(currDist, desiredDist, 2, 0, -0.2, prevErrorDist, integralDist) + baseVolt;
        if (pCenter->desiredHeading > 180)
            move(volt + PID(get_heading(), pCenter->desiredHeading-360, 0.9, 0.01, 1, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading-360, 0.9, 0.01, 1, prevErrorHeading, integralHeading));
        else
            move(volt + PID(get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading));

        currDist += (leftMidMotor.get_position()-prevLeftPos + rightMidMotor.get_position()-prevRightPos)/2 
                    * motorToWheelRatio/360*(M_PI*wheelDiam);
        
        prevLeftPos = leftMidMotor.get_position(), prevRightPos = rightMidMotor.get_position();
        pros::delay(15);
    }
    move(stopType, stopType);
    pros::delay(200);
    pCenter->heading = imu_sensor.get_heading();
}

void move_straight(const double desiredDist, const int volt, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double currDist = get_dist_travelled(); //onst double targetDist = currDist + desiredDist;
    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;
    while (abs(currDist) < abs(desiredDist)) {
        move(volt + PID(imu_sensor.get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading), 
                volt - PID(imu_sensor.get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading));
        currDist = get_dist_travelled();
        pros::delay(15);
    }
    move(stopType, stopType);
    pros::delay(200);
    pCenter->heading = imu_sensor.get_heading();
}

/** Moves the robot a given amount of time forwards or backwards
 * 
 * @param time the time to travel for, in seconds
 * @param volt the voltage for the drive train motors
*/
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

/** Moves the robot forwards until the light sensor
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
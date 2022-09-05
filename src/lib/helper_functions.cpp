/*
 * Functions that support the usage of other functions,
 * such as PID(), go here
 */

#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"

#include <math.h>

/** Gets the distance travelled in the x-y plane by the robot
 * 
 * @return the distance travelled by the motors, in inches
 */
inline double get_dist_travelled() {
    return (leftBackMotor.get_position() + rightBackMotor.get_position()
            + leftMidMotor.get_position() + rightMidMotor.get_position()
            + leftFrontMotor.get_position() + rightFrontMotor.get_position())/6 / (M_PI*wheelDiam);

}

/** Gets the heading of the robot from its gyro sensor
 * relative to its initial direction. A clockwise turn
 * is in positive degrees, whereas a counter-clockwise turn
 * is in negative degrees.
 * 
 * @returns the heading of the robot in degrees,
 * in the range (-180, 180]
 */
inline double get_heading() {
    double heading = imu_sensor.get_heading();
    if (heading > 180)
        heading -= 360;  // sets the heading to a neg val if the robot's heading is counterclockwise
    return heading;
}

/** Gets the speed of the robot's drive train
 * 
 * @return the speed in RPM of the robot's drive train
 */
inline double move_speed() {
    return (leftBackMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()
         + leftFrontMotor.get_actual_velocity() + rightFrontMotor.get_actual_velocity()) / 4;
}

/** A general-purpose PID function that provides the correction
 * needed for a given system
 * 
 * @param input the input from the system
 * @param target the value the system is trying to achieve
 * @param Kp the proportional constant
 * @param Ki the integral constant
 * @param Kd the derivative constant
 * @return the correction feedback for the system
 */
double PID(double input, double target, double Kp, double Ki, double Kd) {
    static int prevError = 0, integral = 0;
    
    double error = target - input;
    double derivative = error - prevError;  // only an approximation
    integral = 0.5 * integral + error;  // only an approximation
    prevError = error;

    return Kp * error + Kd * derivative + Ki * integral;
}
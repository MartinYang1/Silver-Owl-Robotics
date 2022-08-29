/*
 * Functions that support the usage of other functions,
 * such as PID(), go here
 */

#include "../include/main.h"
#include "../globals/globals.hpp"

struct vector {
    double heading;
    double dist;
};

/** Gets the heading of the robot from its gyro sensor
 * relative to its initial direction. A clockwise turn
 * is in positive degrees, whereas a counter-clockwise turn
 * is in negative degrees.
 * 
 * @returns the heading of the robot in degrees,
 * in the range (-180, 180]
 */
inline double get_heading() {
    double heading = inertialSensor.get_heading();
    if (heading > 180)
        heading -= 360;  // sets the heading to a neg val if the robot's heading is counterclockwise
    return heading;
}

/** Gets the speed of the robot's drive train
 * 
 * @return the speed in RPM of the robot's drive train
 */
constexpr double move_speed() {
    return (leftBackMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()
         + leftFrontMotor.get_actual_velocity() + rightFrontMotor.get_actual_velocity()) / 4
}

double PID(double destination, double current, double *pLastError){
    unsigned int elapsedTime = 0;
	static unsigned int previousTime = pros::millis();

    double Kp = 0.01;
    double Ki = 0.01;
    double Kd = 0.01;

    double error = destination - current;
    double culmanativeError = error * elapsedTime;
    double rateError = (error - *pLastError)/elapsedTime;

    double output = Kp * error + Ki * culmanativeError + Kd * rateError;

    //cleanup for next thing
    *pLastError = error;
    previousTime = pros::millis();

    return output;
}
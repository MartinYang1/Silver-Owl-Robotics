/*
 * Functions that support the usage of other functions,
 * such as PID(), go here
 */

#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <math.h>

const double wheelDiam = 4;
const double motorToWheelRatio = 200.0 / 360;
const double robotWidth = 14;

/** Gets the distance travelled in a linear path by the robot
 * 
 * @return the distance travelled by the motors, in inches
 */
double get_dist_travelled() {
    double degreesTravelled = (leftBackMotor.get_position() + rightBackMotor.get_position()
            + leftFrontMotor.get_position() + rightFrontMotor.get_position()) / 4;
    degreesTravelled /= 2;  // for some reason the motor encoder values are exactly 2 times less than how far the motor moves,
                            // so we are dividing by 2. This needs to be fixed when we have time.
    return degreesTravelled * (1/motorToWheelRatio) / 360 * (M_PI*wheelDiam);
}

/** Gets the heading of the robot from its gyro sensor
 * relative to its initial direction. A clockwise turn
 * is in positive degrees, whereas a counter-clockwise turn
 * is in negative degrees.
 * 
 * @returns the heading of the robot in degrees,
 * in the range (-180, 180]
 */
double get_heading() {
    double heading = imu_sensor.get_heading();
    if (heading > 180)
        heading -= 360;  // sets the heading to a neg val if the robot's heading is counterclockwise
    return heading;
}

/** Gets the speed of the robot's drive train
 * 
 * @return the speed in RPM of the robot's drive train
 */
double get_move_speed() {
    return (leftBackMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()
            + leftFrontMotor.get_actual_velocity() + rightFrontMotor.get_actual_velocity())/4 * (1.0/motorToWheelRatio);
}

/** Gets the voltage that the drive train motors are running at
 * 
 * @return the voltage, in volts
 */
double get_move_voltage() {
    return (leftBackMotor.get_voltage() + rightBackMotor.get_voltage()
            + leftFrontMotor.get_voltage() + rightFrontMotor.get_voltage())/4.0 / 1000;
}

/** A general-purpose PID function that provides the correction
 * needed for a given system
 * 
 * @param input the input from the system
 * @param target the value the system is trying to achieve
 * @param Kp the proportional constant
 * @param Ki the integral constant
 * @param Kd the derivative constant
 * @param direction the direction of the correction
 * @return the correction feedback for the system
 */
double PID(double input, double target, double Kp, double Ki, double Kd, int direction) {
    static int prevError = 0, integral = 0;
    
    double error = (target - input) * direction;
    double derivative = error - prevError;  // only an approximation
    integral = 0.5 * integral + error;  // only an approximation
    prevError = error;

    return Kp * error + Kd * derivative + Ki * integral;
}

void odometry(vector *pCentre) {
    float robotWidth =14;
    double L = leftMidMotor.get_position()/motorToWheelRatio;
    double R = rightMidMotor.get_position()/motorToWheelRatio;
    // the angle turned
    float alpha = (R - L) / robotWidth;
    master.print(0, 0, "%f", alpha);
    pros::delay(50);
    double hypotenuse = 2 * (L/alpha + robotWidth/2) * sin(alpha/2);

    double deltaX = hypotenuse * cos(pCentre->heading + alpha/2);
    double deltaY = hypotenuse * sin(pCentre->heading + alpha/2);

    pCentre->heading += alpha;
    pCentre->x += deltaX; pCentre->y += deltaY;
}
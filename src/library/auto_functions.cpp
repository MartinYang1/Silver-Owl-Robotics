#include "../include/main.h"
#include "../globals/globals.hpp"

//returns the distance of the wheel inputted, this allows better PID and odometry
double distance(wheel){
    double distConst = 22.305; //tune this number
    return wheel.get_position()/distConst;
}

//same old move function
void setVoltage(double left, double right){
    left_front = left;
    left_back = left;
    right_front = right;
    right_back = right;
}


//one PID of many
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

//closed loop movement using PID
void move(double distanceLeft, double distanceRight){
    double lastErrorLeft = 0.1;
    double lastErrorRight = 0.1;
    double startLeft = distance(left_back);
    double startRight = distance(right_back);

    while (lastErrorLeft + lastErrorRight != 0){
        PID(distanceLeft, distance(left_back) - startLeft, &lastErrorLeft);
        PID(distanceRight, distance(right_back) - startRight, &lastErrorRight);
    }
 }

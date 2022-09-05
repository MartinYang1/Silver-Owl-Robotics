#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor leftFrontMotor(3,1);
pros::Motor rightFrontMotor(10);
pros::Motor leftBackMotor(12);
pros::Motor rightBackMotor(19,1);;
pros::Motor leftMidMotor(4); 
pros::Motor rightMidMotor(9,1); 

pros::Imu imu_sensor(17);

int autonSelection = SKILLS; // default auton selected
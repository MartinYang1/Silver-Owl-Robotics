#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFrontMotor(5);
pros::Motor rightFrontMotor(5);
pros::Motor leftBackMotor(5);
pros::Motor rightBackMotor(5);
pros::Imu inertialSensor(5);


int autonSelection = SKILLS; // default auton selected
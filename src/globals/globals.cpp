#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor leftFrontMotor(3,1);
pros::Motor rightFrontMotor(10);
pros::Motor leftBackMotor(12);
pros::Motor rightBackMotor(19,1);
pros::Motor leftMidMotor(4); 
pros::Motor rightMidMotor(9,1); 
pros::Motor intake(5); 
pros::Motor flywheel(20); 


pros::Vision vision_sensor(13);

pros::Imu imu_sensor(17);
pros::ADIDigitalOut expander1(2);
pros::ADIDigitalOut expander2(3);
pros::ADIDigitalOut pusher(1);

int autonSelection = SKILLS; // default auton selected
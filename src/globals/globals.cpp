#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// drive train
pros::Motor leftFrontMotor(3,1);
pros::Motor rightFrontMotor(10);
pros::Motor leftBackMotor(12);
pros::Motor rightBackMotor(19,1);
pros::Motor leftMidMotor(4); 
pros::Motor rightMidMotor(9,1); 

// disc mechanisms
pros::Motor intake(5);
pros::Motor &roller = intake;
pros::Motor flywheel(20); 

// sensors
pros::Vision vision_sensor(13);
pros::Imu imu_sensor(17);
pros::Optical optical_sensor(18);

// pneumatics pistons
pros::ADIDigitalOut expander1_piston(3);
pros::ADIDigitalOut expander2_piston(4);
pros::ADIDigitalOut flywheel_piston(1);

int autonSelection = SKILLS; // default auton selected
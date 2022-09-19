#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// drive train
pros::Motor leftFrontMotor(4,1);
pros::Motor rightFrontMotor(3);
pros::Motor leftBackMotor(18, 1);
pros::Motor rightBackMotor(6);
pros::Motor leftMidMotor(4); 
pros::Motor rightMidMotor(9,1); 

// disc mechanisms
pros::Motor intake(19);
pros::Motor intake2(20, 1);
pros::Motor &roller = intake;
pros::Motor &roller2 = intake2;
pros::Motor flywheel(20); 

// sensors
pros::Vision vision_sensor(13);
pros::Imu imu_sensor(16);
pros::Optical optical_sensor(17);

// pneumatics pistons
pros::ADIDigitalOut expander1_piston(3);
pros::ADIDigitalOut expander2_piston(4);
pros::ADIDigitalOut flywheel_piston(1);

int autonSelection = SKILLS; // default auton selected
#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// drive train
pros::Motor leftFrontMotor(2, MOTOR_GEAR_BLUE,1);
pros::Motor rightFrontMotor(1, MOTOR_GEAR_BLUE, 0);
pros::Motor leftBackMotor(3, MOTOR_GEAR_BLUE, 1);
pros::Motor rightBackMotor(5, MOTOR_GEAR_BLUE, 0);
pros::Motor leftMidMotor(4, MOTOR_GEAR_BLUE,1); 
pros::Motor rightMidMotor(6, MOTOR_GEAR_BLUE, 0); 

// disc mechanisms
pros::Motor intake(7);
pros::Motor &roller = intake;
pros::Motor &indexer = intake;  // the flex wheel indexer for the shooter
pros::Motor flywheel(18, MOTOR_GEAR_RED, 1);  

// sensors
pros::Vision vision_sensor(19);
pros::Imu imu_sensor(12);
pros::Optical optical_sensor(20);

// pneumatics pistons
pros::ADIDigitalOut expander1_piston(8);
pros::ADIDigitalOut expander2_piston(3);
pros::ADIDigitalOut flywheel_piston(6);  // the gate for the flywheel

int autonSelection = SKILLS; // default auton selected
#include "../../include/main.h"
#include "globals.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);

// drive train
pros::Motor leftFrontMotor(11, MOTOR_GEAR_BLUE, 1);
pros::Motor rightFrontMotor(15, MOTOR_GEAR_BLUE);
pros::Motor leftBackMotor(14, MOTOR_GEAR_BLUE, 1);
pros::Motor rightBackMotor(3, MOTOR_GEAR_BLUE);
pros::Motor leftMidMotor(12, MOTOR_GEAR_BLUE,1); 
pros::Motor rightMidMotor(2, MOTOR_GEAR_BLUE); 

// disc mechanisms
pros::Motor intake(4);
pros::Motor intake2(20, 1);
pros::Motor &roller = intake;
pros::Motor &roller2 = intake2;
pros::Motor flywheel(10, MOTOR_GEAR_BLUE, 1);    
pros::Motor flywheel2(6, MOTOR_GEAR_BLUE);

// sensors
pros::Vision vision_sensor(9);
pros::Imu imu_sensor(8);
pros::Optical optical_sensor(17);

// pneumatics pistons
pros::ADIDigitalOut expander1_piston(8);
pros::ADIDigitalOut expander2_piston(1);
pros::ADIDigitalOut flywheel_piston(6);

int autonSelection = SKILLS; // default auton selected
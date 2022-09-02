#include "../../include/main.h"
#include "globals.hpp"
using namespace pros;
Controller master(pros::E_CONTROLLER_MASTER);
Motor leftFrontMotor(3,1);
Motor rightFrontMotor(10);
Motor leftMiddleMotor(4);
Motor rightMiddleMotor(9,1);
Motor leftBackMotor(12,1);
Motor rightBackMotor(19,1);
Motor intake(20);
Motor flywheel(5);
pros::Imu imu_sensor();
ADIDigitalOut pusher(1);
ADIDigitalOut expander_1(2);
ADIDigitalOut expander_2(3);



int autonSelection = SKILLS; // default auton selected
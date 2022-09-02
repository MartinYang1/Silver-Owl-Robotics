#include "../../include/main.h"
#include "globals.hpp"
using namespace pros;
Controller master(pros::E_CONTROLLER_MASTER);
Motor left_front(3,1);
Motor right_front(10);
Motor left_middle(4);
Motor right_middle(9,1);
Motor left_back(12,1);
Motor right_back(19,1);
Motor intake(20);
Motor flywheel(5);
pros::Imu imu_sensor();
ADIDigitalOut pusher(1);
ADIDigitalOut expander_1(2);
ADIDigitalOut expander_2(3);



int autonSelection = SKILLS; // default auton selected
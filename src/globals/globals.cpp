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

<<<<<<< HEAD
=======
pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor leftFrontMotor(3,1);
pros::Motor rightFrontMotor(10);
pros::Motor leftBackMotor(12,1);
pros::Motor rightBackMotor(19,1);;
pros::Motor leftMidMotor(4); 
pros::Motor rightMidMotor(9,1); 

pros::Motor lift(12);   // ignore
pros::Motor indexer1(1, 1); //fly
pros::Motor indexer2(2); //fly
pros::Motor indexer3(19); //intake
pros::ADIDigitalOut front_goal_grappler(1); //Pneumatics
pros::ADIDigitalOut back_goal_grappler(2); //Pneumatics 2
pros::ADIDigitalOut expander(3); //Pneumatics 3 expander release
pros::ADIDigitalOut expander2(4);

pros::Motor indexer4(20, 1); //intake

pros::Imu imu_sensor(16);

pros::ADIUltrasonic sonar(10, 6);

>>>>>>> 847f87f39db393a1a3f81b4968b4afafd4833c67


int autonSelection = SKILLS; // default auton selected
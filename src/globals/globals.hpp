#ifndef GLOBALS_H
#define GLOBALS_H

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern pros::Controller master;

extern pros::Motor leftFrontMotor;
extern pros::Motor rightFrontMotor;
extern pros::Motor leftBackMotor;
extern pros::Motor rightBackMotor;
extern pros::Motor leftMidMotor;
extern pros::Motor rightMidMotor;

extern pros::Motor lift;
extern pros::Motor indexer1;
extern pros::Motor indexer2;
extern pros::Motor indexer3;
extern pros::Motor indexer4;
extern pros::Motor indexer;
extern pros::ADIDigitalOut front_goal_grappler;
extern pros::ADIDigitalOut back_goal_grappler;
extern pros::ADIDigitalOut expander;
extern pros::ADIDigitalOut expander2;

extern pros::Imu imu_sensor;

extern pros::ADIUltrasonic sonar;

extern int autonSelection;

enum AutonEnum {S_BLUE5 = -1, B_BLUE3 = -2, S_BLUE7 = -3, S_BLUE8 = -4, B_BLUE6_C = -5, S_RED5 = 1, B_RED3 = 2, S_RED7 = 3, S_RED8 = 4, B_RED6_C = 5, NOTHING = 10, SKILLS = 0};

template<typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif

